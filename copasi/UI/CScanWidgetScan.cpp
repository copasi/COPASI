/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetScan.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/24 16:40:11 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CScanWidgetScan.ui'
 **
 ** Created: Do Feb 24 12:57:47 2005
 **      by: The User Interface Compiler ($Id: CScanWidgetScan.cpp,v 1.2 2005/02/24 16:40:11 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CScanWidgetScan.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtoolbutton.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CScanWidgetScan.ui.h"

/*
 *  Constructs a CScanWidgetScan as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetScan::CScanWidgetScan(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CScanWidgetScan");
  CScanWidgetScanLayout = new QGridLayout(this, 1, 1, 5, 6, "CScanWidgetScanLayout");

  frame = new QFrame(this, "frame");
  frame->setPaletteBackgroundColor(QColor(204, 249, 196));
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setFrameShadow(QFrame::Raised);
  frameLayout = new QVBoxLayout(frame, 6, 6, "frameLayout");

  layout1 = new QGridLayout(0, 1, 1, 0, 3, "layout1");

  labelObject = new QLabel(frame, "labelObject");

  layout1->addWidget(labelObject, 0, 2);
  spacer1 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);
  layout1->addItem(spacer1, 0, 1);

  labelTitle = new QLabel(frame, "labelTitle");

  layout1->addMultiCellWidget(labelTitle, 0, 1, 0, 0);

  lineEditObject = new QLineEdit(frame, "lineEditObject");

  layout1->addWidget(lineEditObject, 1, 2);

  buttonObject = new QToolButton(frame, "buttonObject");

  layout1->addWidget(buttonObject, 1, 3);
  frameLayout->addLayout(layout1);

  layout2 = new QGridLayout(0, 1, 1, 0, 3, "layout2");

  lineEditMin = new QLineEdit(frame, "lineEditMin");

  layout2->addWidget(lineEditMin, 1, 1);

  lineEditNumber = new QLineEdit(frame, "lineEditNumber");

  layout2->addWidget(lineEditNumber, 1, 0);

  labelNumber = new QLabel(frame, "labelNumber");

  layout2->addWidget(labelNumber, 0, 0);

  lineEditMax = new QLineEdit(frame, "lineEditMax");

  layout2->addWidget(lineEditMax, 1, 2);

  labelMin = new QLabel(frame, "labelMin");

  layout2->addWidget(labelMin, 0, 1);

  labelMax = new QLabel(frame, "labelMax");

  layout2->addWidget(labelMax, 0, 2);
  frameLayout->addLayout(layout2);

  checkBoxLog = new QCheckBox(frame, "checkBoxLog");
  frameLayout->addWidget(checkBoxLog);

  CScanWidgetScanLayout->addWidget(frame, 0, 0);
  languageChange();
  resize(QSize(446, 147).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(buttonObject, SIGNAL(clicked()), this, SLOT(slotChooseObject()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetScan::~CScanWidgetScan()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetScan::languageChange()
{
  setCaption(tr("Form1"));
  labelObject->setText(tr("Parameter"));
  labelTitle->setText(tr("<h2>Scan</h2>"));
  buttonObject->setText(tr("..."));
  labelNumber->setText(tr("Intervals"));
  labelMin->setText(tr("min"));
  labelMax->setText(tr("max"));
  checkBoxLog->setText(tr("logarithmic scan"));
}
