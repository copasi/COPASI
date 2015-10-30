// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
  : CCopasiUndoCommand()
  , mNew(value)
  , mOld(index.data(Qt::EditRole))
  , mIndex(index)
  , mpParameterOverviewDM(pParameterOverviewDM)
  , mRole(role)
  , mPathIndex(pathFromIndex(index))
  , mFirstTime(true)
{
  setText(QObject::tr(": Changed parameter overview data"));
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

ParameterOverviewDataChangeCommand::~ParameterOverviewDataChangeCommand()
{
}
