// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQParameterOverviewDM.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/30 18:01:35 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQParameterOverviewDM.cpp
 *
 *  Created on: Jan 9, 2012
 *      Author: shoops
 */

#include "CQParameterOverviewDM.h"
#include "qtUtilities.h"

#include "model/CModelParameterSet.h"

#define COL_NAME       0
#define COL_DIFF       1
#define COL_TYPE       2
#define COL_VALUE      3
#define COL_UNIT       4
#define COL_ASSIGNMENT 5

#define COLUMN_COUNT   6

CQParameterOverviewDM::CQParameterOverviewDM(QObject * pParent):
    QAbstractItemModel(pParent),
    mpModelParameterSet(NULL),
    mFramework(0)
{
}

// virtual
CQParameterOverviewDM::~CQParameterOverviewDM()
{
}

// virtual
int CQParameterOverviewDM::columnCount(const QModelIndex & /* parent */) const
{
  return COLUMN_COUNT;
}

// virtual
QVariant CQParameterOverviewDM::data(const QModelIndex & index, int role) const
{
  CModelParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL) return QVariant();

  switch (index.column())
    {
      case COL_NAME:
        return nameData(pNode, role);
        break;

      case COL_DIFF:
        return diffData(pNode, role);
        break;

      case COL_TYPE:
        return typeData(pNode, role);
        break;

      case COL_VALUE:
        return valueData(pNode, role);
        break;

      case COL_UNIT:
        return unitData(pNode, role);
        break;

      case COL_ASSIGNMENT:
        return assignmentData(pNode, role);
        break;
    }

  return QVariant();
}

// virtual
Qt::ItemFlags CQParameterOverviewDM::flags(const QModelIndex &index) const
{
  CModelParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL)
    {
      return Qt::ItemIsEnabled;
    }

  if (index.column() == COL_VALUE &&
      !pNode->isReadOnly())
    {
      return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

// virtual
QModelIndex CQParameterOverviewDM::index(int row, int column, const QModelIndex & parent) const
{
  CModelParameterGroup * pParent = static_cast< CModelParameterGroup *>(nodeFromIndex(parent));

  if (pParent == NULL) return createIndex(row, column, static_cast< CModelParameter * >(mpModelParameterSet));

  std::cout << *pParent << std::endl;

  if (row < (int) pParent->size())
    return createIndex(row, column, *(pParent->begin() + row));
  else
    return QModelIndex();
}

// virtual
QModelIndex CQParameterOverviewDM::parent(const QModelIndex & index) const
{
  CModelParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL || pNode == mpModelParameterSet)
    {
      return QModelIndex();
    }

  CModelParameter * pParent = static_cast< CModelParameter * >(pNode->getParent());
  std::cout << *pParent << std::endl;

  return createIndex(getRow(pParent), 0, pParent);
}

// virtual
int CQParameterOverviewDM::rowCount(const QModelIndex & parent) const
{
  if (!parent.isValid())
    {
      if (mpModelParameterSet != NULL)
        return 1;
      else
        return 0;

    }

  CModelParameter * pParent = nodeFromIndex(parent);

  switch (pParent->getType())
    {
      case CModelParameter::Group:
      case CModelParameter::Set:
        return (int) static_cast< CModelParameterGroup * >(pParent) ->size();
        break;

      default:
        break;
    }

  return 0;
}

// virtual
bool CQParameterOverviewDM::setData(const QModelIndex &index, const QVariant &value, int role)
{
  CModelParameter * pNode = nodeFromIndex(index);

  if (pNode != NULL &&
      index.column() == COL_VALUE &&
      role == Qt::EditRole)
    {
      pNode->setValue(value.toDouble(), static_cast< CModelParameter::Framework >(mFramework));
    }

  return false;
}

void CQParameterOverviewDM::setModelParameterset(CModelParameterSet * pModelParameterSet)
{
  if (mpModelParameterSet != pModelParameterSet)
    {
      beginResetModel();
      mpModelParameterSet = pModelParameterSet;
      endResetModel();
    }
}

void CQParameterOverviewDM::setFramework(const int & framework)
{
  mFramework = framework;
}

QModelIndex CQParameterOverviewDM::index(CModelParameter * pNode) const
{
  if (pNode == NULL)
    {
      return QModelIndex();
    }

  if (pNode == mpModelParameterSet)
    {
      return index(0, 0, QModelIndex());
    }

  QModelIndex Parent = index(static_cast< CModelParameter * >(pNode->getParent()));

  return index(getRow(pNode), 0, Parent);
}

// static
CModelParameter * CQParameterOverviewDM::nodeFromIndex(const QModelIndex & index)
{
  if (!index.isValid()) return NULL;

  QModelIndex Tmp = index;
  const QAbstractItemModel *pModel = Tmp.model();

  while (pModel->inherits("QSortFilterProxyModel"))
    {
      Tmp = static_cast< const QSortFilterProxyModel *>(pModel)->mapToSource(index);
      pModel = Tmp.model();
    }

  if (Tmp.internalPointer())
    std::cout << *static_cast< CModelParameter * >(Tmp.internalPointer()) << std::endl;

  return static_cast< CModelParameter * >(Tmp.internalPointer());
}

// static
int CQParameterOverviewDM::getRow(const CModelParameter * pNode)
{
  if (pNode == NULL)
    {
      return -1;
    }

  CModelParameterGroup * pParent = pNode->getParent();

  if (pParent == NULL)
    {
      return 0;
    }

  CModelParameterGroup::const_iterator it = pParent->begin();
  CModelParameterGroup::const_iterator end = pParent->end();

  for (int i; it != end; ++it, ++i)
    {
      if (*it == pNode)
        {
          return i;
        }
    }

  return -1;
}

// static
QVariant CQParameterOverviewDM::nameData(const CModelParameter * pNode, int role)
{
  if (role == Qt::DisplayRole)
    {
      return QVariant(QString(FROM_UTF8(pNode->getName())));
    }

  return QVariant();
}

// static
QVariant CQParameterOverviewDM::diffData(const CModelParameter * pNode, int role)
{
  return QVariant();
}

// static
QVariant CQParameterOverviewDM::typeData(const CModelParameter * pNode, int role)
{
  return QVariant();
}

QVariant CQParameterOverviewDM::valueData(const CModelParameter * pNode, int role) const
{
  switch (pNode->getType())
    {
      case CModelParameter::Group:
      case CModelParameter::Set:
        break;

      default:

        if (role == Qt::EditRole)
          return QVariant(QString::number(pNode->getValue(static_cast< CModelParameter::Framework >(mFramework)), 'g', 10));
        else if (role == Qt::DisplayRole)
          return QVariant(pNode->getValue(static_cast< CModelParameter::Framework >(mFramework)));

        break;
    }

  return QVariant();
}

// static
QVariant CQParameterOverviewDM::unitData(const CModelParameter * pNode, int role)
{
  return QVariant();
}

// static
QVariant CQParameterOverviewDM::assignmentData(const CModelParameter * pNode, int role)
{
  if (role == Qt::DisplayRole)
    {
      return QVariant(QString(FROM_UTF8(pNode->getInitialExpression())));
    }

  return QVariant();
}
