// model.cpp : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CModel
#include <string>
#include <vector>

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CModel.h"
#include "CCompartment.h"
#include "tnt/luX.h"

CModel::CModel()
{
  mCompartments = NULL;
  mSteps        = NULL;
  mMoieties     = NULL;

  initialize();
}

void CModel::initialize()
{
  if ( !mCompartments ) mCompartments = new CCopasiVector < CCompartment >;
  if ( !mSteps )        mSteps        = new CCopasiVector < CReaction >;
  if ( !mMoieties )     mMoieties     = new CCopasiVector < CMoiety >;
}

CModel::~CModel()
{
  cleanup();
}

void CModel::cleanup()
{
  if ( mCompartments ) 
    {
      mCompartments->cleanup();
      mCompartments = NULL;
    }
    
  if ( mSteps )
    {
      mSteps->cleanup();
      mSteps = NULL;
    }

  if ( mMoieties )
    {
      mMoieties->cleanup();
      mMoieties = NULL;
    }
}

C_INT32 CModel::load(CReadConfig & configBuffer)
{
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
  unsigned C_INT32 i;

  initialize();
    
  // For old Versions we need must read the list of Metabolites beforehand
  if (configBuffer.getVersion() < "4")
    {
      if ((Fail = configBuffer.getVariable("TotalMetabolites", "C_INT32", 
					   &Size, CReadConfig::LOOP)))
	return Fail;
        
      if ((Fail = Copasi.OldMetabolites.load(configBuffer, Size)))
	return Fail;
    }

  if ((Fail = configBuffer.getVariable("Title", "string", &mTitle,
				       CReadConfig::LOOP)))
    return Fail;

  if ((Fail = configBuffer.getVariable("Comments", "multiline", &mComments,
				       CReadConfig::SEARCH)))
    return Fail;
 
  if ((Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
				       CReadConfig::LOOP)))
    return Fail;
 
  if ((Fail = mCompartments->load(configBuffer, Size))) return Fail;
    
  if (configBuffer.getVersion() < "4")
    {
      // Create the correct compartment / metabolite relationships
      CMetab Metabolite;
      for (i = 0; i < Copasi.OldMetabolites.size(); i++)
        {
	  Metabolite = Copasi.OldMetabolites[i];
            
	  (*mCompartments)[Copasi.OldMetabolites[i].getIndex()].
	    addMetabolite(Metabolite);
        }
    }

  // Create a vector of pointers to all metabolites.
  // Note, the metabolites physically exist in the compartments.
  for (i = 0; i < mCompartments->size(); i++)
    for (unsigned C_INT32 j = 0;
	 j < (*mCompartments)[i].metabolites().size(); j++)
      mMetabolites.push_back(&(*mCompartments)[i].metabolites()[j]);


  if ((Fail = Copasi.FunctionDB.load(configBuffer))) return Fail;

  if ((Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
				       CReadConfig::LOOP)))
    return Fail;
    
  if ((Fail = mSteps->load(configBuffer, Size))) return Fail;
    
  // We must postprocess the steps for old file versions
  if (configBuffer.getVersion() < "4")
    for (i = 0; i < mSteps->size(); i++)
      (*mSteps)[i].old2New(mMetabolites);
            
  for (i = 0; i < mSteps->size(); i++)
    (*mSteps)[i].compile(mCompartments);

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
 
  Size = mCompartments->size();
  if ((Fail = configBuffer.setVariable("TotalCompartments", "C_INT32", &Size)))
    return Fail;
 
  if ((Fail = mCompartments->save(configBuffer))) return Fail;
    
  if ((Fail = Copasi.FunctionDB.save(configBuffer))) return Fail;

  Size = mSteps->size();
  if ((Fail = configBuffer.setVariable("TotalSteps", "C_INT32", &Size)))
    return Fail;
    
  if ((Fail = mSteps->save(configBuffer))) return Fail;

  return Fail;
}

void CModel::buildStoi()
{
  vector < CReaction::ELEMENT > Structure;
  unsigned C_INT32 i,j,k;
    
  mStoi.newsize(mMetabolites.size(), mSteps->size());
    
  for (i=0; i<mSteps->size(); i++)
    {
      Structure = (*mSteps)[i].getChemStructure();
        
      for (j=0; j<mMetabolites.size(); j++)
        {
	  for (k=0; k<Structure.size(); k++)
	    if (Structure[k].mName == mMetabolites[j]->getName()) break;

	  if (k<Structure.size())
	    mStoi[j][i] = Structure[k].mValue;
	  else
	    mStoi[j][i] = 0.0;
        }
    }
  cout << mStoi << endl;
    
  return;
}

void CModel::lUDecomposition()
{
  unsigned C_INT32 i;
    
  TNT::Vector < unsigned C_INT32 > rowLU(mStoi.num_rows());
  TNT::Vector < unsigned C_INT32 > colLU(mStoi.num_cols());
    
  TNT::LUX_factor(mStoi, rowLU, colLU);

  mMetabolitesX = mMetabolites;
    
  mStepsX.resize(mSteps->size());
  for (i=0; i<mSteps->size(); i++)
    mStepsX[i] = &(*mSteps)[i];

  // permutate Metabolites and Steps to match rearangements done during
  // LU decomposition

  CMetab *pMetab;
  for (i = 0; i < mMetabolitesX.size(); i++) 
    {
      if (rowLU[i] - 1 > i)
        {
	  pMetab = mMetabolitesX[i];
	  mMetabolitesX[i] = mMetabolitesX[rowLU[i]-1];
	  mMetabolitesX[rowLU[i]-1] = pMetab;
        }
    }
    
  CReaction *pStep;
  for (i = mStepsX.size(); 0 < i--; ) 
    {
      if (colLU[i]-1 < i)
        {
	  pStep = mStepsX[i];
	  mStepsX[i] = mStepsX[colLU[i]-1];
	  mStepsX[colLU[i]-1] = pStep;
        }
    }

  return;
}

void CModel::setMetabolitesStatus()
{
  C_INT32 i,j,k;
  C_FLOAT64 Sum;
    
  // for (i=0; i<min(mStoi.num_rows(), mStoi.num_cols()); i++)
  // for compiler
  C_INT32 imax = (mStoi.num_rows() < mStoi.num_cols()) ? mStoi.num_cols() : mStoi.num_rows();
  for (i=0; i<imax; i++)
    {
      if (mStoi[i][i] == 0.0) break;
      mMetabolitesX[i]->setStatus(METAB_VARIABLE);
    }
  mMetabolitesInd.clear();
  mMetabolitesInd.insert(0,&mMetabolitesX[0],&mMetabolitesX[i]);
  mStepsInd.insert(0,&mStepsX[0],&mStepsX[i]);
    
  for (j=i; j<mStoi.num_rows(); j++)
    {
      Sum = 0.0;
        
      for (k=0; k<mStoi.num_cols(); k++)
	Sum += fabs(mStoi[j][k]);
      if (Sum == 0.0) break;
      mMetabolitesX[j]->setStatus(METAB_DEPENDENT);
    }
  mMetabolitesDep.clear();
  mMetabolitesDep.insert(0,&mMetabolitesX[i],&mMetabolitesX[j]);

  for (k=j; k<mStoi.num_rows(); k++)
    mMetabolitesX[k]->setStatus(METAB_FIXED);

  return;
}

void CModel::buildRedStoi()
{
  C_INT32 i,j,k;
  C_FLOAT64 Sum;
  C_INT32 kmax;		// wei for compiler

  mRedStoi.newsize(mMetabolitesInd.size(),mStepsX.size());
    
  for (i=0; i<mRedStoi.num_rows(); i++)
    for (j=0; j<mRedStoi.num_cols(); j++)
      {
	Sum = 0.0;
	//for (k=0; k<min(i,j+1); k++) for compiler
	kmax = (i < j+1) ? j+1 : i;
	for (k=0; k<kmax; k++)
	  Sum += mStoi[i][k] * mStoi[k][j];
	if (i<=j) Sum += mStoi[i][j];
	mRedStoi[i][j] = Sum;
      }
  cout << mRedStoi << endl;
    
  return;
}

void CModel::buildConsRel()
{
  // Since we do not use L anymore we could use L to store ConsRel !!!
  mConsRel.newsize(mMetabolites.size(), mMetabolitesInd.size());
    
  C_INT32 i,j;

  C_INT32 imax = (mConsRel.num_rows() < mConsRel.num_cols()) ? 
    mConsRel.num_cols() : mConsRel.num_rows();
    
  // wei for compiler for (i=0; i<min(mConsRel.num_rows(), mConsRel.num_cols()); i++)
  for (i=0; i<imax; i++)
    mConsRel[i+1][i] = mStoi[i+1][i];
    
  for (j=0; j<mConsRel.num_cols(); j++)
    for (i=j+2; i<mConsRel.num_rows(); i++)
      mConsRel[i][j] = mStoi[i][j] + mStoi[i][i-1] * mConsRel[i-1][j];

  return;
}

void CModel::buildMoieties()
{
  unsigned C_INT32 i;
  C_INT32 j;
  CMoiety Moiety;
    
  mMoieties->cleanup();

  for (i=mMetabolitesDep.size();
       i<mMetabolitesDep.size() + mMetabolitesInd.size(); i++)
    {
      Moiety.cleanup();
    
      Moiety.setName(mMetabolitesX[i]->getName());
      Moiety.add(1.0, mMetabolitesX[i]);
        
      for (j=0; j<mConsRel.num_cols(); j++)
        {
	  if (mConsRel[i][j] != 0.0)
	    Moiety.add(mConsRel[i][j], mMetabolitesX[j]);
        }
      Moiety.setInitialValue();
        
      mMoieties->add(Moiety);
    }
    
  return;
}

void CModel::setConcentrations(const C_FLOAT64 * y)
{
  unsigned C_INT32 i;

  // Set the concentration of the independent metabolites
  for (i=0; i < mMetabolitesInd.size(); i++)
    mMetabolitesInd[i]->setNumber(y[i]);
    
  // Set the concentration of the dependent metabolites
  for (i=0; i<mMetabolitesDep.size(); i++)
    mMetabolitesDep[i]->setNumber((*mMoieties)[i].dependentNumber());

  return;
}

CCopasiVector<CReaction> & CModel::getReactions()
{
  return *mSteps;
}

void CModel::lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot)
{
  unsigned C_INT32 i,j;
  //FIXME: This should be a member
  C_FLOAT64 * v = new C_FLOAT64[mSteps->size()];
    
  cout << mTitle << endl;

  setConcentrations(y);
    
  // Calculate the velocity vector depending on the step kinetics
  for (i=0; i<mSteps->size(); i++)
    v[i] = (*mSteps)[i].calculate();

  // Calculate ydot = RedStoi * v
  for (i=0; i<(unsigned C_INT32) n; i++)
    {
      ydot[i] = 0.0;
      for (j=0; j<mSteps->size(); j++)
	ydot[i] += mRedStoi[i][j] * v[j];
    }
    
  delete [] v;
    
  return;
}

vector < CMetab * > & CModel::getMetabolitesInd(){return mMetabolitesInd;}

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


// Added by Yongqun He
/**
 * Get the total steps
 *
*/
//C_INT32 CModel::getTotSteps()
//{
// return mSteps;   //should not return mSteps
//}

C_INT32 CModel::getDimension() const
{
  return mMetabolitesInd.size();
}

/**
 *	Return the comments of this model	Wei Sun 
 */
string CModel::getComments() const
{
  return mComments;
}


/**
 *	Return the title of this model
 *	@return string
 */
string CModel::getTitle() const
{
  return mTitle;
}

/**
 *	Return the comments of this model
 *	@return CCopasiVector < CCompartment > *
 */
CCopasiVector < CCompartment > * CModel::getCompartments()
{
  return mCompartments;
}

/**
 *	Return the metabolites of this model
 *	@return vector < CMetab * > 
 */
vector < CMetab * > & CModel::getMetabolites()
{
  return mMetabolites;
}

/**
 *  Get the Reduced Stoichiometry Matrix of this Model
 */
TNT::Matrix < C_FLOAT64 >& CModel::getRedStoi()
{
  return mRedStoi;
}

/**
 *	Return the mMoieties of this model	
 *	@return CCopasiVector < CMoiety > * 
 */
CCopasiVector < CMoiety > * CModel::getMoieties()
{
  return mMoieties;
}

/**
 *	Returns the index of the metab
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
 *	Returns the index of the step
 */
C_INT32 CModel::findStep(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mSteps->size(); i++ )
    {
      name = (*mSteps)[i].getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *	Returns the index of the compartment
 */
C_INT32 CModel::findCompartment(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mCompartments->size(); i++ )
    {
      name = (*mCompartments)[i].getName();
      if( name == Target) return i;
    }

  return -1;
}

/**
 *	Returns the index of the Moiety
 */
C_INT32 CModel::findMoiety(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mMoieties->size(); i++ )
    {
      name = (*mMoieties)[i].getName();
      if( name == Target) return i;
    }

  return -1;
}



