// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQTSSAResultSubWidget.cpp,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/10 09:54:48 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTSSAResultSubWidget.ui'
 **
 ** Created: Fri Oct 10 11:13:33 2008
 **      by: The User Interface Compiler ($Id: CQTSSAResultSubWidget.cpp,v 1.11 2008/10/10 09:54:48 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTSSAResultSubWidget.h"

#include <qvariant.h>
#include <qregexp.h>
#include "qmessagebox.h"
#include "q3filedialog.h"
#include "CTimeSeriesTable.h"
#include "CQArrayAnnotationsWidget.h"
#include "CQTSSAResultSubWidget.ui.h"
/*
 *  Constructs a CQTSSAResultSubWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTSSAResultSubWidget::CQTSSAResultSubWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTSSAResultSubWidget::~CQTSSAResultSubWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTSSAResultSubWidget::languageChange()
{
  retranslateUi(this);
}
