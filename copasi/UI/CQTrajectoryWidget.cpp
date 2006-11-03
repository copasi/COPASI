/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTrajectoryWidget.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/11/03 19:48:48 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQTrajectoryWidget.ui'
 **
 ** Created: Fri Nov 3 14:47:07 2006
 **      by: The User Interface Compiler ($Id: CQTrajectoryWidget.cpp,v 1.2 2006/11/03 19:48:48 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQTrajectoryWidget.h"

#include <qvariant.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "TaskWidget.h"
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

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpEditIntervals = new QLineEdit(this, "mpEditIntervals");

  mpGridLayout->addWidget(mpEditIntervals, 1, 3);

  mpEditIntervalSize = new QLineEdit(this, "mpEditIntervalSize");

  mpGridLayout->addWidget(mpEditIntervalSize, 1, 1);

  mpLblDeltaT = new QLabel(this, "mpLblDeltaT");
  mpLblDeltaT->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblDeltaT, 2, 0);

  mpEditDuration = new QLineEdit(this, "mpEditDuration");

  mpGridLayout->addWidget(mpEditDuration, 0, 1);

  mpLblIntervals = new QLabel(this, "mpLblIntervals");
  mpLblIntervals->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblIntervals, 1, 2);

  mpCheckDelay = new QCheckBox(this, "mpCheckDelay");

  mpGridLayout->addWidget(mpCheckDelay, 2, 2);

  mpEditDelay = new QLineEdit(this, "mpEditDelay");
  mpEditDelay->setFrameShape(QLineEdit::LineEditPanel);
  mpEditDelay->setFrameShadow(QLineEdit::Sunken);

  mpGridLayout->addWidget(mpEditDelay, 2, 1);

  mpLblDuration = new QLabel(this, "mpLblDuration");
  mpLblDuration->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblDuration, 0, 0);

  mpLblIntervalSize = new QLabel(this, "mpLblIntervalSize");
  mpLblIntervalSize->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblIntervalSize, 1, 0);

  mpCheckSave = new QCheckBox(this, "mpCheckSave");

  mpGridLayout->addMultiCellWidget(mpCheckSave, 3, 3, 1, 2);
  CQTrajectoryWidgetLayout->addLayout(mpGridLayout);

  line1 = new QFrame(this, "line1");
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Sunken);
  line1->setFrameShape(QFrame::HLine);
  CQTrajectoryWidgetLayout->addWidget(line1);
  languageChange();
  resize(QSize(358, 130).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpEditDuration, SIGNAL(lostFocus()), this, SLOT(slotDuration()));
  connect(mpEditIntervalSize, SIGNAL(lostFocus()), this, SLOT(slotIntervalSize()));
  connect(mpEditIntervals, SIGNAL(lostFocus()), this, SLOT(slotIntervals()));
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
  mpLblDeltaT->setText(tr("Start Output Time"));
  mpLblIntervals->setText(tr("Intervals"));
  mpCheckDelay->setText(tr("delayed"));
  mpLblDuration->setText(tr("Duration"));
  mpLblIntervalSize->setText(tr("Interval Size"));
  mpCheckSave->setText(tr("Save Result in Memory"));
}
