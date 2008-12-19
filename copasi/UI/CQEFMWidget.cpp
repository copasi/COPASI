// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMWidget.cpp,v $
//   $Revision: 1.1.28.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/11 17:19:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQEFMWidget.ui'
 **
 ** Created: Tue Nov 11 12:13:27 2008
 **      by: The User Interface Compiler ($Id: CQEFMWidget.cpp,v 1.1.28.1 2008/11/11 17:19:46 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQEFMWidget.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQEFMWidget.ui.h"

/*
 *  Constructs a CQEFMWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEFMWidget::CQEFMWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQEFMWidget");
  CQEFMWidgetLayout = new QVBoxLayout(this, 11, 6, "CQEFMWidgetLayout");

  mpLine = new QFrame(this, "mpLine");
  mpLine->setFrameShape(QFrame::HLine);
  mpLine->setFrameShadow(QFrame::Sunken);
  mpLine->setFrameShape(QFrame::HLine);
  CQEFMWidgetLayout->addWidget(mpLine);

  layout2 = new QHBoxLayout(0, 0, 6, "layout2");

  mpLblFluxModes = new QLabel(this, "mpLblFluxModes");
  layout2->addWidget(mpLblFluxModes);

  mpEditFluxModes = new QLineEdit(this, "mpEditFluxModes");
  mpEditFluxModes->setFrameShape(QLineEdit::LineEditPanel);
  mpEditFluxModes->setFrameShadow(QLineEdit::Sunken);
  mpEditFluxModes->setReadOnly(TRUE);
  layout2->addWidget(mpEditFluxModes);
  mpSpacer = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout2->addItem(mpSpacer);

  mpBtnSave = new QPushButton(this, "mpBtnSave");
  layout2->addWidget(mpBtnSave);
  CQEFMWidgetLayout->addLayout(layout2);

  mpListView = new QListView(this, "mpListView");
  mpListView->addColumn(tr("Reversibility"));
  mpListView->addColumn(tr("Reaction Name"));
  mpListView->addColumn(tr("Reaction Equation"));
  CQEFMWidgetLayout->addWidget(mpListView);
  languageChange();
  resize(QSize(314, 137).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnSave, SIGNAL(clicked()), this, SLOT(slotSave()));

  // tab order
  setTabOrder(mpEditFluxModes, mpBtnSave);
  setTabOrder(mpBtnSave, mpListView);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQEFMWidget::~CQEFMWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQEFMWidget::languageChange()
{
  setCaption(tr("Elementary Flux Modes"));
  mpLblFluxModes->setText(tr("Flux Modes"));
  mpBtnSave->setText(tr("Save Result"));
  mpListView->header()->setLabel(0, tr("Reversibility"));
  mpListView->header()->setLabel(1, tr("Reaction Name"));
  mpListView->header()->setLabel(2, tr("Reaction Equation"));
}
