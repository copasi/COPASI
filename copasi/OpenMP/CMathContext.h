// Copyright (C) 2020 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CMathContext
#define COPASI_CMathContext

#include "copasi/OpenMP/CPointerContext.h"
#include "copasi/math/CMathContainer.h"

class CMathContext : public CPointerContext< CMathContainer >
{
public:
  typedef CPointerContext< CMathContainer > Base;

  CMathContext() = delete;

  CMathContext(const CMathContext & src) = delete;

  CMathContext(const bool & parallel);

  ~CMathContext();

  /**
   * Set the pointer to container used for calculations
   */
  void sync();
};

#endif // COPASI_CMathContext
