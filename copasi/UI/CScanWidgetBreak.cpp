// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetBreak.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CScanWidgetBreak.h"

#include <qvariant.h>
#include "CScanWidgetBreak.ui.h"
/*
 *  Constructs a CScanWidgetBreak as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetBreak::CScanWidgetBreak(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetBreak::~CScanWidgetBreak()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetBreak::languageChange()
{
  retranslateUi(this);
}
