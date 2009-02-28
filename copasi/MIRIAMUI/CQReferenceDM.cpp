// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQReferenceDM.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/28 18:25:17 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "UI/qtUtilities.h"
#include "CQReferenceDM.h"

CQReferenceDM::CQReferenceDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(parent)

{
  mpMIRIAMInfo = MIRIAMInfo;
}

int CQReferenceDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
  {
    return mpMIRIAMInfo->getReferences().size();
  }
int CQReferenceDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
  {
    return TOTAL_COLS_REFERENCES;
  }

QVariant CQReferenceDM::data(const QModelIndex &index, int role) const
  {
    if (!index.isValid())
      return QVariant();

    if (index.row() >= rowCount())
      return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
      {
        switch (index.column())
          {
          case COL_RESOURCE_REFERENCE:
            return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()]->getResource())));
          case COL_ID_REFERENCE:
            return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()]->getId())));
          case COL_DESCRIPTION:
            return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()]->getDescription())));
          }
      }
    return QVariant();
  }

QVariant CQReferenceDM::headerData(int section, Qt::Orientation orientation,
                                   int role) const
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    if (orientation == Qt::Horizontal)
      {
        switch (section)
          {
          case COL_RESOURCE_REFERENCE:
            return QVariant(QString("Resource"));
          case COL_ID_REFERENCE:
            return QVariant(QString("ID"));
          case COL_DESCRIPTION:
            return QVariant(QString("Description"));
          default:
            return QVariant();
          }
      }
    else
      return QString("%1").arg(section + 1);
  }
Qt::ItemFlags CQReferenceDM::flags(const QModelIndex &index) const
  {
    if (!index.isValid())
      return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  }

bool CQReferenceDM::setData(const QModelIndex &index, const QVariant &value,
                            int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      switch (index.column())
        {
        case COL_RESOURCE_REFERENCE:
          mpMIRIAMInfo->getReferences()[index.row()]->setResource(TO_UTF8(value.toString()));
          break;
        case COL_ID_REFERENCE:
          mpMIRIAMInfo->getReferences()[index.row()]->setId(TO_UTF8(value.toString()));
          break;
        case COL_DESCRIPTION:
          mpMIRIAMInfo->getReferences()[index.row()]->setDescription(TO_UTF8(value.toString()));
          break;
        }
      emit dataChanged(index, index);
      return true;
    }
  return false;
}

bool CQReferenceDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->createReference("");
    }

  endInsertRows();
  return true;
}

bool CQReferenceDM::removeRows(int position, int rows, const QModelIndex&)
{
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->removeReference(position);
    }

  endRemoveRows();
  return true;
}
