// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPlotDM.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/01/11 15:30:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QString>
#include <QList>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "plot/CPlotSpecification.h"
#include "plot/COutputDefinitionVector.h"

#include "CQPlotDM.h"
#include "qtUtilities.h"

CQPlotDM::CQPlotDM(QObject *parent)
    : CQBaseDataModel(parent)

{
}

int CQPlotDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList()->size() + 1;
}
int CQPlotDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_PLOTS;
}

Qt::ItemFlags CQPlotDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_PLOTS || index.column() == COL_ACTIVE_PLOTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQPlotDM::data(const QModelIndex &index, int role) const
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
              case COL_NAME_PLOTS:
                return QVariant(QString("No Name"));
              case COL_ACTIVE_PLOTS:
                return QVariant(true);
              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          const CPlotSpecification *pPS = dynamic_cast<const CPlotSpecification*>((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList()->operator[](index.row()));

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_PLOTS:
                return QVariant(QString(FROM_UTF8(pPS->getObjectName())));

              case COL_CURVES_PLOTS:
                return QVariant((unsigned int)pPS->getItems().size());

              case COL_ACTIVE_PLOTS:
                return QVariant(pPS->isActive());
            }
        }
    }

  return QVariant();
}

QVariant CQPlotDM::headerData(int section, Qt::Orientation orientation,
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
          case COL_NAME_PLOTS:
            return QVariant(QString("Name"));
          case COL_CURVES_PLOTS:
            return QVariant(QString("Curves"));
          case COL_ACTIVE_PLOTS:
            return QVariant(QString("Active"));
          default:
            return QVariant();
        }
    }
  else
    return QString("%1").arg(section + 1);
}

bool CQPlotDM::setData(const QModelIndex &index, const QVariant &value,
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

      CPlotSpecification *pPS = (CPlotSpecification*)(*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList()->operator[](index.row());

      if (index.column() == COL_NAME_PLOTS)
        pPS->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_ACTIVE_PLOTS)
        pPS->setActive(value.toBool());

      if (defaultRow && this->index(index.row(), COL_NAME_PLOTS).data().toString() == "No Name")
        pPS->setObjectName(TO_UTF8(createNewName("Plot", COL_NAME_PLOTS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::PLOT, ListViews::CHANGE, "");
    }

  return true;
}

bool CQPlotDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList()->createPlotSpec(TO_UTF8(createNewName("Plot", COL_NAME_PLOTS)), CPlotItem::plot2d);
    }

  endInsertRows();
  emit notifyGUI(ListViews::PLOT, ListViews::ADD, "");

  return true;
}

bool CQPlotDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      (*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList()->CCopasiVector< CPlotSpecification >::remove(position);
    }

  endRemoveRows();
  emit notifyGUI(ListViews::PLOT, ListViews::DELETE, "");

  return true;
}

bool CQPlotDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (!pDataModel->getModel())
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CPlotSpecification *> pPSs;
  QModelIndexList::const_iterator i;
  CPlotSpecification * pPS = NULL;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pDataModel->getPlotDefinitionList()->operator[]((*i).row()))
        {
          pPS = pDataModel->getPlotDefinitionList()->operator[]((*i).row());
          pPSs.append(pPS);
        }
    }

  QList <CPlotSpecification *>::const_iterator j;

  for (j = pPSs.begin(); j != pPSs.end(); ++j)
    {
      pPS = *j;

      unsigned C_INT32 delRow =
        pDataModel->getPlotDefinitionList()->CCopasiVector< CPlotSpecification >::getIndex(pPS);
      removeRow(delRow);
    }

  return true;
}
