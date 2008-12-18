// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemText.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQProgressItemText.h"

#include <qvariant.h>
#include "CQProgressItem.h"
#include "CQProgressItemText.ui.h"
/*
 *  Constructs a CQProgressItemText which is a child of 'parent', with the
 *  name 'name'.'
 */
CQProgressItemText::CQProgressItemText(QWidget* parent, const char* name)
    : CQProgressItem(parent, name)
{
  Ui::CQProgressItemText::setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItemText::~CQProgressItemText()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQProgressItemText::languageChange()
{
  Ui::CQProgressItemText::retranslateUi(this);
}
