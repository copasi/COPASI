// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQLNAWidget.h"

#include "CLNAResultWidget.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "qtUtilities.h"

#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/lna/CLNATask.h"
#include "copasi/lna/CLNAProblem.h"
#include "copasi/lna/CLNAMethod.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/*
 *  Constructs a CQLNAWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQLNAWidget::CQLNAWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQLNAWidget::~CQLNAWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQLNAWidget::slotSteadyStateChecked()
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

bool CQLNAWidget::runTask()
{
  CLNATask * pTask = dynamic_cast< CLNATask * >(mpObject);

  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  return success;
}

bool CQLNAWidget::taskFinishedEvent()
{
  bool success = true;
  CLNAResultWidget *pResult = dynamic_cast< CLNAResultWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::LinearNoiseApproximationResult));

  if (pResult) pResult->loadFromBackend();

  if (success && pResult)
    mpListView->switchToOtherWidget(ListViews::WidgetType::LinearNoiseApproximationResult, std::string()); //change to the results window

  return success;
}

bool CQLNAWidget::loadTaskProtected()
{
  CLNATask * pTask = dynamic_cast< CLNATask * >(mpTask);

  if (!pTask) return false;

  CLNAProblem * pProblem =
    dynamic_cast< CLNAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  mpCheckSteadyState->setChecked(pProblem->isSteadyStateRequested());

  if (mpCheckSteadyState->isChecked())
    {
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

bool CQLNAWidget::saveTaskProtected()
{
  CLNATask * pTask = dynamic_cast< CLNATask * >(mpTask);

  if (!pTask) return false;

  CLNAProblem * pProblem =
    dynamic_cast< CLNAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  if (mpCheckSteadyState->isChecked() != pProblem->isSteadyStateRequested())
    {
      pProblem->setSteadyStateRequested(mpCheckSteadyState->isChecked());
      mChanged = true;
    }

  assert(CRootContainer::getDatamodelList()->size() > 0);

  if (mChanged) mpDataModel->changed();

  mChanged = false;
  return true;
}

void CQLNAWidget::init()
{
  mpHeaderWidget->setTaskName("Linear Noise Approximation");
  mpHeaderWidget->mpUpdateModel->hide();

  vboxLayout->insertWidget(0, mpHeaderWidget);  // header
  // vboxLayout->insertSpacing(1, 14);       // space between header and body

  mpMethodWidget->showMethodParameters(true);
  vboxLayout->addWidget(mpMethodWidget);

  vboxLayout->addWidget(mpBtnWidget);     // 'footer'
}
