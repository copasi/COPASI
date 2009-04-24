// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventWidget1.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/24 19:28:40 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEventWidget1.h"

#include <qvariant.h>
#include "CQExpressionWidget.h"
#include "CQExpressionMmlWidget.h"
#include "MyLineEdit.h"
#include "CQEventWidget1.ui.h"
/*
 *  Constructs a CQEventWidget1 which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEventWidget1::CQEventWidget1(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQEventWidget1::~CQEventWidget1()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQEventWidget1::languageChange()
{
  retranslateUi(this);
}
