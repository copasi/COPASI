// Copyright (C) 2023 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CRandomContext.h"

CRandomContext::CRandomContext(const bool & parallel)
  : Base(parallel)
{}

CRandomContext::~CRandomContext()
{
  CConfigurableRNG * pRNG = Base::master();

  if (pRNG != nullptr)
    {
      Base::setMaster(nullptr);
      delete pRNG;
    }

  if (Base::size() > 1)
    for (size_t i = 0; i < Base::size(); ++i)
      delete Base::threadData()[i];
}

void  CRandomContext::init(CConfigurableRNG::Type type, CConfigurableRNG::result_type seed)
{
  Base::init();

  if (Base::master() != nullptr)
    {
      if (Base::master()->getType() == type
          && seed == 0)
        return;

      delete Base::master();
      Base::master() = nullptr;

      if (Base::size() > 1)
        for (size_t i = 0; i < Base::size(); ++i)
          delete Base::threadData()[i];
    }

  Base::setMaster(nullptr);

  Base::master() = CConfigurableRNG::create(type, seed);

  // We must not parallelize this to ensure higher reproducibility.
  if (Base::size() > 1)
    for (size_t i = 0; i < Base::size(); ++i)
      Base::threadData()[i] = CConfigurableRNG::create(type, Base::master()->operator()());
}
