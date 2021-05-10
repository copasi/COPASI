// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/copasi.h"
#include "CQBaseDataModel.h"
#include <copasi/utilities/utility.h>
#include <copasi/UI/qtUtilities.h>

CQBaseDataModel::CQBaseDataModel(QObject *parent, CDataModel * pDataModel)
  : QAbstractTableModel(parent)
  , mpDataModel(pDataModel)
  , mFramework(0)
  , mFetched(0)
  , mFetchLimit(50)
  , mFetchDisabled(false)
{
  if (mpDataModel == NULL)
    {
      mpDataModel = ListViews::dataModel(this);
    }

  ListViews * pListView = ListViews::ancestor(this);

  if (pListView != NULL)
    {
      connect(pListView, SIGNAL(signalResetCache()), this, SLOT(resetCache()));
    }
}

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
  mFetchDisabled = true;

  resetCache();
  bool success = removeRows(0, size());

  mFetchDisabled = false;
  return success;
}

// virtual
void CQBaseDataModel::resetCache()
{
  assert(mpDataModel != NULL);

  beginResetModel();

  resetCacheProtected();
  mFetched = std::min(mFetchLimit, size());

  endResetModel();
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

// virtual
void CQBaseDataModel::setFramework(int framework)
{
  mFramework = framework;
}

QString CQBaseDataModel::createNewName(const QString name, const int nameCol)
{
  QString nname = name;
  unsigned C_INT32 j, jmax = rowCount() - 1;

  for (unsigned C_INT32 i = 1;; ++i)
    {
      for (j = 0; j < jmax; ++j)
        {
          QString curName = index(j, nameCol).data().toString();
          std::string unQuoted = unQuote(TO_UTF8(nname));

          if (curName == nname ||
              unQuote(TO_UTF8(curName)) == unQuoted) break;
        }

      if (j == jmax) break;

      nname = name + "_" + QString::number(i);
    }

  return nname;
}

void CQBaseDataModel::setDataModel(CDataModel * pDataModel)
{
  beginResetModel();

  mpDataModel = pDataModel;
  resetCache();

  endResetModel();
}

CDataModel * CQBaseDataModel::getDataModel() const
{
  return mpDataModel;
}

void CQBaseDataModel::beginResetModel()
{
  QAbstractTableModel::beginResetModel();
}

void CQBaseDataModel::endResetModel()
{
  QAbstractTableModel::endResetModel();
}

bool CQBaseDataModel::canFetchMore(const QModelIndex & parent) const
{
  if (mFetchDisabled || parent.isValid())
    return false;

  return mFetched < size();
}

void CQBaseDataModel::fetchMore(const QModelIndex & parent)
{
  if (mFetchDisabled || parent.isValid())
    return;

  int ToBeFetched = std::min(mFetchLimit, size() - mFetched);

  if (ToBeFetched <= 0)
    return;

  beginInsertRows(QModelIndex(), mFetched, mFetched + ToBeFetched - 1);

  mFetched += ToBeFetched;

  endInsertRows();
}
