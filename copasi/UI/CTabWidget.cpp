// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/31 23:24:26 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qtabwidget.h>
#include <qlayout.h>

#include "CTabWidget.h"
#include "ModelWidget.h"
#include "CMIRIAMModelWidget.h"

/*
 *  Constructs a CTabWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'. label1 and label2
 *  are the tab names.
 */
CTabWidget::CTabWidget(const QString& label1, const QString& label2,
                       QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  if (!name)
    CopasiWidget::setName("CTabWidget");

  QHBoxLayout* tabLayout = new QHBoxLayout(this, 0, 0, "tabLayout");
  mTabWidget = new QTabWidget (this, "mTabWidget");
  tabLayout->addWidget(mTabWidget);

  Tab1Widget = new ModelWidget(mTabWidget);
  Tab2Widget = new CMIRIAMModelWidget(mTabWidget);

  mTabWidget->addTab(Tab1Widget, label1);
  mTabWidget->addTab(Tab2Widget, label2);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CTabWidget::~CTabWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

bool CTabWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  if (Tab1Widget)
    {
      Tab1Widget->update(objectType, action, key);
    }

  if (Tab2Widget)
    {
      Tab2Widget->update(objectType, action, key);
    }
  return true;
}

CopasiWidget* CTabWidget::getTab1Widget()
{return Tab1Widget;}

CopasiWidget* CTabWidget::getTab2Widget()
{return Tab2Widget;}
