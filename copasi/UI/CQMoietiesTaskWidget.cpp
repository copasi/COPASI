// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QCheckBox>
#include <QtCore/QVariant>

#include "CQMoietiesTaskWidget.h"

#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"

#include "copasi.h"

#include "moieties/CMoietiesMethod.h"
#include "moieties/CMoietiesTask.h"

/*
 *  Constructs a CQMoietiesTaskWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMoietiesTaskWidget::CQMoietiesTaskWidget(QWidget* parent, const char* name)
  : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMoietiesTaskWidget::~CQMoietiesTaskWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

void CQMoietiesTaskWidget::init()
{
  mpHeaderWidget->setTaskName("Mass Conservation");
  mpHeaderWidget->mpUpdateModel->hide();

  vboxLayout->insertWidget(0, mpHeaderWidget);
  vboxLayout->addWidget(mpBtnWidget);
}

void CQMoietiesTaskWidget::destroy()
{}

bool CQMoietiesTaskWidget::runTask()
{
  if (dynamic_cast< CMoietiesTask * >(mpTask) == NULL)
    return false;

  if (!commonBeforeRunTask()) return false;

  return commonRunTask();
}

bool CQMoietiesTaskWidget::taskFinishedEvent()
{
  bool success = true;

  if (success && isVisible())
    mpListView->switchToOtherWidget(2221, std::string()); //change to the results window

  return success;
}

bool CQMoietiesTaskWidget::saveTask()
{
  if (dynamic_cast< CMoietiesTask * >(mpTask) == NULL)
    return false;

  saveCommon();

  return true;
}

bool CQMoietiesTaskWidget::loadTask()
{
  if (dynamic_cast< CMoietiesTask * >(mpTask) == NULL)
    return false;

  loadCommon();

  return true;
}
