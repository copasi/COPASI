/**
 *  CMetab class.
 *  Derived from Gepasi's cmetab.cpp. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CMetabVector
#define COPASI_CMetabVector

#include <vector>

#include "CMetab.h"

class CMetabVector
{
// Attributes
private:
    /**
     *
     */
    vector < CMetab > mMetabs;
    
// Operations
public:
    /**
     *
     */
    CMetabVector();

    /**
     *
     */
    ~CMetabVector();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    long Load(CReadConfig & configbuffer, long index);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    long Save(CWriteConfig & configbuffer);

    /**
     *
     */
    long Add(CMetab & metab);

    /**
     *
     */
    long Delete(long index);

    /**
     *
     */
    long Delete(const string & name);

    /**
     *
     */
    CMetab * Get(long index);

    /**
     *
     */
    CMetab * Get(const string & name);

    /**
     *
     */
    long Size();
};

#endif // COPASI_CMetabVector
