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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// adapted by Stefan Hoops, August 2006, from the original Gepasi file
// nelmea.cpp :

#include <cmath>
#include <sstream>

#include "copasi/copasi.h"

#include "COptMethodSA.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/randomGenerator/CRandom.h"

#define STORED 2
#define NS 10
#define K 1.0

COptMethodSA::COptMethodSA(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType)
  : COptMethod(pParent, methodType, taskType, false)
  , mTemperature(1.0)
  , mhTemperature(C_INVALID_INDEX)
  , mCoolingFactor(0.85)
  , mTolerance(1.e-006)
  , mpRandom(NULL)
  , mVariableSize(0)
  , mEvaluationValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mCurrent()
  , mCurrentValue(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
  , mStep(0)
  , mAccepted()
{
  assertParameter("Start Temperature", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.0);
  assertParameter("Cooling Factor", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 0.85);
  assertParameter("Tolerance", CCopasiParameter::Type::UDOUBLE, (C_FLOAT64) 1.e-006);
  assertParameter("Random Number Generator", CCopasiParameter::Type::UINT, (unsigned C_INT32) CRandom::mt19937, eUserInterfaceFlag::editable);
  assertParameter("Seed", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);

  initObjects();
}

COptMethodSA::COptMethodSA(const COptMethodSA & src,
                           const CDataContainer * pParent)
  : COptMethod(src, pParent)
  , mTemperature(src.mTemperature)
  , mhTemperature(C_INVALID_INDEX)
  , mCoolingFactor(src.mCoolingFactor)
  , mTolerance(src.mTolerance)
  , mpRandom(NULL)
  , mVariableSize(src.mVariableSize)
  , mEvaluationValue(src.mEvaluationValue)
  , mCurrent(src.mCurrent)
  , mCurrentValue(src.mCurrentValue)
  , mStep(src.mStep)
  , mAccepted(src.mAccepted)
{
  initObjects();
}

COptMethodSA::~COptMethodSA()
{cleanup();}

void COptMethodSA::initObjects()
{
  addObjectReference("Current Temperature", mTemperature, CDataObject::ValueDbl);
}

bool COptMethodSA::optimise()
{
  if (!initialize())
    {
      if (mProcessReport
          && !mProcessReport.finishItem(mhTemperature))
        signalStop();

      return false;
    }

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(
      COptLogEntry(
        "Algorithm started",
        "For more information about this method see: http://copasi.org/Support/User_Manual/Methods/Optimization_Methods/Simulated_Annealing/"
      )
    );

  size_t i, j, k, m, h, a, nt;
  C_FLOAT64 xc, p, c, New, minstep;
  C_FLOAT64 fk[STORED];
  bool ready;

  const std::vector< COptItem * > & OptItemList = mProblemContext.master()->getOptItemList(true);

  // set the minimum step size as being the average of step sizes
  // or 100*DBL_EPSILON if average is zero
  for (i = 0, minstep = 0.0; i < mVariableSize; i++)
    {
      minstep += fabs(OptItemList[i]->getItemValue());
    }

  if (minstep > std::numeric_limits< C_FLOAT64 >::epsilon())
    minstep /= mVariableSize;
  else
    minstep = 100 * std::numeric_limits< C_FLOAT64 >::epsilon();

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(COptLogEntry("Minimal step size is " + std::to_string(minstep) + "."));

  // initial point is first guess but we have to make sure that we
  // are within the parameter domain
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      COptItem & OptItem = *OptItemList[i];

      mCurrent[i] = OptItem.getStartValue();
      pointInParameterDomain &= OptItem.setItemValue(mCurrent[i], COptItem::CheckPolicyFlag::All);
      pointInParameterDomain &= (mCurrent[i] == OptItem.getStartValue());

      // The step must not contain any zeroes
      mStep[i] = std::max(fabs(mCurrent[i]), minstep);
    }

  if (!pointInParameterDomain && (mLogVerbosity > 0))
    mMethodLog.enterLogEntry(COptLogEntry("Initial point outside parameter domain."));

  mCurrentValue = evaluate(EvaluationPolicy::Constraints);

  if (!std::isnan(mEvaluationValue))
    setSolution(mEvaluationValue, mCurrent, true);

  // store this in all positions
  for (a = 0; a < STORED; a++)
    fk[a] = mCurrentValue;

  mAccepted = 0;

  // set the number of steps at one single temperature
  nt = (5 * mVariableSize);

  if (nt < 100) nt = 100;

  if (mLogVerbosity > 0)
    mMethodLog.enterLogEntry(COptLogEntry(std::to_string(nt * NS * mVariableSize) + " Steps per temperature cycle."));

  // no temperature reductions yet
  k = 0;

  do // number of internal cycles: max(5*mVariableSize, 100) * NS * mVariableSize
    {
      for (m = 0; m < nt && proceed(); m++) // step adjustments
        {
          for (j = 0; j < NS && proceed(); j++) // adjustment in all directions
            {
              for (h = 0; h < mVariableSize && proceed(); h++) // adjustment in one direction
                {
                  COptItem & OptItem = *OptItemList[h];
                  // Calculate the step
                  xc = (2.0 * mpRandom->getRandomCC() - 1) * mStep[h];
                  New = mCurrent[h] + xc;

                  // Set the new parameter value
                  if (!OptItem.setItemValue(New, COptItem::CheckPolicyFlag::All))
                    {
                      // Undo since not accepted
                      OptItem.setItemValue(mCurrent[h], COptItem::CheckPolicyFlag::None);
                      continue;
                    }

                  // evaluate the function
                  mEvaluationValue = evaluate(EvaluationPolicy::Constraints);

                  // Check all functional constraints
                  if (!mProblemContext.master()->checkFunctionalConstraints())
                    {
                      // Undo since not accepted
                      OptItem.setItemValue(mCurrent[h], COptItem::CheckPolicyFlag::None);
                      continue;
                    }

                  // here we have a completely feasible point
                  // keep if energy is reduced
                  if (mEvaluationValue <= mCurrentValue)
                    {
                      // only one value has changed...
                      mCurrent[h] = New;
                      mCurrentValue = mEvaluationValue;
                      i++;  // a new point
                      mAccepted[h]++; // a new point in this coordinate

                      if (mCurrentValue < getBestValue())
                        setSolution(mEvaluationValue, mCurrent, true);
                    }
                  else
                    {
                      // keep with probability p, if energy is increased
                      p = exp((mCurrentValue - mEvaluationValue) / (K * mTemperature));

                      if (p > mpRandom->getRandomCO())
                        {
                          // only one value has changed...
                          mCurrent[h] = New;
                          mCurrentValue = mEvaluationValue;
                          i++;  // a new point
                          mAccepted[h]++; // a new point in this coordinate
                        }
                      else
                        // Undo since not accepted
                        OptItem.setItemValue(mCurrent[h], COptItem::CheckPolicyFlag::None);
                    }
                }
            }

          // update the step sizes
          for (a = 0; a < mVariableSize; a++)
            {
              c = (C_FLOAT64) mAccepted[a] / (C_FLOAT64) NS;

              if (c > 0.6)
                mStep[a] *= 1 + 5 * (c - 0.6);
              else if (c < 0.4)
                mStep[a] /= 1 + 5 * (0.4 - c);

              mAccepted[a] = 0;
            }
        }

      // the equilibrium energy

      k++;

      // if this is the first cycle ignore the convergence tests
      if (k == 1)
        ready = false;
      else
        {
          ready = true;

          // check termination criterion of not much change since last STORED times
          for (a = 0; a < STORED; a++)
            if (fabs(fk[a] - mCurrentValue) > mTolerance)
              {
                ready = false;
                break;
              }

          if (!ready)
            {
              for (a = 0; a < STORED - 1; a++)
                fk[a] = fk[a + 1];

              fk[STORED - 1] = mCurrentValue;
            }
          // check the termination criterion of not much larger than last optimal
          else
            {
              if (mLogVerbosity > 0)
                {
                  std::ostringstream auxStream;
                  auxStream << mTemperature;
                  mMethodLog.enterLogEntry(
                    COptLogEntry(
                      "At temperature cycle " + std::to_string(k) +
                      " the objective function value improved less than tolerance since last " +
                      std::to_string(STORED) + " cycles.",
                      "Temperature = " + auxStream.str() + "."));
                }

              if (fabs(mCurrentValue - getBestValue()) > mTolerance)
                ready = false;
            }
        }

      if (!ready)
        {
          i++;

          mCurrent = mProblemContext.master()->getSolutionVariables(true);

          for (a = 0; a < mVariableSize; a++)
            OptItemList[a]->setItemValue(mCurrent[a], COptItem::CheckPolicyFlag::None);

          mCurrentValue = getBestValue();
        }
      else
        {
          if (mLogVerbosity > 0)
            {
              std::ostringstream auxStream;
              auxStream << mTemperature;
              mMethodLog.enterLogEntry(
                COptLogEntry(
                  "At temperature cycle " + std::to_string(k) +
                  " the objective function value improved from optimum less than tolerance. Terminating.",
                  "Temperature = " + auxStream.str() + "."));
            }
        }

      // update the temperature
      mTemperature *= mCoolingFactor;

      if (mProcessReport
          && !mProcessReport.progressItem(mhTemperature))
        signalStop();

      mpParentTask->output(COutputInterface::MONITORING);
    }
  while (!ready && proceed());

  if (mLogVerbosity > 0)
    {
      std::ostringstream auxStream;
      auxStream << mTemperature;
      mMethodLog.enterLogEntry(
        COptLogEntry("Algorithm finished.",
                     "Final Temperature was " + auxStream.str() +
                     " after " + std::to_string(k) + " temperature cycles."
                    ));
    }

  if (mProcessReport
      && !mProcessReport.finishItem(mhTemperature))
    signalStop();

  return true;
}

bool COptMethodSA::cleanup()
{
  return true;
}

bool COptMethodSA::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mTemperature = getValue< C_FLOAT64 >("Start Temperature");
  mCoolingFactor = getValue< C_FLOAT64 >("Cooling Factor");
  mTolerance = getValue< C_FLOAT64 >("Tolerance");

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

  if (mProcessReport)
    mhTemperature =
      mProcessReport.addItem("Current Temperature",
                             mTemperature);

  mVariableSize = mProblemContext.master()->getOptItemList(true).size();

  mCurrent.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mAccepted.resize(mVariableSize);

  return true;
}

unsigned C_INT32 COptMethodSA::getMaxLogVerbosity() const
{
  return 1;
}

C_FLOAT64 COptMethodSA::getCurrentValue() const
{
  return mCurrentValue;
}

const CVector< C_FLOAT64 > * COptMethodSA::getBestParameters() const
{
  return &mCurrent;
}

const CVector< C_FLOAT64 > * COptMethodSA::getCurrentParameters() const
{
  return &mCurrent;
}
