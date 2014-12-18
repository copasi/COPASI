// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertSpecieRowsCommand.cpp
 *
 *  Created on: 27 Aug 2014
 *      Author: dada
 */

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CMetab.h"
//#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQSpecieDM.h"

#include "InsertSpecieRowsCommand.h"
#include "UndoSpecieData.h"

InsertSpecieRowsCommand::InsertSpecieRowsCommand(int position, int rows, CQSpecieDM *pSpecieDM, const QModelIndex&): CCopasiUndoCommand()
{
  mpSpecieDM = pSpecieDM;
  mpSpecieData = new UndoSpecieData();
  this->setText(insertRowsText());
  mRows = rows;
  mPosition = position;
  firstTime = true;
  mType = SPECIEINSERT;
  setEntityType("Species");
}

void InsertSpecieRowsCommand::redo()
{
  if (firstTime)
    {
      mpSpecieDM->insertNewSpecieRow(mPosition, mRows, QModelIndex());
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
      assert(pDataModel != NULL);
      CModel * pModel = pDataModel->getModel();
      assert(pModel != NULL);

      CMetab *pSpecie = pModel->getMetabolites()[mPosition];
      mpSpecieData->setName(pSpecie->getObjectName());
      mpSpecieData->setIConc(pSpecie->getInitialConcentration());
      mpSpecieData->setCompartment(pSpecie->getCompartment()->getObjectName());
      firstTime = false;
    }
  else
    {
      mpSpecieDM->addSpecieRow(mpSpecieData);
    }

  setUndoState(true);
  setAction("Add to list");
  setName(mpSpecieData->getName());
}

void InsertSpecieRowsCommand::undo()
{
  mpSpecieDM->deleteSpecieRow(mpSpecieData);
  setUndoState(false);
  setAction("Reomve from list");
}

QString InsertSpecieRowsCommand::insertRowsText() const
{
  return QObject::tr(": Inserted New Species");
}

UndoData *InsertSpecieRowsCommand::getUndoData() const
{
  return mpSpecieData;
}

InsertSpecieRowsCommand::~InsertSpecieRowsCommand()
{
  // TODO Auto-generated destructor stub
}
