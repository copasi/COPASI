/**
 *  CFluxScore class.
 *  Used to compare flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

// #define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFluxScore.h"

CFluxScore::CFluxScore(){CONSTRUCTOR_TRACE;}

CFluxScore::CFluxScore(const vector < C_FLOAT64 > & fluxMode)
{
  CONSTRUCTOR_TRACE;
  unsigned C_INT32 Remainder = fluxMode.size()%(8*sizeof(int));
  unsigned C_INT32 i, imax = fluxMode.size()/(8*sizeof(int));
  unsigned C_INT32 j, k;
  int * Score;
  
  // Size the scoring vector.
  // Note we have to allocate an extra int if Remainder != 0
  mScore.resize(imax + (Remainder ? 1 : 0));

  // Set the bits to 1 if the corresponding fluxMode coefficient is non zero.
  for (i=0, j = 0; i<imax; i++)
    {
      Score = &mScore[i];
      *Score = 0;
      
      for (k=8*sizeof(int)-1; k>(unsigned C_INT32)-1; k--)
        {
          fluxMode[j++] ? (*Score) += 1 << k : 0;
        }
    }
  
  // Do the same for the remaining fluxMode coefficients.
  if (Remainder)
    {
      Score = &mScore[i];
      *Score = 0;

      for (k=8*sizeof(int)-1; k>=8*sizeof(int)-Remainder; k--)
        {
          fluxMode[j++] ? (*Score) += 1 << k : 0;
        }
    }
}

CFluxScore::~CFluxScore(){DESTRUCTOR_TRACE;}

bool CFluxScore::operator <(const CFluxScore & rhs) const
{
  unsigned C_INT32 i, imax = mScore.size();
  const int * lhsScore;
  const int * rhsScore;
  
  for (i=0; i<imax; i++)
    {
      lhsScore = &mScore[i];
      rhsScore = &rhs.mScore[i];

      if (*lhsScore != (*lhsScore & *rhsScore)) return FALSE;
    }
  
  return TRUE;
}
