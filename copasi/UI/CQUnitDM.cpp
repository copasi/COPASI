// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QString>
#include <QtCore/QList>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#include "CQMessageBox.h"
#include "CQUnitDM.h"
#include "qtUtilities.h"

CQUnitDM::CQUnitDM(QObject *parent)
  : CQBaseDataModel(parent)

{
}

int CQUnitDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (int) CCopasiRootContainer::getUnitList()->size() + 1;
}
int CQUnitDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_UNITS;
}

Qt::ItemFlags CQUnitDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (!isDefaultRow(index))
    return QAbstractItemModel::flags(index);

  if (index.column() == COL_SYMBOL_UNITS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQUnitDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (index.column() > 0 && role == Qt::ForegroundRole && !(flags(index) & Qt::ItemIsEditable))
    return QColor(Qt::darkGray);

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(QString(""));

              case COL_NAME_UNITS:
                return QVariant(QString("New Unit"));

              case COL_SYMBOL_UNITS:
                return QVariant(QString(""));

              case COL_DEFINITION_UNITS:
                return QVariant(QString(""));

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          const CUnit * pUnit = (* CCopasiRootContainer::getUnitList())[index.row()];

          if (pUnit == NULL)
            return QVariant();

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_UNITS:
                return QVariant(QString(FROM_UTF8(pUnit->getObjectName())));

              case COL_SYMBOL_UNITS:
                return QVariant(QString(FROM_UTF8(pUnit->getSymbol())));

              case COL_DEFINITION_UNITS:
                return QVariant(QString(FROM_UTF8(pUnit->getDefinition())));
            }
        }
    }

  return QVariant();
}

QVariant CQUnitDM::headerData(int section, Qt::Orientation orientation,
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

          case COL_NAME_UNITS:
            return QVariant(QString("Name"));

          case COL_SYMBOL_UNITS:
            return QVariant(QString("Symbol"));

          case COL_DEFINITION_UNITS:
            return QVariant(QString("Definition"));

          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQUnitDM::setData(const QModelIndex &index, const QVariant &value,
                       int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.data() != value)
            insertRow();
          else
            return false;
        }

      CUnit *pUnit = (* CCopasiRootContainer::getUnitList())[index.row()];

      if (pUnit == NULL)
        return false;

      if (index.column() == COL_NAME_UNITS)
        pUnit->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_SYMBOL_UNITS)
        pUnit->setSymbol(TO_UTF8(value.toString()));
      else if (index.column() == COL_DEFINITION_UNITS)
        {
          if (index.data() != value)
            {
              QString msg;
              msg = "Definition must not be changed for '" + FROM_UTF8(pUnit->getObjectName()) + "'.\n";

              CQMessageBox::information(NULL,
                                        "Unable to change Unit Definition",
                                        msg,
                                        QMessageBox::Ok, QMessageBox::Ok);
            }
        }

      if (defaultRow && this->index(index.row(), COL_SYMBOL_UNITS).data().toString() == "unit")
        pUnit->setObjectName(TO_UTF8(createNewName("unit", COL_SYMBOL_UNITS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::UNIT, ListViews::CHANGE, pUnit->getKey());
    }

  return true;
}

bool CQUnitDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CUnit *pUnit;
      CCopasiRootContainer::getUnitList()->add(pUnit = new CUnit(TO_UTF8(createNewName("unit", COL_SYMBOL_UNITS))), true);
      emit notifyGUI(ListViews::UNIT, ListViews::ADD, pUnit->getKey());
    }

  endInsertRows();

  return true;
}

bool CQUnitDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CCopasiVector< CUnit >::const_iterator itRow =
    CCopasiRootContainer::getUnitList()->begin() + position;
  int row = 0;

  for (itDeletedKey = DeletedKeys.begin(), row = 0; itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow, ++row)
    {
      *itDeletedKey = (*itRow)->getKey();
    }

  beginRemoveRows(QModelIndex(), position, position + row - 1);

  for (itDeletedKey = DeletedKeys.begin(), row = 0; itDeletedKey != endDeletedKey; ++itDeletedKey, ++row)
    {
      if (*itDeletedKey != "")
        {
          CCopasiObject * pUnit = CCopasiRootContainer::getKeyFactory()->get(*itDeletedKey);

          if (pUnit != NULL) delete pUnit;

          emit notifyGUI(ListViews::UNIT, ListViews::DELETE, *itDeletedKey);
        }
    }

  endRemoveRows();

  return true;
}

bool CQUnitDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

  // Build the list of pointers to items to be deleted
  // before actually deleting any item.

  QList <CUnit *> pUnits;
  QModelIndexList::const_iterator i;

  // TODO: Skip (don't delete) our SI units.
  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && (*CCopasiRootContainer::getUnitList())[(*i).row()])
        pUnits.append((*CCopasiRootContainer::getUnitList())[(*i).row()]);
    }

  for (QList <CUnit *>::const_iterator j = pUnits.begin(); j != pUnits.end(); ++j)
    {
      size_t delRow =
        CCopasiRootContainer::getUnitList()->CCopasiVector< CUnit >::getIndex(*j);

      if (delRow != C_INVALID_INDEX)
        {
          CCopasiObject::DataObjectSet DeletedObjects;
          DeletedObjects.insert(*j);

          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "unit",
                                        FROM_UTF8((*j)->getObjectName()),
                                        DeletedObjects);

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}
