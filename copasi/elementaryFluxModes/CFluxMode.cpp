// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CFluxMode class.
 *  Used to return the flux modes in human readable form
 *
 *  Created for Copasi by Stefan Hoops 2002-05-10
 * (C) Stefan Hoops 2002
 */

#include "copasi/copasi.h"
#include "CFluxMode.h"
#include "CTableauLine.h"
#include "copasi/model/CModel.h"
//#include "copasi/model/CChemEqInterface.h"

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
