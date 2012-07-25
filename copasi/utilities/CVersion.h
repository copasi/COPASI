// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
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

/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVersion.h,v $
  $Revision: 1.9 $
  $Name:  $
  $Author: shoops $
  $Date: 2012/05/04 15:06:20 $
  End CVS Header */

/**
 * CVersion
 *
 * (C) Pedro Mendes 2001
 */

#ifndef COPASI_CVersion
#define COPASI_CVersion

#include <string>
#include "copasi.h"

class CVersion
{
  // Attributes

private:
  /**
   *  Major version number.
   *  (4 for first Copasi release)
   */
  C_INT32 mMajor;

  /**
   *  Minor version number.
   *  (changes with releases that are mostly bugfixes)
   */
  C_INT32 mMinor;

  /**
   *  Develpment stage version.
   *  Alpha versions are numbered 101 -> 199
   *  Beta versions are numbered 201 -> 299
   *  Release versions are always 300
   */
  C_INT32 mDevel;

  /**
   *  Comment appendended to the version string, e.g. RC 1
   */
  std::string mComment;

  /**
   *  Version string.
   *  (printable version number in the form "4.01 beta 2")
   */
  std::string mVersion;

  // Operations

  /**
   * Constructor with four arguments.
   */
  CVersion(C_INT32 major, C_INT32 minor, C_INT32 devel, const std::string& comment);

public:
  /**
   *  Default consructor.
   *  This creates a version object without any version info.
   */
  CVersion();

  /**
   *  Destructor.
   */
  ~CVersion();

  /**
   *  Returns the major version number.
   *  @return mMajor
   *  @see mMajor
   */
  C_INT32 getVersionMajor() const;

  /**
   *  Returns the minor version number.
   *  @return mMinor
   *  @see mMinor
   */
  C_INT32 getVersionMinor() const;

  /**
   *  Returns the development version number.
   *  @return mDevel
   *  @see mDevel
   */
  C_INT32 getVersionDevel() const;

  /**
   *  Returns a string with the full version number.
   *  @return mVersion
   *  @see mVersion
   */
  const std::string & getVersion() const;

  /**
   *  Sets a version number
   *  @param const C_INT32 & major
   *  @param const C_INT32 & minor
   *  @param const C_INT32 & devel
   *  @param const std::string & comment
   */
  void setVersion(const C_INT32 & major,
                  const C_INT32 & minor,
                  const C_INT32 & devel,
                  const std::string & comment);

  /**
   * Compare Versions
   */
  bool operator < (const CVersion & rhs) const;

private:
  /**
   *  Creates the version string.
   */
  void setString();

public:
  static const CVersion VERSION;
};

#endif // COPASI_CVersion
