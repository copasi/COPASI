// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "report/CKeyFactory.h"
#include "function/CExpression.h"
#include "model/CModel.h"

#include "CQMessageBox.h"
#include "CQEventDM.h"
#include "qtUtilities.h"

#include "undoFramework/InsertEventRowsCommand.h"
#include "undoFramework/RemoveEventRowsCommand.h"
#include "undoFramework/RemoveAllEventRowsCommand.h"
#include "undoFramework/EventDataChangeCommand.h"
#include "undoFramework/UndoEventData.h"
#include "undoFramework/UndoEventAssignmentData.h"

CQEventDM::CQEventDM(QObject *parent, CDataModel * pDataModel)
  : CQBaseDataModel(parent, pDataModel)

{
}

int CQEventDM::rowCount(const QModelIndex&) const
{
  return mpDataModel->getModel()->getEvents().size() + 1;
}
int CQEventDM::columnCount(const QModelIndex&) const
{
  return TOTAL_COLS_EVENTS;
}

Qt::ItemFlags CQEventDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  if (index.column() == COL_NAME_EVENTS)
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
  else
    return QAbstractItemModel::flags(index);
}

QVariant CQEventDM::data(const QModelIndex &index, int role) const
{
  const CExpression * pExpression = NULL;

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

              default:
                return QVariant(QString(""));
            }
        }
      else
        {
          CEvent *pEvent = &mpDataModel->getModel()->getEvents()[index.row()];
          QString assignmentTarget = "";
          QString assignmentExpression = "";

          if (index.column() == COL_ASSIGNTARGET_EVENTS || index.column() == COL_ASSIGNEXPRESSION_EVENTS)
            {
              CDataVectorN< CEventAssignment >::const_iterator it = pEvent->getAssignments().begin();
              CDataVectorN< CEventAssignment >::const_iterator begin = pEvent->getAssignments().begin();
              CDataVectorN< CEventAssignment >::const_iterator end = pEvent->getAssignments().end();

              for (; it != end; ++it)
                {
                  const CModelEntity * pEntity =
                    dynamic_cast< CModelEntity * >(CRootContainer::getKeyFactory()->get(it->getTargetKey()));

                  if (pEntity != NULL)
                    {
                      if (it != begin)
                        {
                          assignmentTarget += "\n";
                          assignmentExpression += "\n";
                        }

                      assignmentTarget += FROM_UTF8(pEntity->getObjectDisplayName());
                      pExpression = it->getExpressionPtr();

                      if (pExpression != NULL)
                        assignmentExpression += pExpression->getDisplayString().c_str();
                      else
                        assignmentExpression += FROM_UTF8(it->getExpression());
                    }
                }
            }

          switch (index.column())
            {
              case COL_ROW_NUMBER:
                return QVariant(index.row() + 1);

              case COL_NAME_EVENTS:
                return QVariant(FROM_UTF8(pEvent->getObjectName()));

              case COL_TRIGGER_EVENTS:
                pExpression = pEvent->getTriggerExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(FROM_UTF8(pExpression->getDisplayString()));
                else
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
                pExpression = pEvent->getDelayExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(FROM_UTF8(pExpression->getDisplayString()));
                else
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
  if (index.data() == value)
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow)
    {
      mpUndoStack->push(new InsertEventRowsCommand(rowCount(), 1, this, index, value));
    }
  else if (role == Qt::EditRole)
    {
      mpUndoStack->push(new EventDataChangeCommand(index, value, this));
    }

  return true;
}

bool CQEventDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  mpUndoStack->push(new InsertEventRowsCommand(position, rows, this));

  return true;
}

bool CQEventDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, position + rows - 1);

  CModel * pModel = mpDataModel->getModel();

  std::vector< std::string > DeletedKeys;
  DeletedKeys.resize(rows);

  std::vector< std::string >::iterator itDeletedKey;
  std::vector< std::string >::iterator endDeletedKey = DeletedKeys.end();

  CDataVector< CEvent >::const_iterator itRow = pModel->getEvents().begin() + position;

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey, ++itRow)
    {
      *itDeletedKey = itRow->getKey();
    }

  for (itDeletedKey = DeletedKeys.begin(); itDeletedKey != endDeletedKey; ++itDeletedKey)
    {
      mpDataModel->getModel()->removeEvent(*itDeletedKey);
      emit notifyGUI(ListViews::EVENT, ListViews::DELETE, *itDeletedKey);
    }

  endRemoveRows();

  return true;
}

bool CQEventDM::removeRows(QModelIndexList rows, const QModelIndex& index)
{
  removeEventRows(rows, index);
  return true;
}

bool CQEventDM::eventDataChange(const QModelIndex &index, const QVariant &value)
{
  if (!index.isValid())
    return false;

  bool defaultRow = isDefaultRow(index);

  if (defaultRow)
    {
      if (index.data() != value)
        insertRow(rowCount(), index);
      else
        return false;
    }

  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  if ((int)pModel->getEvents().size() <= index.row())
    return false;

  switchToWidget(CCopasiUndoCommand::EVENTS);

  CEvent *pEvent = &pModel->getEvents()[index.row()];

  if (index.column() == COL_NAME_EVENTS)
    pEvent->setObjectName(TO_UTF8(value.toString()));

  if (defaultRow && this->index(index.row(), COL_NAME_EVENTS).data().toString() == "event")
    pEvent->setObjectName(TO_UTF8(createNewName("event", COL_NAME_EVENTS)));

  emit dataChanged(index, index);
  emit notifyGUI(ListViews::EVENT, ListViews::CHANGE, pEvent->getKey());

  return true;
}

void CQEventDM::insertNewEventRow(int position, int rows, const QModelIndex& index, const QVariant& value)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(index.isValid() && index.column() == COL_NAME_EVENTS ? value.toString() : "event", COL_NAME_EVENTS);
      CEvent *pEvent = pModel->createEvent(TO_UTF8(name));
      emit notifyGUI(ListViews::EVENT, ListViews::ADD, pEvent->getKey());
    }

  endInsertRows();
}

void CQEventDM::deleteEventRow(UndoEventData *pEventData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  size_t index = pModel->getEvents().getIndex(pEventData->getName());

  if (index == C_INVALID_INDEX)
    return;

  switchToWidget(CCopasiUndoCommand::EVENTS);

  removeRow((int) index);
}

void CQEventDM::addEventRow(UndoEventData *pEventData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  switchToWidget(CCopasiUndoCommand::EVENTS);

  beginInsertRows(QModelIndex(), 1, 1);

  CDataObject *pEvent = pEventData->restoreObjectIn(pModel);

  if (pEvent == NULL) return;

  std::string key = pEvent->getKey();
  pEventData->setKey(key);

  emit notifyGUI(ListViews::EVENT, ListViews::ADD, key);
  endInsertRows();
}

bool CQEventDM::removeEventRows(QModelIndexList rows, const QModelIndex&)
{
  if (rows.isEmpty())
    return false;

  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  switchToWidget(CCopasiUndoCommand::EVENTS);

  //Build the list of pointers to items to be deleted
  //before actually deleting any item.
  QList <CEvent *> pEvents;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (!isDefaultRow(*i) && &pModel->getEvents()[i->row()])
        pEvents.append(&pModel->getEvents()[i->row()]);
    }

  QList <CEvent *>::const_iterator j;

  QModelIndexList lst;

  for (j = pEvents.begin(); j != pEvents.end(); ++j)
    {
      CEvent * pEvent = *j;

      size_t delRow =
        pModel->getEvents().CDataVector< CEvent >::getIndex(pEvent);

      if (delRow == C_INVALID_INDEX)
        continue;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(NULL, "event",
                                    FROM_UTF8(pEvent->getObjectName()),
                                    pEvent);

      if (choice == QMessageBox::Ok)
        {
          //removeRow((int) delRow);
          lst.append(index((int)delRow, 0));
        }
    }

  if (!lst.empty())
    {
      mpUndoStack->push(new RemoveEventRowsCommand(lst, this));
    }

  return true;
}

bool CQEventDM::insertEventRows(QList <UndoEventData *>& pData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  switchToWidget(CCopasiUndoCommand::EVENTS);

  //reinsert all the events
  QList <UndoEventData *>::const_iterator i;

  for (i = pData.begin(); i != pData.end(); ++i)
    {
      beginInsertRows(QModelIndex(), 1, 1);
      UndoEventData * data = *i;
      CDataObject * pEvent = data->restoreObjectIn(pModel);

      if (pEvent == NULL) continue;

      emit notifyGUI(ListViews::EVENT, ListViews::ADD, pEvent->getKey());
      endInsertRows();
    }

  return true;
}

void CQEventDM::deleteEventRows(QList <UndoEventData *>& pData)
{
  assert(mpDataModel != NULL);
  CModel * pModel = mpDataModel->getModel();
  assert(pModel != NULL);

  switchToWidget(CCopasiUndoCommand::EVENTS);

  QList <UndoEventData *>::const_iterator j;

  for (j = pData.begin(); j != pData.end(); ++j)
    {
      UndoEventData * data = *j;
      size_t index = pModel->getEvents().getIndex(data->getName());

      if (index == C_INVALID_INDEX) continue;

      removeRow((int) index);
    }
}

bool CQEventDM::clear()
{
  mpUndoStack->push(new RemoveAllEventRowsCommand(this, QModelIndex()));
  return true;
}

bool CQEventDM::removeAllEventRows()
{
  return removeRows(0, rowCount() - 1);
}
