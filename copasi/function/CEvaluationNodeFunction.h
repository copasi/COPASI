// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.h,v $
//   $Revision: 1.31.2.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/01/14 09:25:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeFunction
#define COPASI_CEvaluationNodeFunction

#include <limits>
#include <float.h>

#include "copasi/mathematics.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/function/CEvaluationNode.h"

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

class CRandom;

/**
 * This is the class for nodes presenting build-in functions used in an evaluation trees.
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
      PLUS = 0x00000021,
      NOT = 0x00000022,
      RUNIFORM = 0x00000023,
      RNORMAL = 0x00000024
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
        if (mpFunction2)
          return *const_cast<C_FLOAT64 *>(&mValue) = (*mpFunction2)(mpLeft->value(), mpRight->value());
        else
          return *const_cast<C_FLOAT64 *>(&mValue) = (*mpFunction)(mpLeft->value());
      }

    /**
     * Compile a node;
     * @param const CEvaluationTree * pTree
     * @return bool success;
     */
    virtual bool compile(const CEvaluationTree * pTree);

    /**
     * Retrieve the infix value of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getInfix() const;

    /**
     * Retrieve the display string of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getDisplayString(const CEvaluationTree * pTree) const;

    /**
     * Retrieve the display string of the node and its eventual child nodes in C.
     * @return const Data & value
     */
    virtual std::string getDisplay_C_String(const CEvaluationTree * pTree) const;

    /**
     * Retrieve the display string of the node and its eventual child nodes
     * in Berkeley Madonna format.
     * @return const Data & value
     */
    virtual std::string getDisplay_MMD_String(const CEvaluationTree * pTree) const;

    /**
     ** Retrieve the display string of the node and its eventual child nodes
     ** in XPPAUT format.
     ** @return const Data & value
     **/
    virtual std::string getDisplay_XPP_String(const CEvaluationTree * pTree) const;

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
    virtual ASTNode* toAST() const;

    /**
     * Create a simplified node for an operatorNode with children from vector (if not exist, = NULL),
     * and assign new children
     * @return CEvaluationNode* return a pointer to the simplified node;
     */
    virtual CEvaluationNode* simplifyNode(const std::vector<CEvaluationNode*>& children) const;

    /**
     *  generate display MathML recursively
     **/

    virtual void writeMathML(std::ostream & out,
                             const std::vector<std::vector<std::string> > & env,
                             bool expand = true, unsigned C_INT32 l = 0) const;

    CEvaluationNode * getLeft();
    const CEvaluationNode * getLeft() const;

  private:
    std::string handleSign(const std::string & str) const;

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
        return std::numeric_limits<C_FLOAT64>::quiet_NaN();

      if (value > 170)
        return DBL_MAX * 2;

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

    static inline C_FLOAT64 copasiNot(C_FLOAT64 value)
  {return (value != 0.0) ? 0.0 : 1.0;}

    static C_FLOAT64 runiform(const C_FLOAT64 & lowerBound,
                              const C_FLOAT64 & upperBound);

    static C_FLOAT64 rnormal(const C_FLOAT64 & mean,
                             const C_FLOAT64 & sd);

    // Attributes
  private:
    C_FLOAT64 (*mpFunction)(C_FLOAT64 value1);

    C_FLOAT64 (*mpFunction2)(const C_FLOAT64 & value1,
                             const C_FLOAT64 & value2);

    CEvaluationNode * mpLeft;

    CEvaluationNode * mpRight;

    static CRandom * mpRandom;
  };

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

#endif // COPASI_CEvaluationNodeFunction
