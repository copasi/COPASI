// Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRandomContext
#define COPASI_CRandomContext

#include "copasi/OpenMP/CPointerContext.h"
#include "copasi/randomGenerator/CRandom.h"

typedef CPointerContext< CRandom > CRandomContext;

#endif // COPASI_CRandomContext
