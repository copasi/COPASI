/////////////////////////////////////////////////////////////////////////////
// CModel
// model.cpp : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <limits.h>

#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif //DBL_MAX

#define  COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "utilities/utilities.h"
#include "CModel.h"
#include "CCompartment.h"
#include "CState.h"
#include "tnt/luX.h"
#include "tnt/triang.h"
#include "tnt/transv.h"
#include "utilities/CGlobals.h"

using std::cout;

CModel::CModel()
{
  CONSTRUCTOR_TRACE;
  mComments = "";

  mpLView
  = new TNT::UnitLowerTriangularView <TNT::Matrix <C_FLOAT64 > > (mL);

  mpInverseLView
  = new TNT::Transpose_View<TNT::UpperTriangularView<TNT::Matrix<C_FLOAT64 > > > (mL);

  mQuantityUnitName = "unknown";
  mNumber2QuantityFactor = 1.0;
  mQuantity2NumberFactor = 1.0;
}

CModel::CModel(const CModel & src)
{
  CONSTRUCTOR_TRACE;
  mpLView
  = new TNT::UnitLowerTriangularView <TNT::Matrix <C_FLOAT64 > > (mL);

  mpInverseLView
  = new TNT::Transpose_View<TNT::UpperTriangularView<TNT::Matrix<C_FLOAT64 > > > (mL);

  mTitle = src.mTitle;
  mComments = src.mComments;

  mCompartments = CCopasiVectorNS < CCompartment >(src.mCompartments);
  mSteps = CCopasiVectorNS < CReaction >(src.mSteps);

  mQuantityUnitName = src.mQuantityUnitName;
  mNumber2QuantityFactor = src.mNumber2QuantityFactor;
  mQuantity2NumberFactor = src.mQuantity2NumberFactor;

  unsigned C_INT32 i, imax = mSteps.size();

  for (i = 0; i < imax; i++)
    mSteps[i]->compile(mCompartments);

  initializeMetabolites();

  compile();
}

CModel::~CModel()
{
  delete mpLView;
  delete mpInverseLView;

  cleanup();
  DESTRUCTOR_TRACE;
}

void CModel::cleanup()
{
  /* The real objects */
  mCompartments.cleanup();
  mSteps.cleanup();
  mMoieties.cleanup();

  /* The references */
  mStepsX.clear();
  mStepsInd.clear();

  mMetabolites.clear();
  mMetabolitesX.clear();
  mMetabolitesInd.clear();
  mMetabolitesDep.clear();

  mFluxes.clear();
  mFluxesX.clear();
}

C_INT32 CModel::load(CReadConfig & configBuffer)
{
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
  unsigned C_INT32 i;

  // For old Versions we must read the list of Metabolites beforehand

  if (configBuffer.getVersion() < "4")
    {
      if ((Fail = configBuffer.getVariable("TotalMetabolites", "C_INT32",
                                           &Size, CReadConfig::LOOP)))
        return Fail;

      Copasi->OldMetabolites.load(configBuffer, Size);

      Copasi->Model = this;
    }

  if ((Fail = configBuffer.getVariable("Title", "string", &mTitle,
                                       CReadConfig::LOOP)))
    return Fail;

  try
    {
      Fail = configBuffer.getVariable("Comments", "multiline", &mComments,
                                      CReadConfig::SEARCH);
    }

  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        mComments = "";
      else
        throw Exception;
    }

  try
    {
      Fail = configBuffer.getVariable("ConcentrationUnit", "string", &mQuantityUnitName,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        mQuantityUnitName = "unknown";
      else
        throw Exception;
    }

  setQuantityUnit(mQuantityUnitName); // set the factors

  if ((Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mCompartments.load(configBuffer, Size);

  if (configBuffer.getVersion() < "4")
    {
      // Create the correct compartment / metabolite relationships
      CMetab Metabolite;

      for (i = 0; i < Copasi->OldMetabolites.size(); i++)
        {
          Metabolite.cleanup();
          Metabolite = *Copasi->OldMetabolites[i];
          mCompartments[Copasi->OldMetabolites[i]->getIndex()]->
          addMetabolite(Metabolite);
        }
    }

  //cout << mCompartments;       //debug

  initializeMetabolites();

  if ((Fail = Copasi->FunctionDB.load(configBuffer)))
    return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mSteps.load(configBuffer, Size);

  // cout << endl << mSteps << endl;  //debug

  // We must postprocess the steps for old file versions
  if (configBuffer.getVersion() < "4")
    for (i = 0; i < mSteps.size(); i++)
      mSteps[i]->old2New(mMetabolites);

  // cout << "After postprocessing " << endl << mSteps << endl;

  for (i = 0; i < mSteps.size(); i++)
    mSteps[i]->compile(mCompartments);

  // cout << "After compiling " << endl << mSteps << endl;   //debug

  Copasi->OldMetabolites.cleanup();

  return Fail;
}

C_INT32 CModel::save(CWriteConfig & configBuffer)
{
  C_INT32 Size;
  C_INT32 Fail = 0;

  if ((Fail = configBuffer.setVariable("Title", "string", &mTitle)))
    return Fail;

  if ((Fail = configBuffer.setVariable("Comments", "multiline", &mComments)))
    return Fail;

  if ((Fail = configBuffer.setVariable("ConcentrationUnit", "string", &mQuantityUnitName)))
    return Fail;

  Size = mCompartments.size();

  if ((Fail = configBuffer.setVariable("TotalCompartments", "C_INT32", &Size)))
    return Fail;

  mCompartments.save(configBuffer);

  if ((Fail = Copasi->FunctionDB.save(configBuffer)))
    return Fail;

  Size = mSteps.size();

  if ((Fail = configBuffer.setVariable("TotalSteps", "C_INT32", &Size)))
    return Fail;

  mSteps.save(configBuffer);

  return Fail;
}

C_INT32 CModel::saveOld(CWriteConfig & configBuffer)
{
  C_INT32 i, Size;
  C_INT32 Fail = 0;

  if ((Fail = configBuffer.setVariable("Title", "string", &mTitle)))
    return Fail;
  Size = mMetabolites.size();
  if ((Fail = configBuffer.setVariable("TotalMetabolites", "C_INT32", &Size)))
    return Fail;
  Size = mSteps.size();
  if ((Fail = configBuffer.setVariable("TotalSteps", "C_INT32", &Size)))
    return Fail;
  Size = mMoieties.size();
  if ((Fail = configBuffer.setVariable("TotalMoieties", "C_INT32", &Size)))
    return Fail;
  Size = mCompartments.size();
  if ((Fail = configBuffer.setVariable("TotalCompartments", "C_INT32", &Size)))
    return Fail;
  if ((Fail = Copasi->FunctionDB.saveOld(configBuffer)))
    return Fail;
  Size = mMetabolites.size();
  for (i = 0; i < Size; i++)
    mMetabolites[i]->saveOld(configBuffer);
  Size = mMoieties.size();
  for (i = 0; i < Size; i++)
    mMoieties[i]->saveOld(configBuffer);
  Size = mSteps.size();
  for (i = 0; i < Size; i++)
    mSteps[i]->saveOld(configBuffer, getMetabolites());
  Size = mCompartments.size();
  for (i = 0; i < Size; i++)
    mCompartments[i]->saveOld(configBuffer);
  if ((Fail = configBuffer.setVariable("Comments", "multiline", &mComments)))
    return Fail;
  return Fail;
}

void CModel::saveSBML(std::ofstream &fout)
{
  string tmpstr, tmpstr2;
  C_INT32 i, p, dummy;

  fout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fout << "<!-- Created by COPASI version " << Copasi->ProgramVersion.getVersion() << " -->" << endl;
  // TODO: add time stamp to the comment string
  fout << "<sbml xmlns=\"http://www.sbml.org/sbml/level1\" level=\"1\" version=\"1\">" << endl;
  FixSName(mTitle, tmpstr);
  fout << "\t<model name=\"" + tmpstr + "\">" << endl;
  // model notes
  if (! mComments.empty())
    {
      fout << "\t\t<notes>" << endl;
      fout << "\t\t\t<body xmlns=\"http://www.w3.org/1999/xhtml\">" << endl;
      tmpstr = mComments;
      for (i = 0; i != -1; )
        {
          p = tmpstr.find_first_of("\r\n");
          FixXHTML(tmpstr.substr(0, p), tmpstr2);
          fout << "\t\t\t\t<p>" << tmpstr2 << "</p>" << endl;
          i = tmpstr.find('\n');
          tmpstr = tmpstr.substr(i + 1);
        }
      fout << "\t\t\t</body>" << endl;
      fout << "\t\t</notes>" << endl;
    }
  fout << "\t\t<listOfCompartments>" << endl;
  // compartments
  for (i = 0; i < mCompartments.size(); i++)
    mCompartments[i]->saveSBML(fout);
  fout << "\t\t</listOfCompartments>" << endl;
  fout << "\t\t<listOfSpecies>" << endl;
  for (i = 0; i < mMetabolites.size(); i++)
    mMetabolites[i]->saveSBML(fout);
  // check if any reaction has no substrates or no products
  // (necessary because SBML l1v1 does not support empty subs or prods)
  for (dummy = i = 0; (i < mSteps.size()) && (dummy == 0); i++)
    if ((mSteps[i]->getSubstrateNumber() == 0) || (mSteps[i]->getProductNumber()))
      dummy = 1;
  // if there are any, we need a dummy metabolite, let's call it _void !
  if (dummy)
    {
      fout << "\t\t\t<specie name=\"_void_\"";
      FixSName(mCompartments[0]->getName(), tmpstr);
      fout << " compartment=\"" << tmpstr << "\"";
      fout << " initialAmount=\"0.0\" boundaryCondition=\"true\"/>" << endl;
    }
  fout << "\t\t</listOfSpecies>" << endl;
  fout << "\t\t<listOfReactions>" << endl;
  for (i = 0; i < mSteps.size(); i++)
    mSteps[i]->saveSBML(fout, i);
  fout << "\t\t</listOfReactions>" << endl;
  fout << "\t</model>" << endl;
  fout << "</sbml>" << endl;
}

void CModel::compile()
{
  buildStoi();
  lUDecomposition();
  setMetabolitesStatus();
  buildRedStoi();
  buildL();
  buildMoieties();
}

void CModel::buildStoi()
{
  CCopasiVector < CChemEqElement > Structure;
  unsigned C_INT32 i, j, k, imax;
  string Name;

  imax = mMetabolites.size();
  mMetabolitesX.resize(imax);
  j = 0;

  // We reorder mMetabolitesX so that the fixed metabolites appear at the end.

  for (i = 0; i < imax; i++)
    if (mMetabolites[i]->getStatus() == METAB_FIXED)
      mMetabolitesX[imax - ++j] = mMetabolites[i];
    else
      mMetabolitesX[i - j] = mMetabolites[i];

  // Update mMetabolites to reflect the reordering.
  // We need to to this to allow the use of the full model for simulation.
  // :TODO: This most definitely breaks output when reading Gepasi files.
  //        CGlobal::OldMetabolites is still in the expexted order !!!
  for (i = 0; i < imax; i++)
    mMetabolites[i] = mMetabolitesX[i];

  mFluxes.resize(mSteps.size());

  for (i = 0; i < mSteps.size(); i++)
    mFluxes[i] = & mSteps[i]->getFlux();

  mStoi.newsize(imax - j, mSteps.size());

  for (i = 0; i < (unsigned C_INT32) mStoi.num_cols(); i++)
    {
      Structure = mSteps[i]->getChemEq().getBalances();

      for (j = 0; j < (unsigned C_INT32) mStoi.num_rows(); j++)
        {
          mStoi[j][i] = 0.0;
          Name = mMetabolites[j]->getName();
          // Name = mMetabolitesX[j]->getName();

          for (k = 0; k < Structure.size(); k++)
            if (Structure[k]->getMetaboliteName() == Name)
              {
                mStoi[j][i] = Structure[k]->getMultiplicity();
                break;
              }
        }
    }

#ifdef DEBUG_MATRIX
  cout << "Stoichiometry Matrix" << endl;
  cout << mStoi << endl;
#endif

  return;
}

void CModel::lUDecomposition()
{
  unsigned C_INT32 i;

  TNT::Vector < unsigned C_INT32 > rowLU(mStoi.num_rows());
  TNT::Vector < unsigned C_INT32 > colLU(mStoi.num_cols());

  mRowLU.resize(mStoi.num_rows());
  for (i = 0; i < mRowLU.size(); i++)
    mRowLU[i] = i;

  mColLU.resize(mStoi.num_cols());
  for (i = 0; i < mColLU.size(); i++)
    mColLU[i] = i;

  mLU = mStoi;

  TNT::LUX_factor(mLU, rowLU, colLU);

#ifdef DEBUG_MATRIX

  TNT::UpperTriangularView < TNT::Matrix < C_FLOAT64 > > U(mLU);
  TNT::UnitLowerTriangularView < TNT::Matrix < C_FLOAT64 > > L(mLU);

  cout << "U" << endl;
  cout << U << endl;
  cout << "L" << endl;
  cout << L << endl;
#endif

  // mMetabolitesX = mMetabolites;

  mStepsX.resize(mSteps.size());

  for (i = 0; i < mSteps.size(); i++)
    mStepsX[i] = mSteps[i];

  // permutate Metabolites and Steps to match rearangements done during
  // LU decomposition

  // Create a more understandable permutation vector for row and column
  // interchanges

  CMetab *pMetab;
  unsigned C_INT32 tmp;

  for (i = 0; i < (unsigned C_INT32) rowLU.size(); i++)
    {
      if (rowLU[i] - 1 > i)
        {
          pMetab = mMetabolitesX[i];
          mMetabolitesX[i] = mMetabolitesX[rowLU[i] - 1];
          mMetabolitesX[rowLU[i] - 1] = pMetab;

          tmp = mRowLU[i];
          mRowLU[i] = mRowLU[rowLU[i] - 1];
          mRowLU[rowLU[i] - 1] = tmp;
        }
    }

  CReaction *pStep;

  for (i = colLU.size(); 0 < i--; )
    {
      if (colLU[i] - 1 < i)
        {
          pStep = mStepsX[i];
          mStepsX[i] = mStepsX[colLU[i] - 1];
          mStepsX[colLU[i] - 1] = pStep;

          tmp = mColLU[i];
          mColLU[i] = mColLU[colLU[i] - 1];
          mColLU[colLU[i] - 1] = tmp;
        }
    }

  mFluxesX.resize(mStepsX.size());

  for (i = 0; i < mStepsX.size(); i++)
    mFluxesX[i] = &mStepsX[i]->getFlux();

  return;
}

void CModel::setMetabolitesStatus()
{
  C_INT32 i, j, k;
  C_FLOAT64 Sum;

  // for (i=0; i<min(mLU.num_rows(), mLU.num_cols()); i++)
  // for compiler
  C_INT32 imax = (mLU.num_rows() < mLU.num_cols()) ?
                 mLU.num_rows() : mLU.num_cols();

  for (i = 0; i < imax; i++)
    {
      if (mLU[i][i] == 0.0)
        break;

      mMetabolitesX[i]->setStatus(METAB_VARIABLE);
    }

  mMetabolitesInd.clear();
  mMetabolitesInd.insert(mMetabolitesInd.begin(), &mMetabolitesX[0], &mMetabolitesX[i]);
  mStepsInd.insert(mStepsInd.begin(), &mStepsX[0], &mStepsX[i]);

  for (j = i; j < mLU.num_rows(); j++)
    {
      Sum = 0.0;

      for (k = 0; k < mLU.num_cols(); k++)
        Sum += fabs(mLU[j][k]);

      if (Sum == 0.0)
        break;

      mMetabolitesX[j]->setStatus(METAB_DEPENDENT);
    }

  mMetabolitesDep.clear();
  mMetabolitesDep.insert(mMetabolitesDep.begin(), &mMetabolitesX[i], &mMetabolitesX[j]);

  for (k = j; k < mLU.num_rows(); k++)
    mMetabolitesX[k]->setStatus(METAB_FIXED);

  return;
}

void CModel::buildRedStoi()
{
  C_INT32 i, j, k;
  C_FLOAT64 Sum;
  C_INT32 imax, jmax, kmax;                // wei for compiler

  imax = mMetabolitesInd.size();
  jmax = mStepsX.size();

  mRedStoi.newsize(imax, jmax);

  for (i = 0; i < imax; i++)
    for (j = 0; j < jmax; j++)
      {
        /* Since L[i,k] = 1 for k = i and L[i,k] = 0 for k > i
           we have to avoid L[i,k] where k >= i, i.e.. k < i.
           Similarly, since U[k,j] = 0 for k > j
           we have to avoid U[k,j] where k > j, i.e., k <= j. */

        if (j < i)
          {
            Sum = 0.0;
            kmax = j + 1;
          }
        else
          {
            /* For j < i we are missing a part of the sum: */
            /* Sum +=  mLU[i][j]; since L[i,i] = 1 */
            Sum = mLU[i][j];
            kmax = i;
          }

        for (k = 0; k < kmax; k++)
          Sum += mLU[i][k] * mLU[k][j];

        mRedStoi[i][j] = Sum;
      }

#ifdef DEBUG_MATRIX
  cout << "Reduced Stoichiometry Matrix" << endl;
  cout << mRedStoi << endl;
#endif

  return;
}

void CModel::buildL()
{
  unsigned C_INT32 size = mStoi.num_rows();
  unsigned C_INT32 i, j, jmax, k;
  TNT::UnitLowerTriangularView < TNT::Matrix < C_FLOAT64 > > L(mLU);

  mL.newsize(size, size);
  jmax = (size < mSteps.size()) ? size : mSteps.size();

  /* Create L from the UnitLowerTriangularView of mLU */

  for (i = 0; i < size; i++)
    for (j = 0; j < jmax; j++)
      mL[i][j] = L(i + 1, j + 1);

  /* We complete L so that it is a square matrix */
  for (i = 0; i < size; i++)
    for (j = jmax; j < size; j++)
      mL[i][j] = 0.0;

  for (j = jmax; j < size; j++)
    mL[j][j] = 1.0;

  /* Calculate the inverse of L and store it in the upper triangular
     part of L */

  C_FLOAT64 *sum;

  jmax = (size) ? size - 1 : size;

  for (j = 0; j < jmax; j++)
    for (i = j + 1; i < size; i++)
      {
        sum = &mL[j][i];
        *sum = - mL[i][j];

        for (k = j + 1; k < i; k++)
          // I[i][j] -= mL[i][k] * I[k][j]
          *sum -= mL[i][k] * mL[j][k];
      }

#ifdef DEBUG_MATRIX
  cout << "L" << endl;
  cout << TNT::LowerTriangularView< TNT::Matrix< C_FLOAT64 > >(mL)
  << endl;
  cout << "L inverse" << endl;
  cout << TNT::Transpose_View< TNT::UpperTriangularView< TNT::Matrix< C_FLOAT64 > > >(mL)
  << endl;
#endif
}

void CModel::buildMoieties()
{
  unsigned C_INT32 i;
  unsigned C_INT32 imin = mMetabolitesInd.size();
  unsigned C_INT32 imax = imin + mMetabolitesDep.size();
  unsigned C_INT32 j;
  unsigned C_INT32 jmax = imin;

  CMoiety *pMoiety;

  mMoieties.cleanup();

  for (i = imin; i < imax; i++)
    {
      pMoiety = new CMoiety;

      pMoiety->setName(mMetabolitesX[i]->getName());

      pMoiety->add
      (1.0, mMetabolitesX[i]);

      for (j = 0; j < jmax; j++)
        {
          if (mL[j][i] != 0.0)
            pMoiety->add
            (mL[j][i], mMetabolitesX[j]);
        }

      pMoiety->setInitialValue();
      cout << pMoiety->getDescription() << " = "
      << pMoiety->getNumber() << endl;

      mMoieties.add(pMoiety);
    }

  return;
}

void CModel::setNumbersDblAndUpdateConcentrations(const C_FLOAT64 * y)
{
  unsigned C_INT32 i, imax;

  // Set the concentration of the independent metabolites
  imax = mMetabolitesInd.size();

  for (i = 0; i < imax; i++)
    mMetabolitesInd[i]->setNumberDbl(y[i]);

  // Set the concentration of the dependent metabolites
  imax = mMetabolitesDep.size();

  for (i = 0; i < imax; i++)
    mMetabolitesDep[i]->setNumberDbl(mMoieties[i]->dependentNumber());

  // Calculate the velocity vector depending on the step kinetics
  imax = mStepsX.size();

  for (i = 0; i < imax; i++)
    mStepsX[i]->calculate();

  return;
}

void CModel::setRates(const C_FLOAT64 * y)
{
  unsigned C_INT32 i, imax;

  // Set the rate of the independent metabolites
  imax = mMetabolitesInd.size();

  for (i = 0; i < imax; i++)
    mMetabolitesInd[i]->setRate(y[i]);

  // Set the rate of the dependent metabolites
  imax = mMetabolitesDep.size();

  for (i = 0; i < imax; i++)
    mMetabolitesDep[i]->setRate(mMoieties[i]->dependentRate());

  return;
}

void CModel::setTransitionTimes()
{
  unsigned C_INT32 i, imax = mMetabolites.size();
  unsigned C_INT32 j, jmax = mSteps.size();
  unsigned C_INT32 k;

  C_FLOAT64 TotalFlux, PartialFlux;
  C_FLOAT64 TransitionTime;

  mTransitionTime = 0.0;

  for (i = 0, k = 0; i + k < imax; i++)
    {
      if (METAB_FIXED == mMetabolites[i + k]->getStatus())
        {
          i--;
          k++;
          continue;
        }

      TotalFlux = 0.0;

      for (j = 0; j < jmax; j++)
        {
          PartialFlux = mStoi[i][j] * *mFluxes[j];

          if (PartialFlux > 0.0)
            TotalFlux += PartialFlux;
        }

      if (TotalFlux == 0.0)
        for (j = 0; j < jmax; j++)
          {
            PartialFlux = - mStoi[i][j] * *mFluxes[j];

            if (PartialFlux > 0.0)
              TotalFlux += PartialFlux;
          }

      if (TotalFlux == 0.0)
        TransitionTime = DBL_MAX;
      else
        TransitionTime = mMetabolites[i + k]->getNumberDbl() / TotalFlux;

      mMetabolites[i + k]->setTransitionTime(TransitionTime);

      if (TransitionTime == DBL_MAX || mTransitionTime == DBL_MAX)
        mTransitionTime = DBL_MAX;
      else
        mTransitionTime += TransitionTime;
    }
}

CCopasiVectorNS < CReaction > & CModel::getReactions()
{
  return mSteps;
}

const CCopasiVectorNS < CReaction > & CModel::getReactions() const
  {
    return mSteps;
  }

vector < CReaction * > & CModel::getReactionsX()
{
  return mStepsX;
}

void CModel::lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  unsigned C_INT32 i, j;

  setNumbersDblAndUpdateConcentrations(y);

  // Calculate ydot = RedStoi * v

  for (i = 0; i < (unsigned C_INT32) n; i++)
    {
      ydot[i] = 0.0;

      for (j = 0; j < mSteps.size(); j++)
        ydot[i] += mRedStoi[i][j] * *mFluxesX[j];
    }

  return;
}
vector < CMetab * > & CModel::getMetabolitesInd(){ return mMetabolitesInd; }
vector < CMetab * > & CModel::getMetabolitesDep(){ return mMetabolitesDep; }
vector < CMetab * > & CModel::getMetabolitesX(){ return mMetabolitesX; }

unsigned C_INT32 CModel::getTotMetab() const
  {
    return mMetabolites.size();
  }

unsigned C_INT32 CModel::getIntMetab() const
  {
    return mMetabolitesInd.size() + mMetabolitesDep.size();
  }

unsigned C_INT32 CModel::getIndMetab() const
  {
    return mMetabolitesInd.size();
  }

unsigned C_INT32 CModel::getDepMetab() const
  {
    return mMetabolitesDep.size();
  }

C_FLOAT64 * CModel::getInitialNumbersDbl() const
  {
    C_INT32 i, imax = mMetabolitesInd.size();

    C_FLOAT64 * y = new C_FLOAT64[imax];

    for (i = 0; i < imax; i++)
      y[i] = mMetabolitesInd[i]->getInitialNumberDbl();

    return y;
  }

C_FLOAT64 * CModel::getNumbersDbl() const
  {
    C_INT32 i, imax = mMetabolitesInd.size();

    C_FLOAT64 * y = new C_FLOAT64[imax];

    for (i = 0; i < imax; i++)
      y[i] = mMetabolitesInd[i]->getNumberDbl();

    return y;
  }

// Added by Yongqun He
/**
 * Get the total steps
 *
 */
unsigned C_INT32 CModel::getTotSteps()
{
  return mSteps.size();   //should not return mSteps
}

unsigned C_INT32 CModel::getDimension() const
  {
    return mMetabolitesInd.size();
  }

/**
 *        Return the comments of this model        Wei Sun 
 */
string CModel::getComments() const
  {
    return mComments;
  }

/**
 *        Return the title of this model
 *        @return string
 */
string CModel::getTitle() const
  {
    return mTitle;
  }

/**
 *        Return the comments of this model
 *        @return CCopasiVector < CCompartment > *
 */
CCopasiVectorNS < CCompartment > & CModel::getCompartments() const
  {
    return (const_cast< CModel * >(this))->mCompartments;
  }

/**
 *        Return the metabolites of this model
 *        @return vector < CMetab * > 
 */
vector < CMetab * > & CModel::getMetabolites()
{
  return mMetabolites;
}

/**
 *  Get the Reduced Stoichiometry Matrix of this Model
 */
const TNT::Matrix < C_FLOAT64 >& CModel::getRedStoi() const
  {
    return mRedStoi;
  }

/**
 *  Get the Stoichiometry Matrix of this Model
 */
const TNT::Matrix < C_FLOAT64 >& CModel::getStoi() const
  {
    return mStoi;
  }

/**
 *        Return the mMoieties of this model        
 *        @return CCopasiVector < CMoiety > * 
 */
CCopasiVectorN < CMoiety > & CModel::getMoieties()
{
  return mMoieties;
}

/**
 *        Returns the index of the metab
 */
C_INT32 CModel::findMetab(const string & Target)
{
  unsigned C_INT32 i, s;
  string name;

  s = mMetabolites.size();
  for (i = 0; i < s; i++)
    {
      name = mMetabolites[i]->getName();
      if (name == Target)
        return i;
    }
  return -1;
}

/**
 *        Returns the index of the step
 */
C_INT32 CModel::findStep(const string & Target)
{
  unsigned C_INT32 i, s;
  string name;

  s = mSteps.size();
  for (i = 0; i < s; i++)
    {
      name = mSteps[i]->getName();
      if (name == Target)
        return i;
    }
  return -1;
}

/**
 *        Returns the index of the compartment
 */
C_INT32 CModel::findCompartment(const string & Target)
{
  unsigned C_INT32 i, s;
  string name;

  s = mCompartments.size();
  for (i = 0; i < s; i++)
    {
      name = mCompartments[i]->getName();
      if (name == Target)
        return i;
    }
  return -1;
}

/**
 *        Returns the index of the Moiety
 */
C_INT32 CModel::findMoiety(string &Target)
{
  unsigned C_INT32 i, s;
  string name;

  s = mMoieties.size();
  for (i = 0; i < s; i++)
    {
      name = mMoieties[i]->getName();
      if (name == Target)
        return i;
    }
  return -1;
}

void CModel::initializeMetabolites()
{
  unsigned C_INT32 i, j;

  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  mMetabolites.clear();

  for (i = 0; i < mCompartments.size(); i++)
    for (j = 0; j < mCompartments[i]->metabolites().size(); j++)
      {
        mMetabolites.push_back(mCompartments[i]->metabolites()[j]);
        mCompartments[i]->metabolites()[j]->setModel(this);
        mCompartments[i]->metabolites()[j]->checkConcentrationAndNumber();
      }
}

/**
 * Returns the mStepsX of this model
 * @return vector < CStep * > 
 */
vector < CReaction * > & CModel::getStepsX()
{
  return mStepsX;
}

/**
 *  Get the mLU matrix of this model
 */
const TNT::Matrix < C_FLOAT64 > & CModel::getmLU() const
  {
    return mLU;
  }

const TNT::UnitLowerTriangularView<TNT::Matrix<C_FLOAT64 > > & CModel::getL() const
  {
    return *mpLView;
  }

const TNT::Transpose_View<TNT::UpperTriangularView<TNT::Matrix<C_FLOAT64 > > >
& CModel::getInverseL() const
  {
    return *mpInverseLView;
  }

CState * CModel::getInitialState() const
  {
    unsigned C_INT32 i, imax;
    CState * s = new CState(this);

    /* Set the volumes */
    C_FLOAT64 * Dbl = const_cast<C_FLOAT64 *>(s->getVolumeArray());
    for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
      *Dbl = mCompartments[i]->getVolume();

    /* Set the variable Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s->getVariableNumberArrayDbl());
    for (i = 0, imax = getIntMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolites[i]->getInitialNumberDbl();

    C_INT32 * Int = const_cast<C_INT32 *>(s->getVariableNumberArrayInt());
    for (i = 0, imax = getIntMetab(); i < imax; i++, Int++)
      *Int = mMetabolites[i]->getInitialNumberInt();

    /* Set the fixed Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s->getFixedNumberArrayDbl());
    for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolites[i]->getInitialNumberDbl();

    Int = const_cast<C_INT32 *>(s->getFixedNumberArrayInt());
    for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Int++)
      *Int = mMetabolites[i]->getInitialNumberInt();

    return s;
  }

CStateX * CModel::getInitialStateX() const
  {
    unsigned C_INT32 i, imax;
    CStateX * s = new CStateX(this);

    /* Set the volumes */
    C_FLOAT64 * Dbl = const_cast<C_FLOAT64 *>(s->getVolumeArray());
    for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
      *Dbl = mCompartments[i]->getVolume();

    /* Set the independent variable Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s->getVariableNumberArrayDbl());
    for (i = 0, imax = getIndMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolitesX[i]->getInitialNumberDbl();

    C_INT32 * Int = const_cast<C_INT32 *>(s->getVariableNumberArrayInt());
    for (i = 0, imax = getIndMetab(); i < imax; i++, Int++)
      *Int = mMetabolitesX[i]->getInitialNumberInt();

    /* Set the dependent variable Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s->getDependentNumberArrayDbl());
    for (i = getIndMetab(), imax = getIntMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolitesX[i]->getInitialNumberDbl();

    Int = const_cast<C_INT32 *>(s->getDependentNumberArrayInt());
    for (i = getIndMetab(), imax = getIntMetab(); i < imax; i++, Int++)
      *Int = mMetabolitesX[i]->getInitialNumberInt();

    /* Set the fixed Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s->getFixedNumberArrayDbl());
    for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolitesX[i]->getInitialNumberDbl();

    Int = const_cast<C_INT32 *>(s->getFixedNumberArrayInt());
    for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Int++)
      *Int = mMetabolitesX[i]->getInitialNumberInt();

    return s;
  }

void CModel::setInitialState(const CState * state)
{
  unsigned C_INT32 i, imax;

  /* Set the volumes */
  const C_FLOAT64 * Dbl = state->getVolumeArray();

  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);

  /* Set the variable metabolites */
  /* We are not using the set method since it automatically updates the
     numbers which are provided separately in a state */
  Dbl = state->getVariableNumberArrayDbl();
  for (i = 0, imax = getIntMetab(); i < imax; i++, Dbl++)
    *const_cast<C_FLOAT64*>(&mMetabolites[i]->getInitialConcentration())
    = *Dbl * mMetabolites[i]->getCompartment()->getVolumeInv()
      * mNumber2QuantityFactor;

  /* We are not using the set method since it automatically updates the
     concentration which has been already set above */
  const C_INT32 * Int = state->getVariableNumberArrayInt();
  for (i = 0, imax = getIntMetab(); i < imax; i++, Int++)
    *const_cast<C_INT32*>(&mMetabolites[i]->getInitialNumberInt()) = *Int;

  /* Set the fixed metabolites */
  /* We are not using the set method since it automatically updates the
     numbers which are provided separately in a state */
  Dbl = state->getFixedNumberArrayDbl();
  for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
    *const_cast<C_FLOAT64*>(&mMetabolites[i]->getInitialConcentration())
    = *Dbl * mMetabolites[i]->getCompartment()->getVolumeInv()
      * mNumber2QuantityFactor;

  /* We are not using the set method since it automatically updates the
     concentration which has been already set above */
  Int = state->getFixedNumberArrayInt();
  for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Int++)
    *const_cast<C_INT32*>(&mMetabolites[i]->getInitialNumberInt()) = *Int;

  /* We need to update the initial values for moieties */
  for (i = 0, imax = mMoieties.size(); i < imax; i++)
    mMoieties[i]->setInitialValue();

  return;
}

void CModel::setInitialState(const CStateX * state)
{
  unsigned C_INT32 i, imax;

  /* Set the volumes */
  const C_FLOAT64 * Dbl = state->getVolumeArray();
  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);

  /* Set the independent variable metabolites */
  /* We are not using the set method since it automatically updates the
     numbers which are provided separately in a state */
  Dbl = state->getVariableNumberArrayDbl();
  for (i = 0, imax = getIndMetab(); i < imax; i++, Dbl++)
    *const_cast<C_FLOAT64*>(&mMetabolitesX[i]->getInitialConcentration())
    = *Dbl * mMetabolitesX[i]->getCompartment()->getVolumeInv()
      * mNumber2QuantityFactor;

  /* We are not using the set method since it automatically updates the
     concentration which has been already set above */
  const C_INT32 * Int = state->getVariableNumberArrayInt();
  for (i = 0, imax = getIndMetab(); i < imax; i++, Int++)
    *const_cast<C_INT32*>(&mMetabolitesX[i]->getInitialNumberInt()) = *Int;

  /* Set the dependent variable metabolites */
  /* We are not using the set method since it automatically updates the
     numbers which are provided separately in a state */
  Dbl = state->getDependentNumberArrayDbl();
  for (i = getIndMetab(), imax = getIntMetab(); i < imax; i++, Dbl++)
    *const_cast<C_FLOAT64*>(&mMetabolitesX[i]->getInitialConcentration())
    = *Dbl * mMetabolitesX[i]->getCompartment()->getVolumeInv()
      * mNumber2QuantityFactor;

  /* We are not using the set method since it automatically updates the
     concentration which has been already set above */
  Int = state->getVariableNumberArrayInt();
  for (i = getIndMetab(), imax = getIntMetab(); i < imax; i++, Int++)
    *const_cast<C_INT32*>(&mMetabolitesX[i]->getInitialNumberInt()) = *Int;

  /* Set the fixed metabolites */
  /* We are not using the set method since it automatically updates the
     numbers which are provided separately in a state */
  Dbl = state->getFixedNumberArrayDbl();
  for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
    *const_cast<C_FLOAT64*>(&mMetabolites[i]->getInitialConcentration())
    = *Dbl * mMetabolites[i]->getCompartment()->getVolumeInv()
      * mNumber2QuantityFactor;

  /* We are not using the set method since it automatically updates the
     concentration which has been already set above */
  Int = state->getFixedNumberArrayInt();
  for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Int++)
    *const_cast<C_INT32*>(&mMetabolites[i]->getInitialNumberInt()) = *Int;

  /* We need to update the initial values for moieties */
  for (i = 0, imax = mMoieties.size(); i < imax; i++)
    mMoieties[i]->setInitialValue();

  return;
}

void CModel::setState(const CState * state)
{
  unsigned C_INT32 i, imax;
  const C_FLOAT64 * Dbl;

#ifdef XXXX // This gets enabled when we have dynamic volume changes
  /* Set the volumes */
  Dbl = state->getVolumeArray();
  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);
#endif // XXXX

  /* Set the variable metabolites */
  /* We are not using the set method since it automatically updates the
     numbers which are provided separately in a state */
  Dbl = state->getVariableNumberArrayDbl();
  for (i = 0, imax = getIntMetab(); i < imax; i++, Dbl++)
    *const_cast<C_FLOAT64*>(&mMetabolites[i]->getConcentration())
    = *Dbl * mMetabolites[i]->getCompartment()->getVolumeInv()
      * mNumber2QuantityFactor;

  /* We are not using the set method since it automatically updates the
     concentration which has been already set above */
  const C_INT32 * Int = state->getVariableNumberArrayInt();
  for (i = 0, imax = getIntMetab(); i < imax; i++, Int++)
    *const_cast<C_INT32*>(&mMetabolites[i]->getNumberInt()) = *Int;

  return;
}

void CModel::setState(const CStateX * state)
{
  unsigned C_INT32 i, imax;
  const C_FLOAT64 * Dbl;

#ifdef XXXX // This gets enabled when we have dynamic volume changes

  Dbl = state->getVolumeArray();
  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);
#endif // XXXX

  /* Set the independent variable metabolites */
  /* We are not using the set method since it automatically updates the
     numbers which are provided separately in a state */
  Dbl = state->getVariableNumberArrayDbl();
  for (i = 0, imax = getIndMetab(); i < imax; i++, Dbl++)
    *const_cast<C_FLOAT64*>(&mMetabolites[i]->getConcentration())
    = *Dbl * mMetabolites[i]->getCompartment()->getVolumeInv()
      * mNumber2QuantityFactor;

  /* We are not using the set method since it automatically updates the
     concentration which has been already set above */
  const C_INT32 * Int = state->getVariableNumberArrayInt();
  for (i = 0, imax = getIndMetab(); i < imax; i++, Int++)
    *const_cast<C_INT32*>(&mMetabolites[i]->getNumberInt()) = *Int;

  /* We need to update the dependent metabolites by using moieties */
  /* This changes need to be reflected in the current state */
  C_FLOAT64 NumberDbl;

  for (i = 0, imax = mMoieties.size(); i < imax; i++)
    {
      NumberDbl = mMoieties[i]->dependentNumber();
      mMetabolitesDep[i]->
      setConcentration(NumberDbl *
                       mMetabolitesDep[i]->getCompartment()->getVolumeInv()
                       * mNumber2QuantityFactor);
      (const_cast<CStateX *>(state))->setDependentNumber(i, NumberDbl);
    }

  return;
}

void CModel::getRates(CState * state, C_FLOAT64 * rates)
{
  setState(state);

  unsigned C_INT32 i, imax;

  for (i = 0, imax = mSteps.size(); i < imax; i++)
    rates[i] = mSteps[i]->calculate();

  return;
}

void CModel::getRates(CStateX * state, C_FLOAT64 * rates)
{
  setState(state);

  unsigned C_INT32 i, imax;

  for (i = 0, imax = mStepsX.size(); i < imax; i++)
    rates[i] = mStepsX[i]->calculate();

  return;
}

void CModel::getDerivatives(CState * state, C_FLOAT64 * derivatives)
{
  setState(state);

  unsigned C_INT32 i, imax = mMetabolitesInd.size() + mMetabolitesDep.size();
  unsigned C_INT32 j, jmax = mSteps.size();

  for (j = 0; j < jmax; j++)
    mSteps[j]->calculate();

  // Calculate ydot = Stoi * v
  for (i = 0; i < imax; i++)
    {
      derivatives[i] = 0.0;

      for (j = 0; j < jmax; j++)
        derivatives[i] += mStoi[i][j] * *mFluxes[j];
    }

  return;
}

void CModel::getDerivatives(CStateX * state, C_FLOAT64 * derivatives)
{
  setState(state);

  unsigned C_INT32 i, imax = mMetabolitesInd.size();
  unsigned C_INT32 j, jmax = mStepsX.size();

  for (j = 0; j < jmax; j++)
    mStepsX[j]->calculate();

  // Calculate ydot = RedStoi * v
  for (i = 0; i < imax; i++)
    {
      derivatives[i] = 0.0;

      for (j = 0; j < jmax; j++)
        derivatives[i] += mRedStoi[i][j] * *mFluxesX[j];
    }

  return;
}

void CModel::setQuantityUnit(const string & name)
{
  mQuantityUnitName = name;

  mQuantity2NumberFactor = 1.0;

  if ((name == "mol")
      || (name == "M")
      || (name == "Mol"))
    mQuantity2NumberFactor = 6.020402E23;

  if ((name == "mmol")
      || (name == "mM")
      || (name == "mMol"))
    mQuantity2NumberFactor = 6.020402E20;

  if ((name == "nmol")
      || (name == "nM")
      || (name == "nMol"))
    mQuantity2NumberFactor = 6.020402E14;

  mNumber2QuantityFactor = 1 / mQuantity2NumberFactor;
}
string CModel::getQuantityUnit() const { return mQuantityUnitName; }

C_FLOAT64 CModel::getQuantity2NumberFactor() const
  { return mQuantity2NumberFactor; }

C_FLOAT64 CModel::getNumber2QuantityFactor() const
  { return mNumber2QuantityFactor; }

void CModel::setTitle(const string &title)
{
  mTitle = title;
}

void CModel::setComments(const string &comments)
{
  mComments = comments;
}

C_INT32 CModel::addMetabolite(const string & comp,
                              const string & name,
                              C_FLOAT64 iconc,
                              C_INT16 status)
{
  CMetab metab;
  C_INT32 c;

  c = findCompartment(comp);
  if (c == -1)
    return -1;
  if (findMetab(name) != -1)
    return -1;
  metab.setModel(this);
  metab.setCompartment(mCompartments[c]);
  metab.setName(name);
  metab.setStatus(status);
  metab.setInitialConcentration(iconc);
  mCompartments[c]->addMetabolite(metab);
  return 0;
}

C_INT32 CModel::addCompartment(string &name, C_FLOAT64 vol)
{
  CCompartment *cpt;
  // check if there is already a volume with this name
  if (findCompartment(name) == -1)
    {
      cpt = new CCompartment(name, vol);
      mCompartments.add(cpt);
      return mCompartments.size();
    }
  else
    return -1;
}

C_INT32 CModel::addReaction(CReaction *r)
{
  mSteps.add(r);
  r->compile(mCompartments);
  return mSteps.size();
}

const vector <unsigned C_INT32> & CModel::getMetabolitePermutation() const
  { return mRowLU; }

const vector <unsigned C_INT32> & CModel::getReactionPermutation() const
  { return mColLU; }

void CModel::updateDepMetabNumbers(CStateX const & state) const
  {
    (const_cast< CModel * >(this))->setState(&state);
  }
