// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"
#include "CQBaseTreeDataModel.h"
#include <copasi/utilities/utility.h>
#include <copasi/UI/qtUtilities.h>

CQBaseTreeDataModel::CQBaseTreeDataModel(QObject *parent, CDataModel * pDataModel)
  : QAbstractItemModel(parent)
  , mpDataModel(pDataModel)
  , mFramework(0)
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

Qt::ItemFlags CQBaseTreeDataModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_ROW_NUMBER)
    return QAbstractItemModel::flags(index);
  else
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CQBaseTreeDataModel::insertRow(int position, const QModelIndex & source)
{
  return insertRows(position, 1, source);
}

bool CQBaseTreeDataModel::removeRow(int position)
{
  if (0 <= position && position < rowCount() && !isDefaultRow(index(position, 0)))
    return removeRows(position, 1);
  else
    return false;
}

bool CQBaseTreeDataModel::clear()
{
  resetCache();
  return removeRows(0, rowCount() - 1);
}

// virtual
void CQBaseTreeDataModel::resetCache()
{
  assert(mpDataModel != NULL);

  beginResetModel();
  resetCacheProtected();
  endResetModel();
}

bool CQBaseTreeDataModel::isDefaultRow(const QModelIndex& i) const
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
void CQBaseTreeDataModel::setFramework(int framework)
{
  mFramework = framework;
}

QString CQBaseTreeDataModel::createNewName(const QString name, const int nameCol)
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

void CQBaseTreeDataModel::setDataModel(CDataModel * pDataModel)
{
  beginResetModel();

  mpDataModel = pDataModel;
  resetCache();

  endResetModel();
}

CDataModel * CQBaseTreeDataModel::getDataModel() const
{
  return mpDataModel;
}

void CQBaseTreeDataModel::beginResetModel()
{
  QAbstractItemModel::beginResetModel();
}

void CQBaseTreeDataModel::endResetModel()
{
  QAbstractItemModel::endResetModel();
}
