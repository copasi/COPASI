// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFileDialogBtnGrp.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/03 13:51:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQFileDialogBtnGrp.h"

/*
 *  Constructs a CQFileDialogBtnGrp as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQFileDialogBtnGrp::CQFileDialogBtnGrp(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFileDialogBtnGrp::~CQFileDialogBtnGrp()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFileDialogBtnGrp::languageChange()
{
  retranslateUi(this);
}
