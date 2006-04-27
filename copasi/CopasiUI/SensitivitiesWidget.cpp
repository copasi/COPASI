/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SensitivitiesWidget.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:45 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qfiledialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>

#include "SensitivitiesWidget.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "listviews.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"

/**
 *  Constructs a SensitivitiesWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SensitivitiesWidget::SensitivitiesWidget(QWidget* parent, const char* name, WFlags fl)
    : TaskWidget(parent, name, fl)
{
  if (!name)
    setName("SensitivitiesWidget");
  setCaption(trUtf8("SensitivitiesWidget"));

  //if a mpMethodLayout is created here, it will be used by addMethodXXX() below.
  mpMethodLayout = new QGridLayout(this, 1, 1, 11, 6, "mpMethodLayout");

  //SensitivitiesWidgetLayout->insertWidget(0, mpHeaderWidget);

  mpHeaderWidget->setTaskName("Sensitivities");
  addHeaderToGrid();
  addHLineToGrid(mpMethodLayout, 1, 2);

  //addMethodSelectionBox(CSensTask::ValidMethods);
  addMethodParameterTable();

  //QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //mpMethodLayout->addMultiCell(spacer, 10, 10, 0, 1);

  mpMethodLayout->addMultiCellWidget(mpBtnWidget, 11, 11, 0, 2);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SensitivitiesWidget::~SensitivitiesWidget()
{}

bool SensitivitiesWidget::saveTask()
{
  //saveCommon();
  //saveMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(GlobalKeys.get(mObjectKey));
  assert(sensTask);

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);

  CSensMethod* method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());
  assert(method);

  //...

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  if (mChanged) CCopasiDataModel::Global->changed();
  return true;
}

CCopasiMethod * SensitivitiesWidget::createMethod(const CCopasiMethod::SubType & type)
{return CSensMethod::createSensMethod(type);}

bool SensitivitiesWidget::runTask()
{
  //if (!commonBeforeRunTask()) return false;

  //commonAfterRunTask();

  //pListView->switchToOtherWidget(211, ""); //change to the results window

  return true;
}

bool SensitivitiesWidget::loadTask()
{
  //loadCommon();
  //loadMethod();

  CSensTask* sensTask =
    dynamic_cast<CSensTask *>(GlobalKeys.get(mObjectKey));
  assert(sensTask);

  CSensProblem* problem =
    dynamic_cast<CSensProblem *>(sensTask->getProblem());
  assert(problem);

  CSensMethod* method =
    dynamic_cast<CSensMethod *>(sensTask->getMethod());
  assert(method);

  //...

  mChanged = false;

  return true;
}
