/****************************************************************************
 ** Form implementation generated from reading ui file 'curvegroupbox.ui'
 **
 ** Created: Wed Oct 1 13:58:25 2003
 **      by: The User Interface Compiler ($Id: curvegroupbox.cpp,v 1.1 2003/10/14 15:06:04 huwenjun Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "curvegroupbox.h"

//#include <qvariant.h>
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h> 
//#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h> 
//#include <qtooltip.h>
//#include <qwhatsthis.h>
//#include <qimage.h>
//#include <qpixmap.h>

/*
 *  Constructs a CurveGroupBox as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
CurveGroupBox::CurveGroupBox(QWidget* parent, const char* name)
    : QGroupBox(parent, name)
{
  if (!name)
    setName("CurveGroupBox");
  CurveGroupBoxLayout = new QVBoxLayout(this, 11, 6, "CurveGroupBoxLayout");

  layout26 = new QVBoxLayout(0, 0, 6, "layout26");

  layout25 = new QHBoxLayout(0, 0, 6, "layout25");

  layout24 = new QVBoxLayout(0, 0, 6, "layout24");

  curveTitleLabel = new QLabel(this, "curveTitleLabel");
  layout24->addWidget(curveTitleLabel);

  xLabel = new QLabel(this, "xLabel");
  layout24->addWidget(xLabel);

  textLabel5 = new QLabel(this, "textLabel5");
  layout24->addWidget(textLabel5);

  yLabel = new QLabel(this, "yLabel");
  layout24->addWidget(yLabel);

  textLabel5_2 = new QLabel(this, "textLabel5_2");
  layout24->addWidget(textLabel5_2);
  layout25->addLayout(layout24);

  layout23 = new QVBoxLayout(0, 0, 6, "layout23");

  curveTitleLineEdit = new QLineEdit(this, "curveTitleLineEdit");
  layout23->addWidget(curveTitleLineEdit);

  layout22 = new QHBoxLayout(0, 0, 6, "layout22");

  layout34 = new QVBoxLayout(0, 0, 6, "layout34");

  xComboBox = new QComboBox(FALSE, this, "xComboBox");
  xComboBox->setSizeLimit(1);
  layout34->addWidget(xComboBox);

  xTitleLineEdit = new QLineEdit(this, "xTitleLineEdit");
  layout34->addWidget(xTitleLineEdit);

  yComboBox = new QComboBox(FALSE, this, "yComboBox");
  yComboBox->setSizeLimit(1);
  layout34->addWidget(yComboBox);

  yTitleLineEdit = new QLineEdit(this, "yTitleLineEdit");
  layout34->addWidget(yTitleLineEdit);
  layout22->addLayout(layout34);

  layout33 = new QVBoxLayout(0, 0, 6, "layout33");

  buttonGroup2 = new QButtonGroup(this, "buttonGroup2");
  buttonGroup2->setColumnLayout(0, Qt::Vertical);
  buttonGroup2->layout()->setSpacing(6);
  buttonGroup2->layout()->setMargin(11);
  buttonGroup2Layout = new QGridLayout(buttonGroup2->layout());
  buttonGroup2Layout->setAlignment(Qt::AlignTop);

  layout15 = new QVBoxLayout(0, 0, 6, "layout15");

  xBtmRadioButton = new QRadioButton(buttonGroup2, "xBtmRadioButton");
  layout15->addWidget(xBtmRadioButton);

  xTopRadioButton = new QRadioButton(buttonGroup2, "xTopRadioButton");
  layout15->addWidget(xTopRadioButton);

  xBtmRadioButton->setChecked(true);   // use xBottom by default

  buttonGroup2Layout->addLayout(layout15, 0, 0);
  layout33->addWidget(buttonGroup2);

  buttonGroup2_2 = new QButtonGroup(this, "buttonGroup2_2");
  buttonGroup2_2->setColumnLayout(0, Qt::Vertical);
  buttonGroup2_2->layout()->setSpacing(6);
  buttonGroup2_2->layout()->setMargin(11);
  buttonGroup2_2Layout = new QGridLayout(buttonGroup2_2->layout());
  buttonGroup2_2Layout->setAlignment(Qt::AlignTop);

  layout15_2 = new QVBoxLayout(0, 0, 6, "layout15_2");

  yLeftRadioButton = new QRadioButton(buttonGroup2_2, "yLeftRadioButton");
  layout15_2->addWidget(yLeftRadioButton);

  yRightRadioButton = new QRadioButton(buttonGroup2_2, "yRightRadioButton");
  layout15_2->addWidget(yRightRadioButton);

  yLeftRadioButton->setChecked(true);   // use yLeft by default

  buttonGroup2_2Layout->addLayout(layout15_2, 0, 0);
  layout33->addWidget(buttonGroup2_2);
  layout22->addLayout(layout33);
  layout23->addLayout(layout22);
  layout25->addLayout(layout23);
  layout26->addLayout(layout25);

  CurveGroupBoxLayout->addLayout(layout26);
  languageChange();
  resize(QSize(488, 401).expandedTo(minimumSizeHint()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CurveGroupBox::~CurveGroupBox()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CurveGroupBox::languageChange()
{
  //setCaption(tr("Form1"));
  curveTitleLabel->setText(tr("Curve Title"));
  xLabel->setText(tr("X Axis:"));
  textLabel5->setText(tr("Caption"));
  yLabel->setText(tr("Y Axis:"));
  textLabel5_2->setText(tr("Caption"));
  buttonGroup2->setTitle(tr("Use"));
  xBtmRadioButton->setText(tr("Bottom"));
  xTopRadioButton->setText(tr("Top"));
  buttonGroup2_2->setTitle(tr("Use"));
  yLeftRadioButton->setText(tr("Left"));
  yRightRadioButton->setText(tr("Right"));
}
