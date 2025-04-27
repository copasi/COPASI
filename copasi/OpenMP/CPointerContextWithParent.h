// Copyright (C) 2021 - 2025 by Pedro Mendes, Rector and Visitors of the
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
#pragma omp parallel for
    for (size_t i = 0; i < Base::size(); ++i)
      Base::threadData()[i] = NULL;
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

  // We must not parallelize this as setObjectParent my introduce race conditions.
  if (Base::size() > 1)
    for (size_t i = 0; i < Base::size(); ++i)
      if (Base::threadData()[i] != NULL)
        (Base::threadData()[i])->setObjectParent(mpParent);
}

#endif // COPASI_CPointerContextWithParent
