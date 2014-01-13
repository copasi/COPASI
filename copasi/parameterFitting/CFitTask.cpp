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
  * CFitTask class.
  *
  * This class implements a parameter estimation task which is comprised of a
  * of a problem and a method.
  *
  */
#include "copasi.h"

#include "CFitTask.h"
#include "CFitProblem.h"
#include "CFitMethod.h"

#include "utilities/CCopasiMethod.h"

CFitTask::CFitTask(const CCopasiTask::Type & type,
                   const CCopasiContainer * pParent):
  COptTask(type, pParent)
{
  pdelete(mpProblem);
  mpProblem = new CFitProblem(type, this);
  pdelete(mpMethod);
  mpMethod = CFitMethod::createMethod();
  this->add(mpMethod, true);

  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

CFitTask::CFitTask(const CFitTask & src,
                   const CCopasiContainer * pParent):
  COptTask(src, pParent)
{
  pdelete(mpProblem);
  mpProblem = new CFitProblem(*(CFitProblem *) src.mpProblem, this);
  pdelete(mpMethod);
  mpMethod = CFitMethod::createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);

  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

CFitTask::~CFitTask()
{cleanup();}

void CFitTask::cleanup() {}

bool CFitTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;

  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool CFitTask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  return COptTask::initialize(of, pOutputHandler, pOstream);
}

bool CFitTask::process(const bool & useInitialValues)
{
  CFitProblem * pProblem = dynamic_cast<CFitProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  if (useInitialValues)
    {
      pProblem->updateInitialState();
    }

  pProblem->randomizeStartValues();
  pProblem->rememberStartValues();

  output(COutputInterface::BEFORE);

  bool success = pMethod->optimise();

  pProblem->calculateStatistics();

  output(COutputInterface::AFTER);

  return success;
}

bool CFitTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete(mpMethod);

  mpMethod = createMethod(Type);
  this->add(mpMethod, true);

  return true;
}

// virtual
CCopasiMethod * CFitTask::createMethod(const int & type) const
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  return CFitMethod::createMethod(Type);
}

void CFitTask::fixBuild55()
{
  CFitProblem * pFitProblem = dynamic_cast< CFitProblem * >(mpProblem);

  if (pFitProblem == NULL) return;

  pFitProblem->fixBuild55();

  return;
}
