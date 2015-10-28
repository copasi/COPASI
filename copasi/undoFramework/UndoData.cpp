// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoData.cpp
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#include "UndoData.h"
#include <copasi/UI/qtUtilities.h>
#include <copasi/UI/listviews.h>

#include <copasi/undoFramework/UndoCompartmentData.h>
#include <copasi/undoFramework/UndoSpeciesData.h>
#include <copasi/undoFramework/UndoEventData.h>
#include <copasi/undoFramework/UndoReactionData.h>
#include <copasi/undoFramework/UndoGlobalQuantityData.h>

#include <copasi/model/CModel.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CReactionInterface.h>

#include <copasi/function/CExpression.h>

UndoData::UndoData(const std::string &key  /*= ""*/,
                   const std::string &name /*= ""*/,
                   const std::string &type /*= ""*/)
  : QObject()
  , mpData(NULL)
  , mKey(key)
  , mName(name)
  , mType(type)
{
}

UndoData::~UndoData()
{
}

void UndoData::restoreDependentObjects(CModel*)
{

}

const std::string &
UndoData::getName() const
{
  return mName;
}

void
UndoData::setName(const std::string &name)
{
  mName = name;
}

bool UndoData::hasName() const
{
  return mName.empty();
}

const std::string &
UndoData::getType() const
{
  return mType;
}

void UndoData::setType(const std::string &type)
{
  mType = type;
}

void UndoData::restoreDependentObjects(CModel *pModel,
                                       QList<UndoGlobalQuantityData *> *pGlobalQuantityData)
{
  //reinsert the dependency global quantity
  if (pModel == NULL || pGlobalQuantityData == NULL || pGlobalQuantityData->empty())
    return;


  QList <UndoGlobalQuantityData *>::const_iterator g;

  for (g = pGlobalQuantityData->begin(); g != pGlobalQuantityData->end(); ++g)
    {
      UndoGlobalQuantityData* data = *g;
      CModelValue *pGlobalQuantity = data->createQuantityFromData(pModel);

      if (pGlobalQuantity == NULL) continue;

      data->restoreDependentObjects(pModel);

      updateGUI(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());
    }


}

void UndoData::restoreDependentObjects(CModel *pModel, QList<UndoReactionData *> *reactionData)
{
  if (pModel == NULL || reactionData == NULL || reactionData->empty())
    return;


  QList <UndoReactionData *>::const_iterator j;

  for (j = reactionData->begin(); j != reactionData->end(); ++j)
    {

      UndoReactionData * rData = *j;

      //need to make sure reaction doesn't exist in the model already
      if (pModel->getReactions().getIndex(rData->getName()) != C_INVALID_INDEX)
        continue;

      CReaction *pRea = rData->createReactionFromData(pModel);

      CReaction *pRea =  pModel->createReaction(rData->getName());
      CChemEqInterface *chem = new CChemEqInterface(pModel);
      chem->setChemEqString(rData->getRi()->getChemEqString());
      chem->writeToChemEq(pRea->getChemEq());
      rData->getRi()->createMetabolites();
      rData->getRi()->createOtherObjects();
      rData->getRi()->writeBackToReaction(pRea);


      rData->restoreDependentObjects(pModel);

      updateGUI(ListViews::REACTION, ListViews::ADD, pRea->getKey());

    }

}

void UndoData::restoreDependentObjects(CModel *pModel, QList<UndoEventData *> *pEventData)
{
  if (pModel == NULL || pEventData == NULL || pEventData->empty())
    return;

  //reinsert the dependency events
  QList <UndoEventData *>::const_iterator ev;

  for (ev = pEventData->begin(); ev != pEventData->end(); ++ev)
    {
      UndoEventData* data = *ev;
      CEvent* pEvent = data->createEventFromData(pModel);

      if (pEvent == NULL) continue;

      data->restoreDependentObjects(pModel);

      updateGUI(ListViews::EVENT, ListViews::ADD, pEvent->getKey());
    }

}

void UndoData::restoreDependentObjects(CModel *pModel, QList<UndoSpeciesData *> *pSpeciesData)
{
  if (pModel == NULL || pSpeciesData == NULL || pSpeciesData->empty())
    return;

  //reaction may further has dependencies, these must be taken care of
  QList <UndoSpeciesData *>::const_iterator rs;

  for (rs = pSpeciesData->begin(); rs != pSpeciesData->end(); ++rs)
    {
      UndoSpeciesData * data = *rs;

      CMetab* pSpecies = data->createMetabFromData(pModel);

      if (pSpecies == NULL)
        continue;

      data->restoreDependentObjects(pModel);

      updateGUI(ListViews::METABOLITE, ListViews::ADD, pSpecies->getKey());

    }
}

void UndoData::restoreDependentObjects(CModel *pModel, QList<UndoCompartmentData *> *pCompartmentData)
{

}

const std::string &
UndoData::getKey() const
{
  return mKey;
}

void
UndoData::setKey(const std::string &key)
{
  mKey = key;
}

bool
UndoData::hasKey() const
{
  return mKey.empty();
}

