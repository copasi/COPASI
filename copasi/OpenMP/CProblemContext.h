// Copyright (C) 2020 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CProblemContext
#define COPASI_CProblemContext

#include "copasi/OpenMP/CPointerMathContext.h"
#include "copasi/utilities/CCopasiProblem.h"

template < class Problem > 
class CProblemContext : public CPointerMathContext< Problem >
{
public:
  typedef CPointerMathContext< Problem > Base;

  CProblemContext() = delete;

  CProblemContext(const CProblemContext & src) = delete;

  CProblemContext(const bool & parallel, CDataContainer * pParent);

  ~CProblemContext();
};

template < class Problem >
CProblemContext< Problem >::CProblemContext(const bool & parallel, CDataContainer * pParent)
  : Base(parallel, pParent)
{}

template < class Problem >
CProblemContext< Problem >::~CProblemContext()
{}

#endif // COPASI_CProblemContext
