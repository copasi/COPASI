// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/objectdebug.cpp,v $
//   $Revision: 1.10.14.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "objectdebug.h"

#include <qvariant.h>
#include "objectdebug.ui.h"
/*
 *  Constructs a ObjectDebug as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
ObjectDebug::ObjectDebug(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjectDebug::~ObjectDebug()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ObjectDebug::languageChange()
{
  retranslateUi(this);
}
