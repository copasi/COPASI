// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQMetabolite.cpp,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/06/22 17:19:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQMetabolite.h"

#include <qvariant.h>
#include "CQExpressionWidget.h"
#include "CQExpressionMmlWidget.h"
#include "CQMetabolite.ui.h"
/*
 *  Constructs a CQMetabolite which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMetabolite::CQMetabolite(QWidget* parent, const char* name)
    : CopasiWidget(parent, name),
    mpMetab(NULL)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMetabolite::~CQMetabolite()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMetabolite::languageChange()
{
  retranslateUi(this);
}
