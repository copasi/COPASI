// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/27 16:00:44 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  Created by Paul on 5/21/10.
 */

#include "copasi.h"

#include "CQCrossSectionTaskWidget.h"
#include "listviews.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"

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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQCrossSectionTaskWidget::languageChange()
{
  retranslateUi(this);
}

void CQCrossSectionTaskWidget::init()
{
  mpHeaderWidget->setTaskName("Cross Section");

  crossSectionTWLayout->insertWidget(0, mpHeaderWidget); // header
  // crossSectionTWLayout->insertSpacing(1, 14);      // space between header and body
  crossSectionTWLayout->addWidget(mpBtnWidget);      // 'footer'

  addMethodParameterTable(0);
}

bool CQCrossSectionTaskWidget::runTask()
{
  return true;
}

bool CQCrossSectionTaskWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
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
    pProblem->setCrossingsLimit(mpLineEditLC->text().toDouble());

  if (mpCheckLT->isChecked())
    pProblem->setTimeLimit(mpLineEditLT->text().toDouble());

  if (mpCheck->isChecked())
    pProblem->setOutputStartTime(mpLineEdit->text().toDouble());

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

  return true;
}

CCopasiMethod * CQCrossSectionTaskWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return NULL;
}
