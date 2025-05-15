// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/***************************************************************************
                  CRandomSearch.cpp  -  Random Optimizer
                     -------------------

Programmer           : Rohan Luktuke
email                : rluktuke@vt.edu
 ***************************************************************************/

/***************************************************************************
 * This is the implementation of the Random Algorithm for Optimization.  The
 * class is inherited from the COptAlgorithm class
 ***************************************************************************/

#include "copasi/copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "CRandomSearch.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/randomGenerator/CRandom.h"

CRandomSearch::CRandomSearch(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType)
  : COptMethod(pParent, methodType, taskType, false)
  , mIterations(100000)
  , mCurrentIteration(0)
  , mIndividual()
  , mValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mpRandom(NULL)
  , mVariableSize(0)
{
  assertParameter("Number of Iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100000);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

CRandomSearch::CRandomSearch(const CRandomSearch & src,
                             const CDataContainer * pParent)
  : COptMethod(src, pParent, false)
  , mIterations(src.mIterations)
  , mCurrentIteration(src.mCurrentIteration)
  , mIndividual(src.mIndividual)
  , mValue(src.mValue)
  , mpRandom(NULL)
  , mVariableSize(src.mVariableSize)
{initObjects();}

/**
 * Destructor
 */
CRandomSearch::~CRandomSearch()
{
  //*** added similar to coptga
  cleanup();
}

void CRandomSearch::initObjects()
{
  addObjectReference("Current Iteration", mCurrentIteration, CDataObject::ValueInt);
}

/**
 * Optimizer Function
 * Returns: true if properly initialized
 * should return a boolean
 */
bool CRandomSearch::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mIterations = getValue< unsigned C_INT32 >("Number of Iterations");

  pdelete(mpRandom);

  if (getParameter("Random Number Generator") != NULL && getParameter("Seed") != NULL)
    {
      mpRandom = CRandom::createGenerator((CRandom::Type) getValue< unsigned C_INT32 >("Random Number Generator"),
                                          getValue< unsigned C_INT32 >("Seed"));
    }
  else
    {
      mpRandom = CRandom::createGenerator();
    }

  mVariableSize = mProblemContext.active()->getOptItemList(true).size();
  mIndividual.resize(mVariableSize);

  return true;
}

/**
 * Optimizer Function
 * Returns: nothing
 * should return a boolean
 */
//C_INT32 CRandomSearch::optimize()
bool CRandomSearch::optimise()
{
  unsigned C_INT32 j;

  // current value is the initial guess
  bool pointInParameterDomain = true;

  if (!initialize()) return false;

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started.",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Random_Search/"
      )
    );

  for (j = 0; j < mVariableSize; j++)
    {
      C_FLOAT64 & mut = mIndividual[j];
      COptItem & OptItem = *mProblemContext.active()->getOptItemList(true)[j];

      mut = OptItem.getStartValue();
      pointInParameterDomain &= OptItem.setItemValue(mut, COptItem::CheckPolicyFlag::All);
      pointInParameterDomain &= mut == OptItem.getStartValue();
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  mValue = evaluate(EvaluationPolicy::Constraints);
  setSolution(mValue, mIndividual, true);

  CVector< C_FLOAT64 > LastIndividual;

  for (mCurrentIteration = 1; mCurrentIteration < mIterations && proceed(); mCurrentIteration++)
    {
      LastIndividual = mIndividual;
      const std::vector< COptItem * > & OptItemList = mProblemContext.active()->getOptItemList(true);

      for (j = 0; j < mVariableSize && proceed(); j++)
        {
          // CALCULATE lower and upper bounds
          COptItem & OptItem = *OptItemList[j];
          C_FLOAT64 & mut = mIndividual[j];

          mut = OptItem.getRandomValue(mpRandom);

          if (!OptItem.setItemValue(mut, COptItem::CheckPolicyFlag::All))
            break;
        }

      if (j < mVariableSize)
        {
          mIndividual = LastIndividual;
          continue;
        }

      mValue = evaluate(EvaluationPolicy::Constraints);

      // COMPARE
      if (mValue < getBestValue())
        setSolution(mValue, mIndividual, true);

      mpParentTask->output(COutputInterface::MONITORING);
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry("Algorithm finished.",
                   "Terminated after " + std::to_string(mCurrentIteration) + " of " + std::to_string(mIterations) + " iterations."));

  return true;
}

unsigned C_INT32 CRandomSearch::getMaxLogVerbosity() const
{
  return 0;
}

C_FLOAT64 CRandomSearch::getCurrentValue() const
{
  return mValue;
}

const CVector< C_FLOAT64 > * CRandomSearch::getBestParameters() const
{
  return &mIndividual;
}

const CVector< C_FLOAT64 > * CRandomSearch::getCurrentParameters() const
{
  return &mIndividual;
}
