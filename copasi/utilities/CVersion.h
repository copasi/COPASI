/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CVersion.h,v $
   $Revision: 1.6.6.1 $
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

  private:
    /**
     *  Creates the version string.
     */
    void setString();
  };

#endif // COPASI_CVersion
