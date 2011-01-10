// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQModifiedDM.cpp,v $
//   $Revision: 1.10.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/10 13:36:42 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QDateTime>
#include <QMessageBox>

#include "UI/qtUtilities.h"
#include "CQModifiedDM.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

CQModifiedDM::CQModifiedDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(parent)

{
  mpMIRIAMInfo = MIRIAMInfo;
}

int CQModifiedDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mpMIRIAMInfo->getModifications().size() + 1;
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
      if (isDefaultRow(index))
        {
          if (index.column() == COL_ROW_NUMBER)
            return QVariant(QString(""));
          else if (index.column() == COL_DATE_MODIFIED)
            {
              if (role == Qt::DisplayRole)
                return QVariant(QDateTime());
              else
                return QVariant(QDateTime::currentDateTime());
            }
          else
            return QVariant(QString(""));
        }
      else
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);
              case COL_DATE_MODIFIED:
                QDateTime dt(QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getModifications()[index.row()]->getDate()), Qt::ISODate));

                if (dt.isValid())
                  return QVariant(dt);
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
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));
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
      if (isDefaultRow(index))
        {
          if (index.data() != value)
            insertRow();
          else
            return false;
        }

      switch (index.column())
        {
          case COL_DATE_MODIFIED:
            mpMIRIAMInfo->getModifications()[index.row()]->setDate(TO_UTF8(value.toDateTime().toString(Qt::ISODate)));
            break;
        }

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::MIRIAM, ListViews::CHANGE, "");
      return true;
    }

  return false;
}

bool CQModifiedDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      //mpMIRIAMInfo->createModification(TO_UTF8(QDateTime::currentDateTime().toString(Qt::ISODate)));
      mpMIRIAMInfo->createModification("");
    }

  endInsertRows();

  emit notifyGUI(ListViews::MIRIAM, ListViews::ADD, "");
  return true;
}

bool CQModifiedDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->removeModification(position);
    }

  endRemoveRows();

  emit notifyGUI(ListViews::MIRIAM, ListViews::DELETE, "");
  return true;
}

bool CQModifiedDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList < CModification * > pModifieds;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && mpMIRIAMInfo->getModifications()[(*i).row()])
        pModifieds.append(mpMIRIAMInfo->getModifications()[(*i).row()]);
    }

  bool retVal = false, askEveryItem = true;
  QMessageBox::StandardButton choice = QMessageBox::NoToAll;
  QList <CModification *>::const_iterator j;

  for (j = pModifieds.begin(); j != pModifieds.end(); ++j)
    {
      CModification * pModified = *j;

      unsigned C_INT32 delRow =
        mpMIRIAMInfo->getModifications().CCopasiVector< CModification >::getIndex(pModified);

      if (delRow != C_INVALID_INDEX)
        {
          if (askEveryItem)
            {
              QString dateModified = data(this->index(delRow, COL_DATE_MODIFIED), Qt::DisplayRole).toString();
              QString msg = "Do you want to delete Date/Time Modified '";

              if (!dateModified.isNull())
                {
                  msg.append(dateModified);
                }

              msg.append("'?");

              choice = QMessageBox::question(NULL, tr("Confirm Delete"), msg,
                                             QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll,
                                             QMessageBox::No);
            }

          if (choice == QMessageBox::NoToAll)
            {return retVal;}
          else if (choice == QMessageBox::Yes)
            {
              retVal = removeRow(delRow);
            }
          else if (choice == QMessageBox::YesToAll)
            {
              askEveryItem = false;
              retVal = removeRow(delRow);
            }
        }
    }

  return retVal;
}
