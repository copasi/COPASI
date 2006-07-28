/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQTrajectoryWidget.ui.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/28 21:20:57 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CProgressBar.h"
#include "CQValidator.h"
#include "qtUtilities.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"

#define TSMAX 10000000

void CQTrajectoryWidget::init()
{
  mpTrajectoryProblem = NULL;

  mpHeaderWidget->setTaskName("Time Course");

  CQTrajectoryWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQTrajectoryWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(CTrajectoryTask::ValidMethods);
  addMethodParameterTable(0);

  slotOutputDelay(false);

  mpValidatorDuration = new CQValidatorDouble(mpEditDuration);
  mpEditDuration->setValidator(mpValidatorDuration);

  mpValidatorIntervalSize = new CQValidatorDouble(mpEditIntervalSize);
  mpValidatorIntervalSize->setRange(0, DBL_MAX);
  mpEditIntervalSize->setValidator(mpValidatorIntervalSize);

  mpValidatorIntervals = new CQValidatorInt(mpEditIntervals);
  mpValidatorIntervals->setRange(0, LONG_MAX);
  mpEditIntervals->setValidator(mpValidatorIntervals);

  mpValidatorDelay = new CQValidatorDouble(mpEditDelay);
  mpEditDelay->setValidator(mpValidatorDelay);
}

void CQTrajectoryWidget::destroy()
{
  pdelete(mpTrajectoryProblem);
}

void CQTrajectoryWidget::slotDuration()
{
  try
    {
      mpTrajectoryProblem->setDuration(mpEditDuration->text().toDouble());
    }
  catch (...)
    {
      QMessageBox::warning(this, QString("File Warning"),
                           FROM_UTF8(CCopasiMessage::getAllMessageText()),
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
    }

  mpEditIntervalSize->setText(QString::number(mpTrajectoryProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTrajectoryProblem->getStepNumber()));
  mpValidatorIntervals->revalidate();

  checkTimeSeries();
}

void CQTrajectoryWidget::slotIntervalSize()
{
  try
    {
      mpTrajectoryProblem->setStepSize(mpEditIntervalSize->text().toDouble());
    }

  catch (...)
    {
      QMessageBox::warning(this, QString("File Warning"),
                           FROM_UTF8(CCopasiMessage::getAllMessageText()),
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
    }

  mpEditIntervalSize->setText(QString::number(mpTrajectoryProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTrajectoryProblem->getStepNumber()));
  mpValidatorIntervals->revalidate();

  checkTimeSeries();
}

void CQTrajectoryWidget::slotIntervals()
{
  try
    {
      mpTrajectoryProblem->setStepNumber(mpEditIntervals->text().toULong());
    }
  catch (...)
    {
      QMessageBox::warning(this, QString("File Warning"),
                           FROM_UTF8(CCopasiMessage::getAllMessageText()),
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
    }

  mpEditIntervalSize->setText(QString::number(mpTrajectoryProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();

  checkTimeSeries();
}

void CQTrajectoryWidget::slotOutputDelay(bool checked)
{
  mpEditDelay->setEnabled(checked);
}

bool CQTrajectoryWidget::saveTask()
{
  CTrajectoryTask * pTask =
    dynamic_cast< CTrajectoryTask * >(mpTask);
  if (!pTask) return false;

  saveCommon();
  saveMethod();

  CTrajectoryProblem* trajectoryproblem =
    dynamic_cast<CTrajectoryProblem *>(pTask->getProblem());
  assert(trajectoryproblem);

  //numbers
  if (trajectoryproblem->getStepSize() != mpEditIntervalSize->text().toDouble())
    {
      trajectoryproblem->setStepSize(mpEditIntervalSize->text().toDouble());
      mChanged = true;
    }
  else if (trajectoryproblem->getStepNumber() != mpEditIntervals->text().toULong())
    {
      trajectoryproblem->setStepNumber(mpEditIntervals->text().toLong());
      mChanged = true;
    }

  if (trajectoryproblem->getDuration() != mpEditDuration->text().toDouble())
    {
      trajectoryproblem->setDuration(mpEditDuration->text().toDouble());
      mChanged = true;
    }

  C_FLOAT64 Delay = mpEditDelay->text().toDouble();

  if (Delay != trajectoryproblem->getOutputStartTime())
    {
      trajectoryproblem->setOutputStartTime(Delay);
      mChanged = true;
    }

  if (trajectoryproblem->timeSeriesRequested() != mpCheckSave->isChecked())
    {
      trajectoryproblem->setTimeSeriesRequested(mpCheckSave->isChecked());
      mChanged = true;
    }

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();
  mpValidatorIntervals->saved();
  mpValidatorDelay->saved();
  return true;
}

bool CQTrajectoryWidget::loadTask()
{
  CTrajectoryTask * pTask =
    dynamic_cast< CTrajectoryTask * >(mpTask);
  if (!pTask) return false;

  loadCommon();
  loadMethod();

  CTrajectoryProblem* trajectoryproblem =
    dynamic_cast<CTrajectoryProblem *>(pTask->getProblem());
  assert(trajectoryproblem);

  pdelete(mpTrajectoryProblem);
  mpTrajectoryProblem = new CTrajectoryProblem(*trajectoryproblem);

  //numbers
  mpEditIntervalSize->setText(QString::number(trajectoryproblem->getStepSize()));
  mpEditIntervals->setText(QString::number(trajectoryproblem->getStepNumber()));
  mpEditDuration->setText(QString::number(trajectoryproblem->getDuration()));

  bool Delayed;
  if (trajectoryproblem->getStepSize() > 0.0)
    Delayed =
      (trajectoryproblem->getOutputStartTime() - CCopasiDataModel::Global->getModel()->getInitialTime()) > DBL_MIN;
  else
    Delayed =
      (CCopasiDataModel::Global->getModel()->getInitialTime() - trajectoryproblem->getOutputStartTime()) > DBL_MIN;

  mpCheckDelay->setChecked(Delayed);
  mpEditDelay->setEnabled(Delayed);

  mpEditDelay->setText(QString::number(trajectoryproblem->getOutputStartTime()));

  //store time series checkbox
  mpCheckSave->setChecked(trajectoryproblem->timeSeriesRequested());
  checkTimeSeries();

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();
  mpValidatorIntervals->saved();
  mpValidatorDelay->saved();
  return true;
}

CCopasiMethod * CQTrajectoryWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return CTrajectoryMethod::createTrajectoryMethod(type);
}

bool CQTrajectoryWidget::runTask()
{
  CTrajectoryTask * pTask =
    dynamic_cast< CTrajectoryTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  checkTimeSeries();
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

void CQTrajectoryWidget::checkTimeSeries()
{
  if (mpEditIntervals->text().toLong() * CCopasiDataModel::Global->getModel()->getNumVariableMetabs() > TSMAX)
    {
      mpCheckSave->setChecked(false);
      mpCheckSave->setEnabled(false);
    }
  else
    {
      mpCheckSave->setEnabled(true);
    }
}
