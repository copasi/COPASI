/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetRandom.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/03/04 15:18:06 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CScanWidgetRandom.ui'
 **
 ** Created: Fr Mär 4 11:19:17 2005
 **      by: The User Interface Compiler ($Id: CScanWidgetRandom.cpp,v 1.2 2005/03/04 15:18:06 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CScanWidgetRandom.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CScanWidgetRandom.ui.h"

/*
 *  Constructs a CScanWidgetRandom as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetRandom::CScanWidgetRandom(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CScanWidgetRandom");
  CScanWidgetRandomLayout = new QVBoxLayout(this, 5, 6, "CScanWidgetRandomLayout");

  frame = new QFrame(this, "frame");
  frame->setPaletteBackgroundColor(QColor(221, 203, 249));
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

  layout2 = new QGridLayout(0, 1, 1, 0, 6, "layout2");

  comboBoxType = new QComboBox(FALSE, frame, "comboBoxType");

  layout2->addWidget(comboBoxType, 1, 0);

  labelType = new QLabel(frame, "labelType");

  layout2->addWidget(labelType, 0, 0);

  lineEditMax = new QLineEdit(frame, "lineEditMax");

  layout2->addWidget(lineEditMax, 1, 2);

  lineEditMin = new QLineEdit(frame, "lineEditMin");

  layout2->addWidget(lineEditMin, 1, 1);

  labelMin = new QLabel(frame, "labelMin");

  layout2->addWidget(labelMin, 0, 1);

  labelMax = new QLabel(frame, "labelMax");

  layout2->addWidget(labelMax, 0, 2);
  frameLayout->addLayout(layout2);

  checkBoxLog = new QCheckBox(frame, "checkBoxLog");
  frameLayout->addWidget(checkBoxLog);
  CScanWidgetRandomLayout->addWidget(frame);
  languageChange();
  resize(QSize(460, 150).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(buttonObject, SIGNAL(clicked()), this, SLOT(slotChooseObject()));
  connect(comboBoxType, SIGNAL(activated(int)), this, SLOT(changeType()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetRandom::~CScanWidgetRandom()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetRandom::languageChange()
{
  setCaption(tr("Form1"));
  labelObject->setText(tr("Parameter"));
  labelTitle->setText(tr("<h2>Random distribution</h2>"));
  buttonObject->setText(tr("..."));
  comboBoxType->clear();
  comboBoxType->insertItem(tr("Uniform distribution"));
  comboBoxType->insertItem(tr("Normal distribution"));
  comboBoxType->insertItem(tr("Poisson distribution"));
  labelType->setText(tr("Type"));
  labelMin->setText(tr("min"));
  labelMax->setText(tr("max"));
  checkBoxLog->setText(tr("logarithmic"));
}
