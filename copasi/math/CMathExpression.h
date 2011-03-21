// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/CMathExpression.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/21 15:45:57 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathExpression
#define COPASI_CMathExpression

#include <stack>
#include <vector>

#include "copasi/math/CMathObject.h"
#include "copasi/function/CEvaluationTree.h"

class CExpression;
class CEvaluationNode;
class CMathContainer;
template < typename Type > class CCallParameters;

class CMathExpression: public CEvaluationTree
{
private:
  /**
   * Hidden default constructor
   */
  CMathExpression();

public:
  /**
   * Specific constructor
   * @param const CExpression & src
   * @param const CMathContainer & container
   */
  CMathExpression(const CExpression & src, const CMathContainer & container);

  /**
   * Specific constructor
   * @param const CFunction & src
   * @param const CCallParameters< C_FLOAT64 > * mpCallParameters
   * @param const CMathContainer & container
   */
  CMathExpression(const CFunction & src,
                  const CCallParameters< C_FLOAT64 > * pCallParameters,
                  const CMathContainer & container);

  /**
   * Destructor
   */
  virtual ~CMathExpression();

  /**
   * Evaluate the expression
   * @return const C_FLOAT64 & value
   */
  const C_FLOAT64 & value() const;

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const;

private:
  /**
   * Convert the node and its children, which refer to objects not supported in the math expression,
   * which are e.g. calls to functions, access to object nodes
   * @param CEvaluationNode * pNode
   * @return CEvaluationNode * pConvertedNode
   */
  CEvaluationNode * convertNode(CEvaluationNode * pNode);

  /**
   * Create a node based on the given pointer to a data value
   * @param const C_FLOAT64 * pDataValue
   * @return CEvaluationNode * pNode
   */
  CEvaluationNode * createNodeFromValue(const C_FLOAT64 * pDataValue);

  /**
   * Create a part of Mass Action kinetics
   * @param const C_FLOAT64 * pK
   * @param const CCallParameters< C_FLOAT64 > * pSpecies
   * @return CEvaluationNode * massActionPart
   */
  CEvaluationNode * createMassActionPart(const C_FLOAT64 * pK,
                                         const CCallParameters< C_FLOAT64 > * pSpecies);

  // Attributes
  /**
   * The prerequisites for calculating the expression.
   */
  CObjectInterface::ObjectSet mPrerequisites;

  /**
   * A stack to map variable nodes to the value nodes provided
   * in the function call
   */
  std::stack< std::vector< const CEvaluationNode * > > mFunctionVariableMap;
};

#endif // COPASI_CMathExpression
