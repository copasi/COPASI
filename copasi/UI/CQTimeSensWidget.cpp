// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "CQTimeSensWidget.h"

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "CQValidator.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"
#include "CQTimeSeriesWidget.h"

#include "copasi/timesens/CTimeSensTask.h"
#include "copasi/timesens/CTimeSensProblem.h"
#include "copasi/timesens/CTimeSensMethod.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"

/*
 *  Constructs a CQTimeSensWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQTimeSensWidget::CQTimeSensWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  mpCmdAdd->setIcon(CQIconResource::icon(CQIconResource::editAdd));
  mpCmdRemove->setIcon(CQIconResource::icon(CQIconResource::editDelete));
  mpCmdAddTarget->setIcon(CQIconResource::icon(CQIconResource::editAdd));
  mpCmdRemoveTarget->setIcon(CQIconResource::icon(CQIconResource::editDelete));

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTimeSensWidget::~CQTimeSensWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQTimeSensWidget::init()
{
  mpTimeSensProblem = NULL;

  mpHeaderWidget->setTaskName("Time-Course Sensitivities");

  verticalLayout->insertWidget(0, mpHeaderWidget);  // header
  // verticalLayout->insertSpacing(1, 14);       // space between header and body

  mpMethodWidget->setValidMethods(CTimeSensTask::ValidMethods);
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

void CQTimeSensWidget::destroy()
{
  pdelete(mpTimeSensProblem);
}

void CQTimeSensWidget::slotDuration()
{
  if (!mpEditDuration->hasAcceptableInput())
    return;

  try
    {
      mpTimeSensProblem->setDuration(mpEditDuration->text().toDouble());
    }
  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(convertToQString(mpTimeSensProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTimeSensProblem->getStepNumber()));
  mpValidatorIntervals->revalidate();

  checkTimeSeries();
  updateIntervals();
}

void CQTimeSensWidget::slotIntervalSize()
{
  if (!mpEditIntervalSize->hasAcceptableInput())
    return;

  try
    {
      mpTimeSensProblem->setStepSize(mpEditIntervalSize->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(convertToQString(mpTimeSensProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTimeSensProblem->getStepNumber()));
  mpValidatorIntervals->revalidate();

  checkTimeSeries();
  updateIntervals();
}

void CQTimeSensWidget::slotIntervals()
{
  if (!mpEditIntervals->hasAcceptableInput())
    return;

  try
    {
      mpTimeSensProblem->setStepNumber(mpEditIntervals->text().toULong());
    }
  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(convertToQString(mpTimeSensProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();

  checkTimeSeries();
  updateIntervals();
}

void CQTimeSensWidget::slotOutputDelay(bool checked)
{
  mpEditDelay->setEnabled(checked);
  updateIntervals();
}

void CQTimeSensWidget::slotAutomaticIntervals(bool checked)
{
  mpEditIntervals->setEnabled(!checked);
  mpEditIntervalSize->setEnabled(!checked);
}

bool CQTimeSensWidget::saveTaskProtected()
{
  CTimeSensTask * pTask =
    dynamic_cast<CTimeSensTask * >(mpTask);

  if (!pTask) return false;

  CTimeSensProblem* timeSensProblem =
    dynamic_cast<CTimeSensProblem *>(pTask->getProblem());
  assert(timeSensProblem);

  //numbers
  if (mpEditIntervalSize->hasAcceptableInput() &&
      timeSensProblem->getStepSize() != mpEditIntervalSize->text().toDouble())
    {
      timeSensProblem->setStepSize(mpEditIntervalSize->text().toDouble());
      mChanged = true;
    }
  else if (mpEditIntervals->hasAcceptableInput() &&
           timeSensProblem->getStepNumber() != mpEditIntervals->text().toULong())
    {
      timeSensProblem->setStepNumber(mpEditIntervals->text().toLong());
      mChanged = true;
    }

  if (mpEditDuration->hasAcceptableInput() &&
      timeSensProblem->getDuration() != mpEditDuration->text().toDouble())
    {
      timeSensProblem->setDuration(mpEditDuration->text().toDouble());
      mChanged = true;
    }

  if (mpCheckAutomaticInterval->isChecked() != timeSensProblem->getAutomaticStepSize())
    {
      timeSensProblem->setAutomaticStepSize(mpCheckAutomaticInterval->isChecked());
      mChanged = true;
    }

  C_FLOAT64 StartTime = mpEditDelay->text().toDouble();

  if (mpCheckDelay->isChecked())
    {
      if (mpEditDelay->hasAcceptableInput() &&
          StartTime != timeSensProblem->getOutputStartTime())
        {
          timeSensProblem->setOutputStartTime(StartTime);
          mChanged = true;
        }
    }
  else
    {
      assert(mpDataModel != NULL);
      C_FLOAT64 InitialTime =
        mpDataModel->getModel()->getInitialTime();

      if (timeSensProblem->getStepSize() > 0.0)
        {
          if (StartTime > InitialTime)
            {
              timeSensProblem->setOutputStartTime(InitialTime);
              mChanged = true;
            }
        }
      else
        {
          if (StartTime < InitialTime)
            {
              timeSensProblem->setOutputStartTime(InitialTime);
              mChanged = true;
            }
        }
    }

  if (timeSensProblem->timeSeriesRequested() != mpCheckSave->isChecked())
    {
      timeSensProblem->setTimeSeriesRequested(mpCheckSave->isChecked());
      mChanged = true;
    }

  if (timeSensProblem->getOutputEvent() != mpCheckOutputEvent->isChecked())
    {
      timeSensProblem->setOutputEvent(mpCheckOutputEvent->isChecked());
      mChanged = true;
    }

  if (timeSensProblem->getStartInSteadyState() != mpCheckStartInSteadyState->isChecked())
    {
      timeSensProblem->setStartInSteadyState(mpCheckStartInSteadyState->isChecked());
      mChanged = true;
    }

  timeSensProblem->clearParameterCNs();

  for (size_t i = 0; i < mpTimeSensProblem->getNumParameters(); ++i)
    {
      timeSensProblem->addParameterCN(mpTimeSensProblem->getParameterCN(i));
    }

  timeSensProblem->clearTargetCNs();

  for (size_t i = 0; i < mpTimeSensProblem->getNumTargets(); ++i)
    {
      timeSensProblem->addTargetCN(mpTimeSensProblem->getTargetCN(i));
    }

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();
  mpValidatorIntervals->saved();
  mpValidatorDelay->saved();
  return true;
}

bool CQTimeSensWidget::loadTaskProtected()
{
  CTimeSensTask * pTask =
    dynamic_cast< CTimeSensTask * >(mpTask);

  if (!pTask) return false;

  showUnits();

  CTimeSensProblem* timeSensProblem =
    dynamic_cast<CTimeSensProblem *>(pTask->getProblem());
  assert(timeSensProblem);

  pdelete(mpTimeSensProblem);

  mpTimeSensProblem = new CTimeSensProblem(*timeSensProblem, NO_PARENT);

  //numbers
  mpEditIntervalSize->setText(convertToQString(timeSensProblem->getStepSize()));
  mpEditIntervals->setText(QString::number(timeSensProblem->getStepNumber()));
  mpEditDuration->setText(convertToQString(timeSensProblem->getDuration()));
  mpCheckAutomaticInterval->setChecked(timeSensProblem->getAutomaticStepSize());

  assert(mpDataModel != NULL);
  C_FLOAT64 InitialTime = mpDataModel->getModel()->getInitialTime();

  bool Delayed;

  if (timeSensProblem->getStepSize() > 0.0)
    Delayed = (timeSensProblem->getOutputStartTime() - InitialTime) > std::numeric_limits< C_FLOAT64 >::min();
  else
    Delayed = (InitialTime - timeSensProblem->getOutputStartTime()) > std::numeric_limits< C_FLOAT64 >::min();

  mpCheckDelay->setChecked(Delayed);
  mpEditDelay->setEnabled(Delayed);

  mpEditDelay->setText(convertToQString(timeSensProblem->getOutputStartTime()));

  mpCheckOutputEvent->setChecked(timeSensProblem->getOutputEvent());
  mpCheckStartInSteadyState->setChecked(timeSensProblem->getStartInSteadyState());

  //store time series checkbox
  mpCheckSave->setChecked(timeSensProblem->timeSeriesRequested());

  checkTimeSeries();

  updateIntervals();

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();
  mpValidatorIntervals->saved();
  mpValidatorDelay->saved();

  // load parameters
  mpListParameters->clear();

  std::vector<std::string> toBeRemoved;

  for (size_t i = 0; i < timeSensProblem->getNumParameters(); ++i)
    {
      std::string cn = timeSensProblem->getParameterCN(i);
      const CDataObject* pObject = dynamic_cast<const CDataObject*>(mpDataModel->getObjectFromCN(cn));

      if (!pObject)
        {
          toBeRemoved.push_back(cn);
          continue;
        }

      QListWidgetItem* pItem = new QListWidgetItem(FROM_UTF8(pObject->getObjectDisplayName()));
      pItem->setData(Qt::UserRole, FROM_UTF8(pObject->getCN()));
      mpListParameters->addItem(pItem);
    }

  if (!toBeRemoved.empty())
    {
      for (std::string cn : toBeRemoved)
        {
          timeSensProblem->removeParameterCN(cn);
          mpTimeSensProblem->removeParameterCN(cn);
        }
    }

  // load targets
  mpListTargets->clear();
  toBeRemoved.clear();

  for (size_t i = 0; i < timeSensProblem->getNumTargets(); ++i)
    {
      std::string cn = timeSensProblem->getTargetCN(i);
      const CDataObject* pObject = dynamic_cast<const CDataObject*>(mpDataModel->getObjectFromCN(cn));

      if (!pObject)
        {
          toBeRemoved.push_back(cn);
          continue;
        }

      QListWidgetItem* pItem = new QListWidgetItem(FROM_UTF8(pObject->getObjectDisplayName()));
      pItem->setData(Qt::UserRole, FROM_UTF8(pObject->getCN()));
      mpListTargets->addItem(pItem);
    }

  if (!toBeRemoved.empty())
    {
      for (std::string cn : toBeRemoved)
        {
          timeSensProblem->removeTargetCN(cn);
          mpTimeSensProblem->removeTargetCN(cn);
        }
    }

  return true;
}

bool CQTimeSensWidget::runTask()
{
  checkTimeSeries();

  if (!commonBeforeRunTask()) return false;

  bool success = true;

  if (!commonRunTask()) success = false;

  return success;
}

bool CQTimeSensWidget::taskFinishedEvent()
{
  bool success = true;
  // We need to load the result here as this is the only place where
  // we know that it is correct.
  CQTimeSeriesWidget * pResult =
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::TimeCourseSensitivitiesResult));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  return success;
}

void CQTimeSensWidget::checkTimeSeries()
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

void CQTimeSensWidget::updateIntervals()
{
  assert(mpDataModel != NULL);
  C_FLOAT64 InitialTime = mpDataModel->getModel()->getInitialTime();
  C_FLOAT64 Duration = mpEditDuration->text().toDouble();
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
bool CQTimeSensWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
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

void CQTimeSensWidget::showUnits()
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
}

void CQTimeSensWidget::slotAddParameter()
{
  if (mpTimeSensProblem == NULL)
    return;

  std::vector< const CDataObject * > selection =
    CCopasiSelectionDialog::getObjectVector(this,
        (CQSimpleSelectionTree::InitialTime | CQSimpleSelectionTree::Parameters));

  for (const CDataObject * item : selection)
    {
      if (!mpListParameters->findItems(FROM_UTF8(item->getObjectDisplayName()), Qt::MatchExactly).empty())
        continue;

      QListWidgetItem* pItem = new QListWidgetItem(FROM_UTF8(item->getObjectDisplayName()));
      pItem->setData(Qt::UserRole, FROM_UTF8(item->getCN()));
      mpListParameters->addItem(pItem);

      mpTimeSensProblem->addParameterCN(item->getCN());
    }
}

void CQTimeSensWidget::slotRemoveParameter()
{
  if (mpTimeSensProblem == NULL)
    return;

  QModelIndexList items = mpListParameters->selectionModel()->selectedIndexes();

  for (int i = items.size() - 1; i >= 0; --i)
    {
      QListWidgetItem* item = mpListParameters->takeItem(items.at(i).row());

      std::string cn = TO_UTF8(item->data(Qt::UserRole).toString());

      mpTimeSensProblem->removeParameterCN(cn);

      pdelete(item);
    }
}

void CQTimeSensWidget::slotAddTarget()
{
  if (mpTimeSensProblem == NULL)
    return;

  std::vector< const CDataObject * > selection =
    CCopasiSelectionDialog::getObjectVector(this,
        (CQSimpleSelectionTree::Variables | CQSimpleSelectionTree::ObservedValues | CQSimpleSelectionTree::EventTarget));

  for (const CDataObject * item : selection)
    {
      if (!mpListTargets->findItems(FROM_UTF8(item->getObjectDisplayName()), Qt::MatchExactly).empty())
        continue;

      QListWidgetItem* pItem = new QListWidgetItem(FROM_UTF8(item->getObjectDisplayName()));
      pItem->setData(Qt::UserRole, FROM_UTF8(item->getCN()));
      mpListTargets->addItem(pItem);

      mpTimeSensProblem->addTargetCN(item->getCN());
    }
}

void CQTimeSensWidget::slotRemoveTarget()
{
  if (mpTimeSensProblem == NULL)
    return;

  QModelIndexList items = mpListTargets->selectionModel()->selectedIndexes();

  for (int i = items.size() - 1; i >= 0; --i)
    {
      QListWidgetItem* item = mpListTargets->takeItem(items.at(i).row());

      std::string cn = TO_UTF8(item->data(Qt::UserRole).toString());

      mpTimeSensProblem->removeTargetCN(cn);

      pdelete(item);
    }
}
