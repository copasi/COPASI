/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryProblem.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/03/17 22:19:33 $
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
    mStepNumber(1),
    mStepSize(1),
    mStepNumberSetLast(true),
    mStartTime(0),
    mEndTime(1),
    mInitialState(),
    mEndState()
{
  addParameter("StepNumber", CCopasiParameter::UINT, (unsigned C_INT32) 1);

  CONSTRUCTOR_TRACE;
  //  mInitialState.setModel(mpModel);
  //  mEndState.setModel(mpModel);

  //  if (mpModel)
  //    mInitialState = mpModel->getInitialState();

  //  mStartTime = mInitialState.getTime();
}

#ifdef XXXX
CTrajectoryProblem::CTrajectoryProblem(CModel * pmodel,
                                       C_FLOAT64 starttime, C_FLOAT64 endtime,
                                       unsigned C_INT32 stepnumber):
    mpModel(pmodel),
    mStepNumber(stepnumber),
    mStepNumberSetLast(true),
    mStartTime(starttime),
    mEndTime(endtime),
    mInitialState(),
    mEndState()
{
  mInitialState.setModel(mpModel);
  mEndState.setModel(mpModel);

  if (mpModel)
    mInitialState = mpModel->getInitialState();

  mInitialState.setTime(mStartTime);
  sync();
}
#endif // XXXX

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CTrajectoryProblem::CTrajectoryProblem(const CTrajectoryProblem & src,
                                       const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mStepNumber(src.mStepNumber),
    mStepSize(src.mStepSize),
    mStepNumberSetLast(src.mStepNumberSetLast),
    mStartTime(src.mStartTime),
    mEndTime(src.mEndTime),
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
  mStepNumber = stepNumber;
  mStepNumberSetLast = true;
  sync();
}

/**
 * Retrieve the number of time steps the trajectory method should integrate.
 * @return "const unsigned C_INT32 &" stepNumber
 */
const unsigned C_INT32 & CTrajectoryProblem::getStepNumber() const
  {return mStepNumber;}

/**
 * Set the size a integration step the trajectory method should do.
 * @param "const double &" stepSize
 */
void CTrajectoryProblem::setStepSize(const double & stepSize)
{
  mStepSize = stepSize;
  mStepNumberSetLast = false;
  sync();
}

/**
 * Retrieve the size a integration step the trajectory method should do.
 * @return "const double &" stepSize
 */
const double & CTrajectoryProblem::getStepSize() const {return mStepSize;}

/**
 * Set the start time.
 * @param "const double &" startTime
 */
void CTrajectoryProblem::setStartTime(const double & startTime)
{
  mStartTime = startTime;
  mInitialState.setTime(mStartTime);

  sync();
}

/**
 * Retrieve the start time.
 * @return "const double &" startTime
 */
const double & CTrajectoryProblem::getStartTime() const {return mStartTime;}

/**
 * Set the end time.
 * @param "const double &" endTime
 */
void CTrajectoryProblem::setEndTime(const double & endTime)
{
  mEndTime = endTime;
  sync();
}

/**
 * Retrieve the end time.
 * @return "const double &" endTime
 */
const double & CTrajectoryProblem::getEndTime() const {return mEndTime;}

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
                              CReadConfig::Mode mode)
{
  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = Copasi->pModel;
      configBuffer.getVariable("EndTime", "C_FLOAT64",
                               (void *) & mEndTime,
                               CReadConfig::LOOP);
      configBuffer.getVariable("Points", "C_INT32",
                               (void *) & mStepNumber);
      mStepNumberSetLast = true;
      mStartTime = 0.0;
      sync();
      mInitialState = mpModel->getInitialState();
    }
  else
    {
      std::string Tmp;

      configBuffer.getVariable("TrajectoryProblemModel", "string", &Tmp, mode);
      if (Tmp == Copasi->pModel->getTitle())
        mpModel = Copasi->pModel;
      else
        fatalError();

      configBuffer.getVariable("TrajectoryProblemStepNumber",
                               "C_INT32", &mStepNumber);
      configBuffer.getVariable("TrajectoryProblemStepSize",
                               "C_FLOAT64", &mStepSize);
      configBuffer.getVariable("TrajectoryProblemSetLast",
                               "bool", &mStepNumberSetLast);
      configBuffer.getVariable("TrajectoryProblemStartTime",
                               "C_FLOAT64", &mStartTime);
      configBuffer.getVariable("TrajectoryProblemEndTime",
                               "C_FLOAT64", &mEndTime);
      mInitialState.load(configBuffer);
    }
}

/**
 * Save a trajectory problem
 * @param "CWriteConfig &" configBuffer
 */
void CTrajectoryProblem::save(CWriteConfig & configBuffer) const
  {
    std::string Tmp = mpModel->getTitle();
    configBuffer.setVariable("TrajectoryProblemModel", "string", &Tmp);

    configBuffer.setVariable("TrajectoryProblemStepNumber",
                             "C_INT32", &mStepNumber);
    configBuffer.setVariable("TrajectoryProblemStepSize",
                             "C_FLOAT64", &mStepSize);
    configBuffer.setVariable("TrajectoryProblemSetLast",
                             "bool", &mStepNumberSetLast);
    configBuffer.setVariable("TrajectoryProblemStartTime",
                             "C_FLOAT64", &mStartTime);
    configBuffer.setVariable("TrajectoryProblemEndTime",
                             "C_FLOAT64", &mEndTime);
    mInitialState.save(configBuffer);
  }

/**
 * This function synchronizes step size and number
 */
void CTrajectoryProblem::sync()
{
  if (mStepNumberSetLast)
    mStepSize = (mEndTime - mStartTime) / (C_FLOAT64) mStepNumber;
  else
    {
      C_FLOAT64 Tmp = (mEndTime - mStartTime) / mStepSize;
      if (Tmp == (unsigned C_INT32) Tmp)
        mStepNumber = (unsigned C_INT32) Tmp;
      else
        mStepNumber = 1 + (unsigned C_INT32) Tmp;
    }
}
