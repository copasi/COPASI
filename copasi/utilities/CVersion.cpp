/**
 * CVersion
 * 
 * (C) Pedro Mendes 2001
 */

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CVersion.h"
#include "utilities.h"

CVersion::CVersion()
{
  mMajor = 0L;
  mMinor = 0L;
  mDevel = 101L;
  setString();
}

CVersion::~CVersion()
{
  /* get out of here!*/
}

void CVersion::setVersion(C_INT32 major, C_INT32 minor, C_INT32 devel)
{
  mMajor = major;
  mMinor = minor;
  mDevel = devel;
  setString();
}

C_INT32 CVersion::getVersionMajor() const
{
  return mMajor;
}

C_INT32 CVersion::getVersionMinor() const
{
  return mMinor;
}

C_INT32 CVersion::getVersionDevel() const
{
  return mDevel;
}

const std::string & CVersion::getVersion() const
{
  return mVersion;
}

void CVersion::setString()
{
  /* if it is a development version, set a string with 3 numbers */
  if (mDevel < 300L)
    mVersion = StringPrint("%d.%d.%d", mMajor, mMinor, mDevel);
  /* otherwise just major and minor */
  else
    mVersion = StringPrint("%d.%d", mMajor, mMinor);
}
