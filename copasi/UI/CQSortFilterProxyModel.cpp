// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSortFilterProxyModel.h"

#include "CQBaseDataModel.h"
CQSortFilterProxyModel::CQSortFilterProxyModel(QObject *parent)
  : QSortFilterProxyModel(parent)
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

      std::string valLeft = m->data(left, Qt::DisplayRole).toString().toStdString();

      if (valLeft == "nan") return false;

      std::string valRight = m->data(right, Qt::DisplayRole).toString().toStdString();

      if (valRight == "nan") return true;
    }

  return QSortFilterProxyModel::lessThan(left, right);
}
