// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CZeroSet.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/19 01:44:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CZeroSet.h"

CZeroSet::CIndex::CIndex():
    mIndex(0),
    mBit()
{}

CZeroSet::CIndex::CIndex(const CZeroSet::CIndex & src):
    mIndex(src.mIndex),
    mBit(src.mBit)
{}

CZeroSet::CIndex::CIndex(const size_t & index):
    mIndex(index / (CHAR_BIT * sizeof(unsigned C_INT32))),
    mBit(index % (CHAR_BIT * sizeof(unsigned C_INT32)))
{}

CZeroSet::CIndex::~CIndex()
{}

CZeroSet::CIndex & CZeroSet::CIndex::operator ++ ()
{
  if (mBit < CHAR_BIT * sizeof(unsigned C_INT32))
    mBit++;
  else
    {
      mBit = 0;
      mIndex++;
    }

  return *this;
}

CZeroSet::CIndex & CZeroSet::CIndex::operator = (const CZeroSet::CIndex & rhs)
{
  mIndex = rhs.mIndex;
  mBit = rhs.mBit;

  return *this;
}

CZeroSet::CIndex & CZeroSet::CIndex::operator = (const size_t & index)
{
  mIndex = index / (CHAR_BIT * sizeof(unsigned C_INT32));
  mBit = index % (CHAR_BIT * sizeof(unsigned C_INT32));

  return *this;
}

bool CZeroSet::CIndex::operator < (const CZeroSet::CIndex & rhs) const
{
  if (mIndex == rhs.mIndex)
    return mBit < rhs.mBit;

  return mIndex < rhs.mIndex;
}

CZeroSet::CZeroSet(const size_t & size):
    mBitSet(size)
{
  mBitSet = C_INVALID_INDEX;
}

CZeroSet::CZeroSet(const CZeroSet & src):
    mBitSet(src.mBitSet)
{}

CZeroSet::~CZeroSet()
{}
