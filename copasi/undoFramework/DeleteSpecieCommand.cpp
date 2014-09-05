// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteSpecieCommand.cpp
 *
 *  Created on: 2 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQSpecieDM.h"
#include "function/CFunctionDB.h"
#include "UI/CQSpeciesDetail.h"

#include "UndoSpecieData.h"
#include "UndoReactionData.h"

#include "DeleteSpecieCommand.h"

DeleteSpecieCommand::DeleteSpecieCommand(CQSpeciesDetail *pSpecieDetail)
{
  mpSpecieDetail = pSpecieDetail;
  mpSpecieData = new UndoSpecieData();
  std::string sName = mpSpecieDetail->mpMetab->getObjectName();
  mpSpecieData->setName(sName);
  mpSpecieData->setIConc(mpSpecieDetail->mpMetab->getInitialConcentration());
  mpSpecieData->setCompartment(mpSpecieDetail->mpMetab->getCompartment()->getObjectName());
  mpSpecieData->setStatus(mpSpecieDetail->mpMetab->getStatus());

  //store the to be deleted data
  QList<UndoReactionData*> dependencyObjects;
  setDependentObjects(mpSpecieDetail->mpMetab->getDeletedObjects(), &dependencyObjects);
  mpSpecieData->setDependencyObjects(dependencyObjects);

  this->setText(deleteSpecieText(sName));
}

void DeleteSpecieCommand::redo()
{
  mpSpecieDetail->deleteSpecie();
}

void DeleteSpecieCommand::undo()
{
  mpSpecieDetail->addSpecie(mpSpecieData);
}

QString DeleteSpecieCommand::deleteSpecieText(std::string &name) const
{
  std::string myEntityName(": Delete Species " + name);
  char* entityName = (char*)myEntityName.c_str();
  return QObject::tr(entityName);
}

void DeleteSpecieCommand::setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects, QList<UndoReactionData*> *dependencyObjects)
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

  //TODO presently assume only reaction objects can be deleted when species is deleted
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
              dependencyObjects->append(data); //FROM_UTF8((*it)->getObjectName()));
            }
        }
    }
}

DeleteSpecieCommand::~DeleteSpecieCommand()
{
  // TODO Auto-generated destructor stub
}
