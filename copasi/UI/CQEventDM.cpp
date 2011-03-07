// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventDM.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:57 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QString>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CKeyFactory.h"

#include "CQMessageBox.h"
#include "CQEventDM.h"
#include "qtUtilities.h"

CQEventDM::CQEventDM(QObject *parent)
    : CQBaseDataModel(parent)

{
}

int CQEventDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return (int)(*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents().size() + 1;
}
int CQEventDM::columnCount(const QModelIndex& C_UNUSED(parent)) const
{
  return TOTAL_COLS_EVENTS;
}

Qt::ItemFlags CQEventDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_EVENTS || index.column() == COL_ORDER_EVENTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQEventDM::data(const QModelIndex &index, int role) const
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
              case COL_NAME_EVENTS:
                return QVariant(QString("New Event"));
              case COL_ORDER_EVENTS:
              {
                if (role == Qt::DisplayRole)
                  return QVariant();
                else if (role == Qt::EditRole)
                  return QVariant(rowCount());
              }
              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CEvent *pEvent = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents()[index.row()];
          QString assignmentTarget = "";
          QString assignmentExpression = "";

          if (index.column() == COL_ASSIGNTARGET_EVENTS || index.column() == COL_ASSIGNEXPRESSION_EVENTS)
            {
              CCopasiVectorN< CEventAssignment >::const_iterator it = pEvent->getAssignments().begin();
              CCopasiVectorN< CEventAssignment >::const_iterator begin = pEvent->getAssignments().begin();
              CCopasiVectorN< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

              for (; it != end; ++it)
                {
                  const CModelEntity * pEntity =
                    dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get((*it)->getTargetKey()));

                  if (pEntity != NULL)
                    {
                      if (it != begin)
                        {
                          assignmentTarget += "\n";
                          assignmentExpression += "\n";
                        }

                      assignmentTarget += FROM_UTF8(pEntity->getObjectDisplayName());
                      assignmentExpression += FROM_UTF8((*it)->getExpression());
                    }
                }
            }

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_EVENTS:
                return QVariant(FROM_UTF8(pEvent->getObjectName()));

              case COL_ORDER_EVENTS:
                return QVariant((unsigned int)pEvent->getOrder());

              case COL_TRIGGER_EVENTS:
                return QVariant(FROM_UTF8(pEvent->getTriggerExpression()));

              case COL_DELAYED_EVENTS:
              {
                if (pEvent->getDelayExpression() == "")
                  return QVariant(QString("No"));
                else if (pEvent->getDelayAssignment())
                  return QVariant(QString("Assignment"));
                else
                  return QVariant(QString("Calculation"));
              }

              case COL_DELAY_EXPRESSION_EVENTS:
                return QVariant(FROM_UTF8(pEvent->getDelayExpression()));

              case COL_ASSIGNTARGET_EVENTS:
                return QVariant(assignmentTarget);

              case COL_ASSIGNEXPRESSION_EVENTS:
                return QVariant(assignmentExpression);
            }
        }
    }

  return QVariant();
}

QVariant CQEventDM::headerData(int section, Qt::Orientation orientation,
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
          case COL_NAME_EVENTS:
            return QVariant(QString("Name"));
          case COL_ORDER_EVENTS:
            return QVariant(QString("Order"));
          case COL_TRIGGER_EVENTS:
            return QVariant(QString("Trigger Expression"));
          case COL_DELAYED_EVENTS:
            return QVariant("Delayed");
          case COL_DELAY_EXPRESSION_EVENTS:
            return QVariant("Delay Expression");
          case COL_ASSIGNTARGET_EVENTS:
            return QVariant("Assignment Target");
          case COL_ASSIGNEXPRESSION_EVENTS:
            return QVariant("Assignment Expression");
          default:
            return QVariant();
        }
    }
  else  //Vertical header
    return QString("%1").arg(section + 1);
}

bool CQEventDM::setData(const QModelIndex &index, const QVariant &value,
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

      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CEvent *pEvent = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents()[index.row()];

      if (index.column() == COL_NAME_EVENTS)
        pEvent->setObjectName(TO_UTF8(value.toString()));
      else if (index.column() == COL_ORDER_EVENTS)
        pEvent->setOrder(value.toUInt());

      if (defaultRow && this->index(index.row(), COL_NAME_EVENTS).data().toString() == "event")
        pEvent->setObjectName(TO_UTF8(createNewName("event", COL_NAME_EVENTS)));

      emit dataChanged(index, index);
      emit notifyGUI(ListViews::EVENT, ListViews::CHANGE, pEvent->getKey());
    }

  return true;
}

bool CQEventDM::insertRows(int position, int rows, const QModelIndex&)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      CEvent *pEvent =
        (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->createEvent(TO_UTF8(createNewName("event", COL_NAME_EVENTS)));
      emit notifyGUI(ListViews::EVENT, ListViews::ADD, pEvent->getKey());
    }

  endInsertRows();

  return true;
}

bool CQEventDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      std::string deletedKey = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getEvents()[position]->getKey();
      (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->removeEvent(position);
      emit notifyGUI(ListViews::EVENT, ListViews::DELETE, deletedKey);
    }

  endRemoveRows();

  return true;
}

bool CQEventDM::removeRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return false;

//Build the list of pointers to items to be deleted
//before actually deleting any item.
  QList <CEvent *> pEvents;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && pModel->getEvents()[(*i).row()])
        pEvents.append(pModel->getEvents()[(*i).row()]);
    }

  QList <CEvent *>::const_iterator j;

  for (j = pEvents.begin(); j != pEvents.end(); ++j)
    {
      CEvent * pEvent = *j;

      size_t delRow =
        pModel->getEvents().CCopasiVector< CEvent >::getIndex(pEvent);

      if (delRow != C_INVALID_INDEX)
        {
          std::set< const CCopasiObject * > deletedObjects;
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "event",
                                        FROM_UTF8(pEvent->getObjectName()),
                                        deletedObjects);

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}
