// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CQCompartmentDM.h"

#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "model/CReaction.h"
#include "model/CMetab.h"
#include "model/CReactionInterface.h"
#include "model/CEvent.h"
#include "undoFramework/InsertCompartmentRowsCommand.h"
#include "undoFramework/RemoveCompartmentRowsCommand.h"
#include "undoFramework/RemoveAllCompartmentRowsCommand.h"
#include "undoFramework/CompartmentDataChangeCommand.h"
#include "undoFramework/UndoCompartmentData.h"
#include "undoFramework/UndoReactionData.h"
#include "undoFramework/UndoSpeciesData.h"
#include "undoFramework/UndoGlobalQuantityData.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"

#include "UI/CQCopasiApplication.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "function/CExpression.h"

CQCompartmentDM::CQCompartmentDM(QObject *parent)
  : CQBaseDataModel(parent)

{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ODE]));

  mItemToType.push_back(CModelEntity::FIXED);
  mItemToType.push_back(CModelEntity::ASSIGNMENT);
  mItemToType.push_back(CModelEntity::ODE);
}

const QStringList& CQCompartmentDM::getTypes()
{
  return mTypes;
}

const std::vector< unsigned C_INT32 >& CQCompartmentDM::getItemToType()
{
  return mItemToType;
}

int CQCompartmentDM::rowCount(const QModelIndex&) const
{
  return CCopasiRootContainer::getDatamodelList()->operator[](0).getModel()->getCompartments().size() + 1;
}
int CQCompartmentDM::columnCount(const QModelIndex&) const
{
  return TOTAL_COLS_COMPARTMENTS;
}

Qt::ItemFlags CQCompartmentDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_COMPARTMENTS || index.column() == COL_TYPE_COMPARTMENTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else if (index.column() == COL_IVOLUME)
    {
      if (this->index(index.row(), COL_TYPE_COMPARTMENTS).data() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::ASSIGNMENT])))
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEnabled;
      else
        return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQCompartmentDM::data(const QModelIndex &index, int role) const
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

              case COL_NAME_COMPARTMENTS:
                return QVariant(QString("New Compartment"));

              case COL_TYPE_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[0]])));

              case COL_IVOLUME:
                return QVariant(QString::number(1.0, 'g', 10));

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CCompartment *pComp = &CCopasiRootContainer::getDatamodelList()->operator[](0).getModel()->getCompartments()[index.row()];
          const CExpression * pExpression = NULL;

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(pComp->getObjectName())));

              case COL_TYPE_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[pComp->getStatus()])));

              case COL_IVOLUME:

                if (role == Qt::EditRole)
                  return QVariant(QString::number(pComp->getInitialValue(), 'g', 10));
                else
                  return QVariant(pComp->getInitialValue());

              case COL_VOLUME:
                return QVariant(pComp->getValue());

              case COL_RATE_COMPARTMENTS:
                return QVariant(pComp->getRate());

              case COL_IEXPRESSION_COMPARTMENTS:
              {
                pExpression = pComp->getInitialExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }

              case COL_EXPRESSION_COMPARTMENTS:
              {
                pExpression = pComp->getExpressionPtr();

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

QVariant CQCompartmentDM::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    {
      QString ValueUnits, RateUnits, ExpressionUnits;
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      const CModel * pModel = CCopasiRootContainer::getDatamodelList()->operator[](0).getModel();

      if (pModel)
        {
          ValueUnits = FROM_UTF8(pModel->getVolumeUnitsDisplayString());

          if (!ValueUnits.isEmpty())
            ValueUnits = "\n(" + ValueUnits + ")";

          RateUnits = FROM_UTF8(pModel->getVolumeRateUnitsDisplayString());

          if (!RateUnits.isEmpty())
            RateUnits = "\n(" + RateUnits + ")";

          if (!ValueUnits.isEmpty() && !RateUnits.isEmpty())
            {
              if (ValueUnits == RateUnits)
                ExpressionUnits = ValueUnits;
              else
                ExpressionUnits = "\n(" + FROM_UTF8(pModel->getVolumeUnitsDisplayString()) + " or " + FROM_UTF8(pModel->getVolumeRateUnitsDisplayString()) + ")";
            }
          else if (!ValueUnits.isEmpty())
            ExpressionUnits = "\n(" + FROM_UTF8(pModel->getVolumeUnitsDisplayString()) + " or 1)";
          else if (!RateUnits.isEmpty())
            ExpressionUnits = "\n(1 or " + FROM_UTF8(pModel->getVolumeRateUnitsDisplayString()) + ")";
        }

      switch (section)
        {
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));

          case COL_NAME_COMPARTMENTS:
            return QVariant(QString("Name"));

          case COL_TYPE_COMPARTMENTS:
            return QVariant(QString("     Type     "));

          case COL_IVOLUME:
            return QVariant("Initial Volume" + ValueUnits);

          case COL_VOLUME:
            return QVariant("Volume" + ValueUnits);

          case COL_RATE_COMPARTMENTS:
            return QVariant("Rate" + RateUnits);

          case COL_IEXPRESSION_COMPARTMENTS:
            return QVariant("Initial Expression" + ValueUnits);

          case COL_EXPRESSION_COMPARTMENTS:
            return QVariant("Expression" + ExpressionUnits);

          default:
            return QVariant();
        }
    }
  else  //Vertical header
    return QString("%1").arg(section + 1);
}

bool CQCompartmentDM::setData(const QModelIndex &index, const QVariant &value,
                              int role)
{
  QVariant data = index.data();

  if (data == value)
    return false;

  if (index.column() == COL_TYPE_COMPARTMENTS &&  data.toString() == QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow && data != value)
    {
      mpUndoStack->push(new InsertCompartmentRowsCommand(rowCount(), 1, this, index, value));
    }
  else
    {
      mpUndoStack->push(new CompartmentDataChangeCommand(index, value, role, this));
    }

  return true;
}

bool CQCompartmentDM::insertRows(int position, int rows, const QModelIndex&)
{
  mpUndoStack->push(new InsertCompartmentRowsCommand(position, rows, this));

  return true;
}

bool CQCompartmentDM::removeRows(int position, int rows)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  CModel * pModel = CCopasiRootContainer::getDatamodelList()->operator[](0).getModel();

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CCopasiVector< CCompartment >::const_iterator itRow = pModel->getCompartments().begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = itRow->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      CCopasiRootContainer::getDatamodelList()->operator[](0).getModel()->removeCompartment(*itDeletedKey);
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::DELETE, *itDeletedKey);
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::DELETE, "");
      emit notifyGUI(ListViews::METABOLITE, ListViews::DELETE, ""); //Refresh all as there may be dependencies.
    }

  endRemoveRows();

  return true;
}

bool CQCompartmentDM::removeRows(QModelIndexList rows, const QModelIndex& index)
{
  removeCompartmentRows(rows, index);

  return true;
}

bool CQCompartmentDM::compartmentDataChange(const QModelIndex& index,
    const QVariant &value,
    UndoCompartmentData* pUndoData)
{
  GET_MODEL_OR(pModel, return false);
  CCopasiVectorNS < CCompartment > & Compartments = pModel->getCompartments();
  CCompartment* pCompartment = NULL;

  if (pUndoData != NULL)
    {
      pCompartment = &Compartments[pUndoData->getName()];
    }

  if (pCompartment == NULL)
    {
      assert((size_t)index.row() < Compartments.size());
      pCompartment = &Compartments[index.row()];
    }

  assert(pCompartment != NULL);

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  int column = index.column();

  if (column == COL_NAME_COMPARTMENTS)
    {
      pCompartment->setObjectName(TO_UTF8(value.toString()));
      emit notifyGUI(ListViews::COMPARTMENT, ListViews::RENAME, pCompartment->getKey());
    }
  else if (column == COL_TYPE_COMPARTMENTS)
    pCompartment->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
  else if (column == COL_IVOLUME)
    {
      pCompartment->setInitialValue(value.toDouble());

      if (pUndoData != NULL)
        {
          pUndoData->fillDependentObjects(pModel);
        }
    }

  emit dataChanged(index, index);
  emit notifyGUI(ListViews::COMPARTMENT, ListViews::CHANGE, pCompartment->getKey());

  return true;
}

void CQCompartmentDM::insertNewCompartmentRow(int position, int rows, const QModelIndex & index,
    const QVariant& value)
{
  GET_MODEL_OR_RETURN(pModel);

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  int column = index.column();

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(index.isValid() && column == COL_NAME_COMPARTMENTS ? value.toString() : "compartment", COL_NAME_COMPARTMENTS);

      CCompartment * pComp = pModel->createCompartment(TO_UTF8(name));

      if (pComp == NULL)
        continue;

      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pComp->getKey());

      if (index.isValid())
        {
          if (column == COL_TYPE_COMPARTMENTS)
            {
              CModelEntity::Status status = (CModelEntity::Status) mItemToType[value.toInt()];
              pComp->setStatus(status);
            }

          if (column == COL_IVOLUME)
            {
              pComp->setInitialValue(value.toDouble());
            }
        }
    }

  endInsertRows();
}

void CQCompartmentDM::deleteCompartmentRow(UndoCompartmentData *pCompartmentData)
{
  GET_MODEL_OR_RETURN(pModel);

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  size_t index = pModel->getCompartments().getIndex(pCompartmentData->getName());

  if (index == C_INVALID_INDEX)
    return;

  removeRow((int) index);
}

void CQCompartmentDM::addCompartmentRow(UndoCompartmentData *pCompartmentData)
{
  GET_MODEL_OR_RETURN(pModel);

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  beginInsertRows(QModelIndex(), 1, 1);

  CCompartment *pCompartment = pCompartmentData->restoreObjectIn(pModel);

  if (pCompartment != NULL)
    emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());

  endInsertRows();
}

bool CQCompartmentDM::removeCompartmentRows(QModelIndexList& rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  GET_MODEL_OR(pModel, return false);

  // Build the list of pointers to items to be deleted
  // before actually deleting any item.
  QList <CCompartment *> pCompartments;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && &pModel->getCompartments()[i->row()])
        pCompartments.append(&pModel->getCompartments()[i->row()]);
    }

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  QList <CCompartment *>::const_iterator j;

  QModelIndexList lst;

  for (j = pCompartments.begin(); j != pCompartments.end(); ++j)
    {
      CCompartment * pCompartment = *j;

      size_t delRow =
        pModel->getCompartments().CCopasiVector< CCompartment >::getIndex(pCompartment);

      if (delRow == C_INVALID_INDEX)
        continue;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, "compartment",
                                    FROM_UTF8(pCompartment->getObjectName()),
                                    pCompartment->getDeletedObjects());

      if (choice == QMessageBox::Ok)
        {
          //
          lst.append(index((int) delRow, 0));
          //removeRow((int)delRow);
        }
    }

  //
  if (!lst.empty())
    {
      mpUndoStack->push(new RemoveCompartmentRowsCommand(lst, this));
    }

  return true;
}

bool CQCompartmentDM::insertCompartmentRows(QList <UndoCompartmentData *>& pData)
{
  GET_MODEL_OR(pModel, return false);

  //reinsert all the Compartments
  QList <UndoCompartmentData *>::const_iterator k;

  beginInsertRows(QModelIndex(), 1, pData.count());

  for (k = pData.begin(); k != pData.end(); ++k)
    {
      UndoCompartmentData* data = *k;

      CCompartment *pCompartment = data->restoreObjectIn(pModel);

      if (pCompartment == NULL) continue;

      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());
    }

  endInsertRows();

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  return true;
}

void CQCompartmentDM::deleteCompartmentRows(QList <UndoCompartmentData *>& pData)
{
  GET_MODEL_OR_RETURN(pModel);

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  QList <UndoCompartmentData *>::const_iterator j;

  for (j = pData.begin(); j != pData.end(); ++j)
    {
      UndoCompartmentData * data = *j;
      size_t index = pModel->getCompartments().getIndex(data->getName());

      if (index == C_INVALID_INDEX)
        continue;

      removeRow((int) index);
    }
}

bool CQCompartmentDM::clear()
{
  mpUndoStack->push(new RemoveAllCompartmentRowsCommand(this, QModelIndex()));
  return true;
}

bool CQCompartmentDM::removeAllCompartmentRows()
{
  return removeRows(0, rowCount() - 1);
}
