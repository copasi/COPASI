// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQOptimizationWidget.ui.h,v $
//   $Revision: 1.27.2.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/04 15:06:55 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlabel.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qlayout.h>

#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "UI/CQFittingItemWidget.h"
#include "UI/CProgressBar.h"
#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"
#include "UI/CQExpressionWidget.h"

#include "report/CKeyFactory.h"
#include "optimization/COptTask.h"
#include "optimization/COptItem.h"
#include "optimization/COptMethod.h"
#include "optimization/COptProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiException.h"

bool CQOptimizationWidget::saveTask()
{
  COptTask * pTask =
    dynamic_cast< COptTask * >(mpTask);
  if (!pTask) return false;

  saveCommon();
  saveMethod();

  COptProblem * pProblem =
    dynamic_cast<COptProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  // expression
  //  if (pProblem->getObjectiveFunction() != ((CQExpressionWidget *)mpEditExpression->widget(0))->getExpression())
  if (pProblem->getObjectiveFunction() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
      //      if (!pProblem->setObjectiveFunction(((CQExpressionWidget *)mpEditExpression->widget(0))->getExpression()))
      if (!pProblem->setObjectiveFunction(mpExpressionEMW->mpExpressionWidget->getExpression()))
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
          return false;
        }

      mChanged = true;
    }

  if (mpBoxSubtask->currentText() != FROM_UTF8(CCopasiTask::TypeName[pProblem->getSubtaskType()]))
    {
      mChanged = true;
      pProblem->setSubtaskType((CCopasiTask::Type) mSubtaskMap[(const char *) mpBoxSubtask->currentText().utf8()]);
    }

  if (mpCheckMaximize->isChecked() != pProblem->maximize())
    {
      mChanged = true;
      pProblem->setMaximize(mpCheckMaximize->isChecked());
    }

  mChanged |= mpParameters->save(NULL, NULL);
  mChanged |= mpConstraints->save(NULL, NULL);

  if (mChanged) CCopasiDataModel::Global->changed();

  mChanged = false;

  return true;
}

bool CQOptimizationWidget::loadTask()
{
  COptTask * pTask =
    dynamic_cast< COptTask * >(mpTask);
  if (!pTask) return false;

  loadCommon();
  loadMethod();

  COptProblem * pProblem =
    dynamic_cast<COptProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  // expression
  mpExpressionEMW->mpExpressionWidget->setExpression(pProblem->getObjectiveFunction());
  mpExpressionEMW->updateWidget();

  mpCheckMaximize->setChecked(pProblem->maximize());

  mpBoxSubtask->setCurrentText(FROM_UTF8(CCopasiTask::TypeName[pProblem->getSubtaskType()]));

  mpParameters->load(pProblem->getGroup("OptimizationItemList"), NULL, NULL);

  mpConstraints->load(pProblem->getGroup("OptimizationConstraintList"), NULL, NULL);

  mChanged = false;

  return true;
}

bool CQOptimizationWidget::runTask()
{
  // --- expression

  mpExpressionEMW->updateWidget();

  // ----

  COptTask * pTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  commonAfterRunTask();

  return success;
}

void CQOptimizationWidget::slotPageChange(QWidget * currentPage)
{
  if (mpTabWidget->tabLabel(currentPage).contains("Parameters", true))
    mpCurrentList = mpParameters;
  else
    mpCurrentList = mpConstraints;
}

CCopasiMethod * CQOptimizationWidget::createMethod(const CCopasiMethod::SubType & type)
{return COptMethod::createMethod(type);}

void CQOptimizationWidget::slotParameterNumberChanged(int number)
{
  QString TabLabel = "Parameters (" + QString::number(number) + ")";
  mpTabWidget->setTabLabel(mpParametersPage, TabLabel);
}

void CQOptimizationWidget::slotConstraintNumberChanged(int number)
{
  QString TabLabel = "Constraints (" + QString::number(number) + ")";
  mpTabWidget->setTabLabel(mpConstraintsPage, TabLabel);
}

void CQOptimizationWidget::init()
{
  std::string taskName = "Optimization";

  mpHeaderWidget->setTaskName(taskName);

  //  mpExpressionEMW->mpExpressionWidget->setName(FROM_UTF8(taskName));

  //  mpExpressionEMW->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::OBJECTIVE_EXPRESSION);
  mpExpressionEMW->mpExpressionWidget->setExpressionType(CCopasiSimpleSelectionTree::OPTIMIZATION_EXPRESSION);

  CQOptimizationWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQOptimizationWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(COptTask::ValidMethods);
  addMethodParameterTable();

  mpBoxSubtask->insertItem(FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::steadyState]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::steadyState]] = CCopasiTask::steadyState;
  mpBoxSubtask->insertItem(FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::timeCourse]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::timeCourse]] = CCopasiTask::timeCourse;
  mpBoxSubtask->insertItem(FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::mca]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::mca]] = CCopasiTask::mca;
  mpBoxSubtask->insertItem(FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::lyap]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::lyap]] = CCopasiTask::lyap;
  mpBoxSubtask->insertItem(FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::sens]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::steadyState]] = CCopasiTask::sens;

  mpParameterPageLayout = new QHBoxLayout(mpParametersPage, 0, 6, "mpParameterPageLayout");

  mpParameters = new CQFittingItemWidget(mpParametersPage);
  //  mpParameters->setName(FROM_UTF8(taskName));

  mpParameters->setItemType(CQFittingItemWidget::OPT_ITEM);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(numberChanged(int)), this, SLOT(slotParameterNumberChanged(int)));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CQFittingItemWidget(mpConstraintsPage);
  //  mpConstraints->setName(FROM_UTF8(taskName));

  mpConstraints->setItemType(CQFittingItemWidget::OPT_CONSTRAINT);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(numberChanged(int)), this, SLOT(slotConstraintNumberChanged(int)));

  mpCurrentList = mpParameters;
}

void CQOptimizationWidget::destroy()
{}

void CQOptimizationWidget::slotExpressionValid(bool valid)
{
  mpBtnWidget->mpBtnRun->setEnabled(valid);
}

/*!
    The slot to activate the editor page of type CQExpressionWidget
    for being able to type a new mathematical expression or edit the existing one
 */
void CQOptimizationWidget::slotEditExpression()
{}

void CQOptimizationWidget::slotSubtaskChanged(const QString & /* subtask */)
{}
