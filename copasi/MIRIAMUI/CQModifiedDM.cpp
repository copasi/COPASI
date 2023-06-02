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

#include <QtCore/QDateTime>

#include "CQModifiedDM.h"

#include "copasi/copasi.h"

#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

CQModifiedDM::CQModifiedDM(QObject *parent)
  : CQBaseDataModel(parent, NULL)
  , mpMIRIAMInfo(NULL)
{}

void CQModifiedDM::setMIRIAMInfo(CMIRIAMInfo * pMiriamInfo)
{
  beginResetModel();
  mpMIRIAMInfo = pMiriamInfo;
  mFetched = std::min(mFetchLimit, size());
  endResetModel();
}

void CQModifiedDM::resetCacheProtected()
{
  mpMIRIAMInfo = NULL;
}

size_t CQModifiedDM::size() const
{
  if (mpMIRIAMInfo != NULL)
    return (int) mpMIRIAMInfo->getModifications().size();

  return 0;
}

int CQModifiedDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
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
      if (isDefaultRow(index) || index.row() >= (int)mpMIRIAMInfo->getModifications().size())
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
                QDateTime dt(QDateTime::fromString(FROM_UTF8(mpMIRIAMInfo->getModifications()[index.row()].getDate()), Qt::ISODate).toLocalTime());

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
      CUndoData::Type UndoType = CUndoData::Type::CHANGE;

      if (isDefaultRow(index))
        {
          if (index.data() != value)
            {
              insertRow(rowCount(), QModelIndex());
              UndoType = CUndoData::Type::INSERT;
            }
          else
            return false;
        }

      CModification & Modification = mpMIRIAMInfo->getModifications()[index.row()];
      CData OldData = Modification.toData();

      switch (index.column())
        {
          case COL_DATE_MODIFIED:
            Modification.setDate(TO_UTF8(value.toDateTime().toString(Qt::ISODate)));
            break;
        }

      CUndoData UndoData;
      Modification.createUndoData(UndoData, UndoType, OldData);

      if (!UndoData.empty())
        {
          ListViews::addUndoMetaData(this, UndoData);
          emit signalNotifyChanges(mpDataModel->recordData(UndoData));
        }

      return true;
    }

  return false;
}

bool CQModifiedDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  beginInsertRows(parent, position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CModification * pModification = mpMIRIAMInfo->createModification("");

      if (pModification == NULL)
        continue;

      ++mFetched;
    }

  endInsertRows();

  return true;
}

bool CQModifiedDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< const CModification * > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< const CModification * >::iterator it = ToBeDeleted.begin();
  std::vector< const CModification * >::iterator end = ToBeDeleted.end();

  CDataVector< CModification >::const_iterator itRow = mpMIRIAMInfo->getModifications().begin() + position;

  for (; it != end; ++it, ++itRow)
    {
      *it = &*itRow;
    }

  for (it = ToBeDeleted.begin(); it != end; ++it)
    {
      CUndoData UndoData;
      (*it)->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      if (mFetched > 0)
        --mFetched;

      emit signalNotifyChanges(mpDataModel->applyData(UndoData));
    }

  endRemoveRows();

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
      if (i->isValid() && !isDefaultRow(*i) && &mpMIRIAMInfo->getModifications()[i->row()])
        pModifieds.append(&mpMIRIAMInfo->getModifications()[i->row()]);
    }

  bool retVal = false, askEveryItem = true;
  QMessageBox::StandardButton choice = QMessageBox::NoToAll;
  QList <CModification *>::const_iterator j;

  for (j = pModifieds.begin(); j != pModifieds.end(); ++j)
    {
      CModification * pModified = *j;

      size_t delRow =
        mpMIRIAMInfo->getModifications().CDataVector< CModification >::getIndex(pModified);

      if (delRow != C_INVALID_INDEX)
        {
          if (askEveryItem)
            {
              QString dateModified = data(this->index((int) delRow, COL_DATE_MODIFIED), Qt::DisplayRole).toString();
              QString msg = "Do you want to delete Date/Time Modified '";

              if (!dateModified.isNull())
                {
                  msg.append(dateModified);
                }

              msg.append("'?");

              choice = CQMessageBox::question(ListViews::ancestor(this), tr("Confirm Delete"), msg,
                                              QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll,
                                              QMessageBox::No);
            }

          if (choice == QMessageBox::NoToAll)
            {return retVal;}
          else if (choice == QMessageBox::Yes)
            {
              retVal = removeRow((int) delRow);
            }
          else if (choice == QMessageBox::YesToAll)
            {
              askEveryItem = false;
              retVal = removeRow((int) delRow);
            }
        }
    }

  return retVal;
}
