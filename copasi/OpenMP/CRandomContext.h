// Copyright (C) 2021 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRandomContext
#define COPASI_CRandomContext

#include "copasi/OpenMP/CContext.h"
#include "copasi/randomGenerator/CConfigurableRNG.h"

class CRandomContext : public CContext< CConfigurableRNG >
{
public:
  typedef CContext< CConfigurableRNG > Base;

  CRandomContext() = delete;

  CRandomContext(const CRandomContext & src) = delete;

  CRandomContext(const bool & parallel);

  ~CRandomContext();

  void init(CConfigurableRNG::Type type = CConfigurableRNG::Type::MersenneTwister, CConfigurableRNG::result_type seed = 0);
};

#endif // COPASI_CRandomContext
