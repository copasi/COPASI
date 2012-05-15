// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeFunction.h,v $
//   $Revision: 1.51 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/15 18:32:58 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
#include <cmath>

#ifdef WIN32 // These are not part of ANSI C and Visual C++ misses them.
static inline double asinh(double value)
{return log(value + sqrt(value * value + 1.0));}

static inline double acosh(double value)
{return log(value + sqrt(value * value - 1.0));}

static inline double atanh(double value)
{return (.5 * log((1.0 + value) / (1.0 - value)));}

static inline double round(double value)
{return  value < 0.0 ? -floor(-value + 0.5) : floor(value + 0.5);}
#endif // WIN32

#include "copasi/function/CEvaluationNode.h"

class CRandom;
class CCopasiDataModel;

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
    RNORMAL = 0x00000024,
    MAX = 0x00000025,
    MIN =  0x00000026
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
   * Calculate the numerical result of the node. It is assumed that
   * all child nodes are up to date.
   */
  virtual inline void calculate()
  {
    if (mpFunction)
      {
        mValue = (*mpFunction)(mpArg1->getValue());
      }
    else if (mpFunction2)
      {
        mValue = (*mpFunction2)(mpArg1->getValue(), mpArg2->getValue());
      }
    else if (mpFunction4)
      {
        mValue = (*mpFunction4)(mpArg1->getValue(), mpArg2->getValue(),
                                mpArg3->getValue(), mpArg4->getValue());
      }
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
  virtual std::string getInfix(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const std::vector< std::string > & children) const;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return const Data & value
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const;

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
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Check whether the result is Boolean
   * @return bool isBoolean
   */
  virtual bool isBoolean() const;

  /**
   * Create a new ASTNode corresponding to this FunctionNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CCopasiDataModel* pDataModel) const;

  /**
   * Create a simplified node for an operatorNode with children from vector (if not exist, = NULL),
   * and assign new children
   * @return CEvaluationNode* return a pointer to the simplified node;
   */
  virtual CEvaluationNode* simplifyNode(const std::vector<CEvaluationNode*>& children) const;

  /**
   * generate display MathML recursively
   */
  virtual void writeMathML(std::ostream & out,
                           const std::vector<std::vector<std::string> > & env,
                           bool expand = true,
                           size_t l = 0) const;

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
      return std::numeric_limits<C_FLOAT64>::infinity();

    if (value == 0.0)
      return 1.0;

    C_FLOAT64 Value = 1.0;
    C_FLOAT64 Result = 1.0;

    while (Value < value) Result *= ++Value;

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

  static C_FLOAT64 max(const C_FLOAT64 & x1,
                       const C_FLOAT64 & x2);

  static C_FLOAT64 min(const C_FLOAT64 & x1,
                       const C_FLOAT64 & x2);

  // Attributes
private:
  C_FLOAT64(*mpFunction)(C_FLOAT64 arg1);

  C_FLOAT64(*mpFunction2)(const C_FLOAT64 & arg1,
                          const C_FLOAT64 & arg2);

  C_FLOAT64(*mpFunction4)(const C_FLOAT64 & arg1,
                          const C_FLOAT64 & arg2,
                          const C_FLOAT64 & arg3,
                          const C_FLOAT64 & arg4);

  CEvaluationNode * mpArg1;
  CEvaluationNode * mpArg2;
  CEvaluationNode * mpArg3;
  CEvaluationNode * mpArg4;

  static CRandom * mpRandom;
};

#endif // COPASI_CEvaluationNodeFunction
