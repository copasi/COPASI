/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressItem.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQProgressItem.ui'
 **
 ** Created: Thu Apr 21 13:02:56 2005
 **      by: The User Interface Compiler ($Id: CQProgressItem.cpp,v 1.2 2006/04/27 01:27:41 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQProgressItem.h"

#include <qvariant.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQProgressItem.ui.h"

/*
 *  Constructs a CQProgressItem as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQProgressItem::CQProgressItem(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CQProgressItem");

  QWidget* privateLayoutWidget = new QWidget(this, "mLabel");
  privateLayoutWidget->setGeometry(QRect(10, 10, 330, 22));
  mLabel = new QHBoxLayout(privateLayoutWidget, 11, 6, "mLabel");
  languageChange();
  resize(QSize(404, 44).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressItem::~CQProgressItem()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQProgressItem::languageChange()
{
  setCaption(tr("Form1"));
}
