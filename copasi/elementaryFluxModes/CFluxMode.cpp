/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxMode.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $
   $Date: 2011/03/07 19:27:36 $
   End CVS Header */

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
  size_t i, imax = FluxMode.size();

  std::pair< size_t, C_FLOAT64 > Entry;

  for (i = 0; i < imax; i++)
    if (FluxMode[i])
      {
        mReactions[i] = FluxMode[i];
      }

  mReversible = line->isReversible();
}

CFluxMode::~CFluxMode()
{}

CFluxMode::const_iterator CFluxMode::begin() const
{
  return mReactions.begin();
}

CFluxMode::const_iterator CFluxMode::end() const
{
  return mReactions.end();
}

bool CFluxMode::isReversible() const
{
  return mReversible;
}

size_t CFluxMode::size() const
{
  return mReactions.size();
}

bool CFluxMode::isReversed(const CFluxMode &mode)
{
  if (mode.size() != mReactions.size())
    {
      return false;
    }

  const_iterator itThis = mReactions.begin();
  const_iterator endThis = mReactions.end();
  const_iterator itMode = mode.mReactions.begin();

  for (; itThis != endThis; ++itThis, ++itMode)
    {
      if (itThis->first != itMode->first)
        {
          return false;
        }
    }

  return true;
}

C_FLOAT64 CFluxMode::getMultiplier(const size_t & index) const
{
  const_iterator it = mReactions.find(index);

  if (it != mReactions.end())
    return it->second;

  return 0.0;
}
