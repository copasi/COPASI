// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CMCAResultWidget.cpp,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:54:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include "copasi.h"

#include "CMCAResultWidget.h"
#include "CMCAResultSubwidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAMethod.h"
#include "qtUtilities.h"
#include "utilities/CCopasiVector.h"

/*
 *  Constructs a CMCAResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMCAResultWidget::CMCAResultWidget(QWidget* parent, const char* name, Qt::WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name)
    setName("CMCAResultWidget");
  setCaption(trUtf8("CMCAResultWidget"));

  mWidgetLayout = new Q3GridLayout(this, 1, 1, 0, -1, "Layout");

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
  CMCATask * pTask =
    dynamic_cast<CMCATask *>((*CCopasiDataModel::Global->getTaskList())["Metabolic Control Analysis"]);
  if (!pTask) return false;

  mCentralWidget->loadAll(dynamic_cast<CMCAMethod*>(pTask->getMethod()));
  return true;
}

bool CMCAResultWidget::saveToBackend()
{
  return true;
}

bool CMCAResultWidget::update(ListViews::ObjectType objectType,
                              ListViews::Action action,
                              const std::string & C_UNUSED(key))
{
  if (objectType == ListViews::MODEL && action == ListViews::ADD)
    mCentralWidget->loadAll(NULL);

  return true;
}

bool CMCAResultWidget::leave()
{
  return true;
}

bool CMCAResultWidget::enter(const std::string & C_UNUSED(key))
{
  return true;
}
