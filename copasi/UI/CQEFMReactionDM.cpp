// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "CQEFMReactionDM.h"
#include "qtUtilities.h"

#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/elementaryFluxModes/CEFMProblem.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"
#include "copasi/model/CReaction.h"

CQEFMReactionDM::CQEFMReactionDM(QObject *parent):
  CQBaseDataModel(parent, NULL),
  mpTask(NULL),
  mBeginModes(),
  mBeginReactions(),
  mReactionsSize(0)
{}

size_t CQEFMReactionDM::size() const
{
  if (mpTask != NULL)
    return mpTask->getFluxModes().size();

  return 0;
}

int CQEFMReactionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched;
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

  if (section < 0)
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
  beginResetModel();

  mpTask = pTask;

  if (mpTask != NULL)
    {
      mBeginModes = mpTask->getFluxModes().begin();

      mBeginReactions = static_cast< const CEFMProblem * >(mpTask->getProblem())->getReorderedReactions().begin();
      mReactionsSize = static_cast< const CEFMProblem * >(mpTask->getProblem())->getReorderedReactions().size();
    }
  else
    {
      mReactionsSize = 0;
    }

  mFetched = std::min(mFetchLimit, size());

  endResetModel();
}

bool CQEFMReactionDM::setData(const QModelIndex & /* index */, const QVariant & /* value */, int /* role */)
{
  return false;
}

// virtual
void CQEFMReactionDM::resetCacheProtected()
{}

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
