// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/SSAWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/16 19:55:37 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qtoolbutton.h>
#include <qlayout.h>
#include <qmessagebox.h>

#include "SSAWidget.h"

#include "ssa/CSSATask.h"

#include "qtUtilities.h"

#include "report/CKeyFactory.h"
#include "DataModelGUI.h"
#include "listviews.h"
#include "copasiui3window.h"
#include "CProgressBar.h"

#include "utilities/CCopasiException.h"

SSAWidget::SSAWidget(QWidget * parent, const char* name, WFlags fl)
    : TaskWidget(parent, name, fl)
{
  mpMethodLayout = new QGridLayout(this, 0, 1, 11, 6, "mpMethodLayout");
}

SSAWidget::~SSAWidget()
{}

void
SSAWidget::on_RunButton_clicked()
{
  runTask();
}

bool
SSAWidget::runTask()
{
  bool success = true;
  CCopasiMessage::clearDeque();

  if (!commonBeforeRunTask()) return false;

  CSSATask* mSSATask =
    dynamic_cast<CSSATask *>(GlobalKeys.get(mObjectKey));
  assert(mSSATask);

  success = commonRunTask();

  commonAfterRunTask();

  //if (success && isShown()) pListView->switchToOtherWidget(211, ""); //change to the results window

  return success;
}

bool
SSAWidget::loadTask()
{return true;}

bool
SSAWidget::saveTask()
{return true;}

CCopasiMethod *
SSAWidget::createMethod(const CCopasiMethod::SubType& subtype)
{return NULL;}
