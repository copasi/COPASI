/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVariable.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/03 10:24:36 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeVariable
#define COPASI_CEvaluationNodeVariable

class ASTNode;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeVariable : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     * The typing of variables must be handled by the tree.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      ANY = 0x00000000
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeVariable();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeVariable(const SubType & subType,
                            const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeVariable & src
     */
    CEvaluationNodeVariable(const CEvaluationNodeVariable & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeVariable();

    /**
     * Compile a node;
     * @param const CEvaluationTree * pTree
     * @return bool success;
     */
    virtual bool compile(const CEvaluationTree * pTree);

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual inline const C_FLOAT64 & value() const;

    /**
     * Converts this node to an AST Node of type AST_NAME
     * @return ASTNode* the resulting ASTNode.
     */
    virtual ASTNode* toAST() const;

    //Attributes
  private:
    /**
     * Pointer to the evaluation tree.
     */
    const CEvaluationTree * mpTree;

    /**
     * Index of the variable used to retrieve its value from the tree.
     */
    unsigned C_INT32 mIndex;
  };

#endif // COPASI_CEvaluationNodeVariable
