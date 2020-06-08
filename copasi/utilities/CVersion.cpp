// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
#include "copasi/copasi.h"

#include "CVersion.h"
#include "utility.h"
#include "copasi/CopasiVersion.h"
#include "copasi/core/CVector.h"

// initialize the global version instance
// static
const CVersion CVersion::VERSION(COPASI_VERSION_MAJOR,
                                 COPASI_VERSION_MINOR,
                                 COPASI_VERSION_BUILD,
                                 COPASI_VERSION_MODIFIED,
#ifdef COPASI_DEBUG
                                 "Debug",
#else
                                 COPASI_VERSION_COMMENT,
#endif
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
  int length = sizeof(Compatible) / sizeof(Compatible[0]);
  C_INT32 * pCompatible = Compatible;

  for (int count = 0; count < length && *pCompatible != mBuild; pCompatible++, count++)
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

bool CVersion::operator>(const CVersion& other) const
{
  return (mMajor > other.getVersionMajor() ||
          (mMajor == other.getVersionMajor() && mMinor > other.getVersionMinor()) ||
          (mMajor == other.getVersionMajor() && mMinor == other.getVersionMinor() && mBuild > other.getVersionDevel())
         );
}

bool CVersion::operator<(const CVersion& other) const
{
  return (mMajor < other.getVersionMajor() ||
          (mMajor == other.getVersionMajor() && mMinor < other.getVersionMinor()) ||
          (mMajor == other.getVersionMajor() && mMinor == other.getVersionMinor() && mBuild < other.getVersionDevel())
         );
}

bool CVersion::operator==(const CVersion& other) const
{
  return (mMajor == other.getVersionMajor() && mMinor == other.getVersionMinor() && mBuild == other.getVersionDevel());
}

bool CVersion::operator>=(const CVersion& other) const
{
  return (*this > other) || (*this == other);
}

bool CVersion::operator<=(const CVersion& other) const
{
  return (*this < other) || (*this == other);
}

bool CVersion::operator!=(const CVersion& other) const
{
  return !(*this == other);
}

bool CVersion::mayBeUpdated() const
{
  return (mComment == "stable");
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

const CVersion &  CVersion::setVersion(const std::string & version)
{
  const char * pModified;
  CVector< char > Build(version.length() + 1);
  Build = 0x0;

  CVector< char > Comment(version.length() + 1);
  Comment = 0x0;

  if (3 == sscanf(version.c_str(), "%d.%d (Build %s)", &mMajor, &mMinor, Build.array()))
    {
      mComment = "stable";
      mBuild = strToInt(Build.array(), &pModified);
      mSourcesModified = (*pModified == '+');
    }
  else if (4 == sscanf(version.c_str(), "%d.%d.%s (%s)", &mMajor, &mMinor, Build.array(), Comment.array()))
    {
      char c = Comment[strlen(Comment.array())];

      if (c == ')')
        Comment[strlen(Comment.array()) - 1] = 0x0;

      mComment = Comment.array();
      mBuild = strToInt(Build.array(), &pModified);
      mSourcesModified = (*pModified == '+');
    }
  else
    {
      mMajor = 0;
      mMinor = 0;
      mBuild = 0;
      mSourcesModified = false;
      mComment = "";
    }

  setString();

  return *this;
}
