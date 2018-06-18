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

#include "copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "CRandomSearch.h"

#include "math/CMathContainer.h"
#include "copasi/core/CDataObjectReference.h"
#include "randomGenerator/CRandom.h"

CRandomSearch::CRandomSearch(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType)
{
  addParameter("Number of Iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100000);
  addParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0);

  initObjects();
}

CRandomSearch::CRandomSearch(const CRandomSearch & src,
                             const CDataContainer * pParent):
  COptMethod(src, pParent)
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
  mpRandom = & mpContainer->getRandomGenerator();
  mpRandom->initialize(getValue< unsigned C_INT32 >("Seed"));

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();

  mVariableSize = mpOptItem->size();
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
  bool Continue = true;

  if (!initialize()) return false;

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Random.Search"));

  unsigned C_INT32 j;

  // current value is the initial guess
  bool pointInParameterDomain = true;

  for (j = 0; j < mVariableSize; j++)
    {
      C_FLOAT64 & mut = mIndividual[j];
      COptItem & OptItem = *(*mpOptItem)[j];

      mut = OptItem.getStartValue();

      // force it to be within the bounds
      switch (OptItem.checkConstraint(mut))
        {
          case - 1:
            mut = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mut = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;
        }

      // We need to set the value here so that further checks take
      // account of the value.
      *mContainerVariables[j] = (mut);
    }

  if (!pointInParameterDomain) mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_initial_point_out_of_domain));

  Continue = evaluate(mIndividual);
  mBestValue = mValue;
  Continue = mpOptProblem->setSolution(mBestValue, mIndividual);

  // We found a new best value lets report it.
  //if (mpReport) mpReport->printBody();
  mpParentTask->output(COutputInterface::DURING);

  for (mCurrentIteration = 1; mCurrentIteration < mIterations && Continue; mCurrentIteration++)
    {
      for (j = 0; j < mVariableSize && Continue; j++)
        {
          // CALCULATE lower and upper bounds
          COptItem & OptItem = *(*mpOptItem)[j];
          C_FLOAT64 & mut = mIndividual[j];

          mut = OptItem.getRandomValue(*mpRandom);

          // force it to be within the bounds
          switch (OptItem.checkConstraint(mut))
            {
              case - 1:
                mut = *OptItem.getLowerBoundValue();

                if (!OptItem.checkLowerBound(mut)) // Inequality
                  {
                    if (mut == 0.0)
                      mut = std::numeric_limits< C_FLOAT64 >::min();
                    else
                      mut += mut * std::numeric_limits< C_FLOAT64 >::epsilon();
                  }

                break;

              case 1:
                mut = *OptItem.getUpperBoundValue();

                if (!OptItem.checkUpperBound(mut)) // Inequality
                  {
                    if (mut == 0.0)
                      mut = - std::numeric_limits< C_FLOAT64 >::min();
                    else
                      mut -= mut * std::numeric_limits< C_FLOAT64 >::epsilon();
                  }

                break;
            }

          // We need to set the value here so that further checks take
          // account of the value.
          *mContainerVariables[j] = (mut);
        }

      Continue = evaluate(mIndividual);

      // COMPARE
      if (mValue < mBestValue)
        {
          mBestValue = mValue;
          Continue = mpOptProblem->setSolution(mBestValue, mIndividual);

          // We found a new best value lets report it.
          //if (mpReport) mpReport->printBody();
          mpParentTask->output(COutputInterface::DURING);
        }
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish_x_of_max_iter).iter(mCurrentIteration).with(mIterations));

  return true;
}

// evaluate the fitness of one individual
bool CRandomSearch::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue = mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mValue = std::numeric_limits<C_FLOAT64>::infinity();
  else
    mValue = mpOptProblem->getCalculateValue();

  return Continue;
}

unsigned C_INT32 CRandomSearch::getMaxLogVerbosity() const
{
  return 0;
}
