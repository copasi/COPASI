// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSortFilterProxyModel.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/06/22 17:19:07 $
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
        {
          if (sortOrder() == Qt::AscendingOrder)
            return false;
          else
            return true;
        }
      else if (m->isDefaultRow(right))
        {
          if (sortOrder() == Qt::AscendingOrder)
            return true;
          else
            return false;
        }
    }

  return QSortFilterProxyModel::lessThan(left, right);
}
