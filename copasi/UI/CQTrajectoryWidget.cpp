// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTrajectoryWidget.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/10 18:51:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTrajectoryWidget.ui'
 **
 ** Created: Thu Jul 10 14:43:34 2008
 **      by: The User Interface Compiler ($Id: CQTrajectoryWidget.cpp,v 1.3 2008/07/10 18:51:35 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTrajectoryWidget.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CQTrajectoryWidget.ui.h"

/*
 *  Constructs a CQTrajectoryWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQTrajectoryWidget::CQTrajectoryWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQTrajectoryWidget");
  CQTrajectoryWidgetLayout = new QVBoxLayout(this, 11, 6, "CQTrajectoryWidgetLayout");

  layout6 = new QGridLayout(0, 1, 1, 0, 6, "layout6");

  line2 = new QFrame(this, "line2");
  line2->setFrameShape(QFrame::HLine);
  line2->setFrameShadow(QFrame::Sunken);
  line2->setFrameShape(QFrame::HLine);

  layout6->addMultiCellWidget(line2, 4, 4, 0, 3);

  mpEditDuration = new QLineEdit(this, "mpEditDuration");

  layout6->addWidget(mpEditDuration, 0, 1);

  mpEditIntegrationInterval = new QLineEdit(this, "mpEditIntegrationInterval");
  mpEditIntegrationInterval->setReadOnly(TRUE);

  layout6->addWidget(mpEditIntegrationInterval, 5, 1);

  mpLblIntervals = new QLabel(this, "mpLblIntervals");
  mpLblIntervals->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout6->addWidget(mpLblIntervals, 1, 2);

  mpEditIntervals = new QLineEdit(this, "mpEditIntervals");

  layout6->addWidget(mpEditIntervals, 1, 3);

  mpLblOutputInterval = new QLabel(this, "mpLblOutputInterval");
  mpLblOutputInterval->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout6->addWidget(mpLblOutputInterval, 6, 0);

  mpLblIntervalSize = new QLabel(this, "mpLblIntervalSize");
  mpLblIntervalSize->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout6->addWidget(mpLblIntervalSize, 1, 0);

  layout5 = new QHBoxLayout(0, 0, 6, "layout5");

  mpCheckDelay = new QCheckBox(this, "mpCheckDelay");
  layout5->addWidget(mpCheckDelay);

  mpEditDelay = new QLineEdit(this, "mpEditDelay");
  mpEditDelay->setFrameShape(QLineEdit::LineEditPanel);
  mpEditDelay->setFrameShadow(QLineEdit::Sunken);
  layout5->addWidget(mpEditDelay);
  spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout5->addItem(spacer1);

  layout6->addMultiCellLayout(layout5, 2, 2, 1, 3);

  mpLblDuration = new QLabel(this, "mpLblDuration");
  mpLblDuration->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout6->addWidget(mpLblDuration, 0, 0);

  mpLblIntegrationInterval = new QLabel(this, "mpLblIntegrationInterval");
  mpLblIntegrationInterval->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  layout6->addWidget(mpLblIntegrationInterval, 5, 0);

  mpEditOutputInterval = new QLineEdit(this, "mpEditOutputInterval");
  mpEditOutputInterval->setReadOnly(TRUE);

  layout6->addWidget(mpEditOutputInterval, 6, 1);

  mpEditIntervalSize = new QLineEdit(this, "mpEditIntervalSize");

  layout6->addWidget(mpEditIntervalSize, 1, 1);

  mpCheckSave = new QCheckBox(this, "mpCheckSave");

  layout6->addMultiCellWidget(mpCheckSave, 3, 3, 1, 2);
  CQTrajectoryWidgetLayout->addLayout(layout6);

  line1 = new QFrame(this, "line1");
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Sunken);
  line1->setFrameShape(QFrame::HLine);
  CQTrajectoryWidgetLayout->addWidget(line1);
  languageChange();
  resize(QSize(553, 222).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpEditDuration, SIGNAL(lostFocus()), this, SLOT(slotDuration()));
  connect(mpEditIntervalSize, SIGNAL(lostFocus()), this, SLOT(slotIntervalSize()));
  connect(mpEditIntervals, SIGNAL(lostFocus()), this, SLOT(slotIntervals()));
  connect(mpEditDelay, SIGNAL(lostFocus()), this, SLOT(updateIntervals()));
  connect(mpCheckDelay, SIGNAL(toggled(bool)), this, SLOT(slotOutputDelay(bool)));

  // tab order
  setTabOrder(mpEditDuration, mpEditIntervalSize);
  setTabOrder(mpEditIntervalSize, mpEditIntervals);
  setTabOrder(mpEditIntervals, mpCheckDelay);
  setTabOrder(mpCheckDelay, mpEditDelay);
  setTabOrder(mpEditDelay, mpCheckSave);
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
  setCaption(tr("Time Course"));
  mpLblIntervals->setText(tr("Intervals"));
  mpLblOutputInterval->setText(tr("Output Interval"));
  mpLblIntervalSize->setText(tr("Interval Size"));
  mpCheckDelay->setText(tr("Suppress Output Before"));
  mpLblDuration->setText(tr("Duration"));
  mpLblIntegrationInterval->setText(tr("Integration Interval"));
  mpCheckSave->setText(tr("Save Result in Memory"));
}
