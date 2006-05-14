/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapTask.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/14 13:38:53 $
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
#include "report/CCopasiTimer.h"

#define XXXX_Reporting

//this is about the preliminary reporting. The first LYAP_NUM_REF exponents
//get an individual object reference. This will be obsolete when we have
//working annotated vectors
#define LYAP_NUM_REF 10

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
  unsigned C_INT32 i;

  mExponents.resize(LYAP_NUM_REF);
  mvExpRef.resize(LYAP_NUM_REF);

  mLocalExponents.resize(LYAP_NUM_REF);
  mvLocExpRef.resize(LYAP_NUM_REF);

  addVectorReference("Exponents", mExponents, CCopasiObject::ValueDbl);
  addVectorReference("Local exponents", mLocalExponents, CCopasiObject::ValueDbl);

  for (i = 0; i < LYAP_NUM_REF; ++i)
    {
      std::ostringstream sss;
      sss << "Exponent " << i + 1;
      mvExpRef[i] = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
                    (addObjectReference(sss.str(), mExponents.array()[i], CCopasiObject::ValueDbl));
      assert(mvExpRef[i]);

      std::ostringstream sss2;
      sss2 << "Local exponent " << i + 1;
      mvLocExpRef[i] = dynamic_cast<CCopasiObjectReference<C_FLOAT64> *>
                       (addObjectReference(sss2.str(), mLocalExponents.array()[i], CCopasiObject::ValueDbl));
      assert(mvLocExpRef[i]);
    }

  addObjectReference("Sum of exponents", mSumOfExponents, CCopasiObject::ValueDbl);
  addObjectReference("Sum of local exponents", mSumOfLocalExponents, CCopasiObject::ValueDbl);
  addObjectReference("Local divergence", mDivergence, CCopasiObject::ValueDbl);
  addObjectReference("Interval divergence", mIntervalDivergence, CCopasiObject::ValueDbl);
  addObjectReference("Average divergence", mAverageDivergence, CCopasiObject::ValueDbl);
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

  unsigned C_INT32 nnn;
  if (mpLyapProblem->getExponentNumber() > LYAP_NUM_REF)
    nnn = mpLyapProblem->getExponentNumber();
  else
    nnn = LYAP_NUM_REF;

  mLocalExponents.resize(nnn);
  mExponents.resize(nnn);

  //update object references because the object may have been
  //moved by the resize above
  unsigned C_INT32 i;
  for (i = 0; i < LYAP_NUM_REF; ++i)
    {
      mvExpRef[i]->setReference(mExponents.array()[i]);
      mvLocExpRef[i]->setReference(mLocalExponents.array()[i]);
    }

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

      calculationsBeforeOutput();
      output(COutputInterface::DURING);

      if (mpCallBack) mpCallBack->finish(mhProcess);
      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack) mpCallBack->finish(mhProcess);

  calculationsBeforeOutput();
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
  calculationsBeforeOutput();
  output(COutputInterface::DURING);

  mPercentage = percentage;
  if (mpCallBack)
    {
      return mpCallBack->progress(mhProcess);
    }
  return true;
}

void CLyapTask::calculationsBeforeOutput()
{
  mSumOfExponents = 0;
  mSumOfLocalExponents = 0;

  C_INT32 i, imax = mpLyapProblem->getExponentNumber();
  for (i = 0; i < imax; ++i)
    {
      mSumOfExponents += mExponents[i];
      mSumOfLocalExponents += mLocalExponents[i];
    }

  //calculate divergence
  CModel * pModel = mpLyapProblem->getModel();
  CMatrix<C_FLOAT64> jacobian;
  pModel->calculateElasticityMatrix(1e-6, 1e-12); //TODO configure parameters
  pModel->calculateJacobianX(jacobian);
  C_FLOAT64 sum = 0;
  imax = jacobian.numRows();
  for (i = 0; i < imax; ++i)
    sum += jacobian(i, i);
  //std::cout << sum << std::endl;
  mDivergence = sum;
}

void CLyapTask::printResult(std::ostream * ostream) const
  {
    std::ostream & os = *ostream;

    //     CCopasiTimeVariable CPUTime = const_cast<COptProblem *>(this)->mCPUTime.getElapsedTime();
    //     os << "    CPU Time [s]:\t"
    //     << CCopasiTimeVariable::LL2String(CPUTime.getSeconds(), 1) << "."
    //     << CCopasiTimeVariable::LL2String(CPUTime.getMilliSeconds(true), 3) << std::endl;

    os << "Lyapunov exponents:" << std::endl;

    unsigned C_INT32 i, imax = mpLyapProblem->getExponentNumber();
    for (i = 0; i < imax; ++i)
      os << mExponents[i] << " ";
    os << std::endl;

    /*    if (mSolutionVariables.size() == 0)
          {
            return;
          }
        os << "    Objective Function Value:\t" << mSolutionValue << std::endl;

        std::vector< COptItem * >::const_iterator itItem =
          mpOptItems->begin();
        std::vector< COptItem * >::const_iterator endItem =
          mpOptItems->end();

        unsigned C_INT32 i;

        for (i = 0; itItem != endItem; ++itItem, i++)
          {
            os << "    " << (*itItem)->getObjectDisplayName() << ": "
            << mSolutionVariables[i] << std::endl;
          }*/
  }
