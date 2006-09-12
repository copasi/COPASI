/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CTableauLine.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/12 18:01:48 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTableauLine class.
 *  This store one row of the Tableau Matrix
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include <iostream>

#include "copasi.h"
#include "CTableauLine.h"
CTableauLine::CTableauLine() {CONSTRUCTOR_TRACE; mpFluxScore = NULL;}

CTableauLine::CTableauLine(const std::vector <C_FLOAT64> & reaction,
                           bool reversible,
                           const C_INT32 & reactionCounter,
                           const C_INT32 & reactionNumber)
{
  CONSTRUCTOR_TRACE;
  mReaction = reaction;
  mReversible = reversible;

  mFluxMode.resize(reactionNumber, 0);
  mFluxMode[reactionCounter] = 1;

  mpFluxScore = new CFluxScore(mFluxMode);
}

CTableauLine::CTableauLine(const C_FLOAT64 & m1,
                           const CTableauLine & src1,
                           const C_FLOAT64 & m2,
                           const CTableauLine & src2)
{
  CONSTRUCTOR_TRACE;

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

const C_FLOAT64 & CTableauLine::getMultiplier() const
  {return mReaction.back();}

const std::vector < C_FLOAT64 > & CTableauLine::getFluxMode() const
  {
    return mFluxMode;
  }

bool CTableauLine::isReversible() const
  {
    return mReversible;
  }

void CTableauLine::truncate()
{
  mReaction.pop_back();
}

#ifdef XXXX
void CTableauLine::print(void) const
  {
    unsigned C_INT32 i, imax = mReaction.size();
    unsigned C_INT32 j, jmax = mFluxMode.size();

    if (isReversible())
      cout << "reversible:  ";
    else
      cout << "irreversible:";

    for (i = 0; i < imax; i++)
      cout << "  " << mReaction[i];

    cout << "\t";

    for (j = 0; j < jmax; j++)
      cout << "  " << mFluxMode[j];

    cout << endl;
  }

#endif // XXXX
