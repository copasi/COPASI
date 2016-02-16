// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CCopasiArray.h"

CCopasiArray::CCopasiArray()
  : mDim(0) {mData.resize(1);}

CCopasiArray::CCopasiArray(const index_type & sizes)
{
  resize(sizes);
}

void CCopasiArray::resize(const index_type & sizes)
{
  mDim = sizes.size();
  mSizes = sizes;
  mFactors.resize(mDim);

  size_t tmpDataSize = 1;
  index_type::const_reverse_iterator it, itEnd = sizes.rend();
  index_type::reverse_iterator itFaktor;

  for (it = sizes.rbegin(), itFaktor = mFactors.rbegin(); it != itEnd; ++it, ++itFaktor)
    {
      *itFaktor = tmpDataSize;
      tmpDataSize *= *it;
    }

  mData.resize(tmpDataSize);
}

CCopasiArray::data_type & CCopasiArray::operator[](const index_type & index)
{
#ifdef COPASI_DEBUG
  assert(index.size() == mDim);
#endif

  size_t tmpindex = 0;
  index_type::const_iterator itSize = mSizes.begin();
  index_type::const_iterator itFactor = mFactors.begin();
  index_type::const_iterator it = index.begin();
  index_type::const_iterator end = index.end();

  for (; it != end; ++it, ++itSize, ++itFactor)
    {
      if (*it >= *itSize) return * (data_type *) NULL;

      tmpindex += *itFactor **it;
    }

  return mData[tmpindex];
}

const CCopasiArray::data_type & CCopasiArray::operator[](const index_type & index) const
{
#ifdef COPASI_DEBUG
  assert(index.size() == mDim);
#endif

  size_t tmpindex = 0;
  index_type::const_iterator itSize = mSizes.begin();
  index_type::const_iterator itFactor = mFactors.begin();
  index_type::const_iterator it = index.begin();
  index_type::const_iterator end = index.end();

  for (; it != end; ++it, ++itSize, ++itFactor)
    {
      if (*it >= *itSize) return * (const data_type *) NULL;

      tmpindex += *itFactor **it;
    }

  return mData[tmpindex];
}

const CCopasiArray::index_type & CCopasiArray::size() const
{return mSizes;}

size_t CCopasiArray::dimensionality() const
{return mDim;}
