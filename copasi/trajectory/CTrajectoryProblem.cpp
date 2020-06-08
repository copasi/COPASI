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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include <limits.h>
#include <cmath>
#include <string>

#include "copasi/copasi.h"
#include "CTrajectoryProblem.h"
#include "CTrajectoryTask.h"
#include "CTimeSeries.h"
#include "copasi/model/CModel.h"
//#include "copasi/model/CState.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CParameterEstimationUtils.h"

//this constructor is only used by derived classes to provide a different task type
CTrajectoryProblem::CTrajectoryProblem(const CTaskEnum::Task & type,
                                       const CDataContainer * pParent):
  CCopasiProblem(type, pParent),
  mpAutomaticStepSize(NULL),
  mpDuration(NULL),
  mpStepSize(NULL),
  mpStepNumber(NULL),
  mpTimeSeriesRequested(NULL),
  mpOutputStartTime(NULL),
  mpOutputEvent(NULL),
  mpStartInSteadyState(NULL),
  mpUseValues(NULL),
  mpValueString(NULL),
  mStepNumberSetLast(true)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Default constructor.
 */
CTrajectoryProblem::CTrajectoryProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::timeCourse, pParent),
  mpAutomaticStepSize(NULL),
  mpDuration(NULL),
  mpStepSize(NULL),
  mpStepNumber(NULL),
  mpTimeSeriesRequested(NULL),
  mpOutputStartTime(NULL),
  mpOutputEvent(NULL),
  mpStartInSteadyState(NULL),
  mpUseValues(NULL),
  mpValueString(NULL),
  mStepNumberSetLast(true)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CTrajectoryProblem::CTrajectoryProblem(const CTrajectoryProblem & src,
                                       const CDataContainer * pParent):
  CCopasiProblem(src, pParent),
  mpAutomaticStepSize(NULL),
  mpDuration(NULL),
  mpStepSize(NULL),
  mpStepNumber(NULL),
  mpTimeSeriesRequested(NULL),
  mpOutputStartTime(NULL),
  mpOutputEvent(NULL),
  mpStartInSteadyState(NULL),
  mpUseValues(NULL),
  mpValueString(NULL),
  mStepNumberSetLast(src.mStepNumberSetLast)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CTrajectoryProblem::~CTrajectoryProblem()
{DESTRUCTOR_TRACE;}

void CTrajectoryProblem::initializeParameter()
{
  mpAutomaticStepSize = assertParameter("AutomaticStepSize", CCopasiParameter::Type::BOOL, (bool) false);
  mpStepNumber = assertParameter("StepNumber", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100);
  mpStepSize = assertParameter("StepSize", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.01);
  mpDuration = assertParameter("Duration", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 1.0);
  mpTimeSeriesRequested = assertParameter("TimeSeriesRequested", CCopasiParameter::Type::BOOL, (bool) true);
  mpOutputStartTime = assertParameter("OutputStartTime", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.0);
  mpOutputEvent = assertParameter("Output Event", CCopasiParameter::Type::BOOL, (bool) false);
  mpStartInSteadyState = assertParameter("Start in Steady State", CCopasiParameter::Type::BOOL, false);
  mpUseValues = assertParameter("Use Values", CCopasiParameter::Type::BOOL, false);
  mpValueString = assertParameter("Values", CCopasiParameter::Type::STRING, std::string(""));
}

bool CTrajectoryProblem::elevateChildren()
{
  // If we have an old COPASI file "Duration" is not set
  // but we can fix that.
  if (*mpDuration == 1.0) // the default
    setDuration(*mpStepSize * (C_FLOAT64) *mpStepNumber);

  return true;
}

void CTrajectoryProblem::initObjects()
{}

/**
 * Set the number of time steps the trajectory method should integrate.
 * @param "const unsigned C_INT32 &" stepNumber
 */
void CTrajectoryProblem::setStepNumber(const unsigned C_INT32 & stepNumber)
{
  if (*mpStepNumber == stepNumber)
    return;

  *mpStepNumber = stepNumber;
  mStepNumberSetLast = true;
  sync();

  return;
}

/**
 * Retrieve the number of time steps the trajectory method should integrate.
 * @return "const unsigned C_INT32 &" stepNumber
 */
const unsigned C_INT32 & CTrajectoryProblem::getStepNumber() const
{return *mpStepNumber;}

/**
 * Set the size a integration step the trajectory method should do.
 * @param "const C_FLOAT64 &" stepSize
 */
void CTrajectoryProblem::setStepSize(const C_FLOAT64 & stepSize)
{
  if (*mpStepSize == stepSize)
    return;

  *mpStepSize = stepSize;
  mStepNumberSetLast = false;
  sync();

  return;
}

/**
 * Retrieve the size a integration step the trajectory method should do.
 * @return "const C_FLOAT64 &" stepSize
 */
const C_FLOAT64 & CTrajectoryProblem::getStepSize() const
{return *mpStepSize;}

bool CTrajectoryProblem::getAutomaticStepSize() const
{
  return *mpAutomaticStepSize && !*mpUseValues;
}

void CTrajectoryProblem::setAutomaticStepSize(const bool & automaticStepSize)
{
  *mpAutomaticStepSize = automaticStepSize;
}

/**
 * Set the end time.
 * @param "const C_FLOAT64 &" duration
 * @parem bool success
 */
void CTrajectoryProblem::setDuration(const C_FLOAT64 & duration)
{
  *mpDuration = duration;
  sync();

  return;
}

/**
 * Retrieve the end time.
 * @return "const C_FLOAT64 &" duration
 */
const C_FLOAT64 & CTrajectoryProblem::getDuration() const
{return *mpDuration;}

void CTrajectoryProblem::setOutputStartTime(const C_FLOAT64 & startTime)
{
  *mpOutputStartTime = startTime;
}

const C_FLOAT64 & CTrajectoryProblem::getOutputStartTime() const
{return *mpOutputStartTime;}

void CTrajectoryProblem::setTimeSeriesRequested(bool flag)
{
  *mpTimeSeriesRequested = flag;
}

bool CTrajectoryProblem::timeSeriesRequested() const
{return *mpTimeSeriesRequested;}

void CTrajectoryProblem::setOutputEvent(const bool & outputEvent)
{
  *mpOutputEvent = outputEvent;
}

const bool & CTrajectoryProblem::getOutputEvent() const
{return *mpOutputEvent;}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */
void CTrajectoryProblem::load(CReadConfig & configBuffer,
                              CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      configBuffer.getVariable("EndTime", "C_FLOAT64",
                               mpDuration,
                               CReadConfig::LOOP);
      configBuffer.getVariable("Points", "C_INT32",
                               mpStepNumber);
      mStepNumberSetLast = true;

      sync();
    }
}


void CTrajectoryProblem::printResult(std::ostream* pStream) const
{
  if (!pStream)
    return;

  if (!timeSeriesRequested())
    {
      *pStream << " No time series requested, please change problem settings." << std::endl;
    }

  const CTrajectoryTask* pTask = dynamic_cast<const CTrajectoryTask*>(getObjectParent());

  if (!pTask)
    return;

  pTask->getTimeSeries().save(*pStream);
}

/**
 * This function synchronizes step size and number
 */
bool CTrajectoryProblem::sync()
{
  bool success = true;

  if (fabs(*mpDuration) < std::numeric_limits< C_FLOAT64 >::min())
    return success;

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
                         MCTrajectoryProblem + 3, StepSize);

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
                         MCTrajectoryProblem + 3, StepSize);

          StepSize = 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() * fabs(*mpDuration);

          /* Assure that the step size has the appropriate sign. */
          StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
        }

      StepNumber = fabs(ceil(Tmp / StepSize));

      /* Protect against overflow */
      if ((C_FLOAT64) ULONG_MAX < StepNumber)
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTrajectoryProblem + 2, StepNumber);

          StepNumber = (C_FLOAT64) ULONG_MAX;
          StepSize = Tmp / StepNumber;
        }

      /* Assure that the step size has the appropriate sign. */
      StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
    }

  *mpStepSize = StepSize;
  *mpStepNumber = (unsigned C_INT32) StepNumber;

  return success;
}

void CTrajectoryProblem::setStartInSteadyState(bool flag)
{
  *mpStartInSteadyState = flag;
}

bool CTrajectoryProblem::getStartInSteadyState() const
{
  if (mpStartInSteadyState)
    return *mpStartInSteadyState;
  else
    return false;
}

void CTrajectoryProblem::setValues(const std::string& values)
{
  *mpValueString = values;
}

void CTrajectoryProblem::setValues(const std::vector<C_FLOAT64>& values)
{
  std::stringstream str;

for (C_FLOAT64 value : values)
    {
      str << value;
    }

  setValues(str.str());
}

std::set<C_FLOAT64> CTrajectoryProblem::getValues() const
{
  std::set<C_FLOAT64> result;

  std::vector<std::string> elems;
  ResultParser::split(*mpValueString, std::string(",; |\n\t\r"), elems);

for (std::string & number : elems)
    {
      result.insert(ResultParser::saveToDouble(number));
    }

  return result;
}

const std::string& CTrajectoryProblem::getValueString() const
{
  return *mpValueString;
}

void CTrajectoryProblem::setUseValues(bool flag)
{
  *mpUseValues = flag;
}

bool CTrajectoryProblem::getUseValues() const
{
  return *mpUseValues;
}
