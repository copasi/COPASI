// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Modified by Stefan Hoops for COPASI in [2026] to add re-entrancy.
 * Originally derived from SOBOL (https://people.math.sc.edu/burkardt/cpp_src/sobol/sobol.html)
 * Retrieved at: 2026-06-20
 * This file is licensed under the GNU Lesser General Public License.
 */

#pragma once

#include "copasi/core/CCore.h"
#include "copasi/core/CVector.h"

class CSobolSequence
{
private:
  static C_INT32 bit_lo0(C_INT64 n);

  constexpr static C_INT32 DIM_MAX = 40;
  constexpr static C_INT32 DIM_MAX2 = 1111;
  constexpr static C_INT32 LOG_MAX = 62;

public:
  CSobolSequence() = delete;
  CSobolSequence(const CSobolSequence & src) = delete;
  CSobolSequence(const C_INT32 & dimension);

  ~CSobolSequence();

  void seed(C_INT64 seed);

  void operator()(CVectorCore<C_FLOAT64> & point);

private:
  C_INT32 mDimension;
  C_FLOAT64 mReciprocal;
  C_INT64 mSeed;
  C_INT64 mPoint[DIM_MAX2];
  C_INT64 mV[DIM_MAX2][LOG_MAX];
};
