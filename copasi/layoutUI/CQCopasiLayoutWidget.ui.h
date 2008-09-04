// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/Attic/CQCopasiLayoutWidget.ui.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/09/04 14:16:12 $
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

//#include <sstream>
#include <CopasiDataModel/CCopasiDataModel.h>
#include "UI/qtUtilities.h"
#include "utilities/utility.h"
#include "CQLayoutMainWindow.h"

#include "UI/CopasiFileDialog.h"
#include <qmessagebox.h>
#include <qregexp.h>

void CQCopasiLayoutWidget::init()
{}

void CQCopasiLayoutWidget::slotUpdateWidget()
{}

bool CQCopasiLayoutWidget::enter(const std::string &)
{
  slotUpdateWidget();
  return true;
}

void CQCopasiLayoutWidget::newFunction()
{}

void CQCopasiLayoutWidget::displayNetworkWidgetOld()
{
  //QApplication app(argc,argv);
  //mWin(this, "Reaction Network");
  QWidget* pWin = new CQLayoutMainWindow(this, "Reaction Network");
  //mWin((QWidget *)this,"Reaction Network");
  //app.setMainWidget(&gui);
  pWin->resize(900, 430);
  pWin->show();
}
