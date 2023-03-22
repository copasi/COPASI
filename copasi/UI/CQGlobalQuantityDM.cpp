// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <QtCore/QString>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModelValue.h"
#include "copasi/function/CExpression.h"
#include "copasi/model/CModel.h"

#include "CQMessageBox.h"
#include "CQGlobalQuantityDM.h"
#include "qtUtilities.h"

#include "copasi/model/CReaction.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/UI/CQCopasiApplication.h"

CQGlobalQuantityDM::CQGlobalQuantityDM(QObject *parent)
  : CQBaseDataModel(parent, NULL),
    mpGlobalQuantities(NULL)

{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));
}

const QStringList& CQGlobalQuantityDM::getTypes()
{
  return mTypes;
}

size_t CQGlobalQuantityDM::size() const
{
  if (mpGlobalQuantities != NULL)
    return mpGlobalQuantities->size();

  return 0;
}

int CQGlobalQuantityDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
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
      if (isDefaultRow(index) || index.row() >= (int) mpGlobalQuantities->size())
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(QString(""));

              case COL_NAME_GQ:
                return QVariant(QString("New Quantity"));

              case COL_TYPE_GQ:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED])));

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

              case COL_NEXPRESSION_GQ:
              {
                pExpression = GQ.getNoiseExpressionPtr();

                if (GQ.hasNoise() && pExpression != NULL)
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

          case COL_NEXPRESSION_GQ:
            return QVariant("Noise Expression");

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
  QVariant data = index.data();

  if (data == value)
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow)
    {
      insertNewRows(rowCount(), 1, index.column(), value);
    }
  else if (role == Qt::EditRole)
    {
      CModelValue & ModelValue = mpGlobalQuantities->operator[](index.row());
      CData OldData = ModelValue.toData();

      switch (index.column())
        {
          case COL_NAME_GQ:
            if (mpGlobalQuantities->getIndex(TO_UTF8(value.toString())) == C_INVALID_INDEX)
              {
                ModelValue.setObjectName(TO_UTF8(value.toString()));
              }

            break;

          case COL_TYPE_GQ:
            ModelValue.setStatus(CModelEntity::StatusName.toEnum(TO_UTF8(value.toString())));
            break;

          case COL_INITIAL_GQ:
            ModelValue.setInitialValue(value.toDouble());
            break;
        }

      CUndoData UndoData;
      ModelValue.createUndoData(UndoData, CUndoData::Type::CHANGE, OldData);

      if (!UndoData.empty())
        {
          ListViews::addUndoMetaData(this, UndoData);
          emit signalNotifyChanges(mpDataModel->recordData(UndoData));
        }
    }

  return true;
}

// virtual
void CQGlobalQuantityDM::resetCacheProtected()
{
  mpGlobalQuantities = dynamic_cast< CDataVectorN < CModelValue > * >(&mpDataModel->getModel()->getModelValues());
  assert(mpGlobalQuantities != NULL);

  mUnitCache.clear();// data() will add to the unit cache, as needed
}

bool CQGlobalQuantityDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  insertNewRows(position, rows);

  return true;
}

bool CQGlobalQuantityDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< CCommonName > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< CCommonName >::iterator it = ToBeDeleted.begin();
  std::vector< CCommonName >::iterator end = ToBeDeleted.end();

  CDataVector< CModelValue >::const_iterator itRow = mpGlobalQuantities->begin() + position;

  for (; it != end; ++it, ++itRow)
    {
      *it = (*itRow).getCN();
    }

  for (it = ToBeDeleted.begin(); it != end; ++it)
    {

      if (mFetched > 0)
        --mFetched;

      const CModelValue * pObj = dynamic_cast< const CModelValue * >(mpDataModel->getObject(*it));

      if (!pObj)
        continue;

      CUndoData UndoData;
      pObj->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      emit signalNotifyChanges(mpDataModel->applyData(UndoData));
    }

  endRemoveRows();

  return true;
}

bool CQGlobalQuantityDM::removeRows(QModelIndexList rows, const QModelIndex& index)
{
  if (rows.isEmpty())
    return false;

  // Build the list of pointers to items to be deleted
  // before actually deleting any item.
  QList< CModelValue * > ModelValues;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    if (i->isValid()
        && !isDefaultRow(*i))
      {
        ModelValues.append(&mpGlobalQuantities->operator[](i->row()));
      }

  QList< CModelValue * >::const_iterator j;

  for (j = ModelValues.begin(); j != ModelValues.end(); ++j)
    {
      CModelValue * pModelValue = *j;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(ListViews::ancestor(this), "quantity",
                                    FROM_UTF8(pModelValue->getObjectName()),
                                    pModelValue);

      if (choice == QMessageBox::Ok)
        {
          removeRows(mpGlobalQuantities->getIndex(pModelValue->getObjectName()), 1);
        }
    }

  return true;
}

void CQGlobalQuantityDM::insertNewRows(int position, int rows, int column, const QVariant & value)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(column == COL_NAME_GQ ? value.toString() : "quantity", COL_NAME_GQ);

      CModelValue * pModelValue = mpDataModel->getModel()->createModelValue(TO_UTF8(name));

      if (pModelValue == NULL)
        continue;

      ++mFetched;

      if (column == COL_TYPE_GQ)
        {
          pModelValue->setStatus(CModelEntity::StatusName.toEnum(TO_UTF8(value.toString())));
        }

      if (column == COL_INITIAL_GQ)
        {
          pModelValue->setInitialValue(value.toDouble());
        }

      CUndoData UndoData(CUndoData::Type::INSERT, pModelValue);
      ListViews::addUndoMetaData(this, UndoData);
      emit signalNotifyChanges(mpDataModel->recordData(UndoData));
    }

  endInsertRows();
}
