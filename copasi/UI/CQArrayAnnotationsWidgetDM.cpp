// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQArrayAnnotationsWidgetDM.h"
#include "CColorScale.h"
#include "qtUtilities.h"
#include <QSortFilterProxyModel>

#include "copasi.h"
#include "utilities/CAnnotatedMatrix.h"

CQArrayAnnotationsWidgetDM::CQArrayAnnotationsWidgetDM(QObject *parent):
  QAbstractTableModel(parent),
  mpColorScale(NULL),
  mpArray(NULL),
  mIndex(),
  mRow(C_INVALID_INDEX),
  mColumn(C_INVALID_INDEX)
{}

CQArrayAnnotationsWidgetDM::~CQArrayAnnotationsWidgetDM()
{}

// virtual
QVariant CQArrayAnnotationsWidgetDM::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() ||
      (role != Qt::DisplayRole &&
       role != Qt::BackgroundRole) ||
      mpArray == NULL) return QVariant();

  QModelIndex SourceIndex = index;

  while (SourceIndex.model()->inherits("QSortFilterProxyModel"))
    {
      SourceIndex = static_cast< const QSortFilterProxyModel * >(SourceIndex.model())->mapToSource(SourceIndex);
    }

  if (mRow != C_INVALID_INDEX) mIndex[mRow] = SourceIndex.row();

  if (mColumn != C_INVALID_INDEX) mIndex[mColumn] = SourceIndex.column();

  switch (role)
    {
      case Qt::DisplayRole:
        return QVariant((*mpArray->array())[mIndex]);

        break;

      case Qt::BackgroundRole:
        return QVariant(mpColorScale->getColor((*mpArray->array())[mIndex]));
        break;
    }

  return QVariant();
}

// virtual
QVariant CQArrayAnnotationsWidgetDM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if ((role != Qt::DisplayRole &&
       role != Qt::ToolTipPropertyRole) ||
      mpArray == NULL)
    {
      return QVariant();
    }

  if (orientation == Qt::Vertical)
    {
      if (mRow == C_INVALID_INDEX ||
          section < 0 ||
          (C_INT32)mpArray->size()[mRow] <= section)
        {
          return QVariant();
        }

      return QVariant(FROM_UTF8(mpArray->getAnnotationsString(mRow)[section]));
    }
  else
    {
      if (mColumn == C_INVALID_INDEX ||
          section < 0 ||
          (C_INT32)mpArray->size()[mColumn] <= section)
        {
          return QVariant();
        }

      if (role == Qt::DisplayRole)
        {
          return QVariant(FROM_UTF8(mpArray->getAnnotationsString(mColumn)[section]).replace("; {", "\n{"));
        }

      return QVariant(FROM_UTF8(mpArray->getAnnotationsString(mColumn)[section]));
    }

  return QVariant();
}

// virtual
Qt::ItemFlags CQArrayAnnotationsWidgetDM::flags(const QModelIndex &index) const
{
  return QAbstractItemModel::flags(index) & Qt::ItemIsEnabled & ~Qt::ItemIsEditable;
}

// virtual
int CQArrayAnnotationsWidgetDM::rowCount(const QModelIndex & /* parent */) const
{
  if (mpArray == NULL) return 0;

  if (mRow == C_INVALID_INDEX) return 1;

  return mpArray->size()[mRow];
}

// virtual
int CQArrayAnnotationsWidgetDM::columnCount(const QModelIndex & /* parent */) const
{
  if (mpArray == NULL) return 0;

  if (mColumn == C_INVALID_INDEX) return 1;

  return mpArray->size()[mColumn];
}

void CQArrayAnnotationsWidgetDM::setContext(const CColorScale * pColorScale,
    const CArrayAnnotation * pArray,
    const std::vector< size_t > & index,
    const size_t & row,
    const size_t & column)
{
  if (mpArray != pArray ||
      mpColorScale != pColorScale ||
      mIndex != index ||
      mRow != row ||
      mColumn != column)
    {
      beginResetModel();

      mpArray = pArray;
      mpColorScale = pColorScale;
      mIndex = index;
      mRow = row;
      mColumn = column;

      endResetModel();
    }
}
