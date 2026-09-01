// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Modified by Stefan Hoops for COPASI in [2026].
 * Originally derived from SOBOL (https://github.com/RomboDev/Miscellaneous/blob/master/MRbluenoisepointsets/MRperm.cpp)
 * Retrieved at: 2026-06-20
 */

#pragma once

#include "copasi/randomGenerator/CPermutation.h"

class CRandom;

class CBalancedPermutation: public CPermutation
{
  /**
   * Default constructor
   */
  CBalancedPermutation() = delete;

public:
  /**
   * Specific constructor
   * @param CRandom * pRandom
   * @param const size_t & size
   */
  CBalancedPermutation(CRandom * pRandom, const size_t & size);

  /**
   * Copy constructor
   * @param const CPermutation & src
   */
  CBalancedPermutation(const CBalancedPermutation & src);

  /**
   * Destructor
   */
  ~CBalancedPermutation();

  /**
   * Shuffle the permutation
   */
  void shuffle() override;
};
