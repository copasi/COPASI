// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * GlobalQuantityDataChangeCommand.cpp
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#include "CQGlobalQuantityDM.h"

#include "GlobalQuantityDataChangeCommand.h"

GlobalQuantityDataChangeCommand::GlobalQuantityDataChangeCommand(QModelIndex index, const QVariant value, int role, CQGlobalQuantityDM *pGlobalQuantityDM)
{
  // stores the data
  mOld = index.data(Qt::DisplayRole);
  mNew = value;
  mpGlobalQuantityDM = pGlobalQuantityDM;
  mIndex = index;
  mRole = role;

  //mPathIndex = pathFromIndex(index);
  this->setText(globalQuantityDataChangeText());
}

void GlobalQuantityDataChangeCommand::redo()
{
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mNew, mRole);
}
void GlobalQuantityDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpGlobalQuantityDM);
  mpGlobalQuantityDM->globalQuantityDataChange(mIndex, mOld, mRole);
}
QString GlobalQuantityDataChangeCommand::globalQuantityDataChangeText() const
{
  return QObject::tr(": Changed Global Quantity Data");
}

GlobalQuantityDataChangeCommand::~GlobalQuantityDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}
