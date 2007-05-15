// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxScore.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/05/15 13:46:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CFluxScore class.
 *  Used to compare flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include <limits>

#include "copasi.h"
#include "CFluxScore.h"

CFluxScore::CFluxScore(){CONSTRUCTOR_TRACE;}

CFluxScore::CFluxScore(const std::vector < C_FLOAT64 > & fluxMode)
{
  CONSTRUCTOR_TRACE;
  unsigned char Remainder = fluxMode.size() % (CHAR_BIT * sizeof(unsigned char));
  unsigned char imax = fluxMode.size() / (CHAR_BIT * sizeof(unsigned char));
  unsigned char k, kmax = CHAR_BIT * sizeof(unsigned char);

  // Size the scoring vector.
  // Note we have to allocate an extra int if Remainder != 0
  mScore.resize(imax + (Remainder ? 1 : 0));

  std::vector < C_FLOAT64 >::const_iterator itMode = fluxMode.begin();
  unsigned char * pScore = mScore.array();
  unsigned char * pScoreEnd = pScore + imax;

  // Set the bits to 1 if the corresponding fluxMode coefficient is non zero.
  for (; pScore != pScoreEnd; ++pScore)
    {
      *pScore = 0;

      for (k = kmax; k > 0; ++itMode)
        {
          k--;

          if (*itMode != 0)
            (*pScore) |= (0x01 << k);
        }
    }

  // Do the same for the remaining fluxMode coefficients.
  if (Remainder)
    {
      k = kmax;
      kmax -= Remainder;

      *pScore = 0;

      for (; k > kmax; ++itMode)
        {
          k--;

          if (*itMode != 0)
            (*pScore) |= (0x01 << k);
        }
    }
}

CFluxScore::~CFluxScore(){DESTRUCTOR_TRACE;}

bool CFluxScore::operator <(const CFluxScore & rhs) const
  {
    const unsigned char * pScoreLhs = mScore.array();
    const unsigned char * pScoreRhs = rhs.mScore.array();
    const unsigned char * pScoreEnd = pScoreLhs + mScore.size();

    for (; pScoreLhs != pScoreEnd; ++pScoreLhs, ++pScoreRhs)
      if (*pScoreLhs != (*pScoreLhs & *pScoreRhs))
        return false;

    return true;
  }

std::ostream & operator << (std::ostream & os, const CFluxScore & A)
{
  const unsigned char * pScore = A.mScore.array();
  const unsigned char * pScoreEnd = pScore + A.mScore.size();
  unsigned char k, kmax = CHAR_BIT * sizeof(unsigned char);

  for (k = kmax; pScore != pScoreEnd; ++pScore)
    {
      k = kmax;

      while (k > 0)
        {
          k--;
          os << ((*pScore & (0x01 << k)) >> k);
        }
    }

  os << std::endl;

  return os;
}
