// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQBiologicalDescriptionDM.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/23 05:12:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "UI/qtUtilities.h"
#include "CQBiologicalDescriptionDM.h"

CQBiologicalDescriptionDM::CQBiologicalDescriptionDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(MIRIAMInfo, parent)

{}

int CQBiologicalDescriptionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
  {
    return mMIRIAMInfo->getBiologicalDescriptions().size();
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
        switch (index.column())
          {
          case COL_RELATIONSHIP:
            return QVariant(QString(FROM_UTF8(mMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getPredicate())));
          case COL_RESOURCE_BD:
            return QVariant(QString(FROM_UTF8(mMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getResource())));
          case COL_ID_BD:
            return QVariant(QString(FROM_UTF8(mMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getId())));
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
      switch (index.column())
        {
        case COL_RELATIONSHIP:
          mMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setPredicate(TO_UTF8(value.toString()));
          break;
        case COL_RESOURCE_BD:
          mMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setResource(TO_UTF8(value.toString()));
          break;
        case COL_ID_BD:
          mMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setId(TO_UTF8(value.toString()));
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
      mMIRIAMInfo->createBiologicalDescription();
    }

  endInsertRows();
  return true;
}

bool CQBiologicalDescriptionDM::removeRows(int position, int rows, const QModelIndex&)
{
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mMIRIAMInfo->removeBiologicalDescription(position);
    }

  endRemoveRows();
  return true;
}
