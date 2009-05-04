// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQCreatorDM.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/04 15:19:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "UI/qtUtilities.h"
#include "CQCreatorDM.h"

CQCreatorDM::CQCreatorDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(parent)

{
  mpMIRIAMInfo = MIRIAMInfo;
}

int CQCreatorDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mpMIRIAMInfo->getCreators().size() + 1;
}
int CQCreatorDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_CREATORS;
}

QVariant CQCreatorDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          if (index.column() == COL_ROW_NUMBER)
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
              case COL_FAMILY_NAME:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()]->getFamilyName())));
              case COL_GIVEN_NAME:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()]->getGivenName())));
              case COL_EMAIL:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()]->getEmail())));
              case COL_ORG:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()]->getORG())));
            }
        }
    }

  return QVariant();
}

QVariant CQCreatorDM::headerData(int section, Qt::Orientation orientation,
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
          case COL_FAMILY_NAME:
            return QVariant(QString("Family Name"));
          case COL_GIVEN_NAME:
            return QVariant(QString("Given Name"));
          case COL_EMAIL:
            return QVariant(QString("Email"));
          case COL_ORG:
            return QVariant(QString("Organization"));
          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQCreatorDM::setData(const QModelIndex &index, const QVariant &value,
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
          case COL_FAMILY_NAME:
            mpMIRIAMInfo->getCreators()[index.row()]->setFamilyName(TO_UTF8(value.toString()));
            break;
          case COL_GIVEN_NAME:
            mpMIRIAMInfo->getCreators()[index.row()]->setGivenName(TO_UTF8(value.toString()));
            break;
          case COL_EMAIL:
            mpMIRIAMInfo->getCreators()[index.row()]->setEmail(TO_UTF8(value.toString()));
            break;
          case COL_ORG:
            mpMIRIAMInfo->getCreators()[index.row()]->setORG(TO_UTF8(value.toString()));
            break;
        }

      emit dataChanged(index, index);
      return true;
    }

  return false;
}

bool CQCreatorDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->createCreator("");
    }

  endInsertRows();
  return true;
}

bool CQCreatorDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->removeCreator(position);
    }

  endRemoveRows();
  return true;
}
