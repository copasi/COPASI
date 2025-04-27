// Copyright (C) 2020 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CPointerContext
#define COPASI_CPointerContext

#include "copasi/OpenMP/CContext.h"
#include "copasi/core/CRegisteredCommonName.h"

template < class Data >
class CPointerContext : public CContext< Data * >
{
public:
  typedef CContext< Data * > Base;

  CPointerContext() = delete;

  CPointerContext(const CPointerContext & src) = delete;

  CPointerContext(const bool & parallel);

  ~CPointerContext();

  /**
   * Set the pointer to container used for calculations
   * @param CCopasiMethod * pMethod
   */
  void setMaster(Data * pMaster);
};

template < class Data >
CPointerContext< Data >::CPointerContext(const bool & parallel)
  : Base(parallel)
{
  Base::init();
  Base::master() = NULL;

  if (Base::size() > 1)
#pragma omp parallel for
    for (size_t i = 0; i < Base::size(); ++i)
      Base::threadData()[i] = NULL;
}

template < class Data >
CPointerContext< Data >::~CPointerContext()
{
  setMaster(NULL);
}

template < class Data >
void CPointerContext< Data >::setMaster(Data * pMaster)
{
  if (Base::size() == 0)
    return;

  if (Base::master() == pMaster)
    return;

  if (Base::master() != NULL)
    {
      Base::master() = NULL;

      if (Base::size() > 1)
#pragma omp parallel for
        for (size_t i = 0; i < Base::size(); ++i)
          if (Base::threadData()[i] != NULL)
            {
              delete Base::threadData()[i];
              Base::threadData()[i] = NULL;
            }
    }

  if (pMaster != NULL)
    {
      Base::master() = pMaster;

      {
        bool renameEnabled = CRegisteredCommonName::isEnabled();

        if (renameEnabled)
          CRegisteredCommonName::setEnabled(false);

        if (Base::size() > 1)
#pragma omp parallel for
          for (size_t i = 0; i < Base::size(); ++i)
            Base::threadData()[i] = dynamic_cast< Data * >(pMaster->copy());

        if (renameEnabled)
          CRegisteredCommonName::setEnabled(true);
      }
    }
}

#endif // COPASI_CPointerContext
