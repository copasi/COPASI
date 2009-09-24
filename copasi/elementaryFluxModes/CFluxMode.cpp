/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxMode.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $
   $Date: 2009/09/24 18:13:13 $
   End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CFluxMode class.
 *  Used to return the flux modes in human readable form
 *
 *  Created for Copasi by Stefan Hoops 2002-05-10
 * (C) Stefan Hoops 2002
 */

#include "copasi.h"
#include "CFluxMode.h"
#include "CTableauLine.h"
#include "model/CModel.h"
//#include "model/CChemEqInterface.h"

CFluxMode::CFluxMode() {CONSTRUCTOR_TRACE;}

CFluxMode::CFluxMode(const CFluxMode & src) :
    mReactions(src.mReactions),
    mReversible(src.mReversible)
{}

CFluxMode::CFluxMode(const std::map< size_t, C_FLOAT64 > & reactions,
                     const bool & reversible) :
    mReactions(reactions),
    mReversible(reversible)
{}

CFluxMode::CFluxMode(const CTableauLine * line)
{
  const std::vector< C_FLOAT64 > & FluxMode = line->getFluxMode();
  unsigned C_INT32 i, imax = FluxMode.size();

  std::pair< unsigned C_INT32, C_FLOAT64 > Entry;

  for (i = 0; i < imax; i++)
    if (FluxMode[i])
      {
        mReactions[i] = FluxMode[i];
      }

  mReversible = line->isReversible();
}

CFluxMode::~CFluxMode()
{}

// TODO CRITICAL Remove/replace this method with an iterator approach
size_t CFluxMode::getReactionIndex(const size_t & index) const
{
  if (index >= mReactions.size())
    return C_INVALID_INDEX;

  std::map< size_t, C_FLOAT64 >::const_iterator it = mReactions.begin();

  for (size_t i = 0; i < index; ++i)
    ++it;

  return it->first;
}

// TODO CRITICAL Remove/replace this method with an iterator approach
C_FLOAT64 CFluxMode::getMultiplier(const size_t & index) const
{
  if (index >= mReactions.size())
    return 0.0;

  std::map< size_t, C_FLOAT64 >::const_iterator it = mReactions.begin();

  for (size_t i = 0; i < index; ++i)
    ++it;

  return it->second;
}

bool CFluxMode::isReversible() const
{
  return mReversible;
}

unsigned C_INT32 CFluxMode::size() const
{
  return mReactions.size();
}

bool CFluxMode::isReversed(const CFluxMode &mode)
{
  if (mode.size() != mReactions.size())
    {
      return false;
    }

  // This assumes that the order of reactions is the same in both
  // This assumption is NOT true for the Bit Pattern Tree method
  std::map< size_t, C_FLOAT64 >::const_iterator itThis = mReactions.begin();
  std::map< size_t, C_FLOAT64 >::const_iterator endThis = mReactions.end();
  std::map< size_t, C_FLOAT64 >::const_iterator itMode = mode.mReactions.begin();

  for (; itThis != endThis; ++itThis, ++itMode)
    {
      if (itThis->first != itMode->first)
        {
          return false;
        }
    }

  return true;
}
