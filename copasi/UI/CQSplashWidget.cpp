// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSplashWidget.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQSplashWidget.h"

#include <qvariant.h>
#include "CQSplashWidget.ui.h"
/*
 *  Constructs a CQSplashWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSplashWidget::CQSplashWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSplashWidget::~CQSplashWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQSplashWidget::languageChange()
{
  retranslateUi(this);
}
