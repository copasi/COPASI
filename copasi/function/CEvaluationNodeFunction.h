// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeFunction
#define COPASI_CEvaluationNodeFunction

#include <limits>
#include <cmath>

#if defined(WIN32)
#if __cplusplus <= 199711L // These are not part of ANSI C and Visual C++ misses them.
#if _MSVC_LANG <= 201103L
static inline double asinh(double value)
{return log(value + sqrt(value * value + 1.0));}

static inline double acosh(double value)
{return log(value + sqrt(value * value - 1.0));}

static inline double atanh(double value)
{return (.5 * log((1.0 + value) / (1.0 - value)));}

static inline double round(double value)
{return  value < 0.0 ? -floor(-value + 0.5) : floor(value + 0.5);}
#endif
#endif // not c++11
#endif // WIN32

#include "copasi/function/CEvaluationNode.h"

class CRandom;
class CDataModel;

/**
 * This is the class for nodes presenting build-in functions used in an evaluation trees.
 */
class CEvaluationNodeFunction : public CEvaluationNode
{
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
  virtual inline void calculate() override
  {
    if (mpFunction)
      {
        mValue = (*mpFunction)(*mpArgValue1);
      }
    else if (mpFunction2)
      {
        mValue = (*mpFunction2)(*mpArgValue1, *mpArgValue2);
      }
    else if (mpFunction4)
      {
        mValue = (*mpFunction4)(*mpArgValue1, *mpArgValue2, *mpArgValue3, *mpArgValue4);
      }
  }

  /**
   * Compile a node;
   * @param const CEvaluationTree * pTree
   * @return CIssue issue;
   */
  virtual CIssue compile() override;

  /**
   * Retrieve the infix value of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getInfix(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes.
   * @return const Data & value
   */
  virtual std::string getDisplayString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes in C.
   * @return const Data & value
   */
  virtual std::string getCCodeString(const std::vector< std::string > & children) const override;

  /**
   * Retrieve the display string of the node and its eventual child nodes
   * in Berkeley Madonna format.
   * @return const Data & value
   */
  virtual std::string getBerkeleyMadonnaString(const std::vector< std::string > & children) const override;

  /**
   ** Retrieve the display string of the node and its eventual child nodes
   ** in XPPAUT format.
   ** @return const Data & value
   **/
  virtual std::string getXPPString(const std::vector< std::string > & children) const override;

  /**
   * Figure out the appropriate CUnit to use, based on the child nodes.
   * This sets the default, appropriate for many cases, as Dimensionless
   * @param const CMathContainer & container
   * @param const std::vector< CValidatedUnit > & units
   * @return CValidatedUnit unit
   */
  virtual CValidatedUnit getUnit(const CMathContainer & container,
                                 const std::vector< CValidatedUnit > & units) const override;

  /**
   * Set the unit for the node and return the resulting unit. The child node units are
   * added to the map
   * @param const CMathContainer & container
   * @param const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits
   * @param std::map < CEvaluationNode * , CValidatedUnit > & targetUnits
   * @return CValidatedUnit unit
   */
  virtual CValidatedUnit setUnit(const CMathContainer & container,
                                 const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
                                 std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const override;

  /**
   * Creates a new CEvaluationNodeCall from an ASTNode and the given children
   * @param const ASTNode* pNode
   * @param const std::vector< CEvaluationNode * > & children
   * @return CEvaluationNode * pCretedNode
   */
  static CEvaluationNode * fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children);

  /**
   * Create a new ASTNode corresponding to this FunctionNode.
   * @return ASTNode* return a pointer to the newly created node;
   */
  virtual ASTNode* toAST(const CDataModel* pDataModel) const override;

  /**
   * Create a simplified node for an operatorNode with children from vector (if not exist, = NULL),
   * and assign new children
   * @return CEvaluationNode* return a pointer to the simplified node;
   */
  virtual CEvaluationNode* simplifyNode(const std::vector<CEvaluationNode*>& children) const override;

  /**
   * Build the MathML string
   * @param const std::vector< std::string > & children
   * @param bool expand = true
   * @param const std::vector< std::vector< std::string > > & variables
   * @return std::string MMLString
   */
  virtual std::string getMMLString(const std::vector< std::string > & children,
                                   bool expand,
                                   const std::vector< std::vector< std::string > > & variables) const override;

  CEvaluationNode * getLeft();
  const CEvaluationNode * getLeft() const;

  std::string handleSign(const std::string & str) const;

  std::string handleNot(const std::string & str) const;

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

  static inline C_FLOAT64 sign(C_FLOAT64 value)
  {return (value < 0.0) ? -1.0 : (value > 0.0) ? 1.0 : 0.0;}

  static C_FLOAT64 runiform(C_FLOAT64 lowerBound,
                            C_FLOAT64 upperBound);

  static C_FLOAT64 rnormal(C_FLOAT64 mean,
                           C_FLOAT64 sd);

  static C_FLOAT64 rgamma(C_FLOAT64 shape,
                          C_FLOAT64 scale);

  static C_FLOAT64 rpoisson(C_FLOAT64 mu);

  static C_FLOAT64 max(C_FLOAT64 x1,
                       C_FLOAT64 x2);

  static C_FLOAT64 min(C_FLOAT64 x1,
                       C_FLOAT64 x2);

  // Attributes
private:
  C_FLOAT64(*mpFunction)(C_FLOAT64 arg1);

  C_FLOAT64(*mpFunction2)(C_FLOAT64 arg1,
                          C_FLOAT64 arg2);

  C_FLOAT64(*mpFunction4)(C_FLOAT64 arg1,
                          C_FLOAT64 arg2,
                          C_FLOAT64 arg3,
                          C_FLOAT64 arg4);

  CEvaluationNode * mpArgNode1;
  CEvaluationNode * mpArgNode2;
  CEvaluationNode * mpArgNode3;
  CEvaluationNode * mpArgNode4;

  const C_FLOAT64 * mpArgValue1;
  const C_FLOAT64 * mpArgValue2;
  const C_FLOAT64 * mpArgValue3;
  const C_FLOAT64 * mpArgValue4;

  static CRandom * mpRandom;
};

#endif // COPASI_CEvaluationNodeFunction
