// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CArray.h"

CArray::CArray() :
  mDim(0)
{
  mData.resize(1);
}

CArray::CArray(const index_type & sizes)
{
  resize(sizes);
}

void CArray::resize(const index_type & sizes)
{
  mDim = sizes.size();
  mSizes = sizes;
  mFactors.resize(mDim);

  size_t tmpDataSize = 1;
  index_type::const_reverse_iterator it = sizes.rbegin();
  index_type::const_reverse_iterator itEnd = sizes.rend();
  index_type::reverse_iterator itFaktor = mFactors.rbegin();

  for (; it != itEnd; ++it, ++itFaktor)
    {
      *itFaktor = tmpDataSize;

      tmpDataSize *= *it;
    }

  mData.resize(tmpDataSize);
}

CArray::data_type & CArray::operator[](const index_type & index)
{
  static data_type Invalid;

  assert(index.size() == mDim);

  size_t tmpindex = 0;
  index_type::const_iterator itSize = mSizes.begin();
  index_type::const_iterator itFactor = mFactors.begin();
  index_type::const_iterator it = index.begin();
  index_type::const_iterator end = index.end();

  for (; it != end; ++it, ++itSize, ++itFactor)
    {
      if (*it >= *itSize) return Invalid;

      tmpindex += *itFactor **it;
    }

  return mData[tmpindex];
}

const CArray::data_type & CArray::operator[](const index_type & index) const
{
  static const data_type InvalidValue(std::numeric_limits< data_type >::quiet_NaN());

  assert(index.size() == mDim);

  size_t Index = 0;
  index_type::const_iterator itSize = mSizes.begin();
  index_type::const_iterator itFactor = mFactors.begin();
  index_type::const_iterator it = index.begin();
  index_type::const_iterator end = index.end();

  for (; it != end; ++it, ++itSize, ++itFactor)
    {
      if (*it >= *itSize) return InvalidValue;

      Index += *itFactor **it;
    }

  return mData[Index];
}

const CArray::index_type & CArray::size() const
{
  return mSizes;
}

size_t CArray::dimensionality() const
{
  return mDim;
}
