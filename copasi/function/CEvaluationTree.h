/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/24 13:52:06 $
   End CVS Header */

#ifndef COPASI_CEvaluationTree
#define COPASI_CEvaluationTree

#include <vector>

#include "CEvaluationNode.h"
#include "report/CCopasiContainer.h"

class ASTNode;

class CEvaluationTree:
      public CCopasiContainer
  {
  public:
    /**
     *  The valid types of a function
     */
    enum Type
    {
      Function = 0,
      MassAction,
      PreDefined,
      UserDefined,
      Expression
    };

    /**
     *  The string representation of valid types of a function
     */
    static const std::string TypeName[];

    /**
     *  The string representation of valid types of a function
     */
    static const char * XMLType[];

    // Operations
  public:
    /**
     * Create an EvaluationTree of the specified type.
     * Note: the returned object has to be released after use with delete.
     * @param CEvaluationTree::Type type 
     * @return EvaluationTree * pEvaluationTree
     */
    static CEvaluationTree *
    create(CEvaluationTree::Type type);

    /**
     * Copy an EvaluationTree of the specified type.
     * Note: the returned object has to be released after use with delete.
     * @param const EvaluationTree & src
     * @return EvaluationTree * pEvaluationTree
     */
    static CEvaluationTree *
    copy(const CEvaluationTree & src);

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const CEvaluationTree::Type & type (default: Function)
     */
    CEvaluationTree(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NULL,
                    const Type & type = Function);

    /**
     * Copy constructor
     * @param const CEvaluationTree & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CEvaluationTree(const CEvaluationTree & src,
                    const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CEvaluationTree();

    /**
     * Retrieves the type of the function
     * @return const CEvaluationTree::Type & type
     */
    const CEvaluationTree::Type & getType() const;

    /**
     * Set the type of the function
     * @param const CEvaluationTree::Type & type
     */
    void setType(const CEvaluationTree::Type & type);

    /**
     * Retrieves the key of the EvaluationTree
     * @return const std::string & key
     */
    const std::string & getKey() const;

    /**
     * Sets the root node of the tree.
     * @param CEvaluationNode* root node of the tree
     * @return bool success
     */
    bool setRoot(CEvaluationNode* pRootNode);

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
     * Retrieve the list of nodes
     * @return const std::vector< CEvaluationNode * > & nodeList;
     */
    const std::vector< CEvaluationNode * > & getNodeList() const;

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

    /**
     * Returns the root node of the tree.
     */
    CEvaluationNode* getRoot();

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
     * The type of the function
     */
    CEvaluationTree::Type mType;

    /**
     * The key of the function
     */
    std::string mKey;

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
