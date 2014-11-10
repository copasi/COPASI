// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMSpeciesDM.h"
#include "qtUtilities.h"

#include "elementaryFluxModes/CEFMTask.h"
#include "elementaryFluxModes/CEFMMethod.h"
#include "elementaryFluxModes/CFluxMode.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "utilities/CCopasiProblem.h"

CQEFMSpeciesDM::CQEFMSpeciesDM(QObject *parent):
  CQBaseDataModel(parent),
  mpTask(NULL),
  mBeginModes(),
  mModesSize(0),
  mpModel(NULL),
  mBeginSpecies(),
  mSpeciesSize(0)
{}

int CQEFMSpeciesDM::rowCount(const QModelIndex & C_UNUSED(parent)) const
{
  if (mpTask == NULL)
    return 0;

  return (int) mModesSize;
}

int CQEFMSpeciesDM::columnCount(const QModelIndex & C_UNUSED(parent)) const
{
  if (mpTask == NULL)
    return 0;

  return (int)(mSpeciesSize + 1);  // For flux mode number
}

Qt::ItemFlags CQEFMSpeciesDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

QVariant CQEFMSpeciesDM::data(const QModelIndex &index, int role) const
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
          {
            std::pair< C_FLOAT64, C_FLOAT64 > Changes =
              mpTask->getSpeciesChanges(*(mBeginModes + index.row()), **(mBeginSpecies + index.column() - 1));

            if (Changes.first > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() ||
                Changes.second > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
              {
                return QVariant(QString("-" + QString::number(Changes.first) + " | +" + QString::number(Changes.second)));
              }

            return QVariant();
          }
        }
    }

  return QVariant();
}

QVariant CQEFMSpeciesDM::headerData(int section, Qt::Orientation orientation,
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
            return QVariant(QString(FROM_UTF8(CMetabNameInterface::getDisplayName(mpModel, **(mBeginSpecies + section - 1), false))));
            break;
        }
    }

  return QString("%1").arg(section + 1);
}

void CQEFMSpeciesDM::setTask(const CEFMTask * pTask)
{
  mpTask = pTask;

  if (mpTask != NULL)
    {
      mBeginModes = mpTask->getFluxModes().begin();
      mModesSize = mpTask->getFluxModes().size();

      mpModel = mpTask->getProblem()->getModel();

      if (mpModel != NULL)
        {
          mBeginSpecies = mpModel->getMetabolites().begin();
          mSpeciesSize = mpModel->getMetabolites().size();
        }
      else
        {
          mSpeciesSize = 0;
        }
    }
  else
    {
      mModesSize = 0;
      mpModel = NULL;
      mSpeciesSize = 0;
    }
}

bool CQEFMSpeciesDM::setData(const QModelIndex & /* index */, const QVariant & /* value */, int /* role */)
{
  return false;
}

// virtual
bool CQEFMSpeciesDM::insertRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQEFMSpeciesDM::removeRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQEFMSpeciesDM::isDefaultRow(const QModelIndex& /* i */) const
{
  return false;
}
