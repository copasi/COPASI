/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SteadyStateWidget.cpp,v $
   $Revision: 1.111 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/06 16:03:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qfiledialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>

#include "DataModelGUI.h"

#include "SteadyStateWidget.h"
#include "listviews.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CProgressBar.h"
#include "StateWidget.h"

#include "copasi.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"

/**
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, WFlags fl)
    : TaskWidget(parent, name, fl)
{
  if (!name)
    setName("SteadyStateWidget");
  setCaption(trUtf8("SteadyStateWidget"));

  //if a mpMethodLayout is created here, it will be used by addMethodXXX() below.
  mpMethodLayout = new QGridLayout(this, 1, 1, 11, 6, "mpMethodLayout");

  //set the task name and add the name widget to the layout
  mpHeaderWidget->setTaskName("Steady State");
  addHeaderToGrid();

  QSpacerItem* spacer2 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  mpMethodLayout->addItem(spacer2, 1, 1);

  //*************************

  taskJacobian = new QCheckBox(this, "taskJacobian");
  taskJacobian->setText(trUtf8("calculate Jacobian"));
  mpMethodLayout->addWidget(taskJacobian, 3, 1);

  taskStability = new QCheckBox(this, "taskStability");
  taskStability->setText(trUtf8("perform Stability Analysis"));
  mpMethodLayout->addWidget(taskStability, 3, 2);
  taskStability->setEnabled(false);

  addHLineToGrid(mpMethodLayout, 4, 2);

  //************* parameter table ****************
  addMethodParameterTable(10, 5);
  //addMethodParameterTableToLayout(5, 2);

  /*QSpacerItem* spacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TaskWidgetLayout->addMultiCell(spacer_3, 7, 7, 0, 2);*/

  //*******************************************

  mpMethodLayout->addMultiCellWidget(mpBtnWidget, 11, 11, 0, 2);

  // signals and slots connections
  //connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(taskJacobian, SIGNAL(toggled(bool)), this, SLOT(taskJacobianToggled()));

  // tab order
  //setTabOrder(taskName, bExecutable);
  //setTabOrder(bExecutable, setInitialState);
  //setTabOrder(setInitialState, taskJacobian);
  setTabOrder(taskJacobian, taskStability);
  //setTabOrder(taskStability, parameterTable);
  //setTabOrder(parameterTable, bRunButton);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{}

CCopasiMethod * SteadyStateWidget::createMethod(const CCopasiMethod::SubType & /*type*/)
{return NULL; /*CTSSMethod::createTSSMethod(type);*/}

bool SteadyStateWidget::runTask()
{
  if (!commonBeforeRunTask()) return false;

  bool success = true;
  if (!commonRunTask()) success = false;

  if (!commonAfterRunTask()) success = false;

  StateWidget *pResult = dynamic_cast< StateWidget * >(pListView->findWidgetFromId(211));
  if (pResult) pResult->loadFromBackend();

  if (success && isShown()) pListView->switchToOtherWidget(211, ""); //change to the results window

  return success;
}

bool SteadyStateWidget::loadTask()
{
  loadCommon();
  loadMethod();

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(mObjectKey));
  assert(mSteadyStateTask);

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());
  assert(steadystateproblem);

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());
  assert(steadystatemethod);

  bool bJacobian = steadystateproblem->isJacobianRequested();
  bool bStatistics = steadystateproblem->isStabilityAnalysisRequested();
  taskJacobian->setChecked(bJacobian);
  if (bJacobian)
    {
      taskStability->setEnabled(true);
      taskStability->setChecked(bStatistics);
    }

  return true;
}

bool SteadyStateWidget::saveTask()
{
  saveCommon();
  saveMethod();

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(mObjectKey));
  assert(mSteadyStateTask);

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());
  assert(steadystateproblem);

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());
  assert(steadystatemethod);

  CCopasiDataModel::Global->getModel()->compileIfNecessary();
  //steadystateproblem->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

  bool bJacobian = taskJacobian->isChecked();
  bool bStatistics = taskStability->isChecked();

  steadystateproblem->setJacobianRequested(bJacobian);
  steadystateproblem->setStabilityAnalysisRequested(bStatistics);

  //loadSteadyStateTask();

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();
  return true;
}

void SteadyStateWidget::taskJacobianToggled()
{
  if (!taskJacobian->isChecked())
    {
      taskStability->setChecked(false);
      taskStability->setEnabled(false);
    }
  else taskStability->setEnabled(true);
}
