// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ParameterOverviewDataChangeCommand.cpp
 *
 *  Created on: 19 Sep 2014
 *      Author: dada
 */

#include <QDebug>
#include "model/CModelParameter.h"
#include "model/CModelParameterGroup.h"
#include "CQParameterOverviewDM.h"

#include "ParameterOverviewDataChangeCommand.h"

ParameterOverviewDataChangeCommand::ParameterOverviewDataChangeCommand(const QModelIndex &index, const QVariant &value, int role, CQParameterOverviewDM *pParameterOverviewDM)
{
  // stores the data
  mPathIndex = pathFromIndex(index);
  mpParameterOverviewDM = pParameterOverviewDM;
  mOld = index.data(Qt::EditRole);
  mNew = value.toDouble();
  mIndex = index;
  mRole = role;
  mFirstTime = true;

  this->setText(parameterOverviewDataChangeText());
}

void ParameterOverviewDataChangeCommand::redo()
{
  if (mFirstTime)
    {
      mpParameterOverviewDM->parameterOverviewDataChange(mIndex, mNew, mRole);
      mFirstTime = false;
    }
  else
    {
      QModelIndex indx = pathToIndex(mPathIndex, mpParameterOverviewDM);
      mpParameterOverviewDM->parameterOverviewDataChange(indx, mNew, mRole);
    }
}
void ParameterOverviewDataChangeCommand::undo()
{
  QModelIndex indx = pathToIndex(mPathIndex, mpParameterOverviewDM);
  mpParameterOverviewDM->parameterOverviewDataChange(indx, mOld, mRole);
}
QString ParameterOverviewDataChangeCommand::parameterOverviewDataChangeText() const
{
  return QObject::tr(": Changed Parameter Overview Data");
}

ParameterOverviewDataChangeCommand::~ParameterOverviewDataChangeCommand()
{
  // TODO Auto-generated destructor stub
}
