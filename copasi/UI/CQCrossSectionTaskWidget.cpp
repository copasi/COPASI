// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
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

#include "crosssection/CCrossSectionTask.h"
#include "crosssection/CCrossSectionProblem.h"
//#include "crosssection/CCrossSectionMethod.h"

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

  outerLayout->insertWidget(0, mpHeaderWidget);

  mpMethodWidget->showMethodParameters(true);

  outerLayout->addWidget(mpMethodWidget);
  outerLayout->addWidget(mpBtnWidget);

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
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->findWidgetFromId(281));

  if (pResult != NULL)
    pResult->setTitle("<h2>Cross Section Result</h2>");
}

void CQCrossSectionTaskWidget::destroy()
{
  pdelete(mpCrossSectionProblem);
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
bool CQCrossSectionTaskWidget::saveTask()
{
  // check the existence of Task
  CCrossSectionTask * pTask =
    dynamic_cast< CCrossSectionTask * >(mpTask);

  if (!pTask) return false;

  // save functions from the Parent, TaskWidget
  saveCommon();
  saveMethod();

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

  if (mpCheckOutputDelay->isChecked())
    pProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());

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
    dynamic_cast< CQTimeSeriesWidget * >(mpListView->findWidgetFromId(281));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  return success;
}

/*
 * Function to load saved values of the Task
 */
bool CQCrossSectionTaskWidget::loadTask()
{
  // load Task
  CCrossSectionTask * pTask =
    dynamic_cast< CCrossSectionTask * >(mpTask);

  if (!pTask) return false;

  // load functions from the Parent, TaskWidget
  loadCommon();
  loadMethod();

  // load Problem
  CCrossSectionProblem* pProblem =
    dynamic_cast<CCrossSectionProblem *>(pTask->getProblem());
  assert(pProblem);

  pdelete(mpCrossSectionProblem);
  mpCrossSectionProblem = new CCrossSectionProblem(*pProblem);

  //CCrossSectionMethod* pMethod =
  //  dynamic_cast<CCrossSectionMethod *>(pTask->getMethod());
  //assert(pMethod);

  //for now, we use a trajectory method
  CTrajectoryMethod* pMethod =
    dynamic_cast<CTrajectoryMethod *>(pTask->getMethod());
  assert(pMethod);

  // load the saved values
  const std::string &name = pProblem->getSingleObjectCN();

  if (name.empty())
    setSingleObject(NULL);
  else
    setSingleObject(static_cast<const CCopasiObject*>(pTask->getObjectDataModel()->getObject(name)));

  mpLineEditValue->setText(QString::number(pProblem->getThreshold()));
  mpDirectionPositive->setChecked(mpCrossSectionProblem->isPositiveDirection());
  mpDirectionNegative->setChecked(!mpCrossSectionProblem->isPositiveDirection());

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
  mpTxtTime->setEnabled(pProblem->getFlagLimitTime());

  if (pProblem->getFlagLimitTime())
    mpTxtTime->setText(QString::number(pProblem->getTimeLimit()));
  else
    mpTxtTime->setText("");

  if (pProblem->getOutputStartTime() > 0.0)
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

  mpValidatorCrossing->saved();
  mpValidatorTolerance->saved();
  mpValidatorOutTolerance->saved();
  mpValidatorLC->saved();
  mpValidatorOutLC->saved();
  mpValidatorTime->saved();
  mpValidatorOutTime->saved();

  return true;
}

CCopasiMethod * CQCrossSectionTaskWidget::createMethod(const CCopasiMethod::SubType & /* type */)
{
  return NULL;
}

void CQCrossSectionTaskWidget::slotChooseVariable()
{
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::Variables, mpSingleVariable);

  setSingleObject(pObject);
}

void CQCrossSectionTaskWidget::setSingleObject(const CCopasiObject * pSingleVariable)
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
  mpTxtCrossings->setText(QString::number(mpCrossSectionProblem->getCrossingsLimit()));
  mpValidatorLC->revalidate();

  mpTxtOutCrossings->setText(QString::number(mpCrossSectionProblem->getOutCrossingsLimit()));
  mpValidatorOutLC->revalidate();

  mpTxtTime->setText(QString::number(mpCrossSectionProblem->getTimeLimit()));
  mpValidatorTime->revalidate();

  mpTxtOutTime->setText(QString::number(mpCrossSectionProblem->getOutputStartTime()));
  mpValidatorOutTime->revalidate();

  mpTxtConvergence->setText(QString::number(mpCrossSectionProblem->getConvergenceTolerance()));
  mpValidatorTolerance->revalidate();

  mpTxtOutConvergence->setText(QString::number(mpCrossSectionProblem->getConvergenceOutTolerance()));
  mpValidatorOutTolerance->revalidate();

  mpLineEditValue->setText(QString::number(mpCrossSectionProblem->getThreshold()));
  mpValidatorCrossing->revalidate();
}
