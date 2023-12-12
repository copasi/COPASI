// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQMCAWidget.h"

#include "CMCAResultWidget.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "qtUtilities.h"

#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/steadystate/CMCAProblem.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/*
 *  Constructs a CQMCAWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMCAWidget::CQMCAWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMCAWidget::~CQMCAWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQMCAWidget::slotSteadyStateChecked()
{
  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>(&mpDataModel->getTaskList()->operator[]("Steady-State"));

      if (pSteadyStateTask != NULL)
        {
          mpMethodWidget->pushMethod(pSteadyStateTask->getMethod());
        }
    }
  else
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>(&mpDataModel->getTaskList()->operator[]("Steady-State"));

      if (pSteadyStateTask != NULL)
        {
          mpMethodWidget->popMethod(pSteadyStateTask->getMethod());
        }
    }
}

bool CQMCAWidget::runTask()
{
  CMCATask * pTask =
    dynamic_cast< CMCATask * >(mpObject);

  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  return success;
}

bool CQMCAWidget::taskFinishedEvent()
{
  bool success = true;
  CMCAResultWidget *pResult = dynamic_cast< CMCAResultWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::MetabolicControlAnalysisResult));

  if (pResult) pResult->loadFromBackend();

  if (success && pResult)
    mpListView->switchToOtherWidget(ListViews::WidgetType::MetabolicControlAnalysisResult, std::string()); //change to the results window

  return success;
}

bool CQMCAWidget::loadTaskProtected()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);

  if (!pTask) return false;

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  mpCheckSteadyState->setChecked(pProblem->isSteadyStateRequested());

  if (mpCheckSteadyState->isChecked())
    {
      assert(mpDataModel != NULL);
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>(&mpDataModel->getTaskList()->operator[]("Steady-State"));

      if (pSteadyStateTask != NULL)
        {
          mpMethodWidget->pushMethod(pSteadyStateTask->getMethod());
        }
    }

  mChanged = false;

  return true;
}

bool CQMCAWidget::saveTaskProtected()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);

  if (!pTask) return false;

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  if (mpCheckSteadyState->isChecked() != pProblem->isSteadyStateRequested())
    {
      pProblem->setSteadyStateRequested(mpCheckSteadyState->isChecked());
      mChanged = true;
    }

  assert(mpDataModel != NULL);

  if (mChanged) mpDataModel->changed();

  mChanged = false;
  return true;
}

void CQMCAWidget::init()
{
  mpHeaderWidget->setTaskName("Metabolic Control Analysis");
  mpHeaderWidget->mpUpdateModel->hide();

  vboxLayout->insertWidget(0, mpHeaderWidget);  // header
  // vboxLayout->insertSpacing(1, 14);       // space between header and body

  mpMethodWidget->showMethodParameters(true);
  vboxLayout->addWidget(mpMethodWidget);

  vboxLayout->addWidget(mpBtnWidget);     // 'footer'
}
