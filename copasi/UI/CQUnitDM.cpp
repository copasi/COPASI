// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

              case COL_EXPRESSION_UNITS:
                return QVariant(QString(""));

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          const CUnitDefinition * pUnitDef = &CCopasiRootContainer::getUnitList()->operator[](index.row());

          if (pUnitDef == NULL)
            return QVariant();

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_UNITS:
                return QVariant(QString(FROM_UTF8(pUnitDef->getObjectName())));

              case COL_SYMBOL_UNITS:
                return QVariant(QString(FROM_UTF8(pUnitDef->getSymbol())));

              case COL_EXPRESSION_UNITS:
                return QVariant(QString(FROM_UTF8(pUnitDef->getExpression())));
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

          case COL_EXPRESSION_UNITS:
            return QVariant(QString("Expression"));

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
            insertRow(rowCount(), index);
          else
            return false;
        }

      CUnitDefinition *pUnitDef = &CCopasiRootContainer::getUnitList()->operator[](index.row());

      if (pUnitDef == NULL)
        return false;

      if (index.column() == COL_NAME_UNITS)
        pUnitDef->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_SYMBOL_UNITS)
        {
          if (!pUnitDef->setSymbol(TO_UTF8(value.toString())))
            {
              QString msg;
              msg = "Unable set Symbol of Unit '" + FROM_UTF8(pUnitDef->getObjectName()) + "'\n"
                    + "to '" + value.toString() + "' since a Unit with that symbol already exists.\n";

              CQMessageBox::information(NULL,
                                        "Unable set Symbol",
                                        msg,
                                        QMessageBox::Ok, QMessageBox::Ok);
            }
        }
      else if (index.column() == COL_EXPRESSION_UNITS)
        {
          if (index.data() != value)
            {
              QString msg;
              msg = "Expression must not be changed for '" + FROM_UTF8(pUnitDef->getObjectName()) + "'.\n";

              CQMessageBox::information(NULL,
                                        "Unable to change Unit Expression",
                                        msg,
                                        QMessageBox::Ok, QMessageBox::Ok);
            }
        }

      if (defaultRow && this->index(index.row(), COL_SYMBOL_UNITS).data().toString() == "unit")
        pUnitDef->setObjectName(TO_UTF8(createNewName("unit", COL_SYMBOL_UNITS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::UNIT, ListViews::CHANGE, pUnitDef->getKey());
    }

  return true;
}

bool CQUnitDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CUnitDefinition *pUnitDef;
      CCopasiRootContainer::getUnitList()->add(pUnitDef = new CUnitDefinition(TO_UTF8(createNewName("unit", COL_NAME_UNITS)), CCopasiRootContainer::getUnitList()), true);
      emit notifyGUI(ListViews::UNIT, ListViews::ADD, pUnitDef->getKey());
    }

  endInsertRows();

  return true;
}

bool CQUnitDM::removeRows(int position, int rows)
{
  if (rows <= 0)
    return true;

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CCopasiVector< CUnitDefinition >::const_iterator itRow =
    CCopasiRootContainer::getUnitList()->begin() + position;
  int row = 0;

  for (itDeletedKey = DeletedKeys.begin(), row = 0; itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow, ++row)
    {
      *itDeletedKey = itRow->getKey();
    }

  beginRemoveRows(QModelIndex(), position, position + row - 1);

  for (itDeletedKey = DeletedKeys.begin(), row = 0; itDeletedKey != endDeletedKey; ++itDeletedKey, ++row)
    {
      if (*itDeletedKey != "")
        {
          CCopasiObject * pUnitDef = CCopasiRootContainer::getKeyFactory()->get(*itDeletedKey);

          if (pUnitDef != NULL) delete pUnitDef;

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
  CCopasiDataModel* pDataModel = &CCopasiRootContainer::getDatamodelList()->operator[](0);
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

  // Build the list of pointers to items to be deleted
  // before actually deleting any item.

  QList <CUnitDefinition *> pUnitDefQList;
  QModelIndexList::const_iterator i;
  CUnitDefinition * pUnitDef;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) &&
          (pUnitDef = &CCopasiRootContainer::getUnitList()->operator[](i->row())) != NULL &&
          pModel->getUnitSymbolUsage(pUnitDef->getSymbol()).empty() &&
          !pUnitDef->isReadOnly())//Don't delete built-ins or used units
        pUnitDefQList.append(&CCopasiRootContainer::getUnitList()->operator[](i->row()));
    }

  for (QList <CUnitDefinition *>::const_iterator j = pUnitDefQList.begin(); j != pUnitDefQList.end(); ++j)
    {
      size_t delRow =
        CCopasiRootContainer::getUnitList()->CCopasiVector< CUnitDefinition >::getIndex(*j);

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
