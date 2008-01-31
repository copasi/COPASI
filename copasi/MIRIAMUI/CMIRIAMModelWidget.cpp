// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CMIRIAMModelWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/01/31 05:01:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#include "CMIRIAMModelWidget.h"
#include "CAuthorsWidget.h"
#include "CPublicationsWidget.h"

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
  QLabel *pLblAuthors = new QLabel("Creators: ", this);
  mAuthorsWidget = new CAuthorsWidget(this, "AuthorsWidgetForModel");
  pLblAuthors->setBuddy(mAuthorsWidget);

  QLabel *pLblPublications = new QLabel("Publications: ", this);
  mPublicationsWidget = new CPublicationsWidget(this, "PublicationsWidgetForModel");
  pLblPublications->setBuddy(mPublicationsWidget);

  btnOK = new QPushButton("Commit", this);
  btnCancel = new QPushButton("Revert", this);
  btnDelete = new QPushButton("Delete/Undelete", this);
  btnNew = new QPushButton("New", this);
  btnClear = new QPushButton("Clear", this);

  //Layout Widgets
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 6);
  vBoxLayout->addWidget(pLblAuthors);
  vBoxLayout->addWidget(mAuthorsWidget);

  vBoxLayout->addWidget(pLblPublications);
  vBoxLayout->addWidget(mPublicationsWidget);

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

  connect(mPublicationsWidget, SIGNAL(setEnableOKAndCancel(bool)), this,
          SLOT(slotEnableOKAndCancel(bool)));
  connect(mPublicationsWidget, SIGNAL(delKeyPressed()), this,
          SLOT(slotBtnDeleteClicked()));
}

void CMIRIAMModelWidget::slotBtnOKClicked()
{
  mAuthorsWidget->slotBtnOKClicked();
  mPublicationsWidget->slotBtnOKClicked();
}

void CMIRIAMModelWidget::slotBtnCancelClicked()
{
  mAuthorsWidget->slotBtnCancelClicked();
  mPublicationsWidget->slotBtnCancelClicked();
}

void CMIRIAMModelWidget::slotBtnClearClicked()
{
  if (mAuthorsWidget->isTableInFocus())
  {mAuthorsWidget->slotBtnClearClicked();}
  else if (mPublicationsWidget->isTableInFocus())
  {mPublicationsWidget->slotBtnClearClicked();}
}

void CMIRIAMModelWidget::slotBtnDeleteClicked()
{
  if (mAuthorsWidget->isTableInFocus())
  {mAuthorsWidget->slotBtnDeleteClicked();}
  else if (mPublicationsWidget->isTableInFocus())
  {mPublicationsWidget->slotBtnDeleteClicked();}
}

void CMIRIAMModelWidget::slotBtnNewClicked()
{
  if (mAuthorsWidget->isTableInFocus())
  {mAuthorsWidget->slotBtnNewClicked();}
  else if (mPublicationsWidget->isTableInFocus())
  {mPublicationsWidget->slotBtnNewClicked();}
}

void CMIRIAMModelWidget::slotEnableOKAndCancel(bool e)
{
  btnOK->setEnabled(e);
  btnCancel->setEnabled(e);
}

bool CMIRIAMModelWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  mAuthorsWidget->update(objectType, action, key);
  mPublicationsWidget->update(objectType, action, key);
  return true;
}

bool CMIRIAMModelWidget::enter(const std::string & key)
{
  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().loadGraph(key);
  mAuthorsWidget->enter(key);
  mPublicationsWidget->enter(key);
  return true;
}

bool CMIRIAMModelWidget::leave()
{
  mAuthorsWidget->leave();
  mPublicationsWidget->leave();
  return true;
}
