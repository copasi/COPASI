/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVersion.cpp,v $
   $Revision: 1.9.4.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/19 14:19:39 $
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

CVersion::CVersion():
    mMajor(0),
    mMinor(0),
    mDevel(0),
    mComment("")
{
  setString();
}

CVersion::~CVersion()
{}

void CVersion::setVersion(const C_INT32 & major,
                          const C_INT32 & minor,
                          const C_INT32 & devel,
                          const std::string & comment)
{
  mMajor = major;
  mMinor = minor;
  mDevel = devel;
  mComment = comment;

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
  mVersion = StringPrint("%d.%d (Build %d %s)", mMajor, mMinor, mDevel, mComment.c_str());
#endif
}
