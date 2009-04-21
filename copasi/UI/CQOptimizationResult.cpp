// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationResult.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/04/21 16:20:31 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQOptimizationResult.h"

#include <qvariant.h>
#include "CQOptimizationResult.ui.h"
/*
 *  Constructs a CQOptimizationResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQOptimizationResult::CQOptimizationResult(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQOptimizationResult::~CQOptimizationResult()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQOptimizationResult::languageChange()
{
  retranslateUi(this);
}
