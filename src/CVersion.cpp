/**
 * CVersion
 * 
 * (C) Pedro Mendes 2001
 */

#include "CVersion.h"
#include "utilities.h"


CVersion::CVersion()
{
    mMajor = 0L;
    mMinor = 0L;
    mDevel = 101L;
    SetString();
}

CVersion::~CVersion()
{
 /* get out of here!*/
}

void CVersion::SetVersion(C_INT32 major, C_INT32 minor, C_INT32 devel)
{
    mMajor = major;
    mMinor = minor;
    mDevel = devel;
    SetString();
}

C_INT32 CVersion::GetVersionMajor()
{
    return mMajor;
}

C_INT32 CVersion::GetVersionMinor()
{
    return mMinor;
}

C_INT32 CVersion::GetVersionDevel()
{
    return mDevel;
}

const string & CVersion::GetVersion()
{
    return mVersion;
}


void CVersion::SetString()
{
 /* if it is a development version, set a string with 3 numbers */
 if (mDevel<300L)
    mVersion = StringPrint("%d.%d.%d", mMajor, 
                           mMinor, mDevel);
 /* otherwise just major and minor */
 else
    mVersion = StringPrint("%d.%d", mMajor, 
                           mMinor);
}

