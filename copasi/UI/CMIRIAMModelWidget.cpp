// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CMIRIAMModelWidget.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/08 22:26:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qpushbutton.h>

#include "CMIRIAMModelWidget.h"
#include "CAuthorsWidget.h"

/*
 *  Constructs a CMIRIAMModelWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMIRIAMModelWidget::CMIRIAMModelWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  if (!name)
    CopasiWidget::setName("CMIRIAMModelWidget");

  //Create new widgets
  mAuthorsWidget = new CAuthorsWidget(this, "CAuthorsWidgetForModel");

  btnOK = new QPushButton("Commit", this);
  btnCancel = new QPushButton("Revert", this);
  btnDelete = new QPushButton("Delete/Undelete", this);
  btnNew = new QPushButton("New", this);
  btnClear = new QPushButton("Clear", this);

  //Layout Widgets
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 6);
  vBoxLayout->addWidget(mAuthorsWidget);

  QHBoxLayout* hLayout = new QHBoxLayout(vBoxLayout, 0);

  hLayout->addWidget(btnOK);
  hLayout->addSpacing(5);
  hLayout->addWidget(btnCancel);
  hLayout->addStretch();
  hLayout->addWidget(btnClear);
  hLayout->addSpacing(5);
  hLayout->addWidget(btnDelete);
  hLayout->addSpacing(5);
  hLayout->addWidget(btnNew);

  // signals and slots connections
  connect(btnOK, SIGNAL(clicked ()), this,
          SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this,
          SLOT(slotBtnCancelClicked()));
  connect(btnDelete, SIGNAL(clicked ()), this,
          SLOT(slotBtnDeleteClicked()));
  connect(btnClear, SIGNAL(clicked ()), this,
          SLOT(slotBtnClearClicked()));
  connect(btnNew, SIGNAL(clicked ()), this,
          SLOT(slotBtnNewClicked()));

  connect(mAuthorsWidget, SIGNAL(setEnableOKAndCancel(bool)), this,
          SLOT(slotEnableOKAndCancel(bool)));
  connect(mAuthorsWidget, SIGNAL(delKeyPressed()), this,
          SLOT(slotBtnDeleteClicked()));
}

void CMIRIAMModelWidget::slotBtnOKClicked()
{
  mAuthorsWidget->slotBtnOKClicked();
}

void CMIRIAMModelWidget::slotBtnCancelClicked()
{
  mAuthorsWidget->slotBtnCancelClicked();
}

void CMIRIAMModelWidget::slotBtnClearClicked()
{
  mAuthorsWidget->slotBtnClearClicked();
}

void CMIRIAMModelWidget::slotBtnDeleteClicked()
{
  mAuthorsWidget->slotBtnDeleteClicked();
}

void CMIRIAMModelWidget::slotBtnNewClicked()
{
  mAuthorsWidget->slotBtnNewClicked();
}

void CMIRIAMModelWidget::slotEnableOKAndCancel(bool e)
{
  btnOK->setEnabled(e);
  btnCancel->setEnabled(e);
}

bool CMIRIAMModelWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  mAuthorsWidget->update(objectType, action, key);
  return true;
}

bool CMIRIAMModelWidget::enter(const std::string & key)
{
  mAuthorsWidget->enter(key);
  return true;
}

bool CMIRIAMModelWidget::leave()
{
  mAuthorsWidget->leave();
  return true;
}
