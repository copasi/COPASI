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

class CKinFunction: public CBaseFunction
{
// Attributes
private:
    /**
     *  The vector of nodes of the binary tree of the function
     */
    class CNodes: public CCopasiVector < CNodeK >
      {
      private:
	short IsInsertAllowed(CNodeK src) {return TRUE;}
      } mNodes;

    class CIdentifier: public CBaseIdentifier
        {
        // Attributes
        public:
            /*
             *  The nodes which access the same identifier.
             */
            vector < CNodeK * > mNodes;
        };
    
    /**
     *  The vector of pointers to the identifiers to the function
     */
    vector < CIdentifier > mIdentifiers;

    /**
     *  This indicates whether the function is reversible
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
     *  @param char type
     */
    void SetIdentifierType(const string & name,
                           char type);

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
