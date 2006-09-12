/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxScore.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/12 17:10:22 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CFluxScore class.
 *  Used to compare flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include "copasi.h"
#include "CFluxScore.h"

CFluxScore::CFluxScore(){CONSTRUCTOR_TRACE;}

CFluxScore::CFluxScore(const std::vector < C_FLOAT64 > & fluxMode)
{
  CONSTRUCTOR_TRACE;
  unsigned C_INT32 Remainder = fluxMode.size() % (8 * sizeof(int));
  unsigned C_INT32 imax = fluxMode.size() / (8 * sizeof(int));
  unsigned C_INT32 k, kmax = 8 * sizeof(unsigned C_INT32);

  // Size the scoring vector.
  // Note we have to allocate an extra int if Remainder != 0
  mScore.resize(imax + (Remainder ? 1 : 0));

  std::vector < C_FLOAT64 >::const_iterator itMode = fluxMode.begin();
  unsigned C_INT32 * pScore = mScore.array();
  unsigned C_INT32 * pScoreEnd = pScore + imax;

  // Set the bits to 1 if the corresponding fluxMode coefficient is non zero.
  for (; pScore != pScoreEnd; ++pScore)
    {
      *pScore = 0;

      for (k = kmax; k > 0; ++itMode)
        (*itMode) ? (*pScore) += 1 << --k : --k;
    }

  // Do the same for the remaining fluxMode coefficients.
  if (Remainder)
    {
      k = kmax;
      kmax -= Remainder;

      *pScore = 0;

      for (; k > kmax; ++itMode)
        (*itMode) ? (*pScore) += 1 << --k : --k;
    }
}

CFluxScore::~CFluxScore(){DESTRUCTOR_TRACE;}

bool CFluxScore::operator <(const CFluxScore & rhs) const
  {
    const unsigned C_INT32 * pScoreLhs = mScore.array();
    const unsigned C_INT32 * pScoreRhs = rhs.mScore.array();
    const unsigned C_INT32 * pScoreEnd = pScoreLhs + mScore.size();

    for (; pScoreLhs != pScoreEnd; ++pScoreLhs, ++pScoreRhs)
      if (*pScoreLhs != (*pScoreLhs & *pScoreRhs))
        return false;

    return true;
  }
