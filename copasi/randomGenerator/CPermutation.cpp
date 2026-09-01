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

#include "copasi/copasi.h"

#include "CPermutation.h"
#include "CRandom.h"

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

  for (size_t & value : mVector)
    value = Index++;

  if (Index != 0)
    {
      mpNext = mVector.begin();
      mpBeyond = mVector.end();
    }
}

void CPermutation::shuffle()
{
  if (mpRandom == NULL || mpNext == NULL) return;

  if (mVector.size() > 1)
    {
      unsigned C_INT32 max = (unsigned C_INT32) mVector.size() - 1;

      // We swap each element once.
      size_t * pBegin = mVector.begin();
      size_t * pEnd = mVector.end();
      size_t * pIt;
      size_t * pTo;

      for (pIt = pBegin; pIt != pEnd; ++pIt)
        {
          pTo = pBegin + mpRandom->getRandomU(max);

          if (pTo != pIt)
            std::swap(*pIt, *pTo);
        }
    }
}

void CPermutation::createUniquePermutation(std::set< const CPermutation * > & permutations)
{
  bool Found = false;
  size_t Count = 0;

  while (!Found
         && Count < MaxCount)
    {
      ++Count;
      shuffle();

      for (const CPermutation * pPermutation : permutations)
        {
          if (mVector == pPermutation->mVector)
            {
              Found = false;
              break;
            }
        }
    }
}

const size_t & CPermutation::pick()
{
  if (mpRandom == NULL || mpNext == NULL) return InvalidIndex;

  if (mVector.size() > 1)
    mpNext = mVector.array() + mpRandom->getRandomU((unsigned C_INT32)mVector.size() - 1);

  return *mpNext;
}

const size_t & CPermutation::next()
{
  if (mpRandom == NULL || mpNext == NULL) return InvalidIndex;

  if (++mpNext >= mpBeyond)
    mpNext = mVector.array();

  return *mpNext;
}

const CVector< size_t > & CPermutation::getVector() const
{
  return mVector;
}
