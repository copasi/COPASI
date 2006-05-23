/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQOptimizationWidget.ui.h,v $
   $Revision: 1.10.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/23 14:42:26 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlabel.h>
#include <qtoolbutton.h>
#include <qmessagebox.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQFittingItemWidget.h"
#include "CProgressBar.h"
#include "CCopasiSelectionDialog.h"
#include "qtUtilities.h"

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

  mChanged |= saveExpression();

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

  loadExpression();

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

      if (Result == QMessageBox::Abort) goto finish;
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

  return true;
}

void CQOptimizationWidget::slotPageChange(QWidget * currentPage)
{
  if (mpTabWidget->tabLabel(currentPage).contains("Parameters", true))
    mpCurrentList = mpParameters;
  else
    mpCurrentList = mpConstraints;
}

void CQOptimizationWidget::slotExpression()
{}

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
  mpParseList = new std::vector< CCopasiObject * >;

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
{
  pdelete(mpParseList);
}

void CQOptimizationWidget::slotObjectSelect()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      CCopasiObject * pObject = Selection[0];

      if (pObject)
        {
          mpParseList->push_back(pObject);
          std::string Insert = "<" + pObject->getObjectDisplayName() + ">";
          mpEditExpression->insert(FROM_UTF8(Insert));
        }
    }
}

bool CQOptimizationWidget::saveExpression()
{
  COptProblem * pProblem =
    dynamic_cast<COptProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  std::string DisplayName = "";
  std::string InfixCN = "";

  std::string InfixDispayName = (const char *)mpEditExpression->text().utf8();
  std::vector<CCopasiObject *>::iterator it = mpParseList->begin();

  for (unsigned int i = 0; i < InfixDispayName.length(); i++)
    {
      InfixCN += InfixDispayName[i];
      DisplayName = "";

      if (InfixDispayName[i] == '<')
        {
          i++;
          while (i < InfixDispayName.length() && InfixDispayName[i] != '>')
            {
              if (InfixDispayName[i] == '\\') // '\' is an escape character.
                DisplayName += InfixDispayName[i++];

              DisplayName += InfixDispayName[i++];
            }

          it = mpParseList->begin();
          while (it < mpParseList->end())
            {
              if ((*it)->getObjectDisplayName() == DisplayName)
                {
                  InfixCN += (*it)->getCN();
                  break;
                }

              it++;
            }

          if (it == mpParseList->end())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
              return false;
            }

          InfixCN += ">";
        }
    }

  bool changed = false;

  if (pProblem->getObjectiveFunction() != InfixCN)
    {
      if (!pProblem->setObjectiveFunction(InfixCN))
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
          return false;
        }

      changed = true;
    }

  // :TODO: need to handle errors.

  return changed;
}

// load the expression

bool CQOptimizationWidget::loadExpression()
{
  COptProblem * pProblem =
    dynamic_cast<COptProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  std::string objFunc = pProblem->getObjectiveFunction();

  unsigned C_INT32 i = 0;
  mpParseList->clear();

  std::string out_str = "";
  while (i < objFunc.length())
    {
      if (objFunc[i] == '<')
        {
          i++;
          std::string objectName = "";

          while (objFunc[i] != '>' && i < objFunc.length())
            {
              if (objFunc[i] == '\\')
                objectName += objFunc[i++];

              objectName += objFunc[i];
              i++;
            }

          CCopasiObjectName temp_CN(objectName);
          CCopasiObject * temp_object = const_cast<CCopasiObject *>(RootContainer.getObject(temp_CN));
          out_str += "<" + temp_object->getObjectDisplayName() + ">";
          mpParseList->push_back(temp_object);
          continue;
        }

      else if (objFunc[i] == '>')
        {
          //do nothing
        }

      else
        {
          out_str += objFunc[i];
        }

      i++;
    }

  mpEditExpression->setText(FROM_UTF8(out_str));

  return true;
}

bool CQOptimizationWidget::isSteadyState()
{return mpBtnSteadystate->isChecked();}
