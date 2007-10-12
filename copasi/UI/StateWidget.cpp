// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateWidget.cpp,v $
//   $Revision: 1.17 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/10/12 18:35:35 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qpushbutton.h>
#include <qlayout.h>
#include "copasi.h"

#include "StateWidget.h"
#include "StateSubwidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "steadystate/CSteadyStateTask.h"
#include "model/CModel.h"

//#include "report/CKeyFactory.h"
#include "qtUtilities.h"

/*
 *  Constructs a StateWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
StateWidget::StateWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey(""),
    mUpToDate(false)
{
  if (!name)
    setName("StateWidget");
  setCaption(trUtf8("StateWidget"));

  setInitialState = new QPushButton(this, "setInitialState");
  setInitialState->setText(trUtf8("SetResultsAsNextInitialState"));
  connect(setInitialState, SIGNAL(clicked()), this, SLOT(runSetInitialState()));

  parentLayout = new QVBoxLayout(this, 0, 0, "parentLayout");
  stateLayout = new QHBoxLayout(0, 0 , 6, "StateLayout");
  mWidgetLayout = new QGridLayout(NULL, 1, 1, 0, -1, "Layout");

  mCentralWidget = new StateSubwidget(this, "StateSubwidget");
  mWidgetLayout->addWidget(mCentralWidget, 0, 0);

  //parentLayout->addLayout(stateLayout);
  parentLayout->addLayout(mWidgetLayout);
  stateLayout->addWidget(setInitialState);

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
  mCentralWidget->showUnits();
  CSteadyStateTask * pSteadyStateTask
  = dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);

  if (!pSteadyStateTask) return false;
  if (!pSteadyStateTask->getState()) return mCentralWidget->clear();
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
