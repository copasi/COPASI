// Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include "function/CExpression.h"
#include "resourcesUI/CQIconResource.h"

#ifdef COPASI_UNDO
#include <QUndoStack>
#include "model/CModel.h"
#include "undoFramework/ParameterOverviewDataChangeCommand.h"
#endif

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

  if (index.column() == COL_DIFF)
    {
      if (pNode->getCompareResult() != CModelParameter::Identical &&
          pNode->getType() != CModelParameter::Group &&
          pNode->getType() != CModelParameter::Set)
        {
          emit signalOpenEditor(index);

          return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        }

      emit signalCloseEditor(index);
    }

  if (index.column() == COL_ASSIGNMENT)
    {
      if (pNode->getType() == CModelParameter::ReactionParameter)
        {
          emit signalOpenEditor(index);

          return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        }

      emit signalCloseEditor(index);
    }

  return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

// virtual
QVariant CQParameterOverviewDM::headerData(int section, Qt::Orientation /* orientation */, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (section)
    {
      case COL_NAME:
        return QVariant("Name");
        break;

      case COL_DIFF:
        return QVariant("");
        break;

      case COL_TYPE:
        return QVariant("Type");
        break;

      case COL_VALUE:
        return QVariant("Value");
        break;

      case COL_UNIT:
        return QVariant("Unit");
        break;

      case COL_ASSIGNMENT:
        return QVariant("Expression");
        break;
    }

  return QVariant();
}

// virtual
QModelIndex CQParameterOverviewDM::index(int row, int column, const QModelIndex & parent) const
{
  CModelParameterGroup * pParent = static_cast< CModelParameterGroup *>(nodeFromIndex(parent));

  if (pParent == NULL)
    {
      return createIndex(row, column, *(mpModelParameterSet->begin() + row));
    }

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

  if (pNode->getParent() == mpModelParameterSet)
    {
      return QModelIndex();
    }

  CModelParameter * pParent = static_cast< CModelParameter * >(pNode->getParent());

  return createIndex(getRow(pParent), 0, pParent);
}

// virtual
int CQParameterOverviewDM::rowCount(const QModelIndex & parent) const
{
  if (!parent.isValid())
    {
      if (mpModelParameterSet != NULL)
        return 5;
      else
        return 0;
    }

  CModelParameter * pParent = nodeFromIndex(parent);

  switch (pParent->getType())
    {
      case CModelParameter::Reaction:
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
bool CQParameterOverviewDM::setData(const QModelIndex &_index, const QVariant &value, int role)
{
#ifdef COPASI_UNDO

  if (role != Qt::EditRole) return false;

  if (_index.data(Qt::EditRole) == value)
    return false;
  else
    mpUndoStack->push(new ParameterOverviewDataChangeCommand(_index, value, role, this));

#else
  CModelParameter * pNode = nodeFromIndex(_index);
  bool success = false;

  if (pNode != NULL &&
      role == Qt::EditRole)
    {
      switch (_index.column())
        {
          case COL_VALUE:
            pNode->setValue(value.toDouble(), static_cast< CModelParameter::Framework >(mFramework));
            success = true;
            break;

          case COL_ASSIGNMENT:
          {
            CModelParameter * pGlobalQuantity = pNode->getSet()->getModelParameter(TO_UTF8(value.toString()), CModelParameter::ModelValue);

            if (pGlobalQuantity != NULL)
              {
                static_cast< CModelParameterReactionParameter * >(pNode)->setGlobalQuantityCN(pGlobalQuantity->getCN());
              }
            else
              {
                static_cast< CModelParameterReactionParameter * >(pNode)->setGlobalQuantityCN("");
              }
          }

          success = true;
          break;
        }
    }

  return success;
#endif
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
  if (mpModelParameterSet != NULL)
    {
      beginResetModel();
      mFramework = framework;
      endResetModel();
    }
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

  for (int i = 0; it != end; ++it, ++i)
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
  if (pNode->getType() == CModelParameter::Group ||
      pNode->getType() == CModelParameter::Set)
    {
      return QVariant();
    }

  switch (role)
    {
      case Qt::UserRole:

        switch (pNode->getCompareResult())
          {
            case CModelParameter::Obsolete:
              return QVariant(CQIconResource::icon(CQIconResource::parameterObsolete));
              break;

            case CModelParameter::Missing:
              return QVariant(CQIconResource::icon(CQIconResource::parameterMissing));
              break;

            case CModelParameter::Modified:
              return QVariant(CQIconResource::icon(CQIconResource::parameterModified));
              break;

            case CModelParameter::Conflict:
              return QVariant(CQIconResource::icon(CQIconResource::parameterConflict));
              break;

            case CModelParameter::Identical:
              return QVariant();
              break;
          }

        break;

      case Qt::ToolTipRole:

        switch (pNode->getCompareResult())
          {
            case CModelParameter::Obsolete:
              return QVariant(QString("The item is no longer present in the model. \n\n"
                                      "Click to remove from the set."));
              break;

            case CModelParameter::Missing:
              return QVariant(QString("The item is present in the model but is missing in the parameter set. \n\n"
                                      "Click to add to the set."));
              break;

            case CModelParameter::Modified:
              return QVariant(QString("The item's value differs from the current model. \n\n"
                                      "Click to update the sets value."));
              break;

            case CModelParameter::Conflict:
              return QVariant(QString("The item's value cannot be assigned to the model object since the\n"
                                      "object is determined by an assignment. \n\n"
                                      "Click to resolve conflict."));
              break;

            case CModelParameter::Identical:
              return QVariant(QString("The item's value is identical with the current model."));
              break;
          }

        break;

      case Qt::SizeHintRole:
        return QVariant(QSize(20, 20));
        break;
    }

  return QVariant();
}

// static
QVariant CQParameterOverviewDM::typeData(const CModelParameter * pNode, int role)
{
  switch (pNode->getType())
    {
      case CModelParameter::Reaction:
      case CModelParameter::Group:
      case CModelParameter::Set:
        break;

      default:

        if (role == Qt::DisplayRole)
          {
            return QVariant(QString(FROM_UTF8(CModelEntity::StatusName[pNode->getSimulationType()])));
          }

        break;
    }

  return QVariant();
}

QVariant CQParameterOverviewDM::valueData(const CModelParameter * pNode, int role) const
{
  switch (pNode->getType())
    {
      case CModelParameter::Reaction:
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

QVariant CQParameterOverviewDM::unitData(const CModelParameter * pNode, int role) const
{
  if (role == Qt::DisplayRole)
    {
      return QVariant(QString(FROM_UTF8(pNode->getUnit(static_cast< CModelParameter::Framework >(mFramework)))));
    }

  return QVariant();
}

// static
QVariant CQParameterOverviewDM::assignmentData(const CModelParameter * pNode, int role)
{
  if (role == Qt::DisplayRole)
    {
      if (pNode->getType() == CModelParameter::ReactionParameter)
        {
          CCopasiObjectName GlobalQuantityCN = static_cast< const CModelParameterReactionParameter *>(pNode)->getGlobalQuantityCN();
          CModelParameter * pGlobalQuantity = pNode->getSet()->getModelParameter(GlobalQuantityCN);

          if (pGlobalQuantity != NULL)
            {
              return QVariant(QString(FROM_UTF8(pGlobalQuantity->getName())));
            }

          return QVariant(QString(FROM_UTF8(GlobalQuantityCN)));
        }

      const CExpression* pExpression = pNode->getInitialExpressionPtr();

      if (pExpression != NULL)
        return QVariant(QString(FROM_UTF8(pExpression->getDisplayString())));
      else
        return QVariant(QString(FROM_UTF8(pNode->getInitialExpression())));
    }

  return QVariant();
}

#ifdef COPASI_UNDO
bool CQParameterOverviewDM::parameterOverviewDataChange(const QModelIndex& _index, const QVariant &value, int role)
{
  CModelParameter * pNode = nodeFromIndex(_index);
  bool success = false;

  if (pNode != NULL &&
      role == Qt::EditRole)
    {
      switch (_index.column())
        {
          case COL_VALUE:
            pNode->setValue(value.toDouble(), static_cast< CModelParameter::Framework >(mFramework));
            success = true;
            break;

          case COL_ASSIGNMENT:
          {
            CModelParameter * pGlobalQuantity = pNode->getSet()->getModelParameter(TO_UTF8(value.toString()), CModelParameter::ModelValue);

            if (pGlobalQuantity != NULL)
              {
                static_cast< CModelParameterReactionParameter * >(pNode)->setGlobalQuantityCN(pGlobalQuantity->getCN());
              }
            else
              {
                static_cast< CModelParameterReactionParameter * >(pNode)->setGlobalQuantityCN("");
              }
          }

          success = true;
          break;
        }
    }

  emit changeWidget(118);

  return success;
}

void CQParameterOverviewDM::setUndoStack(QUndoStack* undoStack)
{
  mpUndoStack = undoStack;
}
QUndoStack* CQParameterOverviewDM::getUndoStack()
{
  return mpUndoStack;
}
#endif
