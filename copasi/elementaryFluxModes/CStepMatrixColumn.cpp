// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include <stdlib.h>
#include <cmath>
#include <limits>

#include "copasi/copasi.h"

#include "CStepMatrixColumn.h"
#include "CBitPatternTreeMethod.h"

CStepMatrixColumn::CStepMatrixColumn(const size_t & size):
  mZeroSet(size),
  mReaction(),
  mIterator(NULL)
{}

CStepMatrixColumn::CStepMatrixColumn(const CZeroSet & set,
                                     CStepMatrixColumn const * pPositive,
                                     CStepMatrixColumn const * pNegative):
  mZeroSet(set),
  mReaction(),
  mIterator(NULL)
{
  C_INT64 PosMult = -pNegative->getMultiplier();
  C_INT64 NegMult = pPositive->getMultiplier();

  C_INT64 GCD1 = abs64(PosMult);
  C_INT64 GCD2 = abs64(NegMult);

  // Divide PosMult and NegMult by GCD(PosMult, NegMult);
  CBitPatternTreeMethod::GCD(GCD1, GCD2);

  if (GCD1 != 1)
    {
      PosMult /= GCD1;
      NegMult /= GCD1;
    }

  // -1 is used to identify the start of the GCD search.
  GCD1 = -1;

  mReaction.resize(pPositive->mReaction.size());
  std::vector< C_INT64 >::iterator it = mReaction.begin();
  std::vector< C_INT64 >::iterator end = mReaction.end();

  std::vector< C_INT64 >::const_iterator itPos = pPositive->mReaction.begin();
  std::vector< C_INT64 >::const_iterator itNeg = pNegative->mReaction.begin();

  for (; it != end; ++it, ++itPos, ++itNeg)
    {
      // TODO We need to check that we do not have numerical overflow
      *it = PosMult * *itPos + NegMult * *itNeg;

      if (*it == 0 || GCD1 == 1)
        {
          continue;
        }

      if (GCD1 == -1)
        {
          GCD1 = abs64(*it);
          continue;
        }

      GCD2 = abs64(*it);

      CBitPatternTreeMethod::GCD(GCD1, GCD2);
    }

  if (GCD1 > 1)
    {
      for (it = mReaction.begin(); it != end; ++it)
        {
          *it /= GCD1;
        }
    }
}

CStepMatrixColumn::~CStepMatrixColumn()
{
  assert(*mIterator = this);

  *mIterator = NULL;
}

const CZeroSet & CStepMatrixColumn::getZeroSet() const
{
  return mZeroSet;
}

std::vector< C_INT64 > & CStepMatrixColumn::getReaction()
{
  return mReaction;
}

void CStepMatrixColumn::getAllUnsetBitIndexes(CVector<size_t> & indexes) const
{
  size_t Size = mZeroSet.getNumberOfBits();
  indexes.resize(Size);
  size_t * pIndex = indexes.array();

  CZeroSet::CIndex Index;
  size_t i = 0;
  size_t imax = Size - mReaction.size();

  for (; i < imax; ++i, ++Index)
    {
      if (!mZeroSet.isSet(Index))
        {
          *pIndex = i;
          pIndex++;
        }
    }

  for (i = mReaction.size(); i > 0;)
    {
      --i;

      if (mReaction[i] != 0)
        {
          *pIndex = (mReaction.size() - i - 1) + imax;
          pIndex++;
        }
    }

  Size = pIndex - indexes.array();
  indexes.resize(Size, true);

  //DebugFile << *this << std::endl;
  //DebugFile << "@CSMC: " << indexes << std::endl;
}

void CStepMatrixColumn::push_front(const C_INT64 & value)
{
  mReaction.insert(mReaction.begin(), value);
}

void CStepMatrixColumn::truncate()
{
  mReaction.pop_back();
}

std::ostream & operator << (std::ostream & os, const CStepMatrixColumn & c)
{
  os << ' ';

  size_t Size = c.mZeroSet.getNumberOfBits();
  CZeroSet::CIndex Index;
  size_t i = 0;
  size_t imax = Size - c.mReaction.size();

  for (; i < imax; ++i, ++Index)
    {
      if (c.mZeroSet.isSet(Index))
        {
          os << "*\t";
        }
      else
        {
          os << ".\t";
        }
    }

  for (i = c.mReaction.size(); i > 0;)
    {
      --i;

      os << c.mReaction[i] << "\t";;
    }

  return os;
}
