// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/StateSubwidget.cpp,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:58:29 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "StateSubwidget.h"

#include <qvariant.h>
#include "CQArrayAnnotationsWidget.h"
#include "StateSubwidget.ui.h"
/*
 *  Constructs a StateSubwidget which is a child of 'parent', with the
 *  name 'name'.'
 */
StateSubwidget::StateSubwidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
StateSubwidget::~StateSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void StateSubwidget::languageChange()
{
  retranslateUi(this);
}
