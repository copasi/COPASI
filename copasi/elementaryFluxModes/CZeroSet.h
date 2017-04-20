// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CZeroSet
#define COPASI_CZeroSet

#include <limits.h> // needed for CHAR_BIT, <limits.h> is not the same as <limits>

#include <vector>

#include "copasi/core/CVector.h"

class CStepMatrixColumn;

class CZeroSet
{
public:
  class CIndex
  {
    friend class CZeroSet;

    // Operations
  public:
    CIndex(const size_t & index = 0);

    CIndex(const CIndex & src);

    ~CIndex();

    CIndex & operator ++ ();

    CIndex & operator = (const CIndex & rhs);

    CIndex & operator = (const size_t & index);

    bool operator < (const CIndex & rhs) const;

    // Attributes
  private:
    size_t mIndex;
    size_t mBit;
    size_t mNotBit;
  };

  friend std::ostream & operator << (std::ostream &, const CZeroSet &);

  CZeroSet(const size_t & index = 0);

  CZeroSet(const CZeroSet & src);

  ~CZeroSet();

  inline void setBit(const CIndex & index)
  {
    mBitSet[index.mIndex] |= index.mBit;
    mNumberSetBits++;
  }

  inline void unsetBit(const CIndex & index)
  {
    mBitSet[index.mIndex] &= index.mNotBit;
    mNumberSetBits--;
  }

  inline bool isSet(const CIndex & index) const
  {
    return (mBitSet[index.mIndex] & index.mBit) > 0;
  }

  inline const size_t & getNumberOfSetBits() const
  {
    return mNumberSetBits;
  }

  inline size_t getNumberOfUnsetBits() const
  {
    return mBitSet.size() * CHAR_BIT * sizeof(size_t) - mIgnoredBits - mNumberSetBits;
  }

  inline size_t getNumberOfBits() const
  {
    return mBitSet.size() * CHAR_BIT * sizeof(size_t) - mIgnoredBits;
  }

  inline CZeroSet & operator |= (const CZeroSet & rhs)
  {
    size_t * pIt = mBitSet.array();
    size_t * pEnd = pIt + mBitSet.size();
    const size_t * pRhs = rhs.mBitSet.array();
    mNumberSetBits = 0;

    for (; pIt != pEnd; ++pIt, ++pRhs)
      {
        *pIt |= *pRhs;
        mNumberSetBits += countSetBits(*pIt);
      }

    mNumberSetBits -= mIgnoredBits;

    return *this;
  }

  inline CZeroSet & operator &= (const CZeroSet & rhs)
  {
    size_t * pIt = mBitSet.array();
    size_t * pEnd = pIt + mBitSet.size();
    const size_t * pRhs = rhs.mBitSet.array();
    mNumberSetBits = 0;

    for (; pIt != pEnd; ++pIt, ++pRhs)
      {
        *pIt &= *pRhs;
        mNumberSetBits += countSetBits(*pIt);
      }

    mNumberSetBits -= mIgnoredBits;

    return *this;
  }

  static inline
  CZeroSet intersection(const CZeroSet & set1, const CZeroSet & set2)
  {
    CZeroSet Intersection(set1);
    return Intersection &= set2;
  }

  // Superset
  inline bool operator >= (const CZeroSet & rhs) const
  {
    const size_t * pIt = mBitSet.array();
    const size_t * pEnd = pIt + mBitSet.size();
    const size_t * pRhs = rhs.mBitSet.array();

    for (; pIt != pEnd; ++pIt, ++pRhs)
      {
        if (*pIt != (*pIt | *pRhs))
          return false;
      }

    return true;
  }

  inline bool operator == (const CZeroSet & rhs) const
  {
    if (mNumberSetBits != rhs.mNumberSetBits)
      return false;

    return memcmp(mBitSet.array(), rhs.mBitSet.array(),
                  mBitSet.size() * sizeof(size_t)) == 0;
  }

  bool isExtremeRay(const std::vector< CStepMatrixColumn * > & columns) const;

  // Attributes
private:
  CVector<size_t> mBitSet;

  size_t mIgnoredBits;

  size_t mNumberSetBits;

  inline size_t countSetBits(size_t bits)
  {
    size_t numberOfBits = 0;

    for (size_t i = 0; i < CHAR_BIT * sizeof(size_t); ++i)
      {
        if ((bits >> i) & 1)
          {
            numberOfBits++;
          }
      }

    return numberOfBits;
  }
};

#endif // COPASI_CZeroSet
