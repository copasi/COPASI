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
     *  Version string.
     *  (printable version number in the form "4.01 beta 2")
     */
    string mVersion;

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
    const string & getVersion() const;


    /** 
     *  Sets a version number 
     *  @param major major version number. 
     *  @param minor minor version number. 
     *  @param devel development version number. 
     */
    void setVersion(C_INT32 major, C_INT32 minor, C_INT32 devel);

private:
    /**
     *  Creates the version string.
     */
    void setString();
};

#endif // COPASI_CVersion
