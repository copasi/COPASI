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
CTrajectoryProblem::CTrajectoryProblem():
    mpModel(NULL),
    mStepNumberSetLast(true),
    mpInitialState(NULL),
    mpEndState(NULL)
{
  CONSTRUCTOR_TRACE;
  if (mpModel)
    mpInitialState = mpModel->getInitialState();
}

CTrajectoryProblem::CTrajectoryProblem(CModel * pmodel,
                                       C_FLOAT64 starttime, C_FLOAT64 endtime,
                                       unsigned C_INT32 stepnumber):
    mpModel(pmodel),
    mStepNumber(stepnumber),
    mStepNumberSetLast(true),
    mStartTime(starttime),
    mEndTime(endtime),
    mpInitialState(NULL),
    mpEndState(NULL)
{
  if (mpModel)
    mpInitialState = mpModel->getInitialState();
  sync();
}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryProblem &" src
 */
CTrajectoryProblem::CTrajectoryProblem(const CTrajectoryProblem & src):
    mpModel(src.mpModel),
    mStepNumber(src.mStepNumber),
    mStepSize(src.mStepSize),
    mStepNumberSetLast(src.mStepNumberSetLast),
    mStartTime(src.mStartTime),
    mEndTime(src.mEndTime),
    mpInitialState(src.mpInitialState),
    mpEndState(src.mpEndState)
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
void CTrajectoryProblem::setModel(CModel * pModel) {mpModel = pModel;}

/**
 * Retrieve the model the problem is dealing with.
 * @return "CModel *" pModel
 */
CModel * CTrajectoryProblem::getModel() const {return mpModel;}

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
  if (mpInitialState)
    mpInitialState->setTime(mStartTime);

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
 * @param "const CState *" pInitialState
 */
void CTrajectoryProblem::setInitialState(CState * pInitialState)
{
  mpInitialState = pInitialState;
  setStartTime(mpInitialState->getTime());
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState *" pInitialState
 */
const CState * CTrajectoryProblem::getInitialState() const
  {return mpInitialState;}

/**
 * Set the end state of the problem.
 * @param "const CState *" pEndState
 */
void CTrajectoryProblem::setEndState(const CState * pEndState)
{mpEndState = pEndState;}

/**
 * Retrieve the end state of the problem.
 * @return "const CState *" pEndState
 */
const CState * CTrajectoryProblem::getEndState() const
  {return mpEndState;}

/**
 * Load a trajectory problem
 * @param "CReadConfig &" configBuffer
 */
void CTrajectoryProblem::load(CReadConfig & configBuffer,
                              CReadConfig::Mode mode)
{
  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = Copasi->Model;
      configBuffer.getVariable("EndTime", "C_FLOAT64",
                               (void *) & mEndTime,
                               CReadConfig::LOOP);
      configBuffer.getVariable("Points", "C_INT32",
                               (void *) & mStepNumber);
      mStepNumberSetLast = true;
      mStartTime = 0.0;
      sync();
      mpInitialState = mpModel->getInitialState();
    }
  else
    {
      std::string Tmp;

      configBuffer.getVariable("TrajectoryProblemModel", "string", &Tmp, mode);
      if (Tmp == Copasi->Model->getTitle())
        mpModel = Copasi->Model;
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
      mpInitialState = new CState;
      mpInitialState->load(configBuffer);
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
    mpInitialState->save(configBuffer);
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
