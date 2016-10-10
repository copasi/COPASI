// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QUndoStack>

#include "copasi.h"
#include "CQBaseDataModel.h"

CQBaseDataModel::CQBaseDataModel(QObject *parent, CCopasiDataModel * pDataModel)
  : QAbstractTableModel(parent)
  , mpUndoStack(NULL)
  , mpDataModel(pDataModel)
{}

Qt::ItemFlags CQBaseDataModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_ROW_NUMBER)
    return QAbstractItemModel::flags(index);
  else
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CQBaseDataModel::insertRow(int position, const QModelIndex & source)
{
  return insertRows(position, 1, source);
}

bool CQBaseDataModel::removeRow(int position)
{
  if (0 <= position && position < rowCount() && !isDefaultRow(index(position, 0)))
    return removeRows(position, 1);
  else
    return false;
}

bool CQBaseDataModel::clear()
{
  resetCache();
  return removeRows(0, rowCount() - 1);
}

// virtual
void CQBaseDataModel::resetCache()
{}

bool CQBaseDataModel::isDefaultRow(const QModelIndex& i) const
{
  //Index has to be from this model and should be valid.
  if ((i.model() != this) ||
      !i.isValid())
    {
      return false;
    }

  return (i.row() == rowCount() - 1);
}

QString CQBaseDataModel::createNewName(const QString name, const int nameCol)
{
  QString nname = name;
  unsigned C_INT32 j, jmax = rowCount() - 1;

  for (unsigned C_INT32 i = 1;; ++i)
    {
      for (j = 0; j < jmax; ++j)
        if (index(j, nameCol).data() == nname) break;

      if (j == jmax) break;

      nname = name + "_" + QString::number(i);
    }

  return nname;
}

void CQBaseDataModel::setDataModel(CCopasiDataModel * pDataModel)
{
  mpDataModel = pDataModel;
  resetCache();
}

void CQBaseDataModel::setUndoStack(QUndoStack* undoStack)
{
  mpUndoStack = undoStack;
}

QUndoStack* CQBaseDataModel::getUndoStack()
{
  return mpUndoStack;
}

CCopasiDataModel * CQBaseDataModel::getDataModel() const
{
  return mpDataModel;
}
