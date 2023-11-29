// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/copasi.h"

#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/utilities/CCopasiException.h"

#include "copasi/analytics/CAnalyticsTask.h"
#include "copasi/analytics/CAnalyticsProblem.h"
//#include "copasi/crosssection/CCrossSectionMethod.h"

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
  mpHeaderWidget->mpUpdateModel->hide(); // There is no sense in allowing the model to be updated after running this task.
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

  mpValidatorTime = new CQValidatorDouble(mpTxtTime);
  mpValidatorTime->setRange(0, std::numeric_limits< double >::max());
  mpTxtTime->setValidator(mpValidatorTime);

  mpValidatorOutTime = new CQValidatorDouble(mpTxtOutTime);
  mpTxtOutTime->setValidator(mpValidatorOutTime);

  CQTimeSeriesWidget * pResult =
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::AnalyticsResult));

  if (pResult != NULL)
    pResult->setTitle("<h2>Analytics Result</h2>");
}

void CQAnalyticsWidget::destroy()
{}

void CQAnalyticsWidget::commitInput()
{
  if (!mpAnalyticsProblem) return;

  mpAnalyticsProblem->setFlagLimitCrossings(false);
  mpAnalyticsProblem->setCrossingsLimit(false);
  mpAnalyticsProblem->setFlagLimitOutCrossings(false);
  mpAnalyticsProblem->setTimeLimit(mpTxtTime->text().toDouble());
  mpAnalyticsProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());
  mpAnalyticsProblem->setFlagLimitOutTime(mpCheckOutputDelay->isChecked());
  mpAnalyticsProblem->setFlagLimitConvergence(false);
  mpAnalyticsProblem->setFlagLimitOutConvergence(false);
  mpAnalyticsProblem->setSingleObjectCN(mpSingleVariable);
  mpAnalyticsProblem->setPositiveDirection(mpDirectionPositive->isChecked());
  mpAnalyticsProblem->setThreshold(0.0);
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
bool CQAnalyticsWidget::saveTaskProtected()
{
  // check the existence of Task
  CAnalyticsTask * pTask =
    dynamic_cast< CAnalyticsTask * >(mpTask);

  if (!pTask) return false;

  // save functions from the Parent, TaskWidget
  // check the existence of Problem
  CAnalyticsProblem* pProblem =
    dynamic_cast<CAnalyticsProblem *>(pTask->getProblem());
  assert(pProblem);

  pProblem->setPositiveDirection(mpDirectionPositive->isChecked());

  pProblem->setThreshold(0.0);

  pProblem->setTimeLimit(mpTxtTime->text().toDouble());

  pProblem->setSingleObjectCN(mpSingleVariable);

  pProblem->retrieveSelectedObject(mpSingleVariable);

  pProblem->setFlagLimitOutTime(mpCheckOutputDelay->isChecked());

  if (mpCheckOutputDelay->isChecked())
    {
      pProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());
    }

  pProblem->setFlagLimitCrossings(false);
  pProblem->setFlagLimitOutCrossings(false);
  pProblem->setFlagLimitConvergence(false);
  pProblem->setFlagLimitOutConvergence(false);

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
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::AnalyticsResult));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  return success;
}

/*
 * Function to load saved values of the Task
 */
bool CQAnalyticsWidget::loadTaskProtected()
{
  // load Task
  CAnalyticsTask * pTask =
    dynamic_cast< CAnalyticsTask * >(mpTask);

  if (!pTask) return false;

  showUnits();

  // load Problem
  CAnalyticsProblem * pProblem = dynamic_cast<CAnalyticsProblem *>(pTask->getProblem());
  assert(pProblem);

  pdelete(mpAnalyticsProblem);
  mpAnalyticsProblem = new CAnalyticsProblem(*pProblem, NO_PARENT);

  // load the saved values
  const std::string &name = pProblem->getSingleObjectCN();

  if (name.empty())
    setSingleObject(NULL);
  else
    setSingleObject(static_cast<const CDataObject*>(pTask->getObjectDataModel()->getObject(name)));

  mpDirectionPositive->setChecked(mpAnalyticsProblem->isPositiveDirection());
  mpDirectionNegative->setChecked(!mpAnalyticsProblem->isPositiveDirection());

  //mpCheckLT->setChecked(pProblem->getFlagLimitTime());
  if (pProblem->getFlagLimitOutTime())
    {
      mpCheckOutputDelay->setChecked(true);
      mpTxtOutTime->setEnabled(true);
      mpTxtOutTime->setText(convertToQString(pProblem->getOutputStartTime()));
    }
  else
    {
      mpCheckOutputDelay->setChecked(false);
      mpTxtOutTime->setEnabled(false);
      mpTxtOutTime->setText("");
    }

  mpTxtTime->setText(convertToQString(pProblem->getTimeLimit()));

  mpValidatorTime->saved();
  mpValidatorOutTime->saved();

  return true;
}

void CQAnalyticsWidget::slotChooseVariable()
{
  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::Variables, mpSingleVariable);

  setSingleObject(pObject);
}

void CQAnalyticsWidget::setSingleObject(const CDataObject * pSingleVariable)
{
  mpSingleVariable = pSingleVariable;

  if (pSingleVariable == NULL)
    mpLineEditVariable->setText(tr("[Please Choose Object.] --->"));
  else
    mpLineEditVariable->setText(FROM_UTF8(pSingleVariable->getObjectDisplayName()));
}

void CQAnalyticsWidget::slotValueRate()
{
  commitInput();
}

void CQAnalyticsWidget::slotUpdateCrossings(bool b)
{
//  updateValues();
}

void CQAnalyticsWidget::slotUpdateConvergence(bool b)
{
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
{}

void CQAnalyticsWidget::slotOutputConvergence(bool b)
{}

void CQAnalyticsWidget::slotUpdateTime()
{
  if (!mpTxtTime->hasAcceptableInput())
    return;

  commitInput();

  // TODO: Implement
}

void CQAnalyticsWidget::slotUpdateConvergenceTolerance()
{
  // TODO: Implement
}

void CQAnalyticsWidget::slotUpdateCrossingsLimit()
{
  // TODO: Implement
}

void CQAnalyticsWidget::slotOutputConvergenceTolerance()
{
  // TODO: Implement
}
void CQAnalyticsWidget::slotOutputCrossingsLimit()
{}

void CQAnalyticsWidget::slotOutputDelayTime()
{
  if (!mpTxtOutTime->hasAcceptableInput())
    return;

  // TODO: Implement
}

void CQAnalyticsWidget::updateValues()
{
  mpTxtTime->setText(convertToQString(mpAnalyticsProblem->getTimeLimit()));
  mpValidatorTime->revalidate();

  mpTxtOutTime->setText(convertToQString(mpAnalyticsProblem->getOutputStartTime()));
  mpValidatorOutTime->revalidate();
}

// virtual
bool CQAnalyticsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
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

void CQAnalyticsWidget::showUnits()
{
  const CModel * pModel = NULL;

  QString TimeUnits;

  if (mpDataModel != NULL &&
      (pModel = mpDataModel->getModel()) != NULL)
    {
      TimeUnits = "(" + FROM_UTF8(CUnit::prettyPrint(pModel->getTimeUnit())) + ")";
    }

  mpLblEndTime->setText("End-time " + TimeUnits);
  mpCheckOutputDelay->setText("Start-time " + TimeUnits);
}
