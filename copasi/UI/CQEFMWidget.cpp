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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQEFMWidget.h"

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CProgressBar.h"
#include "qtUtilities.h"
#include "CQMessageBox.h"
#include "CQEFMResultWidget.h"

#include "copasi/copasi.h"

#include "copasi/elementaryFluxModes/CEFMMethod.h"
#include "copasi/elementaryFluxModes/CEFMTask.h"

/*
 *  Constructs a CQEFMWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEFMWidget::CQEFMWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  mpHeaderWidget->setTaskName("Elementary Flux Modes");
  mpHeaderWidget->mpUpdateModel->hide();

  verticalLayout->insertWidget(0, mpHeaderWidget);
  verticalLayout->addWidget(mpBtnWidget);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQEFMWidget::~CQEFMWidget()
{}

bool CQEFMWidget::runTask()
{
  if (dynamic_cast< CEFMTask * >(mpTask) == NULL)
    return false;

  if (!commonBeforeRunTask()) return false;

  return commonRunTask();
}

bool CQEFMWidget::taskFinishedEvent()
{
  bool success = true;

  // We need to load the result here as this is the only place where
  // we know that it is correct.
  CQEFMResultWidget * pResult =
    dynamic_cast< CQEFMResultWidget * >(CopasiWidget::mpListView->createWidgetFromId(ListViews::WidgetType::ElementaryModesResult));

  if (pResult == NULL)
    return false;

  success &= pResult->loadResult(mpTask);

  if (success && isVisible())
    CopasiWidget::mpListView->switchToOtherWidget(ListViews::WidgetType::ElementaryModesResult, std::string()); //change to the results window

  return success;
}

bool CQEFMWidget::saveTaskProtected()
{
  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);

  if (!pTask) return false;

  return true;
}

bool CQEFMWidget::loadTaskProtected()
{
  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);

  if (!pTask) return false;

  return true;
}
