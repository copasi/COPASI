/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVersion.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/20 13:20:18 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CVersion
 *
 * (C) Pedro Mendes 2001
 */

#include "copasi.h"
#include "CVersion.h"
#include "utility.h"

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
#ifdef COPASI_DEBUG
  mVersion = StringPrint("%d.%d (Debug %d++)", mMajor, mMinor, mDevel);
#else
  mVersion = StringPrint("%d.%d (Build %d)", mMajor, mMinor, mDevel);
#endif
}
