// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "COscillationTask.h"
#include "COscillationProblem.h"
#include "COscillationMethod.h"
//#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/utilities/CMethodFactory.h"

const unsigned int COscillationTask::ValidMethods[] =
{
  CTaskEnum::Method::oscillationIntegrate,
  CTaskEnum::Method::unset
};

COscillationTask::COscillationTask(const CTaskEnum::Task & type,
                                   const CDataContainer * pParent):
  CCopasiTask(pParent, type)
{
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::oscillationIntegrate, this);
  static_cast< COscillationMethod * >(mpMethod)->setProblem(static_cast< COscillationProblem * >(mpProblem));
}

COscillationTask::COscillationTask(const COscillationTask & src,
                                   const CDataContainer * pParent):
  CCopasiTask(src, pParent)
{
  static_cast< COscillationMethod * >(mpMethod)->setProblem(static_cast< COscillationProblem * >(mpProblem));
}

COscillationTask::~COscillationTask()
{cleanup();}

void COscillationTask::cleanup() {}

bool COscillationTask::setCallBack(CProcessReportLevel callBack)
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

  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  //if (!mReport.open(pOstream)) success = false;
  //if (!mReport.compile()) success = false;

  success &= pProblem->initialize();

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
  CTaskEnum::Method Type = (CTaskEnum::Method) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete(mpMethod);

  mpMethod = createMethod(Type);
  this->add(mpMethod, true);

  return true;
}

// virtual
CCopasiMethod * COscillationTask::createMethod(const int & type) const
{
  CTaskEnum::Method Type = (CTaskEnum::Method) type;

  return COscillationMethod::createMethod(Type);
}
