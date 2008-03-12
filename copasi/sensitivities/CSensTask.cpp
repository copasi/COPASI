// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensTask.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:31:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include "model/CModel.h"
#include "model/CState.h"
//#include "model/CMetabNameInterface.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#define XXXX_Reporting

CSensTask::CSensTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::sens, pParent)
{
  mpProblem = new CSensProblem(this);
  mpMethod = CSensMethod::createSensMethod(CCopasiMethod::sensMethod);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
}

CSensTask::CSensTask(const CSensTask & src,
                     const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem =
    new CSensProblem(* (CSensProblem *) src.mpProblem, this);
  mpMethod =
    CSensMethod::createSensMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
}

CSensTask::~CSensTask()
{}

void CSensTask::cleanup()
{}

//TODO: really necessary?
void CSensTask::print(std::ostream * ostream) const {(*ostream) << (*this);}

bool CSensTask::initialize(const OutputFlag & of,
                           COutputHandler * pOutputHandler,
                           std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CSensProblem* pProblem =
    dynamic_cast<CSensProblem *>(mpProblem);
  assert(pProblem);

  bool success = true;

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  if (!pProblem->getModel()->compileIfNecessary(mpCallBack)) success = false;
  //pProblem->setInitialState(pProblem->getModel()->getInitialState());

  return success;
}

bool CSensTask::process(const bool & /* useInitialValues */)
{
  assert(/*mpProblem && */mpMethod);
  mpMethod->isValidProblem(mpProblem);

  CSensProblem* pProblem =
    dynamic_cast<CSensProblem *>(mpProblem);
  assert(pProblem);

  CSensMethod* pMethod =
    dynamic_cast<CSensMethod *>(mpMethod);
  assert(pMethod);

  //TODO: move to Task::initialize() ?
  pMethod->initialize(pProblem);

  mReport.output(COutputInterface::BEFORE);

  bool success = pMethod->process(mpCallBack);

  mReport.output(COutputInterface::DURING);
  mReport.output(COutputInterface::AFTER);

  return (success);
}

std::ostream &operator<<(std::ostream &os, const CSensTask & /* A */)
{
  return os;
}
