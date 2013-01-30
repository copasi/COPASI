// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
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
#include <sstream>

#include "copasi.h"

#include "CVersion.h"
#include "utility.h"
#include "CopasiVersion.h"

// initialize the global version instance
// static
const CVersion CVersion::VERSION(COPASI_VERSION_MAJOR,
                                 COPASI_VERSION_MINOR,
                                 COPASI_VERSION_BUILD,
                                 COPASI_VERSION_MODIFIED,
                                 COPASI_VERSION_COMMENT,
                                 COPASI_VERSION_CREATOR);

CVersion::CVersion(C_INT32 major,
                   C_INT32 minor,
                   C_INT32 build,
                   const bool & sourcesModified,
                   const std::string & comment,
                   const std::string & creator):
  mMajor(major),
  mMinor(minor),
  mBuild(build),
  mSourcesModified(sourcesModified),
  mComment(comment),
  mCreator(creator),
  mVersion(""),
  mCompatible()
{
  C_INT32 Compatible[] = COPASI_VERSION_COMPATIBILITY;
  C_INT32 * pCompatible = Compatible;

  for (; *pCompatible != mBuild; pCompatible++)
    {
      mCompatible.insert(*pCompatible);
    }

  mCompatible.insert(mBuild);

  setString();
}

CVersion::CVersion():
  mMajor(0),
  mMinor(0),
  mBuild(0),
  mSourcesModified(false),
  mComment(""),
  mCreator(""),
  mVersion(""),
  mCompatible()
{
  setString();
}

CVersion::~CVersion()
{}

bool CVersion::isCompatible(const CVersion & version) const
{
  if (mCompatible.empty())
    {
      if (mMajor > version.mMajor) return false;

      if (mMinor > version.mMinor) return false;

      if (mBuild >= version.mBuild) return false;

      return true;
    }

  if (version.mBuild < *mCompatible.begin()) return true;

  if (mCompatible.find(version.mBuild) != mCompatible.end()) return true;

  return false;
}

void CVersion::setVersion(const C_INT32 & major,
                          const C_INT32 & minor,
                          const C_INT32 & devel,
                          const bool & sourcesModified,
                          const std::string & comment,
                          const std::string & creator)
{
  mMajor = major;
  mMinor = minor;
  mBuild = devel;
  mSourcesModified = sourcesModified;
  mComment = comment;
  mCreator = creator;

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
  return mBuild;
}

const bool & CVersion::isSourceModified() const
{
  return mSourcesModified;
}

const std::string & CVersion::getVersion() const
{
  return mVersion;
}

void CVersion::setString()
{
#ifdef COPASI_DEBUG
  mComment = "Debug";
#endif

  std::stringstream Build;
  Build << mBuild;

  if (mSourcesModified)
    {
      Build << "+";
    }

  if (mComment == "stable")
    mVersion = StringPrint("%d.%d (Build %s)", mMajor, mMinor, Build.str().c_str());
  else if (mComment != "")
    mVersion = StringPrint("%d.%d.%s (%s)", mMajor, mMinor, Build.str().c_str(), mComment.c_str());
  else
    mVersion = StringPrint("%d.%d.%s (Source)", mMajor, mMinor, Build.str().c_str());
}
