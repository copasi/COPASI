// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/*
 * CQIndoDM.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: shoops
 */

#include "CQUndoDM.h"

#include <sstream>
#include <QTableView>

#include "copasi/UI/qtUtilities.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/undo/CUndoStack.h"
#include "copasi/undo/CUndoData.h"

CQUndoDM::CQUndoDM(QObject *parent, CDataModel * pDataModel, QTableView * pTableView)
  : CQBaseDataModel(parent, pDataModel)
  , mpUndoStack(NULL)
  , mpTableView(pTableView)
  , mIgnoredProperties()

{
  if (this->mpDataModel != NULL)
    {
      mpUndoStack = mpDataModel->getUndoStack();
    }

  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_PARENT_CN]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_TYPE]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_FLAG]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_INDEX]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_REFERENCES]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_REFERENCE]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_REFERENCE_CN]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_REFERENCE_INDEX]);
  mIgnoredProperties.insert(CData::PropertyName[CData::Property::OBJECT_POINTER]);

  assert(mpUndoStack != NULL);
}

// virtual
CQUndoDM::~CQUndoDM()
{}

// virtual
int CQUndoDM::rowCount(const QModelIndex &parent) const
{
  return static_cast< int >(mpUndoStack->size());
}

// virtual
int CQUndoDM::columnCount(const QModelIndex &parent) const
{
  return static_cast< int >(ColumnType::__SIZE);
}

// virtual
QVariant CQUndoDM::data(const QModelIndex &index, int role) const
{
  if (index.isValid())
    switch (role)
      {
        case Qt::DisplayRole:
          return displayData(index);
          break;

        default:
          return QVariant();
      }

  return QVariant();
}

QVariant CQUndoDM::displayData(const QModelIndex &index) const
{
  if (mpUndoStack->size() <= index.row() ||
      static_cast< int >(ColumnType::__SIZE) <= index.column()) return QVariant();

  const CUndoData & UndoData = mpUndoStack->operator [](index.row());

  switch (static_cast< ColumnType >(index.column()))
    {
      case ColumnType::Apply:
        return index.row() <= mpUndoStack->currentIndex() ? QVariant("Undo") : QVariant("Redo");
        break;

      case ColumnType::ObjectType:
        return QVariant(FROM_UTF8(UndoData.getObjectType()));
        break;

      case ColumnType::ObjectName:
        return QVariant(FROM_UTF8(UndoData.getObjectDisplayName()));
        break;

      case ColumnType::Action:
        return QVariant(FROM_UTF8(CUndoData::TypeName[UndoData.getType()]));
        break;

      case ColumnType::Property:
        // Loop through all changed properties
      {
        std::vector< std::string > ChangedProperties = changedProperties(UndoData);
        std::vector< std::string >::const_iterator it = ChangedProperties.begin();
        std::vector< std::string >::const_iterator end = ChangedProperties.end();

        std::stringstream  Result;
        bool first = true;

        for (; it != end; ++it)
          {
            if (!first)
              Result << std::endl;

            Result << *it;
            first = false;
          }

        return QVariant(FROM_UTF8(Result.str()));
      }

      break;

      case ColumnType::NewValue:

        // Loop through all changed properties
        if (UndoData.getType() != CUndoData::Type::REMOVE)
          {
            std::vector< std::string > ChangedProperties = changedProperties(UndoData);
            std::vector< std::string >::const_iterator it = ChangedProperties.begin();
            std::vector< std::string >::const_iterator end = ChangedProperties.end();

            const CData & Data = UndoData.getNewData();
            std::stringstream  Result;
            bool first = true;

            for (; it != end; ++it)
              {
                if (!first) Result << std::endl;

                Result << Data.getProperty(*it);
                first = false;
              }

            return QVariant(FROM_UTF8(Result.str()));
          }

        break;

      case ColumnType::OldValue:

        // Loop through all changed properties
        if (UndoData.getType() != CUndoData::Type::INSERT)
          {
            std::vector< std::string > ChangedProperties = changedProperties(UndoData);
            std::vector< std::string >::const_iterator it = ChangedProperties.begin();
            std::vector< std::string >::const_iterator end = ChangedProperties.end();

            const CData & Data = UndoData.getOldData();
            std::stringstream  Result;
            bool first = true;

            for (; it != end; ++it)
              {
                if (!first) Result << std::endl;

                Result << Data.getProperty(*it);
                first = false;
              }

            return QVariant(FROM_UTF8(Result.str()));
          }

        break;
    }

  return QVariant();
}

// virtual
QVariant CQUndoDM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
      switch (static_cast< ColumnType >(section))
        {
          case ColumnType::Apply:
            return QVariant("Apply");
            break;

          case ColumnType::ObjectType:
            return QVariant("Entity Type");
            break;

          case ColumnType::ObjectName:
            return QVariant("Name");
            break;

          case ColumnType::Action:
            return QVariant("Action");
            break;

          case ColumnType::Property:
            return QVariant("Property");
            break;

          case ColumnType::NewValue:
            return QVariant("New Value");
            break;

          case ColumnType::OldValue:
            return QVariant("Old Value");
            break;
        }
    }
  else if (orientation == Qt::Vertical &&
           role == Qt::SizeHintRole &&
           static_cast< size_t >(section) < mpUndoStack->size())
    {
      int Height = QFontMetrics(mpTableView->font()).height();

      return QVariant(QSize(0, changedProperties(mpUndoStack->operator [](section)).size() * (Height + 2)));
    }

  return QVariant();
}

// virtual
Qt::ItemFlags CQUndoDM::flags(const QModelIndex &index) const
{
  if (!index.isValid()) return Qt::ItemIsEnabled;

  return (QAbstractItemModel::flags(index) | Qt::ItemIsEnabled) & ~Qt::ItemIsEditable;
}

// virtual
bool CQUndoDM::setData(const QModelIndex &index, const QVariant &value, int role)
{
  return false;
}

// virtual
bool CQUndoDM::insertRows(int position, int rows, const QModelIndex & source)
{
  return false;
}

// virtual
bool CQUndoDM::removeRows(int position, int rows)
{
  return false;
}

std::vector< std::string > CQUndoDM::changedProperties(const CUndoData & undoData) const
{
  std::vector< std::string > ChangedProperties;

  std::set< std::string >::const_iterator it = undoData.getChangedProperties().begin();
  std::set< std::string >::const_iterator end = undoData.getChangedProperties().end();
  std::set< std::string >::const_iterator itIgnored = mIgnoredProperties.begin();
  std::set< std::string >::const_iterator endIgnored = mIgnoredProperties.end();

  while (it != end && itIgnored != endIgnored)
    {
      if (*it < *itIgnored)
        {
          ChangedProperties.push_back(*it);
          ++it;
        }
      else if (*it > *itIgnored)
        {
          ++itIgnored;
        }
      else
        {
          ++it;
          ++itIgnored;
        }
    }

  for (; it != end; ++it)
    {
      ChangedProperties.push_back(*it);
    }

  return ChangedProperties;
}
