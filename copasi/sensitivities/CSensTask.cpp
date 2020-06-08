// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CSensTask.h"
#include "CSensProblem.h"
#include "CSensMethod.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"

#define XXXX_Reporting

CSensTask::CSensTask(const CDataContainer * pParent,
                     const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpProblem = new CSensProblem(this);

  mpMethod = createMethod(CTaskEnum::Method::sensMethod);
}

CSensTask::CSensTask(const CSensTask & src,
                     const CDataContainer * pParent):
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
  success &= updateMatrices();

  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

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

  bool success = pMethod->process();

  mReport.output(COutputInterface::DURING);
  mReport.output(COutputInterface::AFTER);

  return (success);
}

// virtual
const CTaskEnum::Method * CSensTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::sensMethod,
    CTaskEnum::Method::UnsetMethod
  };

  return ValidMethods;
}

std::ostream &operator<<(std::ostream &os, const CSensTask & /* A */)
{
  return os;
}
