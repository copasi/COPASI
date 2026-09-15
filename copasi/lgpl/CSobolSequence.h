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

#include <random>

#include "copasi/core/CCore.h"
#include "copasi/core/CVector.h"

class CSobolSequence
{
public:
  using result_type = unsigned C_INT64;
  static constexpr result_type min() {return MIN_RESULT;};
  static constexpr result_type max() {return MAX_RESULT;};

  CSobolSequence(const CSobolSequence & src) = default;
  CSobolSequence(result_type seed = 0, const C_INT32 & dimension = 1);
  ~CSobolSequence();

  void setDimension(const C_INT32 & dimension);
  const C_INT32 & getDimension() const;

  void seed(result_type seed = 0);
  result_type operator()();
  void discard(result_type z);

  void uniformI64(CVectorCore<C_INT64> & point);
  void uniformR64(CVectorCore<C_FLOAT64> & point);

private:
  static C_INT32 bit_lo0(C_INT64 n);
  void init();
  result_type next();

  constexpr static C_INT32 DIM_MAX = 1111;
  constexpr static C_INT32 LOG_MAX = 62;
  constexpr static result_type MIN_RESULT = 0;
  constexpr static result_type MAX_RESULT = 4611686018427387904; // 2^62
  constexpr static C_FLOAT64 mReciprocal = 1.0E+00 / (C_FLOAT64) MAX_RESULT;

  result_type mSeed;
  C_INT32 mDimension;
  result_type mPoint[DIM_MAX];
  result_type * mpNext;
  result_type mV[DIM_MAX][LOG_MAX];
};
