/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModel.cpp,v $
   $Revision: 1.151 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/12/04 17:31:54 $
   End CVS Header */

/////////////////////////////////////////////////////////////////////////////
// CModel
// model.cpp : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////
#include "copasi.h"

#include <string>
#include <vector>
#include <limits.h>
#include <cmath>
#include <algorithm>

#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif //DBL_MAX

// #define DEBUG_MATRIX

#define  COPASI_TRACE_CONSTRUCTION
#include "CCompartment.h"
#include "CMetab.h"
#include "CModel.h"
#include "CState.h"
#include "function/CFunctionDB.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CGlobals.h"
#include "utilities/CVector.h"
#include "utilities/CluX.h"
#include "utilities/utility.h"

#include "clapackwrap.h"

const char * CModel::VolumeUnitName[] =
  {"l", "ml", "µl", "nl", "pl", "fl", NULL};

const char * CModel::TimeUnitName[] =
  {"s", "m", "h", "d", NULL};

const char * CModel::QuantityUnitName[] =
  {"Mol", "mMol", "µMol", "nMol", "pMol", "fMol", "#", NULL};

CModel::CModel():
    CCopasiContainer("NoName", &RootContainer, "Model"),
    mKey(CKeyFactory::add("Model", this)),
    mComments(),
    mVolumeUnit("ml"),
    mTimeUnit("s"),
    mQuantityUnit("mMol"),
    mCompartments("Compartments", this),
    mMetabolites("Metabolites", this),
    mMetabolitesX("Reduced Model Metabolites", this),
    mMetabolitesInd("Independent Metabolites", this),
    mMetabolitesDep("Dependent Metabolites", this),
    mSteps("Reactions", this),
    mStepsX("Reduced Model Reactions", this),
    mStepsInd("Independent Reactions", this),
    mFluxes(),
    mFluxesX(),
    mScaledFluxes(),
    mScaledFluxesX(),
    mInitialTime(0),
    mTime(0),
    mTransitionTime(0),
    mMoieties("Moieties", this),
    mStoi(),
    mRedStoi(),
    mL(),
    mLView(mL, mMetabolitesInd),
    mQuantity2NumberFactor(1.0),
    mNumber2QuantityFactor(1.0),
    mStateTemplate()
{
  initObjects();

  unsigned C_INT32 i, imax = mSteps.size();

  for (i = 0; i < imax; i++)
    mSteps[i]->compile(mCompartments);

  initializeMetabolites();

  compile();

  CONSTRUCTOR_TRACE;
}

CModel::CModel(const CModel & src):
    CCopasiContainer(src),
    mKey(CKeyFactory::add("Model", this)),
    mComments(src.mComments),
    mVolumeUnit(src.mVolumeUnit),
    mTimeUnit(src.mTimeUnit),
    mQuantityUnit(src.mQuantityUnit),
    mCompartments(src.mCompartments, this),
    mMetabolites(src.mMetabolites, this),
    mMetabolitesX(src.mMetabolitesX, this),
    mMetabolitesInd(src.mMetabolitesInd, this),
    mMetabolitesDep(src.mMetabolitesDep, this),
    mSteps(src.mSteps, this),
    mStepsX(src.mStepsX, this),
    mStepsInd(src.mStepsInd, this),
    mFluxes(src.mFluxes),
    mFluxesX(src.mFluxesX),
    mScaledFluxes(src.mScaledFluxes),
    mScaledFluxesX(src.mScaledFluxesX),
    mInitialTime(src.mInitialTime),
    mTime(src.mTime),
    mTransitionTime(src.mTransitionTime),
    mMoieties(src.mMoieties, this),
    mStoi(src.mStoi),
    mRedStoi(src.mRedStoi),
    mL(src.mL),
    mLView(mL, mMetabolitesInd),
    mQuantity2NumberFactor(src.mQuantity2NumberFactor),
    mNumber2QuantityFactor(src.mNumber2QuantityFactor),
    mStateTemplate()

{
  CONSTRUCTOR_TRACE;

  unsigned C_INT32 i, imax = mSteps.size();

  for (i = 0; i < imax; i++)
    mSteps[i]->compile(mCompartments);

  initializeMetabolites();

  compile();
  initObjects();
}

CModel::~CModel()
{
  CKeyFactory::remove(mKey);
  //  cleanup();
  DESTRUCTOR_TRACE;
}

void CModel::cleanup()
{
  /* The real objects */
  mCompartments.cleanup();
  mSteps.cleanup();
  mMoieties.cleanup();

  /* The references */
  mStepsX.resize(0);
  mStepsInd.resize(0);
  mMetabolites.resize(0);
  mMetabolitesX.resize(0);
  mMetabolitesInd.resize(0);
  mMetabolitesDep.resize(0);
  mFluxes.resize(0);
  mFluxesX.resize(0);
  mScaledFluxes.resize(0);
  mScaledFluxesX.resize(0);

  /*
    mStepsX.resize(0);
    mStepsInd.resize(0);
   
    mMetabolites.resize(0);
    mMetabolitesX.resize(0);
    mMetabolitesInd.resize(0);
    mMetabolitesDep.resize(0);
   
    mFluxes.resize(0);
    mFluxesX.resize(0);
    mScaledFluxes.resize(0);
    mScaledFluxesX.resize(0);
  */
}

C_INT32 CModel::load(CReadConfig & configBuffer)
{
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
  unsigned C_INT32 i;
  std::string tmp;
  Copasi->pModel = this;

  // For old Versions we must read the list of Metabolites beforehand
  if (configBuffer.getVersion() < "4")
    {
      if ((Fail = configBuffer.getVariable("TotalMetabolites", "C_INT32",
                                           &Size, CReadConfig::LOOP)))
        return Fail;

      Copasi->pOldMetabolites->load(configBuffer, Size);
    }

  if ((Fail = configBuffer.getVariable("Title", "string", &tmp,
                                       CReadConfig::LOOP)))
    return Fail;
  setObjectName(tmp);

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
      Fail = configBuffer.getVariable("TimeUnit", "string", &mTimeUnit,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        mTimeUnit = "unknown";
      else
        throw Exception;
    }

  setTimeUnit(mTimeUnit); // set the factors

  try
    {
      Fail = configBuffer.getVariable("ConcentrationUnit", "string", &mQuantityUnit,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        mQuantityUnit = "unknown";
      else
        throw Exception;
    }

  setQuantityUnit(mQuantityUnit); // set the factors

  try
    {
      Fail = configBuffer.getVariable("VolumeUnit", "string", &mVolumeUnit,
                                      CReadConfig::LOOP);
    }
  catch (CCopasiException Exception)
    {
      if ((MCReadConfig + 1) == Exception.getMessage().getNumber())
        mVolumeUnit = "unknown";
      else
        throw Exception;
    }

  setVolumeUnit(mVolumeUnit); // set the factors

  if (configBuffer.getVersion() < "4")
    mInitialTime = 0;
  else
    {
      if ((Fail = configBuffer.getVariable("InitialTime", "C_FLOAT64",
                                           &mInitialTime, CReadConfig::LOOP)))
        return Fail;
    }

  if ((Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mCompartments.load(configBuffer, Size);

  if (configBuffer.getVersion() < "4")
    {
      // Create the correct compartment / metabolite relationships
      CMetab *pMetabolite;

      for (i = 0; i < Copasi->pOldMetabolites->size(); i++)
        {
          pMetabolite = new CMetab;
          mCompartments[(*Copasi->pOldMetabolites)[i]->getIndex()]->
          addMetabolite(pMetabolite);

          (*pMetabolite) = *(*Copasi->pOldMetabolites)[i];
        }
    }

  //DebugFile << mCompartments;       //debug

  initializeMetabolites();

  if ((Fail = Copasi->pFunctionDB->load(configBuffer))) // slow
    return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;

  mSteps.load(configBuffer, Size); // slow

  // DebugFile << std::endl << mSteps << std::endl;  //debug

  for (i = 0; i < mSteps.size(); i++)
    mSteps[i]->compile(mCompartments);

  // DebugFile << "After compiling " << std::endl << mSteps << std::endl;   //debug

  Copasi->pOldMetabolites->cleanup();

  compile();
  return Fail;
}

C_INT32 CModel::save(CWriteConfig & configBuffer)
{
  C_INT32 Size;
  C_INT32 Fail = 0;
  std::string tmp = getObjectName();

  if ((Fail = configBuffer.setVariable("Title", "string", &tmp)))
    return Fail;

  if ((Fail = configBuffer.setVariable("Comments", "multiline", &mComments)))
    return Fail;

  if ((Fail = configBuffer.setVariable("ConcentrationUnit",
                                       "string",
                                       &mQuantityUnit)))
    return Fail;

  if ((Fail = configBuffer.setVariable("InitialTime", "C_FLOAT64", &mInitialTime)))
    return Fail;

  Size = mCompartments.size();

  if ((Fail = configBuffer.setVariable("TotalCompartments", "C_INT32", &Size)))
    return Fail;

  mCompartments.save(configBuffer);

  if ((Fail = Copasi->pFunctionDB->save(configBuffer)))
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
  std::string tmp = getObjectName();

  if ((Fail = configBuffer.setVariable("Title", "string", &tmp)))
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
  if ((Fail = Copasi->pFunctionDB->saveOld(configBuffer)))
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
  std::string tmpstr, tmpstr2;
  C_INT32 p, dummy;
  unsigned C_INT32 i;

  fout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  fout << "<!-- Created by COPASI version " << Copasi->ProgramVersion.getVersion() << " -->" << std::endl;
  // TODO: add time stamp to the comment string
  fout << "<sbml xmlns=\"http://www.sbml.org/sbml/level1\" level=\"1\" version=\"1\">" << std::endl;
  FixSName(getObjectName(), tmpstr);
  fout << "\t<model name=\"" + tmpstr + "\">" << std::endl;
  // model notes
  if (! mComments.empty())
    {
      fout << "\t\t<notes>" << std::endl;
      fout << "\t\t\t<body xmlns=\"http://www.w3.org/1999/xhtml\">" << std::endl;
      tmpstr = mComments;
      for (i = 0; i != (unsigned C_INT32) - 1;)
        {
          p = tmpstr.find_first_of("\r\n");
          FixXHTML(tmpstr.substr(0, p), tmpstr2);
          fout << "\t\t\t\t<p>" << tmpstr2 << "</p>" << std::endl;
          i = tmpstr.find('\n');
          tmpstr = tmpstr.substr(i + 1);
        }
      fout << "\t\t\t</body>" << std::endl;
      fout << "\t\t</notes>" << std::endl;
    }
  fout << "\t\t<listOfCompartments>" << std::endl;
  // compartments
  for (i = 0; i < mCompartments.size(); i++)
    mCompartments[i]->saveSBML(fout);
  fout << "\t\t</listOfCompartments>" << std::endl;
  fout << "\t\t<listOfSpecies>" << std::endl;
  for (i = 0; i < mMetabolites.size(); i++)
    mMetabolites[i]->saveSBML(fout);
  // check if any reaction has no substrates or no products
  // (necessary because SBML l1v1 does not support empty subs or prods)
  for (dummy = i = 0; (i < mSteps.size()) && (dummy == 0); i++)
    if ((mSteps[i]->getChemEq().getSubstrates().size() == 0)
        || (mSteps[i]->getChemEq().getProducts().size() == 0))
      dummy = 1;
  // if there are any, we need a dummy metabolite, let's call it _void !
  if (dummy)
    {
      fout << "\t\t\t<specie name=\"_void_\"";
      FixSName(mCompartments[0]->getName(), tmpstr);
      fout << " compartment=\"" << tmpstr << "\"";
      fout << " initialAmount=\"0.0\" boundaryCondition=\"true\"/>" << std::endl;
    }
  fout << "\t\t</listOfSpecies>" << std::endl;
  fout << "\t\t<listOfReactions>" << std::endl;
  for (i = 0; i < mSteps.size(); i++)
    mSteps[i]->saveSBML(fout, i);
  fout << "\t\t</listOfReactions>" << std::endl;
  fout << "\t</model>" << std::endl;
  fout << "</sbml>" << std::endl;
}

bool CModel::compile()
{
  CMatrix< C_FLOAT64 > LU;

  unsigned C_INT32 i, imax = mSteps.size();
  for (i = 0; i < imax; i++)
    mSteps[i]->compile(mCompartments);

  buildStoi();
  lUDecomposition(LU);
  setMetabolitesStatus(LU);
  buildRedStoi();
  buildL(LU);
  buildMoieties();
  buildStateTemplate();

  return true;
}

void CModel::buildStoi()
{
  CCopasiVector < CChemEqElement > Structure;
  unsigned C_INT32 i, j, k, imax;
  std::string key;

  imax = mMetabolites.size();
  mMetabolitesX.resize(imax, false);
  j = 0;

  // We reorder mMetabolitesX so that the fixed metabolites appear at the end.

  for (i = 0; i < imax; i++)
    if (mMetabolites[i]->getStatus() == CMetab::METAB_FIXED)
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
  mScaledFluxes.resize(mSteps.size());

  for (i = 0; i < mSteps.size(); i++)
    {
      mFluxes[i] = & mSteps[i]->getFlux();
      mScaledFluxes[i] = & mSteps[i]->getScaledFlux();
    }

  mStoi.resize(imax - j, mSteps.size());

  for (i = 0; i < (unsigned C_INT32) mStoi.numCols(); i++)
    {
      Structure = mSteps[i]->getChemEq().getBalances();

      for (j = 0; j < (unsigned C_INT32) mStoi.numRows(); j++)
        {
          mStoi[j][i] = 0.0;
          key = mMetabolites[j]->getKey();
          // Name = mMetabolitesX[j]->getName();

          for (k = 0; k < Structure.size(); k++)
            if (Structure[k]->getMetaboliteKey() == key)
              {
                mStoi[j][i] = Structure[k]->getMultiplicity();
                break;
              }
        }
    }

#ifdef DEBUG_MATRIX
  DebugFile << "Stoichiometry Matrix" << std::endl;
  DebugFile << mStoi << std::endl;
#endif

  return;
}

void CModel::lUDecomposition(CMatrix< C_FLOAT64 > & LU)
{
  unsigned C_INT32 i;

  std::vector < unsigned C_INT32 > rowLU(mStoi.numRows());
  std::vector < unsigned C_INT32 > colLU(mStoi.numCols());

  mRowLU.resize(mStoi.numRows());
  for (i = 0; i < mRowLU.size(); i++)
    mRowLU[i] = i;

  mColLU.resize(mStoi.numCols());
  for (i = 0; i < mColLU.size(); i++)
    mColLU[i] = i;

  LU = mStoi;

  LUfactor(LU, rowLU, colLU);

  // mMetabolitesX = mMetabolites;

  mStepsX.resize(mSteps.size(), false);

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
      if (rowLU[i] > i)
        {
          pMetab = mMetabolitesX[i];
          mMetabolitesX[i] = mMetabolitesX[rowLU[i]];
          mMetabolitesX[rowLU[i]] = pMetab;

          tmp = mRowLU[i];
          mRowLU[i] = mRowLU[rowLU[i]];
          mRowLU[rowLU[i]] = tmp;
        }
    }

  CReaction *pStep;

  for (i = colLU.size(); 0 < i--;)
    {
      if (colLU[i] < i)
        {
          pStep = mStepsX[i];
          mStepsX[i] = mStepsX[colLU[i]];
          mStepsX[colLU[i]] = pStep;

          tmp = mColLU[i];
          mColLU[i] = mColLU[colLU[i]];
          mColLU[colLU[i]] = tmp;
        }
    }

#ifdef DEBUG_MATRIX
  DebugFile << "Metabolite reordering " << mRowLU << std::endl;
  DebugFile << "Reaction reordering " << mColLU << std::endl;
#endif

  mFluxesX.resize(mStepsX.size());
  mScaledFluxesX.resize(mStepsX.size());

  for (i = 0; i < mStepsX.size(); i++)
    {
      mFluxesX[i] = &mStepsX[i]->getFlux();
      mScaledFluxesX[i] = &mStepsX[i]->getScaledFlux();
    }

  return;
}

void CModel::setMetabolitesStatus(const CMatrix< C_FLOAT64 > & LU)
{
  unsigned C_INT32 i, j, k;
  C_FLOAT64 Sum;

  // for (i=0; i<min(LU.numRows(), LU.numCols()); i++)
  // for compiler
  unsigned C_INT32 imax = (LU.numRows() < LU.numCols()) ?
                          LU.numRows() : LU.numCols();

  for (i = 0; i < imax; i++)
    {
      if (LU[i][i] == 0.0)
        break;

      mMetabolitesX[i]->setStatus(CMetab::METAB_VARIABLE);
    }

  mMetabolitesInd.resize(i, false);
  mStepsInd.resize(i, false);
  for (j = 0; j < i; j++)
    {
      mMetabolitesInd[j] = mMetabolitesX[j];
      mStepsInd[j] = mStepsX[j];
    }
  //  mMetabolitesInd.insert(mMetabolitesInd.begin(), &mMetabolitesX[0], &mMetabolitesX[i]);
  //  mStepsInd.insert(mStepsInd.begin(), &mStepsX[0], &mStepsX[i]);

  for (j = i; j < LU.numRows(); j++)
    {
      Sum = 0.0;

      for (k = 0; k < LU.numCols(); k++)
        Sum += fabs(LU[j][k]);

      if (Sum == 0.0)
        break;

      mMetabolitesX[j]->setStatus(CMetab::METAB_DEPENDENT);
    }

  mMetabolitesDep.resize(j - i, false);
  for (k = i; k < j; k++)
    mMetabolitesDep[k - i] = mMetabolitesX[k];

  //  mMetabolitesDep.insert(mMetabolitesDep.begin(), &mMetabolitesX[i], &mMetabolitesX[j]);

  for (k = j; k < LU.numRows(); k++)
    mMetabolitesX[k]->setStatus(CMetab::METAB_FIXED);

  return;
}

void CModel::buildRedStoi()
{
  C_INT32 i, imax = mMetabolitesInd.size();
  C_INT32 j, jmax = mStepsX.size();                // wei for compiler

  mRedStoi.resize(imax, jmax);

  /* just have to swap rows and colums */
  for (i = 0; i < imax; i++)
    for (j = 0; j < jmax; j++)
      mRedStoi(i, j) = mStoi(mRowLU[i], mColLU[j]);

#ifdef XXXX
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
            /* Sum +=  LU[i][j]; since L[i,i] = 1 */
            Sum = LU[i][j];
            kmax = i;
          }

        for (k = 0; k < kmax; k++)
          Sum += LU[i][k] * LU[k][j];

        mRedStoi[i][j] = Sum;
      }
#endif // XXXX

#ifdef DEBUG_MATRIX
  DebugFile << "Reduced Stoichiometry Matrix" << std::endl;
  DebugFile << mRedStoi << std::endl;
#endif

  return;
}

void CModel::buildL(const CMatrix< C_FLOAT64 > & LU)
{
  C_INT N = mMetabolitesInd.size();
  C_INT LDA = std::max((C_INT) 1, N);
  C_INT Info;

  unsigned C_INT32 i, imin, imax;
  unsigned C_INT32 j, jmax;
  unsigned C_INT32 k;
  C_FLOAT64 * sum;

  CMatrix< C_FLOAT64 > R(N, N);

  for (i = 1; i < (unsigned C_INT32) N; i++)
    for (j = 0; j < i; j++)
      R(i, j) = LU(i, j);

  /* to take care of differences between fortran's and c's memory  acces,
     we need to take the transpose, i.e.,the upper triangular */
  char cL = 'U';
  char cU = 'U'; /* 1 in the diaogonal of R */

  /* int dtrtri_(char *uplo,
   *             char *diag, 
   *             integer *n, 
   *             doublereal * A,
   *             integer *lda, 
   *             integer *info);   
   *  -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     March 31, 1993
   *
   *  Purpose
   *  =======
   *
   *  DTRTRI computes the inverse of a real upper or lower triangular
   *  matrix A.
   *
   *  This is the Level 3 BLAS version of the algorithm.
   *
   *  Arguments
   *  =========
   *
   *  uplo    (input) CHARACTER*1
   *          = 'U':  A is upper triangular;
   *          = 'L':  A is lower triangular.
   *
   *  diag    (input) CHARACTER*1
   *          = 'N':  A is non-unit triangular;
   *          = 'U':  A is unit triangular.
   *
   *  n       (input) INTEGER
   *          The order of the matrix A.  n >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (lda,n)
   *          On entry, the triangular matrix A.  If uplo = 'U', the
   *          leading n-by-n upper triangular part of the array A contains
   *          the upper triangular matrix, and the strictly lower
   *          triangular part of A is not referenced.  If uplo = 'L', the
   *          leading n-by-n lower triangular part of the array A contains
   *          the lower triangular matrix, and the strictly upper
   *          triangular part of A is not referenced.  If diag = 'U', the
   *          diagonal elements of A are also not referenced and are
   *          assumed to be 1.
   *          On exit, the (triangular) inverse of the original matrix, in
   *          the same storage format.
   *
   *  lda     (input) INTEGER
   *          The leading dimension of the array A.  lda >= max(1,n).
   *
   *  info    (output) INTEGER
   *          = 0: successful exit
   *          < 0: if info = -i, the i-th argument had an illegal value
   *          > 0: if info = i, A(i,i) is exactly zero.  The triangular
   *               matrix is singular and its inverse can not be computed.
   */
  dtrtri_(&cL, &cU, &N, R.array(), &LDA, &Info);
  if (Info) fatalError();

  mL.resize(mMetabolitesDep.size(), mMetabolitesInd.size());

  imin = getIndMetab(), imax = getIntMetab();
  jmax = getIndMetab();

  for (i = imin; i < imax; i++)
    for (j = 0; j < jmax; j++)
      {
        sum = & mL(i - imin, j);
        *sum = - LU(i, j);

        for (k = j + 1; k < jmax; k++)
          *sum -= LU(i, k) * R(k, j);
      }

#ifdef DEBUG_MATRIX
  DebugFile << "Link Matrix:" << std::endl;
  DebugFile << mLView << std::endl;
#endif // DEBUG_MATRIX
}

void CModel::buildMoieties()
{
  unsigned C_INT32 i;
  unsigned C_INT32 imin = mMetabolitesInd.size();
  unsigned C_INT32 imax = imin + mMetabolitesDep.size();
  unsigned C_INT32 j, jmax = mMetabolitesInd.size();

  CMoiety *pMoiety;

  mMoieties.cleanup();

  for (i = imin; i < imax; i++)
    {
      pMoiety = new CMoiety;

      pMoiety->setName(mMetabolitesX[i]->getName());

      pMoiety->add(1.0, mMetabolitesX[i]);

      for (j = 0; j < jmax; j++)
        {
          if (mLView(i, j) != 0.0)
            pMoiety->add(mLView(i, j), mMetabolitesX[j]);
        }

      pMoiety->setInitialValue();
      //      DebugFile << pMoiety->getDescription() << " = "
      //      << pMoiety->getNumber() << std::endl;

      mMoieties.add(pMoiety, true);
    }

  return;
}

void CModel::setTransitionTimes()
{
  unsigned C_INT32 i, imax = mMetabolites.size();
  unsigned C_INT32 j, jmax = mSteps.size();

  C_FLOAT64 TotalFlux, PartialFlux;
  C_FLOAT64 TransitionTime;

  mTransitionTime = 0.0;

  for (i = 0; i < imax; i++)
    {
      TotalFlux = 0.0;

      if (CMetab::METAB_FIXED == mMetabolites[i]->getStatus())
        mMetabolites[i]->setTransitionTime(DBL_MAX);
      else
        {
          for (j = 0; j < jmax; j++)
            {
              PartialFlux = mStoi[i][j] * *mScaledFluxes[j];

              if (PartialFlux > 0.0)
                TotalFlux += PartialFlux;
            }

          if (TotalFlux == 0.0)
            for (j = 0; j < jmax; j++)
              {
                PartialFlux = - mStoi[i][j] * *mScaledFluxes[j];

                if (PartialFlux > 0.0)
                  TotalFlux += PartialFlux;
              }

          if (TotalFlux == 0.0)
            TransitionTime = DBL_MAX;
          else
            TransitionTime = mMetabolites[i]->getNumber() / TotalFlux;

          mMetabolites[i]->setTransitionTime(TransitionTime);
          mMetabolites[i]->setRate(TotalFlux * mNumber2QuantityFactor);

          if (TransitionTime == DBL_MAX || mTransitionTime == DBL_MAX)
            mTransitionTime = DBL_MAX;
          else
            mTransitionTime += TransitionTime;
        }
    }
}

CCopasiVectorNS < CReaction > & CModel::getReactions()
{
  return mSteps;
}

const CCopasiVectorNS < CReaction > & CModel::getReactions() const
  {return mSteps;}

const CCopasiVectorN< CReaction > & CModel::getReactionsX() const {return mStepsX;}

/**
 *        Return the metabolites of this model
 *        @return vector < CMetab * >
 */
const CCopasiVector< CMetab > & CModel::getMetabolites() const {return mMetabolites;}
CCopasiVector< CMetab > & CModel::getMetabolites() {return mMetabolites;}
CCopasiVector< CMetab > & CModel::getMetabolitesInd() {return mMetabolitesInd;}
CCopasiVector< CMetab > & CModel::getMetabolitesDep() {return mMetabolitesDep;}
const CCopasiVector< CMetab > & CModel::getMetabolitesX() const
  {return mMetabolitesX;}

unsigned C_INT32 CModel::getTotMetab() const
  {return mMetabolites.size();}

unsigned C_INT32 CModel::getIntMetab() const
  {return mMetabolitesInd.size() + mMetabolitesDep.size();}

unsigned C_INT32 CModel::getIndMetab() const
  {return mMetabolitesInd.size();}

unsigned C_INT32 CModel::getDepMetab() const
  {return mMetabolitesDep.size();}

// Added by Yongqun He
/**
 * Get the total steps
 *
 */
unsigned C_INT32 CModel::getTotSteps() const
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
std::string CModel::getComments() const {return mComments;}

std::string CModel::getKey() const {return mKey;}

/**
 *        Return the title of this model
 *        @return string
 */
std::string CModel::getTitle() const {return getObjectName();}

CCopasiVectorNS < CCompartment > & CModel::getCompartments()
{return mCompartments;}

const CCopasiVectorNS < CCompartment > & CModel::getCompartments() const
  {return mCompartments;}

/**
 *  Get the Reduced Stoichiometry Matrix of this Model
 */
const CMatrix < C_FLOAT64 >& CModel::getRedStoi() const
  {return mRedStoi;}

/**
 *  Get the Stoichiometry Matrix of this Model
 */
const CMatrix < C_FLOAT64 >& CModel::getStoi() const
  {return mStoi;}

/**
 *        Return the mMoieties of this model        
 *        @return CCopasiVector < CMoiety > * 
 */
const CCopasiVectorN < CMoiety > & CModel::getMoieties() const
  {return mMoieties;}

/**
 *        Returns the index of the metab
 */
C_INT32 CModel::findMetabByName(const std::string & Target) const
  {
    unsigned C_INT32 i, s;
    std::string name;

    s = mMetabolites.size();
    for (i = 0; i < s; i++)
      {
        name = mMetabolites[i]->getName();
        if (name == Target)
          return i;
      }
    return - 1;
  }

/**
 *        Returns the index of the Moiety
 */
C_INT32 CModel::findMoiety(std::string &Target) const
  {
    unsigned C_INT32 i, s;
    std::string name;

    s = mMoieties.size();
    for (i = 0; i < s; i++)
      {
        name = mMoieties[i]->getName();
        if (name == Target)
          return i;
      }
    return - 1;
  }

void CModel::initializeMetabolites()
{
  unsigned C_INT32 i, j;

  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  mMetabolites.resize(0);

  for (i = 0; i < mCompartments.size(); i++)
    for (j = 0; j < mCompartments[i]->getMetabolites().size(); j++)
      {
        mMetabolites.add(mCompartments[i]->getMetabolites()[j]);
        //        mCompartments[i]->getMetabolites()[j]->setModel(this);
        // mCompartments[i]->getMetabolites()[j]->checkConcentrationAndNumber();
      }
}

/**
 * Returns the mStepsX of this model
 * @return vector < CStep * > 
 */
const CCopasiVectorN< CReaction > & CModel::getStepsX() const {return mStepsX;}

/* only used in steadystate/CMca.cpp */
/**
 *  Get the mLU matrix of this model
 */ 
// const CMatrix < C_FLOAT64 > & CModel::getmLU() const
//  {return mLU;}

/* only used in steadystate/CMca.cpp */
const CModel::CLinkMatrixView & CModel::getL() const
  {return mLView;}

const CModel::CStateTemplate & CModel::getStateTemplate() const
  {return mStateTemplate;}

bool CModel::buildStateTemplate()
{
  bool success = false;

  mStateTemplate.cleanup();

  mStateTemplate.add(getKey()); // Time

  unsigned C_INT32 i, imax;

  for (i = 0, imax = mCompartments.size(); i < imax; i++)
    mStateTemplate.add(mCompartments[i]->getKey());

  for (i = 0, imax = mMetabolites.size(); i < imax; i++)
    mStateTemplate.add(mMetabolites[i]->getKey());

  return success;
}

CState CModel::getInitialState() const
  {
    unsigned C_INT32 i, imax;
    CState s(this);

    /* Set the time */
    s.setTime(mInitialTime);

    /* Set the volumes */
    C_FLOAT64 * Dbl = const_cast<C_FLOAT64 *>(s.getVolumeVector().array());
    for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
      *Dbl = mCompartments[i]->getInitialVolume();

    /* Set the variable Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s.getVariableNumberVector().array());
    for (i = 0, imax = getIntMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolites[i]->getInitialNumber();

    /* Set the fixed Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s.getFixedNumberVector().array());
    for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolites[i]->getInitialNumber();

    //     DebugFile << "getInitialState " << mInitialTime;
    //     for (i = 0, imax = mMetabolitesX.size(); i < imax; i++)
    //       DebugFile << " " << mMetabolitesX[i]->getInitialConcentration();
    //     DebugFile << std::endl;

    return s;
  }

CStateX CModel::getInitialStateX() const
  {
    unsigned C_INT32 i, imax;
    CStateX s(this);

    /* Set the time */
    s.setTime(mInitialTime);

    /* Set the volumes */
    C_FLOAT64 * Dbl = const_cast<C_FLOAT64 *>(s.getVolumeVector().array());
    for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
      *Dbl = mCompartments[i]->getInitialVolume();

    /* Set the independent variable Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s.getVariableNumberVector().array());
    for (i = 0, imax = getIndMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolitesX[i]->getInitialNumber();

    /* Set the dependent variable Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s.getDependentNumberVector().array());
    for (i = getIndMetab(), imax = getIntMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolitesX[i]->getInitialNumber();

    /* Set the fixed Metabolites */
    Dbl = const_cast<C_FLOAT64 *>(s.getFixedNumberVector().array());
    for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
      *Dbl = mMetabolitesX[i]->getInitialNumber();

    //     DebugFile << "getInitialStateX " << mInitialTime;
    //     for (i = 0, imax = mMetabolitesX.size(); i < imax; i++)
    //       DebugFile << " " << mMetabolitesX[i]->getInitialConcentration();
    //     DebugFile << std::endl;

    return s;
  }

void CModel::setInitialState(const CState * state)
{
  unsigned C_INT32 i, imax;

  /* Set the volumes */
  const C_FLOAT64 * Dbl = state->getVolumeVector().array();

  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);

  /* Set the variable metabolites */
  Dbl = state->getVariableNumberVector().array();
  for (i = 0, imax = getIntMetab(); i < imax; i++, Dbl++)
    mMetabolites[i]->setInitialNumber(*Dbl);

  /* Set the fixed metabolites */
  Dbl = state->getFixedNumberVector().array();
  for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
    mMetabolites[i]->setInitialNumber(*Dbl);

  /* We need to update the initial values for moieties */
  for (i = 0, imax = mMoieties.size(); i < imax; i++)
    mMoieties[i]->setInitialValue();

  return;
}

void CModel::setInitialState(const CStateX * state)
{
  unsigned C_INT32 i, imax;

  /* Set the volumes */
  const C_FLOAT64 * Dbl = state->getVolumeVector().array();
  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);

  /* Set the independent variable metabolites */
  Dbl = state->getVariableNumberVector().array();
  for (i = 0, imax = getIndMetab(); i < imax; i++, Dbl++)
    mMetabolitesX[i]->setInitialNumber(*Dbl);

  /* Set the dependent variable metabolites */
  Dbl = state->getDependentNumberVector().array();
  for (i = getIndMetab(), imax = getIntMetab(); i < imax; i++, Dbl++)
    mMetabolitesX[i]->setInitialNumber(*Dbl);

  /* Set the fixed metabolites */
  Dbl = state->getFixedNumberVector().array();
  for (i = getIntMetab(), imax = getTotMetab(); i < imax; i++, Dbl++)
    mMetabolitesX[i]->setInitialNumber(*Dbl);

  /* We need to update the initial values for moieties */
  for (i = 0, imax = mMoieties.size(); i < imax; i++)
    mMoieties[i]->setInitialValue();

  return;
}

void CModel::setState(const CState * state)
{
  unsigned C_INT32 i, imax;
  const C_FLOAT64 * Dbl;

  //  DebugFile << *state << std::endl;
  /* Set the time */
  mTime = state->getTime();

#ifdef XXXX // This gets enabled when we have dynamic volume changes
  /* Set the volumes */
  Dbl = state->getVolumeVector();
  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);
#endif // XXXX

  /* Set the variable metabolites */
  Dbl = state->getVariableNumberVector().array();
  for (i = 0, imax = getIntMetab(); i < imax; i++, Dbl++)
    mMetabolites[i]->setNumber(*Dbl);

  //   DebugFile << "setState " << mTime;
  //   for (i = 0, imax = mMetabolitesX.size(); i < imax; i++)
  //     DebugFile << " " << mMetabolitesX[i]->getConcentration();
  //   DebugFile << std::endl;

  return;
}

void CModel::initObjects()
{
  addObjectReference("Time", mTime, CCopasiObject::ValueDbl);
  addObjectReference("Comments", mComments);
  //  add(&mCompartments);
  //  add(&mMetabolites);
  //  add(&mMetabolitesX);
  //  add(&mMetabolitesInd);
  //  add(&mMetabolitesDep);
  //  add(&mSteps);
  //  add(&mStepsX);
  //  add(&mStepsInd);
  addVectorReference("Fluxes", mFluxes, CCopasiObject::ValueDbl);
  //  addVectorReference("Reduced Model Fluxes", mFluxesX);
  addVectorReference("Scaled Fluxes", mScaledFluxes, CCopasiObject::ValueDbl);
  //  addVectorReference("Reduced Model Scaled Fluxes", mScaledFluxesX);
  // addObjectReference("Transition Time", mTransitionTime);
  addMatrixReference("Stoichiometry", mStoi, CCopasiObject::ValueDbl);
  addMatrixReference("Reduced Model Stoichiometry", mRedStoi, CCopasiObject::ValueDbl);
  // addVectorReference("Metabolite Interchanges", mRowLU);
  // addVectorReference("Reaction Interchanges", mColLU);
  // addMatrixReference("L", mL);
  addMatrixReference("Link Matrix", mLView, CCopasiObject::ValueDbl);
  addObjectReference("Quantity Unit", mQuantityUnit);
  addObjectReference("Quantity Conversion Factor", mQuantity2NumberFactor, CCopasiObject::ValueDbl);
  // addObjectReference("Inverse Quantity Conversion Factor",
  //                    mNumber2QuantityFactor);
}

void CModel::setState(const CStateX * state)
{
  unsigned C_INT32 i, imax;
  const C_FLOAT64 * Dbl;

  //  DebugFile << *state << std::endl;
  /* Set the time */
  mTime = state->getTime();

#ifdef XXXX // This gets enabled when we have dynamic volume changes

  Dbl = state->getVolumeVector();
  for (i = 0, imax = mCompartments.size(); i < imax; i++, Dbl++)
    mCompartments[i]->setVolume(*Dbl);
#endif // XXXX

  /* Set the independent variable metabolites */
  Dbl = state->getVariableNumberVector().array();
  for (i = 0, imax = getIndMetab(); i < imax; i++, Dbl++)
    mMetabolitesX[i]->setNumber(*Dbl);

  /* We need to update the dependent metabolites by using moieties */
  /* This changes need to be reflected in the current state */
  C_FLOAT64 NumberDbl;

  for (i = 0, imax = mMoieties.size(); i < imax; i++)
    {
      NumberDbl = mMoieties[i]->dependentNumber();
      mMetabolitesDep[i]->setNumber(NumberDbl);
      (const_cast<CStateX *>(state))->setDependentNumber(i, NumberDbl);
    }

  //   DebugFile << "setStateX " << mTime;
  //   for (i = 0, imax = mMetabolitesX.size(); i < imax; i++)
  //     DebugFile << " " << mMetabolitesX[i]->getConcentration();
  //   DebugFile << std::endl;

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

void CModel::getDerivatives(CState * state, CVector< C_FLOAT64 > & derivatives)
{
  setState(state);

  unsigned C_INT32 i, imax = mMetabolitesInd.size() + mMetabolitesDep.size();
  unsigned C_INT32 j, jmax = mSteps.size();

  assert (derivatives.size() == imax);

  for (j = 0; j < jmax; j++)
    mSteps[j]->calculate();

  // Calculate ydot = Stoi * v
  for (i = 0; i < imax; i++)
    {
      derivatives[i] = 0.0;

      for (j = 0; j < jmax; j++)
        derivatives[i] += mStoi[i][j] * *mScaledFluxes[j];
    }

  return;
}

void CModel::getDerivatives(CStateX * state, CVector< C_FLOAT64 > & derivatives)
{
  setState(state);

  unsigned C_INT32 i, imax = mMetabolitesInd.size();
  unsigned C_INT32 j, jmax = mStepsX.size();

  assert (derivatives.size() == imax);

  for (j = 0; j < jmax; j++)
    mStepsX[j]->calculate();

  // Calculate ydot = RedStoi * v
  for (i = 0; i < imax; i++)
    {
      derivatives[i] = 0.0;

      for (j = 0; j < jmax; j++)
        derivatives[i] += mRedStoi[i][j] * *mScaledFluxesX[j];
    }

  return;
}

unsigned C_INT32 CModel::unitCompare(const std::string & name,
                                     const char ** units,
                                     const unsigned C_INT32 unique)
{
  unsigned C_INT32 i, j;
  std::string Unit;

  for (i = 0; *units; i++, units++)
    {
      Unit = *units;
      for (j = Unit.length(); j >= unique || j == Unit.length(); j--)
        if (Unit.substr(0, j) == name.substr(0, j)) return i;
    }

  return i;
}

bool CModel::setVolumeUnit(const std::string & name)
{
  CModel::VolumeUnit Unit =
    (CModel::VolumeUnit) unitCompare(name, VolumeUnitName, 2);

  return setVolumeUnit(Unit);
}

bool CModel::setVolumeUnit(const CModel::VolumeUnit & unit)
{
  bool success = true;

  switch (unit)
    {
    case l:
    case ml:
    case microl:
    case nl:
    case pl:
    case fl:
      mVolumeUnit = VolumeUnitName[unit];
      break;

    default:
      mVolumeUnit = VolumeUnitName[ml];
      success = false;
    }

  return success;
}

std::string CModel::getVolumeUnit() const
{return mVolumeUnit;}

bool CModel::setTimeUnit(const std::string & name)
{
  CModel::TimeUnit Unit =
    (CModel::TimeUnit) unitCompare(name, TimeUnitName, 1);

  return setTimeUnit(Unit);
}

bool CModel::setTimeUnit(const CModel::TimeUnit & unit)
{
  bool success = true;

  switch (unit)
    {
    case s:
    case m:
    case h:
    case d:
      mTimeUnit = TimeUnitName[unit];
      break;

    default:
      mTimeUnit = TimeUnitName[s];
      success = false;
    }

  return success;
}

std::string CModel::getTimeUnit() const
{return mTimeUnit;}

bool CModel::setQuantityUnit(const std::string & name)
{
  CModel::QuantityUnit Unit =
    (CModel::QuantityUnit) unitCompare(name, QuantityUnitName, 2);

  return setQuantityUnit(Unit);
}

bool CModel::setQuantityUnit(const CModel::QuantityUnit & unit)
{
  CModel::QuantityUnit Unit = unit;
  bool success = true;

  switch (Unit)
    {
    case Mol:
      mQuantity2NumberFactor = 6.020402E23;
      break;

    case mMol:
      mQuantity2NumberFactor = 6.020402E20;
      break;

    case microMol:
      mQuantity2NumberFactor = 6.020402E17;
      break;

    case nMol:
      mQuantity2NumberFactor = 6.020402E14;
      break;

    case pMol:
      mQuantity2NumberFactor = 6.020402E11;
      break;

    case fMol:
      mQuantity2NumberFactor = 6.020402E8;
      break;

    case number:
      mQuantity2NumberFactor = 1.0;
      break;

    default:
      Unit = number;
      mQuantity2NumberFactor = 1.0;
      success = false;
    }

  mQuantityUnit = QuantityUnitName[Unit];

  mNumber2QuantityFactor = 1.0 / mQuantity2NumberFactor;

  return success;
}

std::string CModel::getQuantityUnit() const
{return mQuantityUnit;}

const C_FLOAT64 & CModel::getQuantity2NumberFactor() const
  {return mQuantity2NumberFactor;}

const C_FLOAT64 & CModel::getNumber2QuantityFactor() const
  {return mNumber2QuantityFactor;}

bool CModel::setTitle(const std::string &title)
{
  return setObjectName(title);
}

void CModel::setComments(const std::string &comments)
{
  mComments = comments;
}

void CModel::setInitialTime(const C_FLOAT64 & time) {mInitialTime = time;}

const C_FLOAT64 & CModel::getInitialTime() const {return mInitialTime;}

void CModel::setTime(const C_FLOAT64 & time) {mTime = time;}

const C_FLOAT64 & CModel::getTime() const {return mTime;}

bool CModel::addMetabolite(const std::string & name,
                           const std::string & compartment,
                           const C_FLOAT64 & iconc,
                           const CMetab::Status & status)
{
  unsigned C_INT32 Index;

  if (mCompartments.size() == 0)
    addCompartment("compartment_0");

  if (compartment == "")
    Index = 0;
  else if ((Index = mCompartments.getIndex(compartment)) == C_INVALID_INDEX)
    return false;

  if (mCompartments[Index]->getMetabolites().getIndex(name) != C_INVALID_INDEX)
    return false;

  CMetab * pMetab = new CMetab(name);
  // pMetab->setName(name);

  // mCompartments[Index]->addMetabolite(pMetab) takes care of the below
  // pMetab->setModel(this);
  // pMetab->setCompartment(mCompartments[Index]);

  if (!mCompartments[Index]->addMetabolite(pMetab))
    {
      delete pMetab;
      return false;
    }

  pMetab->setStatus(status);
  pMetab->setInitialConcentration(iconc);

  return mMetabolites.add(pMetab);
}

std::vector<std::string> CModel::removeCompReacKeys(const std::string & key)
{
  std::vector<std::string> compReacKeys, metabReacKeys;

  CCompartment* comp = (CCompartment*)(CCopasiContainer*)CKeyFactory::get(key);
  const CCopasiVectorNS < CMetab > & Metabs = comp->getMetabolites();
  C_INT32 j, jmax = Metabs.size();

  for (j = 0; j < jmax; j++)
    {
      metabReacKeys = removeMetabReacKeys(Metabs[j]->getKey());
      if (compReacKeys.size() == 0)
        {
          compReacKeys.resize(metabReacKeys.size());
          compReacKeys = metabReacKeys;
        }
      else
        {
          unsigned C_INT32 reacFound = 0;
          for (unsigned C_INT32 i = 0; i < metabReacKeys.size(); i++)
            {
              reacFound = 0;
              for (unsigned C_INT32 k = 0; k < compReacKeys.size(); k++)
                {
                  if (compReacKeys[k] == metabReacKeys[i])
                    {
                      reacFound = 1;
                      break;
                    }
                }
              if (reacFound == 0)
                {
                  compReacKeys.resize(compReacKeys.size() + 1);
                  compReacKeys[compReacKeys.size() - 1] = metabReacKeys[i];
                }
            }
        }
    }

  return compReacKeys;
}

std::vector<std::string> CModel::removeMetabReacKeys(const std::string & key)
{
  std::vector<std::string> Keys;
  unsigned C_INT32 k = 0;
  const CCopasiVectorN<CReaction> & Reactions = getReactions();
  C_INT32 j, reactionChecked, jmax = Reactions.size();

  for (j = 0; j < jmax; j++)
    {
      reactionChecked = 0;
      const CCopasiVector <CChemEqElement> &Substrates = Reactions[j]->getChemEq().getSubstrates();
      C_INT32 i, imax = Substrates.size();
      for (i = 0; i < imax; i++)
        {
          if (key == Substrates[i]->getMetaboliteKey())
            {
              Keys.resize(k + 1);
              Keys[k++] = Reactions[j]->getKey();
              reactionChecked = 1;
              break;
            }
        }

      if (reactionChecked == 0)
        {
          const CCopasiVector <CChemEqElement> &Products = Reactions[j]->getChemEq().getProducts();
          imax = Products.size();
          for (i = 0; i < imax; i++)
            if (key == Products[i]->getMetaboliteKey())
              {
                Keys.resize(k + 1);
                Keys[k++] = Reactions[j]->getKey();
                reactionChecked = 1;
                break;
              }
        }

      if (reactionChecked == 0)
        {
          const CCopasiVector <CChemEqElement> &Modifiers = Reactions[j]->getChemEq().getModifiers();
          imax = Modifiers.size();
          for (i = 0; i < imax; i++)
            if (key == Modifiers[i]->getMetaboliteKey())
              {
                Keys.resize(k + 1);
                Keys[k++] = Reactions[j]->getKey();
                reactionChecked = 1;
                break;
              }
        }
    }

  return Keys;
}

/*std::string CModel::removeMetabReactions(const std::string & key)
{
  std::string EffectedReactions = "Following Reactions will be effected:\n";
  unsigned C_INT32 reactionFound = 0;
  const CCopasiVectorN <CReaction> & Reactions = getReactions();
  C_INT32 j, reactionChecked, jmax = Reactions.size();
 
  for (j = 0; j < jmax; j++)
    {
      reactionChecked = 0;
      const CCopasiVector <CChemEqElement> &Substrates = Reactions[j]->getChemEq().getSubstrates();
      C_INT32 i, imax = Substrates.size();
      for (i = 0; i < imax; i++)
        {
          if (key == Substrates[i]->getMetaboliteKey())
            {
              EffectedReactions.append(Reactions[j]->getName());
              EffectedReactions.append(", ");
              reactionFound = 1;
              reactionChecked = 1;
              break;
            }
        }
 
      if (reactionChecked == 0)
        {
          const CCopasiVector <CChemEqElement> &Products = Reactions[j]->getChemEq().getProducts();
          imax = Products.size();
          for (i = 0; i < imax; i++)
            if (key == Products[i]->getMetaboliteKey())
              {
                EffectedReactions.append(Reactions[j]->getName());
                EffectedReactions.append(", ");
                reactionFound = 1;
                reactionChecked = 1;
                break;
              }
        }
 
      if (reactionChecked == 0)
        {
          const CCopasiVector <CChemEqElement> &Modifiers = Reactions[j]->getChemEq().getModifiers();
          imax = Modifiers.size();
          for (i = 0; i < imax; i++)
            if (key == Modifiers[i]->getMetaboliteKey())
              {
                EffectedReactions.append(Reactions[j]->getName().c_str());
                EffectedReactions.append(", ");
                reactionFound = 1;
                reactionChecked = 1;
                break;
              }
        }
    }
 
  if (reactionFound == 1)
      return EffectedReactions.substr(0, EffectedReactions.length() - 2);    
  else
   return NULL;
}*/

bool CModel::removeMetabolite(const std::string & key)
{
  CMetab* pMetabolite =
    dynamic_cast<CMetab *>(CKeyFactory::get(key));

  if (!pMetabolite)
    return false;

  /* Check if metabolite with that name exists */
  unsigned C_INT32 index = mMetabolites.getIndex(pMetabolite);
  if (index == C_INVALID_INDEX)
    return false;

  /* Before deleting the metabolite, delete all the reactions that are dependent */
  std::vector<std::string> reacKeys = removeMetabReacKeys(key);
  for (unsigned C_INT32 i = 0; i < reacKeys.size(); i++)
    removeReaction(reacKeys[i]);

  mMetabolites.remove(index);

  compile();

  return true;
}

bool CModel::addCompartment(const std::string & name,
                            const C_FLOAT64 & volume)
{
  // check if there is already a volume with this name
  if (mCompartments.getIndex(name) != C_INVALID_INDEX)
    return false;

  CCompartment * cpt = new CCompartment(name);

  cpt->setInitialVolume(volume);
  cpt->setVolume(volume);

  if (!mCompartments.add(cpt, true))
    {
      delete cpt;
      return false;
    }

  return true;
}

bool CModel::removeCompartment(const std::string & key)
{
  CCompartment *pCompartment =
    dynamic_cast< CCompartment * >(CKeyFactory::get(key));

  if (!pCompartment)
    return false;

  //Check if Compartment with that name exists
  unsigned C_INT32 index =
    mCompartments.CCopasiVector< CCompartment >::getIndex(pCompartment);
  if (index == C_INVALID_INDEX)
    return false;

  /* Delete the dependent Metabolites before deleting the Compartment */
  const CCopasiVectorNS <CMetab> &Metabs = pCompartment->getMetabolites();
  for (unsigned C_INT32 i = 0; i < Metabs.size(); i++)
    removeMetabolite(Metabs[i]->getKey());

  mCompartments.CCopasiVector< CCompartment >::remove(index);

  compile();
  return true;
}

bool CModel::addReaction(const std::string & name)
{
  if (mSteps.getIndex(name) != C_INVALID_INDEX)
    return false;

  CReaction * pReaction = new CReaction(name);

  if (!mSteps.add(pReaction, true))
    {
      delete pReaction;
      return false;
    }
  return true;
}

bool CModel::addReaction(const CReaction & reaction)
{
  if (mSteps.getIndex(reaction.getName()) != C_INVALID_INDEX)
    return false;

  mSteps.add(reaction);
  mSteps[reaction.getName()]->compile(mCompartments);
  return true;
}

bool CModel::removeReaction(const std::string & key)
{
  CReaction * pReaction =
    dynamic_cast< CReaction * >(CKeyFactory::get(key));

  if (!pReaction)
    return false;

  //Check if Reaction exists
  unsigned C_INT32 index =
    mSteps.CCopasiVector< CReaction >::getIndex(pReaction);

  if (index == C_INVALID_INDEX)
    return false;

  mSteps.CCopasiVector< CReaction >::remove(index);

  compile();
  return true;
}

const CVector<unsigned C_INT32> & CModel::getMetabolitePermutation() const
{return mRowLU;}

const CVector<unsigned C_INT32> & CModel::getReactionPermutation() const
  {return mColLU;}

void CModel::updateDepMetabNumbers(CStateX const & state) const
  {
    (const_cast< CModel * >(this))->setState(&state);
  }

const CModel::CLinkMatrixView::elementType CModel::CLinkMatrixView::mZero = 0.0;
const CModel::CLinkMatrixView::elementType CModel::CLinkMatrixView::mUnit = 1.0;

CModel::CLinkMatrixView::CLinkMatrixView(const CMatrix< C_FLOAT64 > & A,
    const CCopasiVector< CMetab > & independent):
    mA(A),
    mIndependent(independent)
{CONSTRUCTOR_TRACE;}

CModel::CLinkMatrixView::~CLinkMatrixView()
{DESTRUCTOR_TRACE;}

CModel::CLinkMatrixView &
CModel::CLinkMatrixView::operator = (const CModel::CLinkMatrixView & rhs)
{
  const_cast< CMatrix< C_FLOAT64 > &>(mA) = rhs.mA;
  const_cast< CCopasiVector< CMetab > &>(mIndependent) = rhs.mIndependent;

  return *this;
}

unsigned C_INT32 CModel::CLinkMatrixView::numRows() const
  {return mIndependent.size() + mA.numRows();}

unsigned C_INT32 CModel::CLinkMatrixView::numCols() const
  {return mA.numCols();}

CModel::CStateTemplate::CStateTemplate() :
    mList(),
    mKeyMap(),
    mObjectMap()
{}

CModel::CStateTemplate::~CStateTemplate() {cleanup();}

bool CModel::CStateTemplate::cleanup()
{
  std::vector< std::pair< std::string, std::string > * >::iterator it =
    mList.begin();
  std::vector< std::pair< std::string, std::string > * >::iterator End =
    mList.end();

  for (; it != End; ++it)
    if (*it)
      {
        CKeyFactory::remove((*it)->first);
        delete *it;
        *it = NULL;
      }

  mList.clear();
  mKeyMap.clear();
  mObjectMap.clear();

  return true;
}

bool CModel::CStateTemplate::add(const std::string & objectKey)
{
  std::pair< std::string, std::string > * pAdd =
    new std::pair< std::string, std::string >
    (CKeyFactory::add("StateVariable", NULL), objectKey);

  mList.push_back(pAdd);

  mKeyMap[pAdd->first] = &objectKey;
  mObjectMap[objectKey] = &pAdd->first;

  return true;
}

std::string CModel::CStateTemplate::getObjectKey(const std::string & key) const
  {return *(*const_cast<std::map< std::string, const std::string * > *>(&mKeyMap))[key];}

std::string CModel::CStateTemplate::getKey(const std::string & objectKey) const
  {return *(*const_cast<std::map< std::string, const std::string * > *>(&mObjectMap))[objectKey];}

unsigned C_INT32 CModel::CStateTemplate::size() const {return mList.size();}

std::pair< std::string, std::string >
CModel::CStateTemplate::operator[](const unsigned C_INT32 & index) const
  {
    return * mList[index];
  }

bool CModel::hasReversibleReaction() const
  {
    unsigned C_INT32 i, imax = mSteps.size();
    for (i = 0; i < imax; ++i) if (mSteps[i]->isReversible()) return true;

    return false;
  }

std::ostream &operator<<(std::ostream &os,
                         const CModel::CLinkMatrixView & A)
{
  unsigned C_INT32 i, imax = A.numRows();
  unsigned C_INT32 j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "  " << A(i, j);
      os << std::endl;
    }
  return os;
}
