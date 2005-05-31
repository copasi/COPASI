/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVariable.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeVariable
#define COPASI_CEvaluationNodeVariable

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
    virtual inline const C_FLOAT64 & value() const {return *mpValue;}

    //Attributes
  private:
    /**
     * Pointer to the value of the variable.
     */
    C_FLOAT64 * mpValue;
  };

#endif // COPASI_CEvaluationNodeVariable
