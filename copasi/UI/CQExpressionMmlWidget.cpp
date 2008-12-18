// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:20 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <qvariant.h>

#include "CQExpressionMmlWidget.h"
#include "mml/qtmmlwidget.h"
#include "CQExpressionWidget.h"
#include "utilities/CCopasiException.h"
#include "CQMmlScrollView.h"
#include "CQExpressionMmlWidget.ui.h"
/*
 *  Constructs a CQExpressionMmlWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQExpressionMmlWidget::CQExpressionMmlWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQExpressionMmlWidget::~CQExpressionMmlWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQExpressionMmlWidget::languageChange()
{
  retranslateUi(this);
}
