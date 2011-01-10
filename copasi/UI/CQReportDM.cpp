// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDM.cpp,v $
//   $Revision: 1.3.4.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/10 13:36:41 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QString>
#include <QList>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"

#include "CQMessageBox.h"
#include "CQReportDM.h"
#include "qtUtilities.h"

CQReportDM::CQReportDM(QObject *parent)
    : CQBaseDataModel(parent)

{
}

int CQReportDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->size() + 1;
}
int CQReportDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_REPORTS;
}

Qt::ItemFlags CQReportDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_REPORTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQReportDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (index.column() > 0 && role == Qt::ForegroundRole && !(flags(index) & Qt::ItemIsEditable))
    return QColor(Qt::darkGray);

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      if (isDefaultRow(index))
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(QString(""));
              case COL_NAME_REPORTS:
                return QVariant(QString("New Report"));
              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CReportDefinition *pRepDef = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->operator[](index.row());

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_REPORTS:
                return QVariant(QString(FROM_UTF8(pRepDef->getObjectName())));
            }
        }
    }

  return QVariant();
}

QVariant CQReportDM::headerData(int section, Qt::Orientation orientation,
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
          case COL_NAME_REPORTS:
            return QVariant(QString("Name"));
          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQReportDM::setData(const QModelIndex &index, const QVariant &value,
                         int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.data() != value)
            insertRow();
          else
            return false;
        }

      CReportDefinition *pRepDef = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->operator[](index.row());

      if (index.column() == COL_NAME_REPORTS)
        pRepDef->setObjectName(TO_UTF8(value.toString()));

      if (defaultRow && this->index(index.row(), COL_NAME_REPORTS).data().toString() == "report")
        pRepDef->setObjectName(TO_UTF8(createNewName("report", COL_NAME_REPORTS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::REPORT, ListViews::CHANGE, pRepDef->getKey());
    }

  return true;
}

bool CQReportDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CReportDefinition *pRepDef =
        (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->createReportDefinition(TO_UTF8(createNewName("report", COL_NAME_REPORTS)), "");
      emit notifyGUI(ListViews::REPORT, ListViews::ADD, pRepDef->getKey());
    }

  endInsertRows();

  return true;
}

bool CQReportDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];

  if (pDataModel == NULL)
    return false;

  CCopasiVector< CReportDefinition > * pReportList = pDataModel->getReportDefinitionList();

  if (pReportList == NULL)
    return false;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CReportDefinition * pReport = (*pReportList)[position];

      if (pReport == NULL)
        continue;

      std::set< const CCopasiObject * > Tasks;
      std::set< const CCopasiObject * > DeletedObjects;
      DeletedObjects.insert(pReport);

      if (pDataModel->appendDependentTasks(DeletedObjects, Tasks))
        {
          std::set< const CCopasiObject * >::iterator it = Tasks.begin();
          std::set< const CCopasiObject * >::iterator end = Tasks.end();

          for (; it != end; ++it)
            {
              const CCopasiTask * pTask = static_cast< const CCopasiTask *>(*it);
              const_cast< CCopasiTask * >(pTask)->getReport().setReportDefinition(NULL);
            }
        }

      std::string deletedKey = pReport->getKey();
      pReportList->remove(pReport);
      emit notifyGUI(ListViews::REPORT, ListViews::DELETE, deletedKey);
    }

  endRemoveRows();

  return true;
}

bool CQReportDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  CCopasiVector< CReportDefinition > * pReportList = pDataModel->getReportDefinitionList();

  if (pReportList == NULL)
    return false;

  QList< CReportDefinition * > Reports;

  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && (*pReportList)[(*i).row()])
        Reports.append((*pReportList)[(*i).row()]);
    }

  QList< CReportDefinition * >::const_iterator j;

  for (j = Reports.begin(); j != Reports.end(); ++j)
    {
      CReportDefinition * pReport = *j;

      unsigned C_INT32 delRow = pReportList->getIndex(pReport);

      if (delRow != C_INVALID_INDEX)
        {
          std::set< const CCopasiObject * > DeletedObjects;
          DeletedObjects.insert(pReport);

          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "report",
                                        FROM_UTF8(pReport->getObjectName()),
                                        DeletedObjects);

          if (choice == QMessageBox::Ok)
            {
              removeRow(delRow);
            }
        }
    }

  return true;
}
