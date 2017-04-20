// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CPermutation
#define COPASI_CPermutation

#include "copasi/core/CVector.h"

class CRandom;

class CPermutation
{
private:
  static size_t InvalidIndex;

  /**
   * Default constructor
   */
  CPermutation();

public:
  /**
   * Specific constructor
   * @param CRandom * pRandom
   * @param const size_t & size
   */
  CPermutation(CRandom * pRandom, const size_t & size);

  /**
   * Copy constructor
   * @param const CPermutation & src
   */
  CPermutation(const CPermutation & src);

  /**
   * Destructor
   */
  ~CPermutation();

  /**
   * Initialize the permutation
   */
  void init();

  /**
   * Shuffle the permutation
   * const size_t & swaps (Default: size of permutation)
   */
  void shuffle(const size_t & swaps = C_INVALID_INDEX);

  /**
   * Pick a random element
   */
  const size_t & pick();

  /**
   * Pick the next element
   */
  const size_t & next();

private:
  // Attributes
  /**
   * A pointer to the random number generator to be used
   */
  CRandom * mpRandom;

  /**
   * A vector containing the permutation
   */
  CVector< size_t > mVector;

  /**
   * A pointer to the next index
   */
  size_t * mpNext;

  /**
   * A pointer beyond the last index
   */
  size_t * mpBeyond;
};

#endif // COPASI_CPermutation
