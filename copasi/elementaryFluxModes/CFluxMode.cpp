/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxMode.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $
   $Date: 2009/09/22 14:57:10 $
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

CFluxMode::CFluxMode(const std::vector < std::pair < unsigned C_INT32, C_FLOAT64 > > & reactions,
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
        Entry.first = i;
        Entry.second = FluxMode[i];
        mReactions.push_back(Entry);
      }

  mReversible = line->isReversible();
}

CFluxMode::~CFluxMode()
{}

unsigned C_INT32 CFluxMode::getReactionIndex(unsigned C_INT32 index) const
{
  return mReactions[index].first;
}

const C_FLOAT64 & CFluxMode::getMultiplier(unsigned C_INT32 index) const
{
  return mReactions[index].second;
}

bool CFluxMode::isReversible() const
{
  return mReversible;
}

unsigned C_INT32 CFluxMode::size() const
{
  return mReactions.size();
}
