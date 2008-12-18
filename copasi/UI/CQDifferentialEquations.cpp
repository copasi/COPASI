// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQDifferentialEquations.h"

#include <qvariant.h>
#include <q3scrollview.h>
#include "CQDifferentialEquations.ui.h"
/*
 *  Constructs a CQDifferentialEquations which is a child of 'parent', with the
 *  name 'name'.'
 */
CQDifferentialEquations::CQDifferentialEquations(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQDifferentialEquations::~CQDifferentialEquations()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQDifferentialEquations::languageChange()
{
  retranslateUi(this);
}
