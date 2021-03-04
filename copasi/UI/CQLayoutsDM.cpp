// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QString>

#include "CQMessageBox.h"
#include "CQLayoutsDM.h"
#include "qtUtilities.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/layout/CListOfLayouts.h"

CQLayoutsDM::CQLayoutsDM(QObject *parent) :
  CQBaseDataModel(parent, NULL),
  mpListOfLayouts(NULL),
  mNewName("layout")
{}

CQLayoutsDM::~CQLayoutsDM()
{}

size_t CQLayoutsDM::size() const
{
  if (mpListOfLayouts != NULL)
    return mpListOfLayouts->size();

  return 0;
}

int CQLayoutsDM::rowCount(const QModelIndex& C_UNUSED(parent)) const
{
  return mFetched;
}

// virtual
void CQLayoutsDM::resetCacheProtected()
{
  mpListOfLayouts = mpDataModel->getListOfLayouts();
}

int CQLayoutsDM::columnCount(const QModelIndex & /* parent */) const
{
  return TOTAL_COLS_LAYOUT;
}

Qt::ItemFlags CQLayoutsDM::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return QAbstractItemModel::flags(index);

  switch (index.column())
    {
      case COL_ROW_NUMBER:
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
        break;

      case COL_NAME:
      case COL_SHOW:
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        break;
    }

  return QAbstractItemModel::flags(index);
}

QVariant CQLayoutsDM::data(const QModelIndex &index, int role) const
{
  if (mpListOfLayouts == NULL) return QVariant();

  if (!index.isValid()) return QVariant();

  if (index.row() >= rowCount()) return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
      switch (index.column())
        {
          case COL_ROW_NUMBER:
            return QVariant(index.row() + 1);
            break;

          case COL_NAME:
            return QVariant(FROM_UTF8(mpListOfLayouts->operator[](index.row()).getObjectName()));
            break;

          case COL_SHOW:
            return (role == Qt::EditRole) ? QVariant("Show") : QVariant();
            break;
        }
    }

  return QVariant();
}

QVariant CQLayoutsDM::headerData(int section, Qt::Orientation orientation,
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

          case COL_NAME:
            return QVariant(QString("Name"));
            break;

          case COL_SHOW:
            return QVariant("Show");
            break;

          default:
            return QVariant();
            break;
        }
    }

  return QString("%1").arg(section + 1);
}

bool CQLayoutsDM::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (mpListOfLayouts == NULL) return false;

  if (!index.isValid()) return false;

  if (index.row() >= rowCount()) return false;

  if (index.isValid() && role == Qt::EditRole)
    {
      switch (index.column())
        {
          case COL_ROW_NUMBER:
            return false;
            break;

          case COL_NAME:
            return mpListOfLayouts->operator[](index.row()).setObjectName(TO_UTF8(createNewName(value.toString(), COL_NAME)));
            break;

          case COL_SHOW:
            return true;
            break;

          default:
            return false;
            break;
        }
    }

  return true;
}

// virtual
bool CQLayoutsDM::isDefaultRow(const QModelIndex & /* index */) const
{
  return false;
}

bool CQLayoutsDM::insertRows(int position, int rows, const QModelIndex & parent)
{
  if (mpListOfLayouts == NULL) return false;

  bool valid = parent.isValid();
  int Position = valid ? parent.row() : position;

  if (Position + rows > (int) mpListOfLayouts->size())  return false;

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      ++mFetched;
      emit notifyGUI(ListViews::ObjectType::LAYOUT, ListViews::ADD, mpListOfLayouts->operator[](Position + row).getCN());
    }

  endInsertRows();
  return true;
}

bool CQLayoutsDM::removeRows(int position, int rows, const QModelIndex & parent)
{
  if (rows <= 0) return true;

  if (mpListOfLayouts == NULL) return false;

  beginRemoveRows(parent, position, std::min< int >(mFetched, position + rows) - 1);
  std::vector< CLayout * > DeletedLayouts;
  DeletedLayouts.resize(rows);
  std::vector< CLayout * >::iterator itDeletedLayout;
  std::vector< CLayout * >::iterator endDeletedLayout = DeletedLayouts.end();
  CListOfLayouts::iterator itRow = mpListOfLayouts->begin() + position;

  for (itDeletedLayout = DeletedLayouts.begin(); itDeletedLayout != endDeletedLayout; ++itDeletedLayout, ++itRow)
    {
      *itDeletedLayout = itRow;
    }

  for (itDeletedLayout = DeletedLayouts.begin(); itDeletedLayout != endDeletedLayout; ++itDeletedLayout)
    {
      if (mFetched > 0)
        --mFetched;

      std::string cn = (*itDeletedLayout)->getCN();
      pdelete(*itDeletedLayout);
      emit notifyGUI(ListViews::ObjectType::LAYOUT, ListViews::DELETE, cn);
    }

  endRemoveRows();
  return true;
}

bool CQLayoutsDM::removeRows(QModelIndexList rows, const QModelIndex & /* index */)
{
  if (rows.isEmpty()) return false;

  if (mpListOfLayouts == NULL) return false;

  //  Build the list of pointers to items to be deleted
  //  before actually deleting any item.
  QList< CLayout * > Layouts;
  QModelIndexList::const_iterator i;

  for (i = rows.begin(); i != rows.end(); ++i)
    {
      if (i->isValid())
        Layouts.append(&mpListOfLayouts->operator[](i->row()));
    }

  QList< CLayout * >::const_iterator j;

  for (j = Layouts.begin(); j != Layouts.end(); ++j)
    {
      CLayout *pLayout = *j;
      size_t delRow = mpListOfLayouts->CDataVector< CLayout >::getIndex(pLayout);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(ListViews::ancestor(this), "layout",
                                        FROM_UTF8(pLayout->getObjectName()),
                                        pLayout);

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}

void CQLayoutsDM::setListOfLayouts(CListOfLayouts *pListOfLayouts)
{
  if (mpListOfLayouts != pListOfLayouts)
    {
      beginResetModel();
      mpListOfLayouts = pListOfLayouts;
      mFetched = std::min(mFetchLimit, size());
      endResetModel();
      //reset();
    }
}
