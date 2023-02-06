// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathExpression
#define COPASI_CMathExpression

#include <stack>
#include <vector>

#include "copasi/math/CMathObject.h"
#include "copasi/function/CEvaluationTree.h"

#ifdef USE_JIT
# include "copasi/math/CJitExpression.h"
#endif

class CExpression;
class CEvaluationNode;
class CMathContainer;

template < typename Type > class CCallParameters;

class CMathExpression:
#ifdef USE_JIT
  public CJitExpression,
#endif
  public CEvaluationTree
{
private:
  /**
   * Hidden default constructor
   */
  CMathExpression();

  CMathExpression(const CMathExpression & src) = delete;

public:
  /**
   * Specific constructor.
   * @param const std::string & name
   * @param CMathContainer & container
   */
  CMathExpression(const std::string & name,
                  CMathContainer & container);

  /**
   * Specific constructor. The src expression must have been successfully compiled
   * in the context of the current model
   * @param const CExpression & src
   * @param CMathContainer & container
   * @param const bool & replaceDiscontinuousNodes
   */
  CMathExpression(const CExpression & src,
                  CMathContainer & container,
                  const bool & replaceDiscontinuousNodes);

  /**
   * Specific constructor. The src function must have been successfully compiled
   * in the context of the current model
   * @param const CFunction & src
   * @param const CCallParameters< C_FLOAT64 > & callParameters
   * @param CMathContainer & container
   * @param const bool & replaceDiscontinuousNodes
   */
  CMathExpression(const CFunction & src,
                  const CCallParameters< C_FLOAT64 > & callParameters,
                  CMathContainer & container,
                  const bool & replaceDiscontinuousNodes);

  /**
   * Destructor
   */
  virtual ~CMathExpression();

  /**
   * Copy an expression with the given offsets
   * @param const CMathExpression & src
   * @param CMathContainer & container
   * @return CMathExpression * copy
   */
  static CMathExpression * copy(const CMathExpression & src,
                                CMathContainer & container);

  /**
   * Copy an expression with the given offsets
   * @param const CMathContainer * pContainer
   * @param const std::vector< CMath::sRelocate > & relocations
   */
  void relocate(const CMathContainer * pContainer,
                const std::vector< CMath::sRelocate > & relocations);

#ifdef USE_JIT
  /**
   * Compile the Jit expression if we have a compiler at hand
   */
  virtual void compileJit() override;
#endif

  /**
   * Evaluate the expression
   * @return const C_FLOAT64 & value
   */
  const C_FLOAT64 & value();

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const override;

  /**
   * Compile the evaluation tree.
   */
  virtual CIssue compile() override;

  /**
   * Convert to a corresponding initial expression.
   * @return bool success
   */
  bool convertToInitialExpression();

private:
  /**
   * Sets the root node of the tree.
   * Note: This is private to assure that only valid root node representing
   *       mathematical expressions are set.
   * @param CEvaluationNode* root node of the tree
   * @return bool success
   */
  virtual bool setRoot(CEvaluationNode* pRootNode) override;

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
};

#endif // COPASI_CMathExpression
