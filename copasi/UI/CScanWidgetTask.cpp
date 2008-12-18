// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetTask.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CScanWidgetTask.ui'
 **
 ** Created: Wed Oct 8 02:15:46 2008
 **      by: The User Interface Compiler ($Id: CScanWidgetTask.cpp,v 1.13 2008/12/18 19:57:33 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CScanWidgetTask.h"

#include <qvariant.h>
#include "CScanWidgetTask.ui.h"
/*
 *  Constructs a CScanWidgetTask as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetTask::CScanWidgetTask(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetTask::~CScanWidgetTask()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetTask::languageChange()
{
  retranslateUi(this);
}
