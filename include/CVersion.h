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
    const string & GetVersion();


    /** 
     *  Sets a version number 
     *  @param major major version number. 
     *  @param minor minor version number. 
     *  @param devel development version number. 
     */
    void SetVersion(long major, long minor, long devel);

private:
    /**
     *  Creates the version string.
     */
    void SetString();
};

#endif // COPASI_CVersion


