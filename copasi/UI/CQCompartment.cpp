// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCompartment.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQCompartment.h"

#include <qvariant.h>
#include "CQExpressionWidget.h"
#include "CQExpressionMmlWidget.h"
#include "CQCompartment.ui.h"
/*
 *  Constructs a CQCompartment which is a child of 'parent', with the
 *  name 'name'.'
 */
CQCompartment::CQCompartment(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQCompartment::~CQCompartment()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQCompartment::languageChange()
{
  retranslateUi(this);
}
