// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CSensTask class.
 *
 */

#include "copasi.h"

#include "CSensTask.h"
#include "CSensProblem.h"
#include "CSensMethod.h"

#include "math/CMathContainer.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#define XXXX_Reporting

CSensTask::CSensTask(const CCopasiContainer * pParent,
                     const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpProblem = new CSensProblem(this);

  mpMethod = createMethod(CTaskEnum::sensMethod);
}

CSensTask::CSensTask(const CSensTask & src,
                     const CCopasiContainer * pParent):
  CCopasiTask(src, pParent)
{
  mpProblem =
    new CSensProblem(*(CSensProblem *) src.mpProblem, this);

  mpMethod = createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
}

CSensTask::~CSensTask()
{}

void CSensTask::cleanup()
{}

//TODO: really necessary?
void CSensTask::print(std::ostream * ostream) const {(*ostream) << (*this);}

bool CSensTask::updateMatrices()
{
  assert(mpProblem && mpMethod);

  CSensProblem* pProblem =
    dynamic_cast<CSensProblem *>(mpProblem);
  assert(pProblem);

  CSensMethod* pMethod =
    dynamic_cast<CSensMethod *>(mpMethod);
  assert(pMethod);

  bool success = true;

  //this does actually more than just update the matrices, but it should do no harm
  if (!pMethod->initialize(pProblem)) success = false;

  return success;
}

bool CSensTask::initialize(const OutputFlag & of,
                           COutputHandler * pOutputHandler,
                           std::ostream * pOstream)
{

  bool success = true;

  //this needs to be done before the initialization of the output
  if (!updateMatrices()) success = false;

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  return success;
}

bool CSensTask::process(const bool & useInitialValues)
{
  assert(/*mpProblem && */mpMethod);
  mpMethod->isValidProblem(mpProblem);

  CSensProblem* pProblem =
    dynamic_cast<CSensProblem *>(mpProblem);
  assert(pProblem);

  CSensMethod* pMethod =
    dynamic_cast<CSensMethod *>(mpMethod);
  assert(pMethod);

  if (useInitialValues)
    mpContainer->applyInitialValues();

  mReport.output(COutputInterface::BEFORE);

  bool success = pMethod->process(mpCallBack);

  mReport.output(COutputInterface::DURING);
  mReport.output(COutputInterface::AFTER);

  return (success);
}

// virtual
bool CSensTask::restore()
{
  bool success = true;

  CSensMethod* pMethod =
    dynamic_cast<CSensMethod *>(mpMethod);

  if (pMethod != NULL)
    pMethod->restore(mUpdateModel);

  return success;
}

// virtual
const CTaskEnum::Method * CSensTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::sensMethod,
    CTaskEnum::UnsetMethod
  };

  return ValidMethods;
}

std::ostream &operator<<(std::ostream &os, const CSensTask & /* A */)
{
  return os;
}
