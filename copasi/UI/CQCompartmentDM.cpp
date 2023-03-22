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

#include "CQCompartmentDM.h"

#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/model/CReaction.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReactionInterface.h"
#include "copasi/model/CEvent.h"

#include "copasi/UI/CQCopasiApplication.h"

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/undo/CUndoData.h"

CQCompartmentDM::CQCompartmentDM(QObject *parent)
  : CQBaseDataModel(parent, NULL)
  , mpCompartments(NULL)
{
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ASSIGNMENT]));
  mTypes.push_back(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::ODE]));

  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
  mUnits.append("?");
}

const QStringList& CQCompartmentDM::getTypes()
{
  return mTypes;
}

size_t CQCompartmentDM::size() const
{
  if (mpCompartments != NULL)
    return mpCompartments->size();

  return 0;
}

int CQCompartmentDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
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
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled;
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
      if (isDefaultRow(index) || index.row() >= (int) mpCompartments->size())
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(QString(""));

              case COL_NAME_COMPARTMENTS:
                return QVariant(QString("New Compartment"));

              case COL_TYPE_COMPARTMENTS:
                return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[CModelEntity::Status::FIXED])));

              case COL_IVOLUME:
                return QVariant(convertToQString(1.0));

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
                  return QVariant(convertToQString(Compartment.getInitialValue()));
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

              case COL_NEXPRESSION_COMPARTMENTS:
              {
                pExpression = Compartment.getNoiseExpressionPtr();

                if (Compartment.hasNoise() && pExpression != NULL)
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

          case COL_NEXPRESSION_COMPARTMENTS:
            return QVariant("Noise Expression");

          default:
            return QVariant();
        }
    }
  else  //Vertical header
    return QString("%1").arg(section + 1);
}

bool CQCompartmentDM::setData(const QModelIndex &index,
                              const QVariant &value,
                              int role)
{
  QVariant data = index.data();

  if (data == value)
    return false;

  if (isDefaultRow(index) && data != value)
    {
      insertNewRows(rowCount(), 1, index.column(), value);
    }
  else if (role == Qt::EditRole)
    {
      CCompartment & Compartment = mpCompartments->operator[](index.row());

      CData OldData = Compartment.toData();

      switch (index.column())
        {
          case COL_NAME_COMPARTMENTS:
            if (mpCompartments->getIndex(TO_UTF8(value.toString())) == C_INVALID_INDEX)
              {
                Compartment.setObjectName(TO_UTF8(value.toString()));
              }

            break;

          case COL_TYPE_COMPARTMENTS:
            Compartment.setStatus(CModelEntity::StatusName.toEnum(TO_UTF8(value.toString())));
            break;

          case COL_IVOLUME:
            Compartment.setInitialValue(value.toDouble());
            break;
        }

      CUndoData UndoData;
      Compartment.createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, (CCore::Framework) mFramework);

      if (!UndoData.empty())
        {
          ListViews::addUndoMetaData(this, UndoData);
          emit signalNotifyChanges(mpDataModel->recordData(UndoData));
        }
    }

  return true;
}

// virtual
void CQCompartmentDM::resetCacheProtected()
{
  mpCompartments = dynamic_cast< CDataVectorNS < CCompartment > * >(&mpDataModel->getModel()->getCompartments());
  assert(mpCompartments != NULL);

  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  mUnits[0] = "1";
  mUnits[1] = FROM_UTF8(CUnit::prettyPrint(pModel->getLengthUnit()));
  mUnits[2] = FROM_UTF8(CUnit::prettyPrint(pModel->getAreaUnit()));
  mUnits[3] = FROM_UTF8(CUnit::prettyPrint(pModel->getVolumeUnit()));
}

bool CQCompartmentDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  insertNewRows(position, rows);

  return true;
}

bool CQCompartmentDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< CCommonName > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< CCommonName >::iterator it = ToBeDeleted.begin();
  std::vector< CCommonName >::iterator end = ToBeDeleted.end();

  CDataVector< CCompartment >::const_iterator itRow = mpCompartments->begin() + position;

  for (; it != end; ++it, ++itRow)
    {
      *it = itRow->getCN();
    }

  for (it = ToBeDeleted.begin(); it != end; ++it)
    {
      if (mFetched > 0)
        --mFetched;

      const CCompartment * pObj = dynamic_cast< const CCompartment * >(mpDataModel->getObject(*it));

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

bool CQCompartmentDM::removeRows(QModelIndexList rows, const QModelIndex& index)
{
  if (rows.isEmpty())
    return false;

  // Build the list of pointers to items to be deleted
  // before actually deleting any item.
  QList <CCompartment *> Compartments;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    if (i->isValid()
        && !isDefaultRow(*i))
      {
        Compartments.append(&mpCompartments->operator[](i->row()));
      }

  QList< CCompartment * >::const_iterator j;

  for (j = Compartments.begin(); j != Compartments.end(); ++j)
    {
      CCompartment * pCompartment = *j;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(ListViews::ancestor(this), "compartment",
                                    FROM_UTF8(pCompartment->getObjectName()),
                                    pCompartment);

      if (choice == QMessageBox::Ok)
        {
          removeRows(mpCompartments->getIndex(pCompartment->getObjectName()), 1);
        }
    }

  return true;
}

void CQCompartmentDM::insertNewRows(int position, int rows, int column, const QVariant & value)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(column == COL_NAME_COMPARTMENTS ? value.toString() : "compartment", COL_NAME_COMPARTMENTS);

      CCompartment * pComp = mpDataModel->getModel()->createCompartment(TO_UTF8(name));

      if (pComp == NULL)
        continue;

      ++mFetched;

      if (column == COL_TYPE_COMPARTMENTS)
        {
          pComp->setStatus(CModelEntity::StatusName.toEnum(TO_UTF8(value.toString())));
        }

      if (column == COL_IVOLUME)
        {
          pComp->setInitialValue(value.toDouble());
        }

      CUndoData UndoData(CUndoData::Type::INSERT, pComp);
      ListViews::addUndoMetaData(this, UndoData);
      emit signalNotifyChanges(mpDataModel->recordData(UndoData));
    }

  endInsertRows();
}
