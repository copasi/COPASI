// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLayoutsDM.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: bergmann $
//   $Date: 2012/04/10 15:19:37 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QString>

#include "CQMessageBox.h"
#include "CQLayoutsDM.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "layout/CListOfLayouts.h"


CQLayoutsDM::CQLayoutsDM(QObject *parent) :
    CQBaseDataModel(parent),
    mpListOfLayouts(NULL)
{}

CQLayoutsDM::~CQLayoutsDM()
{}

int CQLayoutsDM::rowCount(const QModelIndex & /* parent */) const
{
  if (mpListOfLayouts == NULL) return 0;

  return (int) mpListOfLayouts->size();
}


bool CQLayoutsDM::clear()
{
  return removeRows(0, rowCount());
}


int CQLayoutsDM::columnCount(const QModelIndex & /* parent */) const
{
  return TOTAL_COLS;
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
        return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
        break;

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
            return QVariant(FROM_UTF8((*mpListOfLayouts)[index.row()]->getObjectName()));
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

bool CQLayoutsDM::setData(const QModelIndex &index, const QVariant & /* value */, int role)
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
            return false;
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


bool CQLayoutsDM::insertRows(int position, int rows, const QModelIndex&)
{
  if (mpListOfLayouts == NULL) return false;

  if (position + rows > (int) mpListOfLayouts->size())  return false;

  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    {
      emit notifyGUI(ListViews::LAYOUT, ListViews::ADD, (*mpListOfLayouts)[position + row]->getKey());
    }

  endInsertRows();

  return true;
}

bool CQLayoutsDM::removeRows(int position, int rows, const QModelIndex&)
{
  if (rows <= 0) return true;

  if (mpListOfLayouts == NULL) return false;

  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  std::vector< CLayout * > DeletedLayouts;
  DeletedLayouts.resize(rows);

  std::vector< CLayout * >::iterator itDeletedLayout;
  std::vector< CLayout * >::iterator endDeletedLayout = DeletedLayouts.end();

  CListOfLayouts::const_iterator itRow = mpListOfLayouts->begin() + position;

  for (itDeletedLayout = DeletedLayouts.begin(); itDeletedLayout != endDeletedLayout; ++itDeletedLayout, ++itRow)
    {
      *itDeletedLayout = *itRow;
    }

  for (itDeletedLayout = DeletedLayouts.begin(); itDeletedLayout != endDeletedLayout; ++itDeletedLayout)
    {
      std::string Key = (*itDeletedLayout)->getKey();

      pdelete(*itDeletedLayout);

      emit notifyGUI(ListViews::LAYOUT, ListViews::DELETE, Key);
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
      Layouts.append((*mpListOfLayouts)[(*i).row()]);
    }

  QList< CLayout * >::const_iterator j;

  for (j = Layouts.begin(); j != Layouts.end(); ++j)
    {
      CLayout * pLayout = *j;

      size_t delRow = mpListOfLayouts->getIndex(pLayout);

      if (delRow != C_INVALID_INDEX)
        {
          QMessageBox::StandardButton choice =
            CQMessageBox::confirmDelete(NULL, "layout",
                                        FROM_UTF8(pLayout->getObjectName()),
                                        std::set< const CCopasiObject * >());

          if (choice == QMessageBox::Ok)
            removeRow((int) delRow);
        }
    }

  return true;
}

void CQLayoutsDM::setListOfLayouts(CListOfLayouts * pListOfLayouts)
{
  if (mpListOfLayouts != pListOfLayouts)
    {
      mpListOfLayouts = pListOfLayouts;
      reset();
    }
}
