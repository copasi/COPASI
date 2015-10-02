// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CCopasiUndoCommand.cpp
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"

#include "UndoReactionData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"
#include "UndoSpeciesData.h"
#include "UndoData.h"

#include "CCopasiUndoCommand.h"

CCopasiUndoCommand::CCopasiUndoCommand(const std::string& entityType /*= ""*/,
                                       CCopasiUndoCommand::Type type /*= INVALID_TYPE*/,
                                       const std::string& action /*= ""*/,
                                       const std::string& property /*= ""*/,
                                       const std::string& newValue /*= ""*/,
                                       const std::string& oldValue /*= ""*/,
                                       const std::string& name /*= ""*/
                                      )
  : QUndoCommand()
  , mpSpeciesData(new QList <UndoSpeciesData*>())
  , mpReactionData(new  QList <UndoReactionData*>())
  , mpGlobalQuantityData(new  QList <UndoGlobalQuantityData*>())
  , mpEventData(new  QList <UndoEventData*>())
  , mType(type)
  , undoState(false)
  , mNewValue(newValue)
  , mOldValue(oldValue)
  , mProperty(property)
  , mEntityType(entityType)
  , mAction(action)
  , mName(name)
{
}

CCopasiUndoCommand::~CCopasiUndoCommand()
{
  pdelete(mpSpeciesData);
  pdelete(mpReactionData);
  pdelete(mpGlobalQuantityData);
  pdelete(mpEventData);
}

Path CCopasiUndoCommand::pathFromIndex(const QModelIndex &index)
{
  QModelIndex iter = index;
  Path path;

  while (iter.isValid())
    {
      path.prepend(PathItem(iter.row(), iter.column()));
      iter = iter.parent();
    }

  return path;
}

QModelIndex
CCopasiUndoCommand::pathToIndex(
  const Path &path, const QAbstractItemModel *model)
{
  QModelIndex iter;

  for (int i = 0; i < path.size(); i++)
    {
      iter = model->index(path[i].first, path[i].second, iter);
    }

  return iter;
}

const CCopasiUndoCommand::Type&
CCopasiUndoCommand::getType() const
{
  return mType;
}

UndoData *CCopasiUndoCommand::getUndoData() const
{
  return NULL;
}

void CCopasiUndoCommand::setType(const CCopasiUndoCommand::Type & type)
{
  if (mType != type)
    {
      mType = type;
    }
}
void CCopasiUndoCommand::setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects)
{
  CCopasiUndoCommand::setDependentObjects(deletedObjects,
                                          *mpReactionData,
                                          *mpSpeciesData,
                                          *mpGlobalQuantityData,
                                          *mpEventData);
}

void CCopasiUndoCommand::setDependentObjects(
  const std::set<const CCopasiObject *> &deletedObjects,
  QList<UndoReactionData *> &reactionData,
  QList<UndoSpeciesData *> &speciesData,
  QList<UndoGlobalQuantityData *> &globalQuantityData,
  QList<UndoEventData *> &eventData)
{
  if (deletedObjects.size() == 0)
    return;

  // Determine the affected data model
  const CCopasiDataModel * pDataModel = (*deletedObjects.begin())->getObjectDataModel();

  // Determine the affected function DB
  CFunctionDB * pFunctionDB =
    dynamic_cast< CFunctionDB * >((*deletedObjects.begin())->getObjectAncestor("FunctionDB"));

  if (pDataModel == NULL && pFunctionDB == NULL)
    return;

  if (pFunctionDB != NULL)
    {
      // TODO In case a function is deleted we need to loop through all data models
      pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
    }
  else
    {
      pFunctionDB = CCopasiRootContainer::getFunctionList();
    }

  //TODO presently assume only reaction objects can be deleted when GlobalQuantity is deleted
  std::set< const CCopasiObject * > Functions;
  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;
  std::set< const CCopasiObject * > Events;

  bool Used = false;

  if (pFunctionDB != NULL)
    {
      Used |= pFunctionDB->appendDependentFunctions(deletedObjects, Functions);

      if (Functions.size() > 0)
        {
          std::set< const CCopasiObject * >::const_iterator it = Functions.begin();
          std::set< const CCopasiObject * >::const_iterator end = Functions.end();

          for (; it != end; ++it)
            {
              //TODO store the function data
            }
        }
    }


  if (pDataModel == NULL)
    return;

  const CModel* pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  Used |= pModel->appendDependentModelObjects(deletedObjects, Reactions, Metabolites,
          Compartments, Values, Events);

  if (Reactions.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
      std::set< const CCopasiObject * >::const_iterator end = Reactions.end();

      for (; it != end; ++it)
        {
          //store the Reactions data
          UndoReactionData *data = new UndoReactionData();
          data->setRi(new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel()));
          data->getRi()->initFromReaction((*it)->getKey());
          //CReactionInterface* ri = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
          //ri->initFromReaction((*it)->getKey());

          data->setName((*it)->getObjectName());

          const CReaction * pRea = dynamic_cast<const CReaction*>(*it);

          if (pRea->getDeletedObjects().size() > 0)
            {
              setDependentObjects(pRea->getDeletedObjects(),
                                  reactionData,
                                  speciesData,
                                  globalQuantityData,
                                  eventData);
              data->setSpeciesDependencyObjects(&speciesData);
            }

          //  data->setRi(ri);
          reactionData.append(data); //FROM_UTF8((*it)->getObjectName()));
        }
    }

  if (Metabolites.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Metabolites.begin();
      std::set< const CCopasiObject * >::const_iterator end = Metabolites.end();

      for (; it != end; ++it)
        {
          //store the Metabolites data
          const CMetab * pMetab = dynamic_cast<const CMetab*>(*it);
          UndoSpeciesData *data = new UndoSpeciesData(pMetab);
          speciesData.append(data);
        }
    }

  if (Values.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Values.begin();
      std::set< const CCopasiObject * >::const_iterator end = Values.end();

      for (; it != end; ++it)
        {
          //store the Global Quantity data
          UndoGlobalQuantityData *data = new UndoGlobalQuantityData();
          data->setName((*it)->getObjectName());
          const CModelValue * pModelValue = dynamic_cast<const CModelValue*>(*it);
          //data->setModelValue(* pModelValue);
          data->setStatus(pModelValue->getStatus());

          if (pModelValue->getStatus() != CModelEntity::ASSIGNMENT)
            {
              data->setInitialValue(pModelValue->getInitialValue());
            }

          if (pModelValue->getStatus() != CModelEntity::FIXED)
            {
              data->setExpression(pModelValue->getExpression());
            }

          // set initial expression
          if (pModelValue->getStatus() != CModelEntity::ASSIGNMENT)
            {
              data->setInitialExpression(pModelValue->getInitialExpression());
            }

          /*  if(pModelValue->isFixed()){
                      data->setFixed(true);
                      data->setInitialValue(pModelValue->getInitialValue());
                    }else if(!pModelValue->isFixed()){
                      data->setFixed(false);
                      data->setExpression(pModelValue->getExpression());
                    }*/
          globalQuantityData.append(data);
        }
    }

  if (Events.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Events.begin();
      std::set< const CCopasiObject * >::const_iterator end = Events.end();

      for (; it != end; ++it)
        {
          //store the Event data
          UndoEventData *data = new UndoEventData();
          data->setName((*it)->getObjectName());
          const CEvent * pEvent = dynamic_cast<const CEvent*>(*it);
          data->setPriorityExpression(pEvent->getPriorityExpression());
          data->setDelayExpression(pEvent->getDelayExpression());
          data->setTriggerExpression(pEvent->getTriggerExpression());

          CCopasiVector< CEventAssignment >::const_iterator iit = pEvent->getAssignments().begin();
          CCopasiVector< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

          for (; iit != end; ++iit)
            {

              const CModelEntity * pEntity = dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get((*iit)->getTargetKey()));
              data->getEventAssignmentData()->append(
                new UndoEventAssignmentData(pEntity, (*iit)->getExpression()));
            }


          eventData.append(data);
        }
    }

}

QList<UndoReactionData*> *CCopasiUndoCommand::getReactionData() const
{
  return mpReactionData;
}

QList<UndoSpeciesData*> *CCopasiUndoCommand::getSpecieData() const
{
  return mpSpeciesData;
}

void CCopasiUndoCommand::setReactionData(QList<UndoReactionData*> *reactionData)
{
  mpReactionData = reactionData;
}

void CCopasiUndoCommand::setSpecieData(QList<UndoSpeciesData*> *specieData)
{
  mpSpeciesData = specieData;
}

QList<UndoGlobalQuantityData*> *CCopasiUndoCommand::getGlobalQuantityData() const
{
  return mpGlobalQuantityData;
}

void CCopasiUndoCommand::setGlobalQuantityData(QList<UndoGlobalQuantityData*> *globalQuantityData)
{
  mpGlobalQuantityData = globalQuantityData;
}

QList<UndoEventData*> *CCopasiUndoCommand::getEventData() const
{
  return mpEventData;
}

void CCopasiUndoCommand::setEventData(QList<UndoEventData*> *eventData)
{
  mpEventData = eventData;
}

bool CCopasiUndoCommand::isUndoState() const
{
  return undoState;
}

void CCopasiUndoCommand::setUndoState(bool undoState)
{
  this->undoState = undoState;
}

const std::string& CCopasiUndoCommand::getEntityType() const
{
  return mEntityType;
}

const std::string& CCopasiUndoCommand::getNewValue() const
{
  return mNewValue;
}

const std::string& CCopasiUndoCommand::getOldValue() const
{
  return mOldValue;
}

const std::string& CCopasiUndoCommand::getProperty() const
{
  return mProperty;
}

void CCopasiUndoCommand::setEntityType(const std::string& entityType)
{
  mEntityType = entityType;
}

void CCopasiUndoCommand::setNewValue(const std::string& newValue)
{
  mNewValue = newValue;
}

void CCopasiUndoCommand::setOldValue(const std::string& oldValue)
{
  mOldValue = oldValue;
}

void CCopasiUndoCommand::setProperty(const std::string& property)
{
  mProperty = property;
}

const std::string& CCopasiUndoCommand::getAction() const
{
  return mAction;
}

void CCopasiUndoCommand::setAction(const std::string& action)
{
  mAction = action;
}

const std::string& CCopasiUndoCommand::getName() const
{
  return mName;
}

void CCopasiUndoCommand::setName(const std::string& name)
{
  mName = name;
}

const std::string& CCopasiUndoCommand::getKey() const
{
  return mKey;
}

void CCopasiUndoCommand::setKey(const std::string &key)
{
  mKey = key;
}

