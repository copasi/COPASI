// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CMethodContext.h"
#include "copasi/utilities/CMethodFactory.h"
#include "copasi/OpenMP/CMathContext.h"

CMethodContext::CMethodContext(CCopasiMethod * pMethod)
  : CContext()
  , mpMathContext(NULL)
{
  init();
  master() = NULL;
  setMethod(pMethod);
}

CMethodContext::~CMethodContext()
{
  setMethod(NULL);
}

void CMethodContext::setMethod(CCopasiMethod * pMethod)
{
  if (master() != NULL)
    {
      master() = NULL;

      if (mSize > 1)
        {
          CCopasiMethod ** pIt = beginThread();
          CCopasiMethod ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            delete *pIt;
        }
    }

  if (pMethod != NULL)
    {
      master() = pMethod;

      if (mSize > 1)
        {
          CCopasiMethod ** pIt = beginThread();
          CCopasiMethod ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            *pIt = CMethodFactory::copy(pMethod, INHERIT_PARENT);
        }
    }
}

void CMethodContext::setMathContext(CMathContext * pContext)
{
  mpMathContext = pContext;

  if (master() != NULL)
    {
      master()->setMathContainer(mpMathContext->master());

      if (mSize > 1)
        {
          CCopasiMethod ** pIt = beginThread();
          CCopasiMethod ** pEnd = endThread();
          CMathContainer ** pContainer = mpMathContext->beginThread();

          for (; pIt != pEnd; ++pIt, ++pContainer)
            (*pIt)->setMathContainer(*pContainer);
        }
    }
}
