// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMessageBox.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/12/04 15:47:17 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQMessageBox.ui'
 **
 ** Created: Tue Dec 4 10:37:03 2007
 **      by: The User Interface Compiler ($Id: CQMessageBox.cpp,v 1.3 2007/12/04 15:47:17 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQMessageBox.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQMessageBox.ui.h"

/*
 *  Constructs a CQMessageBox as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CQMessageBox::CQMessageBox(QWidget* parent, const char* name, bool modal, WFlags fl)
    : QDialog(parent, name, modal, fl)
{
  if (!name)
    setName("CQMessageBox");
  setSizeGripEnabled(TRUE);
  CQMessageBoxLayout = new QGridLayout(this, 1, 1, 11, 6, "CQMessageBoxLayout");

  mpLayoutBtn = new QHBoxLayout(0, 0, 6, "mpLayoutBtn");

  mpBtn0 = new QPushButton(this, "mpBtn0");
  mpBtn0->setAutoDefault(TRUE);
  mpLayoutBtn->addWidget(mpBtn0);

  mpBtn1 = new QPushButton(this, "mpBtn1");
  mpBtn1->setAutoDefault(TRUE);
  mpBtn1->setDefault(TRUE);
  mpLayoutBtn->addWidget(mpBtn1);

  mpBtn2 = new QPushButton(this, "mpBtn2");
  mpBtn2->setAutoDefault(TRUE);
  mpLayoutBtn->addWidget(mpBtn2);

  mpBtn3 = new QPushButton(this, "mpBtn3");
  mpBtn3->setAutoDefault(TRUE);
  mpLayoutBtn->addWidget(mpBtn3);

  CQMessageBoxLayout->addMultiCellLayout(mpLayoutBtn, 1, 1, 0, 1);

  mpLayoutIcon = new QVBoxLayout(0, 0, 6, "mpLayoutIcon");

  mpLblIcon = new QLabel(this, "mpLblIcon");
  mpLblIcon->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, mpLblIcon->sizePolicy().hasHeightForWidth()));
  mpLblIcon->setAlignment(int(QLabel::AlignTop));
  mpLayoutIcon->addWidget(mpLblIcon);
  mpSpacerIcon = new QSpacerItem(0, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpLayoutIcon->addItem(mpSpacerIcon);

  CQMessageBoxLayout->addLayout(mpLayoutIcon, 0, 0);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");

  tab = new QWidget(mpTabWidget, "tab");
  tabLayout = new QHBoxLayout(tab, 11, 6, "tabLayout");

  mpMessage = new QTextEdit(tab, "mpMessage");
  mpMessage->setResizePolicy(QTextEdit::Manual);
  mpMessage->setReadOnly(TRUE);
  tabLayout->addWidget(mpMessage);
  mpTabWidget->insertTab(tab, QString::fromLatin1(""));

  tab_2 = new QWidget(mpTabWidget, "tab_2");
  tabLayout_2 = new QGridLayout(tab_2, 1, 1, 11, 6, "tabLayout_2");

  mpFilteredMessage = new QTextEdit(tab_2, "mpFilteredMessage");

  tabLayout_2->addWidget(mpFilteredMessage, 0, 0);
  mpTabWidget->insertTab(tab_2, QString::fromLatin1(""));

  CQMessageBoxLayout->addWidget(mpTabWidget, 0, 1);
  languageChange();
  resize(QSize(648, 324).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtn0, SIGNAL(clicked()), this, SLOT(slotBtn0()));
  connect(mpBtn1, SIGNAL(clicked()), this, SLOT(slotBtn1()));
  connect(mpBtn2, SIGNAL(clicked()), this, SLOT(slotBtn2()));
  connect(mpBtn3, SIGNAL(clicked()), this, SLOT(slotBtn3()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQMessageBox::~CQMessageBox()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQMessageBox::languageChange()
{
  setCaption(tr("MyDialog"));
  mpBtn0->setText(tr("0"));
  mpBtn0->setAccel(QKeySequence(QString::null));
  mpBtn1->setText(tr("1"));
  mpBtn1->setAccel(QKeySequence(QString::null));
  mpBtn2->setText(tr("2"));
  mpBtn2->setAccel(QKeySequence(QString::null));
  mpBtn3->setText(tr("3"));
  mpBtn3->setAccel(QKeySequence(QString::null));
  mpLblIcon->setText(QString::null);
  mpTabWidget->changeTab(tab, tr("Messages"));
  mpTabWidget->changeTab(tab_2, tr("Filtered Messages"));
}
