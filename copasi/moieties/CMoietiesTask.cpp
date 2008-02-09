// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesTask.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/09 00:58:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMoietiesTask.h"
#include "CMoietiesProblem.h"
#include "CMoietiesMethod.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

unsigned C_INT32 CMoietiesTask::ValidMethods[] =
  {
    CCopasiMethod::Householder,
    CCopasiMethod::unset
  };

CMoietiesTask::CMoietiesTask(const CCopasiTask::Type & type,
                             const CCopasiContainer * pParent):
    CCopasiTask(type, pParent)
{
  mpProblem = new CMoietiesProblem(type, this);
  mpMethod = CMoietiesMethod::createMethod();
  this->add(mpMethod, true);
}

CMoietiesTask::CMoietiesTask(const CMoietiesTask & src,
                             const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new CMoietiesProblem(* static_cast< CMoietiesProblem * >(src.mpProblem), this);
  mpMethod = CMoietiesMethod::createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
}

CMoietiesTask::~CMoietiesTask()
{}

bool CMoietiesTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;
  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool CMoietiesTask::initialize(const OutputFlag & of,
                               std::ostream * pOstream)
{
  CMoietiesProblem * pProblem = dynamic_cast<CMoietiesProblem *>(mpProblem);
  CMoietiesMethod * pMethod = dynamic_cast<CMoietiesMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  bool success = true;

  //initialize reporting
  if (!CCopasiTask::initialize(of, pOstream)) success = false;

  success &= mpMethod->isValidProblem(mpProblem);

  return success;
}

bool CMoietiesTask::process(const bool & /* useInitialValues */)
{
  bool success = true;

  output(COutputInterface::BEFORE);

  // success = pMethod->...;

  output(COutputInterface::AFTER);

  return success;
}

bool CMoietiesTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);

  mpMethod = CMoietiesMethod::createMethod(Type);
  this->add(mpMethod, true);

  return true;
}
