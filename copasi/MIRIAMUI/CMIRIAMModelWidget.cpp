// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CMIRIAMModelWidget.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/25 20:37:26 $
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
#include "UI/qtUtilities.h"

#include "CMIRIAMModelWidget.h"
#include "CCreatorsWidget.h"
#include "CReferencesWidget.h"
#include "CModifiedWidget.h"

/*
 *  Constructs a CMIRIAMModelWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMIRIAMModelWidget::CMIRIAMModelWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f),
    mWidgets(),
    mChanged(false)
{
  if (!name)
    CopasiWidget::setName("CMIRIAMModelWidget");

  //Create new widgets
  QLabel *pLblCreators = new QLabel("Creators: ", this);
  CopasiTableWidget* pCreatorsWidget = new CCreatorsWidget(this, "CreatorsWidgetForModel");
  pLblCreators->setBuddy(pCreatorsWidget);
  mWidgets.push_back(pCreatorsWidget);

  QLabel *pLblReferences = new QLabel("References: ", this);
  CopasiTableWidget* pReferencesWidget = new CReferencesWidget(this, "ReferencesWidgetForModel");
  pLblReferences->setBuddy(pReferencesWidget);
  mWidgets.push_back(pReferencesWidget);

  QLabel *pLblCreated = new QLabel("Created: ", this);
  mpCreatedWidget = new QDateTimeEdit(this, "CreatedWidgetForModel");
  pLblCreated->setBuddy(mpCreatedWidget);
  mpCreatedWidget->dateEdit()->setRange(QDate(), QDate::currentDate());

  QLabel *pLblModified = new QLabel("Modified: ", this);
  CopasiTableWidget* pModifiedsWidget = new CModifiedWidget(this, "ModifiedWidgetForModel");
  pLblModified->setBuddy(pModifiedsWidget);
  mWidgets.push_back(pModifiedsWidget);

  btnOK = new QPushButton("Commit", this);
  btnCancel = new QPushButton("Revert", this);
  btnDelete = new QPushButton("Delete/Undelete", this);
  btnNew = new QPushButton("New", this);
  btnClear = new QPushButton("Clear", this);

  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 6);
  vBoxLayout->addWidget(pLblCreators);
  vBoxLayout->addWidget(pCreatorsWidget);
  vBoxLayout->addWidget(pLblReferences);
  vBoxLayout->addWidget(pReferencesWidget);

  QHBoxLayout* hLayoutDT = new QHBoxLayout(vBoxLayout, 0);
  hLayoutDT->addWidget(pLblCreated);
  hLayoutDT->addWidget(mpCreatedWidget);
  hLayoutDT->addStretch();
  hLayoutDT->addWidget(pLblModified);
  hLayoutDT->addWidget(pModifiedsWidget);

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

  connect(pCreatorsWidget, SIGNAL(setEnableOKAndCancel(bool)), this,
          SLOT(slotEnableOKAndCancel(bool)));
  connect(pCreatorsWidget, SIGNAL(delKeyPressed()), this,
          SLOT(slotBtnDeleteClicked()));

  connect(pReferencesWidget, SIGNAL(setEnableOKAndCancel(bool)), this,
          SLOT(slotEnableOKAndCancel(bool)));
  connect(pReferencesWidget, SIGNAL(delKeyPressed()), this,
          SLOT(slotBtnDeleteClicked()));

  connect(mpCreatedWidget, SIGNAL(valueChanged(const QDateTime &)), this,
          SLOT(slotCreatedValueChanged(const QDateTime &)));

  connect(pModifiedsWidget, SIGNAL(setEnableOKAndCancel(bool)), this,
          SLOT(slotEnableOKAndCancel(bool)));
  connect(pModifiedsWidget, SIGNAL(delKeyPressed()), this,
          SLOT(slotBtnDeleteClicked()));
}

void CMIRIAMModelWidget::slotBtnOKClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
  {(*it)->slotBtnOKClicked();}

  std::string dt = "";
  if (mpCreatedWidget->dateTime().toString(Qt::ISODate).ascii())
  {dt = mpCreatedWidget->dateTime().toString(Qt::ISODate).ascii();}
  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().setCreatedDT(dt);
}

void CMIRIAMModelWidget::slotBtnCancelClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
  {(*it)->slotBtnCancelClicked();}
  mpCreatedWidget->setDateTime(QDateTime::fromString(FROM_UTF8(CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getCreatedDT()), Qt::ISODate));
}

void CMIRIAMModelWidget::slotBtnClearClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    {
      if ((*it)->isTableInFocus())
      {(*it)->slotBtnClearClicked();}
    }
}

void CMIRIAMModelWidget::slotBtnDeleteClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    {
      if ((*it)->isTableInFocus())
      {(*it)->slotBtnDeleteClicked();}
    }
}

void CMIRIAMModelWidget::slotBtnNewClicked()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
    {
      if ((*it)->isTableInFocus())
      {(*it)->slotBtnNewClicked();}
    }
}

void CMIRIAMModelWidget::slotEnableOKAndCancel(bool e)
{
  btnOK->setEnabled(e);
  btnCancel->setEnabled(e);
}

void CMIRIAMModelWidget::slotCreatedValueChanged(const QDateTime & C_UNUSED(dt))
{slotEnableOKAndCancel(true);}

bool CMIRIAMModelWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
  {(*it)->update(objectType, action, key);}
  mpCreatedWidget->setDateTime(QDateTime::fromString(FROM_UTF8(CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getCreatedDT()), Qt::ISODate));
  return true;
}

bool CMIRIAMModelWidget::enter(const std::string & key)
{
  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().loadGraph(key);
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
  {(*it)->enter(key);}
  return true;
}

bool CMIRIAMModelWidget::leave()
{
  std::vector<CopasiTableWidget*>::const_iterator it = mWidgets.begin();
  std::vector<CopasiTableWidget*>::const_iterator end = mWidgets.end();
  for (; it != end; it++)
  {(*it)->leave();}

  CCopasiDataModel::Global->getModel()->getMIRIAMInfo().saveGraph();
  return true;
}
