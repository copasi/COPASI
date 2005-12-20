/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryProblem.cpp,v $
   $Revision: 1.39 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/20 19:25:07 $
   End CVS Header */

/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <math.h>
#include <string>

#include "copasi.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h" 
//#include "model/CState.h"
#include "CopasiDataModel/CCopasiDataModel.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CTrajectoryProblem::CTrajectoryProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::timeCourse, pParent),
    mStepNumberSetLast(true)
{
  addParameter("StepNumber", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  addParameter("StepSize", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.01);
  addParameter("Duration", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
  addParameter("TimeSeriesRequested", CCopasiParameter::BOOL, (bool) true);
  addParameter("OutputStartTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);

  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CTrajectoryProblem::CTrajectoryProblem(const CTrajectoryProblem & src,
                                       const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mStepNumberSetLast(src.mStepNumberSetLast)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CTrajectoryProblem::~CTrajectoryProblem()
{DESTRUCTOR_TRACE;}

bool CTrajectoryProblem::elevateChildren()
{
  // If we have an old COPASI file "Duration" is not set
  // but we can fix that.
  if (getDuration() == 1.0) // the default
    setDuration(getStepSize() * (C_FLOAT64) getStepNumber());

  return true;
}

void CTrajectoryProblem::initObjects()
{
  const_cast<CCopasiObject *>(getParameter("StepNumber")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this,
                    (bool (CTrajectoryProblem::*)(const C_INT32 &)) &CTrajectoryProblem::setStepNumber);

  const_cast<CCopasiObject *>(getParameter("StepSize")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this, &CTrajectoryProblem::setStepSize);

  const_cast<CCopasiObject *>(getParameter("Duration")
                              ->getObject(CCopasiObjectName("Reference=Value")))
  ->setUpdateMethod(this, &CTrajectoryProblem::setDuration);
}

/**
 * Set the number of time steps the trajectory method should integrate.
 * @param "const unsigned C_INT32 &" stepNumber
 */
bool CTrajectoryProblem::setStepNumber(const unsigned C_INT32 & stepNumber)
{
  setValue("StepNumber", stepNumber);
  mStepNumberSetLast = true;
  return sync();
}

/**
 * Retrieve the number of time steps the trajectory method should integrate.
 * @return "const unsigned C_INT32 &" stepNumber
 */
const unsigned C_INT32 & CTrajectoryProblem::getStepNumber() const
  {return * getValue("StepNumber").pUINT;}

/**
 * Set the size a integration step the trajectory method should do.
 * @param "const C_FLOAT64 &" stepSize
 */
bool CTrajectoryProblem::setStepSize(const C_FLOAT64 & stepSize)
{
  setValue("StepSize", stepSize);
  mStepNumberSetLast = false;
  return sync();
}

/**
 * Retrieve the size a integration step the trajectory method should do.
 * @return "const C_FLOAT64 &" stepSize
 */
const C_FLOAT64 & CTrajectoryProblem::getStepSize() const
  {return * getValue("StepSize").pDOUBLE;}

/**
 * Set the end time.
 * @param "const C_FLOAT64 &" duration
 * @parem bool success
 */
bool CTrajectoryProblem::setDuration(const C_FLOAT64 & duration)
{
  setValue("Duration", duration);
  return sync();
}

/**
 * Retrieve the end time.
 * @return "const C_FLOAT64 &" duration
 */
const C_FLOAT64 & CTrajectoryProblem::getDuration() const
  {return * getValue("Duration").pDOUBLE;}

void CTrajectoryProblem::setOutputStartTime(const C_FLOAT64 & startTime)
{
  setValue("OutputStartTime", startTime);
}

const C_FLOAT64 & CTrajectoryProblem::getOutputStartTime() const
  {return * getValue("OutputStartTime").pDOUBLE;}

void CTrajectoryProblem::setTimeSeriesRequested(bool flag)
{
  setValue("TimeSeriesRequested", flag);
}

bool CTrajectoryProblem::timeSeriesRequested() const
  {return * getValue("TimeSeriesRequested").pBOOL;}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */
void CTrajectoryProblem::load(CReadConfig & configBuffer,
                              CReadConfig::Mode C_UNUSED(mode))
{
  C_FLOAT64 dbl;
  unsigned C_INT32 uint;

  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = CCopasiDataModel::Global->getModel();
      configBuffer.getVariable("EndTime", "C_FLOAT64",
                               & dbl,
                               CReadConfig::LOOP);
      setValue("Duration", dbl);
      configBuffer.getVariable("Points", "C_INT32",
                               & uint);
      setValue("StepNumber", uint);
      mStepNumberSetLast = true;

      sync();
    }
}

/**
 * This function synchronizes step size and number
 */
bool CTrajectoryProblem::sync()
{
  bool success = true;

  C_FLOAT64 Tmp = getDuration();
  C_FLOAT64 StepSize = getStepSize();
  C_FLOAT64 StepNumber = (C_FLOAT64) getStepNumber();

  if (mStepNumberSetLast)
    {
      StepSize = Tmp / (C_FLOAT64) getStepNumber();

      /* Assure that the step size is not to small for machine accuracy */
      if (fabs(StepSize) < 100 * DBL_EPSILON * fabs(getDuration()))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTrajectoryProblem + 3, StepSize);

          StepSize = 100 * DBL_EPSILON * fabs(getDuration());
          /* Assure that the step size has the appropriate sign. */
          StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
          StepNumber = fabs(ceil(Tmp / StepSize));
        }
    }
  else
    {
      if (fabs(StepSize) < 100 * DBL_EPSILON * fabs(getDuration()))
        {
          CCopasiMessage(CCopasiMessage::WARNING,
                         MCTrajectoryProblem + 3, StepSize);

          StepSize = 100 * DBL_EPSILON * fabs(getDuration());

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

          success = false;
        }

      /* Assure that the step size has the appropriate sign. */
      StepSize = (Tmp < 0.0) ? - fabs(StepSize) : fabs(StepSize);
    }

  setValue("StepSize", StepSize);
  setValue("StepNumber", (unsigned C_INT32) StepNumber);

  return success;
}
