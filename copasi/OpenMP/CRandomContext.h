// Copyright (C) 2021 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRandomContext
#define COPASI_CRandomContext

#include "copasi/OpenMP/CPointerContext.h"
#include "copasi/randomGenerator/CRandom.h"

class CRandomContext : public CPointerContext< CRandom >
{
public:
  typedef CPointerContext< CRandom > Base;

  CRandomContext() = delete;

  CRandomContext(const CRandomContext & src) = delete;

  CRandomContext(const bool & parallel);

  ~CRandomContext();

  void init(CRandom::Type type = CRandom::mt19937, unsigned C_INT32 seed = 0);
};

#endif // COPASI_CRandomContext
