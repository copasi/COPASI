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

#include "copasi.h"

#include "COptMethodSA.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "copasi/core/CDataObjectReference.h"
#include "randomGenerator/CRandom.h"

#define STORED 2
#define NS 10
#define K 1.0

COptMethodSA::COptMethodSA(const CDataContainer * pParent,
                           const CTaskEnum::Method & methodType,
                           const CTaskEnum::Task & taskType):
  COptMethod(pParent, methodType, taskType)
{
  addParameter("Start Temperature", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.0);
  addParameter("Cooling Factor", CCopasiParameter::UDOUBLE, (C_FLOAT64) 0.85);
  addParameter("Tolerance", CCopasiParameter::UDOUBLE, (C_FLOAT64) 1.e-006);
  addParameter("Random Number Generator", CCopasiParameter::UINT, (unsigned C_INT32) CRandom::mt19937);
  addParameter("Seed", CCopasiParameter::UINT, (unsigned C_INT32) 0);

  initObjects();
}

COptMethodSA::COptMethodSA(const COptMethodSA & src,
                           const CDataContainer * pParent):
  COptMethod(src, pParent)
{initObjects();}

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
      if (mpCallBack)
        mpCallBack->finishItem(mhTemperature);

      return false;
    }

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_start).with("OD.Simulated.Annealing"));

  size_t i, j, k, m;

  size_t h, a;
  C_FLOAT64 xc, p, c, nt, New;
  C_FLOAT64 fk[STORED];
  bool ready;

  // initial point is first guess but we have to make sure that we
  // are within the parameter domain
  bool pointInParameterDomain = true;

  for (i = 0; i < mVariableSize; i++)
    {
      const COptItem & OptItem = *(*mpOptItem)[i];

      switch (OptItem.checkConstraint(OptItem.getStartValue()))
        {
          case - 1:
            mCurrent[i] = *OptItem.getLowerBoundValue();
            pointInParameterDomain = false;
            break;

          case 1:
            mCurrent[i] = *OptItem.getUpperBoundValue();
            pointInParameterDomain = false;
            break;

          case 0:
            mCurrent[i] = OptItem.getStartValue();
            break;
        }

      *mContainerVariables[i] = (mCurrent[i]);

      // The step must not contain any zeroes
      mStep[i] = std::max(fabs(mCurrent[i]), 1.0);
    }

  if (!pointInParameterDomain) mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_initial_point_out_of_domain));

  mCurrentValue = evaluate();

  if (!isnan(mEvaluationValue))
    {
      // and store that value
      mBestValue = mEvaluationValue;
      mContinue &= mpOptProblem->setSolution(mBestValue, mCurrent);

      // We found a new best value lets report it.
      mpParentTask->output(COutputInterface::DURING);
    }

  // store this in all positions
  for (a = 0; a < STORED; a++)
    fk[a] = mCurrentValue;

  mAccepted = 0;

  // set the number of steps at one single temperature
  nt = (C_FLOAT64)(5 * mVariableSize);

  if (nt < 100) nt = 100;

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::SA_steps_per_temp).with(nt));

  // no temperature reductions yet
  k = 0;

  do // number of internal cycles: max(5*mVariableSize, 100) * NS * mVariableSize
    {
      for (m = 0; m < nt && mContinue; m++) // step adjustments
        {
          for (j = 0; j < NS && mContinue; j++) // adjustment in all directions
            {
              for (h = 0; h < mVariableSize && mContinue; h++) // adjustment in one direction
                {
                  // Calculate the step
                  xc = (2.0 * mpRandom->getRandomCC() - 1) * mStep[h];
                  New = mCurrent[h] + xc;

                  // Set the new parameter value
                  *mContainerVariables[h] = (New);

                  // Check all parametric constraints
                  if (!mpOptProblem->checkParametricConstraints())
                    {
                      // Undo since not accepted
                      *mContainerVariables[h] = (mCurrent[h]);
                      continue;
                    }

                  // evaluate the function
                  evaluate();

                  // Check all functional constraints
                  if (!mpOptProblem->checkFunctionalConstraints())
                    {
                      // Undo since not accepted
                      *mContainerVariables[h] = (mCurrent[h]);
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

                      if (mCurrentValue < mBestValue)
                        {
                          // and store that value
                          mBestValue = mEvaluationValue;
                          mContinue &= mpOptProblem->setSolution(mBestValue, mCurrent);

                          // We found a new best value lets report it.
                          mpParentTask->output(COutputInterface::DURING);
                        }
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
                        *mContainerVariables[h] = (mCurrent[h]);
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
              if (mLogVerbosity >= 1) mMethodLog.enterLogItem(COptLogItem(COptLogItem::SA_fval_progress_lower_than_tol).iter(k).with(STORED).with(mTemperature));

              if (fabs(mCurrentValue - mBestValue) > mTolerance)
                ready = false;
            }
        }

      if (!ready)
        {
          i++;

          mCurrent = mpOptProblem->getSolutionVariables();

          for (a = 0; a < mVariableSize; a++)
            *mContainerVariables[a] = mCurrent[a];

          mCurrentValue = mBestValue;
        }
      else
        mMethodLog.enterLogItem(COptLogItem(COptLogItem::SA_fval_tol_termination).iter(k).with(mTemperature));

      // update the temperature
      mTemperature *= mCoolingFactor;

      if (mpCallBack)
        mContinue &= mpCallBack->progressItem(mhTemperature);
    }
  while (!ready && mContinue);

  mMethodLog.enterLogItem(COptLogItem(COptLogItem::STD_finish_temp_info).iter(k).with(mTemperature));

  if (mpCallBack)
    mpCallBack->finishItem(mhTemperature);

  return true;
}

bool COptMethodSA::cleanup()
{
  return true;
}

const C_FLOAT64 & COptMethodSA::evaluate()
{
  // We do not need to check whether the parametric constraints are fulfilled
  // since the parameters are created within the bounds.

  mContinue &= mpOptProblem->calculate();
  mEvaluationValue = mpOptProblem->getCalculateValue();

  // When we leave the either functional domain
  // we set the objective value +Inf
  if (!mpOptProblem->checkFunctionalConstraints())
    mEvaluationValue = std::numeric_limits<C_FLOAT64>::infinity();

  return mEvaluationValue;
}

bool COptMethodSA::initialize()
{
  cleanup();

  if (!COptMethod::initialize()) return false;

  mTemperature = getValue< C_FLOAT64 >("Start Temperature");
  mCoolingFactor = getValue< C_FLOAT64 >("Cooling Factor");
  mTolerance = getValue< C_FLOAT64 >("Tolerance");

  mpRandom =
    CRandom::createGenerator((CRandom::Type) getValue< unsigned C_INT32 >("Random Number Generator"),
                             getValue< unsigned C_INT32 >("Seed"));

  if (mpCallBack)
    mhTemperature =
      mpCallBack->addItem("Current Temperature",
                          mTemperature);

  mBestValue = std::numeric_limits<C_FLOAT64>::infinity();
  mContinue = true;

  mVariableSize = mpOptItem->size();

  mCurrent.resize(mVariableSize);
  mStep.resize(mVariableSize);
  mAccepted.resize(mVariableSize);

  return true;
}

unsigned C_INT32 COptMethodSA::getMaxLogVerbosity() const
{
  return 1;
}
