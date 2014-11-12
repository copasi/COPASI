// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQCompartmentDM.h"
#include "function/CFunctionDB.h"

#include "UndoCompartmentData.h"
#include "UndoReactionData.h"

#include "RemoveCompartmentRowsCommand.h"

RemoveCompartmentRowsCommand::RemoveCompartmentRowsCommand(QModelIndexList rows, CQCompartmentDM * pCompartmentDM, const QModelIndex&)
{
  mpCompartmentDM = pCompartmentDM;
  mRows = rows;
  mFirstTime = true;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  assert(pModel != NULL);

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      UndoCompartmentData *data = new UndoCompartmentData();

      if (!pCompartmentDM->isDefaultRow(*i) && pModel->getCompartments()[(*i).row()])
        {
          mpSpecieData = new QList <UndoSpecieData*>();
          mpReactionData = new  QList <UndoReactionData*>();
          mpGlobalQuantityData = new  QList <UndoGlobalQuantityData*>();
          mpEventData = new  QList <UndoEventData*>();
          data->setName(pModel->getCompartments()[(*i).row()]->getObjectName());
          data->setStatus(pModel->getCompartments()[(*i).row()]->getStatus());
          data->setInitialValue(pModel->getCompartments()[(*i).row()]->getInitialValue());
          setDependentObjects(pModel->getCompartments()[(*i).row()]->getDeletedObjects());
          data->setReactionDependencyObjects(getReactionData());
          data->setSpecieDependencyObjects(getSpecieData());
          data->setGlobalQuantityDependencyObjects(getGlobalQuantityData());
          data->setEventDependencyObjects(getEventData());

          mpCompartmentData.append(data);
        }
    }

  this->setText(removeCompartmentRowsText());
}

void RemoveCompartmentRowsCommand::redo()
{
  if (mFirstTime)
    {
      mpCompartmentDM->removeCompartmentRows(mRows, QModelIndex());
      mFirstTime = false;
    }
  else
    {
      mpCompartmentDM->deleteCompartmentRows(mpCompartmentData);
    }
}

void RemoveCompartmentRowsCommand::undo()
{
  mpCompartmentDM->insertCompartmentRows(mpCompartmentData);
}

QString RemoveCompartmentRowsCommand::removeCompartmentRowsText() const
{
  return QObject::tr(": Removed Compartments");
}

RemoveCompartmentRowsCommand::~RemoveCompartmentRowsCommand()
{
  // TODO Auto-generated destructor stub
}
