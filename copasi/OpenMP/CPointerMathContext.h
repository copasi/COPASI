// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
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

  CPointerMathContext(Data * pMaster);

  ~CPointerMathContext();

  /**
   * Set the pointer to container used for calculations
   * @param CMathContext * pContext
   */
  void setMathContext(CMathContext * pContext);

private:
  CMathContext * mpMathContext;
};

template < class Data > CPointerMathContext< Data >::CPointerMathContext(Data * pMaster)
  : CPointerContext< Data >(pMaster)
  , mpMathContext(NULL)
{}

template < class Data > CPointerMathContext< Data >::~CPointerMathContext()
{}

template < class Data > void CPointerMathContext< Data >::setMathContext(CMathContext * pContext)
{
  mpMathContext = pContext;

  if (Base::master() != NULL)
    {
      Base::master()->setMathContainer(mpMathContext->master());

      if (Base::mSize > 1)
        {
          Data ** pIt = Base::beginThread();
          Data ** pEnd = Base::endThread();
          CMathContainer ** pContainer = mpMathContext->beginThread();

          for (; pIt != pEnd; ++pIt, ++pContainer)
            (*pIt)->setMathContainer(*pContainer);
        }
    }
}

class CCopasiTask;
class CCopasiProblem;
class CCopasiMethod;

typedef CPointerMathContext< CCopasiTask > CTaskContext;
typedef CPointerMathContext< CCopasiProblem > CProblemContext;
typedef CPointerMathContext< CCopasiMethod > CMethodContext;

#endif // COPASI_CPointerMathContext
