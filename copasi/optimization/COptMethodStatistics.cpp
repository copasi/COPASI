/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodStatistics.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/25 22:19:26 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COptMethod.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "COptMethodStatistics.h"

#include "report/CCopasiObjectReference.h"
#include "randomGenerator/CRandom.h"

COptMethodStatistics::COptMethodStatistics():
    COptMethod(CCopasiTask::optimization, CCopasiMethod::Statistics)
{
  initObjects();
}

COptMethodStatistics::COptMethodStatistics(const COptMethodStatistics & src):
    COptMethod(src)
{initObjects();}

/**
 * Destructor
 */
COptMethodStatistics::~COptMethodStatistics()
{//*** added similar to coptga
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

  mBestValue = mpOptProblem->getSolutionValue();

  mVariableSize = mpOptItem->size();
  mIndividual.resize(mVariableSize);

  return true;
}

/**
 * Optimizer Function
 * Returns: nothing
 * should return a boolean
 */
//C_INT32 COptMethodStatistics::optimise()
bool COptMethodStatistics::optimise()
{
  bool Continue = true;

  if (!initialize()) return false;

  unsigned C_INT32 j;

  // initialise the population
  // first individual is the initial guess
  for (j = 0; j < mVariableSize; j++)
    {
      C_FLOAT64 & mut = mIndividual[j];
      COptItem & OptItem = *(*mpOptItem)[j];

      mut = * OptItem.getObjectValue();

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
      (*(*mpSetCalculateVariable)[j])(mut);
    }

  Continue = evaluate(mIndividual);

  mBestValue = mValue;
  mpOptProblem->setSolutionVariables(mIndividual);
  Continue = mpOptProblem->setSolutionValue(mBestValue);

  // We found a new best value lets report it.
  //if (mpReport) mpReport->printBody();
  mpParentTask->output(COutputInterface::DURING);

  return Continue;
}

// evaluate the fitness of one individual
bool COptMethodStatistics::evaluate(const CVector< C_FLOAT64 > & /* individual */)
{
  bool Continue = true;

  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  // evaluate the fitness
  Continue = mpOptProblem->calculate();

  // check wheter the functional constraints are fulfilled
  if (!mpOptProblem->checkFunctionalConstraints())
    mValue = DBL_MAX;
  else
    mValue = mpOptProblem->getCalculateValue();

  return Continue;
}
