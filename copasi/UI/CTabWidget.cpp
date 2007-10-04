// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/10/04 18:13:22 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CTabWidget.h"

/*
 *  Constructs a CQPreferenceDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CTabWidget::CTabWidget(QWidget* parent, QWidget* Tab1Widget,
                       QString& label1, QWidget* Tab2Widget, QString& label2,
                       const char* name, WFlags f)
    : QDialog(parent, name, f)
{
  if (!name)
    setName("CTabWidget");

  this.Tab1Widget = Tab1Widget;
  this.Tab2Widget = Tab2Widget;
  addTab(QWidget* Tab1Widget, label1);
  addTab(QWidget* Tab2Widget, label2);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CTabWidget::~CTabWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

QWidget* CTabWidget::getTab1Widget()
{return Tab1Widget;}

QWidget* CTabWidget::getTab2Widget()
{return Tab2Widget;}
