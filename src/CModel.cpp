// model.cpp : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CModel
#include <string>
#include <vector>

#include "copasi.h"
#include "CGlobals.h"
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
    if ( !mSteps )        mSteps        = new CCopasiVector < CStep >;
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
    C_INT32 i;

    initialize();
    
    // For old Versions we need must read the list of Metabolites beforehand
    if (configBuffer.getVersion() < "4")
    {
        if (Fail = configBuffer.getVariable("TotalMetabolites", "C_INT32", 
                                            &Size, CReadConfig::LOOP))
            return Fail;
        
        if (Fail = Copasi.OldMetabolites.load(configBuffer, Size))
            return Fail;
    }

    if (Fail = configBuffer.getVariable("Title", "string", &mTitle,
                                        CReadConfig::LOOP))
        return Fail;

    if (Fail = configBuffer.getVariable("Comments", "multiline", &mComments,
                                        CReadConfig::SEARCH))
        return Fail;
 
    if (Fail = configBuffer.getVariable("TotalCompartments", "C_INT32", &Size,
                                        CReadConfig::LOOP))
        return Fail;
 
    if (Fail = mCompartments->load(configBuffer, Size)) return Fail;
    
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
        for (C_INT32 j = 0; j < (*mCompartments)[i].metabolites().size(); j++)
            mMetabolites.push_back(&(*mCompartments)[i].metabolites()[j]);


    if (Fail = Copasi.FunctionDB.load(configBuffer)) return Fail;

    if (Fail = configBuffer.getVariable("TotalSteps", "C_INT32", &Size,
                                        CReadConfig::LOOP))
        return Fail;
    
    if (Fail = mSteps->load(configBuffer, Size)) return Fail;
    
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
    
    if (Fail = configBuffer.setVariable("Title", "string", &mTitle))
        return Fail;

    if (Fail = configBuffer.setVariable("Comments", "multiline", &mComments))
        return Fail;
 
    Size = mCompartments->size();
    if (Fail = configBuffer.setVariable("TotalCompartments", "C_INT32", &Size))
        return Fail;
 
    if (Fail = mCompartments->save(configBuffer)) return Fail;
    
    if (Fail = Copasi.FunctionDB.save(configBuffer)) return Fail;

    Size = mSteps->size();
    if (Fail = configBuffer.setVariable("TotalSteps", "C_INT32", &Size))
        return Fail;
    
    if (Fail = mSteps->save(configBuffer)) return Fail;

    return Fail;
}

void CModel::buildStoi()
{
    vector < CStep::ELEMENT > Structure;
    C_INT32 i,j,k;
    
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
    C_INT32 i;
    
    TNT::Vector < TNT::Subscript > rowLU(mStoi.num_rows());
    TNT::Vector < TNT::Subscript > colLU(mStoi.num_cols());
    
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
    
    CStep *pStep;
    for (i = mStepsX.size() - 1; 0 <= i; i--) 
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
    
    for (i=0; i<min(mStoi.num_rows(), mStoi.num_cols()); i++)
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

    mRedStoi.newsize(mMetabolitesInd.size(),mStepsX.size());
    
    for (i=0; i<mRedStoi.num_rows(); i++)
        for (j=0; j<mRedStoi.num_cols(); j++)
        {
            Sum = 0.0;
            for (k=0; k<min(i,j+1); k++)
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

    for (i=0; i<min(mConsRel.num_rows(), mConsRel.num_cols()); i++)
        mConsRel[i+1][i] = mStoi[i+1][i];
    
    for (j=0; j<mConsRel.num_cols(); j++)
        for (i=j+2; i<mConsRel.num_rows(); i++)
            mConsRel[i][j] = mStoi[i][j] + mStoi[i][i-1] * mConsRel[i-1][j];

    return;
}

void CModel::buildMoieties()
{
    C_INT32 i,j;
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
    C_INT32 i,j;

    // Set the concentration of the independent metabolites
    for (i=0; i < mMetabolitesInd.size(); i++)
        mMetabolitesInd[i]->
            setConcentration(y[i] *
                             mMetabolitesInd[i]->getCompartment()->getVolume());
    
    // Set the concentration of the dependent metabolites
    for (i=0; i<mMetabolitesDep.size(); i++)
        mMetabolitesDep[i]->
            setConcentration((*mMoieties)[i].dependentNumber() *
                             mMetabolitesDep[i]->getCompartment()->getVolume());

    return;
}

CCopasiVector<CStep> *CModel::getSteps()
{
    return mSteps;
}

void CModel::lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot)
{
    C_INT32 i,j;
    C_FLOAT64 v[mSteps->size()];
    
    cout << mTitle << endl;

    setConcentrations(y);
    
    // Calculate the velocity vector depending on the step kinetics
    for (i=0; i<mSteps->size(); i++)
        v[i] = (*mSteps)[i].calculate();

    // Calculate ydot = RedStoi * v
    for (i=0; i<n; i++)
    {
        ydot[i] = 0.0;
        for (j=0; j<mSteps->size(); j++)
            ydot[i] += mRedStoi[i][j] * v[j];
    }
    
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




