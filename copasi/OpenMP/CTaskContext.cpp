// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CTaskContext.h"
#include "copasi/OpenMP/CMathContext.h"
#include "copasi/utilities/CTaskFactory.h"

CTaskContext::CTaskContext(CCopasiTask * pTask)
  : CContext()
  , mpMathContext(NULL)
{
  init();
  master() = NULL;
  setTask(pTask);
}

CTaskContext::~CTaskContext()
{
  setTask(NULL);
}

void CTaskContext::setTask(CCopasiTask * pTask)
{
  if (master() != NULL)
    {
      master() = NULL;

      if (mSize > 1)
        {
          CCopasiTask ** pIt = beginThread();
          CCopasiTask ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            delete *pIt;
        }
    }

  if (pTask != NULL)
    {
      master() = pTask;

      if (mSize > 1)
        {
          CCopasiTask ** pIt = beginThread();
          CCopasiTask ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            *pIt = CTaskFactory::copy(pTask, INHERIT_PARENT);
        }
    }
}

void CTaskContext::setMathContext(CMathContext * pContext)
{
  mpMathContext = pContext;

  if (master() != NULL)
    {
      master()->setMathContainer(mpMathContext->master());

      if (mSize > 1)
        {
          CCopasiTask ** pIt = beginThread();
          CCopasiTask ** pEnd = endThread();
          CMathContainer ** pContainer = mpMathContext->beginThread();

          for (; pIt != pEnd; ++pIt, ++pContainer)
            (*pIt)->setMathContainer(*pContainer);
        }
    }
}