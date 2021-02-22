// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QString>
#include <QtCore/QList>

#include "CQMessageBox.h"
#include "CQUnitDM.h"

#include "copasi/copasi.h"

#include "qtUtilities.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"

CQUnitDM::CQUnitDM(QObject *parent, CDataModel * pDataModel)
  : CQBaseDataModel(parent, pDataModel)
{
}

size_t CQUnitDM::size() const
{
  return CRootContainer::getUnitList()->size();
}

int CQUnitDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
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
      if (isDefaultRow(index) || index.row() >= (int) CRootContainer::getUnitList()->size())
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
          const CUnitDefinition * pUnitDef = &CRootContainer::getUnitList()->operator[](index.row());

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
                QMap< const CUnitDefinition *, QVariant >::const_iterator it = mUnitCache.find(pUnitDef);

                if (it != mUnitCache.end())
                  return it.value(); // Use cached value, if available

                QVariant prettyExpression(QString(FROM_UTF8(CUnit::prettyPrint(pUnitDef->getExpression()))));
                mUnitCache.insert(pUnitDef, prettyExpression);
                return prettyExpression;
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

      CUnitDefinition *pUnitDef = &CRootContainer::getUnitList()->operator[](index.row());

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

              CQMessageBox::information(ListViews::ancestor(this),
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

              CQMessageBox::information(ListViews::ancestor(this),
                                        "Unable to change Unit Expression",
                                        msg,
                                        QMessageBox::Ok, QMessageBox::Ok);
            }
        }

      if (defaultRow && this->index(index.row(), COL_SYMBOL_UNITS).data().toString() == "unit")
        pUnitDef->setObjectName(TO_UTF8(createNewName("unit", COL_SYMBOL_UNITS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::ObjectType::UNIT, ListViews::CHANGE, pUnitDef->getCN());
    }

  return true;
}

bool CQUnitDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  beginInsertRows(parent, position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CUnitDefinition *pUnitDef  = new CUnitDefinition(TO_UTF8(createNewName("unit", COL_NAME_UNITS)), CRootContainer::getUnitList());

      if (pUnitDef == NULL) continue;

      ++mFetched;

      CRootContainer::getUnitList()->add(pUnitDef, true);
      emit notifyGUI(ListViews::ObjectType::UNIT, ListViews::ADD, pUnitDef->getCN());
    }

  endInsertRows();

  return true;
}

bool CQUnitDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);
  std::vector< std::string > DeletedCNs;
  DeletedCNs.resize(rows);

  std::vector< std::string >::iterator itDeletedKey, itDeletedCN;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CDataVector< CUnitDefinition >::const_iterator itRow =
    CRootContainer::getUnitList()->begin() + position;
  int row = 0;

  for (itDeletedKey = DeletedKeys.begin(), row = 0, itDeletedCN = DeletedCNs.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itDeletedCN, ++itRow, ++row)
    {
      *itDeletedKey = itRow->getKey();
      *itDeletedCN = itRow->getCN();
    }

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  for (itDeletedKey = DeletedKeys.begin(), row = 0, itDeletedCN = DeletedCNs.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itDeletedCN, ++row)
    {
      if (*itDeletedKey != "")
        {
          CDataObject * pUnitDef = CRootContainer::getKeyFactory()->get(*itDeletedKey);

          if (pUnitDef != NULL)
            {
              if (mFetched > 0)
                --mFetched;

              delete pUnitDef;
            }

          emit notifyGUI(ListViews::ObjectType::UNIT, ListViews::DELETE, *itDeletedCN);
        }
    }

  endRemoveRows();

  return true;
}

bool CQUnitDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();

  if (pModel == NULL)
    return false;

  // Build the list of pointers to items to be deleted
  // before actually deleting any item.

  QList <CUnitDefinition *> pUnitDefQList;
  QModelIndexList::const_iterator i;
  CUnitDefinition * pUnitDef;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (i->isValid() && !isDefaultRow(*i) &&
          (pUnitDef = &CRootContainer::getUnitList()->operator[](i->row())) != NULL &&
          pModel->getUnitSymbolUsage(pUnitDef->getSymbol()).empty() &&
          !pUnitDef->isReadOnly())//Don't delete built-ins or used units
        pUnitDefQList.append(&CRootContainer::getUnitList()->operator[](i->row()));
    }

  for (QList <CUnitDefinition *>::const_iterator j = pUnitDefQList.begin(); j != pUnitDefQList.end(); ++j)
    {
      size_t delRow =
        CRootContainer::getUnitList()->CDataVector< CUnitDefinition >::getIndex(*j);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(ListViews::ancestor(this), "unit",
                                        FROM_UTF8((*j)->getObjectName()),
                                        *j);

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}

// virtual
void CQUnitDM::resetCacheProtected()
{
  mUnitCache.clear();// data() will add to the unit cache, as needed
}
