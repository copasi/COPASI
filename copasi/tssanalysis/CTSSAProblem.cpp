// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CTSSAProblem.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2007/04/12 12:47:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTSSAProblem class.
 *  This class describes the time scale separation analysis problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 */

#include <math.h>
#include <string>

#include "copasi.h"
#include "CTSSAProblem.h"
#include "model/CModel.h"
//#include "model/CState.h"
#include "CopasiDataModel/CCopasiDataModel.h"

/**
 *  Default constructor.
 */
CTSSAProblem::CTSSAProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::timeCourse, pParent),
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
                           const CCopasiContainer * pParent):
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
  mpStepNumber =
    assertParameter("StepNumber", CCopasiParameter::UINT, (unsigned C_INT32) 100)->getValue().pUINT;
  mpStepSize =
    assertParameter("StepSize", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.01)->getValue().pDOUBLE;;
  mpDuration =
    assertParameter("Duration", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0)->getValue().pDOUBLE;;
  mpTimeSeriesRequested =
    assertParameter("TimeSeriesRequested", CCopasiParameter::BOOL, (bool) true)->getValue().pBOOL;
  mpOutputStartTime =
    assertParameter("OutputStartTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0)->getValue().pDOUBLE;;
}

bool CTSSAProblem::elevateChildren()
{
  // If we have an old COPASI file "Duration" is not set
  // but we can fix that.
  if (*mpDuration == 1.0) // the default
    setDuration(*mpStepSize * (C_FLOAT64) *mpStepNumber);

  return true;
}

void CTSSAProblem::initObjects()
{
  const_cast<CCopasiObject *>(getParameter("StepNumber")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this,
                    (void (CTSSAProblem::*)(const C_INT32 &)) &CTSSAProblem::setStepNumber);

  const_cast<CCopasiObject *>(getParameter("StepSize")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this, &CTSSAProblem::setStepSize);

  const_cast<CCopasiObject *>(getParameter("Duration")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this, &CTSSAProblem::setDuration);
}

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
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */
void CTSSAProblem::load(CReadConfig & configBuffer,
                        CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = CCopasiDataModel::Global->getModel();
      configBuffer.getVariable("EndTime", "C_FLOAT64",
                               mpDuration,
                               CReadConfig::LOOP);
      configBuffer.getVariable("Points", "C_INT32",
                               mpStepNumber);
      mStepNumberSetLast = true;

      sync();
    }
}

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
      if (fabs(StepSize) < 100 * DBL_EPSILON * fabs(*mpDuration))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 3, StepSize);

          StepSize = 100 * DBL_EPSILON * fabs(*mpDuration);
          /* Assure that the step size has the appropriate sign. */
          StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
          StepNumber = fabs(ceil(Tmp / StepSize));
        }
    }
  else
    {
      if (fabs(StepSize) < 100 * DBL_EPSILON * fabs(*mpDuration))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTSSAProblem + 3, StepSize);

          StepSize = 100 * DBL_EPSILON * fabs(*mpDuration);

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
