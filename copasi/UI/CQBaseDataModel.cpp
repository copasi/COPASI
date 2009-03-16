// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQBaseDataModel.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/03/16 14:52:35 $
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
  if (rowCount() == 0)
    {return false;}

  bool rowEmpty = true;

  for (int j = 0; j < columnCount(); j++)
    {
      QModelIndex& ind = index((rowCount() - 1), j);
      QString value = ind.data().toString();

      if (!value.isEmpty() && (value != "-- select --") && (value != "No Name") && (value != "0") && (value != "undefined"))
        rowEmpty = false;
    }

  if (rowEmpty)
    return removeRow(rowCount() - 1);

  return false;
}
