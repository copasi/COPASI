// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include  "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CCopasiTimer.h"

#define XXXX_Reporting

//this is about the preliminary reporting. The first LYAP_NUM_REF exponents
//get an individual object reference. This will be obsolete when we have
//working annotated vectors
#define LYAP_NUM_REF 10

CLyapTask::CLyapTask(const CCopasiContainer * pParent,
                     const CTaskEnum::Task & type):
  CCopasiTask(pParent, type),
  mpLyapProblem(NULL),
  mpLyapMethod(NULL),
  mLocalExponents(),
  mExponents(),
  mSumOfExponents(0.0),
  mSumOfLocalExponents(0.0),
  mIntervalDivergence(0.0),
  mAverageDivergence(0.0),
  mResultAvailable(false),
  mResultHasDivergence(false),
  mModelVariablesInResult(0)
{
  mpProblem = new CLyapProblem(this);
  mpMethod = createMethod(CTaskEnum::lyapWolf);
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
  size_t i;

  mExponents.resize(LYAP_NUM_REF);

  for (i = 0; i < LYAP_NUM_REF; ++i) mExponents[i] = 0.0;

  mvExpRef.resize(LYAP_NUM_REF);

  mLocalExponents.resize(LYAP_NUM_REF);

  for (i = 0; i < LYAP_NUM_REF; ++i) mLocalExponents[i] = 0.0;

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
  //addObjectReference("Local divergence", mDivergence, CCopasiObject::ValueDbl);
  addObjectReference("Interval divergence", mIntervalDivergence, CCopasiObject::ValueDbl);
  addObjectReference("Average divergence", mAverageDivergence, CCopasiObject::ValueDbl);
}

bool CLyapTask::initialize(const OutputFlag & of,
                           COutputHandler * pOutputHandler,
                           std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  mpLyapProblem = dynamic_cast<CLyapProblem *>(mpProblem);
  assert(mpLyapProblem);

  mpLyapMethod = dynamic_cast<CLyapMethod *>(mpMethod);
  assert(mpLyapMethod);

  mpLyapMethod->setProblem(mpLyapProblem);

  bool success = mpMethod->isValidProblem(mpProblem);

  size_t nnn;

  if (mpLyapProblem->getExponentNumber() > LYAP_NUM_REF)
    nnn = mpLyapProblem->getExponentNumber();
  else
    nnn = LYAP_NUM_REF;

  mLocalExponents.resize(nnn);
  mExponents.resize(nnn);

  //update object references because the object may have been
  //moved by the resize above
  size_t i;

  for (i = 0; i < LYAP_NUM_REF; ++i)
    {
      mvExpRef[i]->setReference(mExponents.array()[i]);
      mvLocExpRef[i]->setReference(mLocalExponents.array()[i]);
    }

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  //mTimeSeriesRequested = mpLyapProblem->timeSeriesRequested();

  return success;
}

bool CLyapTask::process(const bool & useInitialValues)
{
  if (useInitialValues)
    {
      mpContainer->applyInitialValues();
    }

  output(COutputInterface::BEFORE);

  //  bool flagProceed = true;
  mPercentage = 0;

  if (mpCallBack)
    {
      mpCallBack->setName("performing lyapunov exponent calculation...");
      C_FLOAT64 hundred = 100;
      mhProcess = mpCallBack->addItem("Completion",
                                      mPercentage,
                                      &hundred);
    }

  try
    {
      mpLyapMethod->calculate();
    }
  catch (CCopasiException & Exception)
    {
      //mpLyapProblem->getModel()->setState(*mpCurrentState);
      mpContainer->updateSimulatedValues(true);

      calculationsBeforeOutput();
      output(COutputInterface::DURING);

      if (mpCallBack) mpCallBack->finishItem(mhProcess);

      output(COutputInterface::AFTER);

      throw CCopasiException(Exception.getMessage());
    }

  if (mpCallBack) mpCallBack->finishItem(mhProcess);

  calculationsBeforeOutput();
  output(COutputInterface::AFTER);

  mResultAvailable = true;
  mResultHasDivergence = mpLyapProblem->divergenceRequested();
  mModelVariablesInResult = mpContainer->getState(true).size() - mpContainer->getTimeIndex() - 1;
  mNumExponentsCalculated = mpLyapProblem->getExponentNumber();

  return true;
}

bool CLyapTask::restore()
{
  bool success = CCopasiTask::restore();

  if (mUpdateModel)
    {
      mpContainer->updateSimulatedValues(true);
      mpContainer->setInitialState(mpContainer->getState(false));
      mpContainer->updateInitialValues(CModelParameter::ParticleNumbers);
      mpContainer->pushInitialState();
    }

  return success;
}

// virtual
const CTaskEnum::Method * CLyapTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::lyapWolf,
    CTaskEnum::UnsetMethod
  };

  return ValidMethods;
}

bool CLyapTask::methodCallback(const C_FLOAT64 & percentage, bool onlyProgress)
{
  if (!onlyProgress)
    {
      calculationsBeforeOutput();
      output(COutputInterface::DURING);
    }

  mPercentage = percentage;

  if (mpCallBack)
    {
      return mpCallBack->progressItem(mhProcess);
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
}

void CLyapTask::printResult(std::ostream * ostream) const
{
  std::ostream & os = *ostream;

  //     CCopasiTimeVariable CPUTime = const_cast<COptProblem *>(this)->mCPUTime.getElapsedTime();
  //     os << "    CPU Time [s]:\t"
  //     << CCopasiTimeVariable::LL2String(CPUTime.getSeconds(), 1) << "."
  //     << CCopasiTimeVariable::LL2String(CPUTime.getMilliSeconds(true), 3) << std::endl;

  os << "Lyapunov Exponents:" << std::endl;

  if (!mpLyapProblem) //this means that task was not yet executed
    {
      os << "No results available." << std::endl;
      return;
    }

  unsigned C_INT32 i, imax = mpLyapProblem->getExponentNumber();

  for (i = 0; i < imax; ++i)
    os << mExponents[i] << " ";

  os << std::endl;

  if (mpLyapProblem->divergenceRequested())
    os << std::endl << "Average divergence: " << mAverageDivergence << std::endl;
}

bool CLyapTask::resultAvailable() const
{
  return mResultAvailable;
}

bool CLyapTask::resultHasDivergence() const
{
  return mResultHasDivergence;
}

size_t CLyapTask::modelVariablesInResult() const
{
  return mModelVariablesInResult;
}

size_t CLyapTask::numberOfExponentsCalculated() const
{
  return mNumExponentsCalculated;
}
