/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetTask.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/22 15:54:50 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CScanWidgetTask.ui'
 **
 ** Created: Di Feb 22 15:03:01 2005
 **      by: The User Interface Compiler ($Id: CScanWidgetTask.cpp,v 1.1 2005/02/22 15:54:50 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CScanWidgetTask.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qtoolbutton.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CScanWidgetTask.ui.h"

/*
 *  Constructs a CScanWidgetTask as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetTask::CScanWidgetTask(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CScanWidgetTask");
  CScanWidgetTaskLayout = new QVBoxLayout(this, 5, 6, "CScanWidgetTaskLayout");

  frame = new QFrame(this, "frame");
  frame->setPaletteBackgroundColor(QColor(197, 201, 249));
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setFrameShadow(QFrame::Raised);
  frameLayout = new QVBoxLayout(frame, 6, 6, "frameLayout");

  layout1 = new QHBoxLayout(0, 0, 6, "layout1");

  labelTitle = new QLabel(frame, "labelTitle");
  layout1->addWidget(labelTitle);
  spacer1 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);
  layout1->addItem(spacer1);

  comboType = new QComboBox(FALSE, frame, "comboType");
  layout1->addWidget(comboType);

  buttonEdit = new QToolButton(frame, "buttonEdit");
  layout1->addWidget(buttonEdit);
  spacer2 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout1->addItem(spacer2);
  frameLayout->addLayout(layout1);

  layout2 = new QHBoxLayout(0, 0, 6, "layout2");

  checkInitialConditions = new QCheckBox(frame, "checkInitialConditions");
  layout2->addWidget(checkInitialConditions);
  spacer3 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);
  layout2->addItem(spacer3);

  checkOutput = new QCheckBox(frame, "checkOutput");
  layout2->addWidget(checkOutput);
  spacer4 = new QSpacerItem(41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout2->addItem(spacer4);
  frameLayout->addLayout(layout2);
  CScanWidgetTaskLayout->addWidget(frame);
  languageChange();
  resize(QSize(524, 80).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetTask::~CScanWidgetTask()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetTask::languageChange()
{
  setCaption(tr("Form1"));
  labelTitle->setText(tr("<h2>Task</h2>"));
  comboType->clear();
  comboType->insertItem(tr("Steady State"));
  comboType->insertItem(tr("Time course"));
  comboType->insertItem(tr("Metabolic Control Analysis"));
  buttonEdit->setText(tr("..."));
  checkInitialConditions->setText(tr("use initial conditions"));
  checkOutput->setText(tr("do output during task"));
}
