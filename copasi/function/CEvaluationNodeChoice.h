/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeChoice.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/03 10:24:36 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeChoice
#define COPASI_CEvaluationNodeChoice

#include <limits>

#include "mathematics.h"
#include "utilities/CCopasiMessage.h"

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeChoice : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      IF = 0x00000000
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeChoice();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeChoice(const SubType & subType,
                          const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeChoice & src
     */
    CEvaluationNodeChoice(const CEvaluationNodeChoice & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeChoice();

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
     * Creates a new CEvaluationNodeChoice from an ASTNode.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

    /**
     * Create a new ASTNode corresponding to this choice node.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toAST() const;

  private:

    // Attributes
  private:
    CEvaluationNode * mpIf;
    CEvaluationNode * mpTrue;
    CEvaluationNode * mpFalse;
  };

#endif // COPASI_CEvaluationNodeChoice
