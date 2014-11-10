// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
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
