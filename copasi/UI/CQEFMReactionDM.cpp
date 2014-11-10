// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMReactionDM.h"
#include "qtUtilities.h"

#include "elementaryFluxModes/CEFMTask.h"
#include "elementaryFluxModes/CEFMProblem.h"
#include "elementaryFluxModes/CFluxMode.h"
#include "model/CReaction.h"

CQEFMReactionDM::CQEFMReactionDM(QObject *parent):
  CQBaseDataModel(parent),
  mpTask(NULL),
  mBeginModes(),
  mModesSize(0),
  mBeginReactions(),
  mReactionsSize(0)
{}

int CQEFMReactionDM::rowCount(const QModelIndex & C_UNUSED(parent)) const
{
  if (mpTask == NULL)
    return 0;

  return (int) mModesSize;
}

int CQEFMReactionDM::columnCount(const QModelIndex & C_UNUSED(parent)) const
{
  if (mpTask == NULL)
    return 0;

  return (int)(mReactionsSize + 1);  // For flux mode number
}

Qt::ItemFlags CQEFMReactionDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

QVariant CQEFMReactionDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      //std::vector< CFluxMode >::const_iterator itMode = mBeginModes + index.row();

      switch (index.column())
        {
          case COL_ROW_NUMBER:
            return QVariant(index.row() + 1);
            break;

          default:
            return QVariant((mBeginModes + index.row())->getMultiplier(index.column() - 1));
        }
    }

  return QVariant();
}

QVariant CQEFMReactionDM::headerData(int section, Qt::Orientation orientation,
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
            break;

          default:
            return QVariant(QString(FROM_UTF8((*(mBeginReactions + section - 1))->getObjectName())));
            break;
        }
    }

  //Vertical header
  return QString("%1").arg(section + 1);
}

void CQEFMReactionDM::setTask(const CEFMTask * pTask)
{
  mpTask = pTask;

  if (mpTask != NULL)
    {
      mBeginModes = mpTask->getFluxModes().begin();
      mModesSize = mpTask->getFluxModes().size();

      mBeginReactions = static_cast< const CEFMProblem * >(mpTask->getProblem())->getReorderedReactions().begin();
      mReactionsSize = static_cast< const CEFMProblem * >(mpTask->getProblem())->getReorderedReactions().size();
    }
  else
    {
      mModesSize = 0;
      mReactionsSize = 0;
    }
}

bool CQEFMReactionDM::setData(const QModelIndex & /* index */, const QVariant & /* value */, int /* role */)
{
  return false;
}

// virtual
bool CQEFMReactionDM::insertRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQEFMReactionDM::removeRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQEFMReactionDM::isDefaultRow(const QModelIndex& /* i */) const
{
  return false;
}
