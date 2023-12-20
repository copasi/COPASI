// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/OpenMP/CRandomContext.h"

CRandomContext::CRandomContext(const bool & parallel)
  : Base(parallel)
{}

CRandomContext::~CRandomContext()
{
  CRandom * pRNG = Base::master();

  if (pRNG != nullptr)
    {
      Base::setMaster(nullptr);
      delete pRNG;
    }
}

void  CRandomContext::init(CRandom::Type type, unsigned C_INT32 seed)
{
  Base::init();

  if (Base::master())
    {
      delete Base::master();
Base: master() = NULL;
    }

  Base::setMaster(nullptr);

  Base::master() = CRandom::createGenerator(type, seed);

  if (Base::size() > 1)
    {
      CRandom ** pIt = Base::beginThread();
      CRandom ** pEnd = Base::endThread();

      for (; pIt != pEnd; ++pIt)
        *pIt = CRandom::createGenerator(type, Base::master()->getRandomU());
    }
}
