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

bool CMathContext::sync()
{
  CMathContainer *& pMaster = Base::master();
  bool changed = false;

  if (size() > 1)
    {
      bool renameEnabled = CRegisteredCommonName::isEnabled();

      if (renameEnabled)
        CRegisteredCommonName::setEnabled(false);

#pragma omp parallel for
      for (size_t i = 0; i < size(); ++i)
        {
          if (threadData()[i] != nullptr)
            {
              if (&pMaster->getModel() == &threadData()[i]->getModel()
                  && pMaster->getCompileTime() <= threadData()[i]->getCompileTime())
                continue;

              delete threadData()[i];
              threadData()[i] = nullptr;
            }

          changed |= true;

          if (pMaster != NULL)
            threadData()[i] = pMaster->copy();
        }

      if (renameEnabled)
        CRegisteredCommonName::setEnabled(true);
    }

  return changed;
}
