// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/TimeSeriesSubwidget.cpp,v $
//   $Revision: 1.13.4.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "TimeSeriesSubwidget.h"

#include <qvariant.h>
#include <qregexp.h>
#include "qmessagebox.h"
#include "q3filedialog.h"
#include "CTimeSeriesTable.h"
#include "TimeSeriesSubwidget.ui.h"
/*
 *  Constructs a TimeSeriesSubWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TimeSeriesSubWidget::TimeSeriesSubWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TimeSeriesSubWidget::~TimeSeriesSubWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TimeSeriesSubWidget::languageChange()
{
  retranslateUi(this);
}
