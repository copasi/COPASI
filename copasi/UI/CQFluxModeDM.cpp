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

#include "CQFluxModeDM.h"
#include "qtUtilities.h"

#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"

CQFluxModeDM::CQFluxModeDM(QObject *parent):
  CQBaseDataModel(parent, NULL),
  mpTask(NULL),
  mBeginModes()
{}

size_t CQFluxModeDM::size() const
{
  if (mpTask != NULL)
    return mpTask->getFluxModes().size();

  return 0;
}

int CQFluxModeDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched;
}

int CQFluxModeDM::columnCount(const QModelIndex & C_UNUSED(parent)) const
{
  return FluxModeDM_COLUMNS;
}

Qt::ItemFlags CQFluxModeDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

QVariant CQFluxModeDM::data(const QModelIndex &index, int role) const
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

          case COL_REVERSIBILITY:

            if (itMode->isReversible() == true)
              {
                return QVariant(QString("Reversible"));
              }
            else
              {
                return QVariant(QString("Irreversible"));
              }

            break;

          case COL_REACTION_NAME:
            return QVariant(QString(FROM_UTF8(mpTask->getFluxModeDescription(*itMode))));
            break;

          case COL_REACTION_EQUATION:
          {
            std::string reactionEq = "";
            std::string separator = "";

            CFluxMode::const_iterator itReaction = itMode->begin();
            CFluxMode::const_iterator endReaction = itMode->end();

            for (; itReaction != endReaction; ++itReaction)
              {
                reactionEq += separator;
                reactionEq += mpTask->getReactionEquation(itReaction);
                separator = "\n";
              }

            return QVariant(QString(FROM_UTF8(reactionEq)));
          }
          break;
        }
    }

  return QVariant();
}

QVariant CQFluxModeDM::headerData(int section, Qt::Orientation orientation,
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

          case COL_REVERSIBILITY:
            return QVariant(QString("Reversibility"));
            break;

          case COL_REACTION_NAME:
            return QVariant(QString("Reaction Name"));
            break;

          case COL_REACTION_EQUATION:
            return QVariant(QString("Reaction Equation"));
            break;

          default:
            return QVariant();
            break;
        }
    }

  //Vertical header
  return QString("%1").arg(section + 1);
}

void CQFluxModeDM::setTask(const CEFMTask * pTask)
{
  beginResetModel();

  mpTask = pTask;

  if (mpTask != NULL)
    mBeginModes = mpTask->getFluxModes().begin();

  mFetched = std::min(mFetchLimit, size());

  endResetModel();
}

bool CQFluxModeDM::setData(const QModelIndex & /* index */, const QVariant & /* value */,
                           int /* role */)
{
  return false;
}

// virtual
void CQFluxModeDM::resetCacheProtected()
{}

// virtual
bool CQFluxModeDM::insertRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQFluxModeDM::removeRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQFluxModeDM::isDefaultRow(const QModelIndex& /* i */) const
{
  return false;
}
