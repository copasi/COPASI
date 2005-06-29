/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeLogical.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/29 21:54:01 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeLogical
#define COPASI_CEvaluationNodeLogical

#include "mathematics.h"

#include "utilities/CCopasiMessage.h"

class ASTNode;

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeLogical : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      //      NOT = 0x00000001,
      OR = 0x00000001,
      XOR = 0x00000002,
      AND = 0x00000003,
      EQ = 0x00000004,
      NE = 0x00000005,
      GT = 0x00000006,
      GE = 0x00000007,
      LT = 0x00000008,
      LE = 0x00000009
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeLogical();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeLogical(const SubType & subType,
                           const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeLogical & src
     */
    CEvaluationNodeLogical(const CEvaluationNodeLogical & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeLogical();

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual inline const C_FLOAT64 & value() const
      {
        C_FLOAT64 &Value = *const_cast<C_FLOAT64 *>(&mValue);
        switch (mType & 0x00FFFFFF)
          {
          case OR:
            Value = (mpLeft->value() != 0.0 ||
                     mpRight->value() != 0.0) ? 1.0 : 0.0;
            break;

          case XOR:
            Value = ((mpLeft->value() != 0.0 && mpRight->value() == 0.0) ||
                     (mpLeft->value() == 0.0 && mpRight->value() != 0.0)) ? 1.0 : 0.0;
            break;

          case AND:
            Value = (mpLeft->value() != 0.0 &&
                     mpRight->value() != 0.0) ? 1.0 : 0.0;
            break;

          case EQ:
            Value = (mpLeft->value() == mpRight->value()) ? 1.0 : 0.0;
            break;

          case NE:
            Value = (mpLeft->value() != mpRight->value()) ? 1.0 : 0.0;
            break;

          case GT:
            Value = (mpLeft->value() > mpRight->value()) ? 1.0 : 0.0;
            break;

          case GE:
            Value = (mpLeft->value() >= mpRight->value()) ? 1.0 : 0.0;
            break;

          case LT:
            Value = (mpLeft->value() < mpRight->value()) ? 1.0 : 0.0;
            break;

          case LE:
            Value = (mpLeft->value() <= mpRight->value()) ? 1.0 : 0.0;
            break;
          }

        return Value;
      }

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
     * Create a new operator node from an ASTNode tree.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

    /**
     * Create a new ASTNode corresponding to this OperatorNode.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toASTNode();

    // Attributes
  private:
    CEvaluationNode * mpLeft;

    CEvaluationNode * mpRight;
  };

#endif // COPASI_CEvaluationNodeLogical
