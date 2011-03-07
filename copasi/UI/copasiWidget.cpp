// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiWidget.cpp,v $
//   $Revision: 1.35 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:50 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// copasiWidget.cpp: implementation of the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////
#include <qapplication.h>
#include <q3valuelist.h>

#include "copasiWidget.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "copasiui3window.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiRootContainer.h"

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, Qt::WFlags f)
    : QWidget(parent, name, f),
    mpListView(NULL),
    mKey(),
    mpObject(NULL),
    mpDataModel(NULL),
    mIgnoreUpdates(false),
    mFramework(0)
{
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
