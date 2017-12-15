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

#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "model/CCompartment.h"
#include "model/CModel.h"
#include "function/CExpression.h"
#include "copasi/undo/CUndoData.h"

CQCompartmentDM::CQCompartmentDM(QObject *parent)
  : CQBaseDataModel(parent, NULL)
  , mpCompartments(NULL)
{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));

  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::FIXED));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ASSIGNMENT));
  mItemToType.push_back(static_cast<unsigned C_INT32>(CModelEntity::Status::ODE));

  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
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
  return mpCompartments->size() + 1;
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
      if (this->index(index.row(), COL_TYPE_COMPARTMENTS).data() == QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT])))
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
          CCompartment & Compartment = mpCompartments->operator[](index.row());
          const CExpression * pExpression = NULL;

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(Compartment.getObjectName())));

              case COL_TYPE_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[Compartment.getStatus()])));

              case COL_UNIT_COMPARTMENTS:
                return QVariant(mUnits[Compartment.getDimensionality()]);

              case COL_IVOLUME:

                if (role == Qt::EditRole)
                  return QVariant(QString::number(Compartment.getInitialValue(), 'g', 10));
                else
                  return QVariant(Compartment.getInitialValue());

              case COL_VOLUME:
                return QVariant(Compartment.getValue());

              case COL_RATE_COMPARTMENTS:
                return QVariant(Compartment.getRate());

              case COL_IEXPRESSION_COMPARTMENTS:
              {
                pExpression = Compartment.getInitialExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }

              case COL_EXPRESSION_COMPARTMENTS:
              {
                pExpression = Compartment.getExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                else
                  return QVariant();
              }

#ifdef WITH_SDE_SUPPORT

              case COL_NEXPRESSION_COMPARTMENTS:
              {
                pExpression = Compartment.getNoiseExpressionPtr();

                if (Compartment.hasNoise() && pExpression != NULL)
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

QVariant CQCompartmentDM::headerData(int section, Qt::Orientation orientation,
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

          case COL_NAME_COMPARTMENTS:
            return QVariant(QString("Name"));

          case COL_TYPE_COMPARTMENTS:
            return QVariant(QString("     Type     "));

          case COL_UNIT_COMPARTMENTS:
            return QVariant("Unit");

          case COL_IVOLUME:
            return QVariant("Initial Size\n" + ValueUnit);

          case COL_VOLUME:
            return QVariant("Size\n" + ValueUnit);

          case COL_RATE_COMPARTMENTS:
            return QVariant("Rate\n" + RateUnit);

          case COL_IEXPRESSION_COMPARTMENTS:
            return QVariant("Initial Expression\n" + ValueUnit);

          case COL_EXPRESSION_COMPARTMENTS:
            if (ValueUnit == RateUnit)
              return QVariant("Expression\n" + ValueUnit);
            else
              return QVariant("Expression\n" + ValueUnit + " or " + RateUnit);

#ifdef WITH_SDE_SUPPORT

          case COL_NEXPRESSION_COMPARTMENTS:
            return QVariant("Noise Expression");
#endif

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

  if (index.column() == COL_TYPE_COMPARTMENTS &&
      data.toString() == QString(FROM_UTF8(CModelEntity::StatusName[mItemToType[value.toInt()]])))
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow && data != value)
    {
      mpUndoStack->push(new InsertCompartmentRowsCommand(rowCount(), 1, this, index, value));
    }
  else if (role == Qt::EditRole)
    {
      CCompartment & Compartment = mpCompartments->operator[](index.row());
      const CExpression * pExpression = NULL;

      CUndoData Data(CUndoData::Type::CHANGE, &Compartment);
      bool changed = false;

      switch (index.column())
        {
          case COL_NAME_COMPARTMENTS:
            changed = Data.addProperty(CData::OBJECT_NAME,
                                       Compartment.getObjectName(),
                                       TO_UTF8(value.toString()));
            break;

          case COL_TYPE_COMPARTMENTS:
            changed = Data.addProperty(CData::SIMULATION_TYPE,
                                       (unsigned C_INT32) Compartment.getStatus(),
                                       (unsigned C_INT32) mItemToType[value.toInt()]);
            break;

          case COL_IVOLUME:
            changed = Data.addProperty(CData::INITIAL_VALUE,
                                       Compartment.getInitialValue(),
                                       value.toDouble());
            break;
        }

      if (changed)
        {
          mpDataModel->applyData(Data);
          mpDataModel->changed();
        }

      mpUndoStack->push(new CompartmentDataChangeCommand(index, value, this));
    }

  return true;
}

// virtual
void CQCompartmentDM::resetCache()
{
  assert(mpDataModel != NULL);

  mpCompartments = dynamic_cast< CDataVectorNS < CCompartment > * >(&mpDataModel->getModel()->getCompartments());
  assert(mpCompartments != NULL);

  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  mUnits[0] = "1";
  mUnits[1] = FROM_UTF8(CUnit::prettyPrint(pModel->getLengthUnit()));
  mUnits[2] = FROM_UTF8(CUnit::prettyPrint(pModel->getAreaUnit()));
  mUnits[3] = FROM_UTF8(CUnit::prettyPrint(pModel->getVolumeUnit()));
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

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CDataVector< CCompartment >::const_iterator itRow = mpCompartments->begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = itRow->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      mpDataModel->getModel()->removeCompartment(*itDeletedKey);
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
  CCompartment* pCompartment = NULL;

  if (pUndoData != NULL)
    {
      if (mpCompartments->getIndex(pUndoData->getName()) != C_INVALID_INDEX)
      pCompartment = &mpCompartments->operator[](pUndoData->getName());
    }

  if (pCompartment == NULL)
    {
      assert((size_t)index.row() < mpCompartments->size());
      pCompartment = &mpCompartments->operator [](index.row());
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
          pUndoData->fillDependentObjects(mpDataModel->getModel());
        }
    }

  emit dataChanged(index, index);
  emit notifyGUI(ListViews::COMPARTMENT, ListViews::CHANGE, pCompartment->getKey());

  return true;
}

void CQCompartmentDM::insertNewCompartmentRow(int position, int rows, const QModelIndex & index,
    const QVariant& value)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  int column = index.column();

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(index.isValid() && column == COL_NAME_COMPARTMENTS ? value.toString() : "compartment", COL_NAME_COMPARTMENTS);

      CCompartment * pComp = mpDataModel->getModel()->createCompartment(TO_UTF8(name));

      if (pComp == NULL)
        continue;

      mpDataModel->recordData(CUndoData(CUndoData::Type::INSERT, pComp));
      mpDataModel->changed();

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
  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  size_t index = mpCompartments->getIndex(pCompartmentData->getName());

  if (index == C_INVALID_INDEX)
    return;

  removeRow((int) index);
}

void CQCompartmentDM::addCompartmentRow(UndoCompartmentData *pCompartmentData)
{
  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  beginInsertRows(QModelIndex(), 1, 1);

  CDataObject *pCompartment = pCompartmentData->restoreObjectIn(mpDataModel->getModel());

  if (pCompartment != NULL)
    emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());

  endInsertRows();
}

bool CQCompartmentDM::removeCompartmentRows(QModelIndexList& rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  // Build the list of pointers to items to be deleted
  // before actually deleting any item.
  QList <CCompartment *> pCompartments;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && &mpCompartments->operator[](i->row()))
        pCompartments.append(&mpCompartments->operator[](i->row()));
    }

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  QList <CCompartment *>::const_iterator j;

  QModelIndexList lst;
  QList< CCompartment * > ToBeDeleted;

  for (j = pCompartments.begin(); j != pCompartments.end(); ++j)
    {
      CCompartment * pCompartment = *j;

      size_t delRow =
        mpCompartments->CDataVector< CCompartment >::getIndex(pCompartment);

      if (delRow == C_INVALID_INDEX)
        continue;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, "compartment",
                                    FROM_UTF8(pCompartment->getObjectName()),
                                    pCompartment);

      if (choice == QMessageBox::Ok)
        {
          //
          lst.append(index((int) delRow, 0));
          ToBeDeleted.append(pCompartment);
          //removeRow((int)delRow);
        }
    }

  for (j = ToBeDeleted.begin(); j != ToBeDeleted.end(); ++j)
    {
      mpDataModel->applyData(CUndoData(CUndoData::Type::REMOVE, *j));
      mpDataModel->changed();
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
  //reinsert all the Compartments
  QList <UndoCompartmentData *>::const_iterator k;

  beginInsertRows(QModelIndex(), 1, pData.count());

  for (k = pData.begin(); k != pData.end(); ++k)
    {
      UndoCompartmentData* data = *k;

      assert(mpDataModel != NULL);
      CModel * pModel = mpDataModel->getModel();
      assert(pModel != NULL);

      CDataObject *pCompartment = data->restoreObjectIn(pModel);

      if (pCompartment == NULL) continue;

      emit notifyGUI(ListViews::COMPARTMENT, ListViews::ADD, pCompartment->getKey());
    }

  endInsertRows();

  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  return true;
}

void CQCompartmentDM::deleteCompartmentRows(QList <UndoCompartmentData *>& pData)
{
  switchToWidget(CCopasiUndoCommand::COMPARTMENTS);

  QList <UndoCompartmentData *>::const_iterator j;

  for (j = pData.begin(); j != pData.end(); ++j)
    {
      assert(mpDataModel != NULL);
      CModel * pModel = mpDataModel->getModel();
      assert(pModel != NULL);

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
