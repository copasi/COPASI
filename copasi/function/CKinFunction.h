/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CKinFunction.h,v $
   $Revision: 1.23 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:23:51 $
   End CVS Header */

/**
 * CKinFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CKinFunction
#define COPASI_CKinFunction

#include <vector>

#include "CFunction.h"
#include "CNodeK.h"
#include "utilities/readwrite.h"

/** @dia:pos 61.7476,54.3157 */
/** @dia:route CFunction; v,58.2,35.55,51.6337,82.8684,54.3157 */
class CKinFunction : public CFunction
  {
    // Attributes
  private:
    /**
     *  The vector of nodes of the binary tree of the function
     *  @supplierCardinality 0..*
     *  @associates <{CNodeK}>
     */
    /** @dia:route 0,2; h,61.7476,54.3157,55.1707,42.4925,46.911 */
    std::vector< CNodeK * > mNodes;

    /**
     *  Internal variable
     */
    unsigned C_INT32 mNidx;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CKinFunction(const std::string & name = "NoName",
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunction &" src
     * @param "CReadConfig *" configBuffer (Default = NULL)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CKinFunction(const CFunction & src,
                 CReadConfig * configBuffer = NULL,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CKinFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CKinFunction(const CKinFunction & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    ~CKinFunction();

    /**
     *  Cleanup
     */
    void cleanup();

#ifdef XXXX
    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    void load(CReadConfig & configbuffer,
              CReadConfig::Mode mode = CReadConfig::LOOP);
#endif // XXXX

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  Output is in Gepasi 3.21 file format.
     *  @param "CWriteConfig &" configBuffer.
     *  @return Fail
     */
    void saveOld(CWriteConfig & configBuffer);

    /**
     *  Returns a string containing the explicit function in SBML format
     *  @param "vector < void * >" callParameters
    *  @param "const string &" r a suffix for parameter names (usually reaction number)
     */
    std::string getSBMLString(const std::vector< std::vector< std::string > > & callParameterNames,
                              const std::string &r) const;

    /**
     *  Compile a function
     */
    void compile();

    /**
     *  This parses the function into a binary tree
     */
    C_INT32 parse();

    /**
     *  Set the description of the function
     *  @param "const string &" description
     */
    virtual void setDescription(const std::string& description);

    /**
     *  Calculates the value of the function
     *  @param "vector < void * >" identifiers
     *  @return "C_FLOAT64" result
     */
    virtual C_FLOAT64
    calcValue(const CCallParameterPointers & callParameters) const;

    /**
     * Returns whether the function depends on the given parameter
     * &param const void * parameter
     * &param const CCallParameters & callParameters
     * &param bool dependsOn
     */
    virtual bool dependsOn(const void * parameter,
                           const CCallParameterPointers & callParameters) const;

    /**
     *  Retreives the nodes of the function
     */
    std::vector< CNodeK * > & getNodes();

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

    /**
     * Cleanup nodes
     */
    void cleanupNodes();
  };

#endif // COPASI_CKinFunction
