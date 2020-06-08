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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTableauLine class.
 *  This store one row of the Tableau Matrix
 *
 *  Created for COPASI by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include <iostream>
#include <cmath>

#include "copasi/copasi.h"
#include "CTableauLine.h"

CTableauLine::CTableauLine() {CONSTRUCTOR_TRACE; mpFluxScore = NULL;}

CTableauLine::CTableauLine(const std::vector <C_FLOAT64> & reaction,
                           bool reversible,
                           const size_t & reactionCounter,
                           const size_t & reactionNumber)
{
  CONSTRUCTOR_TRACE;
  mReaction = reaction;
  mReversible = reversible;

  mFluxMode.resize(reactionNumber, 0);
  mFluxMode[reactionCounter] = 1;

  mpFluxScore = new CFluxScore(mFluxMode);
}

CTableauLine::CTableauLine(C_FLOAT64 m1,
                           const CTableauLine & src1,
                           C_FLOAT64 m2,
                           const CTableauLine & src2)
{
  CONSTRUCTOR_TRACE;

  // We need to remove common factors in m1 and m2
  reduce(m1, m2);

  mReversible = (src1.mReversible && src2.mReversible);

  mReaction.resize(src1.mReaction.size());
  mFluxMode.resize(src1.mFluxMode.size());

  std::vector< C_FLOAT64 >::const_iterator it1 = src1.mReaction.begin();
  std::vector< C_FLOAT64 >::const_iterator it2 = src2.mReaction.begin();
  std::vector< C_FLOAT64 >::iterator it = mReaction.begin();
  std::vector< C_FLOAT64 >::iterator end = mReaction.end();

  for (; it != end; ++it, ++it1, ++it2)
    *it = m1 * *it1 + m2 * *it2;

  it1 = src1.mFluxMode.begin();
  it2 = src2.mFluxMode.begin();
  it = mFluxMode.begin();
  end = mFluxMode.end();

  for (; it != end; ++it, ++it1, ++it2)
    *it = m1 * *it1 + m2 * *it2;

  mpFluxScore = new CFluxScore(mFluxMode);
}
CTableauLine::~CTableauLine() {DESTRUCTOR_TRACE; pdelete(mpFluxScore);}

const CFluxScore & CTableauLine::getScore() const
{
  return *mpFluxScore;
}

const C_FLOAT64 & CTableauLine::getMultiplier(const size_t & index) const
{return mReaction[mReaction.size() - index - 1];}

const std::vector < C_FLOAT64 > & CTableauLine::getFluxMode() const
{
  return mFluxMode;
}

bool CTableauLine::isReversible() const
{
  return mReversible;
}

/*
void CTableauLine::truncate()
{
  mReaction.pop_back();
}
 */
std::ostream & operator << (std::ostream & os, const CTableauLine & l)
{
  size_t i, imax = l.mReaction.size();
  size_t j, jmax = l.mFluxMode.size();

  if (l.isReversible())
    os << "reversible:  ";
  else
    os << "irreversible:";

  for (i = 0; i < imax; i++)
    os << "  " << l.mReaction[i];

  os << "\t";

  for (j = 0; j < jmax; j++)
    os << "  " << l.mFluxMode[j];

  os << std::endl;

  return os;
}

// static
void CTableauLine::reduce(C_FLOAT64 & r1, C_FLOAT64 & r2)
{
  if (floor(r1) != r1 || floor(r2) != r2)
    return;

  C_INT32 GCD1 = (C_INT32) fabs(r1);
  C_INT32 GCD2 = (C_INT32) fabs(r2);

  while (GCD1 != GCD2)
    {
      if (GCD1 > GCD2)
        {
          GCD1 %= GCD2;

          if (GCD1 == 0)
            {
              GCD1 = GCD2;
            }
        }
      else
        {
          GCD2 %= GCD1;

          if (GCD2 == 0)
            {
              GCD2 = GCD1;
            }
        }
    }

  r1 /= (C_FLOAT64) GCD1;
  r2 /= (C_FLOAT64) GCD2;
}
