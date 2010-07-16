// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQReferenceDM.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/07/16 19:01:00 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QMessageBox>

#include "UI/qtUtilities.h"
#include "CQReferenceDM.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

CQReferenceDM::CQReferenceDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(parent)

{
  mpMIRIAMInfo = MIRIAMInfo;
}

int CQReferenceDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mpMIRIAMInfo->getReferences().size() + 1;
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
      if (isDefaultRow(index))
        {
          if (index.column() == COL_RESOURCE_REFERENCE)
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
              case COL_RESOURCE_REFERENCE:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()]->getResource())));
              case COL_ID_REFERENCE:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()]->getId())));
              case COL_DESCRIPTION:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()]->getDescription())));
            }
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
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));
          case COL_RESOURCE_REFERENCE:
            return QVariant(QString("  Resource  "));
          case COL_ID_REFERENCE:
            return QVariant(QString("ID   "));
          case COL_DESCRIPTION:
            return QVariant(QString("Description"));
          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQReferenceDM::setData(const QModelIndex &index, const QVariant &value,
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
      emit notifyGUI(ListViews::MIRIAM, ListViews::CHANGE, "");
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

  emit notifyGUI(ListViews::MIRIAM, ListViews::ADD, "");
  return true;
}

bool CQReferenceDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->removeReference(position);
    }

  endRemoveRows();

  emit notifyGUI(ListViews::MIRIAM, ListViews::DELETE, "");
  return true;
}

bool CQReferenceDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CReference *> pReferences;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && mpMIRIAMInfo->getReferences()[(*i).row()])
        pReferences.append(mpMIRIAMInfo->getReferences()[(*i).row()]);
    }

  bool retVal = false, askEveryItem = true;
  QMessageBox::StandardButton choice = QMessageBox::NoToAll;
  QList <CReference *>::const_iterator j;

  for (j = pReferences.begin(); j != pReferences.end(); ++j)
    {
      CReference * pReference = *j;

      unsigned C_INT32 delRow =
        mpMIRIAMInfo->getReferences().CCopasiVector< CReference >::getIndex(pReference);

      if (delRow != C_INVALID_INDEX)
        {
          if (askEveryItem)
            {
              QString resource = data(this->index(delRow, COL_RESOURCE_REFERENCE), Qt::DisplayRole).toString();
              QString Id = data(this->index(delRow, COL_ID_REFERENCE), Qt::DisplayRole).toString();
              QString msg = "Do you want to delete Reference '";

              if (!resource.isNull())
                {
                  msg.append(resource);
                }

              if (!Id.isNull())
                {
                  msg.append(":");
                  msg.append(Id);
                }

              msg.append("'?");

              choice = QMessageBox::question(NULL, tr("Confirm Delete"), msg,
                                             QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll,
                                             QMessageBox::No);
            }

          if (choice == QMessageBox::NoToAll)
            {return retVal;}
          else if (choice == QMessageBox::Yes)
            {retVal = removeRow(delRow);}
          else if (choice == QMessageBox::YesToAll)
            {
              askEveryItem = false;
              retVal = removeRow(delRow);
            }
        }
    }

  return true;
}
