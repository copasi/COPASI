/**
 *  CTableauLine class.
 *  This store one row of the Tableau Matrix
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include "copasi.h"
#include "CTableauLine.h"

CTableauLine::CTableauLine() {mFluxScore=NULL;} 

CTableauLine::CTableauLine(const vector <C_FLOAT64> & reaction,
                           const C_INT32 & reversible,
                           const C_INT32 & reactionCounter,
                           const C_INT32 & reactionNumber)
{
  mReaction = reaction;
  mReversible = reversible;
  
  mFluxMode.resize(reactionNumber,0);
  mFluxMode[reactionCounter] = 1;
  
  mFluxScore = new CFluxScore(mFluxMode);
}

CTableauLine::CTableauLine(const C_FLOAT64 & m,
                           const CTableauLine & src1,
                           const CTableauLine & src2)
{
  unsigned C_INT32 i, imax = src1.mReaction.size();
  unsigned C_INT32 j, jmax = src2.mFluxMode.size();

  if (src1.mReversible == FALSE || src2.mReversible == FALSE)
    mReversible = FALSE;
  else
    mReversible = TRUE;
  
  for (i=0, mReaction.resize(imax); i<imax; i++)
    mReaction[i] = m * src1.mReaction[i] + src2.mReaction[i];
  
  for (j=0, mFluxMode.resize(jmax); j<jmax; j++)
    mFluxMode[i] = m * src1.mFluxMode[i] + src2.mFluxMode[i];

  mFluxScore = new CFluxScore(mFluxMode);
}

CTableauLine::~CTableauLine() {pdelete(mFluxScore);}

const CFluxScore & CTableauLine::getScore() const
{
  return *mFluxScore;
}

const C_FLOAT64 &
CTableauLine::getReaction(const unsigned C_INT32 & index) const
{
  return mReaction[index];
}

const C_FLOAT64 & 
CTableauLine::getFluxMode(const unsigned C_INT32 & index) const
{
  return mFluxMode[index];
}

bool CTableauLine::isReversible() const
{
  return mReversible;
}

