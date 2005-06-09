/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/09 13:46:28 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeConstant
#define COPASI_CEvaluationNodeConstant

class ASTNode;

/**
 * This is class for nodes presenting Constants used in an evaluation trees
 */
class CEvaluationNodeConstant : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      PI = 0x00000000,
      EXPONENTIALE = 0x00000001,

#ifdef TRUE
# undef TRUE
#endif
      TRUE = 0x00000002,

#ifdef FALSE
# undef FALSE
#endif
      FALSE = 0x00000003
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeConstant();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeConstant(const SubType & subType,
                            const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeConstant & src
     */
    CEvaluationNodeConstant(const CEvaluationNodeConstant & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeConstant();

    /**
     * Create a new operator node from an ASTNode tree.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode* node);

    /**
     * Create a new ASTNode corresponding to this ConstantNode.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toASTNode();
  };

#endif // COPASI_CEvaluationNodeConstant
