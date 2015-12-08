// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  Created by Paul Willy on 5/21/10.
 */

#include "CQAnalyticsWidget.h"
#include "CQTimeSeriesWidget.h"
#include "listviews.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CQMessageBox.h"
#include "CQValidator.h"

#include "resourcesUI/CQIconResource.h"

#include "copasi.h"

#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"

#include "analytics/CAnalyticsTask.h"
#include "analytics/CAnalyticsProblem.h"
//#include "crosssection/CCrossSectionMethod.h"

/*
 *  Constructs a CQAnalyticsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQAnalyticsWidget::CQAnalyticsWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
  , mpSingleVariable(NULL)
  , mpAnalyticsProblem(NULL)
  , mpValidatorLC(NULL)
  , mpValidatorTime(NULL)
  , mpValidatorTolerance(NULL)
  , mpValidatorOutLC(NULL)
  , mpValidatorOutTime(NULL)
  , mpValidatorOutTolerance(NULL)
  , mpValidatorCrossing(NULL)

{
  setupUi(this);
  mpButtonVariable->setIcon(CQIconResource::icon(CQIconResource::copasi));

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQAnalyticsWidget::~CQAnalyticsWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQAnalyticsWidget::init()
{
  mpAnalyticsProblem = NULL;

  mpHeaderWidget->setTaskName("Analytics");

  verticalLayout->insertWidget(0, mpHeaderWidget);

  mpMethodWidget->showMethodParameters(true);
  mpGridLayout->addWidget(mpMethodWidget->mpLblParameter, 11, 0, 1, 1);
  mpGridLayout->addWidget(mpMethodWidget->mpParameterView, 11, 1, 1, 2);

  // unsigned int ValidMethods = CTaskEnum::unset;
  // mpMethodWidget->setValidMethods(&ValidMethods);
  // mpMethodWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  // verticalLayout->addWidget(mpMethodWidget);
  verticalLayout->addWidget(mpBtnWidget);

  mpValidatorCrossing = new CQValidatorDouble(mpLineEditValue);
  mpLineEditValue->setValidator(mpValidatorCrossing);

  mpValidatorLC = new CQValidatorInt(mpTxtCrossings);
  mpValidatorLC->setRange(0, std::numeric_limits< int >::max());
  mpTxtCrossings->setValidator(mpValidatorLC);

  mpValidatorTime = new CQValidatorDouble(mpTxtTime);
  mpValidatorTime->setRange(0, std::numeric_limits< double >::max());
  mpTxtTime->setValidator(mpValidatorTime);

  mpValidatorOutTime = new CQValidatorDouble(mpTxtOutTime);
  mpTxtOutTime->setValidator(mpValidatorOutTime);

  mpValidatorTolerance = new CQValidatorDouble(mpTxtConvergence);
  mpTxtConvergence->setValidator(mpValidatorTolerance);

  mpValidatorOutLC = new CQValidatorInt(mpTxtOutCrossings);
  mpValidatorOutLC->setRange(0, std::numeric_limits< int >::max());
  mpTxtOutCrossings->setValidator(mpValidatorOutLC);

  mpValidatorOutTolerance = new CQValidatorDouble(mpTxtOutConvergence);
  mpTxtOutConvergence->setValidator(mpValidatorOutTolerance);

  CQTimeSeriesWidget * pResult =
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->findWidgetFromId(291));

  if (pResult != NULL)
    pResult->setTitle("<h2>Analytics Result</h2>");
}

void CQAnalyticsWidget::destroy()
{}

void CQAnalyticsWidget::commitInput()
{
  if (!mpAnalyticsProblem) return;

  mpAnalyticsProblem->setFlagLimitCrossings(mpCheckSimCrossings->isChecked());
  mpAnalyticsProblem->setCrossingsLimit(mpTxtCrossings->text().toULong());
  mpAnalyticsProblem->setFlagLimitOutCrossings(mpCheckOutputCrossings->isChecked());
  mpAnalyticsProblem->setOutCrossingsLimit(mpTxtOutCrossings->text().toULong());
  mpAnalyticsProblem->setTimeLimit(mpTxtTime->text().toDouble());
  mpAnalyticsProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());
  mpAnalyticsProblem->setFlagLimitOutTime(mpCheckOutputDelay->isChecked());
  mpAnalyticsProblem->setFlagLimitConvergence(mpCheckSimConvergence->isChecked());
  mpAnalyticsProblem->setConvergenceTolerance(mpTxtConvergence->text().toDouble());
  mpAnalyticsProblem->setFlagLimitOutConvergence(mpCheckOutputConvergence->isChecked());
  mpAnalyticsProblem->setConvergenceOutTolerance(mpTxtOutConvergence->text().toDouble());
  mpAnalyticsProblem->setSingleObjectCN(mpSingleVariable);
  mpAnalyticsProblem->setPositiveDirection(mpDirectionPositive->isChecked());
  mpAnalyticsProblem->setThreshold(mpLineEditValue->text().toDouble());
}

bool CQAnalyticsWidget::runTask()
{
  commitInput();

  if (!commonBeforeRunTask()) return false;

  bool success = true;

  if (!commonRunTask()) success = false;

  return success;
}

/*
 * Function to save actual changes of the Task
 */
bool CQAnalyticsWidget::saveTask()
{
  // check the existence of Task
  CAnalyticsTask * pTask =
    dynamic_cast< CAnalyticsTask * >(mpTask);

  if (!pTask) return false;

  // save functions from the Parent, TaskWidget
  saveCommon();
  saveMethod();

  // check the existence of Problem
  CAnalyticsProblem* pProblem =
    dynamic_cast<CAnalyticsProblem *>(pTask->getProblem());
  assert(pProblem);

  // save the actual changes
  if (mpCheckSimConvergence->isChecked())
    pProblem->setCrossingsLimit(mpTxtCrossings->text().toULong());

  pProblem->setPositiveDirection(mpDirectionPositive->isChecked());
  pProblem->setThreshold(mpLineEditValue->text().toDouble());
  //if (mpCheckLT->isChecked())
  pProblem->setTimeLimit(mpTxtTime->text().toDouble());

  pProblem->setSingleObjectCN(mpSingleVariable);

  //--- ETTORE start ---
  pProblem->retrieveSelectedObject(mpSingleVariable);
  //--- ETTORE end -----

  pProblem->setFlagLimitOutTime(mpCheckOutputDelay->isChecked());

  if (mpCheckOutputDelay->isChecked())
    {
      pProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());
    }

  pProblem->setFlagLimitCrossings(mpCheckSimCrossings->isChecked());
  pProblem->setCrossingsLimit(mpTxtCrossings->text().toULong());
  pProblem->setFlagLimitOutCrossings(mpCheckOutputCrossings->isChecked());
  pProblem->setOutCrossingsLimit(mpTxtOutCrossings->text().toULong());
  pProblem->setFlagLimitConvergence(mpCheckSimConvergence->isChecked());
  pProblem->setConvergenceTolerance(mpTxtConvergence->text().toDouble());
  pProblem->setFlagLimitOutConvergence(mpCheckOutputConvergence->isChecked());
  pProblem->setConvergenceOutTolerance(mpTxtOutConvergence->text().toDouble());

  mpValidatorCrossing->saved();
  mpValidatorTolerance->saved();
  mpValidatorOutTolerance->saved();
  mpValidatorLC->saved();
  mpValidatorOutLC->saved();
  mpValidatorTime->saved();
  mpValidatorOutTime->saved();

  return true;
}

bool CQAnalyticsWidget::taskFinishedEvent()
{
  bool success = true;
  // We need to load the result here as this is the only place where
  // we know that it is correct.
  CQTimeSeriesWidget * pResult =
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->findWidgetFromId(291));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  return success;
}

/*
 * Function to load saved values of the Task
 */
bool CQAnalyticsWidget::loadTask()
{
  // load Task
  CAnalyticsTask * pTask =
    dynamic_cast< CAnalyticsTask * >(mpTask);

  if (!pTask) return false;

  // load functions from the Parent, TaskWidget
  loadCommon();
  loadMethod();

  showUnits();

  // load Problem
  CAnalyticsProblem* pProblem =
    dynamic_cast<CAnalyticsProblem *>(pTask->getProblem());
  assert(pProblem);

  pdelete(mpAnalyticsProblem);
  mpAnalyticsProblem = new CAnalyticsProblem(*pProblem);

  // load the saved values
  const std::string &name = pProblem->getSingleObjectCN();

  if (name.empty())
    setSingleObject(NULL);
  else
    setSingleObject(static_cast<const CCopasiObject*>(pTask->getObjectDataModel()->getObject(name)));


  mpLineEditValue->setText(QString::number(pProblem->getThreshold()));
  mpDirectionPositive->setChecked(mpAnalyticsProblem->isPositiveDirection());
  mpDirectionNegative->setChecked(!mpAnalyticsProblem->isPositiveDirection());

  mpCheckSimConvergence->setChecked(pProblem->getFlagLimitConvergence());
  mpTxtConvergence->setEnabled(pProblem->getFlagLimitConvergence());

  if (pProblem->getFlagLimitConvergence())
    mpTxtConvergence->setText(QString::number(pProblem->getConvergenceTolerance()));
  else
    mpTxtConvergence->setText("");

  mpCheckOutputConvergence->setChecked(pProblem->getFlagLimitOutConvergence());
  mpTxtOutConvergence->setEnabled(pProblem->getFlagLimitOutConvergence());

  if (pProblem->getFlagLimitOutConvergence())
    mpTxtOutConvergence->setText(QString::number(pProblem->getConvergenceOutTolerance()));
  else
    mpTxtOutConvergence->setText("");

  mpCheckSimCrossings->setChecked(pProblem->getFlagLimitCrossings());
  mpTxtCrossings->setEnabled(pProblem->getFlagLimitCrossings());

  if (pProblem->getFlagLimitCrossings())
    mpTxtCrossings->setText(QString::number(pProblem->getCrossingsLimit()));
  else
    mpTxtCrossings->setText("");

  mpCheckOutputCrossings->setChecked(pProblem->getFlagLimitOutCrossings());
  mpTxtOutCrossings->setEnabled(pProblem->getFlagLimitOutCrossings());

  if (pProblem->getFlagLimitOutCrossings())
    mpTxtOutCrossings->setText(QString::number(pProblem->getOutCrossingsLimit()));
  else
    mpTxtOutCrossings->setText("");

  //mpCheckLT->setChecked(pProblem->getFlagLimitTime());
  if (pProblem->getFlagLimitOutTime())
    {
      mpCheckOutputDelay->setChecked(true);
      mpTxtOutTime->setEnabled(true);
      mpTxtOutTime->setText(QString::number(pProblem->getOutputStartTime()));
    }
  else
    {
      mpCheckOutputDelay->setChecked(false);
      mpTxtOutTime->setEnabled(false);
      mpTxtOutTime->setText("");
    }

  mpTxtTime->setText(QString::number(pProblem->getTimeLimit()));

  mpValidatorCrossing->saved();
  mpValidatorTolerance->saved();
  mpValidatorOutTolerance->saved();
  mpValidatorLC->saved();
  mpValidatorOutLC->saved();
  mpValidatorTime->saved();
  mpValidatorOutTime->saved();

  return true;
}

void CQAnalyticsWidget::slotChooseVariable()
{
  //--- ETTORE start ---
  //const CCopasiObject * pObject =
  //  CCopasiSelectionDialog::getObjectSingle(this,
  //      CQSimpleSelectionTree::Variables + CQSimpleSelectionTree::ObservedValues, mpSingleVariable);
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::Variables, mpSingleVariable);

 //--- ETTORE end -----

  setSingleObject(pObject);
}

void CQAnalyticsWidget::setSingleObject(const CCopasiObject * pSingleVariable)
{
  mpSingleVariable = pSingleVariable;

  if (pSingleVariable == NULL)
    mpLineEditVariable->setText(tr("[Please Choose Object.] --->"));
  else
    mpLineEditVariable->setText(FROM_UTF8(pSingleVariable->getObjectDisplayName()));
}

void CQAnalyticsWidget::slotValueRate()
{
  if (!mpLineEditValue->hasAcceptableInput())
    return;

  commitInput();
}

void CQAnalyticsWidget::slotUpdateCrossings(bool b)
{
  mpTxtCrossings->setEnabled(b);

  if (!mpTxtCrossings->hasAcceptableInput())
    return;

  try
    {
      mpAnalyticsProblem->setFlagLimitCrossings(b);
      mpAnalyticsProblem->setCrossingsLimit(mpTxtCrossings->text().toULong());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQAnalyticsWidget::slotUpdateConvergence(bool b)
{
  mpTxtConvergence->setEnabled(b);

  if (!mpTxtConvergence->hasAcceptableInput())
    return;

  try
    {
      mpAnalyticsProblem->setConvergenceTolerance(mpTxtConvergence->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQAnalyticsWidget::slotOutputDelay(bool b)
{
  mpTxtOutTime->setEnabled(b);

  if (!mpTxtOutTime->hasAcceptableInput())
    return;

  try
    {
      mpAnalyticsProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQAnalyticsWidget::slotOutputCrossings(bool b)
{
  mpTxtOutCrossings->setEnabled(b);

  if (!mpTxtOutCrossings->hasAcceptableInput())
    return;

  try
    {
      mpAnalyticsProblem->setOutCrossingsLimit(mpTxtOutCrossings->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }
}
void CQAnalyticsWidget::slotOutputConvergence(bool b)
{
  mpTxtOutConvergence->setEnabled(b);

  if (!mpTxtOutConvergence->hasAcceptableInput())
    return;

  try
    {
      mpAnalyticsProblem->setConvergenceOutTolerance(mpTxtOutConvergence->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }
}

void CQAnalyticsWidget::slotUpdateTime()
{
  if (!mpTxtTime->hasAcceptableInput())
    return;

  commitInput();

  // TODO: Implement
}
void CQAnalyticsWidget::slotUpdateConvergenceTolerance()
{
  if (!mpTxtConvergence->hasAcceptableInput())
    return;

  // TODO: Implement
}
void CQAnalyticsWidget::slotUpdateCrossingsLimit()
{
  if (!mpTxtCrossings->hasAcceptableInput())
    return;

  // TODO: Implement
}

void CQAnalyticsWidget::slotOutputConvergenceTolerance()
{
  if (!mpTxtOutConvergence->hasAcceptableInput())
    return;

  // TODO: Implement
}
void CQAnalyticsWidget::slotOutputCrossingsLimit()
{
  if (!mpTxtOutCrossings->hasAcceptableInput())
    return;

  // TODO: Implement
}
void CQAnalyticsWidget::slotOutputDelayTime()
{
  if (!mpTxtOutTime->hasAcceptableInput())
    return;

  // TODO: Implement
}

void CQAnalyticsWidget::updateValues()
{
  mpTxtCrossings->setText(QString::number(mpAnalyticsProblem->getCrossingsLimit()));
  mpValidatorLC->revalidate();

  mpTxtOutCrossings->setText(QString::number(mpAnalyticsProblem->getOutCrossingsLimit()));
  mpValidatorOutLC->revalidate();

  mpTxtTime->setText(QString::number(mpAnalyticsProblem->getTimeLimit()));
  mpValidatorTime->revalidate();

  mpTxtOutTime->setText(QString::number(mpAnalyticsProblem->getOutputStartTime()));
  mpValidatorOutTime->revalidate();

  mpTxtConvergence->setText(QString::number(mpAnalyticsProblem->getConvergenceTolerance()));
  mpValidatorTolerance->revalidate();

  mpTxtOutConvergence->setText(QString::number(mpAnalyticsProblem->getConvergenceOutTolerance()));
  mpValidatorOutTolerance->revalidate();

  mpLineEditValue->setText(QString::number(mpAnalyticsProblem->getThreshold()));
  mpValidatorCrossing->revalidate();
}

// virtual
bool CQAnalyticsWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & /* key */)
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

void CQAnalyticsWidget::showUnits()
{
  const CModel * pModel = NULL;

  QString TimeUnits;

  if (mpDataModel != NULL &&
      (pModel = mpDataModel->getModel()) != NULL)
    {
      TimeUnits = "(" + FROM_UTF8(pModel->getTimeUnitsDisplayString()) + ")";
    }

  mpLblDurationLimit->setText("if detection time " + TimeUnits + " larger:");
  mpCheckOutputDelay->setText("if time " + TimeUnits + " larger:");
}
