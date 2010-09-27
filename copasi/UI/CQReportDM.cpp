// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDM.cpp,v $
//   $Revision: 1.3.4.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/09/27 13:44:56 $
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
                return QVariant(index.row() + 1);
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

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      std::string deletedKey = (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->operator[](position)->getKey();
      (*CCopasiRootContainer::getDatamodelList())[0]->getReportDefinitionList()->CCopasiVector< CReportDefinition >::remove(position);
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

  if (!pDataModel->getModel())
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CReportDefinition *> pRepDefs;
  QModelIndexList::const_iterator i;
  std::set< std::string > TaskKeys;
  std::set< std::string >::const_iterator it;
  std::set< std::string >::const_iterator end;
  CReportDefinition * pRepDef = NULL;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pDataModel->getReportDefinitionList()->operator[]((*i).row()))
        {
          pRepDef = pDataModel->getReportDefinitionList()->operator[]((*i).row());
          pRepDefs.append(pRepDef);

          //check where the reports are used...
          std::set< std::string > Keys =
            pDataModel->listTaskDependentOnReport(pRepDef->getKey());

          for (it = Keys.begin(), end = Keys.end(); it != end; ++it)
            TaskKeys.insert(*it);
        }
    }

  if (TaskKeys.size() > 0)
    {
      std::set< std::string >::const_iterator it = TaskKeys.begin();
      std::set< std::string >::const_iterator end = TaskKeys.end();

      CCopasiTask * pTask;
      QString msg = "The following tasks are effected:\n";

      for (it = TaskKeys.begin(), end = TaskKeys.end(); it != end; ++it)
        if ((pTask = dynamic_cast< CCopasiTask * >(CCopasiRootContainer::getKeyFactory()->get(*it))))
          msg += FROM_UTF8(pTask->getObjectName()) + ", ";

      msg = msg.remove(msg.length() - 2, 2);

      if (CQMessageBox::question(NULL,
                                 "CONFIRM DELETE",
                                 msg,
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Cancel) == QMessageBox::Cancel)
        return false;

      for (it = TaskKeys.begin(); it != end; ++it)
        if ((pTask = dynamic_cast< CCopasiTask * >(CCopasiRootContainer::getKeyFactory()->get(*it))))
          pTask->getReport().setReportDefinition(NULL);
    }

  QList <CReportDefinition *>::const_iterator j;

  for (j = pRepDefs.begin(); j != pRepDefs.end(); ++j)
    {
      pRepDef = *j;

      unsigned C_INT32 delRow =
        pDataModel->getReportDefinitionList()->CCopasiVector< CReportDefinition >::getIndex(pRepDef);
      removeRow(delRow);
    }

  return true;
}
