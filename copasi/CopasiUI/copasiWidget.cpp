/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/copasiWidget.cpp,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/20 13:18:05 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// copasiWidget.cpp: implementation of the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////

#include "copasiWidget.h"
#include "listviews.h"
#include "qvaluelist.h"

DataModelGUI* CopasiWidget::dataModel = NULL;

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, WFlags f)
    : QWidget (parent, name, f),
    mIgnoreUpdates(false)
{
  pListView = (ListViews*)parent;
  dataModel = ListViews::getDataModel();
}

bool CopasiWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{return true;}

bool CopasiWidget::leave()
{return true;}

bool CopasiWidget::enter(const std::string & C_UNUSED(key))
{return true;}

bool CopasiWidget::protectedNotify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  mIgnoreUpdates = true;
  ListViews::notify(objectType, action, key);
  mIgnoreUpdates = false;

  return true;
}
