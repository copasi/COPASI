/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapTask.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/05 15:14:52 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CLyapTask class.
 */

#include <string>

#include "copasi.h"

#include "CLyapTask.h"
#include "CLyapProblem.h"
#include "CLyapMethod.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include  "CopasiDataModel/CCopasiDataModel.h"

#define XXXX_Reporting

CLyapTask::CLyapTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::lyap, pParent),
    mTimeSeriesRequested(true),
    mTimeSeries(),
    mpLyapProblem(NULL),
    mpLyapMethod(NULL),
    mLocalExponents(),
    mExponents()
{
  mpProblem = new CLyapProblem(this);
  mpMethod =
    CLyapMethod::createLyapMethod(CCopasiMethod::lyapWolf,
                                  (CLyapProblem *) mpProblem);
  this->add(mpMethod, true);

  initObjects();
}

CLyapTask::~CLyapTask()
{
  cleanup();
}

void CLyapTask::cleanup()
{}

void CLyapTask::initObjects()
{
  mExponents.resize(3);
  mExpRef1 = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
             (addObjectReference("Exp1", mExponents.array()[0], CCopasiObject::ValueDbl));
  assert(mExpRef1);
  mExpRef2 = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
             (addObjectReference("Exp2", mExponents.array()[1], CCopasiObject::ValueDbl));
  assert(mExpRef2);
  mExpRef3 = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
             (addObjectReference("Exp3", mExponents.array()[2], CCopasiObject::ValueDbl));
  assert(mExpRef3);

  mLocalExponents.resize(3);
  mLocExpRef1 = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
                (addObjectReference("LocExp1", mLocalExponents.array()[0], CCopasiObject::ValueDbl));
  assert(mLocExpRef1);
  mLocExpRef2 = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
                (addObjectReference("LocExp2", mLocalExponents.array()[1], CCopasiObject::ValueDbl));
  assert(mLocExpRef2);
  mLocExpRef3 = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
                (addObjectReference("LocExp3", mLocalExponents.array()[2], CCopasiObject::ValueDbl));
  assert(mLocExpRef3);
}

bool CLyapTask::initialize(const OutputFlag & of,
                           std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpLyapProblem = dynamic_cast<CLyapProblem *>(mpProblem);
  assert(mpLyapProblem);

  mpLyapMethod = dynamic_cast<CLyapMethod *>(mpMethod);
  assert(mpLyapMethod);

  mpLyapMethod->setProblem(mpLyapProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  mLocalExponents.resize(mpLyapProblem->getExponentNumber());
  mExponents.resize(mpLyapProblem->getExponentNumber());
  //TODO: set reference
  mExpRef1->setReference(mExponents.array()[0]);
  mLocExpRef1->setReference(mLocalExponents.array()[0]);

  if (!CCopasiTask::initialize(of, pOstream)) success = false;
  mTimeSeriesRequested = mpLyapProblem->timeSeriesRequested();

  return success;
}

bool CLyapTask::process(const bool & useInitialValues)
{
  if (useInitialValues)
    mpLyapProblem->getModel()->applyInitialValues();

  output(COutputInterface::BEFORE);

  //  bool flagProceed = true;
  mPercentage = 0;

  if (mpCallBack)
    {
      mpCallBack->setName("performing lyapunov exponent calculation...");
      C_FLOAT64 hundred = 100;
      mhProcess = mpCallBack->addItem("Completion",
                                      CCopasiParameter::DOUBLE,
                                      &mPercentage,
                                      &hundred);
    }

  try
    {
      mpLyapMethod->calculate();
    }
  catch (CCopasiException Exception)
    {
      //mpLyapProblem->getModel()->setState(*mpCurrentState);
      mpLyapProblem->getModel()->refreshConcentrations();

      output(COutputInterface::DURING);

      if (mpCallBack) mpCallBack->finish(mhProcess);
      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack) mpCallBack->finish(mhProcess);

  output(COutputInterface::AFTER);

  return true;
}

bool CLyapTask::restore()
{
  bool success = CCopasiTask::restore();

  if (mUpdateModel)
    {
      CModel * pModel = mpProblem->getModel();

      //TODO
      //pModel->setState(*mpCurrentState);
      pModel->applyAssignments();
      pModel->setInitialState(pModel->getState());
    }

  return success;
}

bool CLyapTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (!CLyapMethod::isValidSubType(Type)) return false;
  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);
  mpMethod =
    CLyapMethod::createLyapMethod(Type,
                                  (CLyapProblem *) mpProblem);
  this->add(mpMethod, true);

  return true;
}

const CTimeSeries & CLyapTask::getTimeSeries() const
{return mTimeSeries;}

void CLyapTask::output(const COutputInterface::Activity & activity)
{
  if (mDoOutput != NO_OUTPUT)
    CCopasiDataModel::Global->output(activity);

  if (mTimeSeriesRequested && mDoOutput == OUTPUT_COMPLETE)
    switch (activity)
      {
      case COutputInterface::BEFORE:
        //TODO
        mTimeSeries.init(10 /*mpLyapProblem->getStepNumber()*/, mpProblem->getModel());
        break;

      case COutputInterface::DURING:
        mTimeSeries.add();
        break;

      case COutputInterface::AFTER:
        mTimeSeries.finish();
        break;
      }
}

bool CLyapTask::methodCallback(const C_FLOAT64 & percentage)
{
  output(COutputInterface::DURING);

  mPercentage = percentage;
  if (mpCallBack)
    {
      return mpCallBack->progress(mhProcess);
    }
  return true;
}
