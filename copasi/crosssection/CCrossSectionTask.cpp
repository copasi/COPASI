// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/CCrossSectionTask.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2010/05/14 22:20:54 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CCrossSectionTask.h"

#include "copasi.h"

#include "CCrossSectionTask.h"
#include "CCrossSectionProblem.h"
#include "CCrossSectionMethod.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"


CCrossSectionTask::CCrossSectionTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::crosssection, pParent)
{
  mpProblem = new CCrossSectionProblem(this);
  mpMethod = CCrossSectionMethod::createCrossSectionMethod(CCopasiMethod::crossSectionMethod);
  this->add(mpMethod, true);
}

CCrossSectionTask::CCrossSectionTask(const CCrossSectionTask & src,
                                     const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem =
    new CCrossSectionProblem(*(CCrossSectionProblem *) src.mpProblem, this);
  mpMethod =
    CCrossSectionMethod::createCrossSectionMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);
}

CCrossSectionTask::~CCrossSectionTask()
{}

void CCrossSectionTask::cleanup()
{}

//TODO: really necessary?
void CCrossSectionTask::print(std::ostream * ostream) const {(*ostream) << (*this);}


bool CCrossSectionTask::initialize(const OutputFlag & of,
                                   COutputHandler * pOutputHandler,
                                   std::ostream * pOstream)
{

  bool success = true;

  //this needs to be done before the initialization of the output
  //if (!updateMatrices()) success = false;

  if (!CCopasiTask::initialize(of, pOutputHandler, pOstream)) success = false;

  return success;
}

bool CCrossSectionTask::process(const bool & useInitialValues)
{
  assert(/*mpProblem && */mpMethod);
  mpMethod->isValidProblem(mpProblem);

  CCrossSectionProblem* pProblem =
    dynamic_cast<CCrossSectionProblem *>(mpProblem);
  assert(pProblem);

  CCrossSectionMethod* pMethod =
    dynamic_cast<CCrossSectionMethod *>(mpMethod);
  assert(pMethod);

  if (useInitialValues)
    pProblem->getModel()->applyInitialValues();

  mReport.output(COutputInterface::BEFORE);

  bool success = pMethod->process(mpCallBack);

  mReport.output(COutputInterface::DURING);
  mReport.output(COutputInterface::AFTER);

  return (success);
}

std::ostream &operator<<(std::ostream &os, const CCrossSectionTask & /* A */)
{
  return os;
}
