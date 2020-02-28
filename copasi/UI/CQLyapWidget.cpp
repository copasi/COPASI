// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQLyapWidget.h"

#include <QMessageBox>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CProgressBar.h"
#include "qtUtilities.h"

#include "copasi/lyap/CLyapTask.h"
#include "copasi/lyap/CLyapProblem.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/*
 *  Constructs a CQLyapWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQLyapWidget::CQLyapWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQLyapWidget::~CQLyapWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

bool CQLyapWidget::runTask()
{
  CLyapTask * pTask = dynamic_cast< CLyapTask * >(mpObject);

  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  return commonRunTask();
}

bool CQLyapWidget::taskFinishedEvent()
{
  mpListView->switchToOtherWidget(ListViews::WidgetType::LyapunovExponentsResult, std::string()); //change to the results window
  return true;
}

bool CQLyapWidget::loadTaskProtected()
{
  CLyapTask * pTask = dynamic_cast< CLyapTask * >(mpTask);

  if (!pTask) return false;

  CLyapProblem* pProblem =
    dynamic_cast< CLyapProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  mpEditExponent->setText(QString::number(pProblem->getExponentNumber()));

  assert(CRootContainer::getDatamodelList()->size() > 0);
  bool enabled =
    (mpDataModel->getModel()->getInitialTime() != pProblem->getTransientTime());

  mpCheckDelay->setChecked(enabled);
  mpEditDelay->setEnabled(enabled);
  mpEditDelay->setText(convertToQString(pProblem->getTransientTime()));

  mpCheckDivergence->setChecked(pProblem->divergenceRequested());

  mChanged = false;

  return true;
}

bool CQLyapWidget::saveTaskProtected()
{
  CLyapTask * pTask = dynamic_cast< CLyapTask * >(mpTask);

  if (!pTask) return false;

  CLyapProblem* pProblem =
    dynamic_cast< CLyapProblem * >(mpTask->getProblem());

  if (!pProblem) return false;

  if (QString::number(pProblem->getExponentNumber()) != mpEditExponent->text())
    {
      pProblem->setExponentNumber(std::max(0, mpEditExponent->text().toInt()));
      mChanged = true;
    }

  assert(mpDataModel != NULL);
  bool enabled =
    (mpDataModel->getModel()->getInitialTime() != pProblem->getTransientTime());

  if (mpCheckDelay->isChecked() != enabled ||
      (mpCheckDelay->isChecked() &&
       mpEditDelay->text() != convertToQString(pProblem->getTransientTime())))
    {
      if (mpCheckDelay->isChecked())
        pProblem->setTransientTime(mpEditDelay->text().toDouble());
      else
        pProblem->setTransientTime(mpDataModel->getModel()->getInitialTime());

      mChanged = true;
    }

  if (mpCheckDivergence->isChecked() != pProblem->divergenceRequested())
    {
      pProblem->setDivergenceRequested(mpCheckDivergence->isChecked());
      mChanged = true;
    }

  if (mChanged) mpDataModel->changed();

  mChanged = false;
  return true;
}

void CQLyapWidget::init()
{
  mpHeaderWidget->setTaskName("Lyapunov Exponents");

  vboxLayout->insertWidget(0, mpHeaderWidget);  // header
  // vboxLayout->insertSpacing(1, 14);       // space between header and body

  mpMethodWidget->showMethodParameters(true);
  vboxLayout->addWidget(mpMethodWidget);

  vboxLayout->addWidget(mpBtnWidget);     // 'footer'
}

void CQLyapWidget::slotDelayChecked()
{
  mpEditDelay->setEnabled(mpCheckDelay->isChecked());
}
