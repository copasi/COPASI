// Copyright (C) 2021 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CPointerContextWithParent
#define COPASI_CPointerContextWithParent

#include "copasi/OpenMP/CPointerContext.h"

class CDataContainer;
template < class Data >
class CPointerContextWithParent : public CPointerContext< Data >
{
public:
  typedef CPointerContext< Data > Base;

  CPointerContextWithParent() = delete;

  CPointerContextWithParent(const CPointerContextWithParent & src) = delete;

  CPointerContextWithParent(const bool & parallel, CDataContainer * pParent);

  ~CPointerContextWithParent();

  /**
   * Set the pointer to container used for calculations
   * @param CCopasiMethod * pMethod
   */
  void setMaster(Data * pMaster);

private:
  CDataContainer * mpParent;
};

template < class Data >
CPointerContextWithParent< Data >::CPointerContextWithParent(const bool & parallel, CDataContainer * pParent)
  : Base(parallel)
  , mpParent(pParent)
{
  Base::init();
  Base::master() = NULL;

  if (Base::size() > 1)
    {
      Data ** pIt = Base::beginThread();
      Data ** pEnd = Base::endThread();

      for (; pIt != pEnd; ++pIt)
        *pIt = NULL;
    }
}

template < class Data >
CPointerContextWithParent< Data >::~CPointerContextWithParent()
{
  Base::setMaster(NULL);
}

template < class Data >
void CPointerContextWithParent< Data >::setMaster(Data * pMaster)
{
  Base::setMaster(pMaster);

  if (Base::size() > 1)
    {
      Data ** pIt = Base::beginThread();
      Data ** pEnd = Base::endThread();

      for (; pIt != pEnd; ++pIt)
        if (*pIt != NULL)
          (*pIt)->setObjectParent(mpParent);
    }
}

#endif // COPASI_CPointerContextWithParent
