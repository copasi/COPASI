// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CQTrajectoryWidget.h"

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "CQValidator.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CQTimeSeriesWidget.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "report/CCopasiRootContainer.h"

/*
 *  Constructs a CQTrajectoryWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQTrajectoryWidget::CQTrajectoryWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTrajectoryWidget::~CQTrajectoryWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQTrajectoryWidget::init()
{
  mpTrajectoryProblem = NULL;

  mpHeaderWidget->setTaskName("Time Course");

  verticalLayout->insertWidget(0, mpHeaderWidget);  // header
  // verticalLayout->insertSpacing(1, 14);       // space between header and body

  mpMethodWidget->setValidMethods(CTrajectoryTask::ValidMethods);
  mpMethodWidget->showMethodParameters(true);
  verticalLayout->addWidget(mpMethodWidget);

  verticalLayout->addWidget(mpBtnWidget);     // 'footer'

  slotOutputDelay(false);

  mpValidatorDuration = new CQValidatorDouble(mpEditDuration);
  mpEditDuration->setValidator(mpValidatorDuration);

  mpValidatorIntervalSize = new CQValidatorDouble(mpEditIntervalSize);
  mpValidatorIntervalSize->setRange(0, std::numeric_limits< double >::max());
  mpEditIntervalSize->setValidator(mpValidatorIntervalSize);

  mpValidatorIntervals = new CQValidatorInt(mpEditIntervals);
  mpValidatorIntervals->setRange(0, std::numeric_limits< int >::max());
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
  if (!mpEditDuration->hasAcceptableInput())
    return;

  try
    {
      mpTrajectoryProblem->setDuration(mpEditDuration->text().toDouble());
    }
  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(QString::number(mpTrajectoryProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTrajectoryProblem->getStepNumber()));
  mpValidatorIntervals->revalidate();

  checkTimeSeries();
  updateIntervals();
}

void CQTrajectoryWidget::slotIntervalSize()
{
  if (!mpEditIntervalSize->hasAcceptableInput())
    return;

  try
    {
      mpTrajectoryProblem->setStepSize(mpEditIntervalSize->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(QString::number(mpTrajectoryProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTrajectoryProblem->getStepNumber()));
  mpValidatorIntervals->revalidate();

  checkTimeSeries();
  updateIntervals();
}

void CQTrajectoryWidget::slotIntervals()
{
  if (!mpEditIntervals->hasAcceptableInput())
    return;

  try
    {
      mpTrajectoryProblem->setStepNumber(mpEditIntervals->text().toULong());
    }
  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(QString::number(mpTrajectoryProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();

  checkTimeSeries();
  updateIntervals();
}

void CQTrajectoryWidget::slotOutputDelay(bool checked)
{
  mpEditDelay->setEnabled(checked);
  updateIntervals();
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
  if (mpEditIntervalSize->hasAcceptableInput() &&
      trajectoryproblem->getStepSize() != mpEditIntervalSize->text().toDouble())
    {
      trajectoryproblem->setStepSize(mpEditIntervalSize->text().toDouble());
      mChanged = true;
    }
  else if (mpEditIntervals->hasAcceptableInput() &&
           trajectoryproblem->getStepNumber() != mpEditIntervals->text().toULong())
    {
      trajectoryproblem->setStepNumber(mpEditIntervals->text().toLong());
      mChanged = true;
    }

  if (mpEditDuration->hasAcceptableInput() &&
      trajectoryproblem->getDuration() != mpEditDuration->text().toDouble())
    {
      trajectoryproblem->setDuration(mpEditDuration->text().toDouble());
      mChanged = true;
    }

  C_FLOAT64 StartTime = mpEditDelay->text().toDouble();

  if (mpCheckDelay->isChecked())
    {
      if (mpEditDelay->hasAcceptableInput() &&
          StartTime != trajectoryproblem->getOutputStartTime())
        {
          trajectoryproblem->setOutputStartTime(StartTime);
          mChanged = true;
        }
    }
  else
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      C_FLOAT64 InitialTime =
        (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getInitialTime();

      if (trajectoryproblem->getStepSize() > 0.0)
        {
          if (StartTime > InitialTime)
            {
              trajectoryproblem->setOutputStartTime(InitialTime);
              mChanged = true;
            }
        }
      else
        {
          if (StartTime < InitialTime)
            {
              trajectoryproblem->setOutputStartTime(InitialTime);
              mChanged = true;
            }
        }
    }

  if (trajectoryproblem->timeSeriesRequested() != mpCheckSave->isChecked())
    {
      trajectoryproblem->setTimeSeriesRequested(mpCheckSave->isChecked());
      mChanged = true;
    }

  if (trajectoryproblem->getOutputEvent() != mpCheckOutputEvent->isChecked())
    {
      trajectoryproblem->setOutputEvent(mpCheckOutputEvent->isChecked());
      mChanged = true;
    }

  if (trajectoryproblem->getContinueSimultaneousEvents() != mpCheckContinueEvents->isChecked())
    {
      trajectoryproblem->setContinueSimultaneousEvents(mpCheckContinueEvents->isChecked());
      mChanged = true;
    }

  if (trajectoryproblem->getStartInSteadyState() != mpCheckStartInSteadyState->isChecked())
    {
      trajectoryproblem->setStartInSteadyState(mpCheckStartInSteadyState->isChecked());
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

  showUnits();

  CTrajectoryProblem* trajectoryproblem =
    dynamic_cast<CTrajectoryProblem *>(pTask->getProblem());
  assert(trajectoryproblem);

  pdelete(mpTrajectoryProblem);
  mpTrajectoryProblem = new CTrajectoryProblem(*trajectoryproblem);

  //numbers
  mpEditIntervalSize->setText(QString::number(trajectoryproblem->getStepSize()));
  mpEditIntervals->setText(QString::number(trajectoryproblem->getStepNumber()));
  mpEditDuration->setText(QString::number(trajectoryproblem->getDuration()));

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  C_FLOAT64 InitialTime = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getInitialTime();

  bool Delayed;

  if (trajectoryproblem->getStepSize() > 0.0)
    Delayed = (trajectoryproblem->getOutputStartTime() - InitialTime) > std::numeric_limits< C_FLOAT64 >::min();
  else
    Delayed = (InitialTime - trajectoryproblem->getOutputStartTime()) > std::numeric_limits< C_FLOAT64 >::min();

  mpCheckDelay->setChecked(Delayed);
  mpEditDelay->setEnabled(Delayed);

  mpEditDelay->setText(QString::number(trajectoryproblem->getOutputStartTime()));

  mpCheckOutputEvent->setChecked(trajectoryproblem->getOutputEvent());
  mpCheckContinueEvents->setChecked(trajectoryproblem->getContinueSimultaneousEvents());
  mpCheckStartInSteadyState->setChecked(trajectoryproblem->getStartInSteadyState());

  //store time series checkbox
  mpCheckSave->setChecked(trajectoryproblem->timeSeriesRequested());

  checkTimeSeries();

  updateIntervals();

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();
  mpValidatorIntervals->saved();
  mpValidatorDelay->saved();
  return true;
}

CCopasiMethod * CQTrajectoryWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return CTrajectoryMethod::createMethod(type);
}

bool CQTrajectoryWidget::runTask()
{
  checkTimeSeries();

  if (!commonBeforeRunTask()) return false;

  bool success = true;

  if (!commonRunTask()) success = false;

  return success;
}

bool CQTrajectoryWidget::taskFinishedEvent()
{
  bool success = true;
  // We need to load the result here as this is the only place where
  // we know that it is correct.
  CQTimeSeriesWidget * pResult =
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->findWidgetFromId(231));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  return success;
}

void CQTrajectoryWidget::checkTimeSeries()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (mpEditIntervals->text().toLong() * (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getStateTemplate().getNumVariable() > TSMAX)
    {
      mpCheckSave->setChecked(false);
      mpCheckSave->setEnabled(false);
    }
  else
    {
      mpCheckSave->setEnabled(true);
    }
}

void CQTrajectoryWidget::updateIntervals()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  C_FLOAT64 InitialTime = (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getInitialTime();
  C_FLOAT64 Duration = mpEditDuration->text().toDouble();
  C_FLOAT64 OutputStartTime = InitialTime;

  if (mpCheckDelay->isChecked())
    {
      if (!mpEditIntervalSize->hasAcceptableInput())
        return;

      OutputStartTime = mpEditDelay->text().toDouble();
    }

  mpEditIntegrationInterval->setText(QString::number(InitialTime) +
                                     " to " +
                                     QString::number(InitialTime + Duration));

  if (Duration > 0.0)
    {
      if (std::max(InitialTime, OutputStartTime) > InitialTime + Duration)
        mpEditOutputInterval->setText("empty");
      else if (InitialTime < OutputStartTime)
        {
          C_FLOAT64 StepSize = mpEditIntervalSize->text().toDouble();
          OutputStartTime = InitialTime + (ceil((OutputStartTime - InitialTime) / StepSize)) * StepSize;
          mpEditOutputInterval->setText(QString::number(OutputStartTime) +
                                        " to " +
                                        QString::number(InitialTime + Duration));
        }
      else
        {
          mpEditOutputInterval->setText(QString::number(InitialTime) +
                                        " to " +
                                        QString::number(InitialTime + Duration));
        }
    }
  else
    {
      if (std::min(InitialTime, OutputStartTime) < InitialTime + Duration)
        mpEditOutputInterval->setText("empty");
      else if (InitialTime > OutputStartTime)
        {
          C_FLOAT64 StepSize = mpEditIntervalSize->text().toDouble();
          OutputStartTime = InitialTime + (ceil((OutputStartTime - InitialTime) / StepSize)) * StepSize;
          mpEditOutputInterval->setText(QString::number(OutputStartTime) +
                                        " to " +
                                        QString::number(InitialTime + Duration));
        }
      else
        mpEditOutputInterval->setText(QString::number(InitialTime) +
                                      " to " +
                                      QString::number(InitialTime + Duration));
    }
}

// virtual
bool CQTrajectoryWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & /* key */)
{
  switch (objectType)
    {
      case ListViews::MODEL:

        if (action == ListViews::CHANGE)
          {
            showUnits();
          }

        break;

      default:
        break;
    }

  return true;
}

void CQTrajectoryWidget::showUnits()
{
  const CModel * pModel = NULL;

  QString TimeUnits;

  if (mpDataModel != NULL &&
      (pModel = mpDataModel->getModel()) != NULL)
    {
      TimeUnits = " (" + FROM_UTF8(pModel->getTimeUnitsDisplayString()) + ")";
    }

  mpLblDuration->setText("Duration" + TimeUnits);
  mpLblIntervalSize->setText("Interval Size" + TimeUnits);
  mpCheckDelay->setText("Suppress Output Before" + TimeUnits);
  mpLblIntegrationInterval->setText("Integration Interval" + TimeUnits);
  mpLblOutputInterval->setText("Output Interval" + TimeUnits);
}
