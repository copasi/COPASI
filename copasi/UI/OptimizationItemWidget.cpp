/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/OptimizationItemWidget.cpp,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 16:40:23 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'OptimizationItemWidget.ui'
 **
 ** Created: Fri Oct 7 12:38:58 2005
 **      by: The User Interface Compiler ($Id: OptimizationItemWidget.cpp,v 1.38 2005/10/07 16:40:23 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "OptimizationItemWidget.h"

#include <qvariant.h>
 #include <qpushbutton.h>
 #include <qframe.h>
 #include <qcheckbox.h>
 #include <qlabel.h>
 #include <qlineedit.h>
 #include <qtoolbutton.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "OptimizationItemWidget.ui.h"

/*
 *  Constructs a OptimizationItemWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
OptimizationItemWidget::OptimizationItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("OptimizationItemWidget");
  OptimizationItemWidgetLayout = new QHBoxLayout(this, 5, 6, "OptimizationItemWidgetLayout");

  frame = new QFrame(this, "frame");
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setFrameShadow(QFrame::Raised);
  frameLayout = new QGridLayout(frame, 1, 1, 6, 6, "frameLayout");

  checkLowerInf = new QCheckBox(frame, "checkLowerInf");
  checkLowerInf->setChecked(TRUE);

  frameLayout->addWidget(checkLowerInf, 1, 2);

  checkUpperInf = new QCheckBox(frame, "checkUpperInf");
  checkUpperInf->setChecked(TRUE);

  frameLayout->addWidget(checkUpperInf, 2, 2);

  textLower = new QLabel(frame, "textLower");

  frameLayout->addWidget(textLower, 1, 0);

  textUpper = new QLabel(frame, "textUpper");

  frameLayout->addWidget(textUpper, 2, 0);

  layoutLower = new QHBoxLayout(0, 0, 6, "layoutLower");

  lineLower = new QLineEdit(frame, "lineLower");
  lineLower->setFrameShape(QLineEdit::LineEditPanel);
  lineLower->setFrameShadow(QLineEdit::Sunken);
  layoutLower->addWidget(lineLower);

  buttonLowerEdit = new QToolButton(frame, "buttonLowerEdit");
  layoutLower->addWidget(buttonLowerEdit);

  frameLayout->addLayout(layoutLower, 1, 1);

  layoutUpper = new QHBoxLayout(0, 0, 6, "layoutUpper");

  lineUpper = new QLineEdit(frame, "lineUpper");
  layoutUpper->addWidget(lineUpper);

  buttonUpperEdit = new QToolButton(frame, "buttonUpperEdit");
  layoutUpper->addWidget(buttonUpperEdit);

  frameLayout->addLayout(layoutUpper, 2, 1);

  layoutParameter = new QHBoxLayout(0, 0, 6, "layoutParameter");

  lineObjectName = new QLineEdit(frame, "lineObjectName");
  layoutParameter->addWidget(lineObjectName);

  buttonParamEdit = new QToolButton(frame, "buttonParamEdit");
  layoutParameter->addWidget(buttonParamEdit);

  frameLayout->addLayout(layoutParameter, 0, 1);

  textParameter = new QLabel(frame, "textParameter");

  frameLayout->addWidget(textParameter, 0, 0);
  OptimizationItemWidgetLayout->addWidget(frame);
  languageChange();
  resize(QSize(630, 125).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(checkLowerInf, SIGNAL(toggled(bool)), this, SLOT(slotNegativeInfinity()));
  connect(checkUpperInf, SIGNAL(toggled(bool)), this, SLOT(slotPositiveInfinity()));
  connect(buttonLowerEdit, SIGNAL(clicked()), this, SLOT(slotLowerEdit()));
  connect(buttonUpperEdit, SIGNAL(clicked()), this, SLOT(slotUpperEdit()));
  connect(buttonParamEdit, SIGNAL(clicked()), this, SLOT(slotParamEdit()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
OptimizationItemWidget::~OptimizationItemWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void OptimizationItemWidget::languageChange()
{
  setCaption(tr("Form1"));
  checkLowerInf->setText(tr("- Infinity"));
  checkUpperInf->setText(tr("+ Infinity"));
  textLower->setText(tr("lower bound"));
  textUpper->setText(tr("upper bound"));
  buttonLowerEdit->setText(tr("..."));
  buttonUpperEdit->setText(tr("..."));
  buttonParamEdit->setText(tr("..."));
  textParameter->setText(tr("parameter"));
}
