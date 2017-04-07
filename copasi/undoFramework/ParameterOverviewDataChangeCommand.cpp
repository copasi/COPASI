// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi.h"
#include "UI/qtUtilities.h"

#include "model/CModelParameter.h"
#include "model/CModelParameterGroup.h"
#include "CQParameterOverviewDM.h"

#include "ParameterOverviewDataChangeCommand.h"

ParameterOverviewDataChangeCommand::ParameterOverviewDataChangeCommand(
  const std::string& cn,
  const std::string& name,
  const QVariant &newValue,
  const QVariant &oldValue,
  CQParameterOverviewDM *pParameterOverviewDM,
  const std::string& parametersetKey,
  int column)
  : CCopasiUndoCommand()
  , mNew(newValue)
  , mOld(oldValue)
  , mCN(cn)
  , mpParameterOverviewDM(pParameterOverviewDM)
  , mParametersetKey(parametersetKey)
  , mColumn(column)
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

  if (column == 3)
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
  mpParameterOverviewDM->parameterOverviewDataChange(mCN, mNew, mParametersetKey, mColumn);
}

void ParameterOverviewDataChangeCommand::undo()
{
  mpParameterOverviewDM->parameterOverviewDataChange(mCN, mOld, mParametersetKey, mColumn);
}

bool ParameterOverviewDataChangeCommand::matches(
  const std::string &cn,
  const std::string& name,
  const QVariant &newValue,
  const QVariant &oldValue,
  const std::string& parametersetKey) const
{
  if (newValue != mNew || oldValue != mOld
      || name != getName()
      || parametersetKey != mParametersetKey)
    return false;

  return cn == mCN;
}

ParameterOverviewDataChangeCommand::~ParameterOverviewDataChangeCommand()
{
}
