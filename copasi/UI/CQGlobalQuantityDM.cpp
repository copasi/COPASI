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

#include <QtCore/QString>

#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "model/CModelValue.h"
#include "function/CExpression.h"
#include "model/CModel.h"

#include "CQMessageBox.h"
#include "CQGlobalQuantityDM.h"
#include "qtUtilities.h"

#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "undoFramework/InsertGlobalQuantityRowsCommand.h"
#include "undoFramework/RemoveGlobalQuantityRowsCommand.h"
#include "undoFramework/RemoveAllGlobalQuantityRowsCommand.h"
#include "undoFramework/GlobalQuantityDataChangeCommand.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoSpeciesData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"
#include <copasi/UI/CQCopasiApplication.h>

CQGlobalQuantityDM::CQGlobalQuantityDM(QObject *parent)
  : CQBaseDataModel(parent, NULL),
    mpGlobalQuantities(NULL)

{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));

  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::FIXED));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ASSIGNMENT));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ODE));
}

const QString & CQGlobalQuantityDM::indexToStatus(int index) const
{
  return mTypes[index];
}

int CQGlobalQuantityDM::statusToIndex(const QString& status) const
{
  return mTypes.indexOf(status);
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
  return mpGlobalQuantities->size() + 1;
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
      if (this->index(index.row(), COL_TYPE_GQ).data() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT])))
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
                return QVariant(convertToQString(0.0));

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CModelValue & GQ = mpGlobalQuantities->operator[](index.row());
          const CExpression * pExpression = NULL;

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_GQ:
                return QVariant(QString(FROM_UTF8(GQ.getObjectName())));

              case COL_UNIT_GQ:
              {
                std::string rawExpression = GQ.getUnitExpression();
                QMap< std::string, QVariant >::const_iterator it = mUnitCache.find(rawExpression);

                if (it != mUnitCache.end())
                  return it.value(); // Use cached value, if available

                QVariant prettyExpression(QString(FROM_UTF8(CUnit::prettyPrint(rawExpression))));
                mUnitCache.insert(rawExpression, prettyExpression);
                return prettyExpression;
              }

              case COL_TYPE_GQ:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[GQ.getStatus()])));

              case COL_INITIAL_GQ:

                if (role == Qt::EditRole)
                  return QVariant(convertToQString(GQ.getInitialValue()));
                else
                  return QVariant(GQ.getInitialValue());

              case COL_TRANSIENT_GQ:
                return QVariant(GQ.getValue());

              case COL_RATE_GQ:
                return QVariant(GQ.getRate());

              case COL_IEXPRESSION_GQ:

                if (GQ.getInitialExpression() != "")
                  {
                    pExpression = GQ.getInitialExpressionPtr();

                    if (pExpression != NULL)
                      return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                    else
                      return QVariant();
                  }

                break;

              case COL_EXPRESSION_GQ:
              {
                pExpression = GQ.getExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }

#ifdef WITH_SDE_SUPPORT

              case COL_NEXPRESSION_GQ:
              {
                pExpression = GQ.getNoiseExpressionPtr();

                if (GQ.hasNoise() && pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }

#endif
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

  std::string tmp = CUnit::prettyPrint("1/(" + mpDataModel->getModel()->getTimeUnit() + ")");

  QString ValueUnit = "[Unit]";
  QString RateUnit = (tmp != "?") ? "[Unit" + FROM_UTF8(tmp.substr(1)) + "]" : "[?]";

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

          case COL_UNIT_GQ:
            return QVariant(QString("Unit"));

          case COL_INITIAL_GQ:
            return QVariant("Initial Value\n" + ValueUnit);

          case COL_TRANSIENT_GQ:
            return QVariant("Transient Value\n" + ValueUnit);

          case COL_RATE_GQ:
            return QVariant("Rate\n" + RateUnit);

          case COL_IEXPRESSION_GQ:
            return QVariant("Initial Expression\n" + ValueUnit);

          case COL_EXPRESSION_GQ:
            if (ValueUnit == RateUnit)
              return QVariant("Expression\n" + ValueUnit);
            else
              return QVariant("Expression\n" + ValueUnit + " or " + RateUnit);

#ifdef WITH_SDE_SUPPORT

          case COL_NEXPRESSION_GQ:
            return QVariant("Noise Expression");
#endif

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
  if (index.data() == value)
    return false;

  if (index.column() == COL_TYPE_GQ && index.data().toString() == QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow)
    {
      mpUndoStack->push(new InsertGlobalQuantityRowsCommand(rowCount(), 1, this, index, value));
    }
  else if (role == Qt::EditRole)
    {
      mpUndoStack->push(new GlobalQuantityDataChangeCommand(index, value, this));
    }

  return true;
}

// virtual
void CQGlobalQuantityDM::resetCache()
{
  assert(mpDataModel != NULL);

  mpGlobalQuantities = dynamic_cast< CDataVectorN < CModelValue > * >(&mpDataModel->getModel()->getModelValues());
  assert(mpGlobalQuantities != NULL);

  mUnitCache.clear();// data() will add to the unit cache, as needed
}

bool CQGlobalQuantityDM::insertRows(int position, int rows, const QModelIndex&)
{
  mpUndoStack->push(new InsertGlobalQuantityRowsCommand(position, rows, this));

  return true;
}

bool CQGlobalQuantityDM::removeRows(int position, int rows)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CDataVector< CModelValue >::const_iterator itRow = mpGlobalQuantities->begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = itRow->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      mpDataModel->getModel()->removeModelValue(*itDeletedKey);
      emit notifyGUI(ListViews::MODELVALUE, ListViews::DELETE, *itDeletedKey);
      emit notifyGUI(ListViews::MODELVALUE, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
    }

  endRemoveRows();

  return true;
}

bool CQGlobalQuantityDM::removeRows(QModelIndexList rows, const QModelIndex& index)
{
  removeGlobalQuantityRows(rows, index);

  return true;
}

bool CQGlobalQuantityDM::globalQuantityDataChange(const QModelIndex &index, const QVariant &value)
{
  assert((size_t)index.row() < mpGlobalQuantities->size());

  if (!index.isValid())
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow)
    {
      if (index.column() == COL_TYPE_GQ)
        {
          if (index.data().toString() != QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
            insertRow(rowCount(), index);
          else
            return false;
        }
      else if (index.data() != value)
        insertRow(rowCount(), index);
      else
        return false;
    }

  switchToWidget(CCopasiUndoCommand::GLOBALQUANTITIES);

  CModelValue & GQ = mpGlobalQuantities->operator [](index.row());

  if (index.column() == COL_NAME_GQ)
    GQ.setObjectName(TO_UTF8(value.toString()));
  else if (index.column() == COL_TYPE_GQ)
    GQ.setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
  else if (index.column() == COL_INITIAL_GQ)
    GQ.setInitialValue(value.toDouble());

  if (defaultRow && this->index(index.row(), COL_NAME_GQ).data().toString() == "quantity")
    GQ.setObjectName(TO_UTF8(createNewName("quantity", COL_NAME_GQ)));

  emit dataChanged(index, index);
  emit notifyGUI(ListViews::MODELVALUE, ListViews::CHANGE, GQ.getKey());

  return true;
}

void CQGlobalQuantityDM::insertNewGlobalQuantityRow(int position, int rows, const QModelIndex& index, const QVariant& value)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  int column = index.column();

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(index.isValid() && column == COL_NAME_GQ ? value.toString() : "quantity", COL_NAME_GQ);

      double initial = index.isValid() && column == COL_INITIAL_GQ ? value.toDouble() : 0.0;

      CModelValue *pGQ = mpDataModel->getModel()->createModelValue(TO_UTF8(name), initial);

      if (pGQ == NULL) continue;

      if (index.isValid() && column == COL_TYPE_GQ)
        {
          pGQ->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
        }

      emit notifyGUI(ListViews::MODELVALUE, ListViews::ADD, pGQ->getKey());
    }

  endInsertRows();
}

void CQGlobalQuantityDM::deleteGlobalQuantityRow(UndoGlobalQuantityData *pGlobalQuantityData)
{
  switchToWidget(CCopasiUndoCommand::GLOBALQUANTITIES);

  size_t index = mpGlobalQuantities->getIndex(pGlobalQuantityData->getName());

  if (index == C_INVALID_INDEX)
    return;

  removeRow((int) index);
}

void CQGlobalQuantityDM::addGlobalQuantityRow(UndoGlobalQuantityData *pGlobalQuantityData)
{
  switchToWidget(CCopasiUndoCommand::GLOBALQUANTITIES);

  beginInsertRows(QModelIndex(), 1, 1);
  CDataObject *pGlobalQuantity = pGlobalQuantityData->restoreObjectIn(mpDataModel->getModel());

  if (pGlobalQuantity != NULL)
    emit notifyGUI(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());

  endInsertRows();
}

bool CQGlobalQuantityDM::removeGlobalQuantityRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  switchToWidget(CCopasiUndoCommand::GLOBALQUANTITIES);

  //Build the list of pointers to items to be deleted
  //before actually deleting any item.
  QList <CModelValue *> pGlobalQuantities;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && &mpGlobalQuantities->operator [](i->row()))
        pGlobalQuantities.append(&mpGlobalQuantities->operator [](i->row()));
    }

  QList <CModelValue *>::const_iterator j;
  QModelIndexList lst;

  for (j = pGlobalQuantities.begin(); j != pGlobalQuantities.end(); ++j)
    {
      CModelValue * pGQ = *j;

      size_t delRow =
        mpGlobalQuantities->CDataVector< CModelValue >::getIndex(pGQ);

      if (delRow == C_INVALID_INDEX)
        continue;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, "quantity",
                                    FROM_UTF8(pGQ->getObjectName()),
                                    pGQ);

      if (choice == QMessageBox::Ok)
        {
          lst.append(index((int)delRow, 0));
          //removeRow((int)delRow);
        }
    }

  if (!lst.empty())
    {
      mpUndoStack->push(new RemoveGlobalQuantityRowsCommand(lst, this));
    }

  return true;
}

bool CQGlobalQuantityDM::insertGlobalQuantityRows(QList <UndoGlobalQuantityData *>& pData)
{
  //reinsert all the GlobalQuantities
  QList <UndoGlobalQuantityData *>::const_iterator i;

  for (i = pData.begin(); i != pData.end(); ++i)
    {
      UndoGlobalQuantityData * data = *i;

      if (mpGlobalQuantities->getIndex(data->getName()) != C_INVALID_INDEX)
        continue;

      beginInsertRows(QModelIndex(), 1, 1);
      CDataObject *pGlobalQuantity = data->restoreObjectIn(mpDataModel->getModel());

      if (pGlobalQuantity != NULL)
        emit notifyGUI(ListViews::MODELVALUE, ListViews::ADD, pGlobalQuantity->getKey());

      endInsertRows();
    }

  switchToWidget(CCopasiUndoCommand::GLOBALQUANTITIES);

  return true;
}

void CQGlobalQuantityDM::deleteGlobalQuantityRows(QList <UndoGlobalQuantityData *>& pData)
{
  switchToWidget(CCopasiUndoCommand::GLOBALQUANTITIES);

  QList <UndoGlobalQuantityData *>::const_iterator j;

  for (j = pData.begin(); j != pData.end(); ++j)
    {
      UndoGlobalQuantityData * data = *j;
      size_t index = mpGlobalQuantities->getIndex(data->getName());
      removeRow((int) index);
    }
}

bool CQGlobalQuantityDM::clear()
{
  mpUndoStack->push(new RemoveAllGlobalQuantityRowsCommand(this, QModelIndex()));
  return true;
}

bool CQGlobalQuantityDM::removeAllGlobalQuantityRows()
{
  return removeRows(0, rowCount() - 1);
}
