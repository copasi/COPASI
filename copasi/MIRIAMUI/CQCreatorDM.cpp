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

#include "CQCreatorDM.h"
#include "copasi/UI/CQMessageBox.h"

#include "copasi/copasi.h"

#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

CQCreatorDM::CQCreatorDM(QObject *parent)
  : CQBaseDataModel(parent, NULL)
  , mpMIRIAMInfo(NULL)
{}

void CQCreatorDM::setMIRIAMInfo(CMIRIAMInfo * pMiriamInfo)
{
  beginResetModel();
  mpMIRIAMInfo = pMiriamInfo;
  mFetched = std::min(mFetchLimit, size());
  endResetModel();
}

size_t  CQCreatorDM::size() const
{
  if (mpMIRIAMInfo != NULL)
    return (int) mpMIRIAMInfo->getCreators().size();

  return 0;
}

int CQCreatorDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
}

int CQCreatorDM::columnCount(const QModelIndex&) const
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
      if (isDefaultRow(index) || index.row() >= (int) mpMIRIAMInfo->getCreators().size())
        {
          if (index.column() == COL_ROW_NUMBER)
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

              case COL_FAMILY_NAME:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()].getFamilyName())));

              case COL_GIVEN_NAME:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()].getGivenName())));

              case COL_EMAIL:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()].getEmail())));

              case COL_ORG:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getCreators()[index.row()].getORG())));
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

      CCreator & Creator = mpMIRIAMInfo->getCreators()[index.row()];
      CData OldData = Creator.toData();

      switch (index.column())
        {
          case COL_FAMILY_NAME:
            Creator.setFamilyName(TO_UTF8(value.toString()));
            break;

          case COL_GIVEN_NAME:
            Creator.setGivenName(TO_UTF8(value.toString()));
            break;

          case COL_EMAIL:
            Creator.setEmail(TO_UTF8(value.toString()));
            break;

          case COL_ORG:
            Creator.setORG(TO_UTF8(value.toString()));
            break;
        }

      CUndoData UndoData;
      Creator.createUndoData(UndoData, UndoType, OldData);

      if (!UndoData.empty())
        {
          mpMIRIAMInfo->save();
          ListViews::addUndoMetaData(this, UndoData);
          emit signalNotifyChanges(mpDataModel->recordData(UndoData));
        }

      return true;
    }

  return false;
}

bool CQCreatorDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  beginInsertRows(parent, position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CCreator * pCreator = mpMIRIAMInfo->createCreator("");

      if (pCreator == NULL)
        continue;

      ++mFetched;
    }

  endInsertRows();

  return true;
}

bool CQCreatorDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< const CCreator * > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< const CCreator * >::iterator it = ToBeDeleted.begin();
  std::vector< const CCreator * >::iterator end = ToBeDeleted.end();

  CDataVector< CCreator >::const_iterator itRow = mpMIRIAMInfo->getCreators().begin() + position;

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

void CQCreatorDM::resetCacheProtected()
{
  mpMIRIAMInfo = NULL;
}

bool CQCreatorDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CCreator *> pCreators;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (i->isValid() && !isDefaultRow(*i) && &mpMIRIAMInfo->getCreators()[i->row()])
        pCreators.append(&mpMIRIAMInfo->getCreators()[i->row()]);
    }

  bool retVal = false, askEveryItem = true;
  QMessageBox::StandardButton choice = QMessageBox::NoToAll;
  QList <CCreator *>::const_iterator j;

  for (j = pCreators.begin(); j != pCreators.end(); ++j)
    {
      CCreator * pCreator = *j;

      size_t delRow =
        mpMIRIAMInfo->getCreators().CDataVector< CCreator >::getIndex(pCreator);

      if (delRow != C_INVALID_INDEX)
        {
          if (askEveryItem)
            {
              QString givenName = data(this->index((int) delRow, COL_GIVEN_NAME), Qt::DisplayRole).toString();
              QString familyName = data(this->index((int) delRow, COL_FAMILY_NAME), Qt::DisplayRole).toString();
              QString msg = "Do you want to delete author '";

              if (!givenName.isNull())
                {
                  msg.append(givenName);
                }

              if (!familyName.isNull())
                {
                  msg.append(" ");
                  msg.append(familyName);
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

void CQCreatorDM::appendDefaultCreator()
{
  beginResetModel();

  CCreator * pCreator = mpMIRIAMInfo->addDefaultCreator(true);

  if (pCreator != NULL)
    {
      CUndoData UndoData;

      pCreator->createUndoData(UndoData, CUndoData::Type::INSERT);
      ListViews::addUndoMetaData(this, UndoData);
      emit signalNotifyChanges(mpDataModel->recordData(UndoData));

      ++mFetched;
    }

  endResetModel();
}
