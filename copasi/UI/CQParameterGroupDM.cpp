// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQMethodParametersDM.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: shoops
 */

#include "CQParameterGroupDM.h"

#include "qtUtilities.h"

#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/resourcesUI/CQIconResource.h"

#define COL_NAME       0
#define COL_VALUE      1
#define COL_TYPE       2

#define COLUMN_COUNT   2

CQParameterGroupDM::CQParameterGroupDM(QObject * pParent):
  QAbstractItemModel(pParent),
  mTopLevelGroups(),
  mAdvanced(true)
{}

// virtual
CQParameterGroupDM::~CQParameterGroupDM()
{}

// virtual
int CQParameterGroupDM::columnCount(const QModelIndex & /* parent */) const
{
  return COLUMN_COUNT;
}

// virtual
QVariant CQParameterGroupDM::data(const QModelIndex & index, int role) const
{
  CCopasiParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL) return QVariant();

  switch (role)
    {
      case Qt::UserRole + 1:
        if (index.column() == COL_NAME)
          return QString(pNode->isBasic() || !pNode->isDefault() ? "basic" : "advanced");

        break;

      case Qt::UserRole + 2:
        if (index.column() == COL_NAME)
          return QString(pNode->isBasic() ? "basic" : "advanced");

        break;

      default:
        switch (index.column())
          {
            case COL_NAME:
              return nameData(pNode, role);
              break;

            case COL_VALUE:
              return valueData(pNode, role);
              break;

            case COL_TYPE:
              return typeData(pNode, role);
              break;
          }
    }

  return QVariant();
}

// virtual
Qt::ItemFlags CQParameterGroupDM::flags(const QModelIndex &index) const
{
  CCopasiParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL)
    {
      return Qt::ItemIsEnabled;
    }

  Qt::ItemFlags Flags = QAbstractItemModel::flags(index);

  if (pNode->isEditable())
    Flags |= Qt::ItemIsEditable;
  else
    Flags &= ~Qt::ItemIsEditable;

  if (index.column() == COL_VALUE)
    {
      if (pNode->getType() == CCopasiParameter::Type::BOOL)
        return Flags | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;

      if (pNode->hasValidValues())
        {
          emit signalCreateComboBox(index);
        }
      else if (pNode->getType() == CCopasiParameter::Type::GROUP &&
               static_cast< CCopasiParameterGroup * >(pNode)->haveTemplate())
        {
          emit signalCreatePushButton(index);
        }
      else
        {
          emit signalCloseEditor(index);
        }

      if (pNode->getType() == CCopasiParameter::Type::CN)
        {
          return (Flags | Qt::ItemIsEnabled) & ~Qt::ItemIsEditable;
        }

      return Flags | Qt::ItemIsEnabled;
    }

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

// virtual
QVariant CQParameterGroupDM::headerData(int section, Qt::Orientation /* orientation */, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (section)
    {
      case COL_NAME:
        return QVariant("Name");
        break;

      case COL_TYPE:
        return QVariant("Type");
        break;

      case COL_VALUE:
        return QVariant("Value");
        break;
    }

  return QVariant();
}

// virtual
QModelIndex CQParameterGroupDM::index(int row, int column, const QModelIndex & parent) const
{
  CCopasiParameterGroup * pParent = static_cast< CCopasiParameterGroup * >(nodeFromIndex(parent));
  int Row = row;

  if (pParent == NULL &&
      mTopLevelGroups.size() > 0)
    {
      QVector< CCopasiParameterGroup * >::const_iterator it = mTopLevelGroups.constBegin();
      QVector< CCopasiParameterGroup * >::const_iterator end = mTopLevelGroups.constEnd();

      for (; it != end; ++it)
        if (Row < (int)(*it)->size())
          {
            if (mAdvanced)
              {
                return createIndex(row, column, *((*it)->beginIndex() + Row));
              }

            CCopasiParameterGroup::index_iterator itRow = (*it)->beginIndex();
            CCopasiParameterGroup::index_iterator endRow = (*it)->endIndex();

            for (; itRow != endRow; ++itRow)
              {
                if ((*itRow)->isBasic() && !(*itRow)->isUnsupported()) --Row;

                if (Row == -1)
                  {
                    return createIndex(row, column, *(itRow));
                  }
              }

            return QModelIndex();
          }
        else
          {
            Row -= (int)(*it)->size();
          }

      return QModelIndex();
    }

  if (pParent != NULL && row < (int) pParent->size())
    {
      if (mAdvanced)
        {
          return createIndex(row, column, *(pParent->beginIndex() + row));
        }

      CCopasiParameterGroup::index_iterator itRow = pParent->beginIndex();
      CCopasiParameterGroup::index_iterator endRow = pParent->endIndex();

      for (; itRow != endRow; ++itRow)
        {
          if ((*itRow)->isBasic() && !(*itRow)->isUnsupported()) --Row;

          if (Row == -1)
            {
              return createIndex(row, column, *(itRow));
            }
        }
    }

  return QModelIndex();
}

// virtual
QModelIndex CQParameterGroupDM::parent(const QModelIndex & index) const
{
  CCopasiParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL || isTopLevelGroup(pNode))
    {
      return QModelIndex();
    }

  if (isTopLevelGroup(dynamic_cast<CCopasiParameter *>(pNode->getObjectParent())))
    {
      return QModelIndex();
    }

  CCopasiParameter * pParent = static_cast< CCopasiParameter * >(pNode->getObjectParent());

  return createIndex(getRow(pParent), 0, pParent);
}

// virtual
int CQParameterGroupDM::rowCount(const QModelIndex & parent) const
{
  CCopasiParameter::UserInterfaceFlag Exclude(CCopasiParameter::eUserInterfaceFlag::unsupported);
  CCopasiParameter::UserInterfaceFlag Require(mAdvanced ? CCopasiParameter::UserInterfaceFlag::None : CCopasiParameter::eUserInterfaceFlag::basic);

  if (!parent.isValid())
    {
      QVector< CCopasiParameterGroup * >::const_iterator it = mTopLevelGroups.constBegin();
      QVector< CCopasiParameterGroup * >::const_iterator end = mTopLevelGroups.constEnd();

      int size = 0;

      for (; it != end; ++it)
        {
          size += (int)(*it)->size(Require, Exclude);
        }

      return size;
    }

  CCopasiParameter * pParent = nodeFromIndex(parent);

  switch (pParent->getType())
    {
      case CCopasiParameter::Type::GROUP:
        return (int) static_cast< CCopasiParameterGroup * >(pParent)->size(Require, Exclude);
        break;

      default:
        break;
    }

  return 0;
}

// virtual
bool CQParameterGroupDM::setData(const QModelIndex &_index, const QVariant &value, int role)
{
  CCopasiParameter * pNode = nodeFromIndex(_index);

  if (pNode == NULL) return false;

  bool success = false;

  if (role == Qt::EditRole ||
      role == Qt::CheckStateRole)
    {
      switch (_index.column())
        {
          case COL_VALUE:
            success = setParameterValue(pNode, value);

            break;

          default:
            success = true;
            break;
        }
    }

  return success;
}

void CQParameterGroupDM::setAdvanced(const bool & advanced)
{
  mAdvanced = advanced;
}

void CQParameterGroupDM::pushGroup(CCopasiParameterGroup * pTopLevelGroup)
{
  assert(pTopLevelGroup != NULL);

  QVector< CCopasiParameterGroup * >::const_iterator it = mTopLevelGroups.constBegin();
  QVector< CCopasiParameterGroup * >::const_iterator end = mTopLevelGroups.constEnd();

  for (; it != end; ++it)
    if (*it == pTopLevelGroup) return;

  beginResetModel();
  mTopLevelGroups.append(pTopLevelGroup);
  endResetModel();
}

void CQParameterGroupDM::popGroup(CCopasiParameterGroup * pTopLevelGroup)
{
  QVector< CCopasiParameterGroup * >::iterator it = mTopLevelGroups.begin();
  QVector< CCopasiParameterGroup * >::iterator end = mTopLevelGroups.end();

  for (; it != end; ++it)
    if (*it == pTopLevelGroup)
      {
        beginResetModel();
        mTopLevelGroups.erase(it);
        endResetModel();
      }
}

void CQParameterGroupDM::clearGroups()
{
  beginResetModel();
  mTopLevelGroups.clear();
  endResetModel();
}

void CQParameterGroupDM::beginResetModel()
{
  QAbstractItemModel::beginResetModel();
}

void CQParameterGroupDM::endResetModel()
{
  QAbstractItemModel::endResetModel();
}

QModelIndex CQParameterGroupDM::index(CCopasiParameter * pNode) const
{
  if (pNode == NULL)
    {
      return QModelIndex();
    }

  if (isTopLevelGroup(pNode))
    {
      return index(0, 0, QModelIndex());
    }

  QModelIndex Parent = index(static_cast< CCopasiParameter * >(pNode->getObjectParent()));

  return index(getRow(pNode), 0, Parent);
}

bool CQParameterGroupDM::isTopLevelGroup(CCopasiParameter * pNode) const
{
  QVector< CCopasiParameterGroup * >::const_iterator it = mTopLevelGroups.constBegin();
  QVector< CCopasiParameterGroup * >::const_iterator end = mTopLevelGroups.constEnd();

  for (; it != end; ++it)
    if (*it == pNode) return true;

  return false;
}

// static
CCopasiParameter * CQParameterGroupDM::nodeFromIndex(const QModelIndex & index)
{
  if (!index.isValid()) return NULL;

  QModelIndex Source = index;

  while (Source.model()->inherits("QSortFilterProxyModel"))
    {
      Source = static_cast< const QSortFilterProxyModel *>(Source.model())->mapToSource(index);
    }

  return static_cast< CCopasiParameter * >(Source.internalPointer());
}

int CQParameterGroupDM::getRow(const CCopasiParameter * pNode) const
{
  if (pNode == NULL)
    {
      return -1;
    }

  CCopasiParameterGroup * pParent = static_cast< CCopasiParameterGroup * >(pNode->getObjectParent());

  if (pParent == NULL)
    {
      return 0;
    }

  if (isTopLevelGroup(pParent))
    {
      QVector< CCopasiParameterGroup * >::const_iterator itTopLevelGroup = mTopLevelGroups.constBegin();
      QVector< CCopasiParameterGroup * >::const_iterator endTopLevelGroup = mTopLevelGroups.constEnd();

      int i = 0;

      for (; itTopLevelGroup != endTopLevelGroup; ++itTopLevelGroup)
        {
          CCopasiParameterGroup::index_iterator it = pParent->beginIndex();
          CCopasiParameterGroup::index_iterator end = pParent->endIndex();

          for (; it != end; ++it)
            if (!(*it)->isUnsupported() &&
                (mAdvanced || (*it)->isBasic()))
              {
                if (*it == pNode) return i;

                ++i;
              }
        }
    }
  else
    {
      int i = 0;

      CCopasiParameterGroup::index_iterator it = pParent->beginIndex();
      CCopasiParameterGroup::index_iterator end = pParent->endIndex();

      for (; it != end; ++it, ++i)
        if (!(*it)->isUnsupported() &&
            (mAdvanced || (*it)->isBasic()))
          {
            if (*it == pNode) return i;

            ++i;
          }
    }

  return -1;
}

// static
QVariant CQParameterGroupDM::nameData(const CCopasiParameter * pNode, int role)
{
  if (role == Qt::DisplayRole)
    {
      return QVariant(QString(FROM_UTF8(pNode->getObjectName())));
    }

  return QVariant();
}

// static
QVariant CQParameterGroupDM::typeData(const CCopasiParameter * pNode, int role)
{
  return QVariant(static_cast< int >(pNode->getType()));
}

QVariant CQParameterGroupDM::valueData(const CCopasiParameter * pNode, int role)
{
  switch (role)
    {
      case Qt::EditRole:
      case Qt::DisplayRole:

        switch (pNode->getType())
          {
            case CCopasiParameter::Type::DOUBLE:
            case CCopasiParameter::Type::UDOUBLE:
              return QVariant(convertToQString(pNode->getValue< C_FLOAT64 >()));
              break;

            case CCopasiParameter::Type::INT:
              return QVariant(QString::number(pNode->getValue< C_INT32 >()));
              break;

            case CCopasiParameter::Type::UINT:
              return QVariant(QString::number(pNode->getValue< unsigned C_INT32 >()));
              break;

            case CCopasiParameter::Type::BOOL:

              if (role == Qt::DisplayRole)
                return QVariant();
              else
                return QVariant(pNode->getValue< bool >());

              break;

            case CCopasiParameter::Type::GROUP:

              if (static_cast< const CCopasiParameterGroup * >(pNode)->haveTemplate())
                {
                  QVariant(QString("Add"));
                }

              return QVariant();
              break;

            case CCopasiParameter::Type::STRING:
            case CCopasiParameter::Type::FILE:
            case CCopasiParameter::Type::EXPRESSION:
            case CCopasiParameter::Type::KEY:
              return QVariant(FROM_UTF8(pNode->getValue< std::string >()));

            case CCopasiParameter::Type::CN:
            {
              const CObjectInterface * pObject = pNode->getObjectFromCN(pNode->getValue< CRegisteredCommonName >());

              if (pObject != NULL)
                {
                  return QVariant(FROM_UTF8(pObject->getObjectDisplayName()));
                }

              return QVariant("Object not found");
            }
            break;

            default:
              return QVariant();
              break;
          }

        break;

      case Qt::CheckStateRole:

        if (pNode->getType() == CCopasiParameter::Type::BOOL)
          {
            return pNode->getValue< bool >() ? Qt::Checked : Qt::Unchecked;
          }

        break;

      case Qt::UserRole:
      {
        QList< QPair < QVariant, QVariant > > ValidValues = getParameterValidValues(pNode);

        QList< QPair < QVariant, QVariant > >::const_iterator it = ValidValues.constBegin();
        QList< QPair < QVariant, QVariant > >::const_iterator end = ValidValues.constEnd();
        QStringList ValidValueList;

        for (; it != end; ++it)
          if (it->first == it->second) ValidValueList.append(it->first.toString());

        return QVariant(ValidValueList);
      }
      break;
    }

  return QVariant();
}
