// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQReferenceDM.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/09 21:05:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQReferenceDM.h"
#include "UI/qtUtilities.h"

CQReferenceDM::CQReferenceDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : QAbstractTableModel(parent)

{
  mMIRIAMInfo = MIRIAMInfo;
}

int CQReferenceDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
  {
    return mMIRIAMInfo->getReferences().size();
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
          case COL_RESOURCE:
            return QVariant(QString(FROM_UTF8(mMIRIAMInfo->getReferences()[index.row()]->getResource())));
          case COL_ID:
            return QVariant(QString(FROM_UTF8(mMIRIAMInfo->getReferences()[index.row()]->getId())));
          case COL_DESCRIPTION:
            return QVariant(QString(FROM_UTF8(mMIRIAMInfo->getReferences()[index.row()]->getDescription())));
          default:
            return QVariant();
          }
      }
    else
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
          case COL_RESOURCE:
            return QVariant(QString("Resource"));
          case COL_ID:
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
        case COL_RESOURCE:
          mMIRIAMInfo->getReferences()[index.row()]->setResource(TO_UTF8(value.toString()));
          break;
        case COL_ID:
          mMIRIAMInfo->getReferences()[index.row()]->setId(TO_UTF8(value.toString()));
          break;
        case COL_DESCRIPTION:
          mMIRIAMInfo->getReferences()[index.row()]->setDescription(TO_UTF8(value.toString()));
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
      mMIRIAMInfo->createReference("");
    }

  endInsertRows();
  return true;
}

bool CQReferenceDM::insertRow()
{
  return insertRows(rowCount(), 1);
}

bool CQReferenceDM::removeRows(int position, int rows, const QModelIndex&)
{
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mMIRIAMInfo->removeReference(position);
    }

  endRemoveRows();
  return true;
}

bool CQReferenceDM::removeRow(int position)
{
  return removeRows(position, 1);
}

bool CQReferenceDM::clear()
{
  return removeRows(0, rowCount());
}
