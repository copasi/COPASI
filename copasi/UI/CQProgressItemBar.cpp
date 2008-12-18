// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemBar.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:51 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQProgressItemBar.h"

#include <qvariant.h>
#include "CQProgressItem.h"
#include "CQProgressItemBar.ui.h"
/*
 *  Constructs a CQProgressItemBar which is a child of 'parent', with the
 *  name 'name'.'
 */
CQProgressItemBar::CQProgressItemBar(QWidget* parent, const char* name)
    : CQProgressItem(parent, name)
{
  Ui::CQProgressItemBar::setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItemBar::~CQProgressItemBar()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQProgressItemBar::languageChange()
{
  Ui::CQProgressItemBar::retranslateUi(this);
}
