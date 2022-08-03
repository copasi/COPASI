// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"
#include <copasi/model/CEvent.h>

#include "CAnalyticsTask.h"
#include "CAnalyticsProblem.h"
//#include "CAnalyticsMethod.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CCallback.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/analytics/CStatistics.h"
#include "copasi/utilities/CMethodFactory.h"

CAnalyticsTask::CAnalyticsTask(const CDataContainer * pParent,
                               const CTaskEnum::Task & type):
  CTrajectoryTask(pParent, type),
  mpAnalyticsProblem(NULL),
  mIndex(-1),
  mStatVal(),
  mStatTime(),
  pStats(NULL),
  pStatsTime(NULL),
  mpSelectedObject(NULL),
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
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::deterministic, this);
  initObjects();
}

CAnalyticsTask::CAnalyticsTask(const CAnalyticsTask & src,
                               const CDataContainer * pParent):
  CTrajectoryTask(src, pParent),
  mpAnalyticsProblem(NULL),
  mIndex(-1),
  mStatVal(),
  mStatTime(),
  pStats(NULL),
  pStatsTime(NULL),
  mpSelectedObject(NULL),
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
}

CAnalyticsTask::~CAnalyticsTask()
{
  pdelete(mpEventCallback);
}

void CAnalyticsTask::initObjects()
{
  addObjectReference("Period", mPeriod, CDataObject::ValueDbl);
  addObjectReference("Average Period", mAveragePeriod, CDataObject::ValueDbl);
  addObjectReference("Last Period", mLastPeriod, CDataObject::ValueDbl);
  addObjectReference("Periodicity", mPeriodicity, CDataObject::ValueInt);
  addObjectReference("Last Frequency", mLastFreq, CDataObject::ValueDbl);
  addObjectReference("Frequency", mFreq, CDataObject::ValueDbl);
  addObjectReference("Average Frequency", mAverageFreq, CDataObject::ValueDbl);
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
      mpSelectedObject = mpAnalyticsProblem->getSelectedObject();

      // 1) Retrieve the corresponding CMathObject:
      CMathObject * pMathObject = mpContainer->getMathObject(mpSelectedObject);

      // 2) Determine the index of the Object in the state:
      CMathObject * pFirstStateObject =
        mpContainer->getMathObject(mpContainer->getState(false).array());
      mIndex = pMathObject - pFirstStateObject;

      // 3) Get the rate object:
      CMathObject * pRateObject =
        mpContainer->getMathObject(mpContainer->getRate(false).array()) + mIndex;

      std::string rateObjectName = pRateObject->getCN();

      //--- ETTORE end -----

      std::stringstream expression;
      expression << "<" << rateObjectName << "> "
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

  /* Clear the vectors storing the time points recorded in the previous run of the task. */
  mValues.clear();
  mTimes.clear();
  mValuesSeries.clear();

  /* Retrieve initial value of the selected variablevariables.
   * 'false' means I want the entire state, not the reduced one. */
  if (mIndex >= 0) // If an object was selected...
    {
      mValues.push_back(*(mpContainer->getState(false).array() + mIndex));
      mTimes.push_back(*mpContainerStateTime);
      mValuesSeries.push_back(mpContainer->getState(false));
    }

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

  //output(COutputInterface::BEFORE);

  bool flagProceed = true;
  mProgressFactor = 100.0 / (MaxDuration + mpAnalyticsProblem->getOutputStartTime());
  mProgressValue = 0;

  if (mProcessReport)
    {
      mProcessReport.setName("performing simulation...");
      mProgressMax = 100.0;
      mhProgress = mProcessReport.addItem("Completion",
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

  finish();

  return true;
}

void CAnalyticsTask::finish()
{
  if (mProcessReport) mProcessReport.finishItem(mhProgress);

  //ComputeRequestedStatistics
  if (mIndex >= 0) // If an object was selected...
    {
      mValues.push_back(*(mpContainer->getState(false).array() + mIndex));
      mTimes.push_back(*mpContainerStateTime);
      computeSelectedStatistics(mValues, mTimes);
    }

  output(COutputInterface::DURING);
  output(COutputInterface::AFTER);
}

void CAnalyticsTask::computeSelectedStatistics(std::vector< C_FLOAT64 > mValues, std::vector< C_FLOAT64 > mTimes)
{

  std::cout << mStatVal << std::endl;
  std::cout << mStatTime << std::endl;
  std::cout << "----------" << std::endl;

  int StatsIndex = mValues.size() - 1;

  mStatVal = mValues[mValues.size() - 1];
  mStatTime = mTimes[mTimes.size() - 1];

  for (int i = mValues.size() - 1; i >= 0 ; i--)
    {
      if (mpAnalyticsProblem->isPositiveDirection())     //Looking for minimum
        {
          if (mValues[i] <= (mStatVal * (1 + 1e-6)))
            {
              mStatVal = mValues[i];
              mStatTime = mTimes[i];
              StatsIndex = i;
            }
        }
      else                                               //Looking for maximum
        {
          if (mValues[i] >= (mStatVal * (1 - 1e-6)))
            {
              mStatVal = mValues[i];
              mStatTime = mTimes[i];
              StatsIndex = i;
            }
        }
    }

  // The state of the system and the corresponding time
  // when the stats was reached...
  mpContainer->setState(mValuesSeries[StatsIndex]);

  //std::cout << "Variable's value: " << *(mpContainer->getState(false).array() + mIndex) << std::endl;
  //std::cout << "System's time: " << (*mpContainerStateTime) << std::endl;

  std::cout << mStatVal << std::endl;
  std::cout << mStatTime << std::endl;
  std::cout << "==================================" << std::endl;

  // Create the new Statistics object to be added to the model.

  std::string nameStats = "";
  std::string nameStatsTime = "";

  if (mpAnalyticsProblem->isPositiveDirection())
    nameStats = "min(" + mpSelectedObject->getObjectDisplayName() + ")";
  else
    nameStats = "max(" + mpSelectedObject->getObjectDisplayName() + ")";

  nameStatsTime = "Time of " + nameStats;

  const CDataContainer * pParent = this;
  const std::string & type = "Statistics";
  const unsigned C_INT32 & flag = CDataObject::ValueDbl;

  pdelete(pStats);
  pdelete(pStatsTime);
  //if (pStats) {delete pStats; pStats = 0;}
  //if (pStatsTime) {delete pStatsTime; pStatsTime = 0;}

  pStats = new CStatistics(nameStats, pParent, type, flag, mStatVal);
  pStatsTime = new CStatistics(nameStatsTime, pParent, type, flag, mStatTime);
}

bool CAnalyticsTask::restore()
{
  bool success = CCopasiTask::restore();

  removeEvent();

  return success;
}

// virtual
const CTaskEnum::Method * CAnalyticsTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::deterministic,
    CTaskEnum::Method::UnsetMethod
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
  if (mProcessReport)
    {
      mProgressValue = (*mpContainerStateTime - mStartTime) * mProgressFactor;

      if (!mProcessReport.progressItem(mhProgress))
        {
          mState = FINISH;
          mProceed = false;
        }
    }

  mpContainer->setState(mContainerState);
  mpContainer->updateSimulatedValues(mUpdateMoieties);

  // count the crossings
  ++mNumCrossings;

  //--- ETTORE start ---
  // I store the max / min of the variable and the corresponding times
  mValues.push_back(*(mpContainer->getState(false).array() + mIndex));
  mTimes.push_back(*mpContainerStateTime);
  mValuesSeries.push_back(mContainerState);
  //--- ETTORE end -----

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
                  mPeriod = *mpContainerStateTime - mStatesRing[i % RING_SIZE][mpContainer->getCountFixedEventTargets()];
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
                  mPeriod = *mpContainerStateTime - mStatesRing[i % RING_SIZE][mpContainer->getCountFixedEventTargets()];
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

      if (!std::isnan(mPreviousCrossingTime))
        {
          mLastPeriod = *mpContainerStateTime - mPreviousCrossingTime;
        }

      mLastFreq = 1 / mLastPeriod;

      //output(COutputInterface::DURING);

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
  const C_FLOAT64 * pTime = p1 + mpContainer->getCountFixedEventTargets();
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
