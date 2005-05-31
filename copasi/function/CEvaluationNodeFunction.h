/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeFunction
#define COPASI_CEvaluationNodeFunction

#include "mathematics.h"

#include "utilities/CCopasiMessage.h"

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeFunction : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      LOG = 0x00000000,
      LOG10 = 0x00000001,
      EXP = 0x00000002,
      SIN = 0x00000003,
      COS = 0x00000004,
      TAN = 0x00000005,
#ifdef SEC
# undef SEC
#endif
      SEC = 0x00000006,
      CSC = 0x00000007,
      COT = 0x00000008,
      SINH = 0x00000009,
      COSH = 0x00000010,
      TANH = 0x00000011,
      SECH = 0x00000012,
      CSCH = 0x00000013,
      COTH = 0x00000014,
      ARCSIN = 0x00000015,
      ARCCOS = 0x00000016,
      ARCTAN = 0x00000017,
      ARCSEC = 0x00000018,
      ARCCSC = 0x00000019,
      ARCCOT = 0x00000020,
      ARCSINH = 0x00000021,
      ARCCOSH = 0x00000022,
      ARCTANH = 0x00000023,
      ARCSECH = 0x00000024,
      ARCCSCH = 0x00000025,
      ARCCOTH = 0x00000026,
      SQRT = 0x00000027,
      ABS = 0x00000028,
      MINUS = 0x00000029
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeFunction();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeFunction(const SubType & subType,
                            const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeFunction & src
     */
    CEvaluationNodeFunction(const CEvaluationNodeFunction & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeFunction();

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual inline const C_FLOAT64 & value() const
      {
        return *const_cast<C_FLOAT64 *>(&mValue)
        = (*mpFunction)(mpLeft->value());
      }

    /**
     * Compile a node;
     * @param const CEvaluationTree * pTree
     * @return bool success;
     */
    virtual bool compile(const CEvaluationTree * pTree);

  private:
    static inline C_FLOAT64 sec(C_FLOAT64 value)
    {return 1.0 / cos(value);}

    static inline C_FLOAT64 csc(C_FLOAT64 value)
    {return 1.0 / sin(value);}

    static inline C_FLOAT64 cot(C_FLOAT64 value)
    {return 1.0 / tan(value);}

    static inline C_FLOAT64 sech(C_FLOAT64 value)
    {return 1.0 / cosh(value);}

    static inline C_FLOAT64 csch(C_FLOAT64 value)
    {return 1.0 / sinh(value);}

    static inline C_FLOAT64 coth(C_FLOAT64 value)
    {return 1.0 / tanh(value);}

    static inline C_FLOAT64 arcsec(C_FLOAT64 value)
    {return acos(1.0 / value);}

    static inline C_FLOAT64 arccsc(C_FLOAT64 value)
    {return asin(1.0 / value);}

    static inline C_FLOAT64 arccot(C_FLOAT64 value)
    {return atan(1.0 / value);}

    static inline C_FLOAT64 asech(C_FLOAT64 value)
    {return acosh(1.0 / value);}

    static inline C_FLOAT64 acsch(C_FLOAT64 value)
    {return asinh(1.0 / value);}

    static inline C_FLOAT64 acoth(C_FLOAT64 value)
    {return atanh(1.0 / value);}

    static inline C_FLOAT64 minus(C_FLOAT64 value)
    {return - value;}

    // Attributes
  private:
    C_FLOAT64 (*mpFunction)(C_FLOAT64 value1);

    CEvaluationNode * mpLeft;
  };

#endif // COPASI_CEvaluationNodeFunction
