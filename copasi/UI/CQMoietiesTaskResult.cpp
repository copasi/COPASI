// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQMoietiesTaskResult.cpp,v $
//   $Revision: 1.4.4.2 $
//   $Name: Qt3To4 $
//   $Author: shoops $
//   $Date: 2008/12/08 16:32:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qvariant.h>

#include "CQMoietiesTaskResult.h"
#include "CQMoietiesTaskResult.ui.h"
/*
 *  Constructs a CQMoietiesTaskResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMoietiesTaskResult::CQMoietiesTaskResult(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMoietiesTaskResult::~CQMoietiesTaskResult()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMoietiesTaskResult::languageChange()
{
  retranslateUi(this);
}
