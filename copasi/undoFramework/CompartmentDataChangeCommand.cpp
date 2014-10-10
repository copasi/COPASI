// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CompartmentDataChangeCommand.cpp
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#include "CQCompartmentDM.h"

#include "CompartmentDataChangeCommand.h"

CompartmentDataChangeCommand::CompartmentDataChangeCommand(QModelIndex index, const QVariant value, int role, CQCompartmentDM *pCompartmentDM)
{
  // stores the data
  mOld = index.data(Qt::DisplayRole);
  mNew = value;
  mpCompartmentDM = pCompartmentDM;
  mIndex = index;
  mRole = role;

  //mPathIndex = pathFromIndex(index);
  this->setText(compartmentDataChangeText());
}

void CompartmentDataChangeCommand::redo()
{
  mpCompartmentDM->compartmentDataChange(mIndex, mNew, mRole);
}
void CompartmentDataChangeCommand::undo()
{
  //mIndex = pathToIndex(mPathIndex, mpCompartmentDM);
  mpCompartmentDM->compartmentDataChange(mIndex, mOld, mRole);
}
QString CompartmentDataChangeCommand::compartmentDataChangeText() const
{
  return QObject::tr(": Changed Compartment Data");
}

CompartmentDataChangeCommand::~CompartmentDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}
