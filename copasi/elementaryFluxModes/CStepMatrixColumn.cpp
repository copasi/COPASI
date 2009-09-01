// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CStepMatrixColumn.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/01 15:58:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <math.h>

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
    mReaction(pPositive->mReaction)
{
  C_FLOAT64 Multiplier = pPositive->getMultiplier() / pNegative->getMultiplier();

  std::vector< C_FLOAT64 >::const_iterator itNeg = pNegative->mReaction.begin();

  std::vector< C_FLOAT64 >::iterator it = mReaction.begin();
  std::vector< C_FLOAT64 >::iterator end = mReaction.end();

  for (; it != end; ++it, ++itNeg)
    {
      // std::cout << *it << " - " << Multiplier << " * " << *itNeg << " = ";

      *it -= Multiplier * *itNeg;

      if (fabs(*it) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          *it = 0.0;
        }

      // std::cout << *it << std::endl;
    }
}

CStepMatrixColumn::~CStepMatrixColumn()
{}

const CZeroSet & CStepMatrixColumn::getZeroSet() const
{
  return mZeroSet;
}

std::vector< C_FLOAT64 > & CStepMatrixColumn::getReaction()
{
  return mReaction;
}

void CStepMatrixColumn::push_front(const C_FLOAT64 & value)
{
  mReaction.insert(mReaction.begin(), value);
}

void CStepMatrixColumn::truncate()
{
  mReaction.pop_back();
}
