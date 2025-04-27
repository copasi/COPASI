// Copyright (C) 2020 - 2025 by Pedro Mendes, Rector and Visitors of the
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

  if (size() > 1)
    {
      bool renameEnabled = CRegisteredCommonName::isEnabled();

      if (renameEnabled)
        CRegisteredCommonName::setEnabled(false);

#pragma omp parallel for
      for (size_t i = 0; i < size(); ++i)
        {
          if (threadData()[i] != NULL)
            {
              delete threadData()[i];
              threadData()[i] = NULL;
            }

          if (pMaster != NULL)
            threadData()[i] = pMaster->copy();
        }

      if (renameEnabled)
        CRegisteredCommonName::setEnabled(true);
    }
}
