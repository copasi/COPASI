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
     *  @param "CReadConfig *" configBuffer (Default = NULL)
     */
    CKinFunction(const CFunction & src, CReadConfig * configBuffer = NULL);

    /**
     *  Copy constructor
     *  @param "const CKinFunction &" src
     */
    CKinFunction(const CKinFunction & src);

    /**
     *  This creates a kinetic function with a name and description
     *  @param "const string" &name
     *  @param "const string" &description
     */
    CKinFunction(const string & name, const string & description);

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
     *  Saves the contents of the object to a CWriteConfig object.
     *  Output is in Gepasi 3.21 file format.
     *  @param "CWriteConfig &" configBuffer.
     *  @return Fail
     */
    void saveOld(CWriteConfig & configBuffer);

    /**
     *  Compile a function
     */
    void compile();

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

    /**
     *  Retreives the nodes of the function
     */
    CCopasiVectorS < CNodeK > & getNodes();

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
     *  This function assignes the appropriate indeces to nodes of type identifier
     *  so that the value of the matching call parameter is returned when 
     *  calculating the function.
     */
    void initIdentifierNodes();
  };

#endif // COPASI_CKinFunction
