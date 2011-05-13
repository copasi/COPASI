// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQPrintAsDialog.cpp,v $
//   $Revision: 1.3.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:57 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qvariant.h>

#include "CQPrintAsDialog.h"
#include "CQPrintAsDialog.ui.h"
/*
 *  Constructs a CQPrintAsDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQPrintAsDialog::CQPrintAsDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQPrintAsDialog::~CQPrintAsDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

