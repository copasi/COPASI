/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxMode.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/16 16:20:18 $
   End CVS Header */

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
#include "model/CModel.h"
#include "model/CChemEqInterface.h"

CFluxMode::CFluxMode() {CONSTRUCTOR_TRACE;}

CFluxMode::CFluxMode(const CFluxMode & src) :
    mReactions(src.mReactions), mReversible(src.mReversible)
{CONSTRUCTOR_TRACE;}

CFluxMode::CFluxMode(const CTableauLine * line)
{
  CONSTRUCTOR_TRACE;
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
CFluxMode::~CFluxMode() {DESTRUCTOR_TRACE;}

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

const CReaction * CFluxMode::getReaction(unsigned C_INT32 index, const CModel * model) const
  {return model->getReactions()[index];}

std::string CFluxMode::getReactionName(unsigned C_INT32 index, const CModel * model) const
  {return getReaction(index, model)->getObjectName();}

std::string CFluxMode::getReactionEquation(unsigned C_INT32 index, const CModel * model) const
  {return CChemEqInterface::getChemEqString(model, *getReaction(index, model), false);}
