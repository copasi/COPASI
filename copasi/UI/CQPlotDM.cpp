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

#include <QtCore/QString>
#include <QtCore/QList>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/plot/CPlotSpecification.h"
#include "copasi/plot/COutputDefinitionVector.h"

#include "CQPlotDM.h"
#include "qtUtilities.h"

CQPlotDM::CQPlotDM(QObject *parent, CDataModel * pDataModel)
  : CQBaseDataModel(parent, pDataModel)
  , mNewName("plot")
{
}

size_t CQPlotDM::size() const
{
  if (mpDataModel != NULL)
    return mpDataModel->getPlotDefinitionList()->size();

  return 0;
}

int CQPlotDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
}

int CQPlotDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_PLOTS;
}

Qt::ItemFlags CQPlotDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_PLOTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else if (index.column() == COL_ACTIVE_PLOTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
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
      if (isDefaultRow(index) || index.row() >= (int) mpDataModel->getPlotDefinitionList()->size())
        {
          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(QString(""));

              case COL_NAME_PLOTS:
                return QVariant(QString("New Plot"));

              case COL_ACTIVE_PLOTS:

                if (role == Qt::DisplayRole)
                  return QVariant();
                else
                  return QVariant(true);

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          const CPlotSpecification *pPS = dynamic_cast<const CPlotSpecification *>(&mpDataModel->getPlotDefinitionList()->operator[](index.row()));

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_PLOTS:
                return QVariant(QString(FROM_UTF8(pPS->getObjectName())));

              case COL_CURVES_PLOTS:
                return QVariant((unsigned int)pPS->getItems().size());

              case COL_ACTIVE_PLOTS:

                if (role == Qt::DisplayRole)
                  return QVariant();
                else
                  return QVariant(pPS->isActive());
            }
        }
    }
  else if (role == Qt::CheckStateRole && index.column() == COL_ACTIVE_PLOTS)
    return index.data(Qt::EditRole).toBool() ? QVariant(Qt::Checked) : QVariant(Qt::Unchecked);

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
            return QVariant(QString("Nr. of Curves"));

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
      bool changed = false;
      bool defaultRow = isDefaultRow(index);

      if (defaultRow)
        {
          if (index.data() != value)
            {
              mNewName = (index.column() == COL_NAME_PLOTS) ? value.toString() : "plot";

              insertRow(rowCount(), index);
              changed = true;
            }
          else
            return false;
        }

      CPlotSpecification *pPS = &mpDataModel->getPlotDefinitionList()->operator[](index.row());

      switch (index.column())
        {
          case COL_NAME_PLOTS:

            if (pPS->getObjectName() != TO_UTF8(value.toString()))
              {
                pPS->setObjectName(TO_UTF8(value.toString()));
                changed = true;
              }

            break;

          case COL_ACTIVE_PLOTS:

            if (pPS->isActive() != value.toBool())
              {
                pPS->setActive(value.toBool());
                changed = true;
              }

            break;

          default:
            break;
        }

      if (changed)
        {
          emit dataChanged(index, index);
          emit notifyGUI(ListViews::ObjectType::PLOT, ListViews::CHANGE, pPS->CCopasiParameter::getCN());
        }
    }
  else if (role == Qt::CheckStateRole && index.column() == COL_ACTIVE_PLOTS)
    {
      QVariant data = value.toInt() == Qt::Checked ? QVariant(true) : QVariant(false);
      return setData(index, data, Qt::EditRole);
    }

  return true;
}

// virtual
void CQPlotDM::resetCacheProtected()
{}

bool CQPlotDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  beginInsertRows(parent, position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString Name = this->createNewName(mNewName, COL_NAME_PLOTS);

      CPlotSpecification *pPS = mpDataModel->getPlotDefinitionList()->createPlotSpec(TO_UTF8(Name), CPlotItem::plot2d);

      if (pPS == NULL) continue;

      ++mFetched;

      emit notifyGUI(ListViews::ObjectType::PLOT, ListViews::ADD, pPS->CCopasiParameter::getCN());
    }

  endInsertRows();

  mNewName = "plot";

  return true;
}

bool CQPlotDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  for (int row = 0; row < rows; ++row)
    {
      CPlotSpecification* pPS =
        &mpDataModel->getPlotDefinitionList()->operator[](position);
      std::string deletedKey = pPS->CCopasiParameter::getCN();

      if (mFetched > 0)
        --mFetched;

      mpDataModel->getPlotDefinitionList()->CDataVector< CPlotSpecification >::remove(position);
      emit notifyGUI(ListViews::ObjectType::PLOT, ListViews::DELETE, deletedKey);
    }

  endRemoveRows();

  return true;
}

bool CQPlotDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(mpDataModel != NULL);

  if (!mpDataModel->getModel())
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CPlotSpecification *> pPSs;
  QModelIndexList::const_iterator i;
  CPlotSpecification * pPS = NULL;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (i->isValid() && !isDefaultRow(*i) && &mpDataModel->getPlotDefinitionList()->operator[](i->row()))
        {
          pPS = &mpDataModel->getPlotDefinitionList()->operator[](i->row());
          pPSs.append(pPS);
        }
    }

  QList <CPlotSpecification *>::const_iterator j;

  for (j = pPSs.begin(); j != pPSs.end(); ++j)
    {
      pPS = *j;

      size_t delRow =
        mpDataModel->getPlotDefinitionList()->CDataVector< CPlotSpecification >::getIndex(pPS);
      removeRow((int) delRow);
    }

  return true;
}
