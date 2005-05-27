/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeOperator.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/27 18:08:59 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeOperator
#define COPASI_CEvaluationNodeOperator

#include "mathematics.h"

#include "utilities/CCopasiMessage.h"

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeOperator : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      POWER = 0x00000000,
      MULTIPLY = 0x00000001,
      DIVIDE = 0x00000002,
      MODULUS = 0x00000003,
      PLUS = 0x00000004,
      MINUS = 0x00000005
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeOperator();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeOperator(const SubType & subType,
                            const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeOperator & src
     */
    CEvaluationNodeOperator(const CEvaluationNodeOperator & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeOperator();

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual inline const C_FLOAT64 & value() const
      {
        return *const_cast<C_FLOAT64 *>(&mValue)
        = (*mpOperation)(mpLeft->value(), mpRight->value());
      }

    /**
     * Compile a node;
     * @return bool success;
     */
    virtual bool compile();

  private:
    static inline C_FLOAT64 operationPower(const C_FLOAT64 & value1,
                                           const C_FLOAT64 & value2)
    {return pow(value1, value2);}

    static inline C_FLOAT64 operationMultiply(const C_FLOAT64 & value1,
        const C_FLOAT64 & value2)
    {return value1 * value2;}

    static inline C_FLOAT64 operationDivide(const C_FLOAT64 & value1,
                                            const C_FLOAT64 & value2)
    {return value1 / value2;}

    static inline C_FLOAT64 operationModulus(const C_FLOAT64 & value1,
        const C_FLOAT64 & value2)
    {return (C_FLOAT64) (((C_INT32) value1) % ((C_INT32) value2));}

    static inline C_FLOAT64 operationPlus(const C_FLOAT64 & value1,
                                          const C_FLOAT64 & value2)
    {return value1 + value2;}

    static inline C_FLOAT64 operationMinus(const C_FLOAT64 & value1,
                                           const C_FLOAT64 & value2)
    {return value1 - value2;}

    // Attributes
  private:
    C_FLOAT64 (*mpOperation)(const C_FLOAT64 & value1,
                             const C_FLOAT64 & value2);

    CEvaluationNode * mpLeft;

    CEvaluationNode * mpRight;
  };

#endif // COPASI_CEvaluationNodeOperator
