// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

/**
 *   CHybridNextReactionRKMethod
 *
 *   First approach to an hybrid algorithm. Gibson's Next Reaction method is
 *   combined with a RungeKutta numerical integrator.
 *
 *   File name: CHybridNextReactionRKMethod.h
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml-r.villa-bosch.de
 *
 *   Last change: 15, December 2004
 *
 *   (C) European Media Lab 2003.
 */

/* HEADER FILE ***************************************************************/
#include "copasi/copasi.h"

#include "CHybridNextReactionRKMethod.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/math/CMathReaction.h"

CHybridNextReactionRKMethod::CHybridNextReactionRKMethod(const CDataContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CHybridMethod(pParent, methodType, taskType)
{
  initializeParameter();
}

/**
 * Copy constructor.
 * @param const CHybridNextReactionRKMethod & src
 * @param const CDataContainer * pParent
 */
CHybridNextReactionRKMethod::CHybridNextReactionRKMethod(const CHybridMethod & src,
    const CDataContainer * pParent):
  CHybridMethod(src, pParent)
{
  initializeParameter();
}

void CHybridNextReactionRKMethod::initializeParameter()
{
  CCopasiParameter *pParm;

  assertParameter("Runge Kutta Stepsize", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) RUNGE_KUTTA_STEPSIZE);

  // Check whether we have a method with the old parameter names
  if ((pParm = getParameter("HYBRID.MaxSteps")) != NULL)
    {
      if ((pParm = getParameter("HYBRID.RungeKuttaStepsize")) != NULL)
        {
          setValue("Runge Kutta Stepsize", pParm->getValue< C_FLOAT64 >());
          removeParameter("HYBRID.RungeKuttaStepsize");
        }
    }
}

/**
 *   Integrates the deterministic reactions of the system over the specified
 *   time interval.
 *
 *   @param ds A C_FLOAT64 specifying the stepsize.
 */
void CHybridNextReactionRKMethod::integrateDeterministicPart(C_FLOAT64 dt)
{
  C_FLOAT64 integrationTime = 0.0;
  CHybridStochFlag * react = NULL;

  // This method uses a 4th order RungeKutta-method to integrate the deterministic part of the system. Maybe a better numerical method (adaptive stepsize, lsoda, ...) should be introduced here later on

  while ((dt - integrationTime) > mStepsize)
    {
      rungeKutta(mStepsize); // for the deterministic part of the system
      integrationTime += mStepsize;
    }

  rungeKutta(dt - integrationTime);

  mpContainer->updateSimulatedValues(false);

  return;
}

/**
 *   Does one 4th order RungeKutta step to integrate the system
 *   numerically.
 *
 *   @param dt A C_FLOAT64 specifying the stepsize
 *   @param result A reference to a vector, into which the result, that is
 *                 the increment vector, will be written
 */
void CHybridNextReactionRKMethod::rungeKutta(C_FLOAT64 dt)
{
  size_t i;

  CVector< C_FLOAT64 > CurrentState = mCurrentState;

  /* k1 step: k1 = dt*f(x(n)) */
  calculateDerivative(temp); // systemState == x(n)

  for (i = 0; i < mNumVariableMetabs; i++)
    {
      k1[i] = temp[i] * dt;
    }

  /* k2 step: k2 = dt*f(x(n) + k1/2) */
  for (i = 0; i < mNumVariableMetabs; i++)
    {
      temp[i] = k1[i] / 2.0 + CurrentState[i];
    }

  mCurrentState = temp;
  calculateDerivative(temp); // systemState == x(n) + k1/2

  for (i = 0; i < mNumVariableMetabs; i++)
    {
      k2[i] = temp[i] * dt;
    }

  /* k3 step: k3 = dt*f(x(n) + k2/2) */
  for (i = 0; i < mNumVariableMetabs; i++)
    {
      temp[i] = k2[i] / 2.0 + CurrentState[i];
    }

  mCurrentState = temp;
  calculateDerivative(temp); // systemState == x(n) + k2/2

  for (i = 0; i < mNumVariableMetabs; i++)
    {
      k3[i] = temp[i] * dt;
    }

  /* k4 step: k4 = dt*f(x(n) + k3); */
  for (i = 0; i < mNumVariableMetabs; i++)
    {
      temp[i] = k3[i] + CurrentState[i];
    }

  mCurrentState = temp;
  calculateDerivative(temp); // systemState == x(n) + k3

  for (i = 0; i < mNumVariableMetabs; i++)
    {
      k4[i] = temp[i] * dt;
    }

  /* Find next position: x(n+1) = x(n) + 1/6*(k1 + 2*k2 + 2*k3 + k4)  */
  for (i = 0; i < mNumVariableMetabs; i++)
    {
      temp[i] = CurrentState[i] + (1.0 / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
    }

  mCurrentState = temp;

  return;
}

void CHybridNextReactionRKMethod::start()
{
  CHybridMethod::start();

  temp.resize(mNumVariableMetabs);
  k1.resize(mNumVariableMetabs);
  k2.resize(mNumVariableMetabs);
  k3.resize(mNumVariableMetabs);
  k4.resize(mNumVariableMetabs);

  mStepsize = getValue< C_FLOAT64 >("Runge Kutta Stepsize");

  /* Runge Kutta Stepsize */
  if (mStepsize <= 0.0)
    {
      // Runge Kutta Stepsize must be positive
      CCopasiMessage(CCopasiMessage::ERROR, MCTrajectoryMethod + 13);
    }
}
