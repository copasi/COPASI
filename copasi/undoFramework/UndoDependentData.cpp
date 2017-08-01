// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "UndoDependentData.h"
#include "CCopasiUndoCommand.h"
#include "UndoCompartmentData.h"
#include "UndoSpeciesData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoReactionData.h"
#include "UndoEventData.h"

#include "copasi/core/CDataObject.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/UI/listviews.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"

UndoDependentData::UndoDependentData(const CModelEntity *pObject)
{
  initializeFrom(pObject);
}

UndoDependentData::UndoDependentData()
{
}

UndoDependentData::~UndoDependentData()
{
  freeUndoData();
}

void
UndoDependentData::initializeFrom(const CModelEntity* pObject)
{
  CDataObject::DataObjectSet Descendants;
  pObject->getDescendants(Descendants, true);
  initializeFrom(Descendants);
}

void
UndoDependentData::initializeFrom(const CReaction* pObject)
{
  CDataObject::DataObjectSet Descendants;
  pObject->getDescendants(Descendants, true);
  Descendants.insert(pObject);
  initializeFrom(Descendants);
}

void UndoDependentData::fillIn(CModel *pModel)
{
  fillDependentObjects(pModel, &mCompartmentData);
  fillDependentObjects(pModel, &mSpeciesData);
  fillDependentObjects(pModel, &mParameterData);
  fillDependentObjects(pModel, &mReactionData);
  fillDependentObjects(pModel, &mEventData);
}

void UndoDependentData::createIn(CModel *pModel)
{
  createDependentObjects(pModel, &mCompartmentData);
  createDependentObjects(pModel, &mSpeciesData);
  createDependentObjects(pModel, &mParameterData);
  createDependentObjects(pModel, &mReactionData);
  createDependentObjects(pModel, &mEventData);
}

void
UndoDependentData::restoreIn(CModel *pModel)
{
  restoreDependentObjects(pModel, &mCompartmentData);
  restoreDependentObjects(pModel, &mSpeciesData);
  restoreDependentObjects(pModel, &mParameterData);
  restoreDependentObjects(pModel, &mReactionData);
  restoreDependentObjects(pModel, &mEventData);
}

void UndoDependentData::createDependentObjects(CModel *pModel,
    QList<UndoGlobalQuantityData *> *pGlobalQuantityData)
{
  //reinsert the dependency global quantity
  if (pModel == NULL || pGlobalQuantityData == NULL || pGlobalQuantityData->empty())
    return;

  QList <UndoGlobalQuantityData *>::const_iterator g;

  for (g = pGlobalQuantityData->begin(); g != pGlobalQuantityData->end(); ++g)
    {
      UndoGlobalQuantityData* data = *g;
      CDataObject *pGlobalQuantity = data->createObjectIn(pModel);

      if (pGlobalQuantity == NULL) continue;

      updateGUI(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());
    }
}

void UndoDependentData::createDependentObjects(CModel *pModel, QList<UndoReactionData *> *reactionData)
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

      CDataObject *pRea = rData->createObjectIn(pModel);

      if (pRea == NULL) continue;

      updateGUI(ListViews::REACTION, ListViews::ADD, pRea->getKey());
    }
}

void UndoDependentData::createDependentObjects(CModel *pModel, QList<UndoEventData *> *pEventData)
{
  if (pModel == NULL || pEventData == NULL || pEventData->empty())
    return;

  //reinsert the dependency events
  QList <UndoEventData *>::const_iterator ev;

  for (ev = pEventData->begin(); ev != pEventData->end(); ++ev)
    {
      UndoEventData* data = *ev;
      CDataObject* pEvent = data->createObjectIn(pModel);

      if (pEvent == NULL) continue;

      updateGUI(ListViews::EVENT, ListViews::ADD, pEvent->getKey());
    }
}

void UndoDependentData::createDependentObjects(CModel *pModel, QList<UndoSpeciesData *> *pSpeciesData)
{
  if (pModel == NULL || pSpeciesData == NULL || pSpeciesData->empty())
    return;

  //reaction may further has dependencies, these must be taken care of
  QList <UndoSpeciesData *>::const_iterator rs;

  for (rs = pSpeciesData->begin(); rs != pSpeciesData->end(); ++rs)
    {
      UndoSpeciesData * data = *rs;

      CDataObject* pSpecies = data->createObjectIn(pModel);

      if (pSpecies == NULL)
        continue;

      updateGUI(ListViews::METABOLITE, ListViews::ADD, pSpecies->getKey());
    }
}

void UndoDependentData::createDependentObjects(CModel *pModel, QList<UndoCompartmentData *> *pCompartmentData)
{
  if (pModel == NULL || pCompartmentData == NULL || pCompartmentData->empty())
    return;

  //reaction may further has dependencies, these must be taken care of
  QList <UndoCompartmentData *>::const_iterator rs;

  for (rs = pCompartmentData->begin(); rs != pCompartmentData->end(); ++rs)
    {
      UndoCompartmentData * data = *rs;

      CDataObject* pCompartment = data->createObjectIn(pModel);

      if (pCompartment == NULL)
        continue;

      updateGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());
    }
}

void UndoDependentData::restoreDependentObjects(CModel *pModel,
    QList<UndoGlobalQuantityData *> *pGlobalQuantityData)
{
  //reinsert the dependency global quantity
  if (pModel == NULL || pGlobalQuantityData == NULL || pGlobalQuantityData->empty())
    return;

  QList <UndoGlobalQuantityData *>::const_iterator g;

  for (g = pGlobalQuantityData->begin(); g != pGlobalQuantityData->end(); ++g)
    {
      UndoGlobalQuantityData* data = *g;
      CDataObject *pGlobalQuantity = data->restoreObjectIn(pModel);

      if (pGlobalQuantity == NULL) continue;

      data->restoreDependentObjects(pModel);

      updateGUI(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());
    }
}

void UndoDependentData::restoreDependentObjects(CModel *pModel, QList<UndoReactionData *> *reactionData)
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

      CDataObject *pRea = rData->restoreObjectIn(pModel);

      rData->restoreDependentObjects(pModel);

      updateGUI(ListViews::REACTION, ListViews::ADD, pRea->getKey());
    }
}

void UndoDependentData::restoreDependentObjects(CModel *pModel, QList<UndoEventData *> *pEventData)
{
  if (pModel == NULL || pEventData == NULL || pEventData->empty())
    return;

  //reinsert the dependency events
  QList <UndoEventData *>::const_iterator ev;

  for (ev = pEventData->begin(); ev != pEventData->end(); ++ev)
    {
      UndoEventData* data = *ev;
      CDataObject* pEvent = data->restoreObjectIn(pModel);

      if (pEvent == NULL) continue;

      data->restoreDependentObjects(pModel);

      updateGUI(ListViews::EVENT, ListViews::ADD, pEvent->getKey());
    }
}

void UndoDependentData::restoreDependentObjects(CModel *pModel, QList<UndoSpeciesData *> *pSpeciesData)
{
  if (pModel == NULL || pSpeciesData == NULL || pSpeciesData->empty())
    return;

  //reaction may further has dependencies, these must be taken care of
  QList <UndoSpeciesData *>::const_iterator rs;

  for (rs = pSpeciesData->begin(); rs != pSpeciesData->end(); ++rs)
    {
      UndoSpeciesData * data = *rs;

      CDataObject * pSpecies = data->restoreObjectIn(pModel);

      if (pSpecies == NULL)
        continue;

      data->restoreDependentObjects(pModel);

      updateGUI(ListViews::METABOLITE, ListViews::ADD, pSpecies->getKey());
    }
}

void UndoDependentData::restoreDependentObjects(CModel *pModel, QList<UndoCompartmentData *> *pCompartmentData)
{
  if (pModel == NULL || pCompartmentData == NULL || pCompartmentData->empty())
    return;

  //reaction may further has dependencies, these must be taken care of
  QList <UndoCompartmentData *>::const_iterator rs;

  for (rs = pCompartmentData->begin(); rs != pCompartmentData->end(); ++rs)
    {
      UndoCompartmentData * data = *rs;

      CDataObject* pCompartment = data->restoreObjectIn(pModel);

      if (pCompartment == NULL)
        continue;

      data->restoreDependentObjects(pModel);

      updateGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());
    }
}

void UndoDependentData::fillDependentObjects(CModel *pModel,
    QList<UndoGlobalQuantityData *> *pGlobalQuantityData)
{
  //reinsert the dependency global quantity
  if (pModel == NULL || pGlobalQuantityData == NULL || pGlobalQuantityData->empty())
    return;

  QList <UndoGlobalQuantityData *>::const_iterator g;

  for (g = pGlobalQuantityData->begin(); g != pGlobalQuantityData->end(); ++g)
    {
      UndoGlobalQuantityData* data = *g;
      data->fillObject(pModel);
    }
}

void UndoDependentData::fillDependentObjects(CModel *pModel, QList<UndoReactionData *> *reactionData)
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

      rData->fillObject(pModel);
    }
}

void UndoDependentData::fillDependentObjects(CModel *pModel, QList<UndoEventData *> *pEventData)
{
  if (pModel == NULL || pEventData == NULL || pEventData->empty())
    return;

  //reinsert the dependency events
  QList <UndoEventData *>::const_iterator ev;

  for (ev = pEventData->begin(); ev != pEventData->end(); ++ev)
    {
      UndoEventData* data = *ev;
      data->fillObject(pModel);
    }
}

void UndoDependentData::fillDependentObjects(CModel *pModel, QList<UndoSpeciesData *> *pSpeciesData)
{
  if (pModel == NULL || pSpeciesData == NULL || pSpeciesData->empty())
    return;

  //reaction may further has dependencies, these must be taken care of
  QList <UndoSpeciesData *>::const_iterator rs;

  for (rs = pSpeciesData->begin(); rs != pSpeciesData->end(); ++rs)
    {
      UndoSpeciesData * data = *rs;

      data->fillObject(pModel);
    }
}

void UndoDependentData::fillDependentObjects(CModel *pModel, QList<UndoCompartmentData *> *pCompartmentData)
{
  if (pModel == NULL || pCompartmentData == NULL || pCompartmentData->empty())
    return;

  //reaction may further has dependencies, these must be taken care of
  QList <UndoCompartmentData *>::const_iterator rs;

  for (rs = pCompartmentData->begin(); rs != pCompartmentData->end(); ++rs)
    {
      UndoCompartmentData * data = *rs;

      data->fillObject(pModel);
    }
}

void
UndoDependentData::freeUndoData()
{
  foreach (UndoCompartmentData * data, mCompartmentData)
    {
      delete data;
    }

  mCompartmentData.clear();

  foreach (UndoSpeciesData * data, mSpeciesData)
    {
      delete data;
    }

  mSpeciesData.clear();

  foreach (UndoGlobalQuantityData * data, mParameterData)
    {
      delete data;
    }

  mParameterData.clear();

  foreach (UndoReactionData * data, mReactionData)
    {
      delete data;
    }

  mReactionData.clear();

  foreach (UndoEventData * data, mEventData)
    {
      delete data;
    }

  mEventData.clear();
}

void
UndoDependentData::initializeFrom(const std::set< const CDataObject * > &deletedObjects)
{
  freeUndoData();

  if (deletedObjects.size() == 0)
    return;

  CDataObject::ObjectSet DeletedObjects;

  std::set< const CDataModel * > DMs;
  CDataObject::DataObjectSet::const_iterator it = deletedObjects.begin();
  CDataObject::DataObjectSet::const_iterator end = deletedObjects.end();

  for (; it != end; ++it)
    {
      DeletedObjects.insert(*it);
      CDataModel * pDataModel = (*it)->getObjectDataModel();

      if (pDataModel != NULL)
        {
          DMs.insert(pDataModel);
        }
      else
        {
          // We may have a unit definition or a function which may be used in any data model.
          CDataVector< CDataModel >::const_iterator itDM = CRootContainer::getDatamodelList()->begin();
          CDataVector< CDataModel >::const_iterator endDM = CRootContainer::getDatamodelList()->end();

          for (; itDM != endDM; ++itDM)
            {
              DMs.insert(&*itDM);
            }

          break;
        }
    }

  if (DMs.size() == 0)
    return;

  //TODO presently assume only reaction objects can be deleted when GlobalQuantity is deleted
  CDataObject::DataObjectSet Functions;
  CDataObject::DataObjectSet Units;

  // First check whether any units depend on the deleted objects since functions may have units.
  CRootContainer::getUnitList()->appendDependentUnits(deletedObjects, Units);

  it = Units.begin();
  end = Units.end();
  DeletedObjects.insert(it, end);

  for (; it != end; ++it)
    {
      // TODO store the unit data
    }

  // Check whether any functions depend on the deleted objects
  CRootContainer::getFunctionList()->appendDependentFunctions(DeletedObjects, Functions);
  it = Functions.begin();
  end = Functions.end();
  DeletedObjects.insert(it, end);

  for (; it != end; ++it)
    {
      // TODO store the function data
    }

  std::set< const CDataModel * >::const_iterator itDM = DMs.begin();
  std::set< const CDataModel * >::const_iterator endDM = DMs.end();

  for (; itDM != endDM; ++itDM)
    {
      const CModel* pModel = (*itDM)->getModel();

      if (pModel == NULL)
        continue;

      CDataObject::DataObjectSet Reactions;
      CDataObject::DataObjectSet Metabolites;
      CDataObject::DataObjectSet Values;
      CDataObject::DataObjectSet Compartments;
      CDataObject::DataObjectSet Events;
      CDataObject::DataObjectSet EventAssignments;

      pModel->appendAllDependents(DeletedObjects, Reactions, Metabolites, Compartments, Values, Events, EventAssignments);

      if (Reactions.size() > 0)
        {
          std::set< const CDataObject * >::const_iterator it = Reactions.begin();
          std::set< const CDataObject * >::const_iterator end = Reactions.end();

          for (; it != end; ++it)
            {
              //store the Reactions data
              const CReaction * pRea = dynamic_cast<const CReaction*>(*it);

              if (pRea == NULL) continue;

              UndoReactionData *data = new UndoReactionData(pRea, false);
              mReactionData.append(data);
            }
        }

      if (Metabolites.size() > 0)
        {
          std::set< const CDataObject * >::const_iterator it = Metabolites.begin();
          std::set< const CDataObject * >::const_iterator end = Metabolites.end();

          for (; it != end; ++it)
            {
              //store the Metabolites data
              const CMetab * pMetab = dynamic_cast<const CMetab*>(*it);

              if (pMetab == NULL) continue;

              UndoSpeciesData *data = new UndoSpeciesData(pMetab, false);
              mSpeciesData.append(data);
            }
        }

      if (Compartments.size() > 0)
        {
          std::set< const CDataObject * >::const_iterator it = Compartments.begin();
          std::set< const CDataObject * >::const_iterator end = Compartments.end();

          for (; it != end; ++it)
            {
              const CCompartment * pCompartment = dynamic_cast<const CCompartment*>(*it);

              if (pCompartment == NULL)
                continue;

              //store the Global Quantity data
              UndoCompartmentData *data = new UndoCompartmentData(pCompartment, false);
              mCompartmentData.append(data);
            }
        }

      if (Values.size() > 0)
        {
          std::set< const CDataObject * >::const_iterator it = Values.begin();
          std::set< const CDataObject * >::const_iterator end = Values.end();

          for (; it != end; ++it)
            {
              const CModelValue * pModelValue = dynamic_cast<const CModelValue*>(*it);

              if (pModelValue == NULL)
                continue;

              //store the Global Quantity data
              UndoGlobalQuantityData *data = new UndoGlobalQuantityData(pModelValue, false);
              mParameterData.append(data);
            }
        }

      if (Events.size() > 0)
        {
          std::set< const CDataObject * >::const_iterator it = Events.begin();
          std::set< const CDataObject * >::const_iterator end = Events.end();

          for (; it != end; ++it)
            {
              //store the Event data
              const CEvent * pEvent = dynamic_cast<const CEvent*>(*it);

              UndoEventData *data = new UndoEventData(pEvent);
              mEventData.append(data);
            }
        }

      if (EventAssignments.size() > 0)
        {
          std::set< const CDataObject * >::const_iterator it = EventAssignments.begin();
          std::set< const CDataObject * >::const_iterator end = EventAssignments.end();

          for (; it != end; ++it)
            {
              //store the Event data
              const CEvent * pEvent = dynamic_cast<const CEvent*>((*it)->getObjectAncestor("Event"));

              if (Events.find(pEvent) == Events.end())
                {
                  UndoEventData *data = new UndoEventData(pEvent);
                  mEventData.append(data);

                  Events.insert(pEvent);
                }
            }
        }
    }
}
