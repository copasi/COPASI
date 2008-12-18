// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMoietiesTaskWidget.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qvariant.h>

#include "CQMoietiesTaskWidget.h"
#include "CQMoietiesTaskWidget.ui.h"
/*
 *  Constructs a CQMoietiesTaskWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMoietiesTaskWidget::CQMoietiesTaskWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMoietiesTaskWidget::~CQMoietiesTaskWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMoietiesTaskWidget::languageChange()
{
  retranslateUi(this);
}
