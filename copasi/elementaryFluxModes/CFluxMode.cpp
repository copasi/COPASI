/**
 *  CFluxMode class.
 *  Used to return the flux modes in human readable form
 *
 *  Created for Copasi by Stefan Hoops 2002-05-10
 * (C) Stefan Hoops 2002
 */

#include "copasi.h"
#include "CFluxMode.h"

CFluxMode::CFluxMode() {}

CFluxMode::CFluxMode(const CTableauLine * line)
{
  const vector < C_FLOAT64 > & FluxMode = line->getFluxMode();
  unsigned C_INT32 i, imax = FluxMode.size();

  pair < unsigned C_INT32, C_FLOAT64 > Entry;

  for (i=0; i<imax; i++)
    if (FluxMode[i])
      {
        Entry.first = i;
        Entry.second = FluxMode[i];
        mReactions.push_back(Entry);
      }

  mReversible = line->isReversible();
}
CFluxMode::~CFluxMode() {}

const unsigned C_INT32 &
CFluxMode::getReaction(const unsigned C_INT32 & index) const
{
  return mReactions[index].first;
}

const C_FLOAT64 &
CFluxMode::getMultiplier(const unsigned C_INT32 & index) const
{
  return mReactions[index].second;
}

const bool & CFluxMode::isReversible() const
{
  return mReversible;
}

const unsigned C_INT32 CFluxMode::size() const
{
  return mReactions.size();
}
