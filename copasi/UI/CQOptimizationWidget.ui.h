/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQOptimizationWidget.ui.h,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/28 00:18:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlabel.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qmessagebox.h>

#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "UI/CQFittingItemWidget.h"
#include "UI/CProgressBar.h"
#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"

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

  if (pProblem->getObjectiveFunction() != mpEditExpression->getExpression())
    {
      if (!pProblem->setObjectiveFunction(mpEditExpression->getExpression()))
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
          return false;
        }

      mChanged = true;
    }

  if (mpBtnSteadystate->isChecked() &&
      *pProblem->getValue("Steady-State").pSTRING == "")
    {
      mChanged = true;

      pProblem->setValue("Time-Course", std::string(""));
      pProblem->setValue("Steady-State", (*CCopasiDataModel::Global->getTaskList())["Steady-State"]->getKey());
    }
  else if (mpBtnTimeCourse->isChecked() &&
           *pProblem->getValue("Time-Course").pSTRING == "")
    {
      mChanged = true;

      pProblem->setValue("Time-Course", (*CCopasiDataModel::Global->getTaskList())["Time-Course"]->getKey());
      pProblem->setValue("Steady-State", std::string(""));
    }

  mChanged |= mpParameters->save(NULL);
  mChanged |= mpConstraints->save(NULL);

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

  mpEditExpression->setExpression(pProblem->getObjectiveFunction());

  if (*pProblem->getValue("Steady-State").pSTRING != "")
    {
      mpBtnSteadystate->setChecked(true);
      mpBtnTimeCourse->setChecked(false);
    }
  else
    {
      mpBtnSteadystate->setChecked(false);
      mpBtnTimeCourse->setChecked(true);
    }

  mpParameters->load(pProblem->getGroup("OptimizationItemList"), NULL);

  mpConstraints->load(pProblem->getGroup("OptimizationConstraintList"), NULL);

  mChanged = false;

  return true;
}

bool CQOptimizationWidget::runTask()
{
  COptTask * pTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = true;

  // Initialize the task
  try
    {
      if (!pTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::critical(this, "Initialization Error",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();

          success = false;
          goto finish;
        }
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        QMessageBox::warning(this, "Initialization Warning",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ignore | QMessageBox::Default,
                             QMessageBox::Abort);
      CCopasiMessage::clearDeque();

      if (Result == QMessageBox::Abort)
        {
          success = false;
          goto finish;
        }
    }

  // Execute the task
  try
    {
      if (!pTask->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }

      success = false;
      goto finish;
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        QMessageBox::warning(this, "Calculation Warning",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

finish:
  try {pTask->restore();}

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  catch (...) {}

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        QMessageBox::warning(this, "Calculation Warning",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

  commonAfterRunTask();
  loadTask();

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
  mpHeaderWidget->setTaskName("Optimization");

  CQOptimizationWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQOptimizationWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(COptTask::ValidMethods);
  addMethodParameterTable();

  mpParameterPageLayout = new QHBoxLayout(mpParametersPage, 0, 6, "mpParameterPageLayout");
  mpParameters = new CQFittingItemWidget(mpParametersPage);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(numberChanged(int)), this, SLOT(slotParameterNumberChanged(int)));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CQFittingItemWidget(mpConstraintsPage);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(numberChanged(int)), this, SLOT(slotConstraintNumberChanged(int)));

  mpCurrentList = mpParameters;
}

void CQOptimizationWidget::destroy()
{}

bool CQOptimizationWidget::isSteadyState()
{return mpBtnSteadystate->isChecked();}

void CQOptimizationWidget::slotExpressionValid(bool valid)
{
  mpBtnWidget->mpBtnRun->setEnabled(valid);
}
