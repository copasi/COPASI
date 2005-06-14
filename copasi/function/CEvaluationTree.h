/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/14 17:34:38 $
   End CVS Header */

#ifndef COPASI_CEvaluationTree
#define COPASI_CEvaluationTree

#include <vector>

#include "CEvaluationNode.h"

class CCopasiObjectName;
class ASTNode;

class CEvaluationTree
  {
  public:
    typedef const C_FLOAT64 & (CEvaluationTree::*VariableValue)();

    // Operations
  public:
    /**
     * Default constructor
     */
    CEvaluationTree();

    /**
     * Copy constructor
     * @param const CEvaluationTree & src
     */
    CEvaluationTree(const CEvaluationTree & src);

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
     * Set the infix description of the tree and compile it.
     * @param const std::string & infix
     * @return bool success
     */
    virtual bool setInfix(const std::string & infix);

    /**
     * Retrieve the infix description of the tree
     * @return const std::string & infix
     */
    const std::string & getInfix() const;

    /**
     * Retrieve the position of the error in the string description.
     * std::string::npos indicates no error.
     * @return std::string::size_type errorPosition
     */
    std::string::size_type getErrorPosition() const;

    /**
     * Retrieve the index to the value of the named variable.
     * @param const std::string & name
     * @return unsigned C_INT32
     */
    virtual unsigned C_INT32 getVariableIndex(const std::string & name) const;

    /**
     * Retrieve the value of the indexed variable
     * @param const unsigned C_INT32 & index
     * @return const C_FLOAT64 & variableValue
     */
    virtual const C_FLOAT64 & getVariableValue(const unsigned C_INT32 & index) const;

    /**
     * Retrieve a pointer to the value of the object define dby CN.
     * @param const CCopasiObjectName & CN
     * @return C_FLOAT64 * value
     */
    virtual C_FLOAT64 * getObjectValue(const CCopasiObjectName & CN) const;

  protected:
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
     * The infix representation of the expression
     */
    std::string mInfix;

    /**
     * The error position in case the compilation fails.
     * std::string::npos indicates no error.
     */
    std::string::size_type mErrorPosition;

  protected:
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
