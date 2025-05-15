// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CMethodContext
#define COPASI_CMethodContext

#include "copasi/OpenMP/CProblemContext.h"

template < class Method >
class CMethodContext : public CPointerMathContext< Method >
{
public:
  typedef CPointerMathContext< Method > Base;

  CMethodContext() = delete;

  CMethodContext(const CMethodContext & src) = delete;

  CMethodContext(const bool & parallel, CDataContainer * pParent);

  ~CMethodContext();

  /**
   * Set the pointer to problem used for calculations
   * @param CProblemContext * pContext
   */
  template < class Problem >
  bool setProblemContext(CProblemContext< Problem > & Context);
};

template < class Method >
CMethodContext< Method >::CMethodContext(const bool & parallel, CDataContainer * pParent)
  : Base(parallel, pParent)
{}

template < class Method >
CMethodContext< Method >::~CMethodContext()
{}

template < class Method >
template < class Problem >
bool CMethodContext< Method >::setProblemContext(CProblemContext< Problem > & Context)
{
  bool success = false;

  if (Base::master() != NULL)
    {
      success = true;

      success &= Base::master()->setProblem(Context.master());

      if (Base::size() > 1)
#pragma omp parallel for reduce(&: success)
        for (size_t i = 0; i < Base::size(); ++i)
          success &= Base::threadData()[i]->setProblem(Context.threadData()[i]);
    }

  return success;
}

#endif // COPASI_CMethodContext
