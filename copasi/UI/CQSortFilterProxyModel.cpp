// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSortFilterProxyModel.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/04/07 23:14:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSortFilterProxyModel.h"

#include "CQBaseDataModel.h"
CQSortFilterProxyModel::CQSortFilterProxyModel()
    : QSortFilterProxyModel()
{
}

CQSortFilterProxyModel::~CQSortFilterProxyModel()
{
}

bool CQSortFilterProxyModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
  if (dynamic_cast<CQBaseDataModel *>(sourceModel()))
    {
      CQBaseDataModel * m = dynamic_cast<CQBaseDataModel *>(sourceModel());

      if (m->isDefaultRow(left))
        return false;
      else if (m->isDefaultRow(right))
        return true;
    }

  return QSortFilterProxyModel::lessThan(left, right);
}
