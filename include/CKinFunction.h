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
    vector < CNodeK * > mNodes;

// Operations
public:
    /**
     *  Default constructor
     */
    CKinIdentifier();
                    
    /**
     *  Destructor
     */
    ~CKinIdentifier();
};

class CKinFunction: public CBaseFunction
{
// Attributes
private:
    class CKinNodes: public CCopasiVector < CNodeK >
        {
        public:
            CKinNodes();
            ~CKinNodes();

        private:
            C_INT16 IsInsertAllowed(const CNodeK & src);
        };

    /**
     *  The vector of nodes of the binary tree of the function
     */
    CKinNodes * mNodes;
    
    /**
     *  Internal variable
     */
    C_INT32 mNidx;

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
     *  Copy
     */
    void Copy(const CKinFunction & in);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 Load(CReadConfig & configbuffer,
                 CReadConfig::Mode mode = CReadConfig::LOOP);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 Save(CWriteConfig & configbuffer);

    /**
     *  This retrieves the node tree of the function
     *  @return "CCopasiVector < CNodeK > &"
     */
    CKinNodes & Nodes();

    /**
     *  This sets the type of an identifier
     *  @param "const string" &name
     *  @param char identifierType
     */
    void SetIdentifierType(const string & name,
                           char identifierType);

    /**
     *  This parses the function into a binary tree
     */
    C_INT32 Parse();

    /**
     *  This calculates the value of this sub-tree (ie with this node as root)
     *  @param "vector < C_FLOAT64 * >" &identifiers
     *  @return C_FLOAT64
     */
    C_FLOAT64 CalcValue(vector < CCallParameter > & callParameters) const;

private:
    /**
     *  This clears all nodes of the function tree
     */
    void ClearNodes();

    /**
     *  This  connects the nodes to build the binary function tree
     */
    C_INT32 ConnectNodes();

    /**
     *  This function is part of the algorithm that builds the binary tree
     *  @param long priority
     *  @return CNodeK *
     */
    CNodeK * ParseExpression(C_INT16 priority);

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
