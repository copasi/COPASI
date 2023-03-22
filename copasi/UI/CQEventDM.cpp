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

#include <QtCore/QString>

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/function/CExpression.h"
#include "copasi/model/CModel.h"

#include "CQMessageBox.h"
#include "CQEventDM.h"
#include "qtUtilities.h"

CQEventDM::CQEventDM(QObject *parent, CDataModel * pDataModel)
  : CQBaseDataModel(parent, pDataModel)
  , mpEvents(NULL)
{
}

size_t CQEventDM::size() const
{
  if (mpDataModel != NULL)
    return mpDataModel->getModel()->getEvents().size();

  return 0;
}

int CQEventDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched + 1;
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
      if (isDefaultRow(index) || index.row() >= (int) mpDataModel->getModel()->getEvents().size())
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
          const CEvent & Event = mpDataModel->getModel()->getEvents()[index.row()];
          QString assignmentTarget = "";
          QString assignmentExpression = "";

          if (index.column() == COL_ASSIGNTARGET_EVENTS || index.column() == COL_ASSIGNEXPRESSION_EVENTS)
            {
              CDataVectorN< CEventAssignment >::const_iterator it = Event.getAssignments().begin();
              CDataVectorN< CEventAssignment >::const_iterator begin = Event.getAssignments().begin();
              CDataVectorN< CEventAssignment >::const_iterator end = Event.getAssignments().end();

              for (; it != end; ++it)
                {
                  const CModelEntity * pEntity =
                    dynamic_cast< const CModelEntity * >(CObjectInterface::DataObject(mpDataModel->getObject(it->getTargetCN())));

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
                return QVariant(FROM_UTF8(Event.getObjectName()));

              case COL_TRIGGER_EVENTS:
                pExpression = Event.getTriggerExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(FROM_UTF8(pExpression->getDisplayString()));
                else
                  return QVariant(FROM_UTF8(Event.getTriggerExpression()));

              case COL_DELAYED_EVENTS:
              {
                if (Event.getDelayExpression() == "")
                  return QVariant(QString("No"));
                else if (Event.getDelayAssignment())
                  return QVariant(QString("Assignment"));
                else
                  return QVariant(QString("Calculation"));
              }

              case COL_DELAY_EXPRESSION_EVENTS:
                pExpression = Event.getDelayExpressionPtr();

                if (pExpression != NULL)
                  return QVariant(FROM_UTF8(pExpression->getDisplayString()));
                else
                  return QVariant(FROM_UTF8(Event.getDelayExpression()));

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
      insertNewRows(rowCount(), 1, index.column(), value);
    }
  else if (role == Qt::EditRole)
    {
      CEvent & Event = mpEvents->operator [](index.row());
      CData OldData = Event.toData();

      if (index.column() == COL_NAME_EVENTS)
        Event.setObjectName(TO_UTF8(value.toString()));

      CUndoData UndoData;
      Event.createUndoData(UndoData, CUndoData::Type::CHANGE, OldData);

      if (!UndoData.empty())
        {
          ListViews::addUndoMetaData(this, UndoData);
          emit signalNotifyChanges(mpDataModel->recordData(UndoData));
        }
    }

  return true;
}

// virtual
void CQEventDM::resetCacheProtected()
{
  mpEvents = dynamic_cast< CDataVectorN < CEvent > * >(&mpDataModel->getModel()->getEvents());
  assert(mpEvents != NULL);
}

bool CQEventDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  insertNewRows(position, rows);

  return true;
}

bool CQEventDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0)
    return true;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);

  std::vector< CCommonName > ToBeDeleted;
  ToBeDeleted.resize(rows);

  std::vector< CCommonName >::iterator it = ToBeDeleted.begin();
  std::vector< CCommonName >::iterator end = ToBeDeleted.end();

  CDataVector< CEvent >::const_iterator itRow = mpEvents->begin() + position;

  for (; it != end; ++it, ++itRow)
    {
      *it = itRow->getCN();
    }

  for (it = ToBeDeleted.begin(); it != end; ++it)
    {
      if (mFetched > 0)
        --mFetched;

      const CEvent * pObj = dynamic_cast< const CEvent * >(mpDataModel->getObject(*it));

      if (!pObj)
        continue;

      CUndoData UndoData;
      pObj->createUndoData(UndoData, CUndoData::Type::REMOVE);
      ListViews::addUndoMetaData(this, UndoData);

      emit signalNotifyChanges(mpDataModel->applyData(UndoData));
    }

  endRemoveRows();

  return true;
}

bool CQEventDM::removeRows(QModelIndexList rows, const QModelIndex& index)
{
  if (rows.isEmpty())
    return false;

  //Build the list of pointers to items to be deleted
  //before actually deleting any item.
  QList < CEvent * > Events;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    if (i->isValid()
        && !isDefaultRow(*i))
      {
        Events.append(&mpEvents->operator[](i->row()));
      }

  QList <CEvent *>::const_iterator j;

  for (j = Events.begin(); j != Events.end(); ++j)
    {
      CEvent * pEvent = *j;

      QMessageBox::StandardButton choice =
        CQMessageBox::confirmDelete(ListViews::ancestor(this), "event",
                                    FROM_UTF8(pEvent->getObjectName()),
                                    pEvent);

      if (choice == QMessageBox::Ok)
        {
          removeRows(mpEvents->getIndex(pEvent->getObjectName()), 1);
        }
    }

  return true;
}

void CQEventDM::insertNewRows(int position, int rows, int column, const QVariant & value)
{
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      QString name = createNewName(column == COL_NAME_EVENTS ? value.toString() : "event", COL_NAME_EVENTS);

      CEvent * pEvent = mpDataModel->getModel()->createEvent(TO_UTF8(name));

      if (pEvent == NULL)
        continue;

      ++mFetched;

      CUndoData UndoData(CUndoData::Type::INSERT, pEvent);
      ListViews::addUndoMetaData(this, UndoData);
      emit signalNotifyChanges(mpDataModel->recordData(UndoData));
    }

  endInsertRows();
}
