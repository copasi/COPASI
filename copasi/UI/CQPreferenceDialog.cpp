// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPreferenceDialog.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/06/23 16:29:21 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQPreferenceDialog.ui'
 **
 ** Created: Sat Jun 23 12:19:37 2007
 **      by: The User Interface Compiler ($Id: CQPreferenceDialog.cpp,v 1.2 2007/06/23 16:29:21 aekamal Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQPreferenceDialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQPreferenceDialog.ui.h"

/*
 *  Constructs a CQPreferenceDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQPreferenceDialog::CQPreferenceDialog(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQPreferenceDialog");
  setSizeGripEnabled(TRUE);

  QWidget* privateLayoutWidget = new QWidget(this, "Layout1");
  privateLayoutWidget->setGeometry(QRect(10, 190, 240, 28));
  Layout1 = new QHBoxLayout(privateLayoutWidget, 0, 6, "Layout1");

  mpBtnOk = new QPushButton(privateLayoutWidget, "mpBtnOk");
  mpBtnOk->setAutoDefault(TRUE);
  mpBtnOk->setDefault(TRUE);
  Layout1->addWidget(mpBtnOk);

  mpBtnCancel = new QPushButton(privateLayoutWidget, "mpBtnCancel");
  mpBtnCancel->setAutoDefault(TRUE);
  Layout1->addWidget(mpBtnCancel);

  mpListView = new QListView(this, "mpListView");
  mpListView->addColumn(tr("Name"));
  mpListView->addColumn(tr("Value"));
  mpListView->setGeometry(QRect(10, 10, 238, 170));
  mpListView->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, mpListView->sizePolicy().hasHeightForWidth()));
  mpListView->setAllColumnsShowFocus(TRUE);
  mpListView->setDefaultRenameAction(QListView::Accept);
  languageChange();
  resize(QSize(261, 225).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnOk, SIGNAL(clicked()), this, SLOT(slotBtnOk()));
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(slotBtnCancel()));
  connect(mpListView, SIGNAL(clicked(QListViewItem*, const QPoint&, int)), this, SLOT(editItem(QListViewItem*, const QPoint&, int)));
  connect(mpListView, SIGNAL(returnPressed(QListViewItem*)), this, SLOT(editItem(QListViewItem*)));

  // tab order
  setTabOrder(mpListView, mpBtnOk);
  setTabOrder(mpBtnOk, mpBtnCancel);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQPreferenceDialog::~CQPreferenceDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQPreferenceDialog::languageChange()
{
  setCaption(tr("Preferences"));
  mpBtnOk->setText(tr("&OK"));
  mpBtnOk->setAccel(QKeySequence(QString::null));
  mpBtnCancel->setText(tr("&Cancel"));
  mpBtnCancel->setAccel(QKeySequence(QString::null));
  mpListView->header()->setLabel(0, tr("Name"));
  mpListView->header()->setLabel(1, tr("Value"));
}
