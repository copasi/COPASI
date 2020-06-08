// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"

#include "CPermutation.h"
#include "CRandom.h"

// static
size_t CPermutation::InvalidIndex(C_INVALID_INDEX);

CPermutation::CPermutation() :
  mpRandom(NULL),
  mVector(),
  mpNext(NULL),
  mpBeyond(NULL)
{};

CPermutation::CPermutation(CRandom * pRandom, const size_t & size) :
  mpRandom(pRandom),
  mVector(size),
  mpNext(NULL),
  mpBeyond(NULL)
{
  init();
};

CPermutation::CPermutation(const CPermutation & src) :
  mpRandom(src.mpRandom),
  mVector(src.mVector),
  mpNext(NULL),
  mpBeyond(NULL)
{
  if (src.mpNext != NULL)
    {
      mpNext = mVector.array() + (src.mpNext - src.mVector.array());
      mpBeyond = mVector.array() + mVector.size();
    }
};

CPermutation::~CPermutation()
{}

void CPermutation::init()
{
  size_t Index = 0;
  size_t * pIt = mVector.array();
  size_t * pEnd = pIt + mVector.size();

  for (; pIt != pEnd; ++pIt, ++Index)
    {
      *pIt = Index;
    }

  if (Index != 0)
    {
      mpNext = mVector.array();
      mpBeyond = pEnd;
    }
}

void CPermutation::shuffle(const size_t & swaps)
{
  if (mpRandom == NULL || mpNext == NULL) return;

  if (mVector.size() > 1)
    {
      unsigned C_INT32 max = mVector.size() - 1;
      size_t Swaps = std::min(swaps, mVector.size());

      // We swap each element once.
      size_t tmp;
      size_t * pBegin = mVector.array();
      size_t * pIt = pBegin;
      size_t * pEnd = pIt + Swaps;
      size_t * pTo;

      for (; pIt != pEnd; ++pIt)
        {
          pTo = pBegin + mpRandom->getRandomU(max);

          if (pTo != pIt)
            {
              tmp = *pTo;
              *pTo = *pIt;
              *pIt = tmp;
            }
        }
    }
}

const size_t & CPermutation::pick()
{
  if (mpRandom == NULL || mpNext == NULL) return InvalidIndex;

  if (mVector.size() > 1)
    {
      mpNext = mVector.array() + mpRandom->getRandomU(mVector.size() - 1);
    }

  return *mpNext;
}

const size_t & CPermutation::next()
{
  if (mpRandom == NULL || mpNext == NULL) return InvalidIndex;

  mpNext++;

  if (mpNext >= mpBeyond)
    {
      mpNext -= mVector.size();
    }

  return *mpNext;
}
