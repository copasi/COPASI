/****************************************************************************
 ** Form implementation generated from reading ui file '.\ScanItemWidget.ui'
 **
 ** Created: Thu May 22 10:43:21 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "ScanItemWidget.h"
#include "ScanWidget.h"
#include <qvariant.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a ScanItemWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ScanItemWidget::ScanItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("ScanItemWidget");

  setCaption(trUtf8("ScanItemWidget"));
  ScanItemWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanItemWidgetLayout");

  Layout13 = new QVBoxLayout(0, 0, 6, "Layout13");

  bMaster = new ScanCheckBox(this, "bMaster");
  bMaster->setText(trUtf8("          Master"));
  Layout13->addWidget(bMaster);

  bLogarithmic = new ScanCheckBox(this, "bLogarithmic");
  bLogarithmic->setText(trUtf8("          Logarithmic"));
  Layout13->addWidget(bLogarithmic);

  ScanItemWidgetLayout->addLayout(Layout13, 2, 0);

  Layout34 = new QGridLayout(0, 1, 1, 0, 6, "Layout34");

  Layout7 = new QGridLayout(0, 1, 1, 0, 6, "Layout7");

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Density"));

  Layout7->addWidget(TextLabel3, 2, 0);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Max"));

  Layout7->addWidget(TextLabel2, 1, 0);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Min"));

  Layout7->addWidget(TextLabel1, 0, 0);

  Layout34->addLayout(Layout7, 0, 0);

  Layout33 = new QVBoxLayout(0, 0, 6, "Layout33");
  QSpacerItem* spacer = new QSpacerItem(170, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  Layout33->addItem(spacer);

  nMin = new ScanLineEdit(this, "nMin");
  Layout33->addWidget(nMin);
  QSpacerItem* spacer_2 = new QSpacerItem(170, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  Layout33->addItem(spacer_2);

  nMax = new ScanLineEdit(this, "nMax");
  Layout33->addWidget(nMax);
  QSpacerItem* spacer_3 = new QSpacerItem(150, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);
  Layout33->addItem(spacer_3);

  nDensity = new ScanLineEdit(this, "nDensity");
  nDensity->setText(trUtf8(""));
  Layout33->addWidget(nDensity);
  QSpacerItem* spacer_4 = new QSpacerItem(170, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
  Layout33->addItem(spacer_4);

  Layout34->addLayout(Layout33, 0, 1);

  ScanItemWidgetLayout->addMultiCellLayout(Layout34, 0, 1, 0, 0);

  bRegularGrid = new ScanRadioButton(this, "bRegularGrid");
  bRegularGrid->setText(trUtf8("Regular Grid"));

  ScanItemWidgetLayout->addWidget(bRegularGrid, 0, 1);

  RandomGroup = new QButtonGroup(this, "RandomGroup");
  RandomGroup->setFrameShape(QButtonGroup::Panel);
  RandomGroup->setTitle(trUtf8("   Random"));
  RandomGroup->setExclusive(TRUE);
  RandomGroup->setColumnLayout(0, Qt::Vertical);
  RandomGroup->layout()->setSpacing(6);
  RandomGroup->layout()->setMargin(11);
  RandomGroupLayout = new QGridLayout(RandomGroup->layout());
  RandomGroupLayout->setAlignment(Qt::AlignTop);

  mNormalRadio = new ScanRadioButton(RandomGroup, "mNormalRadio");
  mNormalRadio->setText(trUtf8("Normal"));

  RandomGroupLayout->addWidget(mNormalRadio, 1, 0);

  mPosNormalRadio = new ScanRadioButton(RandomGroup, "mPosNormalRadio");
  mPosNormalRadio->setText(trUtf8("Pos. Normal"));

  RandomGroupLayout->addWidget(mPosNormalRadio, 2, 0);

  mUniformRadio = new ScanRadioButton(RandomGroup, "mUniformRadio");
  mUniformRadio->setText(trUtf8("Uniform"));

  RandomGroupLayout->addWidget(mUniformRadio, 0, 0);

  ScanItemWidgetLayout->addMultiCellWidget(RandomGroup, 1, 2, 1, 1);

  /*
    setCaption(trUtf8("ScanItemWidget"));
    ScanItemWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanItemWidgetLayout");
   
    Layout13 = new QVBoxLayout(0, 0, 6, "Layout13");
   
    bMaster = new ScanCheckBox(this, "bMaster");
    bMaster->setText(trUtf8("      Master"));
    Layout13->addWidget(bMaster);
   
    bLogarithmic = new ScanCheckBox(this, "bLogarithmic");
    bLogarithmic->setText(trUtf8("      Logarithmic"));
    Layout13->addWidget(bLogarithmic);
   
    ScanItemWidgetLayout->addLayout(Layout13, 2, 0);
   
    RandomGroup = new QButtonGroup(this, "RandomGroup");
    RandomGroup->setFrameShape(QButtonGroup::Panel);
    RandomGroup->setTitle(trUtf8("   Random"));
   
    QWidget* privateLayoutWidget = new QWidget(RandomGroup, "Layout4");
    privateLayoutWidget->setGeometry(QRect(9, 25, 110, 68));
    Layout4 = new QGridLayout(privateLayoutWidget, 1, 1, 0, 6, "Layout4");
   
    mUniformRadio = new ScanRadioButton(privateLayoutWidget, "mUniformRadio");
    mUniformRadio->setText(trUtf8("Uniform"));
   
    Layout4->addWidget(mUniformRadio, 0, 0);
   
    mPosNormalRadio = new ScanRadioButton(privateLayoutWidget, "mPosNormalRadio");
    mPosNormalRadio->setText(trUtf8("Pos. Normal"));
   
    Layout4->addWidget(mPosNormalRadio, 2, 0);
   
    mNormalRadio = new ScanRadioButton(privateLayoutWidget, "mNormalRadio");
    mNormalRadio->setText(trUtf8("Normal"));
   
    Layout4->addWidget(mNormalRadio, 1, 0);
   
    ScanItemWidgetLayout->addMultiCellWidget(RandomGroup, 1, 2, 1, 1);
   
    bRegularGrid = new ScanRadioButton(this, "bRegularGrid");
    bRegularGrid->setText(trUtf8("Regular Grid"));
   
    ScanItemWidgetLayout->addWidget(bRegularGrid, 0, 1);
   
    Layout34 = new QGridLayout(0, 1, 1, 0, 6, "Layout34");
   
    Layout7 = new QGridLayout(0, 1, 1, 0, 6, "Layout7");
   
    TextLabel3 = new QLabel(this, "TextLabel3");
    TextLabel3->setText(trUtf8("Density"));
   
    Layout7->addWidget(TextLabel3, 2, 0);
   
    TextLabel2 = new QLabel(this, "TextLabel2");
    TextLabel2->setText(trUtf8("Max"));
   
    Layout7->addWidget(TextLabel2, 1, 0);
   
    TextLabel1 = new QLabel(this, "TextLabel1");
    TextLabel1->setText(trUtf8("Min"));
   
    Layout7->addWidget(TextLabel1, 0, 0);
   
    Layout34->addLayout(Layout7, 0, 0);
   
    Layout33 = new QVBoxLayout(0, 0, 6, "Layout33");
    QSpacerItem* spacer = new QSpacerItem(170, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
    Layout33->addItem(spacer);
   
    nMin = new ScanLineEdit(this, "nMin");
    Layout33->addWidget(nMin);
    QSpacerItem* spacer_2 = new QSpacerItem(170, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
    Layout33->addItem(spacer_2);
   
    nMax = new ScanLineEdit(this, "nMax");
    Layout33->addWidget(nMax);
    QSpacerItem* spacer_3 = new QSpacerItem(150, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);
    Layout33->addItem(spacer_3);
   
    nDensity = new ScanLineEdit(this, "nDensity");
    nDensity->setText(trUtf8(""));
    Layout33->addWidget(nDensity);
    QSpacerItem* spacer_4 = new QSpacerItem(170, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);
    Layout33->addItem(spacer_4);
   
    Layout34->addLayout(Layout33, 0, 1);
   
    ScanItemWidgetLayout->addMultiCellLayout(Layout34, 0, 1, 0, 0);
  */
  pObject = NULL;
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScanItemWidget::~ScanItemWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void ScanItemWidget::loadObject()
{
  if (!pObject)
    return;
  int i = 0;
}
