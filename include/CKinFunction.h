/**
 * CKinFunction
 * 
 * CKinFunction.cpp based on UDKType.cpp from
 * (C) Pedro Mendes 1995-2000
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CKinFunction
#define COPASI_CKinFunction

#include <string>
#include <vector>

#include "copasi.h"
#include "CBaseFunction.h"
#include "CNodeK.h"
#include "CCopasiVector.h"

class CKinIdentifier: public CBaseIdentifier
{
// Attributes
public:
    /*
     *  The nodes which access the same identifier.
     */
    vector < CNodeK * > * mNodes;

// Operations
public:
    /**
     *  Default constructor
     */
    CKinIdentifier();
                    
    /**
     *  Init
     */
    void Init();
            
    /**
     *  Destructor
     */
    ~CKinIdentifier();

    /**
     *  Delete
     */
    void Delete();
};

class CKinCallParameter: public CBaseCallParameter
{
    friend class CKinFunction;
// Attributes
private:
    vector < CKinIdentifier > * mIdentifiers;

// Operations
public:
    /**
     *  Default constructor
     */
    CKinCallParameter();

    /**
     *  Init
     */
    void Init();
            
    /**
     *  Destructor
     */
    ~CKinCallParameter();

    /**
     *  Delete
     */
    void Delete();
};
    
class CKinFunction: public CBaseFunction
{
// Attributes
private:
    class CKinNodes: public CCopasiVector < CNodeK >
        {
        private:
            short IsInsertAllowed(CNodeK src);
            
        public:
            CKinNodes();
            ~CKinNodes();
        };

    /**
     *  The vector of nodes of the binary tree of the function
     */
    CKinNodes * mNodes;
    
    /**
     *  The vector of pointers to the identifiers to the function
     */
    vector < CKinCallParameter > * mCallParameters;

    /**
     *  Internal variable
     */
    long mNidx;

// Operations
public:
    /**
     *  Default constructor
     */
    CKinFunction();
    
    /**
     *  This creates a kinetic function with a name an description
     *  @param "const string" &name
     *  @param "const string" &description
     */
    CKinFunction(const string & name,
                 const string & description);

    /**
     *  Init
     */
    void Init();
            
    /**
     *  Destructor
     */
    ~CKinFunction();

    /**
     *  Delete
     */
    void Delete();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    long Load(CReadConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    long Save(CWriteConfig & configbuffer);

    /**
     *  This retrieves the node tree of the function
     *  @return "CCopasiVector < CNodeK > &"
     */
    CCopasiVector < CNodeK > & Nodes();

    /**
     *  This sets the type of an identifier
     *  @param "const string" &name
     *  @param char identifierType
     */
    void SetIdentifierType(const string & name,
                           char identifierType);

    /**
     *  This parses the function longo a binary tree
     */
    long Parse();

    /**
     *  This calculates the value of this sub-tree (ie with this node as root)
     *  @param "vector < double * >" &identifiers
     *  @return double
     */
    double CalcValue(vector < CCallParameter > & callParameters);

    /**
     *
     */
    pair < long, long > FindIdentifier(const string & name);

private:
    /**
     *  This clears all nodes of the function tree
     */
    void ClearNodes();

    /**
     *  This  connects the nodes to build the binary function tree
     */
    long ConnectNodes();

    /**
     *  This function is part of the algorithm that builds the binary tree
     *  @param long priority
     *  @return CNodeK *
     */
    CNodeK * ParseExpression(short priority);

    /**
     *  This function is part of the algorithm that builds the binary tree
     *  @return CNodeK *
     */
    CNodeK * ParsePrimary();

    /**
     *
     */
    void InitIdentifiers();
};

#endif // COPASI_CKinFunction
