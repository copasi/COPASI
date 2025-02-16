// Copyright (C) 2020 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CPointerMathContext
#define COPASI_CPointerMathContext

#include "copasi/OpenMP/CMathContext.h"
#include "copasi/OpenMP/CPointerContextWithParent.h"

template < class Data >
class CPointerMathContext : public CPointerContextWithParent< Data >
{
public:
  typedef CPointerContextWithParent< Data > Base;

  CPointerMathContext() = delete;

  CPointerMathContext(const CPointerMathContext & src) = delete;

  CPointerMathContext(const bool & parallel, CDataContainer * pParent);

  ~CPointerMathContext();

  /**
   * Set the pointer to container used for calculations
   * @param CMathContext * pContext
   */
  void setMathContext(CMathContext & Context);
};

template < class Data >
CPointerMathContext< Data >::CPointerMathContext(const bool & parallel, CDataContainer * pParent)
  : Base(parallel, pParent)
{}

template < class Data >
CPointerMathContext< Data >::~CPointerMathContext()
{}

template < class Data >
void CPointerMathContext< Data >::setMathContext(CMathContext & Context)
{
  if (Base::master() != NULL)
    {
      Base::master()->setMathContainer(Context.master());

      if (Base::size() > 1)
#pragma omp parallel for
        for (size_t i = 0; i < Base::size(); ++i)
          Base::threadData()[i]->setMathContainer(Context.Base::threadData()[i]);
    }
}

#endif // COPASI_CPointerMathContext
