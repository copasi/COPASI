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

    class CCallParameter
        {
            friend class CBaseFunction;
            friend class CKinFunction;
        // Attributes
        private:
            long mType; // currently we only have double
            long mCount;
            vector < char > mIdentifierTypes;
            /**
             *  Vector of identifiers of the function
             */
            vector< CBaseIdentifier > mIdentifiers;

        // Operations
        public:
            virtual long GetType();
            virtual long GetCount();
            virtual vector < char > IdentifierTypes();
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
    vector < CCallParameter > mCallParameters;
    
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
     *  Retrieves the name of the function
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
    vector < CCallParameter > & CallParameters();

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
    virtual long FindIdentifier(const string & name);
};

#endif // COPASI_CBaseFunction
