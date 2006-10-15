/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeCall.h,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 07:16:08 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeCall
#define COPASI_CEvaluationNodeCall

#include <limits>

#include "mathematics.h"

#include "function/CCallParameters.h"
#include "utilities/CCopasiMessage.h"

class CFunction;
class CExpression;
class CFunctionParameters;

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
     * Check whether node the calls any tree in the list
     * @param std::set< std::string > & list
     * @return bool calls
     */
    bool calls(std::set< std::string > & list) const;

    /**
     * Retrieve the infix value of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getInfix() const;

    /**
     * Retrieve the display string of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getDisplayString(const CEvaluationTree * pTree) const;

    /**
     * Retrieve the display string of the node and its eventual child nodes in C.
     * @return const Data & value
     */
    virtual std::string getDisplay_C_String(const CEvaluationTree * pTree) const;

    /**
     * Retrieve the display string of the node and its eventual child nodes
     * in Berkeley Madonna format.
     * @return const Data & value
     */
    virtual std::string getDisplay_MMD_String(const CEvaluationTree * pTree) const;

    /**
     ** Retrieve the display string of the node and its eventual child nodes
     ** in XPPAUT format.
     ** @return const Data & value
     **/
    virtual std::string getDisplay_XPP_String(const CEvaluationTree * pTree) const;

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
     * Add a child to a node.
     * If pAfter == this the child will be inserted at the front of the list
     * of children.
     * @param CCopasiNode< Data > * pChild
     * @param CCopasiNode< Data > * pAfter
     *        (default: NULL appended to the list of children)
     * @return bool Success
     */
    virtual bool addChild(CCopasiNode< Data > * pChild,
                          CCopasiNode< Data > * pAfter = NULL);

    /**
     * Remove a child from a node.
     * @param CCopasiNode< Data > * pChild
     * @return bool Success
     */
    virtual bool removeChild(CCopasiNode< Data > * pChild);

    /**
     * Retreive the tree which is called from this node
     * @return const CEvaluationTree * calledTree
     */
    const CEvaluationTree * getCalledTree() const;

    /**
     *  generate display MathML recursively
     */

    virtual void writeMathML(std::ostream & out,
                             const std::vector<std::vector<std::string> > & env,
                             bool expand = true, unsigned C_INT32 l = 0) const;
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

    /**
     * Verifies that the parameters match the function parameters.
     * @param const std::vector<CEvaluationNode *> & vector
     * @param const CFunctionParameters & functionParameters
     * @return bool verified
     */
    static bool
    verifyParameters(const std::vector<CEvaluationNode *> & vector,
                     const CFunctionParameters &functionParameters);

    // Attributes
  private:
    CFunction * mpFunction;
    CExpression * mpExpression;
    std::vector<CEvaluationNode *> mCallNodes;
    CCallParameters< C_FLOAT64 > * mpCallParameters;
  };

#endif // COPASI_CEvaluationNodeCall
