/**
 *  CCompartmentVector class.
 *  Derived from Gepasi's ccompart.h. (C) Pedro Mendes 1995-2000.
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CCompartmentVector
#define COPASI_CCompartmentVector

#include <vector>

#include "CCompartment.h"

class CCompartmentVector
{
// Attributes
private:
    /**
     *
     */
    vector < CCompartment > mCompartments;
    
// Operations
public:
    /**
     *
     */
    CCompartmentVector();

    /**
     *
     */
    ~CCompartmentVector();

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
    long Add(CCompartment & c);

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
    CCompartment * Get(long index);

    /**
     *
     */
    CCompartment * Get(const string & name);

    /**
     *
     */
    long Size();
};

#endif // COPASI_CCompartmentVector
