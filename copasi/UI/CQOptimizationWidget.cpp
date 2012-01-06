// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.cpp,v $
//   $Revision: 1.31 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/01/06 19:13:44 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQOptimizationWidget.h"

#include <QtCore/QVariant>

#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CQTaskMethodWidget.h"
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
#include "utilities/CCopasiException.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a CQOptimizationWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQOptimizationWidget::CQOptimizationWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQOptimizationWidget::~CQOptimizationWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

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
  if (pProblem->getObjectiveFunction() != mpExpressionEMW->mpExpressionWidget->getExpression())
    {
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
      pProblem->setSubtaskType((CCopasiTask::Type) mSubtaskMap[TO_UTF8(mpBoxSubtask->currentText())]);
    }

  if (mpBtnMaximize->isChecked() != pProblem->maximize())
    {
      mChanged = true;
      pProblem->setMaximize(mpBtnMaximize->isChecked());
    }

  if (mpCheckRandomize->isChecked() != pProblem->getRandomizeStartValues())
    {
      mChanged = true;
      pProblem->setRandomizeStartValues(mpCheckRandomize->isChecked());
    }

  if (mpCheckStatistics->isChecked() != pProblem->getCalculateStatistics())
    {
      mChanged = true;
      pProblem->setCalculateStatistics(mpCheckStatistics->isChecked());
    }

  mChanged |= mpParameters->save(NULL, NULL);
  mChanged |= mpConstraints->save(NULL, NULL);

  if (mChanged)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      (*CCopasiRootContainer::getDatamodelList())[0]->changed();
    }

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

  mpBtnMaximize->setChecked(pProblem->maximize());
  mpBtnMinimize->setChecked(!pProblem->maximize());

  mpCheckRandomize->setChecked(pProblem->getRandomizeStartValues());
  mpCheckStatistics->setChecked(pProblem->getCalculateStatistics());

  mpBoxSubtask->setCurrentIndex(mpBoxSubtask->findText(FROM_UTF8(CCopasiTask::TypeName[pProblem->getSubtaskType()])));

  mpParameters->load(mpDataModel, pProblem->getGroup("OptimizationItemList"), NULL, NULL);

  mpConstraints->load(mpDataModel, pProblem->getGroup("OptimizationConstraintList"), NULL, NULL);

  mChanged = false;

  return true;
}

bool CQOptimizationWidget::runTask()
{
  // --- expression

  mpExpressionEMW->updateWidget();

  // ----

  COptTask * pTask =
    dynamic_cast< COptTask * >(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  return commonRunTask();
}

void CQOptimizationWidget::slotPageChange(QWidget * currentPage)
{
  if (mpTabWidget->tabText(mpTabWidget->indexOf(currentPage)).contains("Parameters", Qt::CaseSensitive))
    mpCurrentList = mpParameters;
  else
    mpCurrentList = mpConstraints;
}

CCopasiMethod * CQOptimizationWidget::createMethod(const CCopasiMethod::SubType & type)
{return COptMethod::createMethod(type);}

void CQOptimizationWidget::slotParameterNumberChanged(int number)
{
  QString TabLabel = "Parameters (" + QString::number(number) + ")";
  mpTabWidget->setTabText(mpTabWidget->indexOf(mpParameters), TabLabel);
}

void CQOptimizationWidget::slotConstraintNumberChanged(int number)
{
  QString TabLabel = "Constraints (" + QString::number(number) + ")";
  mpTabWidget->setTabText(mpTabWidget->indexOf(mpConstraints), TabLabel);
}

void CQOptimizationWidget::init()
{
  std::string taskName = "Optimization";

  mpHeaderWidget->setTaskName(taskName);

  verticalLayout->insertWidget(0, mpHeaderWidget);
  // verticalLayout->insertSpacing(1, 14);      // space between header and body

  mpMethodWidget->setValidMethods(COptTask::ValidMethods);
  mpMethodWidget->showMethodParameters(true);
  verticalLayout->addWidget(mpMethodWidget);

  verticalLayout->addWidget(mpBtnWidget);

  mpExpressionEMW->mpExpressionWidget->setExpressionType(CQExpressionWidget::ObjectiveFunctions);

  mpBtnMaximize->setMinimumWidth(mpLblExpression->width());

  mpBoxSubtask->insertItem(mpBoxSubtask->count(), FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::steadyState]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::steadyState]] = CCopasiTask::steadyState;
  mpBoxSubtask->insertItem(mpBoxSubtask->count(), FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::timeCourse]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::timeCourse]] = CCopasiTask::timeCourse;
  mpBoxSubtask->insertItem(mpBoxSubtask->count(), FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::mca]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::mca]] = CCopasiTask::mca;
  mpBoxSubtask->insertItem(mpBoxSubtask->count(), FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::lna]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::lna]] = CCopasiTask::lna;
  mpBoxSubtask->insertItem(mpBoxSubtask->count(), FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::lyap]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::lyap]] = CCopasiTask::lyap;
  mpBoxSubtask->insertItem(mpBoxSubtask->count(), FROM_UTF8(CCopasiTask::TypeName[CCopasiTask::sens]));
  mSubtaskMap[CCopasiTask::TypeName[CCopasiTask::sens]] = CCopasiTask::sens;

  mpParameters->setItemType(CQFittingItemWidget::OPT_ITEM);

  connect(mpParameters, SIGNAL(numberChanged(int)), this, SLOT(slotParameterNumberChanged(int)));

  mpConstraints->setItemType(CQFittingItemWidget::OPT_CONSTRAINT);

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
