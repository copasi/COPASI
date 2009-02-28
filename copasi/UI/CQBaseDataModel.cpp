// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQBaseDataModel.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/28 18:25:45 $
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
