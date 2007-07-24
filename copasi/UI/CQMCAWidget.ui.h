// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMCAWidget.ui.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/07/24 18:40:20 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include <qmessagebox.h>
#include <qtable.h>

#include "CMCAResultWidget.h"
#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "UI/CProgressBar.h"
#include "UI/qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAProblem.h"
#include "steadystate/CMCAMethod.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"

void CQMCAWidget::slotSteadyStateChecked()
{
  loadParameterTable();
}

bool CQMCAWidget::runTask()
{
  CMCATask * pTask =
    dynamic_cast< CMCATask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  commonAfterRunTask();

  CMCAResultWidget *pResult = dynamic_cast< CMCAResultWidget * >(pListView->findWidgetFromId(241));
  if (pResult) pResult->loadFromBackend();

  if (success && pResult)
    pListView->switchToOtherWidget(241, ""); //change to the results window

  return success;
}

CCopasiMethod * CQMCAWidget::createMethod(const CCopasiMethod::SubType & /* type */)
{return new CMCAMethod;}

bool CQMCAWidget::loadTask()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);
  if (!pTask) return false;

  loadCommon();

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());
  if (!pProblem) return false;

  mpCheckSteadyState->setChecked(pProblem->isSteadyStateRequested());

  mpTblParameter->setNumRows(0);
  bool success = loadParameterTable();

  mChanged = false;
  return success;
}

bool CQMCAWidget::saveTask()
{
  CMCATask * pTask = dynamic_cast< CMCATask * >(mpTask);
  if (!pTask) return false;

  saveCommon();
  saveMethod();

  CMCAProblem * pProblem =
    dynamic_cast< CMCAProblem * >(mpTask->getProblem());
  if (!pProblem) return false;

  if (mpCheckSteadyState->isChecked() != pProblem->isSteadyStateRequested())
    {
      pProblem->setSteadyStateRequested(mpCheckSteadyState->isChecked());
      mChanged = true;
    }

  bool success = saveParameterTable();

  if (mChanged) CCopasiDataModel::Global->changed();

  mChanged = false;
  return success;
}

void CQMCAWidget::init()
{
  mpHeaderWidget->setTaskName("Metabolic Control Analysis");
  mpHeaderWidget->mpUpdateModel->hide();

  CQMCAWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQMCAWidgetLayout->addWidget(mpBtnWidget);

  addMethodParameterTable(0, 0);
}

bool CQMCAWidget::loadParameterTable()
{
  bool init = (mpTblParameter->numRows() == 0);

  unsigned C_INT32 NumRows = mpMethod->size();
  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      NumRows += pSteadyStateTask->getMethod()->size();
    }

  mpTblParameter->setNumRows(NumRows);
  QHeader *rowHeader = mpTblParameter->verticalHeader();

  unsigned C_INT32 i, k;
  CCopasiParameter::Type Type;
  QString value;

  for (i = 0; i < mpMethod->size() && init; i++)
    {
      rowHeader->setLabel(i, FROM_UTF8(mpMethod->getName(i)));

      value = getParameterValue(mpMethod, i, &Type);
      mpTblParameter->setText(i, 0, value);
    }

  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      CCopasiMethod * pMethod = pSteadyStateTask->getMethod();

      for (i = mpMethod->size(), k = 0; k < pMethod->size(); k++, i++)
        {
          rowHeader->setLabel(i, FROM_UTF8(pMethod->getName(k)));

          value = getParameterValue(pMethod, k, &Type);
          mpTblParameter->setText(i, 0, value);
        }
    }

  return true;
}

bool CQMCAWidget::saveParameterTable()
{
  unsigned C_INT32 i, k;
  QString value;
  CCopasiParameter::Type Type;

  for (i = 0; i < mpMethod->size(); i++)
    {
      value = mpTblParameter->text(i, 0);
      if (value != getParameterValue(mpMethod, i, &Type))
        {
          setParameterValue(mpMethod, i, value);
          mChanged = true;
        }
    }

  if (mpCheckSteadyState->isChecked())
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);

      if (!pSteadyStateTask) return false;

      CCopasiMethod * pMethod = pSteadyStateTask->getMethod();

      for (i = mpMethod->size(), k = 0; k < pMethod->size(); i++, k++)
        {
          value = mpTblParameter->text(i, 0);
          if (value != getParameterValue(pMethod, k, &Type))
            {
              setParameterValue(pMethod, k, value);
              mChanged = true;
            }
        }
    }

  return true;
}
