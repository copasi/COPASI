// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QLayout>

#include "copasi/copasi.h"

#include "CMCAResultWidget.h"
#include "CMCAResultSubwidget.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "qtUtilities.h"
#include "copasi/core/CDataVector.h"

/*
 *  Constructs a CMCAResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMCAResultWidget::CMCAResultWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : CopasiWidget(parent, name, fl)
{
  if (!name)
    setObjectName("CMCAResultWidget");

  setWindowTitle("CMCAResultWidget");

  mWidgetLayout = new QGridLayout(this);
  mWidgetLayout->setObjectName("Layout");

  mCentralWidget = new CMCAResultSubwidget(this, "CMCAResultSubwidget");
  mWidgetLayout->addWidget(mCentralWidget, 0, 0);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMCAResultWidget::~CMCAResultWidget()
{}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
bool CMCAResultWidget::loadFromBackend()
{
  assert(mpDataModel != NULL);
  CMCATask * pTask =
    dynamic_cast<CMCATask *>(&mpDataModel->getTaskList()->operator[]("Metabolic Control Analysis"));

  if (!pTask) return false;

  mCentralWidget->loadAll(dynamic_cast<CMCAMethod*>(pTask->getMethod()));
  return true;
}

bool CMCAResultWidget::saveToBackend()
{
  return true;
}

bool CMCAResultWidget::updateProtected(ListViews::ObjectType objectType,
                                       ListViews::Action action,
                                       const CCommonName & cn)
{
  if (objectType == ListViews::ObjectType::MODEL && action == ListViews::ADD)
    mCentralWidget->loadAll(NULL);

  return true;
}

bool CMCAResultWidget::leaveProtected()
{
  return true;
}

bool CMCAResultWidget::enterProtected()
{
  return true;
}
