// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QString>

#include "CQMessageBox.h"
#include "CQParameterSetsDM.h"
#include "qtUtilities.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CModelParameterSet.h"

CQParameterSetsDM::CQParameterSetsDM(QObject *parent) :
  CQBaseDataModel(parent, NULL),
  mpListOfParameterSets(NULL)
{}

CQParameterSetsDM::~CQParameterSetsDM()
{}

size_t CQParameterSetsDM::size() const
{
  if (mpListOfParameterSets != NULL)
    return mpListOfParameterSets->size();

  return 0;
}

int CQParameterSetsDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched;
}

void CQParameterSetsDM::resetCacheProtected()
{
  if (mpDataModel == NULL || mpDataModel->getModel() == NULL)
    {
      mpListOfParameterSets = NULL;
      return;
    }

  mpListOfParameterSets = &mpDataModel->getModel()->getModelParameterSets();
}

int CQParameterSetsDM::columnCount(const QModelIndex & /* parent */) const
{
  return TOTAL_COLS_PARAMETERSET;
}

Qt::ItemFlags CQParameterSetsDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return QAbstractItemModel::flags(index);

  switch (index.column())
    {
      case COL_ROW_NUMBER:
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
        break;

      case COL_NAME:
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
        break;
    }

  return QAbstractItemModel::flags(index);
}

QVariant CQParameterSetsDM::data(const QModelIndex &index, int role) const
{
  if (mpListOfParameterSets == NULL) return QVariant();

  if (!index.isValid()) return QVariant();

  if (index.row() >= rowCount()) return QVariant();

  if (mpListOfParameterSets->size() <= index.row())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      switch (index.column())
        {
          case COL_ROW_NUMBER:
            return QVariant(index.row() + 1);
            break;

          case COL_NAME:
            return QVariant(FROM_UTF8(mpListOfParameterSets->operator[](index.row()).getObjectName()));
            break;
        }
    }

  return QVariant();
}

QVariant CQParameterSetsDM::headerData(int section, Qt::Orientation orientation,
                                       int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    {
      switch (section)
        {
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));
            break;

          case COL_NAME:
            return QVariant(QString("Name"));
            break;

          default:
            return QVariant();
            break;
        }
    }

  return QString("%1").arg(section + 1);
}

bool CQParameterSetsDM::setData(const QModelIndex &index, const QVariant & /* value */, int role)
{
  if (mpListOfParameterSets == NULL) return false;

  if (!index.isValid()) return false;

  if (index.row() >= rowCount()) return false;

  if (index.isValid() && role == Qt::EditRole)
    {
      switch (index.column())
        {
          case COL_ROW_NUMBER:
            return false;
            break;

          case COL_NAME:
            return false;
            break;

          default:
            return false;
            break;
        }
    }

  return true;
}

// virtual
bool CQParameterSetsDM::isDefaultRow(const QModelIndex & /* index */) const
{
  return false;
}

bool CQParameterSetsDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  if (mpListOfParameterSets == NULL) return false;

  if (mpDataModel == NULL) return false;

  CModel *pModel = mpDataModel->getModel();

  if (pModel == NULL) return false;

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString Name = QString("Parameter Set %1").arg(LocalTimeStamp().c_str());

      while (pModel->getModelParameterSets().getIndex(TO_UTF8(Name)) != C_INVALID_INDEX)
        Name = QString("Parameter Set %1").arg(LocalTimeStamp().c_str());

      CModelParameterSet * pNew = new CModelParameterSet(pModel->getActiveModelParameterSet(), NULL, false);
      pNew->setObjectName(TO_UTF8(Name));
      mpListOfParameterSets->add(pNew, true);
      ++mFetched;

      CUndoData UndoData(CUndoData::Type::INSERT, pNew->toData());
      ListViews::addUndoMetaData(this, UndoData);
      emit signalNotifyChanges(mpDataModel->recordData(UndoData));
    }

  endInsertRows();
  return true;
}

bool CQParameterSetsDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0) return true;

  if (mpListOfParameterSets == NULL) return false;

  std::vector< const CModelParameterSet * > ToBeDeleted;
  CDataVectorN< CModelParameterSet >::const_iterator it = mpListOfParameterSets->begin() + position;
  CDataVectorN< CModelParameterSet >::const_iterator end = mpListOfParameterSets->begin()
      + position + std::min(rows, (int)mpListOfParameterSets->size());

  for (; it != end; ++it)
    {
      ToBeDeleted.push_back(&*it);
    }

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< const CModelParameterSet * >::iterator itDeleted = ToBeDeleted.begin();
  std::vector< const CModelParameterSet * >::iterator endDeleted = ToBeDeleted.end();

  for (itDeleted = ToBeDeleted.begin(); itDeleted != endDeleted; ++itDeleted)
    {
      CUndoData UndoData(CUndoData::Type::REMOVE, (*itDeleted)->toData());
      ListViews::addUndoMetaData(this, UndoData);

      if (mFetched > 0)
        --mFetched;

      emit signalNotifyChanges(mpDataModel->applyData(UndoData));
    }

  endRemoveRows();
  return true;
}

bool CQParameterSetsDM::removeRows(QModelIndexList rows, const QModelIndex & /* index */)
{
  if (rows.isEmpty()) return false;

  if (mpListOfParameterSets == NULL) return false;

  //  Build the list of pointers to items to be deleted
  //  before actually deleting any item.
  QList< CModelParameterSet * > ModelParameterSets;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (i->isValid())
        ModelParameterSets.append(&mpListOfParameterSets->operator[](i->row()));
    }

  QList< CModelParameterSet * >::const_iterator j;

  for (j = ModelParameterSets.begin(); j != ModelParameterSets.end(); ++j)
    {
      CModelParameterSet *pModelParameterSet = *j;
      size_t delRow = mpListOfParameterSets->CDataVector< CModelParameterSet >::getIndex(pModelParameterSet);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(ListViews::ancestor(this), "layout",
                                        FROM_UTF8(pModelParameterSet->getObjectName()),
                                        pModelParameterSet);

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}

void CQParameterSetsDM::setListOfModelParameterSets(CDataVectorN< CModelParameterSet > *pListOfModelParameterSets)

{
  beginResetModel();
  mpListOfParameterSets = pListOfModelParameterSets;
  mFetched = std::min(mFetchLimit, size());
  endResetModel();
  //reset();
}
