/**
 * CBaseIdentifier
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CBaseIdentifier
#define COPASI_CBaseIdentifier

#include <string>

#include "copasi.h"

class CBaseIdentifier 
{
// Attributes
private:
    /**
     *  The name of the identifier
     */
    string mName;

    /**
     *  The Type of the identifier
     */
    char mType;
// Operations
public:
    
    /**
     *  Default constructor
     */
    CBaseIdentifier();
    
    /**
     *  Default destructor
     */
    virtual ~CBaseIdentifier();
    
    /**
     *  Set the name of an identifier.
     *  @param "const string" &name
     */
    virtual void SetName(const string & name);

    /**
     *  Set the type of an identifier.
     *  @param char type
     */
    virtual void SetType(const char type);

    /**
     *  Retrieve the name of an identifier.
     *  @return string
     */
    virtual string GetName() const;

    /**
     *  Retrieve the type of an identifier
     *  @return char
     */
    virtual char GetType() const;
};

#endif // COPASI_CBaseIdentifier
