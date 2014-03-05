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
#include "model/CMathModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include  "CopasiDataModel/CCopasiDataModel.h"

const unsigned int CCrossSectionTask::ValidMethods[] =
{
  CCopasiMethod::deterministic,
  CCopasiMethod::unset
};

CCrossSectionTask::CCrossSectionTask(const CCopasiContainer * pParent):
  CTrajectoryTask(CCopasiTask::crosssection, pParent),
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
  mpMethod = createMethod(CCopasiMethod::deterministic);
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
{}

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

  bool success = CTrajectoryTask::initialize(of, pOutputHandler, pOstream);

  mpTrajectoryMethod->setProblem(mpCrossSectionProblem);
  success &= mpMethod->isValidProblem(mpProblem);

  return success;
}

void CCrossSectionTask::createEvent()
{
  if (mpEvent != NULL) return;

  CModel* pModel = mpCrossSectionProblem->getModel();

  if (!mpCrossSectionProblem->getSingleObjectCN().empty())
    {
      int count = 0;
      std::string name = "__cutplane";

      while (pModel->getEvents().getIndex(name) != C_INVALID_INDEX)
        {
          std::stringstream str;
          str << "__cutplane" << ++count;
          name = str.str();
        }

      mpEvent = pModel->createEvent(name);
      mpEvent->setType(CEvent::CutPlane);

      std::stringstream expression;
      expression << "<" << mpCrossSectionProblem->getSingleObjectCN() << "> "
                 << (mpCrossSectionProblem->isPositiveDirection() ? std::string(" > ") : std::string(" < "))
                 << mpCrossSectionProblem->getThreshold();

      mpEvent ->setTriggerExpression(expression.str());
    }

  pModel->setCompileFlag();
  pModel->compileIfNecessary(NULL);
}

void CCrossSectionTask::removeEvent()
{
  // TODO: remove event
  if (mpEvent != NULL)
    {
      mpCrossSectionProblem->getModel()->removeEvent(mpEvent);
      mpEvent = NULL;
    }
}

bool CCrossSectionTask::process(const bool & useInitialValues)
{
  createEvent();

  processStart(useInitialValues);

  //this instructs the process queue to call back whenever an event is
  //executed
  // TODO CRITICAL Implement me!
  // mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(this, &EventCallBack);

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
      mOutputStartTime = *mpCurrentStateTime + mpCrossSectionProblem->getOutputStartTime();
      MaxDuration += mpCrossSectionProblem->getOutputStartTime();
    }
  else
    {
      mOutputStartTime = *mpCurrentStateTime;
    }

  const C_FLOAT64 EndTime = *mpCurrentStateTime + MaxDuration;

  mStartTime = *mpCurrentStateTime;

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
      while ((*mpCurrentStateTime < CompareEndTime) && flagProceed);
    }

  catch (int)
    {
      mpContainer->setState(mCurrentState);
      mpContainer->updateSimulatedValues(mUpdateMoieties);
      mpContainer->pushState();

      finish();
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTrajectoryMethod + 16);
    }

  catch (CCopasiException & Exception)
    {
      mpContainer->setState(mCurrentState);
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
  //reset call back
  // TODO CRITICAL Implement me!
  // mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(NULL, NULL);

  if (mpCallBack != NULL) mpCallBack->finishItem(mhProgress);

  output(COutputInterface::AFTER);
}

bool CCrossSectionTask::restore()
{
  bool success = CTrajectoryTask::restore();

  removeEvent();
  //reset call back
  // TODO CRITICAL Implement me!
  // mpCrossSectionProblem->getModel()->getMathModel()->getProcessQueue().setEventCallBack(NULL, NULL);

  return success;
}

const CState * CCrossSectionTask::getState()
{
  mpContainer->setState(mCurrentState);
  mpContainer->updateSimulatedValues(mUpdateMoieties);
  mpContainer->pushState();

  return & mpContainer->getModel().getState();
}

//static
void CCrossSectionTask::EventCallBack(void* pCSTask, CEvent::Type type)
{static_cast<CCrossSectionTask *>(pCSTask)->eventCallBack(type);}

void CCrossSectionTask::eventCallBack(CEvent::Type type)
{
  //  std::cout << "event call back: " << type << std::endl;

  //do progress reporting
  if (mpCallBack != NULL)
    {
      mProgressValue = (*mpCurrentStateTime - mStartTime) * mProgressFactor;

      if (!mpCallBack->progressItem(mhProgress))
        {
          mState = FINISH;
          mProceed = false;
        }
    }

  //do nothing else if the event is not representing a cut plane
  if (type != CEvent::CutPlane)
    return;

  mpContainer->setState(mCurrentState);
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
      else if (mpCrossSectionProblem->getFlagLimitOutTime() && *mpCurrentStateTime >= mOutputStartTime)
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
                              mCurrentState);

              if (tmp < mpCrossSectionProblem->getConvergenceOutTolerance())
                {
                  mPeriodicity = mStatesRingCounter - i;
                  mPeriod = *mpCurrentStateTime - mStatesRing[i % RING_SIZE][mpContainer->getTimeIndex()];
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
                              mCurrentState);

              if (tmp < mpCrossSectionProblem->getConvergenceTolerance())
                {
                  mPeriodicity = mStatesRingCounter - i;
                  mPeriod = *mpCurrentStateTime - mStatesRing[i % RING_SIZE][mpContainer->getTimeIndex()];
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
          mLastPeriod = *mpCurrentStateTime - mPreviousCrossingTime;
        }

      mLastFreq = 1 / mLastPeriod;

      output(COutputInterface::DURING);

      //check if the conditions for stopping are met
      //we don't have to check for maximum duration, this is done elsewhere
      if (mMaxNumCrossings > 0 && mNumCrossings >= mMaxNumCrossings)
        mState = FINISH;
    }

  //store state in ring buffer
  mStatesRing[mStatesRingCounter % RING_SIZE] = mCurrentState;
  mPreviousCrossingTime = *mpCurrentStateTime;
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
