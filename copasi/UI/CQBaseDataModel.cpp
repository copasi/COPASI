// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifdef COPASI_UNDO
#include <QUndoStack>
#endif

#include "copasi.h"
#include "CQBaseDataModel.h"

CQBaseDataModel::CQBaseDataModel(QObject *parent)
  : QAbstractTableModel(parent)
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

bool CQBaseDataModel::insertRow()
{
  return insertRows(rowCount() - 1, 1);
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
  return removeRows(0, rowCount() - 1);
}

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
  unsigned C_INT32 j, jmax = rowCount();

  for (unsigned C_INT32 i = 1;; ++i)
    {
      nname = name + "_" + QString::number(i);

      for (j = 0; j < jmax; ++j)
        if (index(j, nameCol).data() == nname) break;

      if (j == jmax) break;
    }

  return nname;
}

#ifdef COPASI_UNDO
void CQBaseDataModel::setUndoStack(QUndoStack* undoStack)
{
  mpUndoStack = undoStack;
}
QUndoStack* CQBaseDataModel::getUndoStack()
{
  return mpUndoStack;
}
#endif
