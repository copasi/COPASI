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

CVersion::SetVersion(long major, long minor, long devel)
{
    mMajor = major;
    mMinor = minor;
    mDevel = devel;
    SetString();
}

long CVersion::GetVersionMajor()
{
    return mMajor;
}

long CVersion::GetVersionMinor()
{
    return mMinor;
}

long CVersion::GetVersionDevel()
{
    return mDevel;
}

string CVersion::GetVersion()
{
    return mVersion;
}


CVersion::SetString()
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

