/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/06/10 11:54:30 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeFunction
#define COPASI_CEvaluationNodeFunction

#include <limits>

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
      COSH = 0x0000000a,
      TANH = 0x0000000b,
      SECH = 0x0000000c,
      CSCH = 0x0000000d,
      COTH = 0x0000000e,
      ARCSIN = 0x0000000f,
      ARCCOS = 0x00000010,
      ARCTAN = 0x00000011,
      ARCSEC = 0x00000012,
      ARCCSC = 0x00000013,
      ARCCOT = 0x00000014,
      ARCSINH = 0x00000015,
      ARCCOSH = 0x00000016,
      ARCTANH = 0x00000017,
      ARCSECH = 0x00000018,
      ARCCSCH = 0x00000019,
      ARCCOTH = 0x0000001a,
      SQRT = 0x0000001b,
      ABS = 0x0000001c,
      FLOOR = 0x0000001d,
      CEIL = 0x0000001e,
      FACTORIAL = 0x0000001f,
      MINUS = 0x00000020,
      PLUS = 0x00000021
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

    /**
     * Creates a new CEvaluationNodeFunction from an ASTNode.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

    /**
     * Create a new ASTNode corresponding to this FunctionNode.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toASTNode();

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

    static inline C_FLOAT64 factorial(C_FLOAT64 value)
    {
      if (value < 0.0 ||
          value != ceil(value))
        return std::numeric_limits<C_FLOAT64>::signaling_NaN();

      if (value > 170)
        return std::numeric_limits<C_FLOAT64>::infinity();

      if (value == 0.0)
        return 0.0;

      C_FLOAT64 Value = 1.0;
      C_FLOAT64 Result = 1.0;

      while (Value < value) Result *= Value++;

      return Result;
    }

    static inline C_FLOAT64 minus(C_FLOAT64 value)
  {return - value;}

    static inline C_FLOAT64 plus(C_FLOAT64 value)
    {return value;}

    // Attributes
  private:
    C_FLOAT64 (*mpFunction)(C_FLOAT64 value1);

    CEvaluationNode * mpLeft;
  };

#endif // COPASI_CEvaluationNodeFunction
