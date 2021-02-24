// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "CQReferenceDM.h"

#include "copasi/copasi.h"

#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

CQReferenceDM::CQReferenceDM(QObject *parent)
  : CQBaseDataModel(parent, NULL)
  , mpMIRIAMInfo(NULL)
{}

void CQReferenceDM::setMIRIAMInfo(CMIRIAMInfo * pMiriamInfo)
{
  beginResetModel();
  mpMIRIAMInfo = pMiriamInfo;
  mFetched = std::min(mFetchLimit, size());
  endResetModel();
}

void CQReferenceDM::resetCacheProtected()
{
  mpMIRIAMInfo = NULL;
}

size_t CQReferenceDM::size() const
{
  if (mpMIRIAMInfo != NULL)
    return (int) mpMIRIAMInfo->getReferences().size();

  return 0;
}

int CQReferenceDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
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
      if (isDefaultRow(index) || index.row() >= (int)mpMIRIAMInfo->getReferences().size())
        {
          if (index.column() == COL_RESOURCE_REFERENCE)
            return QVariant(QString("-- select --"));
          else if (index.column() == COL_ROW_NUMBER)
            return QVariant(QString(""));
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
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()].getResource())));

              case COL_ID_REFERENCE:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()].getId())));

              case COL_DESCRIPTION:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getReferences()[index.row()].getDescription())));
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

      CReference & Reference = mpMIRIAMInfo->getReferences()[index.row()];
      CData OldData = Reference.toData();

      switch (index.column())
        {
          case COL_RESOURCE_REFERENCE:
            Reference.setResource(TO_UTF8(value.toString()));
            break;

          case COL_ID_REFERENCE:
            Reference.setId(TO_UTF8(value.toString()));
            break;

          case COL_DESCRIPTION:
            Reference.setDescription(TO_UTF8(value.toString()));
            break;
        }

      CUndoData UndoData;
      Reference.createUndoData(UndoData, UndoType, OldData);

      if (!UndoData.empty())
        {
          ListViews::addUndoMetaData(this, UndoData);
          emit signalNotifyChanges(mpDataModel->recordData(UndoData));
        }

      return true;
    }

  return false;
}

bool CQReferenceDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  beginInsertRows(parent, position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CReference * pReference = mpMIRIAMInfo->createReference("");

      if (pReference == NULL)
        continue;

      ++mFetched;
    }

  endInsertRows();

  return true;
}

bool CQReferenceDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< const CReference * > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< const CReference * >::iterator it = ToBeDeleted.begin();
  std::vector< const CReference * >::iterator end = ToBeDeleted.end();

  CDataVector< CReference >::const_iterator itRow = mpMIRIAMInfo->getReferences().begin() + position;

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
      if (i->isValid() && !isDefaultRow(*i) && &mpMIRIAMInfo->getReferences()[i->row()])
        pReferences.append(&mpMIRIAMInfo->getReferences()[i->row()]);
    }

  bool retVal = false, askEveryItem = true;
  QMessageBox::StandardButton choice = QMessageBox::NoToAll;
  QList <CReference *>::const_iterator j;

  for (j = pReferences.begin(); j != pReferences.end(); ++j)
    {
      CReference * pReference = *j;

      size_t delRow =
        mpMIRIAMInfo->getReferences().CDataVector< CReference >::getIndex(pReference);

      if (delRow != C_INVALID_INDEX)
        {
          if (askEveryItem)
            {
              QString resource = data(this->index((int) delRow, COL_RESOURCE_REFERENCE), Qt::DisplayRole).toString();
              QString Id = data(this->index((int) delRow, COL_ID_REFERENCE), Qt::DisplayRole).toString();
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

              choice = CQMessageBox::question(ListViews::ancestor(this), tr("Confirm Delete"), msg,
                                              QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll,
                                              QMessageBox::No);
            }

          if (choice == QMessageBox::NoToAll)
            {return retVal;}
          else if (choice == QMessageBox::Yes)
            {retVal = removeRow((int) delRow);}
          else if (choice == QMessageBox::YesToAll)
            {
              askEveryItem = false;
              retVal = removeRow((int) delRow);
            }
        }
    }

  return true;
}
