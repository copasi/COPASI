// Copyright (C) 2020 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CMathContext.h"

CMathContext::CMathContext(const bool & parallel)
  : Base(parallel)
{}

CMathContext::~CMathContext()
{}

void CMathContext::sync()
{
  CMathContainer *& pMaster = Base::master();
  CMathContainer ** pIt = Base::beginThread();
  CMathContainer ** pEnd = Base::endThread();

  for (; pIt != pEnd; ++pIt)
    {
      if (*pIt != NULL
          && pMaster != NULL
          && **pIt == *pMaster)
        continue;

      if (*pIt != NULL)
        {
          delete *pIt;
          *pIt = NULL;
        }

      if (pMaster != NULL)
        *pIt = pMaster->copy();
    }
}
