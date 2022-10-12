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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "COptMethodStatistics.h"

#include "copasi/core/CDataObjectReference.h"
#include "copasi/randomGenerator/CRandom.h"

COptMethodStatistics::COptMethodStatistics(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType, false),
  mIndividual(),
  mValue(0.0),
  mVariableSize(0),
  mBestValue(0.0)
{
  initObjects();
}

COptMethodStatistics::COptMethodStatistics(const COptMethodStatistics & src,
    const CDataContainer * pParent):
  COptMethod(src, pParent),
  mIndividual(src.mIndividual),
  mValue(src.mValue),
  mVariableSize(src.mVariableSize),
  mBestValue(src.mBestValue)
{initObjects();}

/**
 * Destructor
 */
COptMethodStatistics::~COptMethodStatistics()
{
  //*** added similar to coptga
  cleanup();
}

/**
 * Optimizer Function
 * Returns: true if properly initialized
 * should return a boolean
 */
bool COptMethodStatistics::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mBestValue = std::numeric_limits< C_FLOAT64 >::infinity();

  mVariableSize = mProblemContext.master()->getOptItemList(true).size();
  mIndividual.resize(mVariableSize);

  return true;
}

/**
 * Optimizer Function
 * Returns: nothing
 * should return a boolean
 */
bool COptMethodStatistics::optimise()
{
  bool Continue = true;

  if (!initialize()) return false;

  size_t j;

  // Initialize the population
  // first individual is the initial guess
  for (j = 0; j < mVariableSize; j++)
    {
      C_FLOAT64 & mut = mIndividual[j];
      const COptItem & OptItem = *mProblemContext.master()->getOptItemList(true)[j];

      mut = OptItem.getStartValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
          case - 1:
            mut = *OptItem.getLowerBoundValue();
            break;

          case 1:
            mut = *OptItem.getUpperBoundValue();
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      *mProblemContext.master()->getContainerVariables(true)[j] = mut;
    }

  Continue = evaluate(mIndividual);

  mBestValue = mValue;
  Continue = mProblemContext.master()->setSolution(mBestValue, mIndividual, true);

  // We found a new best value lets report it.
  //if (mpReport) mpReport->printBody();
  mpParentTask->output(COutputInterface::DURING);

  mpParentTask->output(COutputInterface::MONITORING);

  return true;
}

C_FLOAT64 COptMethodStatistics::getBestValue() const
{
  return mValue;
}

C_FLOAT64 COptMethodStatistics::getCurrentValue() const
{
  return mValue;
}

const CVector< C_FLOAT64 > * COptMethodStatistics::getBestParameters() const
{
  return &mIndividual;
}

const CVector< C_FLOAT64 > * COptMethodStatistics::getCurrentParameters() const
{
  return &mIndividual;
}

// evaluate the fitness of one individual
bool COptMethodStatistics::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue = mProblemContext.master()->calculate();

  // check whether the functional constraints are fulfilled
  if (!mProblemContext.master()->checkFunctionalConstraints())
    mValue = std::numeric_limits< C_FLOAT64 >::max();
  else
    mValue = mProblemContext.master()->getCalculateValue();

  return Continue;
}
