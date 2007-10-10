// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/10 16:24:00 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qtabwidget.h>

#include "CTabWidget.h"
#include "ModelWidget.h"

/*
 *  Constructs a CQPreferenceDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CTabWidget::CTabWidget(QString& label1, QString& label2,
                       QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  if (!name)
    CopasiWidget::setName("CTabWidget");

  mTabWidget = new QTabWidget (this);
  Tab1Widget = new ModelWidget(mTabWidget);
  Tab2Widget = new ModelWidget(mTabWidget);
  mTabWidget->addTab(Tab1Widget, label1);
  mTabWidget->addTab(Tab2Widget, label2);
  Tab1Widget->show();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CTabWidget::~CTabWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

CopasiWidget* CTabWidget::getTab1Widget()
{return Tab1Widget;}

CopasiWidget* CTabWidget::getTab2Widget()
{return Tab2Widget;}
