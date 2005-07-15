/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeCall.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/15 14:20:51 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeCall
#define COPASI_CEvaluationNodeCall

#include <limits>

#include "mathematics.h"

#include "CCallParameters.h"
#include "utilities/CCopasiMessage.h"

class CFunction;
class CExpression;

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeCall : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      FUNCTION = 0x00000000,
      EXPRESSION = 0x00000001
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeCall();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeCall(const SubType & subType,
                        const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeCall & src
     */
    CEvaluationNodeCall(const CEvaluationNodeCall & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeCall();

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual const C_FLOAT64 & value() const;

    /**
     * Compile a node;
     * @param const CEvaluationTree * pTree
     * @return bool success;
     */
    virtual bool compile(const CEvaluationTree * pTree);

    /**
     * Retrieve the infix value of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getInfix() const;

    /**
     * Creates a new CEvaluationNodeCall from an ASTNode.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

    /**
     * Create a new ASTNode corresponding to this choice node.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toAST() const;

    /**
     * Set the name of the evaluation tree to be called.
     * @param const std::string & name
     */
    void setEvaluationTreeName(const std::string & name);

    /**
     * Add a child to a node.
     * If pAfter == this the child will be inserted at the fornt of the list
     * of children.
     * @param CCopasiNode< Data > * pChild
     * @param CCopasiNode< Data > * pAfter 
     *        (default: NULL appended to the list of children)
     * @return bool Success
     */
    bool addChild(CCopasiNode< Data > * pChild,
                  CCopasiNode< Data > * pAfter = NULL);

  private:
    /**
     * Build the list of call parameters which correspond to
     * the list of call nodes.
     */
    static CCallParameters< C_FLOAT64 > *
    buildParameters(const std::vector<CEvaluationNode *> & vector);

    /**
     * Clear the list of call parameters.
     */
    static void
    clearParameters(CCallParameters< C_FLOAT64 > * pCallParameters,
                    const std::vector<CEvaluationNode *> & vector);

    // Attributes
  private:
    std::string mEvaluationTreeName;
    CFunction * mpFunction;
    CExpression * mpExpression;
    std::vector<CEvaluationNode *> mCallNodes;
    CCallParameters< C_FLOAT64 > * mpCallParameters;
  };

#endif // COPASI_CEvaluationNodeCall
