// Copyright (C) 2020 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CPointerMathContext
#define COPASI_CPointerMathContext

#include "copasi/OpenMP/CMathContext.h"

template < class Data > class CPointerMathContext : public CPointerContext< Data >
{
public:
  typedef CPointerContext< Data > Base;

  CPointerMathContext() = delete;

  CPointerMathContext(const CPointerMathContext & src) = delete;

  CPointerMathContext(const bool & parallel);

  ~CPointerMathContext();

  /**
   * Set the pointer to container used for calculations
   * @param CMathContext * pContext
   */
  void setMathContext(CMathContext & Context);
};

template < class Data > CPointerMathContext< Data >::CPointerMathContext(const bool & parallel)
  : CPointerContext< Data >(parallel)
{}

template < class Data > CPointerMathContext< Data >::~CPointerMathContext()
{}

template < class Data > void CPointerMathContext< Data >::setMathContext(CMathContext & Context)
{
  if (Base::master() != NULL)
    {
      Base::master()->setMathContainer(Context.master());

      if (Base::mSize > 1)
        {
          Data ** pIt = Base::beginThread();
          Data ** pEnd = Base::endThread();
          CMathContainer ** pContainer = Context.beginThread();

          for (; pIt != pEnd; ++pIt, ++pContainer)
            (*pIt)->setMathContainer(*pContainer);
        }
    }
}

#endif // COPASI_CPointerMathContext
