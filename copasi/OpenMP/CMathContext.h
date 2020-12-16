// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CMathContext
#define COPASI_CMathContext

#include "copasi/OpenMP/CContext.h"
#include "copasi/math/CMathContainer.h"

class CMathContext : public CContext< CMathContainer * >
{
public:
  CMathContext() = delete;

  CMathContext(const CMathContext & src) = delete;

  CMathContext(CMathContainer * pContainer);

  ~CMathContext();

  void setMathContainer(CMathContainer * pContainer);
};

#endif // COPASI_CMathContext
