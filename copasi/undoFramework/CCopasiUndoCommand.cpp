// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "UndoSpecieData.h"
#include "UndoData.h"

#include "CCopasiUndoCommand.h"

CCopasiUndoCommand::CCopasiUndoCommand(): QUndoCommand()
{
  //initialise the UNDO entity data
  mpSpecieData = new QList <UndoSpecieData*>();
  mpReactionData = new  QList <UndoReactionData*>();
}

CCopasiUndoCommand::~CCopasiUndoCommand()
{
  // TODO Auto-generated destructor stub
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

QModelIndex CCopasiUndoCommand::pathToIndex(const Path &path, const QAbstractItemModel *model)
{
  QModelIndex iter;

  for (int i = 0; i < path.size(); i++)
    {
      iter = model->index(path[i].first, path[i].second, iter);
    }

  return iter;
}

void CCopasiUndoCommand::setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects)
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
  std::set< const CCopasiObject * > Tasks;

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

  const CModel * pModel = NULL;

  if (pDataModel != NULL)
    {
      pModel = pDataModel->getModel();
    }

  if (pModel != NULL)
    {
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
              CReactionInterface* ri = new CReactionInterface((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
              ri->initFromReaction((*it)->getKey());
              data->setName((*it)->getObjectName());
              data->setRi(ri);
              mpReactionData->append(data); //FROM_UTF8((*it)->getObjectName()));
            }
        }

      if (Metabolites.size() > 0)
        {
          std::set< const CCopasiObject * >::const_iterator it = Metabolites.begin();
          std::set< const CCopasiObject * >::const_iterator end = Metabolites.end();

          for (; it != end; ++it)
            {
              //store the Metabolites data
              UndoSpecieData *data = new UndoSpecieData();
              data->setName((*it)->getObjectName());
              const CMetab * pMetab = dynamic_cast<const CMetab*>(*it);
              data->setIConc(pMetab->getInitialConcentration());
              data->setCompartment(pMetab->getCompartment()->getObjectName());
              data->setStatus(pMetab->getStatus());

              //store the reaction data
              //  QList<UndoReactionData*> *dependencyObjects = new QList <UndoReactionData*>();
              //  setDependentObjects(pMetab->getDeletedObjects(), dependencyObjects);
              //  data->setDependencyObjects(dependencyObjects);
              mpSpecieData->append(data);
            }
        }
    }
}

QList<UndoReactionData*> *CCopasiUndoCommand::getReactionData() const
{
  return mpReactionData;
}

QList<UndoSpecieData*> *CCopasiUndoCommand::getSpecieData() const
{
  return mpSpecieData;
}

void CCopasiUndoCommand::setReactionData(QList<UndoReactionData*> *reactionData)
{
  mpReactionData = reactionData;
}

void CCopasiUndoCommand::setSpecieData(QList<UndoSpecieData*> *specieData)
{
  mpSpecieData = specieData;
}
