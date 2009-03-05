// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQModifiedDM.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/03/05 17:23:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QDateTime>
#include "UI/qtUtilities.h"
#include "CQModifiedDM.h"

CQModifiedDM::CQModifiedDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(parent)

{
  mpMIRIAMInfo = MIRIAMInfo;
}

int CQModifiedDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
  {
    return mpMIRIAMInfo->getModifications().size();
  }
int CQModifiedDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
  {
    return TOTAL_COLS_MODIFIEDS;
  }

QVariant CQModifiedDM::data(const QModelIndex &index, int role) const
  {
    if (!index.isValid())
      return QVariant();

    if (index.row() >= rowCount())
      return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
      {
        switch (index.column())
          {
          case COL_DATE_MODIFIED:
            QDateTime dt(QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getModifications()[index.row()]->getDate()), Qt::ISODate));
            if (dt.isValid())
              {
                if (role == Qt::DisplayRole)
                  return QVariant(dt.toString(Qt::TextDate));
                else
                  return QVariant(dt.toString(Qt::ISODate));
              }
          }
      }
    return QVariant();
  }

QVariant CQModifiedDM::headerData(int section, Qt::Orientation orientation,
                                  int role) const
  {
    if (role != Qt::DisplayRole)
      return QVariant();

    if (orientation == Qt::Horizontal)
      {
        switch (section)
          {
          case COL_DATE_MODIFIED:
            return QVariant(QString("Date and Time Modified"));
          default:
            return QVariant();
          }
      }
    else
      return QString("%1").arg(section + 1);
  }

bool CQModifiedDM::setData(const QModelIndex &index, const QVariant &value,
                           int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      switch (index.column())
        {
        case COL_DATE_MODIFIED:
          mpMIRIAMInfo->getModifications()[index.row()]->setDate(TO_UTF8(value.toString()));
          break;
        }
      emit dataChanged(index, index);
      return true;
    }
  return false;
}

bool CQModifiedDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->createModification(TO_UTF8(QDateTime::currentDateTime().toString(Qt::ISODate)));
    }

  endInsertRows();
  return true;
}

bool CQModifiedDM::removeRows(int position, int rows, const QModelIndex&)
{
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->removeModification(position);
    }

  endRemoveRows();
  return true;
}
