// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CStepMatrixColumn.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/24 18:13:13 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <math.h>
#include <limits>

#include "copasi.h"

#include "CStepMatrixColumn.h"

CStepMatrixColumn::CStepMatrixColumn(const size_t & size):
    mZeroSet(size),
    mReaction()
{}

CStepMatrixColumn::CStepMatrixColumn(const CZeroSet & set,
                                     CStepMatrixColumn const * pPositive,
                                     CStepMatrixColumn const * pNegative):
    mZeroSet(set),
    mReaction()
{
  C_INT32 GCD1 = -1;
  C_INT32 GCD2;

  C_INT32 PosMult = -pNegative->getMultiplier();
  C_INT32 NegMult = pPositive->getMultiplier();

  mReaction.resize(pPositive->mReaction.size());
  std::vector< C_INT32 >::iterator it = mReaction.begin();
  std::vector< C_INT32 >::iterator end = mReaction.end();

  std::vector< C_INT32 >::const_iterator itPos = pPositive->mReaction.begin();
  std::vector< C_INT32 >::const_iterator itNeg = pNegative->mReaction.begin();

  for (; it != end; ++it, ++itPos, ++itNeg)
    {
      *it = PosMult * *itPos + NegMult * *itNeg;

      if (*it == 0 || GCD1 == 1)
        {
          continue;
        }

      if (GCD1 == -1)
        {
          GCD1 = abs(*it);
          continue;
        }

      GCD2 = abs(*it);

      while (GCD1 != GCD2)
        {
          if (GCD1 > GCD2)
            {
              GCD1 -= GCD2;
            }
          else
            {
              GCD2 -= GCD1;
            }
        }
    }

  if (abs(GCD1) > 1)
    {
      for (it = mReaction.begin(); it != end; ++it)
        {
          *it /= GCD1;
        }
    }
}

CStepMatrixColumn::~CStepMatrixColumn()
{}

const CZeroSet & CStepMatrixColumn::getZeroSet() const
{
  return mZeroSet;
}

std::vector< C_INT32 > & CStepMatrixColumn::getReaction()
{
  return mReaction;
}

void CStepMatrixColumn::push_front(const C_INT32 & value)
{
  mReaction.insert(mReaction.begin(), value);
}

void CStepMatrixColumn::truncate()
{
  mReaction.pop_back();
}
