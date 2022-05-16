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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTSSAProblem class.
 *  This class describes the time scale separation analysis problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 */

#include <cmath>
#include <string>
#include <limits.h>

#include "copasi/copasi.h"
#include "CTSSAProblem.h"
#include "CTSSATask.h"
#include "copasi/model/CModel.h"
//#include "copasi/model/CState.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

/**
 *  Default constructor.
 */
CTSSAProblem::CTSSAProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::tssAnalysis, pParent),
  mpDuration(NULL),
  mpStepSize(NULL),
  mpStepNumber(NULL),
  mpTimeSeriesRequested(NULL),
  mpOutputStartTime(NULL),
  mStepNumberSetLast(true)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTSSAProblem &" src
 */
CTSSAProblem::CTSSAProblem(const CTSSAProblem & src,
                           const CDataContainer * pParent):
  CCopasiProblem(src, pParent),
  mpDuration(NULL),
  mpStepSize(NULL),
  mpStepNumber(NULL),
  mpTimeSeriesRequested(NULL),
  mpOutputStartTime(NULL),
  mStepNumberSetLast(src.mStepNumberSetLast)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CTSSAProblem::~CTSSAProblem()
{DESTRUCTOR_TRACE;}

void CTSSAProblem::initializeParameter()
{
  mpStepNumber = assertParameter("StepNumber", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100);
  mpStepSize = assertParameter("StepSize", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.01);
  mpDuration = assertParameter("Duration", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 1.0);
  mpTimeSeriesRequested = assertParameter("TimeSeriesRequested", CCopasiParameter::Type::BOOL, (bool) true);
  mpOutputStartTime = assertParameter("OutputStartTime", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.0);
}

bool CTSSAProblem::elevateChildren()
{
  // If we have an old COPASI file "Duration" is not set
  // but we can fix that.
  if (*mpDuration == 1.0) // the default
    setDuration(*mpStepSize * (C_FLOAT64) *mpStepNumber);

  removeParameter("Deuflhard Tolerance");

  return true;
}

void CTSSAProblem::initObjects()
{}

/**
 * Set the number of time steps the trajectory method should integrate.
 * @param "const unsigned C_INT32 &" stepNumber
 */
void CTSSAProblem::setStepNumber(const unsigned C_INT32 & stepNumber)
{
  *mpStepNumber = stepNumber;
  mStepNumberSetLast = true;
  sync();

  return;
}

/**
 * Retrieve the number of time steps the trajectory method should integrate.
 * @return "const unsigned C_INT32 &" stepNumber
 */
const unsigned C_INT32 & CTSSAProblem::getStepNumber() const
{return *mpStepNumber;}

/**
 * Set the size a integration step the trajectory method should do.
 * @param "const C_FLOAT64 &" stepSize
 */
void CTSSAProblem::setStepSize(const C_FLOAT64 & stepSize)
{
  *mpStepSize = stepSize;
  mStepNumberSetLast = false;
  sync();

  return;
}

/**
 * Retrieve the size a integration step the trajectory method should do.
 * @return "const C_FLOAT64 &" stepSize
 */
const C_FLOAT64 & CTSSAProblem::getStepSize() const
{return *mpStepSize;}

/**
 * Set the end time.
 * @param "const C_FLOAT64 &" duration
 * @parem bool success
 */
void CTSSAProblem::setDuration(const C_FLOAT64 & duration)
{
  *mpDuration = duration;
  sync();

  return;
}

/**
 * Retrieve the end time.
 * @return "const C_FLOAT64 &" duration
 */
const C_FLOAT64 & CTSSAProblem::getDuration() const
{return *mpDuration;}

void CTSSAProblem::setOutputStartTime(const C_FLOAT64 & startTime)
{
  *mpOutputStartTime = startTime;
}

const C_FLOAT64 & CTSSAProblem::getOutputStartTime() const
{return *mpOutputStartTime;}

void CTSSAProblem::setTimeSeriesRequested(bool flag)
{
  *mpTimeSeriesRequested = flag;
}

bool CTSSAProblem::timeSeriesRequested() const
{return *mpTimeSeriesRequested;}

/**
 * This function synchronizes step size and number
 */
bool CTSSAProblem::sync()
{
  bool success = true;

  C_FLOAT64 Tmp = *mpDuration;
  C_FLOAT64 StepSize = *mpStepSize;
  C_FLOAT64 StepNumber = (C_FLOAT64) * mpStepNumber;

  if (mStepNumberSetLast)
    {
      StepSize = Tmp / (C_FLOAT64) * mpStepNumber;

      /* Assure that the step size is not to small for machine accuracy */
      if (fabs(StepSize) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 3, StepSize);

          StepSize = 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration);
          /* Assure that the step size has the appropriate sign. */
          StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
          StepNumber = fabs(ceil(Tmp / StepSize));
        }
    }
  else
    {
      if (fabs(StepSize) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 3, StepSize);

          StepSize = 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration);

          /* Assure that the step size has the appropriate sign. */
          StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
        }

      StepNumber = fabs(ceil(Tmp / StepSize));

      /* Protect against overflow */
      if ((C_FLOAT64) ULONG_MAX < StepNumber)
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 2, StepNumber);

          StepNumber = (C_FLOAT64) ULONG_MAX;
          StepSize = Tmp / StepNumber;

          success = false;
        }

      /* Assure that the step size has the appropriate sign. */
      StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
    }

  *mpStepSize = StepSize;
  *mpStepNumber = (unsigned C_INT32) StepNumber;

  if (!success) throw 1;

  return success;
}

void CTSSAProblem::printResult(std::ostream * ostream) const
{
  std::ostream & os = *ostream;

  const CDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);
  const CCopasiTask* mpTask =
    dynamic_cast<const CTSSATask *>(&const_cast<CDataModel*>(pDataModel)->getTaskList()->operator[]("Time Scale Separation Analysis"));

  if (!mpTask) return;

  const CCopasiMethod* mpMethod = mpTask->getMethod();

  this->print(&os);

  mpMethod->printResult(&os);
}
