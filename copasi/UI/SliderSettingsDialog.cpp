// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderSettingsDialog.cpp,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:58:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "SliderSettingsDialog.h"

#include <qvariant.h>
#include "SliderSettingsDialog.ui.h"
/*
 *  Constructs a SliderSettingsDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
SliderSettingsDialog::SliderSettingsDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
SliderSettingsDialog::~SliderSettingsDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SliderSettingsDialog::languageChange()
{
  retranslateUi(this);
}
