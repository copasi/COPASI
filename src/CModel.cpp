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

    Init();
}

void CModel::Init()
{
    if ( !mCompartments ) mCompartments = new CCopasiVector < CCompartment >;
    if ( !mSteps )        mSteps        = new CCopasiVector < CStep >;
    if ( !mMoieties )     mMoieties     = new CCopasiVector < CMoiety >;
}

CModel::~CModel()
{
    Delete();
}

void CModel::Delete()
{
    if ( mCompartments ) 
    {
        mCompartments->Delete();
        mCompartments = NULL;
    }
    
    if ( mSteps )
    {
        mSteps->Delete();
        mSteps = NULL;
    }

    if ( mMoieties )
    {
        mMoieties->Delete();
        mMoieties = NULL;
    }
}

C_INT32 CModel::Load(CReadConfig & configBuffer)
{
    C_INT32 Size = 0;
    C_INT32 Fail = 0;
    C_INT32 i;

    Init();
    
    // For old Versions we need must read the list of Metabolites beforehand
    if (configBuffer.GetVersion() < "4")
    {
        if (Fail = configBuffer.GetVariable("TotalMetabolites", "C_INT32", 
                                            &Size, CReadConfig::LOOP))
            return Fail;
        
        if (Fail = Copasi.OldMetabolites.Load(configBuffer, Size))
            return Fail;
    }

    if (Fail = configBuffer.GetVariable("Title", "string", &mTitle,
                                        CReadConfig::LOOP))
        return Fail;

    if (Fail = configBuffer.GetVariable("Comments", "multiline", &mComments,
                                        CReadConfig::SEARCH))
        return Fail;
 
    if (Fail = configBuffer.GetVariable("TotalCompartments", "C_INT32", &Size,
                                        CReadConfig::LOOP))
        return Fail;
 
    if (Fail = mCompartments->Load(configBuffer, Size)) return Fail;
    
    if (configBuffer.GetVersion() < "4")
    {
        // Create the correct compartment / metabolite relationships
        CMetab Metabolite;
        for (i = 0; i < Copasi.OldMetabolites.Size(); i++)
        {
            Metabolite = Copasi.OldMetabolites[i];
            
            (*mCompartments)[Copasi.OldMetabolites[i].GetIndex()].
                AddMetabolite(Metabolite);
        }
    }

    // Create a vector of pointers to all metabolites.
    // Note, the metabolites physically exist in the compartments.
    for (i = 0; i < mCompartments->Size(); i++)
        for (C_INT32 j = 0; j < (*mCompartments)[i].Metabolites().Size(); j++)
            mMetabolites.push_back(&(*mCompartments)[i].Metabolites()[j]);


    if (Fail = Copasi.FunctionDB.Load(configBuffer)) return Fail;

    if (Fail = configBuffer.GetVariable("TotalSteps", "C_INT32", &Size,
                                        CReadConfig::LOOP))
        return Fail;
    
    if (Fail = mSteps->Load(configBuffer, Size)) return Fail;
    
    // We must postprocess the steps for old file versions
    if (configBuffer.GetVersion() < "4")
        for (i = 0; i < mSteps->Size(); i++)
            (*mSteps)[i].Old2New(mMetabolites);
            
    for (i = 0; i < mSteps->Size(); i++)
        (*mSteps)[i].Compile(mCompartments);

    return Fail;
}

C_INT32 CModel::Save(CWriteConfig & configBuffer)
{
    C_INT32 Size;
    C_INT32 Fail = 0;
    
    if (Fail = configBuffer.SetVariable("Title", "string", &mTitle))
        return Fail;

    if (Fail = configBuffer.SetVariable("Comments", "multiline", &mComments))
        return Fail;
 
    Size = mCompartments->Size();
    if (Fail = configBuffer.SetVariable("TotalCompartments", "C_INT32", &Size))
        return Fail;
 
    if (Fail = mCompartments->Save(configBuffer)) return Fail;
    
    if (Fail = Copasi.FunctionDB.Save(configBuffer)) return Fail;

    Size = mSteps->Size();
    if (Fail = configBuffer.SetVariable("TotalSteps", "C_INT32", &Size))
        return Fail;
    
    if (Fail = mSteps->Save(configBuffer)) return Fail;

    return Fail;
}

void CModel::BuildStoi()
{
    vector < CStep::ELEMENT > Structure;
    C_INT32 i,j,k;
    
    mStoi.newsize(mMetabolites.size(), mSteps->Size());
    
    for (i=0; i<mSteps->Size(); i++)
    {
        Structure = (*mSteps)[i].GetChemStructure();
        
        for (j=0; j<mMetabolites.size(); j++)
        {
            for (k=0; k<Structure.size(); k++)
                if (Structure[k].mName == mMetabolites[j]->GetName()) break;

            if (k<Structure.size())
                mStoi[j][i] = Structure[k].mValue;
            else
                mStoi[j][i] = 0.0;
        }
    }

    return;
}

void CModel::LUDecomposition()
{
    C_INT32 i;
    
    TNT::Vector < TNT::Subscript > rowLU(mStoi.num_rows());
    TNT::Vector < TNT::Subscript > colLU(mStoi.num_cols());
    
    TNT::LUX_factor(mStoi, rowLU, colLU);

    mMetabolitesX = mMetabolites;
    
    mStepsX.resize(mSteps->Size());
    for (i=0; i<mSteps->Size(); i++)
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

void CModel::SetMetabolitesStatus()
{
    C_INT32 i,j,k;
    C_FLOAT64 Sum;
    
    for (i=0; i<min(mStoi.num_rows(), mStoi.num_cols()); i++)
    {
        if (mStoi[i][i] == 0.0) break;
        mMetabolitesX[i]->SetStatus(METAB_VARIABLE);
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
        mMetabolitesX[j]->SetStatus(METAB_DEPENDENT);
    }
    mMetabolitesDep.clear();
    mMetabolitesDep.insert(0,&mMetabolitesX[i],&mMetabolitesX[j]);

    for (k=j; k<mStoi.num_rows(); k++)
        mMetabolitesX[k]->SetStatus(METAB_FIXED);

    return;
}

void CModel::BuildRedStoi()
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
    cout << mRedStoi;
    
    return;
}

void CModel::BuildConsRel()
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

void CModel::BuildMoieties()
{
    C_INT32 i,j;
    CMoiety Moiety;
    
    mMoieties->Delete();

    for (i=mMetabolitesDep.size();
         i<mMetabolitesDep.size() + mMetabolitesInd.size(); i++)
    {
        Moiety.Delete();
    
        Moiety.SetName(mMetabolitesX[i]->GetName());
        Moiety.Add(1.0, mMetabolitesX[i]);
        
        for (j=0; j<mConsRel.num_cols(); j++)
        {
            if (mConsRel[i][j] != 0.0)
                Moiety.Add(mConsRel[i][j], mMetabolitesX[j]);
        }
        Moiety.SetInitialValue();
        
        mMoieties->Add(Moiety);
    }
    
    return;
}

void CModel::LSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot)
{
    C_INT32 i,j;
    C_FLOAT64 v[mSteps->Size()];
    
    cout << mTitle << endl;

    // Set the concentration of the independent metabolites
    for (i=0; i<n; i++)
        mMetabolitesInd[i]->
            SetConcentration(y[i] *
                             mMetabolitesInd[i]->GetCompartment()->GetVolume());
    
    // Set the concentration of the dependent metabolites
    for (i=0; i<mMetabolitesDep.size(); i++)
        mMetabolitesDep[i]->
            SetConcentration((*mMoieties)[i].DependentNumber() *
                             mMetabolitesDep[i]->GetCompartment()->GetVolume());

    // Calculate the velocity vector depending on the step kinetics
    for (i=0; i<mSteps->Size(); i++)
        v[i] = (*mSteps)[i].Calculate();

    // Calculate ydot = RedStoi * v
    for (i=0; i<n; i++)
    {
        ydot[j] = 0.0;
        for (j=0; j<mSteps->Size(); j++)
            ydot[i] += mRedStoi[i][j] * v[j];
    }
    
    return;
}

vector < CMetab * > & CModel::GetMetabolitesInd(){return mMetabolitesInd;}
