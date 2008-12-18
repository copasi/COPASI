// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQProgressItem.cpp,v $
//   $Revision: 1.2.28.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQProgressItem.h"

#include <qvariant.h>
#include "CQProgressItem.ui.h"
/*
 *  Constructs a CQProgressItem as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQProgressItem::CQProgressItem(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItem::~CQProgressItem()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQProgressItem::languageChange()
{
  retranslateUi(this);
}
