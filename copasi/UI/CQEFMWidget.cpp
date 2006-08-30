/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/30 17:13:49 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQEFMWidget.ui'
 **
 ** Created: Wed Aug 30 12:36:10 2006
 **      by: The User Interface Compiler ($Id: CQEFMWidget.cpp,v 1.1 2006/08/30 17:13:49 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQEFMWidget.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "TaskWidget.h"
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

  mpLayoutFluxModes = new QHBoxLayout(0, 0, 6, "mpLayoutFluxModes");

  mpLblFluxModes = new QLabel(this, "mpLblFluxModes");
  mpLayoutFluxModes->addWidget(mpLblFluxModes);

  mpEditFluxModes = new QLineEdit(this, "mpEditFluxModes");
  mpEditFluxModes->setFrameShape(QLineEdit::LineEditPanel);
  mpEditFluxModes->setFrameShadow(QLineEdit::Sunken);
  mpEditFluxModes->setReadOnly(TRUE);
  mpLayoutFluxModes->addWidget(mpEditFluxModes);
  mpSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpLayoutFluxModes->addItem(mpSpacer);
  CQEFMWidgetLayout->addLayout(mpLayoutFluxModes);

  mpListView = new QListView(this, "mpListView");
  mpListView->addColumn(tr("Reversibility"));
  mpListView->addColumn(tr("Reaction Name"));
  mpListView->addColumn(tr("Reaction Equation"));
  CQEFMWidgetLayout->addWidget(mpListView);
  languageChange();
  resize(QSize(366, 168).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
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
  mpListView->header()->setLabel(0, tr("Reversibility"));
  mpListView->header()->setLabel(1, tr("Reaction Name"));
  mpListView->header()->setLabel(2, tr("Reaction Equation"));
}
