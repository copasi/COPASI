// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// copasiWidget.cpp: implementation of the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////
#include <QApplication>

#include "copasi/UI/copasiWidget.h"
#include "copasi/UI/listviews.h"
#include "copasi/UI/DataModelGUI.h"
#include "copasi/UI/copasiui3window.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "CQSortFilterProxyModel.h"

CopasiWidget::CopasiWidget(QWidget *parent, const char *name, Qt::WindowFlags f)
  : QWidget(parent, f),
    mpListView(NULL),
    mpObject(NULL),
    mpDataModel(NULL),
    mObjectType(ListViews::ObjectType::RESULT),
    mObjectCN(),
    mIgnoreUpdates(false),
    mFramework(0),
    mOldCN()
{
  setObjectName(name);
  initContext();
}

bool CopasiWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  // Assure that the object still exists
  CObjectInterface::ContainerList List;
  List.push_back(mpDataModel);

  // This will check the current data model and the root container for the object;
  mpObject = const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mObjectCN)));

  bool success = updateProtected(objectType, action, cn != mOldCN ? cn : mObjectCN);
  mOldCN = mObjectCN;

  return success;
}

bool CopasiWidget::leave()
{
  CObjectInterface::ContainerList List;
  List.push_back(mpDataModel);

  // This will check the current data model and the root container for the object;
  mpObject = const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mObjectCN)));

  if (mpObject != NULL)
    {
      bool success = leaveProtected();
      mOldCN = mObjectCN;

      return success;
    }

  return true;
}

bool CopasiWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  return false;
}

bool CopasiWidget::leaveProtected()
{
  return true;
}

void CopasiWidget::setFilterExpression(CQSortFilterProxyModel * model, bool empty, QString Filter)
{
  if (!model)
    return;

  if (empty)
    {
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
      model->setFilterRegExp(QRegExp());
#else
      model->setFilterRegularExpression(QRegularExpression());
#endif
      return;
    }

#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
  QRegExp regExp(Filter, Qt::CaseInsensitive, QRegExp::RegExp);
  model->setFilterRegExp(regExp);
#else
  QRegularExpression regExp(Filter, QRegularExpression::CaseInsensitiveOption);
  model->setFilterRegularExpression(regExp);
#endif
}

void CopasiWidget::refresh()
{
  leave();
  qApp->processEvents();
  enter(mObjectCN);
}

bool CopasiWidget::enter(const CCommonName & cn)
{
  if (mpListView == NULL)
    {
      initContext();
    }

  mObjectCN = cn;
  mOldCN = cn;

  CObjectInterface::ContainerList List;
  List.push_back(mpDataModel);

  // This will check the current data model and the root container for the object;
  mpObject = const_cast< CDataObject * >(CObjectInterface::DataObject(CObjectInterface::GetObjectFromCN(List, mObjectCN)));
  mObjectType = mpObject != NULL ? ListViews::DataObjectType.toEnum(mpObject->getObjectType(), ListViews::ObjectType::RESULT) : ListViews::ObjectType::RESULT;

  return enterProtected();
}

const CDataObject * CopasiWidget::getObject() const
{
  return mpObject;
}

CQBaseDataModel * CopasiWidget::getCqDataModel()
{
  return NULL;
}

bool CopasiWidget::enterProtected()
{
  return true;
}

void CopasiWidget::setFramework(int framework)
{mFramework = framework;}

bool CopasiWidget::protectedNotify(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  bool notifyRun = false;

  if (!mIgnoreUpdates)
    {
      mIgnoreUpdates = true;
      mpListView->getDataModelGUI()->notify(objectType, action, cn);
      notifyRun = true;
    }

  mIgnoreUpdates = false;
  return notifyRun;
}

// virtual
void CopasiWidget::slotNotifyChanges(const CUndoData::CChangeSet & changes)
{
  if (!mIgnoreUpdates)
    {
      mIgnoreUpdates = true;
      mpListView->getDataModelGUI()->notifyChanges(changes);
    }

  mIgnoreUpdates = false;
}

bool CopasiWidget::getIgnoreUpdates()
{
  return mIgnoreUpdates;
}

void CopasiWidget::setIgnoreUpdates(bool v)
{
  mIgnoreUpdates = v;
}

CDataModel *CopasiWidget::getDataModel() const
{
  return mpDataModel;
}

void CopasiWidget::initContext()
{
  QObject *pParent = parent();

  if (pParent == NULL) return;

  if (mpListView == NULL)
    while (pParent != NULL &&
           (mpListView = dynamic_cast< ListViews * >(pParent)) == NULL)
      {
        pParent = pParent->parent();
      }

  if (mpDataModel == NULL &&
      mpListView != NULL)
    mpDataModel = mpListView->getDataModel();
}
