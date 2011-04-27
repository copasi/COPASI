// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQGlobalQuantityDM.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/27 17:05:34 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QString>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModelValue.h"
#include "function/CExpression.h"

#include "CQMessageBox.h"
#include "CQGlobalQuantityDM.h"
#include "qtUtilities.h"

CQGlobalQuantityDM::CQGlobalQuantityDM(QObject *parent)
    : CQBaseDataModel(parent)

{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
}

const QStringList& CQGlobalQuantityDM::getTypes()
{
  return mTypes;
}

const std::vector< unsigned C_INT32 >& CQGlobalQuantityDM::getItemToType()
{
  return mItemToType;
}

int CQGlobalQuantityDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (int)(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getModelValues().size() + 1;
}
int CQGlobalQuantityDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_GQ;
}

Qt::ItemFlags CQGlobalQuantityDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_GQ || index.column() == COL_TYPE_GQ)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else if (index.column() == COL_INITIAL_GQ)
    {
      if (this->index(index.row(), COL_TYPE_GQ).data() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT])))
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEnabled;
      else
        return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQGlobalQuantityDM::data(const QModelIndex &index, int role) const
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
              case COL_NAME_GQ:
                return QVariant(QString("New Quantity"));
              case COL_TYPE_GQ:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[0]])));
              case COL_INITIAL_GQ:
                return QVariant(QString("0.0"));
              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CModelValue *pGQ = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getModelValues()[index.row()];
          const CExpression * pExpression = NULL;

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_GQ:
                return QVariant(QString(FROM_UTF8(pGQ->getObjectName())));

              case COL_TYPE_GQ:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[pGQ->getStatus()])));

              case COL_INITIAL_GQ:
              {
                if (role == Qt::EditRole)
                  return QVariant(QString::number(pGQ->getInitialValue(), 'g', 10));
                else
                  return QVariant(pGQ->getInitialValue());
              }
              case COL_TRANSIENT_GQ:
                return QVariant(pGQ->getValue());

              case COL_RATE_GQ:
                return QVariant(pGQ->getRate());

              case COL_IEXPRESSION_GQ:
              {
                if (pGQ->getInitialExpression() != "")
                  {
                    pExpression = pGQ->getInitialExpressionPtr();

                    if (pExpression != NULL)
                      return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                    else
                      return QVariant();
                  }
              }

              case COL_EXPRESSION_GQ:
              {
                pExpression = pGQ->getExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }
            }
        }
    }

  return QVariant();
}

QVariant CQGlobalQuantityDM::headerData(int section, Qt::Orientation orientation,
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
          case COL_NAME_GQ:
            return QVariant(QString("Name"));
          case COL_TYPE_GQ:
            return QVariant(QString("     Type     "));
          case COL_INITIAL_GQ:
            return QVariant("Initial Value");
          case COL_TRANSIENT_GQ:
            return QVariant("Transient Value");
          case COL_RATE_GQ:
            return QVariant("Rate");
          case COL_IEXPRESSION_GQ:
            return QVariant("Initial Expression");
          case COL_EXPRESSION_GQ:
            return QVariant("Expression");
          default:
            return QVariant();
        }
    }
  else  //Vertical header
    return QString("%1").arg(section + 1);
}

bool CQGlobalQuantityDM::setData(const QModelIndex &index, const QVariant &value,
                                 int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.column() == COL_TYPE_GQ)
            {
              if (index.data().toString() != QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
                insertRow();
              else
                return false;
            }
          else if (index.data() != value)
            insertRow();
          else
            return false;
        }

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CModelValue *pGQ = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getModelValues()[index.row()];

      if (index.column() == COL_NAME_GQ)
        pGQ->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_TYPE_GQ)
        pGQ->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
      else if (index.column() == COL_INITIAL_GQ)
        pGQ->setInitialValue(value.toDouble());

      if (defaultRow && this->index(index.row(), COL_NAME_GQ).data().toString() == "quantity")
        pGQ->setObjectName(TO_UTF8(createNewName("quantity", COL_NAME_GQ)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::MODELVALUE, ListViews::CHANGE, pGQ->getKey());
    }

  return true;
}

bool CQGlobalQuantityDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CModelValue *pGQ = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createModelValue(TO_UTF8(createNewName("quantity", COL_NAME_GQ)));
      emit notifyGUI(ListViews::MODELVALUE, ListViews::ADD, pGQ->getKey());
    }

  endInsertRows();

  return true;
}

bool CQGlobalQuantityDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CCopasiVector< CModelValue >::const_iterator itRow = pModel->getModelValues().begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = (*itRow)->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      pModel->removeModelValue(*itDeletedKey);
      emit notifyGUI(ListViews::MODELVALUE, ListViews::DELETE, *itDeletedKey);
      emit notifyGUI(ListViews::MODELVALUE, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
    }

  endRemoveRows();

  return true;
}

bool CQGlobalQuantityDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CModelValue *> pGlobalQuantities;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pModel->getModelValues()[(*i).row()])
        pGlobalQuantities.append(pModel->getModelValues()[(*i).row()]);
    }

  QList <CModelValue *>::const_iterator j;

  for (j = pGlobalQuantities.begin(); j != pGlobalQuantities.end(); ++j)
    {
      CModelValue * pGQ = *j;

      size_t delRow =
        pModel->getModelValues().CCopasiVector< CModelValue >::getIndex(pGQ);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "quantity",
                                        FROM_UTF8(pGQ->getObjectName()),
                                        pGQ->getDeletedObjects());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}
