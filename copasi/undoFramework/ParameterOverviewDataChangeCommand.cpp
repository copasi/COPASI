// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

ParameterOverviewDataChangeCommand::ParameterOverviewDataChangeCommand(
  const QModelIndex &index,
  const std::string& name,
  const QVariant &newValue,
  const QVariant &oldValue,
  CQParameterOverviewDM *pParameterOverviewDM,
  const std::string& parametersetKey
)
  : CCopasiUndoCommand()
  , mNew(newValue)
  , mOld(oldValue)
  , mIndex(index)
  , mpParameterOverviewDM(pParameterOverviewDM)
  , mPathIndex(pathFromIndex(index))
  , mParametersetKey(parametersetKey)
{
  if (mParametersetKey.empty())
    {
      setText(QObject::tr(": Changed parameter overview data"));
      setEntityType("Parameter Overview");
    }
  else
    {
      setText(QObject::tr(": Changed parameter set data"));
      setEntityType("Parameter Set");
    }

  if (index.column() == 3)
    {
      setProperty("Value");
    }
  else
    {
      setProperty("Assignment");
    }

  setAction("Change");
  setName(name);
  setOldValue(TO_UTF8(mOld.toString()));
  setNewValue(TO_UTF8(mNew.toString()));
}

void
ParameterOverviewDataChangeCommand::redo()
{
  mpParameterOverviewDM->parameterOverviewDataChange(mPathIndex, mNew, mParametersetKey);
}

void ParameterOverviewDataChangeCommand::undo()
{
  mpParameterOverviewDM->parameterOverviewDataChange(mPathIndex, mOld, mParametersetKey);
}

bool ParameterOverviewDataChangeCommand::matches(
  const QModelIndex &index,
  const std::string& name,
  const QVariant &newValue,
  const QVariant &oldValue,
  const std::string& parametersetKey) const
{
  if (newValue != mNew || oldValue != mOld
      || name != getName()
      || parametersetKey != mParametersetKey)
    return false;

  Path temp = pathFromIndex(index);

  return temp == mPathIndex;
}

ParameterOverviewDataChangeCommand::~ParameterOverviewDataChangeCommand()
{
}
