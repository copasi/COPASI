// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"
#include <model/CEvent.h>

#include "CCrossSectionTask.h"
#include "CCrossSectionProblem.h"
//#include "CCrossSectionMethod.h"
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include "utilities/CCallback.h"
#include  "CopasiDataModel/CCopasiDataModel.h"

CCrossSectionTask::CCrossSectionTask(const CCopasiContainer * pParent,
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
  mpEvent(NULL),
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
  mpProblem = new CCrossSectionProblem(this);
  mpMethod = createMethod(CTaskEnum::deterministic);
  this->add(mpMethod, true);
}

CCrossSectionTask::CCrossSectionTask(const CCrossSectionTask & src,
                                     const CCopasiContainer * pParent):
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
  mpEvent(NULL),
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
  mpProblem =
    new CCrossSectionProblem(*static_cast< CCrossSectionProblem * >(src.mpProblem), this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  * mpMethod = * src.mpMethod;

  mpMethod->elevateChildren();

  this->add(mpMethod, true);
}

CCrossSectionTask::~CCrossSectionTask()
{
  pdelete(mpEventCallback);
}

void CCrossSectionTask::initObjects()
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

bool CCrossSectionTask::initialize(const OutputFlag & of,
                                   COutputHandler * pOutputHandler,
                                   std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpCrossSectionProblem = dynamic_cast<CCrossSectionProblem *>(mpProblem);
  assert(mpCrossSectionProblem);

  //init the ring buffer for the states
  mStatesRing.resize(RING_SIZE);
  mStatesRingCounter = 0;

  createEvent();

  bool success = CTrajectoryTask::initialize(of, pOutputHandler, pOstream);

  return success;
}

void CCrossSectionTask::createEvent()
{
  if (mpEvent != NULL) return;

  if (!mpCrossSectionProblem->getSingleObjectCN().empty())
    {
      CEvent Event("__cutplane", &mpContainer->getModel());
      Event.setType(CEvent::Callback);

      std::stringstream expression;
      expression << "<" << mpCrossSectionProblem->getSingleObjectCN() << "> "
                 << (mpCrossSectionProblem->isPositiveDirection() ? std::string(" > ") : std::string(" < "))
                 << mpCrossSectionProblem->getThreshold();

      Event.setTriggerExpression(expression.str());

      Event.compile(CObjectInterface::ContainerList());

      mpEvent = mpContainer->addEvent(Event);
    }

  setEventCallback(true);
}

void CCrossSectionTask::removeEvent()
{
  // reset call back of the cut plane event
  setEventCallback(false);

  if (mpEvent != NULL)
    {
      mpContainer->removeEvent(mpEvent);
      mpEvent = NULL;
    }
}

bool CCrossSectionTask::process(const bool & useInitialValues)
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

  bool flagProceed = true;
  mProgressFactor = 100.0 / (MaxDuration + mpCrossSectionProblem->getOutputStartTime());
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
      mpContainer->pushState();

      finish();
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpContainer->setState(mContainerState);
      mpContainer->updateSimulatedValues(mUpdateMoieties);
      mpContainer->pushState();

      finish();
      throw CCopasiException(Exception.getMessage());
    }

  finish();

  return true;
}

void CCrossSectionTask::finish()
{
  if (mpCallBack != NULL) mpCallBack->finishItem(mhProgress);

  output(COutputInterface::AFTER);
}

bool CCrossSectionTask::restore()
{
  bool success = CTrajectoryTask::restore();

  removeEvent();

  return success;
}

// virtual
const CTaskEnum::Method * CCrossSectionTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::deterministic,
    CTaskEnum::UnsetMethod
  };

  return ValidMethods;
}

const CState * CCrossSectionTask::getState()
{
  mpContainer->setState(mContainerState);
  mpContainer->updateSimulatedValues(mUpdateMoieties);
  mpContainer->pushState();

  return & mpContainer->getModel().getState();
}

void CCrossSectionTask::setEventCallback(const bool & set)
{
  if (set && mpEventCallback == NULL)
    {
      mpEventCallback = new CCallback< CCrossSectionTask >(this, &CCrossSectionTask::eventCallBack);
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

void CCrossSectionTask::eventCallBack(void * /* pData */, void * /* pCaller */)
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

              if (tmp < mpCrossSectionProblem->getConvergenceTolerance())
                {
                  mPeriodicity = mStatesRingCounter - i;
                  mPeriod = *mpContainerStateTime - mStatesRing[i % RING_SIZE][mpContainer->getTimeIndex()];
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
