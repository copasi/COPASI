// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateWidget.cpp,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/03/23 12:58:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qpushbutton.h>
#include <qlayout.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include "copasi.h"

#include "StateWidget.h"
#include "StateSubwidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CKeyFactory.h"
#include "steadystate/CSteadyStateTask.h"
#include "model/CModel.h"

//#include "report/CKeyFactory.h"
#include "qtUtilities.h"

/*
 *  Constructs a StateWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
StateWidget::StateWidget(QWidget* parent, const char* name, Qt::WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey(""),
    mUpToDate(false)
{
  if (!name)
    setName("StateWidget");

  setCaption(trUtf8("StateWidget"));

  mWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "Layout");
  /*
    buttonSetInitialState = new QPushButton(this, "buttonSetInitialState");
    buttonSetInitialState->setText(trUtf8("Set Results As Next Initial State"));
    mWidgetLayout->addWidget(buttonSetInitialState, 1, 0);
  */
  setInitialState = new QPushButton(this, "setInitialState");
  setInitialState->setText(trUtf8("Set Results As Next Initial State"));
  mWidgetLayout->addWidget(setInitialState, 1, 0);

  mCentralWidget = new StateSubwidget(this, "StateSubwidget");
  mWidgetLayout->addWidget(mCentralWidget, 0, 0);

  /*commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout5->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Revert"));
  Layout5->addWidget(cancelChanges);*/

  // signals and slots connections
  //connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  //connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
StateWidget::~StateWidget()
{}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
bool StateWidget::loadFromBackend()
{
  mUpToDate = true;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CSteadyStateTask * pSteadyStateTask
  = dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

  if (!pSteadyStateTask) return false;

  if (!pSteadyStateTask->getState())
    {
      mCentralWidget->clear();
      return true;
    }

  return mCentralWidget->loadAll(pSteadyStateTask);
}

bool StateWidget::saveToBackend()
{
  return true;
}

bool StateWidget::update(ListViews::ObjectType objectType, ListViews::Action
                         C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (objectType != ListViews::STATE)
    mUpToDate = false;

  // :TODO: update the validity indicator
  // if (this->isShown())
  //   ...;

  return true;
}

bool StateWidget::leave()
{
  return true;
}

bool StateWidget::enter(const std::string & C_UNUSED(key))
{
  // :TODO: update the validity indicator
  // ...;

  return true;
}
