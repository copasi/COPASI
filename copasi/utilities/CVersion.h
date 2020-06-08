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

#ifndef COPASI_CVersion
#define COPASI_CVersion

#include <set>

#include <copasi/copasi.h>

class CVersion
{
  // Attributes
private:
  /**
   * Major version number.
   * (4 for first COPASI release)
   */
  C_INT32 mMajor;

  /**
   * Minor version number.
   * (changes with releases that are mostly bug fixes)
   */
  C_INT32 mMinor;

  /**
   * The monotonously increasing build number
   */
  C_INT32 mBuild;

  /**
   * Boolean value indicating whether mBuild is describing the
   * current state of the sources.
   */
  bool mSourcesModified;

  /**
   * Comment appended to the version string
   */
  std::string mComment;

  /**
   * Creator who compiled this version for official unmodified sources
   * it is copasi.org
   */
  std::string mCreator;

  /**
   * Version string.
   */
  std::string mVersion;

  /**
   * The list of compatible builds
   */
  std::set< C_INT32 > mCompatible;

  // Operations

  /**
   * Constructor with four arguments.
   */
  CVersion(C_INT32 major,
           C_INT32 minor,
           C_INT32 build,
           const bool & sourcesModified,
           const std::string & comment,
           const std::string & creator);

public:
  /**
   *  Default constructor.
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
   *  @return mBuild
   *  @see mBuild
   */
  C_INT32 getVersionDevel() const;

  /**
   * Retrieve the whether the source code is modified compared to the official build
   * @return const bool & isSourceModified
   */
  const bool & isSourceModified() const;

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
   *  @param const C_INT32 & build
   *  @param const bool & sourcesModified
   *  @param const std::string & comment
   *  @param const std::string & creator
   */
  void setVersion(const C_INT32 & major,
                  const C_INT32 & minor,
                  const C_INT32 & devel,
                  const bool & sourcesModified,
                  const std::string & comment = "",
                  const std::string & creator = "");

  /**
   * Set a version number
   * @param const std::string & version
   */
  const CVersion & setVersion(const std::string & version);

  /**
   * Compare Versions
   * @param const CVersion & version
   * @return bool isCompatible
   */
  bool isCompatible(const CVersion & version) const;

  bool operator>(const CVersion& other) const;
  bool operator<(const CVersion& other) const;

  bool operator>=(const CVersion& other) const;
  bool operator<=(const CVersion& other) const;

  bool operator==(const CVersion& other) const;
  bool operator!=(const CVersion& other) const;

  bool mayBeUpdated() const;

private:
  /**
   *  Creates the version string.
   */
  void setString();

public:
  static const CVersion VERSION;
};

#endif // COPASI_CVersion
