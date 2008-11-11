// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/oscillation/COscillationMethod.cpp,v $
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
#include "COscillationMethod.h"
#include "COscillationProblem.h"

#include "COscillationMethodIntegrate.h"

COscillationMethod * COscillationMethod::createMethod(CCopasiMethod::SubType subType)
{
  COscillationMethod * pMethod = NULL;

  switch (subType)
    {
    case oscillationIntegrate:
      pMethod = new COscillationMethodIntegrate();
      break;

    default:
      pMethod = new COscillationMethodIntegrate();
    }
  //TODO
  return pMethod;
}

// Default constructor
COscillationMethod::COscillationMethod():
    CCopasiMethod(CCopasiTask::optimization, CCopasiMethod::unset),
    mpOscProblem(NULL)
    //    mpParentTask(NULL),
{CONSTRUCTOR_TRACE;}

COscillationMethod::COscillationMethod(const CCopasiTask::Type & taskType,
                                       const COscillationMethod::SubType & subType,
                                       const CCopasiContainer * pParent):
    CCopasiMethod(taskType, subType, pParent),
    mpOscProblem(NULL)
    //    mpParentTask(NULL),
{CONSTRUCTOR_TRACE;}

COscillationMethod::COscillationMethod(const COscillationMethod & src,
                                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpOscProblem(src.mpOscProblem)
    //    mpParentTask(src.mpParentTask),
{CONSTRUCTOR_TRACE;}

COscillationMethod::~COscillationMethod()
{}

void COscillationMethod::setProblem(COscillationProblem * problem)
{
  assert(problem);
  mpOscProblem = problem;
}

// bool COscillationMethod::run(void)
// {
//   return false;
//}

bool COscillationMethod::initialize()
{
  if (!mpOscProblem)
    return false;

  //  mpParentTask = dynamic_cast<COptTask *>(getObjectParent());
  //  if (!mpParentTask) return false;

  return true;
}

bool COscillationMethod::cleanup()
{return true;}

//virtual
bool COscillationMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const COscillationProblem * pTP = dynamic_cast<const COscillationProblem *>(pProblem);
  if (!pTP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not an oscillation detection problem.");
      return false;
    }

  return true;
}
