/*****************************************************************************
 * PROGRAM NAME: CUDFunction.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Define the user defined function object
 *****************************************************************************/
#ifndef COPASI_CUDFunction
#define COPASI_CUDFunction

#include <string>
#include <vector>

#include "copasi.h"
#include "utilities/readwrite.h"
#include "function/CKinFunction.h"
#include "model/CModel.h"
#include "CNodeO.h"

class CUDFunction: public CKinFunction
  {
  private:
    /**
     *  The vector of nodes of the binary tree of the function
     */
    std::vector< CNodeO * > mNodes;

    /**
     * Value of user defined function
     */
    C_FLOAT64 mValue;

    /**
     *  Internal variable
     */
    unsigned C_INT32 mNidx;

    /**
     *  A pointer to the  call parameters of the user defined function
     */ 
    //CCallParameters mCallParameters;

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CUDFunction(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CUDFunction(const CFunction & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CUDFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CUDFunction(const CUDFunction & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  This creates a user defined function with a name an description
     *  @param "const string" &name
     *  @param "const string" &description
     */
    CUDFunction(const std::string & name,
                const std::string & description,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    virtual ~CUDFunction();

    /**
     *  Delete
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
     *  Compile a function
     */
    void compile();

    /**
     *  This parses the function into a binary tree
     */
    C_INT32 parse();

    /**
     * Calculate the value of this user defined function
     * return the pointer of this user defined function
     */
    C_FLOAT64 calcValue();

    /**
     * Get the pointer of user defined function
     */
    void * getValueAddr();

    /**
     * Return the value of user defined function
     */
    C_FLOAT64 getValue() const;

    //CCallParameters & getCallParameters();

    /**
     *  This parses the function into a binary tree
     */ 
    //C_INT32 parse();

    /**
     *  Retreives the nodes of the function
     */
    std::vector< CNodeO * > & getNodes();

  private:
    /**
     *  This function creates the parameter description for older file versions
     */
    void createParameters();

    /**
     *  This  connects the nodes to build the binary function tree
     */
    C_INT32 connectNodes();

    /**
     *  This function is part of the algorithm that builds the binary tree
     *  @param C_INT16 priority
     *  @return CNodeK *
     */
    CNodeO * parseExpression(C_INT16 priority);

    /**
     *  This function is part of the algorithm that builds the binary tree
     *  @return CNodeK *
     */
    CNodeO * parsePrimary();

    /**
     * Cleanup nodes
     */
    void cleanupNodes();
  };

#endif
