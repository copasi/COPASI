// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartmentDM.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/15 19:36:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QString>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CCompartment.h"
#include "function/CExpression.h"

#include "CQCompartmentDM.h"
#include "qtUtilities.h"

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

int CQCompartmentDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments().size() + 1;
}
int CQCompartmentDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
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

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);
              case COL_NAME_COMPARTMENTS:
                return QVariant(QString("No Name"));
              case COL_TYPE_COMPARTMENTS:
                return QVariant(QString("fixed"));
              case COL_IVOLUME:
                return QVariant(QString("1"));
              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CCompartment *pComp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[index.row()];
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
                return QVariant(QString::number(pComp->getInitialValue()));

              case COL_VOLUME:
                return QVariant(QString::number(pComp->getValue()));

              case COL_RATE:
                return QVariant(QString::number(pComp->getRate()));

              case COL_IEXPRESSION_COMPARTMENTS:
              {
                if (pComp->getInitialExpression() != "")
                  {
                    pExpression = pComp->getInitialExpressionPtr();

                    if (pExpression != NULL)
                      return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
                    else
                      return QVariant();
                  }
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
      const CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

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
            return QVariant(QString("Type"));
          case COL_IVOLUME:
            return QVariant("Initial Volume" + ValueUnits);
          case COL_VOLUME:
            return QVariant("Volume" + ValueUnits);
          case COL_RATE:
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
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.column() == COL_TYPE_COMPARTMENTS)
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
      CCompartment *pComp = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getCompartments()[index.row()];

      if (index.column() == COL_NAME_COMPARTMENTS)
        pComp->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_TYPE_COMPARTMENTS)
        pComp->setStatus((CModelEntity::Status) mItemToType[value.toInt()]);
      else if (index.column() == COL_IVOLUME)
        pComp->setInitialValue(value.toDouble());

      if (defaultRow && this->index(index.row(), COL_NAME_COMPARTMENTS).data().toString() == "No Name")
        pComp->setObjectName(TO_UTF8(createNewName("Compartment", COL_NAME_COMPARTMENTS)));

      emit dataChanged(index, index);
    }

  return true;
}

bool CQCompartmentDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createCompartment("");
    }

  endInsertRows();
  return true;
}

bool CQCompartmentDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->removeCompartment(position);
    }

  endRemoveRows();
  return true;
}
