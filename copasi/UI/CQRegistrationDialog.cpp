// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQRegistrationDialog.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:39 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQRegistrationDialog.h"

#include <QtCore/QVariant>
#include "CQRegistrationDialog.ui.h"
/*
 *  Constructs a CQRegistrationDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQRegistrationDialog::CQRegistrationDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQRegistrationDialog::~CQRegistrationDialog()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}
