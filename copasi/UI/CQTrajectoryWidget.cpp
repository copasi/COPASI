// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTrajectoryWidget.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:11 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQTrajectoryWidget.h"

#include <qvariant.h>
#include "CQTrajectoryWidget.ui.h"
/*
 *  Constructs a CQTrajectoryWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQTrajectoryWidget::CQTrajectoryWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTrajectoryWidget::~CQTrajectoryWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTrajectoryWidget::languageChange()
{
  retranslateUi(this);
}
