// CDatum
// 
// Derived from Gepasi's CDatum.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Pedro Mendes
//
// CDatum is not yet finished: because all data are now private, we will need 
// to add a few more methods (perhaps not in this class, though - thus it is
// best to wait until we hit the problem in CGepasiDoc.   PEDRO 1/11/01

#include <iostream>
#include <string>

#include "copasi.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CDatum.h"


CDatum::CDatum()
{
    mTitle = "";
    mType = D_UNDEF;
    mI = "";
    mJ = "";
    mpValue = NULL;
}

CDatum::CDatum(const string& title, C_INT32 type, const string& i, const string& j,
               C_FLOAT64 *pval)
{
    mTitle = title;
    mType = type;
    mI = i;
    mJ = j;
    mpValue = pval;
}

// overload assignment operator
CDatum& CDatum::operator=(const CDatum &RHS)
{
    mTitle = RHS.mTitle;
    mType = RHS.mType;
    mI = RHS.mI;
    mJ = RHS.mJ;
    mpValue = RHS.mpValue;
    return *this;
}

C_INT32 CDatum::save(CWriteConfig &pconfigbuffer)
{
    // this really should be changed to something like Load
    // TO BE DONE SOON

    // make sure fp numbers come out in scientific notation
    mFail = pconfigbuffer.setVariable((string) "Title", 
                                      (string) "string",
                                      (void *) &mTitle);
    if (mFail) return mFail;

    mFail = pconfigbuffer.setVariable((string) "Type", 
                                      (string) "C_INT32",
                                      (void *) &mType);
    if (mFail) return mFail;

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
    case D_EIGVI:
        mFail = pconfigbuffer.setVariable((string) "I", 
                                          (string) "string",
                                          (void *) &mI);
        if (mFail) return mFail;
        break;
    case D_KIN:     // Fall through as all have mI and mJ
    case D_ELAST:
    case D_CCC:
    case D_FCC:
    case D_EIG:
        mFail = pconfigbuffer.setVariable((string) "I", 
                                          (string) "C_INT32",
                                          (void *) &mI);
        if (mFail) return mFail;
        mFail = pconfigbuffer.setVariable((string) "J", 
                                          (string) "string",
                                          (void *) &mJ);
        if (mFail) return mFail;
        break;
    default:        mFail = 1; // we should never get here!
    }
    
    // mpValue is not output as it is set at a different stage

    return mFail;
}


C_INT32 CDatum::load(CReadConfig &pconfigbuffer)
{
    mFail = pconfigbuffer.getVariable((string) "Title", 
                                      (string) "string",
                                      (void *) &mTitle);
    if (mFail) return mFail;

    mFail = pconfigbuffer.getVariable((string) "Type", 
                                      (string) "C_INT32",
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
    case D_EIGVI:   mFail = pconfigbuffer.getVariable((string) "I", 
                                                      (string) "string",
                                                      (void *) &mI);
    if (mFail) return mFail;
    break;
    case D_KIN:     // Fall through as all have mI and mJ
    case D_ELAST:
    case D_CCC:
    case D_FCC:
    case D_EIG:
        mFail = pconfigbuffer.getVariable((string) "I", 
                                          (string) "C_INT32",
                                          (void *) &mI);
        if (mFail) return mFail;
        mFail = pconfigbuffer.getVariable((string) "J", 
                                          (string) "string",
                                          (void *) &mJ);
        if (mFail) return mFail;
        break;
    default:        mFail = 1; // we should never get here!
    }

    return mFail;
}

void CDatum::setValue(C_FLOAT64* pvalue)
{
    mpValue = pvalue;
}

C_FLOAT64 CDatum::getValue()
{
    return *mpValue;
}

void CDatum::setI(const string& str)
{
    mI = str;
}

string CDatum::getI()
{
    return mI;
}

void CDatum::setJ(const string& str)
{
    mJ = str;
}

string CDatum::getJ()
{
    return mJ;
}

void CDatum::setType(C_INT32 type)
{
    mType = type;
}

C_INT32 CDatum::getType()
{
    return mType;
}

void CDatum::setTitle(const string& str)
{
    mTitle = str;
}

string CDatum::getTitle()
{
    return mTitle;
}
