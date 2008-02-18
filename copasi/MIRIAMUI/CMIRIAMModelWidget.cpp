// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CMIRIAMModelWidget.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/18 16:27:44 $
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
  mpAuthorsWidget = new CAuthorsWidget(this, "AuthorsWidgetForModel");
  pLblAuthors->setBuddy(mpAuthorsWidget);

  QLabel *pLblPublications = new QLabel("Publications: ", this);
  mpPublicationsWidget = new CPublicationsWidget(this, "PublicationsWidgetForModel");
  pLblPublications->setBuddy(mpPublicationsWidget);

  QLabel *pLblCreated = new QLabel("Created: ", this);
  mpCreatedWidget = new QDateTimeEdit(this, "CreatedWidgetForModel");
  pLblCreated->setBuddy(mpCreatedWidget);
  mpCreatedWidget->setFixedWidth(200);
  mpCreatedWidget->dateEdit()->setRange(QDate(), QDate::currentDate());

  btnOK = new QPushButton("Commit", this);
  btnCancel = new QPushButton("Revert", this);
  btnDelete = new QPushButton("Delete/Undelete", this);
  btnNew = new QPushButton("New", this);
  btnClear = new QPushButton("Clear", this);

  //Layout Widgets
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 6);
  vBoxLayout->addWidget(pLblAuthors);
  vBoxLayout->addWidget(mpAuthorsWidget);

  vBoxLayout->addWidget(pLblPublications);
  vBoxLayout->addWidget(mpPublicationsWidget);

  vBoxLayout->addWidget(pLblCreated);
  vBoxLayout->addWidget(mpCreatedWidget);

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

  connect(mpAuthorsWidget, SIGNAL(setEnableOKAndCancel(bool)), this,
          SLOT(slotEnableOKAndCancel(bool)));
  connect(mpAuthorsWidget, SIGNAL(delKeyPressed()), this,
          SLOT(slotBtnDeleteClicked()));

  connect(mpPublicationsWidget, SIGNAL(setEnableOKAndCancel(bool)), this,
          SLOT(slotEnableOKAndCancel(bool)));
  connect(mpPublicationsWidget, SIGNAL(delKeyPressed()), this,
          SLOT(slotBtnDeleteClicked()));

  connect(mpCreatedWidget, SIGNAL(valueChanged(const QDateTime &)), this,
          SLOT(slotCreatedValueChanged(const QDateTime &)));
}

void CMIRIAMModelWidget::slotBtnOKClicked()
{
  mpAuthorsWidget->slotBtnOKClicked();
  mpPublicationsWidget->slotBtnOKClicked();

  std::string dt = "";
  if (mpCreatedWidget->dateTime().toString(Qt::ISODate).ascii())
  {dt = mpCreatedWidget->dateTime().toString(Qt::ISODate).ascii();}
  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().setCreatedDT(dt);
}

void CMIRIAMModelWidget::slotBtnCancelClicked()
{
  mpAuthorsWidget->slotBtnCancelClicked();
  mpPublicationsWidget->slotBtnCancelClicked();
  mpCreatedWidget->setDateTime(QDateTime::fromString(CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getCreatedDT().c_str(), Qt::ISODate));
}

void CMIRIAMModelWidget::slotBtnClearClicked()
{
  if (mpAuthorsWidget->isTableInFocus())
  {mpAuthorsWidget->slotBtnClearClicked();}
  else if (mpPublicationsWidget->isTableInFocus())
  {mpPublicationsWidget->slotBtnClearClicked();}
}

void CMIRIAMModelWidget::slotBtnDeleteClicked()
{
  if (mpAuthorsWidget->isTableInFocus())
  {mpAuthorsWidget->slotBtnDeleteClicked();}
  else if (mpPublicationsWidget->isTableInFocus())
  {mpPublicationsWidget->slotBtnDeleteClicked();}
}

void CMIRIAMModelWidget::slotBtnNewClicked()
{
  if (mpAuthorsWidget->isTableInFocus())
  {mpAuthorsWidget->slotBtnNewClicked();}
  else if (mpPublicationsWidget->isTableInFocus())
  {mpPublicationsWidget->slotBtnNewClicked();}
}

void CMIRIAMModelWidget::slotEnableOKAndCancel(bool e)
{
  btnOK->setEnabled(e);
  btnCancel->setEnabled(e);
}

void CMIRIAMModelWidget::slotCreatedValueChanged(const QDateTime & dt)
{slotEnableOKAndCancel(true);}

bool CMIRIAMModelWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  mpAuthorsWidget->update(objectType, action, key);
  mpPublicationsWidget->update(objectType, action, key);
  mpCreatedWidget->setDateTime(QDateTime::fromString(CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getCreatedDT().c_str(), Qt::ISODate));
  return true;
}

bool CMIRIAMModelWidget::enter(const std::string & key)
{
  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().loadGraph(key);
  mpAuthorsWidget->enter(key);
  mpPublicationsWidget->enter(key);
  return true;
}

bool CMIRIAMModelWidget::leave()
{
  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().saveGraph();
  mpAuthorsWidget->leave();
  mpPublicationsWidget->leave();
  return true;
}
