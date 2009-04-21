// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQLyapWidget.ui.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/21 16:20:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include <qmessagebox.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CProgressBar.h"

#include "lyap/CLyapTask.h"
#include "lyap/CLyapProblem.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "report/CCopasiRootContainer.h"

bool CQLyapWidget::runTask()
{
  CLyapTask * pTask =
    dynamic_cast< CLyapTask * >(CCopasiRootContainer::getKeyFactory()->get(mObjectKey));

  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  commonAfterRunTask();

  if (success)
    mpListView->switchToOtherWidget(261, ""); //change to the results window

  return success;
}

CCopasiMethod * CQLyapWidget::createMethod(const CCopasiMethod::SubType & type)
{return CLyapMethod::createMethod(type);}

bool CQLyapWidget::loadTask()
{
  CLyapTask * pTask = dynamic_cast< CLyapTask * >(mpTask);

  if (!pTask) return false;

  loadCommon();
  loadMethod();

  CLyapProblem* pProblem =
    dynamic_cast< CLyapProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  mpEditExponent->setText(QString::number(pProblem->getExponentNumber()));

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  bool enabled =
    ((*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getInitialTime() != pProblem->getTransientTime());

  mpCheckDelay->setChecked(enabled);
  mpEditDelay->setEnabled(enabled);
  mpEditDelay->setText(QString::number(pProblem->getTransientTime()));

  mpCheckDivergence->setChecked(pProblem->divergenceRequested());

  mChanged = false;

  return true;
}

bool CQLyapWidget::saveTask()
{
  CLyapTask * pTask = dynamic_cast< CLyapTask * >(mpTask);

  if (!pTask) return false;

  saveCommon();
  saveMethod();

  CLyapProblem* pProblem =
    dynamic_cast< CLyapProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  if (QString::number(pProblem->getExponentNumber()) != mpEditExponent->text())
    {
      pProblem->setExponentNumber(std::max(0, mpEditExponent->text().toInt()));
      mChanged = true;
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  bool enabled =
    ((*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getInitialTime() != pProblem->getTransientTime());

  if (mpCheckDelay->isChecked() != enabled ||
      (mpCheckDelay->isChecked() &&
       mpEditDelay->text() != QString::number(pProblem->getTransientTime())))
    {
      if (mpCheckDelay->isChecked())
        pProblem->setTransientTime(mpEditDelay->text().toDouble());
      else
        pProblem->setTransientTime((*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getInitialTime());

      mChanged = true;
    }

  if (mpCheckDivergence->isChecked() != pProblem->divergenceRequested())
    {
      pProblem->setDivergenceRequested(mpCheckDivergence->isChecked());
      mChanged = true;
    }

  if (mChanged)(*CCopasiRootContainer::getDatamodelList())[0]->changed();

  mChanged = false;
  return true;
}

void CQLyapWidget::init()
{
  mpHeaderWidget->setTaskName("Lyapunov Exponents");

  vboxLayout->insertWidget(0, mpHeaderWidget);
  vboxLayout->addWidget(mpBtnWidget);

  CQValidatorInt* tmpval = new CQValidatorInt(mpEditExponent);
  tmpval->setRange(0, LONG_MAX);
  mpEditExponent->setValidator(tmpval);

  //  addMethodSelectionBox(CLyapTask::ValidMethods);
  addMethodParameterTable(0, 2);
}

void CQLyapWidget::slotDelayChecked()
{
  mpEditDelay->setEnabled(mpCheckDelay->isChecked());
}
