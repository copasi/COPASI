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

#include "CNodeK.h"
#include "CCopasiVector.h"

class CKinFunction
{
// Attributes
public:

private:
    /**
     *  The name of the function
     */
    string mName;

    /**
     *  The description of the function
     */
    string mDescription;

    /**
     *  The vector of nodes of the binary tree of the function
     */
    CCopasiVector < CNodeK > mNodes;

    /**
     *  The vector of pointers to the identifiers to the function
     */
    typedef struct IDENTIFIER 
    {
        string Name;
        vector < CNodeK * > Nodes;
    };
    vector < IDENTIFIER > mIdentifiers;

    /**
     *  This indicates whether the function is reversible
     */
    short mReversible;

    /**
     *  Internal variable (We should get rid of this)
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
     *  Destructor
     */
    ~CKinFunction();

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
     *  This retrieves the name of the function
     *  @return string
     */
    string GetName();

    /**
     *  This retrieves the description of the function
     *  @return string
     */
    string GetDescription();

    /**
     *  This retrieves the node tree of the function
     *  @return "CCopasiVector < CNodeK > &"
     */
    CCopasiVector < CNodeK > & Nodes();

    /**
     *  This retrieves the identifiers of the function
     *  @return vector < CNodeK >
     */
    vector < IDENTIFIER > & Identifiers();

    /**
     *  This retrieves the type of an identifier of the function
     *  @return char 
     */
    char GetIdentifierType(const string & name);

    /**
     *  This sets the name of the function
     *  @param "const string" &name
     */
    SetName(const string & name);

    /**
     *  This sets the description of the function
     *  @param "const string" &description
     */
    SetDescription(const string & description);

    /**
     *  This sets wheter the function is reversible
     *  @param short reversible
     */
    SetReversible(short reversible);

    /**
     *  This sets the type of an identifier
     *  @param "const string" &name
     *  @param char type
     */
    SetIdentifierType(const string & name,
                           char type);

    /**
     *  This returns the value of mReversible
     *  @return short
     */
    short IsReversible();

    /**
     *  This parses the function longo a binary tree
     */
    long Parse();

    /**
     *  The finds the identifier with the given name
     *  @param "const string" &name
     *  @return long index of the identifier or -1 if not found
     */
    long FindIdentifier(const string & name);

    /**
     *  This calculates the value of this sub-tree (ie with this node as root)
     *  @param "vector < double * >" &identifiers
     *  @return double
     */
    double CalcValue(vector < double * > &identifiers);

  private:
    /**
     *  This clears all nodes of the function tree
     */
    long ClearNodes();

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
    long InitIdentifiers();
};

#endif // COPASI_CKinFunction
