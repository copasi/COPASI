// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/copasi/UI/CQFittingResult.cpp,v $
//   $Revision: 1.8.12.2 $
//   $Name: Qt3To4 $
//   $Author: aekamal $
//   $Date: 2008/11/03 15:56:55 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQFittingResult.h"

#include <qvariant.h>
#include "CQFittingResult.ui.h"
/*
 *  Constructs a CQFittingResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFittingResult::CQFittingResult(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingResult::~CQFittingResult()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingResult::languageChange()
{
  retranslateUi(this);
}
