// model.cpp : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CModel
#include <string>
#include <vector>
#include <limits.h>
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif //DBL_MAX

//#include "utilities/CCopasiException.h"

#define  COPASI_TRACE_CONSTRUCTION 

#include "copasi.h"
#include "utilities/utilities.h"
#include "CModel.h"
#include "CCompartment.h"
#include "tnt/luX.h"
#include "tnt/triang.h"
#include "tnt/transv.h"
#include "utilities/CGlobals.h"

CModel::CModel()
{
  CONSTRUCTOR_TRACE;
  mComments = "";

  mpLView = new
    TNT::UnitLowerTriangularView <TNT::Matrix <C_FLOAT64 > > (mL);
  
  mpInverseLView = new
    TNT::Transpose_View<TNT::UpperTriangularView<TNT::Matrix<C_FLOAT64 > > >
    (mL);
}

CModel::CModel(const CModel & src)
{
  CONSTRUCTOR_TRACE;
  mpLView = new
    TNT::UnitLowerTriangularView <TNT::Matrix <C_FLOAT64 > > (mL);
  
  mpInverseLView = new
    TNT::Transpose_View<TNT::UpperTriangularView<TNT::Matrix<C_FLOAT64 > > >
    (mL);

  mTitle = src.mTitle;
  mComments = src.mComments;

  mCompartments = CCopasiVectorNS < CCompartment >(src.mCompartments);
  mSteps = CCopasiVectorS < CReaction >(src.mSteps);

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
  mCompartments.cleanup();
  mSteps.cleanup();
  mMoieties.cleanup();
}

C_INT32 CModel::load(CReadConfig & configBuffer)
{
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
  unsigned C_INT32 i;

  // For old Versions we need must read the list of Metabolites beforehand
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

  initializeMetabolites();

  if ((Fail = Copasi->FunctionDB.load(configBuffer))) return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                       CReadConfig::LOOP)))
    return Fail;
    
  mSteps.load(configBuffer, Size);
    
  // We must postprocess the steps for old file versions
  if (configBuffer.getVersion() < "4")
    for (i = 0; i < mSteps.size(); i++)
      mSteps[i]->old2New(mMetabolites);
            
  for (i = 0; i < mSteps.size(); i++)
    mSteps[i]->compile(mCompartments);

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
 
  Size = mCompartments.size();
  if ((Fail = configBuffer.setVariable("TotalCompartments", "C_INT32", &Size)))
    return Fail;
 
  mCompartments.save(configBuffer);
  
  if ((Fail = Copasi->FunctionDB.save(configBuffer))) return Fail;

  Size = mSteps.size();
  if ((Fail = configBuffer.setVariable("TotalSteps", "C_INT32", &Size)))
    return Fail;
    
  mSteps.save(configBuffer);

  return Fail;
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
  
  for (i=0; i<imax; i++)
    if (mMetabolites[i]->getStatus() == METAB_FIXED)
      mMetabolitesX[imax - ++j] = mMetabolites[i];
    else
      mMetabolitesX[i - j] = mMetabolites[i];
  
  for (i=0; i<imax; i++)
    mMetabolites[i] = mMetabolitesX[i];
  
  mFluxes.resize(mSteps.size());
  for (i=0; i<mSteps.size(); i++)
    mFluxes[i] = (C_FLOAT64 *) mSteps[i]->getFluxAddr();
    
  mStoi.newsize(imax-j, mSteps.size());
  for (i=0; i<(unsigned C_INT32) mStoi.num_cols(); i++)
    {
      Structure = mSteps[i]->getChemEq().getBalances();
        
      for (j=0; j<(unsigned C_INT32) mStoi.num_rows(); j++)
        {
          mStoi[j][i] = 0.0;
          Name = mMetabolites[j]->getName();

          for (k=0; k<Structure.size(); k++)
            if (Structure[k]->getMetaboliteName() == Name)
              {
                mStoi[j][i] = Structure[k]->getMultiplicity();
                break;
              }
        }
    }
  cout << "Stoichiometry Matrix" << endl;
  cout << mStoi << endl;
    
  return;
}

void CModel::lUDecomposition()
{
  unsigned C_INT32 i;
    
  TNT::Vector < unsigned C_INT32 > rowLU(mStoi.num_rows());
  TNT::Vector < unsigned C_INT32 > colLU(mStoi.num_cols());
  
  mLU = mStoi;
  
  TNT::LUX_factor(mLU, rowLU, colLU);
  
  TNT::UpperTriangularView < TNT::Matrix < C_FLOAT64 > > U(mLU);
  TNT::UnitLowerTriangularView < TNT::Matrix < C_FLOAT64 > > L(mLU);

  cout << "U" << endl;
  cout << U << endl;
  cout << "L" << endl;
  cout << L << endl;

  // mMetabolitesX = mMetabolites;
    
  mStepsX.resize(mSteps.size());
  for (i=0; i<mSteps.size(); i++)
    mStepsX[i] = mSteps[i];

  // permutate Metabolites and Steps to match rearangements done during
  // LU decomposition

  CMetab *pMetab;
  for (i = 0; i < (unsigned C_INT32) rowLU.size(); i++) 
    {
      if (rowLU[i] - 1 > i)
        {
          pMetab = mMetabolitesX[i];
          mMetabolitesX[i] = mMetabolitesX[rowLU[i]-1];
          mMetabolitesX[rowLU[i]-1] = pMetab;
        }
    }
    
  CReaction *pStep;
  for (i = colLU.size(); 0 < i--; ) 
    {
      if (colLU[i]-1 < i)
        {
          pStep = mStepsX[i];
          mStepsX[i] = mStepsX[colLU[i]-1];
          mStepsX[colLU[i]-1] = pStep;
        }
    }
  
  mFluxesX.resize(mStepsX.size());
  
  for (i=0; i<mFluxesX.size(); i++)
    mFluxesX[i] = (C_FLOAT64 *) mStepsX[i]->getFluxAddr();
  
  return;
}

void CModel::setMetabolitesStatus()
{
  C_INT32 i,j,k;
  C_FLOAT64 Sum;
    
  // for (i=0; i<min(mLU.num_rows(), mLU.num_cols()); i++)
  // for compiler
  C_INT32 imax = (mLU.num_rows() < mLU.num_cols()) ? 
    mLU.num_rows() : mLU.num_cols();
  for (i=0; i<imax; i++)
    {
      if (mLU[i][i] == 0.0) break;
      mMetabolitesX[i]->setStatus(METAB_VARIABLE);
    }
  mMetabolitesInd.clear();
  mMetabolitesInd.insert(0,&mMetabolitesX[0],&mMetabolitesX[i]);
  mStepsInd.insert(0,&mStepsX[0],&mStepsX[i]);
    
  for (j=i; j<mLU.num_rows(); j++)
    {
      Sum = 0.0;
        
      for (k=0; k<mLU.num_cols(); k++)
        Sum += fabs(mLU[j][k]);
      if (Sum == 0.0) break;
      mMetabolitesX[j]->setStatus(METAB_DEPENDENT);
    }
  mMetabolitesDep.clear();
  mMetabolitesDep.insert(0,&mMetabolitesX[i],&mMetabolitesX[j]);

  for (k=j; k<mLU.num_rows(); k++)
    mMetabolitesX[k]->setStatus(METAB_FIXED);

  return;
}

void CModel::buildRedStoi()
{
  C_INT32 i,j,k;
  C_FLOAT64 Sum;
  C_INT32 imax, jmax, kmax;                // wei for compiler

  imax = mMetabolitesInd.size();
  jmax = mStepsX.size();
  
  mRedStoi.newsize(imax, jmax);
  
  for (i=0; i<imax; i++)
    for (j=0; j<jmax; j++)
      {
        /* Since L[i,k] = 1 for k = i and L[i,k] = 0 for k > i
           we have to avoid L[i,k] where k >= i, i.e.. k < i.
           Similarly, since U[k,j] = 0 for k > j
           we have to avoid U[k,j] where k > j, i.e., k <= j. */
        if (j<i)
          {    
            Sum = 0.0;
            kmax = j+1;
          }
        else
          {
            /* For j < i we are missing a part of the sum: */
            /* Sum +=  mLU[i][j]; since L[i,i] = 1 */
            Sum = mLU[i][j];
            kmax = i;
          }

        for (k=0; k<kmax; k++)
          Sum += mLU[i][k] * mLU[k][j];

        mRedStoi[i][j] = Sum;
      }
  cout << "Reduced Stoichiometry Matrix" << endl;
  cout << mRedStoi << endl;
    
  return;
}

void CModel::buildL()
{
  unsigned C_INT32 size = mStoi.num_rows();
  unsigned C_INT32 i, j, jmax, k;
  TNT::UnitLowerTriangularView < TNT::Matrix < C_FLOAT64 > > L(mLU);
  
  mL.newsize(size,size);
  jmax = (size < mSteps.size()) ? size : mSteps.size();
 
  /* Create L from the UnitLowerTriangularView of mLU */
  for (i=0; i<size; i++)
    for (j=0; j<jmax; j++)
      mL[i][j] = L(i+1,j+1);
  
  /* We complete L so that it is a square matrix */
  for (i=0; i<size; i++)
    for (j=jmax; j<size; j++)
      mL[i][j] = 0.0;

  for (j=jmax; j<size; j++)
    mL[j][j] = 1.0;

  /* Calculate the inverse of L and store it in the upper triangular 
     part of L */

  C_FLOAT64 *sum;
  jmax = (size) ? size - 1: size;
  for (j=0; j<jmax; j++)
    for (i=j+1; i<size; i++)
    {
        sum = &mL[j][i];
        *sum = - mL[i][j];
        for (k=j+1; k<i; k++)
            // I[i][j] -= mL[i][k] * I[k][j]
            *sum -= mL[i][k] * mL[j][k];
    }

  cout << "L" << endl; 
  cout << 
    TNT::LowerTriangularView< TNT::Matrix< C_FLOAT64 > >(mL) 
       << endl;
  cout << "L inverse" << endl; 
  cout << 
    TNT::Transpose_View< TNT::UpperTriangularView< TNT::Matrix< C_FLOAT64 > > >(mL)
       << endl;
  
}

#ifdef XXXX
void CModel::buildConsRel()
{
  mConsRel.newsize(mMetabolites.size(), mMetabolitesInd.size());
    
  C_INT32 i,j;

  C_INT32 imax = (mConsRel.num_rows() > mConsRel.num_cols()) ? 
    mConsRel.num_cols() : mConsRel.num_rows();
    
  // wei for compiler for (i=0; i<min(mConsRel.num_rows(), mConsRel.num_cols()); i++)
  for (i=0; i<imax; i++)
    mConsRel[i+1][i] = mLU[i+1][i];
    
  for (j=0; j<mConsRel.num_cols(); j++)
    for (i=j+2; i<mConsRel.num_rows(); i++)
      mConsRel[i][j] = mLU[i][j] + mLU[i][i-1] * mConsRel[i-1][j];

  cout << mConsRel << endl;
  
  return;
}
#endif // XXXX

void CModel::buildMoieties()
{
  unsigned C_INT32 i;
  unsigned C_INT32 imin = mMetabolitesInd.size();
  unsigned C_INT32 imax = imin + mMetabolitesDep.size();
  unsigned C_INT32 j;
  unsigned C_INT32 jmax = imin;
  
  CMoiety *pMoiety;
  
  mMoieties.cleanup();

  for (i=imin; i<imax; i++)
    {
      pMoiety = new CMoiety;
    
      pMoiety->setName(mMetabolitesX[i]->getName());
      pMoiety->add(1.0, mMetabolitesX[i]);
        
      for (j=0; j<jmax; j++)
        {
          if (mL[j][i] != 0.0)
            pMoiety->add(mL[j][i], mMetabolitesX[j]);
        }
      pMoiety->setInitialValue();
      cout << pMoiety->getDescription() << " = " 
	   << pMoiety->getNumber() << endl;
      
      mMoieties.add(pMoiety);
    }
    
  return;
}

void CModel::setConcentrations(const C_FLOAT64 * y)
{
  unsigned C_INT32 i;

  // Set the concentration of the independent metabolites
  for (i=0; i < mMetabolitesInd.size(); i++)
    {
      mMetabolitesInd[i]->setNumber(y[i]);
      cout << *mMetabolitesInd[i]->getConcentration() << "  ";
    }
  
  // Set the concentration of the dependent metabolites
  for (i=0; i<mMetabolitesDep.size(); i++)
    {
      mMetabolitesDep[i]->setNumber(mMoieties[i]->dependentNumber());
      cout << *mMetabolitesDep[i]->getConcentration() << "  ";
    }
  cout << endl;
  
  // Calculate the velocity vector depending on the step kinetics
  for (i=0; i<mStepsX.size(); i++)
   mStepsX[i]->calculate();

  return;
}

void CModel::setTransitionTimes()
{
  unsigned C_INT32 i, imax = getIntMetab();
  unsigned C_INT32 j, jmax = mSteps.size();
  C_FLOAT64 TotalFlux, PartialFlux;
  C_FLOAT64 TransitionTime;
  
  mTransitionTime = 0.0;
  
  for(i=0; i<imax; i++)
    {
      TotalFlux = 0.0;
      for (j=0; j<jmax; j++)
	{
	  PartialFlux = mStoi[i][j] * *mFluxes[j];
	  if (PartialFlux > 0.0) TotalFlux += PartialFlux;
	}

      if (TotalFlux == 0.0)
	TransitionTime = DBL_MAX;
      else
	TransitionTime = mMetabolites[i]->getNumber() / TotalFlux;

      mMetabolites[i]->setTransitionTime(TransitionTime);

      if (TransitionTime == DBL_MAX || mTransitionTime == DBL_MAX)
	mTransitionTime = DBL_MAX;
      else
	mTransitionTime += TransitionTime;
    }
}

const C_FLOAT64 & CModel::getTransitionTime() {return mTransitionTime;}

CCopasiVectorS < CReaction > & CModel::getReactions()
{
  return mSteps;
}

vector < CReaction * > & CModel::getReactionsX()
{
  return mStepsX;
}

void CModel::lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  unsigned C_INT32 i,j;
    
  setConcentrations(y);
    
  // Calculate ydot = RedStoi * v
  for (i=0; i<(unsigned C_INT32) n; i++)
    {
      ydot[i] = 0.0;
      for (j=0; j<mSteps.size(); j++)
        ydot[i] += mRedStoi[i][j] * *mFluxesX[j];
    }
    
  return;
}

vector < CMetab * > & CModel::getMetabolitesInd(){return mMetabolitesInd;}

vector < CMetab * > & CModel::getMetabolitesX(){return mMetabolitesX;}

C_INT32 CModel::getTotMetab() const
{
  return mMetabolites.size();
}

C_INT32 CModel::getIntMetab() const
{
  return mMetabolitesInd.size() + mMetabolitesDep.size();
}

C_INT32 CModel::getIndMetab() const
{
  return mMetabolitesInd.size();
}

C_INT32 CModel::getDepMetab() const
{
  return mMetabolitesDep.size();
}

C_FLOAT64 * CModel::getInitialNumbers()
{
  C_INT32 i, imax = mMetabolitesInd.size();

  C_FLOAT64 * y = new C_FLOAT64[imax];

  for (i=0; i<imax; i++)
    y[i] = mMetabolitesInd[i]->getInitialNumber();
  
  return y;
}

C_FLOAT64 * CModel::getNumbers()
{
  C_INT32 i, imax = mMetabolitesInd.size();

  C_FLOAT64 * y = new C_FLOAT64[imax];

  for (i=0; i<imax; i++)
    y[i] = mMetabolitesInd[i]->getNumber();
  
  return y;
}

// Added by Yongqun He
/**
 * Get the total steps
 *
*/
C_INT32 CModel::getTotSteps()
{
 return mSteps.size();   //should not return mSteps
}

C_INT32 CModel::getDimension() const
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
CCopasiVectorNS < CCompartment > & CModel::getCompartments()
{
  return mCompartments;
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
C_INT32 CModel::findMetab(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mMetabolites.size(); i++ )
    {
      name = mMetabolites[i]->getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *        Returns the index of the step
 */
C_INT32 CModel::findStep(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mSteps.size(); i++ )
    {
      name = mSteps[i]->getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *        Returns the index of the compartment
 */
C_INT32 CModel::findCompartment(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mCompartments.size(); i++ )
    {
      name = mCompartments[i]->getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *        Returns the index of the Moiety
 */
C_INT32 CModel::findMoiety(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mMoieties.size(); i++ )
    {
      name = mMoieties[i]->getName();
      if( name == Target) return i;
    }

  return -1;
}
void CModel::initializeMetabolites()
{
  unsigned C_INT32 i, j;

  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  for (i = 0; i < mCompartments.size(); i++)
    for (j = 0; j < mCompartments[i]->metabolites().size(); j++)
      mMetabolites.push_back(mCompartments[i]->metabolites()[j]);
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

/**
 *  Get the reverse Matrix of this Model
 */
const TNT::Matrix < C_FLOAT64 >& CModel::getML() const
{
	return mL;
}
