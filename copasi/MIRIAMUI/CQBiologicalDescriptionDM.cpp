// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQBiologicalDescriptionDM.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/02 18:56:24 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQBiologicalDescriptionDM.h"

#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "MIRIAM/CModelMIRIAMInfo.h"

CQBiologicalDescriptionDM::CQBiologicalDescriptionDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent)
    : CQBaseDataModel(parent)

{
  mpMIRIAMInfo = MIRIAMInfo;
}

int CQBiologicalDescriptionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (int) mpMIRIAMInfo->getBiologicalDescriptions().size() + 1;
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
      if (isDefaultRow(index))
        {
          if (index.column() == COL_RELATIONSHIP || index.column() == COL_RESOURCE_BD)
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
              case COL_RELATIONSHIP:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getPredicate())));
              case COL_RESOURCE_BD:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getResource())));
              case COL_ID_BD:
                return QVariant(QString(FROM_UTF8(mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->getId())));
            }
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
          case COL_ROW_NUMBER:
            return QVariant(QString("#"));
          case COL_RELATIONSHIP:
            return QVariant(QString("Relationship"));
          case COL_RESOURCE_BD:
            return QVariant(QString("                 Resource                 "));
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
      if (isDefaultRow(index))
        {
          if (index.data() != value)
            insertRow();
          else
            return false;
        }

      switch (index.column())
        {
          case COL_RELATIONSHIP:
            mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setPredicate(TO_UTF8(value.toString()));
            break;
          case COL_RESOURCE_BD:
            mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setResource(TO_UTF8(value.toString()));
            break;
          case COL_ID_BD:
            mpMIRIAMInfo->getBiologicalDescriptions()[index.row()]->setId(TO_UTF8(value.toString()));
            break;
        }

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::MIRIAM, ListViews::CHANGE, "");
      return true;
    }

  return false;
}

bool CQBiologicalDescriptionDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->createBiologicalDescription();
    }

  endInsertRows();
  emit notifyGUI(ListViews::MIRIAM, ListViews::ADD, "");
  return true;
}

bool CQBiologicalDescriptionDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      mpMIRIAMInfo->removeBiologicalDescription(position);
    }

  endRemoveRows();

  emit notifyGUI(ListViews::MIRIAM, ListViews::DELETE, "");
  return true;
}

bool CQBiologicalDescriptionDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CBiologicalDescription *> pBiologicalDescriptions;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && mpMIRIAMInfo->getBiologicalDescriptions()[(*i).row()])
        pBiologicalDescriptions.append(mpMIRIAMInfo->getBiologicalDescriptions()[(*i).row()]);
    }

  bool retVal = false, askEveryItem = true;
  QMessageBox::StandardButton choice = QMessageBox::NoToAll;
  QList <CBiologicalDescription *>::const_iterator j;

  for (j = pBiologicalDescriptions.begin(); j != pBiologicalDescriptions.end(); ++j)
    {
      CBiologicalDescription * pBiologicalDescription = *j;

      size_t delRow =
        mpMIRIAMInfo->getBiologicalDescriptions().CCopasiVector< CBiologicalDescription >::getIndex(pBiologicalDescription);

      if (delRow != C_INVALID_INDEX)
        {
          if (askEveryItem)
            {

              QString resource = data(this->index((int) delRow, COL_RESOURCE_BD), Qt::DisplayRole).toString();
              QString Id = data(this->index((int) delRow, COL_ID_BD), Qt::DisplayRole).toString();

              QString msg = "Do you want to delete Description '";

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

              choice = CQMessageBox::question(NULL, tr("Confirm Delete"), msg,
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
