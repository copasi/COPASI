/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryProblem.cpp,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/13 20:30:39 $
   End CVS Header */

/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <string>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CTrajectoryProblem.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CTrajectoryProblem::CTrajectoryProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::timeCourse, pParent),
    mStepNumberSetLast(true),
    mInitialState(),
    mEndState()
{
  addParameter("StepNumber", CCopasiParameter::UINT, (unsigned C_INT32) 100);
  addParameter("StepSize", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.01);
  addParameter("StartTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 0.0);
  addParameter("EndTime", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);

  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CTrajectoryProblem::CTrajectoryProblem(const CTrajectoryProblem & src,
                                       const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mStepNumberSetLast(src.mStepNumberSetLast),
    mInitialState(src.mInitialState),
    mEndState(src.mEndState)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CTrajectoryProblem::~CTrajectoryProblem()
{DESTRUCTOR_TRACE;}

/**
 * Set the model the problem is dealing with.
 * @param "CModel *" pModel
 */
bool CTrajectoryProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  mInitialState.setModel(mpModel);
  mEndState.setModel(mpModel);

  return true;
}

/**
 * Set the number of time steps the trajectory method should integrate.
 * @param "const unsigned C_INT32 &" stepNumber
 */
void CTrajectoryProblem::setStepNumber(const unsigned C_INT32 & stepNumber)
{
  setValue("StepNumber", stepNumber);
  mStepNumberSetLast = true;
  sync();
}

/**
 * Retrieve the number of time steps the trajectory method should integrate.
 * @return "const unsigned C_INT32 &" stepNumber
 */
const unsigned C_INT32 & CTrajectoryProblem::getStepNumber() const
  {return * (unsigned C_INT32 *) getValue("StepNumber");}

/**
 * Set the size a integration step the trajectory method should do.
 * @param "const C_FLOAT64 &" stepSize
 */
void CTrajectoryProblem::setStepSize(const C_FLOAT64 & stepSize)
{
  setValue("StepSize", stepSize);
  mStepNumberSetLast = false;
  sync();
}

/**
 * Retrieve the size a integration step the trajectory method should do.
 * @return "const C_FLOAT64 &" stepSize
 */
const C_FLOAT64 & CTrajectoryProblem::getStepSize() const
  {return * (C_FLOAT64 *) getValue("StepSize");}

/**
 * Set the start time.
 * @param "const C_FLOAT64 &" startTime
 */
void CTrajectoryProblem::setStartTime(const C_FLOAT64 & startTime)
{
  setValue("StartTime", startTime);
  mInitialState.setTime(startTime);

  sync();
}

/**
 * Retrieve the start time.
 * @return "const C_FLOAT64 &" startTime
 */
const C_FLOAT64 & CTrajectoryProblem::getStartTime() const
  {return * (C_FLOAT64 *) getValue("StartTime");}

/**
 * Set the end time.
 * @param "const C_FLOAT64 &" endTime
 */
void CTrajectoryProblem::setEndTime(const C_FLOAT64 & endTime)
{
  setValue("EndTime", endTime);
  sync();
}

/**
 * Retrieve the end time.
 * @return "const C_FLOAT64 &" endTime
 */
const C_FLOAT64 & CTrajectoryProblem::getEndTime() const
  {return * (C_FLOAT64 *) getValue("EndTime");}

/**
 * Set the initial state of the problem.
 * @param "const CState &" initialState
 */
void CTrajectoryProblem::setInitialState(const CState & initialState)
{
  mInitialState = initialState;
  setStartTime(mInitialState.getTime());
}

/**
 * Set the initial state of the problem.
 * @param "const CStateX &" initialState
 */
void CTrajectoryProblem::setInitialState(const CStateX & initialState)
{
  mInitialState = initialState;
  setStartTime(mInitialState.getTime());
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState *" pInitialState
 */
const CState & CTrajectoryProblem::getInitialState() const
  {return mInitialState;}

/**
 * Set the end state of the problem.
 * @param "const CState *" pEndState
 */
void CTrajectoryProblem::setEndState(const CState * pEndState)
{mEndState = *pEndState;}

/**
 * Set the end state of the problem.
 * @param "const CStateX *" pEndState
 */
void CTrajectoryProblem::setEndState(const CStateX * pEndState)
{mEndState = *pEndState;}

/**
 * Retrieve the end state of the problem.
 * @return "const CState &" pEndState
 */
const CState & CTrajectoryProblem::getEndState() const
  {return mEndState;}

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
      mpModel = Copasi->pModel;
      configBuffer.getVariable("EndTime", "C_FLOAT64",
                               & dbl,
                               CReadConfig::LOOP);
      setValue("EndTime", dbl);
      configBuffer.getVariable("Points", "C_INT32",
                               & uint);
      setValue("StepNumber", uint);
      mStepNumberSetLast = true;
      setValue("StartTime", (C_FLOAT64) 0.0);
      sync();
      mInitialState = mpModel->getInitialState();
    }
}

/**
 * This function synchronizes step size and number
 */
void CTrajectoryProblem::sync()
{
  C_FLOAT64 Tmp = getEndTime() - getStartTime();

  if (mStepNumberSetLast)
    setValue("StepSize", Tmp / (C_FLOAT64) getStepNumber());
  else
    {
      Tmp /= getStepSize();

      if (Tmp == (unsigned C_INT32) Tmp)
        setValue("StepNumber", (unsigned C_INT32) Tmp);
      else
        setValue("StepNumber", 1 + (unsigned C_INT32) Tmp);
    }
}
