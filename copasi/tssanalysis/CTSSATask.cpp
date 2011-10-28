// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CTSSATask.cpp,v $
//   $Revision: 1.14.2.3 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2011/10/28 14:01:29 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CTSSATask class.
 *
 * This class implements a time scale separation analysis task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting
 * methods are done when initialized.
 *
 */

#include <string>

#include "copasi.h"

#include "CTSSATask.h"
#include "CTSSAProblem.h"
#include "CTSSAMethod.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include  "CopasiDataModel/CCopasiDataModel.h"

#define XXXX_Reporting

bool tfle(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 <= d2);}

bool tfl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 < d2);}

bool tble(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 >= d2);}

bool tbl(const C_FLOAT64 & d1, const C_FLOAT64 & d2)
{return (d1 > d2);}

const unsigned int CTSSATask::ValidMethods[] =
{
  CCopasiMethod::tssILDM,
  CCopasiMethod::tssILDMModified,
#ifdef WITH_CSPMETHOD
  CCopasiMethod::tssCSP,
#endif // WITH_CSPMETHOD
  CCopasiMethod::unset
};

CTSSATask::CTSSATask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::tssAnalysis, pParent),
    mTimeSeriesRequested(true),
    mTimeSeries(),
    mpTSSAProblem(NULL),
    mpTSSAMethod(NULL),
    mpCurrentState(NULL),
    mpCurrentTime(NULL)
{
  mpProblem = new CTSSAProblem(this);
  mpMethod = createMethod(CCopasiMethod::tssILDM);
  this->add(mpMethod, true);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;
}

CTSSATask::CTSSATask(const CTSSATask & src,
                     const CCopasiContainer * pParent):
    CCopasiTask(src, pParent),
    mTimeSeriesRequested(src.mTimeSeriesRequested),
    mTimeSeries(),
    mpTSSAProblem(NULL),
    mpTSSAMethod(NULL),
    mpCurrentState(NULL),
    mpCurrentTime(NULL)
{
  mpProblem =
    new CTSSAProblem(*static_cast< CTSSAProblem * >(src.mpProblem), this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  * mpMethod = * src.mpMethod;
  mpMethod->elevateChildren();

  this->add(mpMethod, true);


  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;

}

CTSSATask::~CTSSATask()
{
  cleanup();
}

void CTSSATask::cleanup()
{
  pdelete(mpCurrentState);
}

bool CTSSATask::initialize(const OutputFlag & of,
                           COutputHandler * pOutputHandler,
                           std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpTSSAProblem = dynamic_cast<CTSSAProblem *>(mpProblem);
  assert(mpTSSAProblem);

  mpTSSAMethod = dynamic_cast<CTSSAMethod *>(mpMethod);
  assert(mpTSSAMethod);

  mpTSSAMethod->setProblem(mpTSSAProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  CCopasiParameter * pParameter = mpMethod->getParameter("Integrate Reduced Model");

  if (pParameter != NULL)
    mUpdateMoieties = *pParameter->getValue().pBOOL;
  else
    mUpdateMoieties = false;


  pdelete(mpCurrentState);
  mpCurrentState = new CState(mpTSSAProblem->getModel()->getState());
  mpCurrentTime = &mpCurrentState->getTime();

  // Handle the time series as a regular output.
  mTimeSeriesRequested = mpTSSAProblem->timeSeriesRequested();

  if (pOutputHandler != NULL)
    {
      if (mTimeSeriesRequested)
        {
          mTimeSeries.allocate(mpTSSAProblem->getStepNumber());
          pOutputHandler->addInterface(&mTimeSeries);
        }
      else
        {
          mTimeSeries.clear();
        }
    }

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  return success;
}

bool CTSSATask::process(const bool & useInitialValues)
{
  //*****

  processStart(useInitialValues);

  //*****

  C_FLOAT64 StepSize = mpTSSAProblem->getStepSize();
  C_FLOAT64 NextTimeToReport;

  const C_FLOAT64 EndTime = *mpCurrentTime + mpTSSAProblem->getDuration();
  const C_FLOAT64 StartTime = *mpCurrentTime;

  C_FLOAT64 StepNumber = (mpTSSAProblem->getDuration()) / StepSize;

  bool (*LE)(const C_FLOAT64 &, const C_FLOAT64 &);
  bool (*L)(const C_FLOAT64 &, const C_FLOAT64 &);

  if (StepSize < 0.0)
    {
      LE = &tble;
      L = &tbl;
    }
  else
    {
      LE = &tfle;
      L = &tfl;
    }

  size_t StepCounter = 1;

  C_FLOAT64 outputStartTime = mpTSSAProblem->getOutputStartTime();

  if (StepSize == 0.0 && mpTSSAProblem->getDuration() != 0.0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCTSSAProblem + 1, StepSize);
      return false;
    }

  output(COutputInterface::BEFORE);

  bool flagProceed = true;
  C_FLOAT64 handlerFactor = 100.0 / mpTSSAProblem->getDuration();

  C_FLOAT64 Percentage = 0;
  size_t hProcess;

  if (mpCallBack)
    {
      mpCallBack->setName("performing simulation...");
      C_FLOAT64 hundred = 100;
      hProcess = mpCallBack->addItem("Completion",
                                     Percentage,
                                     &hundred);
    }

  if ((*LE)(outputStartTime, *mpCurrentTime)) output(COutputInterface::DURING);

  try
    {
      do
        {
          // This is numerically more stable then adding
          // mpTSSAProblem->getStepSize().
          NextTimeToReport =
            StartTime + (EndTime - StartTime) * StepCounter++ / StepNumber;

          flagProceed &= processStep(NextTimeToReport);

          if (mpCallBack)
            {
              Percentage = (*mpCurrentTime - StartTime) * handlerFactor;
              flagProceed &= mpCallBack->progressItem(hProcess);
            }

          if ((*LE)(outputStartTime, *mpCurrentTime))
            {
              output(COutputInterface::DURING);
            }
        }
      while ((*L)(*mpCurrentTime, EndTime) && flagProceed);
    }

  catch (int)
    {
      mpTSSAProblem->getModel()->setState(*mpCurrentState);
      mpTSSAProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

      if ((*LE)(outputStartTime, *mpCurrentTime))
        {
          output(COutputInterface::DURING);
        }

      if (mpCallBack) mpCallBack->finishItem(hProcess);

      output(COutputInterface::AFTER);

      CCopasiMessage(CCopasiMessage::EXCEPTION, MCTSSAMethod + 4);
    }

  catch (CCopasiException Exception)
    {
      mpTSSAProblem->getModel()->setState(*mpCurrentState);
      mpTSSAProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

      if ((*LE)(outputStartTime, *mpCurrentTime))
        {
          output(COutputInterface::DURING);
        }

      if (mpCallBack) mpCallBack->finishItem(hProcess);

      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack) mpCallBack->finishItem(hProcess);

  output(COutputInterface::AFTER);

  return true;
}

void CTSSATask::processStart(const bool & useInitialValues)
{
  if (useInitialValues)
    mpTSSAProblem->getModel()->applyInitialValues();

  *mpCurrentState = mpTSSAProblem->getModel()->getState();

  mpTSSAMethod->setCurrentState(mpCurrentState);
  mpTSSAMethod->start(mpCurrentState);

  return;
}

bool CTSSATask::processStep(const C_FLOAT64 & nextTime)
{
  C_FLOAT64 CompareTime = nextTime - 100.0 * fabs(nextTime) * std::numeric_limits< C_FLOAT64 >::epsilon();

  if (*mpCurrentTime <= CompareTime)
    {
      do
        {
          mpTSSAMethod->step(nextTime - *mpCurrentTime);

          if (*mpCurrentTime > CompareTime) break;

          /* Here we will do conditional event processing */

          /* Currently this is correct since no events are processed. */
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTSSAMethod + 3);
        }
      while (true);

      mpTSSAProblem->getModel()->setState(*mpCurrentState);
      mpTSSAProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

      return true;
    }

  CompareTime = nextTime + 100.0 * fabs(nextTime) * std::numeric_limits< C_FLOAT64 >::epsilon();

  if (*mpCurrentTime >= CompareTime)
    {
      do
        {
          mpTSSAMethod->step(nextTime - *mpCurrentTime);

          if (*mpCurrentTime < CompareTime) break;

          /* Here we will do conditional event processing */

          /* Currently this is correct since no events are processed. */
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCTSSAMethod + 3);
        }
      while (true);

      mpTSSAProblem->getModel()->setState(*mpCurrentState);
      mpTSSAProblem->getModel()->updateSimulatedValues(mUpdateMoieties);

      return true;
    }

  // Current time is approximately nextTime;
  return false;
}

bool CTSSATask::restore()
{
  bool success = CCopasiTask::restore();

  if (mUpdateModel)
    {
      CModel * pModel = mpProblem->getModel();

      pModel->setState(*mpCurrentState);
      pModel->updateSimulatedValues(mUpdateMoieties);
      pModel->setInitialState(pModel->getState());
      pModel->updateInitialValues();
    }

  return success;
}

bool CTSSATask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (!isValidMethod(Type, ValidMethods)) return false;

  if (mpMethod->getSubType() == Type) return true;

  pdelete(mpMethod);
  mpMethod = createMethod(Type);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);

  return true;
}

// virtual
CCopasiMethod * CTSSATask::createMethod(const int & type) const
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  return CTSSAMethod::createMethod(Type);
}

CState * CTSSATask::getState()
{return mpCurrentState;}

const CTimeSeries & CTSSATask::getTimeSeries() const
{return mTimeSeries;}
