// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ssa/Attic/CSSATask.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/02 18:18:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string.h>

#include "copasi.h"

#include "CSSATask.h"
#include "CSSAProblem.h"
#include "CSSAMethod.h"

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"

CSSATask::CSSATask(const CCopasiContainer * pParent)
    : CCopasiTask(CCopasiTask::ssa, pParent)
{
  mpProblem = new CSSAProblem();
  mpMethod = CSSAMethod::createSSAMethod(CCopasiMethod::ssaMethod);
  this->add(mpMethod, true);
}

CSSATask::~CSSATask()
{DESTRUCTOR_TRACE}

bool
CSSATask::initialize(const OutputFlag & of, std::ostream * pOstream)
{
  assert(mpProblem && mpMethod);

  CSSAProblem* pProblem =
    dynamic_cast<CSSAProblem *>(mpProblem);
  assert(pProblem);

  mpModel = pProblem->getModel();

  dynamic_cast<CSSAMethod *>(mpMethod)->initialize(pProblem);

  bool success = true;

  if (CCopasiTask::initialize(of, pOstream)) success = false;

  if (!mpModel->compileIfNecessary()) success = false;
  //pProblem->setInitialState(pProblem->getModel()->getInitialState());

  return success;
}

bool
CSSATask::process(const bool & useInitialValues)
{
  if (!dynamic_cast<CSSAMethod *>(mpMethod)->calculate())
    return false;

  return true;
}

void
CSSATask::print(std::ostream * ostream) const
{}

std::ostream &operator<<(std::ostream &os, const CSSATask &A)
{return os;}
