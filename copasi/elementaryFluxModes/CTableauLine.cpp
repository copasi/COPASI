/**
 *  CTableauLine class.
 *  This store one row of the Tableau Matrix
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include <iostream>

// #define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CTableauLine.h"
CTableauLine::CTableauLine() {CONSTRUCTOR_TRACE; mFluxScore = NULL;}

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

  mFluxScore = new CFluxScore(mFluxMode);
}

CTableauLine::CTableauLine(const C_FLOAT64 & m1,
                           const CTableauLine & src1,
                           const C_FLOAT64 & m2,
                           const CTableauLine & src2)
{
  CONSTRUCTOR_TRACE;
  unsigned C_INT32 i, imax = src1.mReaction.size();
  unsigned C_INT32 j, jmax = src2.mFluxMode.size();

  if (src1.mReversible == false || src2.mReversible == false)
    mReversible = false;
  else
    mReversible = true;

  for (i = 1, mReaction.resize(imax); i < imax; i++)
    mReaction[i] = m1 * src1.mReaction[i] + m2 * src2.mReaction[i];

  for (j = 0, mFluxMode.resize(jmax); j < jmax; j++)
    mFluxMode[j] = m1 * src1.mFluxMode[j] + m2 * src2.mFluxMode[j];

  mFluxScore = new CFluxScore(mFluxMode);
}
CTableauLine::~CTableauLine() {DESTRUCTOR_TRACE; pdelete(mFluxScore);}

const CFluxScore & CTableauLine::getScore() const
{
  return *mFluxScore;
}

const C_FLOAT64 &
CTableauLine::getReaction(const unsigned C_INT32 & index) const
{
  return mReaction[index];
}

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
  std::vector < C_FLOAT64 >::iterator i = mReaction.begin();

  mReaction.erase(i, i + 1);
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
