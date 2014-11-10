// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QtGui/QApplication>

#ifdef COPASI_UNDO
#include <QUndoStack>
#endif

#include "copasi/UI/copasiWidget.h"
#include "copasi/UI/listviews.h"
#include "copasi/UI/DataModelGUI.h"
#include "copasi/UI/copasiui3window.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, Qt::WFlags f)
  : QWidget(parent, f),
    mpListView(NULL),
    mKey(),
    mpObject(NULL),
    mpDataModel(NULL),
    mIgnoreUpdates(false),
    mFramework(0)
{
  setObjectName(name);
  QObject *pParent = parent;

  while (pParent != NULL &&
         (mpListView = dynamic_cast< ListViews * >(pParent)) == NULL)
    {
      pParent = pParent->parent();
    }

  assert(mpListView != NULL);
}

bool CopasiWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{return true;}

bool CopasiWidget::leave()
{return true;}

bool CopasiWidget::enter(const std::string & key)
{
  mKey = key;
  mpObject = CCopasiRootContainer::getKeyFactory()->get(key);

  if (mpObject != NULL)
    {
      mpDataModel = mpObject->getObjectDataModel();
    }
  else
    {
      mpDataModel = NULL;
    }

  return enterProtected();
}

bool CopasiWidget::enterProtected()
{
  return true;
}

void CopasiWidget::setFramework(int framework)
{mFramework = framework;}

bool CopasiWidget::protectedNotify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  bool notifyRun = false;

  if (!mIgnoreUpdates)
    {
      mIgnoreUpdates = true;
      mpListView->getDataModel()->notify(objectType, action, key);
      notifyRun = true;
    }

  mIgnoreUpdates = false;

  return notifyRun;
}

bool CopasiWidget::getIgnoreUpdates()
{
  return mIgnoreUpdates;
}

void CopasiWidget::setIgnoreUpdates(bool v)
{
  mIgnoreUpdates = v;
}

CCopasiDataModel * CopasiWidget::getDataModel()
{
  return mpDataModel;
}

#ifdef COPASI_UNDO
void CopasiWidget::setUndoStack(QUndoStack* undoStack)
{
  mpUndoStack = undoStack;
}
QUndoStack* CopasiWidget::getUndoStack()
{
  return mpUndoStack;
}
#endif
