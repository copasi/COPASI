/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/25 15:55:42 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeConstant
#define COPASI_CEvaluationNodeConstant

/**
 * This is class for nodes presenting Constants used in an evaluation trees
 */
class CEvaluationNodeConstant : public CEvaluationNode
  {
    /**
     * friend declaration
     */
    friend
    CEvaluationNode * CEvaluationNode::create(const Type & type,
        const Data & data);

  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      PI = 0x00000001,
      EXPONENTIALE = 0x00000002,
      TRUE = 0x00000003,
      FALSE = 0x00000004
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeConstant();

    /**
     * Default constructor
     * @param const Type & subType
     * @param const Data & data
     */
    CEvaluationNodeConstant(const Type & subType,
                            const Data & data);

  public:
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
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual inline const C_FLOAT64 & value() const {return mValue;}
  };

#endif // COPASI_CEvaluationNodeConstant
