// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQBiologicalDescriptionDM.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/04 15:19:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "UI/qtUtilities.h"
#include "CQBiologicalDescriptionDM.h"

CQBiologicalDescriptionDM::CQBiologicalDescriptionDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(parent)

{
  mpMIRIAMInfo = MIRIAMInfo;
}

int CQBiologicalDescriptionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mpMIRIAMInfo->getBiologicalDescriptions().size() + 1;
}
int CQBiologicalDescriptionDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_BIOLOGICAL_DESCRIPTIONS;
}

QVariant CQBiologicalDescriptionDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          if (index.column() == COL_RELATIONSHIP || index.column() == COL_RESOURCE_BD)
            return QVariant(QString("-- select --"));
          else if (index.column() == COL_ROW_NUMBER)
            return QVariant(index.row() + 1);
          else
            return QVariant(QString(""));
        }
      else
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);
              case COL_RELATIONSHIP:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getPredicate())));
              case COL_RESOURCE_BD:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getResource())));
              case COL_ID_BD:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getId())));
            }
        }
    }

  return QVariant();
}

QVariant CQBiologicalDescriptionDM::headerData(int section, Qt::Orientation orientation,
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
          case COL_RELATIONSHIP:
            return QVariant(QString("Relationship"));
          case COL_RESOURCE_BD:
            return QVariant(QString("Resource"));
          case COL_ID_BD:
            return QVariant(QString("ID"));
          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQBiologicalDescriptionDM::setData(const QModelIndex &index, const QVariant &value,
                                        int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          if (index.data() != value)
            insertRow();
          else
            return false;
        }

      switch (index.column())
        {
          case COL_RELATIONSHIP:
            mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setPredicate(TO_UTF8(value.toString()));
            break;
          case COL_RESOURCE_BD:
            mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setResource(TO_UTF8(value.toString()));
            break;
          case COL_ID_BD:
            mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setId(TO_UTF8(value.toString()));
            break;
        }

      emit dataChanged(index, index);
      return true;
    }

  return false;
}

bool CQBiologicalDescriptionDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->createBiologicalDescription();
    }

  endInsertRows();
  return true;
}

bool CQBiologicalDescriptionDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->removeBiologicalDescription(position);
    }

  endRemoveRows();
  return true;
}
