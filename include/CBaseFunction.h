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
#include "CReadConfig.h"
#include "CWriteConfig.h"

/**
 *
 */
class CRange
{
//Attributes
public:
    enum Constants {UNSPECIFIED = -1};
    
// Attributes
private:
    /**
     *
     */
    unsigned C_INT32 mLow;
    
    /**
     *
     */
    unsigned C_INT32 mHigh;

// Operations
public:
    /**
     *
     */
    CRange();
    
    /**
     *
     */
    CRange(unsigned C_INT32 low, unsigned C_INT32 high);

    /**
     *
     */
    ~CRange();

    /**
     *
     */
    void setLow(unsigned C_INT32 low);
    
    /**
     *
     */
    void setHigh(unsigned C_INT32 high);

    /**
     *
     */
    void setRange(unsigned C_INT32 low, unsigned C_INT32 high);

    /**
     *
     */
    unsigned C_INT32 getLow() const;
    
    /**
     *
     */
    unsigned C_INT32 getHigh() const;

    /**
     *
     */
    C_INT16 isRange() const;

private:
    /**
     *
     */
    void checkRange() const;
};

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
    vector < void * > mIdentifiers;

//Operations
public:
    /**
     *
     */
    CCallParameter();

    /**
     *
     */
    ~CCallParameter();

    /**
     *
     */
    void setType(CCallParameter::Type type);

    /**
     *
     */
    CCallParameter::Type getType() const;

    /**
     *
     */
    vector < void * > &identifiers();
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
    CRange mCount;

    /**
     *  The valid identifier types
     */
    vector < C_INT32 > mIdentifierTypes;

    /**
     *  Vector of identifiers of the function
     */
    vector< CBaseIdentifier * > mIdentifiers;
        
    // Operations
public:
    /**
     *
     */
    CBaseCallParameter();
        
    /**
     *
     */
    virtual ~CBaseCallParameter();

    /**
     *  
     */
    virtual void cleanup();

    /**
     *  
     */
    virtual void copy(const CBaseCallParameter &in);
    
    /**
     *
     */
    virtual void setType(enum CCallParameter::Type type);
        
    /**
     *
     */
    virtual void setCount();

    /**
     *
     */
    virtual void setCount(unsigned C_INT32 count);

    /**
     *
     */
    virtual void setCount(unsigned C_INT32 low,
                          unsigned C_INT32 high);

    /**
     *  Retrieves the type of the the call parameter
     *  @return enum Type
     */
    virtual enum CCallParameter::Type getType() const;

    /**
     *  Retrieves the type of the function
     *  @return C_INT32 Count
     */
    virtual unsigned C_INT32 getCountLow() const;

    /**
     *  Retrieves the type of the function
     *  @return C_INT32 Count
     */
    virtual unsigned C_INT32 getCountHigh() const;

    /**
     *  Retrieves the valis identifier types
     */
    virtual vector < C_INT32 > & identifierTypes();

    /**
     *  Retrieves the number of identifiers of a specific type
     *  @param char identifierType Default = 0 (all identifiers)
     *  @return C_INT32
     */
    virtual C_INT32 noIdentifiers(char identifierType = 0);
            
    /**
     *  Retrieves the vector of identifiers
     *  @return "vector < char > &"
     */
    virtual vector < CBaseIdentifier * > & identifiers();

    /**
     *  Retrieves the vector of identifiers of a specific type
     *  @param char identifierType Default = 0 (all identifiers)
     *  @return "vector < char > &"
     */
    virtual vector < CBaseIdentifier * >
        identifiers(char identifierType);
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
        USERDEFINED,
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
    vector < CBaseCallParameter * > mCallParameters;
    
// Operations
public:
    /**
     *  Default constructor
     */
    CBaseFunction();

    /**
     *  Default destructor
     */
    virtual ~CBaseFunction();

    /**
     *  Delete
     */
    virtual void cleanup();

    /**
     *  Copy
     */
    virtual void copy(const CBaseFunction & in);
    
    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    virtual C_INT32 load(CReadConfig & configbuffer,
                         CReadConfig::Mode mode = CReadConfig::SEARCH);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    virtual C_INT32 save(CWriteConfig & configbuffer);

    /**
     *  Set the name of the function
     *  @param "const string" &name
     */
    virtual void setName(const string & name);

    /**
     *  Set the name of the function
     *  @param "CBaseIdentifier::TYPE" &type
     */
    virtual void setType(enum Type type);

    /**
     *  Set the description of the function
     *  @param "const string" &description
     */
    virtual void setDescription(const string & description);

    /**
     *  Set the reversiblity of the function
     *  @param C_INT16 reversible
     */
    virtual void setReversible(C_INT16 reversible);

    /**
     *  Retrieves the name of the function
     *  @return string
     */
    virtual string getName() const;
    
    /**
     *  Retrieves the type of the function
     *  @return enum Type
     */
    virtual C_INT32 getType() const;
    
    /**
     *  Retrieves the description of the function
     *  @return string
     */
    virtual string getDescription() const;
    
    /**
     *  Retrieves whether the function is reversible
     *  @return C_INT16
     */
    virtual C_INT16 isReversible() const;
    
    /**
     *  Retrieves the vector of allowed identifiers
     *  @return "vector < char > &"
     */
    vector < CBaseCallParameter * > & callParameters();

    /**
     *  Calculates the value of the function
     *  @param "vector < C_FLOAT64 * >" identifiers
     */
    virtual C_FLOAT64 
        calcValue(const vector < CCallParameter > & callParameters) const;

    /**
     *  Returns the index of an identifier. The index specifies the position in
     *  the identifier vector of the function call CalcValue.
     *  @param "const string" &name
     *  @return C_INT32
     */
    virtual pair < C_INT32, C_INT32 > findIdentifier(const string & name) const;
};


#endif // COPASI_CBaseFunction
