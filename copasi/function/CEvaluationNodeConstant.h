/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/24 21:02:37 $
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
    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeConstant();

    /**
     * Default constructor
     * @param const Data & data
     */
    CEvaluationNodeConstant(const Data & data);

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

    /**
     * Set the data of the Node.
     * @param const Data & data
     * @return bool success
     */
    virtual bool setData(const Data & data);
  };

#endif // COPASI_CEvaluationNodeConstant
