// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQTimeSeriesDM.h"
#include "qtUtilities.h"

#include "trajectory/CTimeSeries.h"

CQTimeSeriesDM::CQTimeSeriesDM(QObject *parent):
  CQBaseDataModel(parent),
  mpTimeSeries(NULL),
  mFramework(0)
{}

CQTimeSeriesDM::~CQTimeSeriesDM()
{}

// virtual
int CQTimeSeriesDM::rowCount(const QModelIndex & /* parent */) const
{
  if (mpTimeSeries == NULL) return 0;

  return (int) mpTimeSeries->getRecordedSteps();
}

// virtual
int CQTimeSeriesDM::columnCount(const QModelIndex & /* parent */) const
{
  if (mpTimeSeries == NULL) return 0;

  return (int) mpTimeSeries->getNumVariables();
}

// virtual
Qt::ItemFlags CQTimeSeriesDM::flags(const QModelIndex &index) const
{
  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

// virtual
QVariant CQTimeSeriesDM::data(const QModelIndex &index, int role) const
{
  if (mpTimeSeries == NULL || role != Qt::DisplayRole) return QVariant();

  if (!index.isValid() ||
      index.row() < 0 || rowCount() <= index.row() ||
      index.column() < 0 || columnCount() <= index.column())  return QVariant();

  switch (mFramework)
    {
      case 0:
        return mpTimeSeries->getConcentrationData(index.row(), index.column());

      case 1:
        return mpTimeSeries->getData(index.row(), index.column());
    }

  return QVariant();
}

// virtual
QVariant CQTimeSeriesDM::headerData(int section, Qt::Orientation orientation,
                                    int role) const
{
  if (mpTimeSeries == NULL || role != Qt::DisplayRole) return QVariant();

  switch (orientation)
    {
      case Qt::Horizontal:

        if (section < 0 || columnCount() <= section) return QVariant();

        return QString(FROM_UTF8(mpTimeSeries->getTitle(section)));

      case Qt::Vertical:

        if (section < 0 || rowCount() <= section) return QVariant();

        return QString("%1").arg(section + 1);
    }

  return QVariant();
}

void CQTimeSeriesDM::setTimeSeries(const CTimeSeries * pTimeSeries)
{
  mpTimeSeries = pTimeSeries;
  reset();
}

void CQTimeSeriesDM::setFramework(int framework)
{
  if (mFramework == framework) return;

  mFramework = framework;
  emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
}

bool CQTimeSeriesDM::setData(const QModelIndex & /* index */, const QVariant & /* value */, int /* role */)
{
  return false;
}

// virtual
bool CQTimeSeriesDM::insertRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQTimeSeriesDM::removeRows(int /* position */, int /* rows */, const QModelIndex & /* index */)
{
  return false;
}

// virtual
bool CQTimeSeriesDM::isDefaultRow(const QModelIndex& /* i */) const
{
  return false;
}
