// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * Modified by Stefan Hoops for COPASI in [2026].
 * Originally derived from SOBOL (https://github.com/RomboDev/Miscellaneous/blob/master/MRbluenoisepointsets/MRperm.cpp)
 * Retrieved at: 2026-06-20
 */

#include "copasi/copasi.h"

#include "copasi/randomGenerator/CBalancedPermutation.h"

CBalancedPermutation::CBalancedPermutation(CRandom * pRandom, const size_t & size) :
  CPermutation(pRandom, size + size % 2) // make sure the size is even
{}

CBalancedPermutation::CBalancedPermutation(const CBalancedPermutation & src) :
  CPermutation(src)
{};

CBalancedPermutation::~CBalancedPermutation()
{}

void CBalancedPermutation::shuffle()
{
  if (mpRandom == NULL
      || mpNext == NULL)
    return;

  size_t Size = mVector.size();
  size_t HalfSize = Size / 2;
  CVector< C_INT32 > Steps(Size);
  CVector< size_t > BalancedVector(Size);

  bool Found = false;
  size_t Count = 0;

  while (!Found
         && Count < MaxCount)
    {
      ++Count;

      init();
      shuffle();

      size_t * pIt = mVector.begin();
      size_t * pEnd = mVector.end();
      C_INT32 * pStep = Steps.begin();
      size_t Index = 0;

      for (; pIt != pEnd; ++pIt, ++pStep, ++Index)
        {
          *pStep = *pIt - HalfSize;

          if (*pStep >= 0)
            *pStep += 1;

          *pIt = Index;
        }

      Index = pick();

      BalancedVector[0] = Index;
      mVector[Index] = C_INVALID_INDEX;

      size_t i = 1;

      for (; i < Size; i++)
        {
          C_INT32 Step = 0;

          for (size_t j = 0; j < Size; j++)
            {
              Step = Steps[j];

              if (Step == 0)
                continue;

              C_INT32 NextElement = BalancedVector[i - 1] + Step;

              if (NextElement >= 0
                  && NextElement < Size
                  && mVector[NextElement] != C_INVALID_INDEX)
                {
                  BalancedVector[i] = NextElement;
                  mVector[NextElement] = C_INVALID_INDEX;
                  Steps[j] = 0;
                  break;
                }
              else
                Step = 0;
            }

          if (Step == 0)
            break;
        }

      if (i == Size)
        Found = true;
    }

  mVector = BalancedVector;
}
