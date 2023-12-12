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

/*
 *  Created by Paul Willy on 5/21/10.
 */

#include "CQCrossSectionTaskWidget.h"
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

#include "copasi/crosssection/CCrossSectionTask.h"
#include "copasi/crosssection/CCrossSectionProblem.h"
//#include "copasi/crosssection/CCrossSectionMethod.h"

/*
 *  Constructs a CQCrossSectionWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCrossSectionTaskWidget::CQCrossSectionTaskWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
  , mpSingleVariable(NULL)
  , mpCrossSectionProblem(NULL)
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
CQCrossSectionTaskWidget::~CQCrossSectionTaskWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQCrossSectionTaskWidget::init()
{
  mpCrossSectionProblem = NULL;

  mpHeaderWidget->setTaskName("Cross Section");

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
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::CrossSectionResult));

  if (pResult != NULL)
    pResult->setTitle("<h2>Cross Section Result</h2>");
}

void CQCrossSectionTaskWidget::destroy()
{
  if (mpCrossSectionProblem != NULL)
    {
      mpCrossSectionProblem->setObjectParent(NULL);
      delete mpCrossSectionProblem;
    }
}

void CQCrossSectionTaskWidget::commitInput()
{
  if (!mpCrossSectionProblem) return;

  mpCrossSectionProblem->setFlagLimitCrossings(mpCheckSimCrossings->isChecked());
  mpCrossSectionProblem->setCrossingsLimit(mpTxtCrossings->text().toULong());
  mpCrossSectionProblem->setFlagLimitOutCrossings(mpCheckOutputCrossings->isChecked());
  mpCrossSectionProblem->setOutCrossingsLimit(mpTxtOutCrossings->text().toULong());
  mpCrossSectionProblem->setTimeLimit(mpTxtTime->text().toDouble());
  mpCrossSectionProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());
  mpCrossSectionProblem->setFlagLimitOutTime(mpCheckOutputDelay->isChecked());
  mpCrossSectionProblem->setFlagLimitConvergence(mpCheckSimConvergence->isChecked());
  mpCrossSectionProblem->setConvergenceTolerance(mpTxtConvergence->text().toDouble());
  mpCrossSectionProblem->setFlagLimitOutConvergence(mpCheckOutputConvergence->isChecked());
  mpCrossSectionProblem->setConvergenceOutTolerance(mpTxtOutConvergence->text().toDouble());
  mpCrossSectionProblem->setSingleObjectCN(mpSingleVariable);
  mpCrossSectionProblem->setPositiveDirection(mpDirectionPositive->isChecked());
  mpCrossSectionProblem->setThreshold(mpLineEditValue->text().toDouble());
}

bool CQCrossSectionTaskWidget::runTask()
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
bool CQCrossSectionTaskWidget::saveTaskProtected()
{
  // check the existence of Task
  CCrossSectionTask * pTask =
    dynamic_cast< CCrossSectionTask * >(mpTask);

  if (!pTask) return false;

  // check the existence of Problem
  CCrossSectionProblem* pProblem =
    dynamic_cast<CCrossSectionProblem *>(pTask->getProblem());
  assert(pProblem);

  // save the actual changes
  if (mpCheckSimConvergence->isChecked())
    pProblem->setCrossingsLimit(mpTxtCrossings->text().toULong());

  pProblem->setPositiveDirection(mpDirectionPositive->isChecked());
  pProblem->setThreshold(mpLineEditValue->text().toDouble());
  //if (mpCheckLT->isChecked())
  pProblem->setTimeLimit(mpTxtTime->text().toDouble());

  pProblem->setSingleObjectCN(mpSingleVariable);

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

bool CQCrossSectionTaskWidget::taskFinishedEvent()
{
  bool success = true;
  // We need to load the result here as this is the only place where
  // we know that it is correct.
  CQTimeSeriesWidget * pResult =
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::CrossSectionResult));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  return success;
}

/*
 * Function to load saved values of the Task
 */
bool CQCrossSectionTaskWidget::loadTaskProtected()
{
  // load Task
  CCrossSectionTask * pTask =
    dynamic_cast< CCrossSectionTask * >(mpTask);

  if (!pTask) return false;

  showUnits();

  // load Problem
  CCrossSectionProblem * pProblem = dynamic_cast<CCrossSectionProblem *>(pTask->getProblem());
  assert(pProblem);

  pdelete(mpCrossSectionProblem);
  mpCrossSectionProblem = new CCrossSectionProblem(*pProblem, NO_PARENT);

  // load the saved values
  const std::string &name = pProblem->getSingleObjectCN();

  if (name.empty())
    setSingleObject(NULL);
  else
    setSingleObject(static_cast<const CDataObject*>(pTask->getObjectDataModel()->getObject(name)));

  mpLineEditValue->setText(convertToQString(pProblem->getThreshold()));
  mpDirectionPositive->setChecked(mpCrossSectionProblem->isPositiveDirection());
  mpDirectionNegative->setChecked(!mpCrossSectionProblem->isPositiveDirection());

  mpCheckSimConvergence->setChecked(pProblem->getFlagLimitConvergence());
  mpTxtConvergence->setEnabled(pProblem->getFlagLimitConvergence());

  if (pProblem->getFlagLimitConvergence())
    mpTxtConvergence->setText(convertToQString(pProblem->getConvergenceTolerance()));
  else
    mpTxtConvergence->setText("");

  mpCheckOutputConvergence->setChecked(pProblem->getFlagLimitOutConvergence());
  mpTxtOutConvergence->setEnabled(pProblem->getFlagLimitOutConvergence());

  if (pProblem->getFlagLimitOutConvergence())
    mpTxtOutConvergence->setText(convertToQString(pProblem->getConvergenceOutTolerance()));
  else
    mpTxtOutConvergence->setText("");

  mpCheckSimCrossings->setChecked(pProblem->getFlagLimitCrossings());
  mpTxtCrossings->setEnabled(pProblem->getFlagLimitCrossings());

  if (pProblem->getFlagLimitCrossings())
    mpTxtCrossings->setText(convertToQString(pProblem->getCrossingsLimit()));
  else
    mpTxtCrossings->setText("");

  mpCheckOutputCrossings->setChecked(pProblem->getFlagLimitOutCrossings());
  mpTxtOutCrossings->setEnabled(pProblem->getFlagLimitOutCrossings());

  if (pProblem->getFlagLimitOutCrossings())
    mpTxtOutCrossings->setText(convertToQString(pProblem->getOutCrossingsLimit()));
  else
    mpTxtOutCrossings->setText("");

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

  mpValidatorCrossing->saved();
  mpValidatorTolerance->saved();
  mpValidatorOutTolerance->saved();
  mpValidatorLC->saved();
  mpValidatorOutLC->saved();
  mpValidatorTime->saved();
  mpValidatorOutTime->saved();

  return true;
}

void CQCrossSectionTaskWidget::slotChooseVariable()
{
  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::Variables + CQSimpleSelectionTree::ObservedValues, mpSingleVariable);

  setSingleObject(pObject);
}

void CQCrossSectionTaskWidget::setSingleObject(const CDataObject * pSingleVariable)
{
  mpSingleVariable = pSingleVariable;

  if (pSingleVariable == NULL)
    mpLineEditVariable->setText(tr("[Please Choose Object.] --->"));
  else
    mpLineEditVariable->setText(FROM_UTF8(pSingleVariable->getObjectDisplayName()));
}

void CQCrossSectionTaskWidget::slotValueRate()
{
  if (!mpLineEditValue->hasAcceptableInput())
    return;

  commitInput();
}

void CQCrossSectionTaskWidget::slotUpdateCrossings(bool b)
{
  mpTxtCrossings->setEnabled(b);

  if (!mpTxtCrossings->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setFlagLimitCrossings(b);
      mpCrossSectionProblem->setCrossingsLimit(mpTxtCrossings->text().toULong());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQCrossSectionTaskWidget::slotUpdateConvergence(bool b)
{
  mpTxtConvergence->setEnabled(b);

  if (!mpTxtConvergence->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setConvergenceTolerance(mpTxtConvergence->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQCrossSectionTaskWidget::slotOutputDelay(bool b)
{
  mpTxtOutTime->setEnabled(b);

  if (!mpTxtOutTime->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQCrossSectionTaskWidget::slotOutputCrossings(bool b)
{
  mpTxtOutCrossings->setEnabled(b);

  if (!mpTxtOutCrossings->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setOutCrossingsLimit(mpTxtOutCrossings->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }
}
void CQCrossSectionTaskWidget::slotOutputConvergence(bool b)
{
  mpTxtOutConvergence->setEnabled(b);

  if (!mpTxtOutConvergence->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setConvergenceOutTolerance(mpTxtOutConvergence->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }
}

void CQCrossSectionTaskWidget::slotUpdateTime()
{
  if (!mpTxtTime->hasAcceptableInput())
    return;

  commitInput();

  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotUpdateConvergenceTolerance()
{
  if (!mpTxtConvergence->hasAcceptableInput())
    return;

  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotUpdateCrossingsLimit()
{
  if (!mpTxtCrossings->hasAcceptableInput())
    return;

  // TODO: Implement
}

void CQCrossSectionTaskWidget::slotOutputConvergenceTolerance()
{
  if (!mpTxtOutConvergence->hasAcceptableInput())
    return;

  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotOutputCrossingsLimit()
{
  if (!mpTxtOutCrossings->hasAcceptableInput())
    return;

  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotOutputDelayTime()
{
  if (!mpTxtOutTime->hasAcceptableInput())
    return;

  // TODO: Implement
}

void CQCrossSectionTaskWidget::updateValues()
{
  mpTxtCrossings->setText(convertToQString(mpCrossSectionProblem->getCrossingsLimit()));
  mpValidatorLC->revalidate();

  mpTxtOutCrossings->setText(convertToQString(mpCrossSectionProblem->getOutCrossingsLimit()));
  mpValidatorOutLC->revalidate();

  mpTxtTime->setText(convertToQString(mpCrossSectionProblem->getTimeLimit()));
  mpValidatorTime->revalidate();

  mpTxtOutTime->setText(convertToQString(mpCrossSectionProblem->getOutputStartTime()));
  mpValidatorOutTime->revalidate();

  mpTxtConvergence->setText(convertToQString(mpCrossSectionProblem->getConvergenceTolerance()));
  mpValidatorTolerance->revalidate();

  mpTxtOutConvergence->setText(convertToQString(mpCrossSectionProblem->getConvergenceOutTolerance()));
  mpValidatorOutTolerance->revalidate();

  mpLineEditValue->setText(convertToQString(mpCrossSectionProblem->getThreshold()));
  mpValidatorCrossing->revalidate();
}

// virtual
bool CQCrossSectionTaskWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
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

void CQCrossSectionTaskWidget::showUnits()
{
  const CModel * pModel = NULL;

  QString TimeUnits;

  if (mpDataModel != NULL &&
      (pModel = mpDataModel->getModel()) != NULL)
    {
      TimeUnits = "(" + FROM_UTF8(CUnit::prettyPrint(pModel->getTimeUnit())) + ")";
    }

  mpLblDurationLimit->setText("if detection time " + TimeUnits + " larger");
  mpCheckOutputDelay->setText("if time " + TimeUnits + " larger");
}
