// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "COscillationTask.h"
#include "COscillationMethod.h"
#include "COscillationProblem.h"

#include "COscillationMethodIntegrate.h"

// Default constructor
COscillationMethod::COscillationMethod(const CCopasiContainer * pParent,
                                       const CTaskEnum::Method & methodType,
                                       const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mpOscProblem(NULL)

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
