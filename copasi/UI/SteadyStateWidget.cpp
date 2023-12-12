// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "DataModelGUI.h"

#include "SteadyStateWidget.h"
#include "listviews.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "CQSteadyStateResult.h"

#include "copasi/copasi.h"
#include "qtUtilities.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/report/CKeyFactory.h"

/**
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : TaskWidget(parent, name, fl)
{
  setupUi(this);

  init();
  retranslateUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{}

void SteadyStateWidget::init()
{
  mpHeaderWidget->setTaskName("Steady State");

  SteadyStateWidgetLayout->insertWidget(0, mpHeaderWidget); // header
  // SteadyStateWidgetLayout->insertSpacing(1, 14);      // space between header and body

  mpMethodWidget->showMethodParameters(true);
  mpMethodWidget->showMethodCheckbox(false);
  SteadyStateWidgetLayout->addWidget(mpMethodWidget);

  SteadyStateWidgetLayout->addWidget(mpBtnWidget);      // 'footer'
}

bool SteadyStateWidget::runTask()
{
  bool success = true;

  if (!commonBeforeRunTask()) return false;

  if (!commonRunTask()) success = false;

  return success;
}

bool SteadyStateWidget::taskFinishedEvent()
{
  bool success = false;

  CSteadyStateTask* pSteadyStateTask = dynamic_cast<CSteadyStateTask *>(mpObject);
  CCopasiMethod * pMethod = NULL;

  if (pSteadyStateTask == NULL)
    return success;

  switch (pSteadyStateTask->getResult())
    {
      case CSteadyStateMethod::found:
      case CSteadyStateMethod::foundEquilibrium:
        success = true;
        break;

      case CSteadyStateMethod::foundNegative:

        if ((pMethod = pSteadyStateTask->getMethod()) != NULL)
          {
            const CCopasiParameter *pParm = pMethod->getParameter("Accept Negative Concentrations");

            if (pParm != NULL)
              {
                success = pParm->getValue< bool >();
              }
          }

        break;

      default:
        break;
    }

  CQSteadyStateResult *pResult =
    dynamic_cast< CQSteadyStateResult * >(mpListView->createWidgetFromId(ListViews::WidgetType::SteadyStateResult));

  if (pResult)
    pResult->loadResult();

  if (success && isVisible())
    mpListView->switchToOtherWidget(ListViews::WidgetType::SteadyStateResult, std::string()); //change to the results window

  return success;
}

bool SteadyStateWidget::loadTaskProtected()
{
  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(mpObject);

  if (mSteadyStateTask == NULL)
    return false;

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());

  if (steadystateproblem == NULL)
    return false;

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());

  if (steadystatemethod == NULL)
    return false;

  bool bJacobian = steadystateproblem->isJacobianRequested();
  bool bStatistics = steadystateproblem->isStabilityAnalysisRequested();
  taskJacobian->setChecked(bJacobian);

  if (bJacobian)
    {
      taskStability->setEnabled(true);
      taskStability->setChecked(bStatistics);
    }

  mChanged = false;

  return true;
}

bool SteadyStateWidget::saveTaskProtected()
{
  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(mpObject);

  if (mSteadyStateTask == NULL)
    return false;

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());

  if (steadystateproblem == NULL)
    return false;

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());

  if (steadystatemethod == NULL)
    return false;

  bool bJacobian = taskJacobian->isChecked();
  bool bStatistics = taskStability->isChecked();

  steadystateproblem->setJacobianRequested(bJacobian);
  steadystateproblem->setStabilityAnalysisRequested(bStatistics);

  if (mChanged)
    {
      if (mpDataModel != NULL)
        {
          mpDataModel->changed();
        }

      mChanged = false;
    }

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
