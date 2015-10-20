// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQMethodParametersDM.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: shoops
 */

#include "CQTaskMethodParametersDM.h"

#include "CQTaskMethodParametersDM.h"
#include "qtUtilities.h"

#include "utilities/CCopasiMethod.h"
#include "resourcesUI/CQIconResource.h"

#define COL_NAME       0
#define COL_VALUE      1
#define COL_TYPE       2

#define COLUMN_COUNT   2

CQTaskMethodParametersDM::CQTaskMethodParametersDM(QObject * pParent):
  QAbstractItemModel(pParent),
  mMethods(),
  mFramework(0)
{}

// virtual
CQTaskMethodParametersDM::~CQTaskMethodParametersDM()
{}

// virtual
int CQTaskMethodParametersDM::columnCount(const QModelIndex & /* parent */) const
{
  return COLUMN_COUNT;
}

// virtual
QVariant CQTaskMethodParametersDM::data(const QModelIndex & index, int role) const
{
  CCopasiParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL) return QVariant();

  switch (index.column())
    {
      case COL_NAME:
        return nameData(pNode, role);
        break;

      case COL_TYPE:
        return typeData(pNode, role);
        break;

      case COL_VALUE:
        return valueData(pNode, role);
        break;
    }

  return QVariant();
}

// virtual
Qt::ItemFlags CQTaskMethodParametersDM::flags(const QModelIndex &index) const
{
  CCopasiParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL)
    {
      return Qt::ItemIsEnabled;
    }

  if (index.column() == COL_VALUE)
    {
      if (pNode->getType() == CCopasiParameter::BOOL)
        return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;;

      if (pNode->hasValidValues())
        {
          emit signalOpenEditor(index);
        }
      else
        {
          emit signalCloseEditor(index);
        }

      return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

// virtual
QVariant CQTaskMethodParametersDM::headerData(int section, Qt::Orientation /* orientation */, int role) const
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
QModelIndex CQTaskMethodParametersDM::index(int row, int column, const QModelIndex & parent) const
{
  CCopasiParameterGroup * pParent = static_cast< CCopasiParameterGroup * >(nodeFromIndex(parent));

  if (pParent == NULL &&
      mMethods.size() > 0)
    {
      QVector< CCopasiMethod * >::const_iterator it = mMethods.constBegin();
      QVector< CCopasiMethod * >::const_iterator end = mMethods.constEnd();

      int Row = row;

      for (; it != end; ++it)
        if (Row < (int)(*it)->size())
          {
            return createIndex(row, column, *((*it)->beginIndex() + Row));
          }
        else
          {
            Row -= (int)(*it)->size();
          }

      return QModelIndex();
    }

  if (pParent != NULL && row < (int) pParent->size())
    return createIndex(row, column, *(pParent->beginIndex() + row));
  else
    return QModelIndex();
}

// virtual
QModelIndex CQTaskMethodParametersDM::parent(const QModelIndex & index) const
{
  CCopasiParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL || isMethod(pNode))
    {
      return QModelIndex();
    }

  if (isMethod(dynamic_cast<CCopasiParameter *>(pNode->getObjectParent())))
    {
      return QModelIndex();
    }

  CCopasiParameter * pParent = static_cast< CCopasiParameter * >(pNode->getObjectParent());

  return createIndex(getRow(pParent), 0, pParent);
}

// virtual
int CQTaskMethodParametersDM::rowCount(const QModelIndex & parent) const
{
  if (!parent.isValid())
    {
      QVector< CCopasiMethod * >::const_iterator it = mMethods.constBegin();
      QVector< CCopasiMethod * >::const_iterator end = mMethods.constEnd();

      int size = 0;

      for (; it != end; ++it)
        size += (int)(*it)->size();

      return size;
    }

  CCopasiParameter * pParent = nodeFromIndex(parent);

  switch (pParent->getType())
    {
      case CCopasiParameter::GROUP:
        return (int) static_cast< CCopasiParameterGroup * >(pParent)->size();
        break;

      default:
        break;
    }

  return 0;
}

// virtual
bool CQTaskMethodParametersDM::setData(const QModelIndex &_index, const QVariant &value, int role)
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

void CQTaskMethodParametersDM::setMethod(CCopasiMethod * pMethod)
{
  assert(pMethod != NULL);

  beginResetModel();

  if (mMethods.size() <= 0)
    {
      mMethods.append(pMethod);
    }
  else
    {
      mMethods[0] = pMethod;
    }

  endResetModel();
}

void CQTaskMethodParametersDM::pushMethod(CCopasiMethod * pMethod)
{
  assert(pMethod != NULL);

  QVector< CCopasiMethod * >::const_iterator it = mMethods.constBegin();
  QVector< CCopasiMethod * >::const_iterator end = mMethods.constEnd();

  for (; it != end; ++it)
    if (*it == pMethod) return;

  beginResetModel();
  mMethods.append(pMethod);
  endResetModel();
}

void CQTaskMethodParametersDM::popMethod(CCopasiMethod * pMethod)
{
  QVector< CCopasiMethod * >::iterator it = mMethods.begin();
  QVector< CCopasiMethod * >::iterator end = mMethods.end();

  for (; it != end; ++it)
    if (*it == pMethod)
      {
        beginResetModel();
        mMethods.erase(it);
        endResetModel();
      }
}

void CQTaskMethodParametersDM::setFramework(const int & framework)
{
  beginResetModel();
  mFramework = framework;
  endResetModel();
}

QModelIndex CQTaskMethodParametersDM::index(CCopasiParameter * pNode) const
{
  if (pNode == NULL)
    {
      return QModelIndex();
    }

  if (isMethod(pNode))
    {
      return index(0, 0, QModelIndex());
    }

  QModelIndex Parent = index(static_cast< CCopasiParameter * >(pNode->getObjectParent()));

  return index(getRow(pNode), 0, Parent);
}

bool CQTaskMethodParametersDM::isMethod(CCopasiParameter * pNode) const
{
  QVector< CCopasiMethod * >::const_iterator it = mMethods.constBegin();
  QVector< CCopasiMethod * >::const_iterator end = mMethods.constEnd();

  for (; it != end; ++it)
    if (*it != static_cast< CCopasiMethod * >(pNode)) return true;

  return false;
}

// static
CCopasiParameter * CQTaskMethodParametersDM::nodeFromIndex(const QModelIndex & index)
{
  if (!index.isValid()) return NULL;

  QModelIndex Tmp = index;
  const QAbstractItemModel *pModel = Tmp.model();

  while (pModel->inherits("QSortFilterProxyModel"))
    {
      Tmp = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(Tmp);
      pModel = Tmp.model();
    }

  return static_cast< CCopasiParameter * >(Tmp.internalPointer());
}

int CQTaskMethodParametersDM::getRow(const CCopasiParameter * pNode) const
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

  if (isMethod(pParent))
    {
      QVector< CCopasiMethod * >::const_iterator itMethod = mMethods.constBegin();
      QVector< CCopasiMethod * >::const_iterator endMethod = mMethods.constEnd();

      int i = 0;

      for (; itMethod != endMethod; ++itMethod)
        {
          CCopasiParameterGroup::index_iterator it = pParent->beginIndex();
          CCopasiParameterGroup::index_iterator end = pParent->endIndex();

          for (; it != end; ++it, ++i)
            if (*it == pNode)
              {
                return i;
              }
        }
    }
  else
    {
      int i = 0;

      CCopasiParameterGroup::index_iterator it = pParent->beginIndex();
      CCopasiParameterGroup::index_iterator end = pParent->endIndex();

      for (; it != end; ++it, ++i)
        if (*it == pNode)
          {
            return i;
          }
    }

  return -1;
}

// static
QVariant CQTaskMethodParametersDM::nameData(const CCopasiParameter * pNode, int role)
{
  if (role == Qt::DisplayRole)
    {
      return QVariant(QString(FROM_UTF8(pNode->getObjectName())));
    }

  return QVariant();
}

// static
QVariant CQTaskMethodParametersDM::typeData(const CCopasiParameter * pNode, int role)
{
  return QVariant(pNode->getType());
}

QVariant CQTaskMethodParametersDM::valueData(const CCopasiParameter * pNode, int role)
{
  switch (role)
    {
      case Qt::EditRole:
      case Qt::DisplayRole:
        switch (pNode->getType())
          {
            case CCopasiParameter::DOUBLE:
            case CCopasiParameter::UDOUBLE:
              return QVariant(QString::number(pNode->getValue< C_FLOAT64 >(), 'g', 10));
              break;

            case CCopasiParameter::INT:
              return QVariant(QString::number(pNode->getValue< C_INT32 >()));
              break;

            case CCopasiParameter::UINT:
              return QVariant(QString::number(pNode->getValue< unsigned C_INT32 >()));
              break;

            case CCopasiParameter::BOOL:
              if (role == Qt::DisplayRole)
                return QVariant();
              else
                return QVariant(pNode->getValue< bool >());

              break;

            case CCopasiParameter::GROUP:
              return QVariant(FROM_UTF8(pNode->getObjectName()));
              break;

            case CCopasiParameter::STRING:
            case CCopasiParameter::FILE:
            case CCopasiParameter::EXPRESSION:
            case CCopasiParameter::KEY:
              return QVariant(FROM_UTF8(pNode->getValue< std::string >()));

            case CCopasiParameter::CN:
              return QVariant(FROM_UTF8(pNode->getValue< CRegisteredObjectName >()));
              break;

            default:
              return QVariant();
              break;
          }

        break;

      case Qt::CheckStateRole:
        if (pNode->getType() == CCopasiParameter::BOOL)
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
