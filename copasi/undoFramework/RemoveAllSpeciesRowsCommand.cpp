// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllSpecieRowsCommand.cpp
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "UI/CQSpecieDM.h"
#include "function/CFunctionDB.h"

#include "model/CReaction.h"
#include "model/CReactionInterface.h"

#include "RemoveAllSpeciesRowsCommand.h"
#include "UndoSpeciesData.h"
#include "UndoReactionData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoEventData.h"

RemoveAllSpecieRowsCommand::RemoveAllSpecieRowsCommand(
  CQSpecieDM * pSpecieDM, const QModelIndex&)
  : CCopasiUndoCommand("Species", SPECIES_REMOVE_ALL)
  , mpSpecieDM(pSpecieDM)
  , mpSpeciesData()
{
  GET_MODEL_OR_RETURN(pModel);

  for (int i = 0; i != pSpecieDM->rowCount() - 1; ++i)
    {
      UndoSpeciesData *data = new UndoSpeciesData();

      if (pModel->getMetabolites()[i])
        {
          //  mpReactionData = new  QList <UndoReactionData*>();
          //  mpGlobalQuantityData = new  QList <UndoGlobalQuantityData*>();
          //  mpEventData = new  QList <UndoEventData*>();
          data->setName(pModel->getMetabolites()[i]->getObjectName());
          data->setIConc(pModel->getMetabolites()[i]->getInitialConcentration());
          data->setCompartment(pModel->getMetabolites()[i]->getCompartment()->getObjectName());
          data->setStatus(pModel->getMetabolites()[i]->getStatus());

          if (pModel->getMetabolites()[i]->getStatus() != CModelEntity::ASSIGNMENT)
            {
              data->setIConc(pModel->getMetabolites()[i]->getInitialConcentration());
            }

          if (pModel->getMetabolites()[i]->getStatus() ==  CModelEntity::ASSIGNMENT || pModel->getMetabolites()[i]->getStatus() == CModelEntity::ODE)
            {
              data->setExpression(pModel->getMetabolites()[i]->getExpression());
            }

          // set initial expression
          if (pModel->getMetabolites()[i]->getStatus() != CModelEntity::ASSIGNMENT)
            {
              data->setInitialExpression(pModel->getMetabolites()[i]->getInitialExpression());
            }

          setDependentObjects(pModel->getMetabolites()[i]->getDeletedObjects());
          data->setReactionDependencyObjects(getReactionData());
          data->setGlobalQuantityDependencyObjects(getGlobalQuantityData());
          data->setEventDependencyObjects(getEventData());
          mpSpeciesData.append(data);
        }
    }

  setText(removeAllSpecieRowsText());
}

void RemoveAllSpecieRowsCommand::redo()
{
  mpSpecieDM->removeAllSpecieRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllSpecieRowsCommand::undo()
{
  mpSpecieDM->insertSpecieRows(mpSpeciesData);
  setUndoState(false);
  setAction("Undelete all");
}

QString RemoveAllSpecieRowsCommand::removeAllSpecieRowsText() const
{
  return QObject::tr(": Removed All Species");
}

RemoveAllSpecieRowsCommand::~RemoveAllSpecieRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoSpeciesData * data, mpSpeciesData)
  {
    pdelete(data);
  }
  mpSpeciesData.clear();
}
