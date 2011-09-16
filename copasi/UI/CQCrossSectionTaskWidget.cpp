// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.15.2.2 $
//   $Name: Build-33 $
//   $Author: shoops $
//   $Date: 2011/02/17 19:14:45 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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
#include "UI/icons/Copasi16-Alpha.xpm"
#include "CQMessageBox.h"
#include "CQValidator.h"

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
#include "crosssection/CCrossSectionMethod.h"

/*
 *  Constructs a CQCrossSectionWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCrossSectionTaskWidget::CQCrossSectionTaskWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  setupUi(this);
  mpButtonVariable->setIcon(QPixmap(Copasi16_Alpha_xpm));

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

  verticalLayout->insertWidget(0, mpHeaderWidget); // header

  mpMethodWidget->enableMethodParameter(true);
  verticalLayout->addWidget(mpMethodWidget);

  verticalLayout->addWidget(mpBtnWidget);      // 'footer'

  mpValidatorCrossing = new CQValidatorDouble(mpLineEditValue);
  mpLineEditValue->setValidator(mpValidatorCrossing);

  mpValidatorLC = new CQValidatorInt(mpLineEditLC);
  mpValidatorLC->setRange(0, std::numeric_limits< int >::max());
  mpLineEditLC->setValidator(mpValidatorLC);

  mpValidatorLT = new CQValidatorDouble(mpLineEditLT);
  mpValidatorLT->setRange(0, std::numeric_limits< double >::max());
  mpLineEditLT->setValidator(mpValidatorLT);

  mpValidator = new CQValidatorDouble(mpLineEdit);
  mpLineEdit->setValidator(mpValidator);
}


void CQCrossSectionTaskWidget::destroy()
{
  pdelete(mpCrossSectionProblem);
}


bool CQCrossSectionTaskWidget::runTask()
{
  return true;
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

  if (mpCheckLC->isChecked())
    pProblem->setCrossingsLimit(mpLineEditLC->text().toULong());

  if (mpCheckLT->isChecked())
    pProblem->setTimeLimit(mpLineEditLT->text().toDouble());

  if (mpCheck->isChecked())
    pProblem->setOutputStartTime(mpLineEdit->text().toDouble());

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

  CCrossSectionMethod* pMethod =
    dynamic_cast<CCrossSectionMethod *>(pTask->getMethod());
  assert(pMethod);

  // load the saved values

  mpCheckLC->setChecked(pProblem->getFlagLimitCrossings());
  mpLineEditLC->setEnabled(pProblem->getFlagLimitCrossings());

  if (pProblem->getFlagLimitCrossings())
    mpLineEditLC->setText(QString::number(pProblem->getCrossingsLimit()));
  else
    mpLineEditLC->setText("");

  mpCheckLT->setChecked(pProblem->getFlagLimitTime());
  mpLineEditLT->setEnabled(pProblem->getFlagLimitTime());

  if (pProblem->getFlagLimitTime())
    mpLineEditLT->setText(QString::number(pProblem->getTimeLimit()));
  else
    mpLineEditLT->setText("");

  if (pProblem->getOutputStartTime() > 0.0)
    {
      mpCheck->setChecked(true);
      mpLineEdit->setEnabled(true);
      mpLineEdit->setText(QString::number(pProblem->getOutputStartTime()));
    }
  else
    {
      mpCheck->setChecked(false);
      mpLineEdit->setEnabled(false);
      mpLineEdit->setText("");
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
                                            CQSimpleSelectionTree::InitialTime |
                                            CQSimpleSelectionTree::Parameters);

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

void CQCrossSectionTaskWidget::slotUpdateLC(bool b)
{
  mpLineEditLC->setEnabled(b);

  if (!b && !(mpCheckLT->isChecked()))
    mpCheckLT->setChecked(true);

  if (!mpLineEditLC->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setCrossingsLimit(mpLineEditLC->text().toULong());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQCrossSectionTaskWidget::slotUpdateLT(bool b)
{
  mpLineEditLT->setEnabled(b);

  if (!b && !(mpCheckLC->isChecked()))
    mpCheckLC->setChecked(true);

  if (!mpLineEditLT->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setTimeLimit(mpLineEditLT->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQCrossSectionTaskWidget::slotUpdateSupress(bool b)
{
  mpLineEdit->setEnabled(b);

  if (!mpLineEdit->hasAcceptableInput())
    return;

  try
    {
      mpCrossSectionProblem->setOutputStartTime(mpLineEdit->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok, QMessageBox::Ok);
    }

//  updateValues();
}

void CQCrossSectionTaskWidget::updateValues()
{
  mpLineEditLC->setText(QString::number(mpCrossSectionProblem->getCrossingsLimit()));
  mpValidatorLC->revalidate();

  mpLineEditLT->setText(QString::number(mpCrossSectionProblem->getTimeLimit()));
  mpValidatorLT->revalidate();

  mpLineEdit->setText(QString::number(mpCrossSectionProblem->getOutputStartTime()));
  mpValidator->revalidate();
}

