// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressItemText.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:20 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
