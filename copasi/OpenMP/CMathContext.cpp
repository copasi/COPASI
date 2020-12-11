// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CMathContext.h"

CMathContext::CMathContext(CMathContainer * pContainer)
  : CContext()
{
  init();
  master() = NULL;
  setMathContainer(pContainer);
}

CMathContext::~CMathContext()
{
  setMathContainer(NULL);
}

void CMathContext::setMathContainer(CMathContainer * pContainer)
{
  if (master() != NULL)
    {
      master() = NULL;

      if (mSize > 1)
        {
          CMathContainer ** pIt = beginThread();
          CMathContainer ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            delete *pIt;
        }
    }

  if (pContainer != NULL)
    {
      master() = pContainer;

      if (mSize > 1)
        {
          CMathContainer ** pIt = beginThread();
          CMathContainer ** pEnd = endThread();

          for (; pIt != pEnd; ++pIt)
            *pIt = new CMathContainer(*pContainer);
        }
    }
}
