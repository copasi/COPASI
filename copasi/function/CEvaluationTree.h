/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 19:12:36 $
   End CVS Header */

#ifndef COPASI_CEvaluationTree
#define COPASI_CEvaluationTree

#include <vector>

#include "utilities/CCopasiTree.h"
#include "CEvaluationNode.h"

class CCopasiObjectName;

class CEvaluationTree : public CCopasiTree < CEvaluationNode >
  {
    // Operations
  public:
    /**
     * Default constructor
     */
    CEvaluationTree();

    /**
     * Destructor
     */
    virtual ~CEvaluationTree();

    /**
     * Set the string description of the tree and compile it.
     * @param const std::string & description
     * @return bool success
     */
    bool setDescription(const std::string & description);

    /**
     * Compile the description into a tree.
     * @return bool success
     */
    bool compile();

    /**
     * Retrieve the position of the error in the string description.
     * std::string::npos indicates no error.
     * @return std::string::size_type errorPosition
     */
    std::string::size_type getErrorPosition() const;

    /**
     * Retrieve a pointer to the value of the named variable.
     * @param const std::string & name
     * @return C_FLOAT64 * value
     */
    C_FLOAT64 * getVariableValue(const std::string & name) const;

    /**
     * Retrieve a pointer to the value of the object define dby CN.
     * @param const CCopasiObjectName & CN
     * @return C_FLOAT64 * value
     */
    C_FLOAT64 * getObjectValue(const CCopasiObjectName & CN) const;

  private:
    /**
     * Parse the description
     * @return bool success
     */
    bool parse();

    /**
     * Link the nodes in the tree.
     * @return bool success
     */
    bool linkNodes();

    /**
     * Compile the individual nodes.
     * @return bool success
     */
    bool compileNodes();

    // Attributes
  private:
    /**
     * The string representation of the expression
     */
    std::string mDescription;

    /**
     * The error position in case the compilation fails.
     * std::string::npos indicates no error.
     */
    std::string::size_type mErrorPosition;

    /**
     * A vector of nodes containing the result of parse.
     */
    std::vector< CEvaluationNode * > * mpNodeList;
  };

#endif // COPASI_CEvaluationTree
