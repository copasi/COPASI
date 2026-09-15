// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include "copasi/core/CCore.h"

class CR250
{
public:
  using result_type = unsigned C_INT32;
  static constexpr result_type min() {return MIN_RESULT;};
  static constexpr result_type max() {return MAX_RESULT;};

  CR250(const CR250 & src) = default;
  CR250(result_type seed = 0);
  ~CR250();

  void seed(result_type seed = 0);
  result_type operator()();
  void discard(result_type z);

  // Attributes
private:
  unsigned C_INT16 myrand(void);

  constexpr static result_type MIN_RESULT = 0;
  constexpr static result_type MAX_RESULT = 65535; // 2^16 - 1

  C_INT32 mIndex;
  result_type mSeed;
  unsigned C_INT16 mBuffer[250];
};
