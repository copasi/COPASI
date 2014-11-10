// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAProblem.h"
#include "steadystate/CMCAMethod.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "report/CCopasiRootContainer.h"

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
  loadParameterTable();
}

bool CQMCAWidget::runTask()
{
  CMCATask * pTask =
    dynamic_cast< CMCATask * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  return success;
}

bool CQMCAWidget::taskFinishedEvent()
{
  bool success = true;
  CMCAResultWidget *pResult = dynamic_cast< CMCAResultWidget * >(mpListView->findWidgetFromId(241));

  if (pResult) pResult->loadFromBackend();

  if (success && pResult)
    mpListView->switchToOtherWidget(241, ""); //change to the results window

  return success;
}

CCopasiMethod * CQMCAWidget::createMethod(const CCopasiMethod::SubType & /* type */)
{return new CMCAMethod;}

bool CQMCAWidget::loadTask()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);

  if (!pTask) return false;

  loadCommon();
//  loadMethod(); --> we cannot do that because of different structure -- 08.04.09

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  // instead calling loadMethod(), the following codes is used
  mpCheckSteadyState->setChecked(pProblem->isSteadyStateRequested());

  bool success = loadParameterTable();

  mChanged = false;

  return success;
}

bool CQMCAWidget::saveTask()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);

  if (!pTask) return false;

  saveCommon();
  // saveMethod();

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  if (mpCheckSteadyState->isChecked() != pProblem->isSteadyStateRequested())
    {
      pProblem->setSteadyStateRequested(mpCheckSteadyState->isChecked());
      mChanged = true;
    }

  bool success = saveParameterTable();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (mChanged)(*CCopasiRootContainer::getDatamodelList())[0]->changed();

  mChanged = false;
  return success;
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

bool CQMCAWidget::loadParameterTable()
{

  bool init = (mpMethodWidget->mpTableParameter->rowCount() == 0);

  size_t NumRows = mpMethod->size();
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      NumRows += pSteadyStateTask->getMethod()->size();
    }

  mpMethodWidget->mpTableParameter->setRowCount((int) NumRows);

  size_t i, k;
  CCopasiParameter::Type Type;
  QString value;

  for (i = 0; i < mpMethod->size() && init; i++)
    {
      mpMethodWidget->mpTableParameter->setVerticalHeaderItem((int) i, new QTableWidgetItem());
      mpMethodWidget->mpTableParameter->verticalHeaderItem((int) i)->setText(FROM_UTF8(mpMethod->getName(i)));

      value = getParameterValue(mpMethod, i, &Type);
      QTableWidgetItem *itemValue = new QTableWidgetItem(value);
      itemValue->setTextAlignment(Qt::AlignRight);
      mpMethodWidget->mpTableParameter->setItem((int) i, 0, itemValue);
    }

  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      CCopasiMethod * pMethod = pSteadyStateTask->getMethod();

      for (i = mpMethod->size(), k = 0; k < pMethod->size(); k++, i++)
        {
          // create item of the current row and give it a name
          mpMethodWidget->mpTableParameter->setVerticalHeaderItem((int) i, new QTableWidgetItem());
          mpMethodWidget->mpTableParameter->verticalHeaderItem((int) i)->setText(FROM_UTF8(pMethod->getName(k)));

          value = getParameterValue(pMethod, k, &Type);
          QTableWidgetItem *itemValue = new QTableWidgetItem(value);
          itemValue->setTextAlignment(Qt::AlignRight);
          mpMethodWidget->mpTableParameter->setItem((int) i, 0, itemValue);
        }
    }

  // the table will be automatically adjusted -> 31.10.09

  return true;
}

bool CQMCAWidget::saveParameterTable()
{
  size_t i, k;
  QString value;
  CCopasiParameter::Type Type;

  for (i = 0; i < mpMethod->size(); i++)
    {
      value = mpMethodWidget->mpTableParameter->item((int) i, 0)->text();

      if (value != getParameterValue(mpMethod, i, &Type))
        {
          setParameterValue(mpMethod, i, value);
          mChanged = true;
        }
    }

  if (mpCheckSteadyState->isChecked())
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      CCopasiMethod * pMethod = pSteadyStateTask->getMethod();

      for (i = mpMethod->size(), k = 0; k < pMethod->size(); i++, k++)
        {
          value = mpMethodWidget->mpTableParameter->item((int) i, 0)->text();

          if (value != getParameterValue(pMethod, k, &Type))
            {
              setParameterValue(pMethod, k, value);
              mChanged = true;
            }
        }
    }

  return true;
}
