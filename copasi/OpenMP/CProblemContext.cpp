// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CProblemContext.h"
#include "copasi/utilities/CProblemFactory.h"
#include "copasi/OpenMP/CMathContext.h"

CProblemContext::CProblemContext(CCopasiProblem * pProblem)
  : CContext()
  , mpMathContext(NULL)
{
  init();
  master() = NULL;
  setProblem(pProblem);
}

CProblemContext::~CProblemContext()
{
  setProblem(NULL);
}

void CProblemContext::setProblem(CCopasiProblem * pProblem)
{
  if (master() != NULL)
    {
      master() = NULL;

      if (mSize > 1)
        {
          CCopasiProblem ** pIt = beginThread();
          CCopasiProblem ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            delete *pIt;
        }
    }

  if (pProblem != NULL)
    {
      master() = pProblem;

      if (mSize > 1)
        {
          CCopasiProblem ** pIt = beginThread();
          CCopasiProblem ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            *pIt = CProblemFactory::copy(pProblem, INHERIT_PARENT);
        }
    }
}

void CProblemContext::setMathContext(CMathContext * pContext)
{
  mpMathContext = pContext;

  if (master() != NULL)
    {
      master()->setMathContainer(mpMathContext->master());

      if (mSize > 1)
        {
          CCopasiProblem ** pIt = beginThread();
          CCopasiProblem ** pEnd = endThread();
          CMathContainer ** pContainer = mpMathContext->beginThread();

          for (; pIt != pEnd; ++pIt, ++pContainer)
            (*pIt)->setMathContainer(*pContainer);
        }
    }
}
