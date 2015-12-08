// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CAnalyticsMethod.h"

#include "CAnalyticsProblem.h"

/**
 *  Default constructor.
 */
CAnalyticsMethod::CAnalyticsMethod(const CCopasiContainer * pParent,
    const CTaskEnum::Method & methodType,
    const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType)
{}

/**
 *  Copy constructor.
 *  @param "const CAnalyticsMethod &" src
 */
CAnalyticsMethod::CAnalyticsMethod(const CAnalyticsMethod & src,
    const CCopasiContainer * pParent):
  CCopasiMethod(src, pParent)
  //mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CAnalyticsMethod::~CAnalyticsMethod()
{DESTRUCTOR_TRACE;}

bool CAnalyticsMethod::process(CProcessReport * /* handler */)
{
  return false;
}

bool CAnalyticsMethod::initialize(CAnalyticsProblem* /* problem */)
{
  return false;
}

bool CAnalyticsMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CAnalyticsProblem * pP = dynamic_cast<const CAnalyticsProblem *>(pProblem);

  if (!pP)
    {
      //not a correct Problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not an Analytivs problem.");
      return false;
    }

  return true;
}
