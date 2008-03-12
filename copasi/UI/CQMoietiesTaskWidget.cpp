// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMoietiesTaskWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:32:59 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMoietiesTaskWidget.ui'
 **
 ** Created: Wed Feb 20 14:48:52 2008
 **      by: The User Interface Compiler ($Id: CQMoietiesTaskWidget.cpp,v 1.2 2008/03/12 00:32:59 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMoietiesTaskWidget.h"

#include <qvariant.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQMoietiesTaskWidget.ui.h"

/*
 *  Constructs a CQMoietiesTaskWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQMoietiesTaskWidget::CQMoietiesTaskWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQMoietiesTaskWidget");
  CQMoietiesTaskWidgetLayout = new QVBoxLayout(this, 11, 6, "CQMoietiesTaskWidgetLayout");
  mpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQMoietiesTaskWidgetLayout->addItem(mpSpacer);
  languageChange();
  resize(QSize(260, 23).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMoietiesTaskWidget::~CQMoietiesTaskWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMoietiesTaskWidget::languageChange()
{
  setCaption(tr("Mass Conservation"));
}
