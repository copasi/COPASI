// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CCrossSectionMethod.h"
#include "CCrossSectionProblem.h"

/**
 *  Default constructor.
 */
CCrossSectionMethod::CCrossSectionMethod(const CCopasiContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType)
{}

/**
 *  Copy constructor.
 *  @param "const CCrossSectionMethod &" src
 */
CCrossSectionMethod::CCrossSectionMethod(const CCrossSectionMethod & src,
    const CCopasiContainer * pParent):
  CCopasiMethod(src, pParent)
  //mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CCrossSectionMethod::~CCrossSectionMethod()
{DESTRUCTOR_TRACE;}

bool CCrossSectionMethod::process(CProcessReport * /* handler */)
{
  return false;
}

bool CCrossSectionMethod::initialize(CCrossSectionProblem* /* problem */)
{
  return false;
}

bool CCrossSectionMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CCrossSectionProblem * pP = dynamic_cast<const CCrossSectionProblem *>(pProblem);

  if (!pP)
    {
      //not a correct Problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a Cross section problem.");
      return false;
    }

  return true;
}
