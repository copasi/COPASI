// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/copasiWidget.cpp,v $
//   $Revision: 1.28 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/24 15:51:21 $
// End CVS Header

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
#include <qvaluelist.h>

#include "copasiWidget.h"
#include "listviews.h"
#include "copasiui3window.h"

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, WFlags f)
    : QWidget (parent, name, f),
    mpListView(static_cast<ListViews *>(parent)),
    mIgnoreUpdates(false),
    mFramework(0)
{}

bool CopasiWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{return true;}

bool CopasiWidget::leave()
{return true;}

bool CopasiWidget::enter(const std::string & C_UNUSED(key))
{return true;}

void CopasiWidget::setFramework(int framework)
{mFramework = framework;}

bool CopasiWidget::protectedNotify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  mIgnoreUpdates = true;
  ListViews::notify(objectType, action, key);
  mIgnoreUpdates = false;

  return true;
}

bool CopasiWidget::getIgnoreUpdates()
{return mIgnoreUpdates;}
void CopasiWidget::setIgnoreUpdates(bool v)
{mIgnoreUpdates = v;}
