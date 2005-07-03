/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeStructure.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/07/03 10:24:36 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeStructure
#define COPASI_CEvaluationNodeStructure

class ASTNode;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeStructure : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      OPEN = 0x00000000,
      COMMA = 0x00000001,
      CLOSE = 0x00000002
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeStructure();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeStructure(const SubType & subType,
                             const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeStructure & src
     */
    CEvaluationNodeStructure(const CEvaluationNodeStructure & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeStructure();

    /**
     * Create a new ASTNode corresponding to this structure node.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toAST() const;
  };

#endif // COPASI_CEvaluationNodeStructure
