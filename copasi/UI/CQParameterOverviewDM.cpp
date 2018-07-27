// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QCommonStyle>
#include "model/CModel.h"
#include "copasi/UI/copasiWidget.h"
#include "copasi/utilities/CValidatedUnit.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#define COL_NAME       0
#define COL_DIFF       1
#define COL_TYPE       2
#define COL_UNIT       4
#define COL_ASSIGNMENT 5

#define COLUMN_COUNT   6

CQParameterOverviewDM::CQParameterOverviewDM(QObject * pParent)
  : CQBaseDataModel(pParent, NULL)
  , mpModelParameterSet(NULL)
  , mFramework(0)
{}

// virtual
CQParameterOverviewDM::~CQParameterOverviewDM()
{}

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
      if (pNode->getCompareResult() != CModelParameter::CompareResult::Identical &&
          pNode->getType() != CModelParameter::Type::Group &&
          pNode->getType() != CModelParameter::Type::Set)
        {
          emit signalOpenEditor(index);

          return QAbstractItemModel::flags(index)  | Qt::ItemIsEditable | Qt::ItemIsEnabled;
        }

      emit signalCloseEditor(index);
    }

  if (index.column() == COL_ASSIGNMENT)
    {
      if (pNode->getType() == CModelParameter::Type::ReactionParameter)
        {
          return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
        }
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
      pParent = mpModelParameterSet->toGroup();
    }

  if (pParent != NULL && row < (int) pParent->size())
    return createIndex(row, column, *(pParent->begin() + row));
  else
    return QModelIndex();
}

// virtual
QModelIndex CQParameterOverviewDM::parent(const QModelIndex & index) const
{
  CModelParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL || pNode == mpModelParameterSet->toGroup())
    {
      return QModelIndex();
    }

  if (pNode->getParent() == mpModelParameterSet->toGroup())
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
      case CModelParameter::Type::Reaction:
      case CModelParameter::Type::Group:
      case CModelParameter::Type::Set:
        return (int) static_cast< CModelParameterGroup * >(pParent) ->size();
        break;

      default:
        break;
    }

  return 0;
}

void CQParameterOverviewDM::setModelParameterSet(CModelParameterSet * pModelParameterSet)
{
  if (mpModelParameterSet != pModelParameterSet)
    {
      beginResetModel();
      mpModelParameterSet = pModelParameterSet;
      mUnitCache.clear();
      endResetModel();
    }
}

void CQParameterOverviewDM::setFramework(const int & framework)
{
  beginResetModel();
  mFramework = framework;
  mUnitCache.clear();
  endResetModel();
}

QModelIndex CQParameterOverviewDM::index(CModelParameter * pNode, int column) const
{
  if (pNode == NULL)
    {
      return QModelIndex();
    }

  if (pNode == mpModelParameterSet->toGroup())
    {
      return QModelIndex();
    }

  QModelIndex Parent = index(static_cast< CModelParameter * >(pNode->getParent()), 0);

  return index(getRow(pNode), column, Parent);
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
  if (pNode->getType() == CModelParameter::Type::Group ||
      pNode->getType() == CModelParameter::Type::Set)
    {
      return QVariant();
    }

  switch (role)
    {
      case Qt::UserRole:

        switch (pNode->getCompareResult())
          {
            case CModelParameter::CompareResult::Obsolete:
              return QVariant(CQIconResource::icon(CQIconResource::parameterObsolete));
              break;

            case CModelParameter::CompareResult::Missing:
              return QVariant(CQIconResource::icon(CQIconResource::parameterMissing));
              break;

            case CModelParameter::CompareResult::Modified:
              return QVariant(CQIconResource::icon(CQIconResource::parameterModified));
              break;

            case CModelParameter::CompareResult::Conflict:
              return QVariant(CQIconResource::icon(CQIconResource::warning));
              break;

            case CModelParameter::CompareResult::Identical:
              return QVariant();
              break;
          }

        break;

      case Qt::ToolTipRole:

        switch (pNode->getCompareResult())
          {
            case CModelParameter::CompareResult::Obsolete:
              return QVariant(QString("The item is no longer present in the model. \n\n"
                                      "Click to remove from the set."));
              break;

            case CModelParameter::CompareResult::Missing:
              return QVariant(QString("The item is present in the model but is missing in the parameter set. \n\n"
                                      "Click to add to the set."));
              break;

            case CModelParameter::CompareResult::Modified:
              return QVariant(QString("The item's value differs from the current model. \n\n"
                                      "Click to update the sets value."));
              break;

            case CModelParameter::CompareResult::Conflict:
              return QVariant(QString("The item's value cannot be assigned to the model object since the\n"
                                      "object is determined by an assignment. \n\n"
                                      "Click to resolve conflict."));
              break;

            case CModelParameter::CompareResult::Identical:
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
      case CModelParameter::Type::Reaction:
      case CModelParameter::Type::Group:
      case CModelParameter::Type::Set:
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
      case CModelParameter::Type::Reaction:
      case CModelParameter::Type::Group:
      case CModelParameter::Type::Set:
        break;

      default:

        if (role == Qt::EditRole)
          return QVariant(convertToQString(pNode->getValue(static_cast< CCore::Framework >(mFramework))));
        else if (role == Qt::DisplayRole)
          return QVariant(pNode->getValue(static_cast< CCore::Framework >(mFramework)));

        break;
    }

  return QVariant();
}

QVariant CQParameterOverviewDM::unitData(const CModelParameter * pNode, int role) const
{
  if (pNode->getType() == CModelParameter::Type::Group)
    return QVariant();

  CValidatedUnit Unit = pNode->getUnit(static_cast< CCore::Framework >(mFramework));

  std::set< CValidatedUnit >::const_iterator it = mUnitCache.find(Unit);

  if (it == mUnitCache.end())
    {
      Unit.buildExpression();
      it = mUnitCache.insert(Unit).first;
    }

  switch (role)
    {
      case Qt::DecorationRole:
        if (it->conflict())
          return QCommonStyle().standardIcon(QStyle::SP_MessageBoxWarning);

        break;

      case Qt::ToolTipRole:
        if (it->conflict())
          {
            CValidity Validity;
            Validity.add(CIssue(CIssue::eSeverity::Warning, CIssue::eKind::UnitConflict));
            return FROM_UTF8(Validity.getIssueMessages());
          }

        break;

      case Qt::DisplayRole:
        return FROM_UTF8(it->getExpression());
        break;
    }

  return QVariant();
}

// static
QVariant CQParameterOverviewDM::assignmentData(const CModelParameter * pNode, int role)
{
  if (role == Qt::DisplayRole)
    {
      if (pNode->getType() == CModelParameter::Type::ReactionParameter)
        {
          CCommonName GlobalQuantityCN = static_cast< const CModelParameterReactionParameter *>(pNode)->getGlobalQuantityCN();
          const CModelParameter * pGlobalQuantity = pNode->getSet()->getModelParameter(GlobalQuantityCN);

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

// virtual
bool CQParameterOverviewDM::setData(const QModelIndex & index, const QVariant &value, int role)
{
  CModelParameter * pNode = nodeFromIndex(index);

  if (pNode == NULL || role != Qt::EditRole)
    return false;

  if (index.data() == value)
    return false;

  bool success = false;
  CDataObject * pObject = NULL;

  if (pNode != NULL &&
      role == Qt::EditRole)
    {
      switch (index.column())
        {
          case COL_VALUE:
            if (mpModelParameterSet->isActive() &&
                (pObject = pNode->getObject()) != NULL)
              {
                CData OldData(pObject->toData());
                pNode->setValue(value.toDouble(), static_cast<CCore::Framework>(mFramework));
                CUndoData UndoData;
                pObject->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast<CCore::Framework>(mFramework));
                emit signalNotifyChanges(pObject->getObjectDataModel()->recordData(UndoData));

                success = true;
              }
            else
              {
                // The changes are recorded when we commit
                pNode->setValue(value.toDouble(), static_cast<CCore::Framework>(mFramework));
              }

            break;

          case COL_ASSIGNMENT:
          {
            const CModelParameter * pGlobalQuantity = mpModelParameterSet->getModelParameter(mpModelParameterSet->getModel()->getModelValues().getCN() + "[" + CCommonName::escape(TO_UTF8(value.toString())) + "]");

            if (mpModelParameterSet->isActive() &&
                (pObject = pNode->getObject()) != NULL)
              {
                // We update the referenced object directly as the active parameter set updates the model values
                // We need to work on the reaction itself since this involves parameter mapping.
                CReaction * pReaction = dynamic_cast< CReaction * >(pObject->getObjectAncestor("Reaction"));

                if (pReaction == NULL)
                  {
                    return false;
                  }

                CData OldData(pReaction->toData());
                static_cast<CModelParameterReactionParameter *>(pNode)->setGlobalQuantityCN(pGlobalQuantity != NULL ? pGlobalQuantity->getCN() : CCommonName());
                pNode->setValue(value.toDouble(), static_cast<CCore::Framework>(mFramework));
                CUndoData UndoData;
                pReaction->createUndoData(UndoData, CUndoData::Type::CHANGE, OldData, static_cast<CCore::Framework>(mFramework));
                emit signalNotifyChanges(pObject->getObjectDataModel()->recordData(UndoData));

                success = true;
              }
            else
              {
                // The changes are recorded when we commit
                static_cast<CModelParameterReactionParameter *>(pNode)->setGlobalQuantityCN(pGlobalQuantity != NULL ? pGlobalQuantity->getCN() : CCommonName());
                pNode->setValue(value.toDouble(), static_cast<CCore::Framework>(mFramework));
              }
          }

          break;
        }
    }

  return success;
}

bool CQParameterOverviewDM::insertRows(int /*position*/, int /*rows*/, const QModelIndex & /*source*/)
{
  return false;
}

bool CQParameterOverviewDM::removeRows(int /*position*/, int /*rows*/, const QModelIndex & /* parent */)
{
  return false;
}

// virtual
void CQParameterOverviewDM::resetCacheProtected()
{
  mUnitCache.clear();
}
