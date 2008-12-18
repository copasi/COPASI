// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CMCAResultSubwidget.cpp,v $
//   $Revision: 1.11.4.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:55 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMCAResultSubwidget.h"

#include <qvariant.h>
#include "CQArrayAnnotationsWidget.h"
#include "CMCAResultSubwidget.ui.h"
/*
 *  Constructs a CMCAResultSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CMCAResultSubwidget::CMCAResultSubwidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMCAResultSubwidget::~CMCAResultSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CMCAResultSubwidget::languageChange()
{
  retranslateUi(this);
}
