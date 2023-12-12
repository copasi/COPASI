// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "CQTrajectoryWidget.h"

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "CQValidator.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CQTimeSeriesWidget.h"

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/utilities/CParameterEstimationUtils.h"

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

  mpVerticalLayout->insertWidget(0, mpHeaderWidget);  // header
  // verticalLayout->insertSpacing(1, 14);       // space between header and body

  mpMethodWidget->setValidMethods(CTrajectoryTask::ValidMethods);
  mpMethodWidget->showMethodParameters(true);
  mpVerticalLayout->addWidget(mpMethodWidget);

  mpVerticalLayout->addWidget(mpBtnWidget);     // 'footer'

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

  mpEditIntervalSize->setText(convertToQString(mpTrajectoryProblem->getStepSize()));
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

  mpEditIntervalSize->setText(convertToQString(mpTrajectoryProblem->getStepSize()));
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

  mpEditIntervalSize->setText(convertToQString(mpTrajectoryProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();

  checkTimeSeries();
  updateIntervals();
}

void CQTrajectoryWidget::slotOutputDelay(bool checked)
{
  mpEditDelay->setEnabled(checked);
  updateIntervals();
}

void CQTrajectoryWidget::slotAutomaticIntervals(bool checked)
{
  mpEditIntervals->setEnabled(!checked);
  mpEditIntervalSize->setEnabled(!checked);
}

void CQTrajectoryWidget::slotOutputEvent(bool checked)
{
  mpCheckOutputEvent->setChecked(checked);
}

void CQTrajectoryWidget::slotStartInSteadyState(bool checked)
{
  mpCheckStartInSteadyState->setChecked(checked);
}

void CQTrajectoryWidget::slotSaveOutput(bool checked)
{
  mpCheckSave->setChecked(checked);
}

bool CQTrajectoryWidget::saveTaskProtected()
{
  CTrajectoryTask * pTask =
    dynamic_cast< CTrajectoryTask * >(mpTask);

  if (!pTask) return false;

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

  if (mpCheckAutomaticInterval->isChecked() != trajectoryproblem->getAutomaticStepSize())
    {
      trajectoryproblem->setAutomaticStepSize(mpCheckAutomaticInterval->isChecked());
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
      assert(mpDataModel != NULL);
      C_FLOAT64 InitialTime =
        mpDataModel->getModel()->getInitialTime();

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

  if (trajectoryproblem->getStartInSteadyState() != mpCheckStartInSteadyState->isChecked())
    {
      trajectoryproblem->setStartInSteadyState(mpCheckStartInSteadyState->isChecked());
      mChanged = true;
    }

  bool useValues = (mpTabWidget->currentWidget() == mpValuesWidget);

  if (trajectoryproblem->getUseValues() != useValues)
    {
      trajectoryproblem->setUseValues(useValues);
      mChanged = true;
    }

  std::string valueString = TO_UTF8(mpEditValues->text());

  if (trajectoryproblem->getValueString() != valueString)
    {
      trajectoryproblem->setValues(valueString);
      mChanged = true;
    }

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();
  mpValidatorIntervals->saved();
  mpValidatorDelay->saved();
  return true;
}

bool CQTrajectoryWidget::loadTaskProtected()
{
  CTrajectoryTask * pTask =
    dynamic_cast< CTrajectoryTask * >(mpTask);

  if (!pTask) return false;

  showUnits();

  CTrajectoryProblem* TrajectoryProblem =
    dynamic_cast<CTrajectoryProblem *>(pTask->getProblem());
  assert(TrajectoryProblem);

  pdelete(mpTrajectoryProblem);

  mpTrajectoryProblem = new CTrajectoryProblem(*TrajectoryProblem, NO_PARENT);

  //numbers
  mpEditIntervalSize->setText(convertToQString(TrajectoryProblem->getStepSize()));
  mpEditIntervals->setText(QString::number(TrajectoryProblem->getStepNumber()));
  mpEditDuration->setText(convertToQString(TrajectoryProblem->getDuration()));
  mpCheckAutomaticInterval->setChecked(TrajectoryProblem->getAutomaticStepSize());

  assert(mpDataModel != NULL);
  C_FLOAT64 InitialTime = mpDataModel->getModel()->getInitialTime();

  bool Delayed;

  if (TrajectoryProblem->getStepSize() > 0.0)
    Delayed = (TrajectoryProblem->getOutputStartTime() - InitialTime) > std::numeric_limits< C_FLOAT64 >::min();
  else
    Delayed = (InitialTime - TrajectoryProblem->getOutputStartTime()) > std::numeric_limits< C_FLOAT64 >::min();

  mpCheckDelay->setChecked(Delayed);
  mpEditDelay->setEnabled(Delayed);

  mpEditDelay->setText(convertToQString(TrajectoryProblem->getOutputStartTime()));

  mpCheckOutputEvent->setChecked(TrajectoryProblem->getOutputEvent());
  mpCheckStartInSteadyState->setChecked(TrajectoryProblem->getStartInSteadyState());

  //store time series checkbox
  mpCheckSave->setChecked(TrajectoryProblem->timeSeriesRequested());

  checkTimeSeries();

  updateIntervals();

  mpEditValues->setText(FROM_UTF8(TrajectoryProblem->getValueString()));

  if (TrajectoryProblem->getUseValues())
    mpTabWidget->setCurrentWidget(mpValuesWidget);
  else
    mpTabWidget->setCurrentWidget(mpDurationWidget);

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();
  mpValidatorIntervals->saved();
  mpValidatorDelay->saved();
  return true;
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
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::TimeCourseResult));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  return success;
}

void CQTrajectoryWidget::checkTimeSeries()
{
  assert(mpDataModel != NULL);

  if (mpEditIntervals->text().toLong() * mpDataModel->getModel()->getStateTemplate().getNumVariable() > TSMAX)
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
  assert(mpDataModel != NULL);
  C_FLOAT64 InitialTime = mpDataModel->getModel()->getInitialTime();
  C_FLOAT64 Duration;

  if (mpTabWidget->currentWidget() == mpValuesWidget)
    {
      std::set< C_FLOAT64 > Values;

      std::vector< std::string > elems;
      ResultParser::split(TO_UTF8(mpEditValues->text()), std::string(",; |\n\t\r"), elems);

      for (std::string & number : elems)
        {
          Values.insert(ResultParser::saveToDouble(number));
        }

      Duration = Values.size() ? *Values.rbegin() : std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }
  else
    {
      Duration = mpEditDuration->text().toDouble();
    }

  C_FLOAT64 OutputStartTime = InitialTime;

  if (mpCheckDelay->isChecked())
    {
      if (!mpEditIntervalSize->hasAcceptableInput())
        return;

      OutputStartTime = mpEditDelay->text().toDouble();
    }

  mpEditIntegrationInterval->setText(convertToQString(InitialTime) +
                                     " to " +
                                     convertToQString(InitialTime + Duration));

  if (Duration > 0.0)
    {
      if (std::max(InitialTime, OutputStartTime) > InitialTime + Duration)
        mpEditOutputInterval->setText("empty");
      else if (InitialTime < OutputStartTime)
        {
          C_FLOAT64 StepSize = mpEditIntervalSize->text().toDouble();
          OutputStartTime = InitialTime + (ceil((OutputStartTime - InitialTime) / StepSize)) * StepSize;
          mpEditOutputInterval->setText(convertToQString(OutputStartTime) +
                                        " to " +
                                        convertToQString(InitialTime + Duration));
        }
      else
        {
          mpEditOutputInterval->setText(convertToQString(InitialTime) +
                                        " to " +
                                        convertToQString(InitialTime + Duration));
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
          mpEditOutputInterval->setText(convertToQString(OutputStartTime) +
                                        " to " +
                                        convertToQString(InitialTime + Duration));
        }
      else
        mpEditOutputInterval->setText(convertToQString(InitialTime) +
                                      " to " +
                                      convertToQString(InitialTime + Duration));
    }
}

// virtual
bool CQTrajectoryWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  TaskWidget::updateProtected(objectType, action, cn);

  if (mIgnoreUpdates || !isVisible())
    {
      return true;
    }

  switch (objectType)
    {
      case ListViews::ObjectType::MODEL:

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
      TimeUnits = " [" + FROM_UTF8(CUnit::prettyPrint(pModel->getTimeUnit())) + "]";
    }

  mpLblDuration->setText("Duration" + TimeUnits);
  mpLblIntervalSize->setText("Interval Size" + TimeUnits);
  mpCheckDelay->setText("Suppress Output Before" + TimeUnits);
  mpLblIntegrationInterval->setText("Integration Interval" + TimeUnits);
  mpLblOutputInterval->setText("Output Interval" + TimeUnits);
  mpLblValues->setText("Values" + TimeUnits);
}
