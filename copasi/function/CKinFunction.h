/**
 * CKinFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CKinFunction
#define COPASI_CKinFunction

#include "CFunction.h"
#include "CNodeK.h"
#include "utilities/utilities.h"

class CKinFunction : public CFunction
{
  // Attributes
 private:
  /**
   *  The vector of nodes of the binary tree of the function
   *  @supplierCardinality 0..*
   *  @associates <{CNodeK}>
   */
  CCopasiVectorS < CNodeK > mNodes;

  /**
   *  Internal variable
   */
  unsigned C_INT32 mNidx;

  // Operations  
 public:    
  /**
   *  Default constructor
   */
  CKinFunction();

  /**
   *  Copy constructor
   *  @param "const CFunction &" src
   */
  CKinFunction(const CFunction & src);

  /**
   *  Copy constructor
   *  @param "const CKinFunction &" src
   */
  CKinFunction(const CKinFunction & src);

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
   *  Cleanup
   */
  void cleanup();

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return Fail
   */
  void load(CReadConfig & configbuffer,
            CReadConfig::Mode mode = CReadConfig::LOOP);

  /**
   *  This parses the function into a binary tree
   */
  C_INT32 parse();

  /**
   *  Calculates the value of the function
   *  @param "vector < void * >" identifiers
   *  @return "C_FLOAT64" result
   */
  virtual C_FLOAT64 
    calcValue(const CCallParameters & callParameters) const;

 private:

  /**
   *  This  connects the nodes to build the binary function tree
   */
  C_INT32 connectNodes();

  /**
   *  This function is part of the algorithm that builds the binary tree
   *  @param C_INT16 priority
   *  @return CNodeK *
   */
  CNodeK * parseExpression(C_INT16 priority);

  /**
   *  This function is part of the algorithm that builds the binary tree
   *  @return CNodeK *
   */
  CNodeK * parsePrimary();

  /**
   *  This function creates the parameter description for older file versions
   */
  void createParameters();

  /**
   *  This function assignes the appropriate indezes to nodes of type identifier
   *  so that the value of the matching call parameter is returned when 
   *  calculating the function.
   */
  void initIdentifierNodes();
};

#endif // COPASI_CKinFunction
