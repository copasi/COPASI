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

#include "CQEFMNetReactionDM.h"
#include "qtUtilities.h"

#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/elementaryFluxModes/CEFMMethod.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiProblem.h"

CQEFMNetReactionDM::CQEFMNetReactionDM(QObject *parent):
  CQBaseDataModel(parent, NULL),
  mpTask(NULL),
  mBeginModes()
{}

size_t CQEFMNetReactionDM::size() const
{
  if (mpTask != NULL)
    return mpTask->getFluxModes().size();

  return 0;
}

int CQEFMNetReactionDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched;
}

int CQEFMNetReactionDM::columnCount(const QModelIndex & C_UNUSED(parent)) const
{
  return NetReactionDM_COLUMNS;
}

Qt::ItemFlags CQEFMNetReactionDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

QVariant CQEFMNetReactionDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      std::vector< CFluxMode >::const_iterator itMode = mBeginModes + index.row();

      switch (index.column())
        {
          case COL_ROW_NUMBER:
            return QVariant(index.row() + 1);
            break;

          case COL_REACTION:
            return QVariant(QString(FROM_UTF8(mpTask->getNetReaction(*itMode))));
            break;

          case COL_MODIFIER:
            return QVariant(QString(FROM_UTF8(mpTask->getInternalSpecies(*itMode))));
            break;
        }
    }

  return QVariant();
}

QVariant CQEFMNetReactionDM::headerData(int section, Qt::Orientation orientation,
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

          case COL_REACTION:
            return QVariant(QString("Net Reaction"));
            break;

          case COL_MODIFIER:
            return QVariant(QString("Internal Species"));
            break;
        }
    }

  return QString("%1").arg(section + 1);
}

void CQEFMNetReactionDM::setTask(const CEFMTask * pTask)
{
  beginResetModel();

  mpTask = pTask;

  if (mpTask != NULL)
    mBeginModes = mpTask->getFluxModes().begin();

  mFetched = std::min(mFetchLimit, size());

  endResetModel();
}

bool CQEFMNetReactionDM::setData(const QModelIndex & /* index */, const QVariant & /* value */, int /* role */)
{
  return false;
}

// virtual
void CQEFMNetReactionDM::resetCacheProtected()
{}

// virtual
bool CQEFMNetReactionDM::insertRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQEFMNetReactionDM::removeRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQEFMNetReactionDM::isDefaultRow(const QModelIndex& /* i */) const
{
  return false;
}
