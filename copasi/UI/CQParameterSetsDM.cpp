// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QString>

#include "CQMessageBox.h"
#include "CQParameterSetsDM.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "model/CModelParameterSet.h"

CQParameterSetsDM::CQParameterSetsDM(QObject *parent) :
  CQBaseDataModel(parent),
  mpListOfParameterSets(NULL)
{}

CQParameterSetsDM::~CQParameterSetsDM()
{}

int CQParameterSetsDM::rowCount(const QModelIndex & /* parent */) const
{
  if (mpListOfParameterSets == NULL) return 0;

  return (int) mpListOfParameterSets->size();
}

bool CQParameterSetsDM::clear()
{
  return removeRows(0, rowCount());
}

int CQParameterSetsDM::columnCount(const QModelIndex & /* parent */) const
{
  return TOTAL_COLS;
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

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      switch (index.column())
        {
          case COL_ROW_NUMBER:
            return QVariant(index.row() + 1);
            break;

          case COL_NAME:
            return QVariant(FROM_UTF8((*mpListOfParameterSets)[index.row()]->getObjectName()));
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

bool CQParameterSetsDM::insertRows(int position, int rows, const QModelIndex&)
{
  if (mpListOfParameterSets == NULL) return false;

  if (position + rows > (int) mpListOfParameterSets->size())  return false;

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      emit notifyGUI(ListViews::LAYOUT, ListViews::ADD, (*mpListOfParameterSets)[position + row]->getKey());
    }

  endInsertRows();

  return true;
}

bool CQParameterSetsDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0) return true;

  if (mpListOfParameterSets == NULL) return false;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  std::vector< CModelParameterSet * > DeletedModelParameterSets;
  DeletedModelParameterSets.resize(rows);

  std::vector< CModelParameterSet * >::iterator itDeletedModelParameterSet;
  std::vector< CModelParameterSet * >::iterator endDeletedModelParameterSet = DeletedModelParameterSets.end();

  CCopasiVectorN< CModelParameterSet >::const_iterator itRow = mpListOfParameterSets->begin() + position;

  for (itDeletedModelParameterSet = DeletedModelParameterSets.begin(); itDeletedModelParameterSet != endDeletedModelParameterSet; ++itDeletedModelParameterSet, ++itRow)
    {
      *itDeletedModelParameterSet = *itRow;
    }

  for (itDeletedModelParameterSet = DeletedModelParameterSets.begin(); itDeletedModelParameterSet != endDeletedModelParameterSet; ++itDeletedModelParameterSet)
    {
      std::string Key = (*itDeletedModelParameterSet)->getKey();

      pdelete(*itDeletedModelParameterSet);

      emit notifyGUI(ListViews::MODELPARAMETERSET, ListViews::DELETE, Key);
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
      ModelParameterSets.append((*mpListOfParameterSets)[(*i).row()]);
    }

  QList< CModelParameterSet * >::const_iterator j;

  for (j = ModelParameterSets.begin(); j != ModelParameterSets.end(); ++j)
    {
      CModelParameterSet * pModelParameterSet = *j;

      size_t delRow = mpListOfParameterSets->CCopasiVector< CModelParameterSet >::getIndex(pModelParameterSet);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "layout",
                                        FROM_UTF8(pModelParameterSet->getObjectName()),
                                        std::set< const CCopasiObject * >());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}

void CQParameterSetsDM::setListOfModelParameterSets(CCopasiVectorN< CModelParameterSet > * pListOfModelParameterSets)

{
  if (mpListOfParameterSets != pListOfModelParameterSets)
    {
      mpListOfParameterSets = pListOfModelParameterSets;
      reset();
    }
}
