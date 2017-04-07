// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CCopasiUndoCommand.cpp
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */

#include <QDateTime>

#include "copasi.h"

#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "function/CFunctionDB.h"

#include "UndoReactionData.h"
#include "UndoGlobalQuantityData.h"
#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"
#include "UndoSpeciesData.h"
#include "UndoData.h"

#include "CCopasiUndoCommand.h"

CCopasiUndoCommand::CCopasiUndoCommand(const std::string& entityType /*= ""*/,
                                       CCopasiUndoCommand::Type type /*= INVALID_TYPE*/,
                                       const std::string& action /*= ""*/,
                                       const std::string& property /*= ""*/,
                                       const std::string& newValue /*= ""*/,
                                       const std::string& oldValue /*= ""*/,
                                       const std::string& name /*= ""*/
                                      )
  : QUndoCommand()
  , mType(type)
  , undoState(false)
  , mNewValue(newValue)
  , mOldValue(oldValue)
  , mProperty(property)
  , mEntityType(entityType)
  , mAction(action)
  , mName(name)
  , mTime(QDateTime::currentDateTime().toString().toStdString())
{
}

CCopasiUndoCommand::~CCopasiUndoCommand()
{
}

Path CCopasiUndoCommand::pathFromIndex(const QModelIndex &index)
{
  QModelIndex iter = index;
  Path path;

  while (iter.isValid())
    {
      path.prepend(PathItem(iter.row(), iter.column()));
      iter = iter.parent();
    }

  return path;
}

QModelIndex
CCopasiUndoCommand::pathToIndex(
  const Path &path, const QAbstractItemModel *model)
{
  QModelIndex iter;

  for (int i = 0; i < path.size(); i++)
    {
      iter = model->index(path[i].first, path[i].second, iter);
    }

  return iter;
}

const CCopasiUndoCommand::Type&
CCopasiUndoCommand::getType() const
{
  return mType;
}

void CCopasiUndoCommand::setType(const CCopasiUndoCommand::Type & type)
{
  if (mType != type)
    {
      mType = type;
    }
}

bool CCopasiUndoCommand::isUndoState() const
{
  return undoState;
}

void CCopasiUndoCommand::setUndoState(bool undoState)
{
  this->undoState = undoState;
}

const std::string& CCopasiUndoCommand::getEntityType() const
{
  return mEntityType;
}

const std::string& CCopasiUndoCommand::getNewValue() const
{
  return mNewValue;
}

const std::string& CCopasiUndoCommand::getOldValue() const
{
  return mOldValue;
}

const std::string& CCopasiUndoCommand::getProperty() const
{
  return mProperty;
}

void CCopasiUndoCommand::setEntityType(const std::string& entityType)
{
  mEntityType = entityType;
}

void CCopasiUndoCommand::setNewValue(const std::string& newValue)
{
  mNewValue = newValue;
}

void CCopasiUndoCommand::setOldValue(const std::string& oldValue)
{
  mOldValue = oldValue;
}

void CCopasiUndoCommand::setProperty(const std::string& property)
{
  mProperty = property;
}

const std::string& CCopasiUndoCommand::getAction() const
{
  return mAction;
}

void CCopasiUndoCommand::setAction(const std::string& action)
{
  mAction = action;
}

const std::string& CCopasiUndoCommand::getName() const
{
  return mName;
}

void CCopasiUndoCommand::setName(const std::string& name)
{
  mName = name;
}

const std::string& CCopasiUndoCommand::getKey() const
{
  return mKey;
}

void CCopasiUndoCommand::setKey(const std::string &key)
{
  mKey = key;
}

const std::string& CCopasiUndoCommand::getTime() const
{
  return mTime;
}
