// Copyright (C) 2023 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CRandomContext.h"

CRandomContext::CRandomContext(const bool & parallel)
  : Base(parallel)
{}

CRandomContext::~CRandomContext()
{}

void  CRandomContext::init(CConfigurableRNG::Type type, CConfigurableRNG::result_type seed)
{
  Base::master().setType(type, seed);
  Base::init();

  if (Base::size() > 1)
    for (size_t i = 0; i < Base::size(); ++i)
      Base::threadData()[i].setType(type, Base::master().operator()());
}
