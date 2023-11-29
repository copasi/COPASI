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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQTSSAWidget.h"

#include "copasi/copasi.h"

#include "CQTSSAResultSubWidget.h"
#include "CQTSSAResultWidget.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "CQValidator.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/tssanalysis/CTSSATask.h"
#include "copasi/tssanalysis/CTSSAProblem.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/tssanalysis/CCSPMethod.h"
#include "copasi/tssanalysis/CILDMMethod.h"
#include "copasi/tssanalysis/CILDMModifiedMethod.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/*
 *  Constructs a CQTSSAWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQTSSAWidget::CQTSSAWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTSSAWidget::~CQTSSAWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQTSSAWidget::init()
{
  mpTSSAProblem = NULL;

  mpHeaderWidget->setTaskName("Time Scale Separation Analysis");

  vboxLayout->insertWidget(0, mpHeaderWidget);  // header
  // vboxLayout->insertSpacing(1, 14);       // space between header and body

  mpMethodWidget->setValidMethods(CTSSATask::ValidMethods);
  mpMethodWidget->showMethodParameters(true);
  vboxLayout->addWidget(mpMethodWidget);

  vboxLayout->addWidget(mpBtnWidget);     // 'footer'

  mpValidatorDuration = new CQValidatorDouble(mpEditDuration);
  mpEditDuration->setValidator(mpValidatorDuration);

  mpValidatorIntervalSize = new CQValidatorDouble(mpEditIntervalSize);
  mpValidatorIntervalSize->setRange(0, std::numeric_limits< C_FLOAT64 >::max());
  mpEditIntervalSize->setValidator(mpValidatorIntervalSize);
}

void CQTSSAWidget::destroy()
{
  if (mpTSSAProblem != NULL)
    {
      mpTSSAProblem->setObjectParent(NULL);
      delete mpTSSAProblem;
    }
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
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(convertToQString(mpTSSAProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTSSAProblem->getStepNumber()));
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
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(convertToQString(mpTSSAProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
  mpEditIntervals->setText(QString::number(mpTSSAProblem->getStepNumber()));
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
                                QMessageBox::Ok, QMessageBox::Ok);
    }

  mpEditIntervalSize->setText(convertToQString(mpTSSAProblem->getStepSize()));
  mpValidatorIntervalSize->revalidate();
}

bool CQTSSAWidget::saveTaskProtected()
{
  CTSSATask * pTask =
    dynamic_cast< CTSSATask * >(mpTask);

  if (!pTask) return false;

  CTSSAProblem* pTssaProblem =
    dynamic_cast<CTSSAProblem *>(pTask->getProblem());

  if (!pTssaProblem)
    return false;

  //numbers
  if (pTssaProblem->getStepSize() != mpEditIntervalSize->text().toDouble())
    {
      pTssaProblem->setStepSize(mpEditIntervalSize->text().toDouble());
      mChanged = true;
    }
  else if (pTssaProblem->getStepNumber() != mpEditIntervals->text().toULong())
    {
      pTssaProblem->setStepNumber(mpEditIntervals->text().toLong());
      mChanged = true;
    }

  if (pTssaProblem->getDuration() != mpEditDuration->text().toDouble())
    {
      pTssaProblem->setDuration(mpEditDuration->text().toDouble());
      mChanged = true;
    }

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();

  return true;
}

bool CQTSSAWidget::loadTaskProtected()
{
  CTSSATask * pTask =
    dynamic_cast< CTSSATask * >(mpTask);

  if (!pTask) return false;

  CTSSAProblem * pTssaProblem = dynamic_cast<CTSSAProblem *>(pTask->getProblem());

  if (!pTssaProblem)
    return false;

  pdelete(mpTSSAProblem);
  mpTSSAProblem = new CTSSAProblem(*pTssaProblem, NO_PARENT);

  //numbers
  mpEditIntervalSize->setText(convertToQString(pTssaProblem->getStepSize()));
  mpEditIntervals->setText(QString::number(pTssaProblem->getStepNumber()));
  mpEditDuration->setText(convertToQString(pTssaProblem->getDuration()));

  mpValidatorDuration->saved();
  mpValidatorIntervalSize->saved();

  return true;
}

bool CQTSSAWidget::runTask()
{
  assert(mpDataModel != NULL);
  mpCTSSATask =
    dynamic_cast<CTSSATask *>(&mpDataModel->getTaskList()->operator[]("Time Scale Separation Analysis"));

  if (!mpCTSSATask) return false;

  mpTSSMethod = dynamic_cast<CTSSAMethod*>(mpCTSSATask->getMethod());

  if (!mpTSSMethod)
    mpTSSMethod->emptyVectors();

  if (!commonBeforeRunTask()) return false;

  bool success = true;

  if (!commonRunTask()) success = false;

  return success;
}

bool CQTSSAWidget::taskFinishedEvent()
{
  // We need to load the result here as this is the only place where
  // we know that it is correct.
  CQTSSAResultWidget * pResult =
    dynamic_cast< CQTSSAResultWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::TimeScaleSeparationAnalysisResult));

  if (pResult == NULL)
    {
      return false;
    }

  mpTSSResultSubWidget = pResult->getSubWidget();

  if (!mpTSSResultSubWidget)
    return false;

  mpTSSResultSubWidget->discardOldResults();

  mpTSSResultSubWidget->displayResult();
  mpListView->switchToOtherWidget(ListViews::WidgetType::TimeScaleSeparationAnalysisResult, std::string()); //change to the results window

  return true;
}

bool CQTSSAWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (objectType == ListViews::ObjectType::MODEL && action == ListViews::DELETE)
    {
      // need to clear annotated matrices, as otherwise they will hold pointers to non-existing things.
      CQTSSAResultWidget * pResult =
        dynamic_cast< CQTSSAResultWidget * >(mpListView->createWidgetFromId(ListViews::WidgetType::TimeScaleSeparationAnalysisResult));

      if (pResult == NULL)
        {
          return false;
        }

      mpTSSResultSubWidget = pResult->getSubWidget();

      if (!mpTSSResultSubWidget)
        return false;

      mpTSSResultSubWidget->discardOldResults();
    }

  return true;
}
