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
    short mReversible;

    class CBaseCallParameter
    {
        friend class CBaseFunction;
//        friend class CKinFunction;
        // Attributes
    public:
        /**
         *  The valid types of a parameter.
         */
        enum Type
        {
            DOUBLE = 0,
            VECTOR_DOUBLE,
            LONG,
            VECTOR_LONG
        };
        
    private:
        /**
         *  The type of the parameter.
         */
        long mType;

        /**
         *  The count of objects for parameters of type VECTOR_xxx else
         *  this is meaningless.
         *  A value of 0 (zero) means an arbitrary count.
         */
        long mCount;

        /**
         *  The valid identifier types
         */
        vector < char > * mIdentifierTypes;

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
        ~CBaseCallParameter();

        /**
         *
         */
        void SetType(enum Type type);
        
        /**
         *
         */
        void SetCount(long count);

        /**
         *  Retrieves the type of the the call parameter
         *  @return enum Type
         */
        long GetType();

        /**
         *  Retrieves the type of the function
         *  @return long Count
         */
        long GetCount();

        /**
         *  Retrieves the valis identifier types
         */
        vector < char > IdentifierTypes();

        /**
         *  Retrieves the number of identifiers of a specific type
         *  @param char identifierType Default = 0 (all identifiers)
         *  @return long
         */
        virtual long NoIdentifiers(char identifierType = 0);
            
        /**
         *  Retrieves the vector of identifiers of a specific type
         *  @param char identifierType Default = 0 (all identifiers)
         *  @return "vector < char > &"
         */
        virtual vector< CBaseIdentifier * >
        Identifiers(char identifierType = 0);
    };

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
     *  Default destructor
     */
    virtual ~CBaseFunction();

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
     *  @param short reversible
     */
    virtual void SetReversible(short reversible);

    /**
     *  Retrieves the name of the function
     *  @return string
     */
    virtual string GetName();
    
    /**
     *  Retrieves the type of the function
     *  @return enum Type
     */
    virtual long GetType();
    
    /**
     *  Retrieves the description of the function
     *  @return string
     */
    virtual string GetDescription();
    
    /**
     *  Retrieves whether the function is reversible
     *  @return short
     */
    virtual short IsReversible();
    
    /**
     *  Retrieves the vector of allowed identifiers
     *  @return "vector < char > &"
     */
    vector < CBaseCallParameter > & CallParameters();

    /**
     *  Calculates the value of the function
     *  @param "vector < double * >" identifiers
     */
    virtual double CalcValue(vector < double * > identifiers);

    /**
     *  Returns the index of an identifier. The index specifies the position in
     *  the identifier vector of the function call CalcValue.
     *  @param "const string" &name
     *  @return long
     */
    virtual pair < long, long > FindIdentifier(const string & name);
};

#endif // COPASI_CBaseFunction
