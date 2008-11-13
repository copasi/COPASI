// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQTSSAWidget.ui.h,v $
//   $Revision: 1.13.2.2 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2008/11/13 12:43:03 $
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

#include "copasi.h"

#include <qtable.h>
#include <qcombobox.h>
#include <qheader.h>
#include <qtabwidget.h>

#include "UI/CQTSSAResultSubWidget.h"
#include "UI/CQTSSAResultWidget.h"
#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "UI/CProgressBar.h"
#include "UI/CQValidator.h"
#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"

#include "tssanalysis/CTSSATask.h"
#include "tssanalysis/CTSSAProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"
#include "tssanalysis/CCSPMethod.h"
#include "tssanalysis/CILDMMethod.h"
#include "tssanalysis/CILDMModifiedMethod.h"
#include "CQTSSAResultSubWidget.h"
#include "CQTSSAResultWidget.h"

#define TSSAMAX 10000000

CTSSAMethod* pTSSMethod;

CILDMMethod *pILDM_Method;
CILDMModifiedMethod *pILDMModiMethod;

CQTSSAResultSubWidget* pTSSResultSubWidget;
CTSSATask * pCTSSATask;

class mpTSSResultSubWidget;
class QTabWidget;

void CQTSSAWidget::init()
{
  mpTSSAProblem = NULL;

  mpHeaderWidget->setTaskName("Time Scale Separation Analysis");

  CQTSSAWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQTSSAWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(CTSSATask::ValidMethods);
  addMethodParameterTable(0);

  mpValidatorDuration = new CQValidatorDouble(mpEditDuration);
  mpEditDuration->setValidator(mpValidatorDuration);

  mpValidatorIntervalSize = new CQValidatorDouble(mpEditIntervalSize);
  mpValidatorIntervalSize->setRange(0, DBL_MAX);
  mpEditIntervalSize->setValidator(mpValidatorIntervalSize);

  //mpLbDeuflTol->setText("Deuflhard Tolerance");

  connect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(disableDeuflhard(int)));
}

void CQTSSAWidget::destroy()
{
  pdelete(mpTSSAProblem);
}

void CQTSSAWidget::slotDuration()
{
  try
    {
      mpTSSAProblem->setDuration(mpEditDuration->text().toDouble());
    }
  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok,
                                QMessageBox::NoButton,
                                QMessageBox::NoButton);
    }

  mpEditIntervalSize->setText(QString::number(mpTSSAProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTSSAProblem->getStepNumber()));

  checkTimeSeries();
}

void CQTSSAWidget::slotIntervalSize()
{
  try
    {
      mpTSSAProblem->setStepSize(mpEditIntervalSize->text().toDouble());
    }

  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok,
                                QMessageBox::NoButton,
                                QMessageBox::NoButton);
    }

  mpEditIntervalSize->setText(QString::number(mpTSSAProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTSSAProblem->getStepNumber()));

  checkTimeSeries();
}

void CQTSSAWidget::slotIntervals()
{
  try
    {
      mpTSSAProblem->setStepNumber(mpEditIntervals->text().toULong());
    }
  catch (...)
    {
      CQMessageBox::information(this, QString("Information"),
                                FROM_UTF8(CCopasiMessage::getAllMessageText()),
                                QMessageBox::Ok,
                                QMessageBox::NoButton,
                                QMessageBox::NoButton);
    }

  mpEditIntervalSize->setText(QString::number(mpTSSAProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();

  checkTimeSeries();
}

bool CQTSSAWidget::saveTask()
{
  CTSSATask * pTask =
    dynamic_cast< CTSSATask * >(mpTask);
  if (!pTask) return false;

  saveCommon();
  saveMethod();

  CTSSAProblem* tssaproblem =
    dynamic_cast<CTSSAProblem *>(pTask->getProblem());
  assert(tssaproblem);

  //set the Deufelhard Tolerance
  tssaproblem->setDeufelhardTol(mpEditDeufelTol->text().toDouble());

  //numbers
  if (tssaproblem->getStepSize() != mpEditIntervalSize->text().toDouble())
    {
      tssaproblem->setStepSize(mpEditIntervalSize->text().toDouble());
      mChanged = true;
    }
  else if (tssaproblem->getStepNumber() != mpEditIntervals->text().toULong())
    {
      tssaproblem->setStepNumber(mpEditIntervals->text().toLong());
      mChanged = true;
    }

  if (tssaproblem->getDuration() != mpEditDuration->text().toDouble())
    {
      tssaproblem->setDuration(mpEditDuration->text().toDouble());
      mChanged = true;
    }

  if (tssaproblem->timeSeriesRequested() != mpCheckSave->isChecked())
    {
      tssaproblem->setTimeSeriesRequested(mpCheckSave->isChecked());
      mChanged = true;
    }

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();

  return true;
}

bool CQTSSAWidget::loadTask()
{
  CTSSATask * pTask =
    dynamic_cast< CTSSATask * >(mpTask);
  if (!pTask) return false;

  loadCommon();
  loadMethod();

  disableDeuflhard(mpBoxMethod->currentItem());

  CTSSAProblem* tssaproblem =
    dynamic_cast<CTSSAProblem *>(pTask->getProblem());
  assert(tssaproblem);

  pdelete(mpTSSAProblem);
  mpTSSAProblem = new CTSSAProblem(*tssaproblem);

  //numbers
  mpEditIntervalSize->setText(QString::number(tssaproblem->getStepSize()));
  mpEditIntervals->setText(QString::number(tssaproblem->getStepNumber()));
  mpEditDuration->setText(QString::number(tssaproblem->getDuration()));

  //get the Deufelhard Tolerance
  mpEditDeufelTol->setText(QString::number(tssaproblem->getDeufelhardTol()));

  //store time series checkbox
  mpCheckSave->setChecked(tssaproblem->timeSeriesRequested());
  checkTimeSeries();

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();

  return true;
}

CCopasiMethod * CQTSSAWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return CTSSAMethod::createTSSAMethod(type);
}

bool CQTSSAWidget::runTask()
{
  pCTSSATask =
    dynamic_cast<CTSSATask *>((*CCopasiDataModel::Global->getTaskList())["Time Scale Separation Analysis"]);
  if (!pCTSSATask) return false;

  pTSSMethod = dynamic_cast<CTSSAMethod*>(pCTSSATask->getMethod());
  if (!pTSSMethod)
    pTSSMethod->emptyVectors();

  checkTimeSeries();
  if (!commonBeforeRunTask()) return false;

  bool success = true;
  if (!commonRunTask()) success = false;

  if (!commonAfterRunTask()) success = false;

  // We need to load the result here as this is the only place where
  // we know that it is correct.
  CQTSSAResultWidget * pResult =
    dynamic_cast< CQTSSAResultWidget * >(mpListView->findWidgetFromId(271));

  if (pResult == NULL)
    return false;

  success &= pResult->loadFromBackend();

  pTSSResultSubWidget = pResult->getSubWidget();
  if (!pTSSResultSubWidget)
    return false;
  pTSSResultSubWidget->discardOldResults();

  pILDM_Method = dynamic_cast<CILDMMethod*>(pCTSSATask->getMethod());
  if (pILDM_Method)
    {
      pTSSResultSubWidget->changeToILDM();
    }
  else
    {
      pILDMModiMethod = dynamic_cast<CILDMModifiedMethod*>(pCTSSATask->getMethod());
      if (pILDMModiMethod)
        {
          pTSSResultSubWidget->changeToILDMModified();
        }
      else
        {
          pTSSResultSubWidget->changeToCSP();
        }
    }

  if (success)
    {

      pTSSResultSubWidget->setStepNumber();

      mpListView->switchToOtherWidget(271, ""); //change to the results window
    }

  return success;
}

void CQTSSAWidget::checkTimeSeries()
{
  if (mpEditIntervals->text().toLong() * CCopasiDataModel::Global->getModel()->getStateTemplate().getNumVariable() > TSSAMAX)
    {
      mpCheckSave->setChecked(false);
      mpCheckSave->setEnabled(false);
    }
  else
    {
      mpCheckSave->setEnabled(true);
    }
}

void CQTSSAWidget::disableDeuflhard(int i)
{
  if ((i == 2))
    {
      mpEditDeufelTol->setDisabled(true);
      mpLbDeuflTol->setDisabled(true);
    }
  else
    {
      mpEditDeufelTol->setDisabled(false);
      mpLbDeuflTol->setDisabled(false);
    }
}
