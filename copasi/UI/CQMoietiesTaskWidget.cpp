// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QtGui/QCheckBox>
#include <QtCore/QVariant>

#include "copasi/UI/CQTaskBtnWidget.h"
#include "copasi/UI/CQTaskHeaderWidget.h"

#include "copasi/moieties/CMoietiesMethod.h"
#include "copasi/moieties/CMoietiesTask.h"
#include "CQMoietiesTaskWidget.h"

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
    mpListView->switchToOtherWidget(2221, ""); //change to the results window

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

CCopasiMethod * CQMoietiesTaskWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return CMoietiesMethod::createMethod(type);
}
