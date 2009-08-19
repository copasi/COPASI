// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CZeroSet.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/19 01:44:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CZeroSet
#define COPASI_CZeroSet

#include "copasi/utilities/CVector.h"

class CZeroSet
{
public:
  class CIndex
  {
    friend class CZeroSet;

    // Operations
  public:
    CIndex();

    CIndex(const CIndex & src);

    CIndex(const size_t & index);

    ~CIndex();

    CIndex & operator ++ ();

    CIndex & operator = (const CIndex & rhs);

    CIndex & operator = (const size_t & index);

    bool operator < (const CIndex & rhs) const;

    // Attributes
  private:
    size_t mIndex;
    size_t mBit;
  };

  CZeroSet(const size_t & index = 0);

  CZeroSet(const CZeroSet & src);

  ~CZeroSet();

  inline void setBit(const CIndex & index)
  {
    unsigned C_INT32 BitMask = 1 << index.mBit;

    mBitSet[index.mIndex] |= BitMask;
  }

  inline bool isSet(const CIndex & index) const
  {
    unsigned C_INT32 BitMask = 1 << index.mBit;

    return (mBitSet[index.mIndex] & BitMask) > 0;
  }

  inline CZeroSet & operator |= (const CZeroSet & rhs)
  {
    unsigned C_INT32 * pIt = mBitSet.array();
    unsigned C_INT32 * pEnd = pIt + mBitSet.size();
    const unsigned C_INT32 * pRhs = rhs.mBitSet.array();

    for (; pIt != pEnd; ++pIt, ++pRhs)
      {
        *pIt |= *pRhs;
      }
  }

  // Attributes
private:
  CVector<unsigned C_INT32> mBitSet;
};

#endif // COPASI_CZeroSet
