// CDatum
// 
// Derived from Gepasi's CDatum.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes

#include <iostream>
#include <string>

using namespace std ;

#include "CReadConfig.h"
#include "CDatum.h"


CDatum::CDatum()
{
    mTitle = "";
    mType = D_UNDEF;
    mI = "";
    mJ = "";
    mpValue = NULL;
}

CDatum::CDatum(const string& title, int type, const string& i, const string& j,
               double *pval)
{
    mTitle = title;
    mType = type;
    mI = i;
    mJ = j;
    mpValue = pval;
}

// overload assignment operator
CDatum& CDatum::operator=(CDatum &ptRHS)
{
    mTitle = ptRHS.mTitle;
    mType = ptRHS.mType;
    mI = ptRHS.mI;
    mJ = ptRHS.mJ;
    mpValue = ptRHS.mpValue;
    return *this;
}

int CDatum::Save(ostream* pout)
{
    // this really should be changed to something like Load
    // TO BE DONE SOON

    // make sure fp numbers come out in scientific notation
    pout->setf( ios::scientific ); 

    *pout << "Title=" << mTitle << endl;
    *pout << "Type=" << mType << endl;

    // there may be 0 or 1 mI and mJ references
    switch (mType)
    {
        case D_UNDEF:   // Fall through as all have no mI and no mJ
        case D_T:
        case D_RT:
        case D_INTS:
        case D_FEVAL:
        case D_JEVAL:
        case D_SSIZE:
        case D_RTOL:
        case D_ATOL:
        case D_SSRES:
        case D_UFUNC:
        case D_DERIV:
        case D_ENDT:
        case D_POINT:
        case D_EIGMR:
        case D_EIGMI:
        case D_EIGPR:
        case D_EIGNR:
        case D_EIGR:
        case D_EIGI:
        case D_EIGC:
        case D_EIGZ:
        case D_THIER:
        case D_STIFF:   break;
        case D_ICONC:   // Fall through as all have mI but no mJ
        case D_SCONC:
        case D_TCONC:
        case D_SFLUX:
        case D_TFLUX:
        case D_VOL:
        case D_MOIT:
        case D_TT:
        case D_EIGVR:
        case D_EIGVI:   *pout << "I=" << mI << endl;
                        break;
        case D_KIN:     // Fall through as all have mI and mJ
        case D_ELAST:
        case D_CCC:
        case D_FCC:
        case D_EIG:     *pout << "I=" << mI << endl;
                        *pout << "J=" << mJ << endl;
                        break;
        default:        mFail = 1; // we should never get here!
    }
    
    // mpValue is not output as it is set at a different stage

    return mFail;
}


int CDatum::Load(CReadConfig* pconfigbuffer)
{
    mFail = pconfigbuffer->GetVariable((string) "Title", 
                                       (string) "string",
                                       (void *) &mTitle);
    if (mFail) return mFail;

    mFail = pconfigbuffer->GetVariable((string) "Type", 
                                       (string) "int",
                                       (void *) &mType);
    if (mFail) return mFail;

    // some types need more input... (mI or mJ)
    switch (mType)
    {
        case D_UNDEF:   // Fall through as all have no mI and no mJ
        case D_T:
        case D_RT:
        case D_INTS:
        case D_FEVAL:
        case D_JEVAL:
        case D_SSIZE:
        case D_RTOL:
        case D_ATOL:
        case D_SSRES:
        case D_UFUNC:
        case D_DERIV:
        case D_ENDT:
        case D_POINT:
        case D_EIGMR:
        case D_EIGMI:
        case D_EIGPR:
        case D_EIGNR:
        case D_EIGR:
        case D_EIGI:
        case D_EIGC:
        case D_EIGZ:
        case D_THIER:
        case D_STIFF:   break;
        case D_ICONC:   // Fall through as all have mI but no mJ
        case D_SCONC:
        case D_TCONC:
        case D_SFLUX:
        case D_TFLUX:
        case D_VOL:
        case D_MOIT:
        case D_TT:
        case D_EIGVR:
        case D_EIGVI:   mFail = pconfigbuffer->GetVariable((string) "I", 
                                                           (string) "string",
                                                           (void *) &mI);
                        if (mFail) return mFail;
                        break;
        case D_KIN:     // Fall through as all have mI and mJ
        case D_ELAST:
        case D_CCC:
        case D_FCC:
        case D_EIG:     mFail = pconfigbuffer->GetVariable((string) "I", 
                                                           (string) "int",
                                                           (void *) &mI);
                        if (mFail) return mFail;
                        mFail = pconfigbuffer->GetVariable((string) "J", 
                                                           (string) "string",
                                                           (void *) &mJ);
                        if (mFail) return mFail;
                        break;
        default:        mFail = 1; // we should never get here!
    }

    return mFail;
}

void CDatum::SetValue(double* pvalue)
{
    mpValue = pvalue;
}

double CDatum::GetValue()
{
    return *mpValue;
}

void CDatum::SetI(const string& str)
{
    mI = str;
}

string CDatum::GetI()
{
    return mI;
}

void CDatum::SetJ(const string& str)
{
    mJ = str;
}

string CDatum::GetJ()
{
    return mJ;
}

void CDatum::SetType(int type)
{
    mType = type;
}

int CDatum::GetType()
{
    return mType;
}

void CDatum::SetTitle(const string& str)
{
    mTitle = str;
}

string CDatum::GetTitle()
{
    return mTitle;
}
