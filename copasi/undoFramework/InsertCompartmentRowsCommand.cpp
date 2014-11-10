// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertCompartmentRowsCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "CQCompartmentDM.h"

#include "UndoCompartmentData.h"

#include "InsertCompartmentRowsCommand.h"

InsertCompartmentRowsCommand::InsertCompartmentRowsCommand(int position, int rows, CQCompartmentDM *pCompartmentDM, const QModelIndex&): CCopasiUndoCommand()
{
  mpCompartmentDM = pCompartmentDM;
  mpCompartmentData = new UndoCompartmentData();
  this->setText(insertRowsText());
  mRows = rows;
  mPosition = position;
  firstTime = true;
}

void InsertCompartmentRowsCommand::redo()
{
  if (firstTime)
    {
      mpCompartmentDM->insertNewCompartmentRow(mPosition, mRows, QModelIndex());
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      CModel * pModel = pDataModel->getModel();
      assert(pModel != NULL);

      CCompartment *pCompartment = pModel->getCompartments()[mPosition];
      mpCompartmentData->setName(pCompartment->getObjectName());
      mpCompartmentData->setStatus(pCompartment->getStatus());
      mpCompartmentData->setInitialValue(pCompartment->getInitialValue());
      firstTime = false;
    }
  else
    {
      mpCompartmentDM->addCompartmentRow(mpCompartmentData);
    }
}

void InsertCompartmentRowsCommand::undo()
{
  mpCompartmentDM->deleteCompartmentRow(mpCompartmentData);
}

QString InsertCompartmentRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted New Compartments");
}

InsertCompartmentRowsCommand::~InsertCompartmentRowsCommand()
{
  // TODO Auto-generated destructor stub
}
