/**
 * CBaseFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CBaseFunction
#define COPASI_CBaseFunction

#include <string>
#include <vector>

#include "CBaseIdentifier.h"

/**
 *
 */
class CCallParameter
{
//Attributes
public:
    /**
     *  The valid types of a parameter.
     */
    enum Type {VECTOR_DOUBLE = 0, VECTOR_LONG};

// Attributes
private:
    /**
     *
     */
    CCallParameter::Type mType;

    /**
     *
     */
    vector < void * > * mIdentifiers;

//Operations
public:
    /**
     *
     */
    CCallParameter();

    /**
     *
     */
    void Init();

    /**
     *
     */
    ~CCallParameter();

    /**
     *
     */
    void Delete();

    /**
     *
     */
    void SetType(CCallParameter::Type type);

    /**
     *
     */
    CCallParameter::Type GetType();

    /**
     *
     */
    vector < void * > &Identifiers();
};
    
class CBaseCallParameter
{
    friend class CBaseFunction;

// Attributes
public:
        
private:
    /**
     *  The type of the parameter.
     */
    enum CCallParameter::Type mType;

    /**
     *  The count of objects in vector of identifiers VECTOR_xxx else
     *  this is meaningless.
     *  A value of 0 (zero) means an arbitrary count.
     */
    C_INT32 mCount;

    /**
     *  The valid identifier types
     */
    vector < C_INT32 > * mIdentifierTypes;

    /**
     *  Vector of identifiers of the function
     */
    vector< CBaseIdentifier > * mIdentifiers;
        
    // Operations
public:
    /**
     *
     */
    CBaseCallParameter();
        
    /**
     *
     */
    virtual void Init();

    /**
     *
     */
    virtual ~CBaseCallParameter();

    /**
     *
     */
    virtual void Delete();

    /**
     *
     */
    virtual void SetType(enum CCallParameter::Type type);
        
    /**
     *
     */
    virtual void SetCount();

    /**
     *
     */
    virtual void SetCount(C_INT32 count);

    /**
     *  Retrieves the type of the the call parameter
     *  @return enum Type
     */
    virtual enum CCallParameter::Type GetType();

    /**
     *  Retrieves the type of the function
     *  @return C_INT32 Count
     */
    virtual C_INT32 GetCount();

    /**
     *  Retrieves the valis identifier types
     */
    virtual vector < C_INT32 > & IdentifierTypes();

    /**
     *  Retrieves the number of identifiers of a specific type
     *  @param char identifierType Default = 0 (all identifiers)
     *  @return C_INT32
     */
    virtual C_INT32 NoIdentifiers(char identifierType = 0);
            
    /**
     *  Retrieves the vector of identifiers of a specific type
     *  @param char identifierType Default = 0 (all identifiers)
     *  @return "vector < char > &"
     */
    virtual vector< CBaseIdentifier * >
        Identifiers(char identifierType = 0);
};

class CBaseFunction
{
// Attributes
public:
    /**
     *  The valid types of a function
     */
    enum Type
    {
        BASIC = 0,
        USERDIFINED,
        BUILTIN
    };
  
private:
    /**
     *  The type of the function
     */
    Type mType;
 
    /**
     *  The name of the function
     */
    string mName;

    /**
     *  The description of the function
     */
    string mDescription;

    /**
     *  Whether the function is reversible
     */
    C_INT16 mReversible;

    /**
     *  Vector of call parameter specificying their structure
     */
    vector < CBaseCallParameter > * mCallParameters;
    
// Operations
public:
    /**
     *  Default constructor
     */
    CBaseFunction();

    /**
     *
     */
    virtual void Init();

    /**
     *  Default destructor
     */
    virtual ~CBaseFunction();

    /**
     *  Delete
     */
    virtual void Delete();

    /**
     *  Set the name of the function
     *  @param "const string" &name
     */
    virtual void SetName(const string & name);

    /**
     *  Set the name of the function
     *  @param "CBaseIdentifier::TYPE" &type
     */
    virtual void SetType(enum Type type);

    /**
     *  Set the description of the function
     *  @param "const string" &description
     */
    virtual void SetDescription(const string & description);

    /**
     *  Set the reversiblity of the function
     *  @param C_INT16 reversible
     */
    virtual void SetReversible(C_INT16 reversible);

    /**
     *  Retrieves the name of the function
     *  @return string
     */
    virtual string GetName();
    
    /**
     *  Retrieves the type of the function
     *  @return enum Type
     */
    virtual C_INT32 GetType();
    
    /**
     *  Retrieves the description of the function
     *  @return string
     */
    virtual string GetDescription();
    
    /**
     *  Retrieves whether the function is reversible
     *  @return C_INT16
     */
    virtual C_INT16 IsReversible();
    
    /**
     *  Retrieves the vector of allowed identifiers
     *  @return "vector < char > &"
     */
    vector < CBaseCallParameter > & CallParameters();

    /**
     *  Calculates the value of the function
     *  @param "vector < C_FLOAT64 * >" identifiers
     */
    virtual C_FLOAT64 CalcValue(vector < CCallParameter > callParameters);

    /**
     *  Returns the index of an identifier. The index specifies the position in
     *  the identifier vector of the function call CalcValue.
     *  @param "const string" &name
     *  @return C_INT32
     */
    virtual pair < C_INT32, C_INT32 > FindIdentifier(const string & name);
};


#endif // COPASI_CBaseFunction
