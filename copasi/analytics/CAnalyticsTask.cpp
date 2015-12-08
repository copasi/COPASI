// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * CAnalyticsTask class.
 *
 * This class implements a cross section task.
 */

#include <string>
#include <sstream>
#include <cmath>

#include "copasi.h"
#include <model/CEvent.h>

#include "CAnalyticsTask.h"
#include "CAnalyticsProblem.h"
//#include "CAnalyticsMethod.h"
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCallback.h"
#include  "CopasiDataModel/CCopasiDataModel.h"

CAnalyticsTask::CAnalyticsTask(const CCopasiContainer * pParent,
                                     const CTaskEnum::Task & type):
  CTrajectoryTask(pParent, type),
  mpAnalyticsProblem(NULL),
  mStartTime(0.0),
  mNumCrossings(0),
  mOutputStartNumCrossings(0),
  mMaxNumCrossings(std::numeric_limits< size_t >::max()),
  mhProgress(C_INVALID_INDEX),
  mProgressMax(1),
  mProgressValue(0),
  mProgressFactor(1),
  mpEvent(NULL),
  mpEventCallback(NULL),
  mState(CAnalyticsTask::TRANSIENT),
  mStatesRing(),
  mStatesRingCounter(0),
  mPreviousCrossingTime(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mPeriod(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mAveragePeriod(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mLastPeriod(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mPeriodicity(-1),
  mLastFreq(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mFreq(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mAverageFreq(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{
  initObjects();
  mpProblem = new CAnalyticsProblem(this);
  mpMethod = createMethod(CTaskEnum::deterministic);
  this->add(mpMethod, true);
}

CAnalyticsTask::CAnalyticsTask(const CAnalyticsTask & src,
                                     const CCopasiContainer * pParent):
  CTrajectoryTask(src, pParent),
  mpAnalyticsProblem(NULL),
  mStartTime(0.0),
  mNumCrossings(0),
  mOutputStartNumCrossings(0),
  mMaxNumCrossings(std::numeric_limits< size_t >::max()),
  mhProgress(C_INVALID_INDEX),
  mProgressMax(1),
  mProgressValue(0),
  mProgressFactor(1),
  mpEvent(NULL),
  mpEventCallback(NULL),
  mState(CAnalyticsTask::TRANSIENT),
  mStatesRing(),
  mStatesRingCounter(0),
  mPreviousCrossingTime(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mPeriod(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mAveragePeriod(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mLastPeriod(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mPeriodicity(-1),
  mLastFreq(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mFreq(std::numeric_limits< C_FLOAT64 >::quiet_NaN()),
  mAverageFreq(std::numeric_limits< C_FLOAT64 >::quiet_NaN())
{
  initObjects();
  mpProblem =
    new CAnalyticsProblem(*static_cast< CAnalyticsProblem * >(src.mpProblem), this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  * mpMethod = * src.mpMethod;

  mpMethod->elevateChildren();

  this->add(mpMethod, true);
}

CAnalyticsTask::~CAnalyticsTask()
{
  pdelete(mpEventCallback);
}

void CAnalyticsTask::initObjects()
{
  addObjectReference("Period", mPeriod, CCopasiObject::ValueDbl);
  addObjectReference("Average Period", mAveragePeriod, CCopasiObject::ValueDbl);
  addObjectReference("Last Period", mLastPeriod, CCopasiObject::ValueDbl);
  addObjectReference("Periodicity", mPeriodicity, CCopasiObject::ValueInt);
  addObjectReference("Last Frequency", mLastFreq, CCopasiObject::ValueDbl);
  addObjectReference("Frequency", mFreq, CCopasiObject::ValueDbl);
  addObjectReference("Average Frequency", mAverageFreq, CCopasiObject::ValueDbl);
}

#define RING_SIZE 16

bool CAnalyticsTask::initialize(const OutputFlag & of,
                                   COutputHandler * pOutputHandler,
                                   std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpAnalyticsProblem = dynamic_cast<CAnalyticsProblem *>(mpProblem);
  assert(mpAnalyticsProblem);

  //init the ring buffer for the states
  mStatesRing.resize(RING_SIZE);
  mStatesRingCounter = 0;

  createEvent();

  bool success = CTrajectoryTask::initialize(of, pOutputHandler, pOstream);

  return success;
}


//--- ETTORE --- This creates the event that will trigger the callback functiuon
// so that a snapshot of the system will be taken at that time.
void CAnalyticsTask::createEvent()
{
  if (mpEvent != NULL) return;

  if (!mpAnalyticsProblem->getSingleObjectCN().empty())
    {
      CEvent Event("__cutplane", &mpContainer->getModel());
      Event.setType(CEvent::Callback);
      Event.setPersistentTrigger(true);
      Event.setDelayAssignment(false);

      //--- ETTORE start ---
      // I need to retrieve the rate-object of the object selected by the user.
      //
      // Stefan's suggestion:
      //
      // 0) Retrieve object selected by the user
      const CCopasiObject * pSelectedObject = mpAnalyticsProblem->getSelectedObject();

      // 1) Retrieve the corresponding CMathObject:
      CMathObject * pMathObject = mpContainer->getMathObject(pSelectedObject);

      // 2) Determine the index of the Object in the state:
      CMathObject * pFirstStateObject =
          mpContainer->getMathObject(mpContainer->getState(false).array());
      size_t Index = pMathObject - pFirstStateObject;

      // 3) Get the rate object:
      CMathObject * pRateObject =
          mpContainer->getMathObject(mpContainer->getRate(false).array()) + Index;

      std::string rateObjectName = pRateObject->getCN();

      //--- ETTORE end -----

      std::stringstream expression;
      expression << "<" << rateObjectName << "> "
      //expression << "<" << mpAnalyticsProblem->getSingleObjectCN() << "> "
                 << (mpAnalyticsProblem->isPositiveDirection() ? std::string(" > ") : std::string(" < "))
                 << mpAnalyticsProblem->getThreshold();

      Event.setTriggerExpression(expression.str());

      Event.compile(CObjectInterface::ContainerList());

      mpEvent = mpContainer->addAnalysisEvent(Event);
    }

  setEventCallback(true);
}

void CAnalyticsTask::removeEvent()
{
  // reset call back of the cut plane event
  setEventCallback(false);

  if (mpEvent != NULL)
    {
      if (!mpContainer->removeAnalysisEvent(mpEvent)) fatalError();
    }
}

bool CAnalyticsTask::process(const bool & useInitialValues)
{
  processStart(useInitialValues);

  mPreviousCrossingTime = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mPeriod = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mAveragePeriod = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mLastPeriod = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mPeriodicity = -1;
  mLastFreq = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mFreq = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mAverageFreq = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  //--- ETTORE start ---
  /* Retrieve initial value of variables.
   * 'false' means I want the entire state, not the reduced one. */
  //mInitialState = mpContainer->getState(false);
  //--- ETTORE end -----

  C_FLOAT64 MaxDuration = mpAnalyticsProblem->getDuration();

  //the output starts only after "outputStartTime" has passed
  if (mpAnalyticsProblem->getFlagLimitOutTime())
    {
      mOutputStartTime = *mpContainerStateTime + mpAnalyticsProblem->getOutputStartTime();
      MaxDuration += mpAnalyticsProblem->getOutputStartTime();
    }
  else
    {
      mOutputStartTime = *mpContainerStateTime;
    }

  const C_FLOAT64 EndTime = *mpContainerStateTime + MaxDuration;

  mStartTime = *mpContainerStateTime;

  // It suffices to reach the end time within machine precision
  C_FLOAT64 CompareEndTime = mOutputStartTime - 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());

  if (mpAnalyticsProblem->getFlagLimitCrossings())
    mMaxNumCrossings = mpAnalyticsProblem->getCrossingsLimit();
  else
    mMaxNumCrossings = 0;

  if (mpAnalyticsProblem->getFlagLimitOutCrossings())
    mOutputStartNumCrossings = mpAnalyticsProblem->getOutCrossingsLimit();
  else
    mOutputStartNumCrossings = 0;

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  mProgressFactor = 100.0 / (MaxDuration + mpAnalyticsProblem->getOutputStartTime());
  mProgressValue = 0;

  if (mpCallBack != NULL)
    {
      mpCallBack->setName("performing simulation...");
      mProgressMax = 100.0;
      mhProgress = mpCallBack->addItem("Completion",
                                       mProgressValue,
                                       &mProgressMax);
    }

  mState = TRANSIENT;
  mStatesRingCounter = 0;

  mNumCrossings = 0;

  try
    {
      do
        {
          flagProceed &= processStep(EndTime);
        }
      while ((*mpContainerStateTime < CompareEndTime) && flagProceed);
    }

  catch (int)
    {
      mpContainer->setState(mContainerState);
      mpContainer->updateSimulatedValues(mUpdateMoieties);
      mpContainer->updateTransientDataValues();
      mpContainer->pushAllTransientValues();

      finish();
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpContainer->setState(mContainerState);
      mpContainer->updateSimulatedValues(mUpdateMoieties);
      mpContainer->updateTransientDataValues();
      mpContainer->pushAllTransientValues();

      finish();
      throw CCopasiException(Exception.getMessage());
    }

  //--- ETTORE start ---
  // Add something here to deal with situations in which there are no max or min found.

  //if (mNumCrossings == 0)
  //  {
  //    mNumCrossings = 1;
  //    mFinalState = mpContainer->getState(false);

      // Now retrieve the value of the specific variables from initial and final states.
      // TO DO
  //    const CObjectInterface *obj = mpContainer->getObjectFromCN(mpAnalyticsProblem->getSingleObjectCN());


      //CModel & pModel = mpContainer->getModel();
      //pModel->getObject(CCopasiObjectName())
      //const CObjectInterface * final = mpContainer->getObjectFromCN(mpAnalyticsProblem->getSingleObjectCN());
      
      // Compare initial and final value for variable.
      // TO DO
      
      // Push the result of teh comparison to the output
      // TO DO

  //  }
  //--- ETTORE end -----

  finish();

  return true;
}

void CAnalyticsTask::finish()
{
  if (mpCallBack != NULL) mpCallBack->finishItem(mhProgress);

  output(COutputInterface::AFTER);
}

bool CAnalyticsTask::restore()
{
  bool success = CTrajectoryTask::restore();

  removeEvent();

  return success;
}

// virtual
const CTaskEnum::Method * CAnalyticsTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::deterministic,
    CTaskEnum::UnsetMethod
  };

  return ValidMethods;
}

void CAnalyticsTask::setEventCallback(const bool & set)
{
  if (set && mpEventCallback == NULL)
    {
      mpEventCallback = new CCallback< CAnalyticsTask >(this, &CAnalyticsTask::eventCallBack);
    }

  if (mpEvent != NULL)
    {
      if (set)
        {
          mpEvent->setCallback(mpEventCallback);
        }
      else
        {
          mpEvent->setCallback(NULL);
        }
    }
}

void CAnalyticsTask::eventCallBack(void * /* pData */, void * /* pCaller */)
{
  //  std::cout << "event call back: " << type << std::endl;

  //do progress reporting
  if (mpCallBack != NULL)
    {
      mProgressValue = (*mpContainerStateTime - mStartTime) * mProgressFactor;

      if (!mpCallBack->progressItem(mhProgress))
        {
          mState = FINISH;
          mProceed = false;
        }
    }

  mpContainer->setState(mContainerState);
  mpContainer->updateSimulatedValues(mUpdateMoieties);

  // count the crossings
  ++mNumCrossings;

  // now check if we can transition to the main state
  if (mState == TRANSIENT)
    {
      // if output is not delayed by time and not delayed by number of crossings
      // and also not delayed by convergence
      // output is started immediately
      if (!mpAnalyticsProblem->getFlagLimitOutCrossings() &&
          !mpAnalyticsProblem->getFlagLimitOutTime() &&
          !mpAnalyticsProblem->getFlagLimitOutConvergence())
        {
          mState = MAIN;
        }
      else if (mpAnalyticsProblem->getFlagLimitOutTime() && *mpContainerStateTime >= mOutputStartTime)
        {
          mState = MAIN;
        }
      else if (mpAnalyticsProblem->getFlagLimitOutCrossings() && mNumCrossings >= mOutputStartNumCrossings)
        {
          mState = MAIN;
        }
      else if (mpAnalyticsProblem->getFlagLimitOutConvergence() &&
               mStatesRingCounter > 0)
        {
          int i;

          for (i = mStatesRingCounter - 1; i >= 0 && i >= ((int) mStatesRingCounter) - RING_SIZE; --i)
            {
              C_FLOAT64 tmp = relativeDifferenceOfStates(mStatesRing[i % RING_SIZE],
                              mContainerState);

              if (tmp < mpAnalyticsProblem->getConvergenceOutTolerance())
                {
                  mPeriodicity = mStatesRingCounter - i;
                  mPeriod = *mpContainerStateTime - mStatesRing[i % RING_SIZE][mpContainer->getTimeIndex()];
                  mFreq = 1 / mPeriod;
                  mAveragePeriod = mPeriod / ((C_FLOAT64)mPeriodicity);
                  mAverageFreq = 1 / mAveragePeriod;

                  mState = MAIN;
                  break;
                }

              //std::cout << i << "  " << tmp     << std::endl;
            }
        }

      if (mState == MAIN)
        {
          mStatesRingCounter = 0;
          mNumCrossings = 1;
        }
    }

  if (mState == MAIN)
    {
      //check for convergence (actually for the occurrence of similar states)
      if (mStatesRingCounter > 0)
        {
          int i;

          for (i = mStatesRingCounter - 1; i >= 0 && i >= ((int) mStatesRingCounter) - RING_SIZE; --i)
            {
              C_FLOAT64 tmp = relativeDifferenceOfStates(mStatesRing[i % RING_SIZE],
                              mContainerState);

              if (tmp < mpAnalyticsProblem->getConvergenceTolerance())
                {
                  mPeriodicity = mStatesRingCounter - i;
                  mPeriod = *mpContainerStateTime - mStatesRing[i % RING_SIZE][mpContainer->getTimeIndex()];
                  mFreq = 1 / mPeriod;
                  mAveragePeriod = mPeriod / ((C_FLOAT64)mPeriodicity);
                  mAverageFreq = 1 / mAveragePeriod;

                  if (mpAnalyticsProblem->getFlagLimitConvergence())
                    mState = FINISH;

                  break;
                }

              //std::cout << "MAIN" << i << "  " << tmp     << std::endl;
            }
        }

      if (!isnan(mPreviousCrossingTime))
        {
          mLastPeriod = *mpContainerStateTime - mPreviousCrossingTime;
        }

      mLastFreq = 1 / mLastPeriod;

      output(COutputInterface::DURING);

      //check if the conditions for stopping are met
      //we don't have to check for maximum duration, this is done elsewhere
      if (mMaxNumCrossings > 0 && mNumCrossings >= mMaxNumCrossings)
        mState = FINISH;
    }

  //store state in ring buffer
  mStatesRing[mStatesRingCounter % RING_SIZE] = mContainerState;
  mPreviousCrossingTime = *mpContainerStateTime;
  ++mStatesRingCounter;
}

C_FLOAT64 CAnalyticsTask::relativeDifferenceOfStates(const CVectorCore< C_FLOAT64 > & s1,
    const CVectorCore< C_FLOAT64 > & s2)
{
  if (s1.size() != s2.size())
    {
      return std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }

  C_FLOAT64 ret = 0;

  const C_FLOAT64 * p1 = s1.array();
  const C_FLOAT64 * p1End = p1 + s1.size();
  const C_FLOAT64 * pTime = p1 + mpContainer->getTimeIndex();
  const C_FLOAT64 * p2 = s2.array();

  for (; p1 != p1End; ++p1, ++p2)
    {
      // We skip the time variable
      if (p1 == pTime)
        {
          continue;
        }

      ret += (*p1 != *p2) ? pow((*p1 - *p2) / (fabs(*p1) + fabs(*p2)), 2) : 0.0;
    }

  return 2.0 * sqrt(ret);
}
