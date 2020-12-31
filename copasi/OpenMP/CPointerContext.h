// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CPointerContext
#define COPASI_CPointerContext

#include "copasi/OpenMP/CContext.h"

template < class Data > class CPointerContext : public CContext< Data * >
{
public:
  typedef CContext< Data * > Base;

  CPointerContext() = delete;

  CPointerContext(const CPointerContext & src) = delete;

  CPointerContext(Data * pMaster);

  ~CPointerContext();

  /**
   * Set the pointer to container used for calculations
   * @param CCopasiMethod * pMethod
   */
  void setMaster(Data * pMaster);
};

template < class Data > CPointerContext< Data >::CPointerContext(Data * pMaster)
  : Base()
{
  Base::init();
  Base::master() = NULL;
  setMaster(pMaster);
}

template < class Data > CPointerContext< Data >::~CPointerContext()
{
  setMaster(NULL);
}

template < class Data > void CPointerContext< Data >::setMaster(Data * pMaster)
{
  if (Base::master() != NULL)
    {
      Base::master() = NULL;

      if (Base::mSize > 1)
        {
          Data ** pIt = Base::beginThread();
          Data ** pEnd = Base::endThread();

          for (; pIt != pEnd; ++pIt)
            delete *pIt;
        }
    }

  if (pMaster != NULL)
    {
      Base::master() = pMaster;

      if (Base::mSize > 1)
        {
          Data ** pIt = Base::beginThread();
          Data ** pEnd = Base::endThread();

          for (; pIt != pEnd; ++pIt)
            *pIt = pMaster->copy();
        }
    }
}

#endif // COPASI_CPointerContext
