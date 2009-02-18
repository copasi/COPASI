// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVersion.cpp,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:56:57 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasiversion.h"

// initialize the gobal version instance
const CVersion CVersion::VERSION(COPASI_VERSION_MAJOR, COPASI_VERSION_MINOR, COPASI_VERSION_BUILD, COPASI_VERSION_COMMENT);

CVersion::CVersion(C_INT32 major, C_INT32 minor, C_INT32 devel, const std::string& comment):
    mMajor(major),
    mMinor(minor),
    mDevel(devel),
    mComment(comment)
{
  setString();
}

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
  mVersion = StringPrint("%d.%d.%d (Debug)", mMajor, mMinor, mDevel);
#else
  if (mComment == "stable")
    mVersion = StringPrint("%d.%d (Build %d)", mMajor, mMinor, mDevel);
  else if (mComment != "")
    mVersion = StringPrint("%d.%d.%d (%s)", mMajor, mMinor, mDevel, mComment.c_str());
  else
    mVersion = StringPrint("%d.%d.%d", mMajor, mMinor, mDevel);
#endif
}
