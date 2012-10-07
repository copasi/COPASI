// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  Created by Paul Willy on 5/21/10.
 */

#include "CQCrossSectionTaskWidget.h"
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

  //verticalLayout->insertWidget(0, mpHeaderWidget); // header
  //formLayout->insertRow(0, mpHeaderWidget);
  outerLayout->insertWidget(0, mpHeaderWidget);

  mpMethodWidget->showMethodParameters(true);
  //verticalLayout->addWidget(mpMethodWidget);
  //formLayout->addRow(mpMethodWidget);
  outerLayout->addWidget(mpMethodWidget);
  //verticalLayout->addWidget(mpBtnWidget);      // 'footer'
  //formLayout->addWidget(mpBtnWidget);
  outerLayout->addWidget(mpBtnWidget);

  mpValidatorCrossing = new CQValidatorDouble(mpLineEditValue);
  mpLineEditValue->setValidator(mpValidatorCrossing);

  mpValidatorLC = new CQValidatorInt(mpTxtCrossings);
  mpValidatorLC->setRange(0, std::numeric_limits< int >::max());
  mpTxtCrossings->setValidator(mpValidatorLC);

  mpValidatorLT = new CQValidatorDouble(mpTxtTime);
  mpValidatorLT->setRange(0, std::numeric_limits< double >::max());
  mpTxtTime->setValidator(mpValidatorLT);

  mpValidator = new CQValidatorDouble(mpTxtOutTime);
  mpTxtOutTime->setValidator(mpValidator);
}

void CQCrossSectionTaskWidget::destroy()
{
  pdelete(mpCrossSectionProblem);
}

void CQCrossSectionTaskWidget::validateInput()
{
}

bool CQCrossSectionTaskWidget::runTask()
{
  validateInput();

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

  //if (mpCheckLT->isChecked())
  pProblem->setTimeLimit(mpTxtTime->text().toDouble());

  if (mpCheckOutputDelay->isChecked())
    pProblem->setOutputStartTime(mpTxtOutTime->text().toDouble());

  mpValidatorCrossing->saved();
  mpValidatorLC->saved();
  mpValidatorLT->saved();
  mpValidator->saved();

  return true;
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

  mpCheckSimConvergence->setChecked(pProblem->getFlagLimitCrossings());
  mpTxtCrossings->setEnabled(pProblem->getFlagLimitCrossings());

  if (pProblem->getFlagLimitCrossings())
    mpTxtCrossings->setText(QString::number(pProblem->getCrossingsLimit()));
  else
    mpTxtCrossings->setText("");

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
  mpValidatorLC->saved();
  mpValidatorLT->saved();
  mpValidator->saved();

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
        CQSimpleSelectionTree::Variables);

  if (pObject)
    {
      mpLineEditVariable->setText(FROM_UTF8(pObject->getObjectDisplayName()));
      mpSingleVariable = pObject;
    }
}

void CQCrossSectionTaskWidget::slotValueRate()
{
  /*  // check validity
    QString yt = mpLineEditValue->text();

  //  const QString number("^[0-9]+$");
    const QString number("[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?");

    QRegExp numberRegExp(number);
    numberRegExp.setPatternSyntax(QRegExp::RegExp2);

    if (numberRegExp.exactMatch(yt))
    {
      std::cout << "RIGHT yt = " << TO_UTF8(yt) << std::endl;
    }
    else
    {
      std::cout << "ERR yt = " << TO_UTF8(yt) << " - " << yt.length() << std::endl;

    mpLineEditValue->setText(yt.remove(yt.length()-1,1));
    yt = mpLineEditValue->text();
      std::cout << "TEST yt = " << TO_UTF8(yt) << std::endl;
    }
  */
}

void CQCrossSectionTaskWidget::slotUpdateCrossings(bool b)
{
  mpTxtCrossings->setEnabled(b);

  //if (!b && !(mpCheckLT->isChecked()))
//    mpCheckLT->setChecked(true);

  if (!mpTxtCrossings->hasAcceptableInput())
    return;

  try
    {
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
  mpTxtTime->setEnabled(b);

  if (!b && !(mpCheckSimConvergence->isChecked()))
    mpCheckSimConvergence->setChecked(true);

  if (!mpTxtTime->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setTimeLimit(mpTxtTime->text().toDouble());
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
  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotOutputConvergence(bool b)
{
  // TODO: Implement
}

void CQCrossSectionTaskWidget::slotUpdateTime()
{
  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotUpdateConvergenceTolerance()
{
  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotUpdateCrossingsLimit()
{
  // TODO: Implement
}

void CQCrossSectionTaskWidget::slotOutputConvergenceTolerance()
{
  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotOutputCrossingsLimit()
{
  // TODO: Implement
}
void CQCrossSectionTaskWidget::slotOutputDelayTime()
{
  // TODO: Implement
}

void CQCrossSectionTaskWidget::updateValues()
{
  mpTxtCrossings->setText(QString::number(mpCrossSectionProblem->getCrossingsLimit()));
  mpValidatorLC->revalidate();

  mpTxtTime->setText(QString::number(mpCrossSectionProblem->getTimeLimit()));
  mpValidatorLT->revalidate();

  mpTxtOutTime->setText(QString::number(mpCrossSectionProblem->getOutputStartTime()));
  mpValidator->revalidate();
}
