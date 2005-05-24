/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeNumber.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/24 18:06:17 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeNumber
#define COPASI_CEvaluationNodeNumber

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeNumber : public CEvaluationNode
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
    CEvaluationNodeNumber();

    /**
     * Default constructor
     * @param const Data & data
     */
    CEvaluationNodeNumber(const Data & data);

  public:
    /**
     * Copy constructor
     * @param const CEvaluationNodeNumber & src
     */
    CEvaluationNodeNumber(const CEvaluationNodeNumber & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeNumber();

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

#endif // COPASI_CEvaluationNodeNumber
