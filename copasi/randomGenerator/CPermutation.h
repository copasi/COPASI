// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CPermutation
#define COPASI_CPermutation

#include <set>

#include "copasi/core/CVector.h"

class CRandom;

class CPermutation
{
public:
  /**
   * Default constructor
   */
  CPermutation() = delete;

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
  virtual void shuffle();

  /**
   * Create a unique permutation
   */
  void createUniquePermutation(std::set< const CPermutation * > & permutations);

   /**
   * Pick a random element
   */
  const size_t & pick();

  /**
   * Pick the next element
   */
  const size_t & next();

  /**
   * Retrieve the permuted vector
   * @return const CVector< size_t > & vector
   */
  const CVector< size_t > & getVector() const;

protected:
  constexpr static size_t InvalidIndex = std::numeric_limits< size_t >::max();
  constexpr static size_t MaxCount = 1000;

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
