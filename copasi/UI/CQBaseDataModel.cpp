// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQBaseDataModel.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/04/07 23:14:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQBaseDataModel.h"

CQBaseDataModel::CQBaseDataModel(QObject *parent)
    : QAbstractTableModel(parent)

{}

Qt::ItemFlags CQBaseDataModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CQBaseDataModel::insertRow()
{
  return insertRows(rowCount(), 1);
}

bool CQBaseDataModel::removeRow(int position)
{
  return removeRows(position, 1);
}

bool CQBaseDataModel::clear()
{
  return removeRows(0, rowCount());
}

bool CQBaseDataModel::removeLastRowIfEmpty()
{
  if (isLastDefaultRow())
    return removeRow(rowCount() - 1);

  return false;
}

bool CQBaseDataModel::isLastDefaultRow()
{
  if (rowCount() == 0)
    {return false;}

  return isDefaultRow(index((rowCount() - 1), 0));
}

bool CQBaseDataModel::isDefaultRow(const QModelIndex& i) const
{
  if (!i.isValid())
    {return false;}

  bool rowDefault = true;

  for (int j = 0; j < columnCount(); j++)
    {
      QModelIndex ind = index(i.row(), j);
      QString value = ind.data().toString();

      if (!value.isEmpty() && (value != "-- select --"))
        rowDefault = false;
    }

  return rowDefault;
}
