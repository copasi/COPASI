/**
 * CVersion
 * 
 * (C) Pedro Mendes 2001
 */

#ifndef COPASI_CVersion
#define COPASI_CVersion

#include <string>
#include "Copasi.h"

class CVersion  
{
// Attributes
private:
    /**
     *  Major version number.
     *  (4 for first Copasi release)
     */
    long mMajor;

    /**
     *  Minor version number.
     *  (changes with releases that are mostly bugfixes)
     */
    long mMinor;

    /**
     *  Develpment stage version.
     *  Alpha versions are numbered 101 -> 199
     *  Beta versions are numbered 201 -> 299
     *  Release versions are always 300
     */
    long mDevel;

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
     *  It is of no use, the specified constructor should always be used. 
     */
	CVersion();

    /**
     *  Specified consructor. 
     *  This creates a version object and sets the version numbers 
     *  @param major major version number. 
     *  @param minor minoor version number. 
     *  @param devel development version number. 
     */
	CVersion(long major, long minor, long devel);

    /**
     *  Destructor. 
     */
	~CVersion();

    /**
     *  Returns the major version number.
     *  @return mMajor
     *  @see mMajor  
     */
    long GetVersionMajor();

    /**
     *  Returns the minor version number.
     *  @return mMinor
     *  @see mMinor  
     */
    long GetVersionMinor();

    /**
     *  Returns the development version number.
     *  @return mDevel
     *  @see mDevel  
     */
    long GetVersionDevel();

    /**
     *  Returns a string with the full version number.
     *  @return mVersion
     *  @see mVersion  
     */
    string GetVersion();

private:
    /**
     *  Creates the version string.
     */
    SetString();
};

#endif // COPASI_CVersion
