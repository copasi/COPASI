// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

/**
 * CCrossSectionTask class.
 *
 * This class implements a cross section task.
 */

#include <string>
#include <sstream>
#include <cmath>

#include "copasi/copasi.h"
#include <copasi/model/CEvent.h>

#include "CCrossSectionTask.h"
#include "CCrossSectionProblem.h"
//#include "CCrossSectionMethod.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"
#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CCallback.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CMethodFactory.h"

CCrossSectionTask::CCrossSectionTask(const CDataContainer * pParent,
                                     const CTaskEnum::Task & type):
  CTrajectoryTask(pParent, type),
  mpCrossSectionProblem(NULL),
  mStartTime(0.0),
  mNumCrossings(0),
  mOutputStartNumCrossings(0),
  mMaxNumCrossings(std::numeric_limits< size_t >::max()),
  mhProgress(C_INVALID_INDEX),
  mProgressMax(1),
  mProgressValue(0),
  mProgressFactor(1),
  mpDataEvent(NULL),
  mpMathEvent(NULL),
  mpEventCallback(NULL),
  mState(CCrossSectionTask::TRANSIENT),
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

CCrossSectionTask::CCrossSectionTask(const CCrossSectionTask & src,
                                     const CDataContainer * pParent):
  CTrajectoryTask(src, pParent),
  mpCrossSectionProblem(NULL),
  mStartTime(0.0),
  mNumCrossings(0),
  mOutputStartNumCrossings(0),
  mMaxNumCrossings(std::numeric_limits< size_t >::max()),
  mhProgress(C_INVALID_INDEX),
  mProgressMax(1),
  mProgressValue(0),
  mProgressFactor(1),
  mpDataEvent(NULL),
  mpMathEvent(NULL),
  mpEventCallback(NULL),
  mState(CCrossSectionTask::TRANSIENT),
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

CCrossSectionTask::~CCrossSectionTask()
{
  pdelete(mpEventCallback);
}

void CCrossSectionTask::initObjects()
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

bool CCrossSectionTask::initialize(const OutputFlag & of,
                                   COutputHandler * pOutputHandler,
                                   std::ostream * pOstream)
{
  if (!mpProblem || !mpMethod)
    return false;

  mpCrossSectionProblem = dynamic_cast<CCrossSectionProblem *>(mpProblem);

  if (!mpCrossSectionProblem)
    return false;

  //init the ring buffer for the states
  mStatesRing.resize(RING_SIZE);
  mStatesRingCounter = 0;

  createEvent();

  bool success = CTrajectoryTask::initialize(of, pOutputHandler, pOstream);

  return success;
}

void CCrossSectionTask::createEvent()
{
  if (mpMathEvent != NULL) return;

  if (!mpCrossSectionProblem->getSingleObjectCN().empty())
    {
      mpDataEvent = new CEvent("__cutplane", &mpContainer->getModel());
      mpDataEvent->setType(CEvent::Callback);
      mpDataEvent->setPersistentTrigger(true);
      mpDataEvent->setDelayAssignment(false);

      std::stringstream expression;
      expression << "<" << mpCrossSectionProblem->getSingleObjectCN() << "> "
                 << (mpCrossSectionProblem->isPositiveDirection() ? std::string(" > ") : std::string(" < "))
                 << mpCrossSectionProblem->getThreshold();

      mpDataEvent->setTriggerExpression(expression.str());
      mpDataEvent->compile(CObjectInterface::ContainerList());
      mpMathEvent = mpContainer->addAnalysisEvent(mpDataEvent);
    }

  setEventCallback(true);
}

void CCrossSectionTask::removeEvent()
{
  // reset call back of the cut plane event
  setEventCallback(false);

  if (mpMathEvent != NULL)
    {
      mpContainer->removeAnalysisEvent(mpMathEvent);
    }

  pdelete(mpDataEvent);

  signalMathContainerChanged();
}

bool CCrossSectionTask::process(const bool & useInitialValues)
{
  mpCrossSectionProblem = dynamic_cast< CCrossSectionProblem * >(mpProblem);

  if (!mpCrossSectionProblem)
    return false;

  processStart(useInitialValues);

  mPreviousCrossingTime = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mPeriod = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mAveragePeriod = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mLastPeriod = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mPeriodicity = -1;
  mLastFreq = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mFreq = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  mAverageFreq = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  C_FLOAT64 MaxDuration = mpCrossSectionProblem->getDuration();

  //the output starts only after "outputStartTime" has passed
  if (mpCrossSectionProblem->getFlagLimitOutTime())
    {
      mOutputStartTime = *mpContainerStateTime + mpCrossSectionProblem->getOutputStartTime();
      MaxDuration += mpCrossSectionProblem->getOutputStartTime();
    }
  else
    {
      mOutputStartTime = *mpContainerStateTime;
    }

  const C_FLOAT64 EndTime = *mpContainerStateTime + MaxDuration;

  mStartTime = *mpContainerStateTime;

  // It suffices to reach the end time within machine precision
  C_FLOAT64 CompareEndTime = mOutputStartTime - 100.0 * (fabs(EndTime) * std::numeric_limits< C_FLOAT64 >::epsilon() + std::numeric_limits< C_FLOAT64 >::min());

  if (mpCrossSectionProblem->getFlagLimitCrossings())
    mMaxNumCrossings = mpCrossSectionProblem->getCrossingsLimit();
  else
    mMaxNumCrossings = 0;

  if (mpCrossSectionProblem->getFlagLimitOutCrossings())
    mOutputStartNumCrossings = mpCrossSectionProblem->getOutCrossingsLimit();
  else
    mOutputStartNumCrossings = 0;

  output(COutputInterface::BEFORE);

  mProgressFactor = 100.0 / (MaxDuration + mpCrossSectionProblem->getOutputStartTime());
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

  bool Proceed;

  try
    {
      do
        {
          Proceed = processStep(EndTime);
        }
      while ((*mpContainerStateTime < CompareEndTime) && Proceed);
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

void CCrossSectionTask::finish()
{
  if (mProcessReport) mProcessReport.finishItem(mhProgress);

  output(COutputInterface::AFTER);
}

bool CCrossSectionTask::restore(const bool & updateModel)
{
  bool success = CCopasiTask::restore(updateModel);

  removeEvent();

  return success;
}

// virtual
const CTaskEnum::Method * CCrossSectionTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::deterministic,
    CTaskEnum::Method::UnsetMethod
  };

  return ValidMethods;
}

void CCrossSectionTask::setEventCallback(const bool & set)
{
  if (set && mpEventCallback == NULL)
    {
      mpEventCallback = new CCallback< CCrossSectionTask >(this, &CCrossSectionTask::eventCallBack);
    }

  if (mpMathEvent != NULL)
    {
      if (set)
        {
          mpMathEvent->setCallback(mpEventCallback);
        }
      else
        {
          mpMathEvent->setCallback(NULL);
        }
    }
}

void CCrossSectionTask::eventCallBack(void * /* pData */, void * /* pCaller */)
{
  //  std::cout << "event call back: " << type << std::endl;

  //do progress reporting
  if (mProcessReport)
    {
      mProgressValue = (*mpContainerStateTime - mStartTime) * mProgressFactor;

      if (!mProcessReport.progressItem(mhProgress))
        {
          mState = FINISH;
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
      if (!mpCrossSectionProblem->getFlagLimitOutCrossings() &&
          !mpCrossSectionProblem->getFlagLimitOutTime() &&
          !mpCrossSectionProblem->getFlagLimitOutConvergence())
        {
          mState = MAIN;
        }
      else if (mpCrossSectionProblem->getFlagLimitOutTime() && *mpContainerStateTime >= mOutputStartTime)
        {
          mState = MAIN;
        }
      else if (mpCrossSectionProblem->getFlagLimitOutCrossings() && mNumCrossings >= mOutputStartNumCrossings)
        {
          mState = MAIN;
        }
      else if (mpCrossSectionProblem->getFlagLimitOutConvergence() &&
               mStatesRingCounter > 0)
        {
          int i;

          for (i = mStatesRingCounter - 1; i >= 0 && i >= ((int) mStatesRingCounter) - RING_SIZE; --i)
            {
              C_FLOAT64 tmp = relativeDifferenceOfStates(mStatesRing[i % RING_SIZE],
                              mContainerState);

              if (tmp < mpCrossSectionProblem->getConvergenceOutTolerance())
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

              if (tmp < mpCrossSectionProblem->getConvergenceTolerance())
                {
                  mPeriodicity = mStatesRingCounter - i;
                  mPeriod = *mpContainerStateTime - mStatesRing[i % RING_SIZE][mpContainer->getCountFixedEventTargets()];
                  mFreq = 1 / mPeriod;
                  mAveragePeriod = mPeriod / ((C_FLOAT64)mPeriodicity);
                  mAverageFreq = 1 / mAveragePeriod;

                  if (mpCrossSectionProblem->getFlagLimitConvergence())
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

C_FLOAT64 CCrossSectionTask::relativeDifferenceOfStates(const CVectorCore< C_FLOAT64 > & s1,
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
