/**
 *  CFluxMode class.
 *  Used to return the flux modes in human readable form
 *
 *  Created for Copasi by Stefan Hoops 2002-05-10
 * (C) Stefan Hoops 2002
 */

// #define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFluxMode.h"
#include "CTableauLine.h"
CFluxMode::CFluxMode() {CONSTRUCTOR_TRACE; }

CFluxMode::CFluxMode(const CFluxMode & src) :
    mReactions(src.mReactions), mReversible(src.mReversible)
{CONSTRUCTOR_TRACE; }

CFluxMode::CFluxMode(const CTableauLine * line)
{
  CONSTRUCTOR_TRACE;
  const vector < C_FLOAT64 > & FluxMode = line->getFluxMode();
  unsigned C_INT32 i, imax = FluxMode.size();

  pair < unsigned C_INT32, C_FLOAT64 > Entry;

  for (i = 0; i < imax; i++)
    if (FluxMode[i])
      {
        Entry.first = i;
        Entry.second = FluxMode[i];
        mReactions.push_back(Entry);
      }

  mReversible = line->isReversible();
}
CFluxMode::~CFluxMode() {DESTRUCTOR_TRACE; }

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
