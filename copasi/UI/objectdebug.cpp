// Begin CVS Header
//   $Source: /home/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/05/31 18:21:38 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'objectdebug.ui'
 **
 ** Created: Di Aug 7 23:52:02 2007
 **      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "objectdebug.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "objectdebug.ui.h"

/*
 *  Constructs a ObjectDebug as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ObjectDebug::ObjectDebug(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("ObjectDebug");
  ObjectDebugLayout = new QGridLayout(this, 1, 1, 11, 6, "ObjectDebugLayout");

  UpdateButton = new QPushButton(this, "UpdateButton");

  ObjectDebugLayout->addWidget(UpdateButton, 1, 3);

  ListOfObjects = new QListView(this, "ListOfObjects");
  ListOfObjects->addColumn(tr("Column 1"));

  ObjectDebugLayout->addMultiCellWidget(ListOfObjects, 0, 0, 0, 3);

  pushButton2 = new QPushButton(this, "pushButton2");

  ObjectDebugLayout->addWidget(pushButton2, 1, 2);
  spacer5 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ObjectDebugLayout->addItem(spacer5, 1, 0);

  ButtonModelCheck = new QPushButton(this, "ButtonModelCheck");

  ObjectDebugLayout->addWidget(ButtonModelCheck, 1, 1);
  languageChange();
  resize(QSize(517, 486).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(UpdateButton, SIGNAL(clicked()), this, SLOT(update()));
  connect(pushButton2, SIGNAL(clicked()), this, SLOT(writeDot()));
  connect(ButtonModelCheck, SIGNAL(clicked()), this, SLOT(checkModel()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ObjectDebug::~ObjectDebug()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ObjectDebug::languageChange()
{
  setCaption(tr("Copasi Object Tree"));
  UpdateButton->setText(tr("update"));
  ListOfObjects->header()->setLabel(0, tr("Column 1"));
  ListOfObjects->clear();
  QListViewItem * item = new QListViewItem(ListOfObjects, 0);
  item->setText(0, tr("New Item"));

  pushButton2->setText(tr("write Dependencies"));
  ButtonModelCheck->setText(tr("check model"));
}
