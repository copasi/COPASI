// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/oscillation/COscillationTask.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/11/11 16:47:54 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "COscillationTask.h"
#include "COscillationProblem.h"
#include "COscillationMethod.h"
//#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

unsigned C_INT32 COscillationTask::ValidMethods[] =
  {
    CCopasiMethod::oscillationIntegrate,
    CCopasiMethod::unset
  };

COscillationTask::COscillationTask(const CCopasiTask::Type & type,
                                   const CCopasiContainer * pParent):
    CCopasiTask(type, pParent)
{
  mpProblem = new COscillationProblem(type, this);
  mpMethod = COscillationMethod::createMethod();
  this->add(mpMethod, true);
  ((COscillationMethod *) mpMethod)->setProblem((COscillationProblem *) mpProblem);
}

COscillationTask::COscillationTask(const COscillationTask & src,
                                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new COscillationProblem(* (COscillationProblem *) src.mpProblem, this);
  mpMethod = COscillationMethod::createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
  ((COscillationMethod *) mpMethod)->setProblem((COscillationProblem *) mpProblem);
}

COscillationTask::~COscillationTask()
{cleanup();}

void COscillationTask::cleanup(){}

bool COscillationTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;
  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool COscillationTask::initialize(const OutputFlag & of,
                                  COutputHandler * pOutputHandler,
                                  std::ostream * pOstream)
{
  COscillationProblem * pProblem = dynamic_cast<COscillationProblem *>(mpProblem);
  COscillationMethod * pMethod = dynamic_cast<COscillationMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  //initialize reporting
  bool success = true;

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;
  //if (!mReport.open(pOstream)) success = false;
  //if (!mReport.compile()) success = false;

  if (!pProblem->initialize()) success = false;

  pMethod->setProblem(pProblem);
  //  if (!pMethod->initialize()) return false;

  return success;
}

bool COscillationTask::process(const bool & /* useInitialValues */)
{
  COscillationProblem * pProblem = dynamic_cast<COscillationProblem *>(mpProblem);
  COscillationMethod * pMethod = dynamic_cast<COscillationMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  output(COutputInterface::BEFORE);

  bool success = pMethod->run();

  output(COutputInterface::AFTER);

  return success;
}

bool COscillationTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);

  mpMethod = COscillationMethod::createMethod(Type);
  this->add(mpMethod, true);

  return true;
}
