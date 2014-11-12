// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpecieDataChangeCommand.cpp
 *
 *  Created on: 27 Aug 2014
 *      Author: dada
 */

#include "CQSpecieDM.h"

#include "SpecieDataChangeCommand.h"

SpecieDataChangeCommand::SpecieDataChangeCommand(QModelIndex index, const QVariant value, int role, CQSpecieDM *pSpecieDM)
{
  // stores the data
  mOld = index.data(Qt::DisplayRole);
  mNew = value;
  mpSpecieDM = pSpecieDM;
  mIndex = index;
  mRole = role;

  mPathIndex = pathFromIndex(index);
  this->setText(specieDataChangeText());
}

SpecieDataChangeCommand::~SpecieDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}

void SpecieDataChangeCommand::redo()
{
  mIndex = pathToIndex(mPathIndex, mpSpecieDM);
  mpSpecieDM->specieDataChange(mIndex, mNew, mRole);
}
void SpecieDataChangeCommand::undo()
{
  mIndex = pathToIndex(mPathIndex, mpSpecieDM);
  mpSpecieDM->specieDataChange(mIndex, mOld, mRole);
}
QString SpecieDataChangeCommand::specieDataChangeText() const
{
  return QObject::tr(": Changed Species Data");
}
