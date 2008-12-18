// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQFittingResultTab1.h"

#include <qvariant.h>
#include "CQFittingResultTab1.ui.h"
/*
 *  Constructs a CQFittingResultTab1 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQFittingResultTab1::CQFittingResultTab1(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingResultTab1::~CQFittingResultTab1()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingResultTab1::languageChange()
{
  retranslateUi(this);
}
