/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/10 11:54:31 $
   End CVS Header */

#ifndef COPASI_CEvaluationTree
#define COPASI_CEvaluationTree

#include <vector>

#include "CEvaluationNode.h"

class CCopasiObjectName;
class ASTNode;

class CEvaluationTree
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
     * Sets the complete tree from an SBML ASTNode.
     * @param const ASTNode& root node of the tree
     * @return bool success
     */
    bool setTree(const ASTNode& pRootNode);

    /**
     * Converts an SBML ASTNode to the corresponding
     * CEvaluationNode tree. 
     * @param const ASTNode& node
     * @return CEvaluationNode*
     */
    static CEvaluationNode* convertASTNode(const ASTNode& node);

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

    /**
     * The root node of the tree.
     */
    CEvaluationNode * mpRoot;
  };

#endif // COPASI_CEvaluationTree
