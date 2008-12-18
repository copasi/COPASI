// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CUpDownSubwidget.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CUpDownSubwidget.h"

#include <qvariant.h>
#include "CUpDownSubwidget.ui.h"
/*
 *  Constructs a CUpDownSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CUpDownSubwidget::CUpDownSubwidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CUpDownSubwidget::~CUpDownSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CUpDownSubwidget::languageChange()
{
  retranslateUi(this);
}
