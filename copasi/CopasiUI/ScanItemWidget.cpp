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

#include "utilities/CMethodParameterList.h" 
/*
 *  Constructs a ScanItemWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ScanItemWidget::ScanItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("ScanItemWidget");
  ScanItemWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanItemWidgetLayout");

  layout18 = new QVBoxLayout(0, 0, 6, "layout18");

  layout15 = new QHBoxLayout(0, 0, 6, "layout15");

  mMinLabel = new QLabel(this, "mMinLabel");
  layout15->addWidget(mMinLabel);
  QSpacerItem* spacer = new QSpacerItem(31, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout15->addItem(spacer);

  mMin = new ScanLineEdit(this, "mMin");
  mMin->setFrameShape(ScanLineEdit::LineEditPanel);
  mMin->setFrameShadow(ScanLineEdit::Sunken);
  layout15->addWidget(mMin);
  layout18->addLayout(layout15);

  layout16 = new QHBoxLayout(0, 0, 6, "layout16");

  mMaxLabel = new QLabel(this, "mMaxLabel");
  layout16->addWidget(mMaxLabel);
  QSpacerItem* spacer_2 = new QSpacerItem(31, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout16->addItem(spacer_2);

  mMax = new ScanLineEdit(this, "mMax");
  layout16->addWidget(mMax);
  layout18->addLayout(layout16);

  layout17 = new QHBoxLayout(0, 0, 6, "layout17");

  mDensityLabel = new QLabel(this, "mDensityLabel");
  layout17->addWidget(mDensityLabel);
  QSpacerItem* spacer_3 = new QSpacerItem(31, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout17->addItem(spacer_3);

  mDensity = new ScanLineEdit(this, "mDensity");
  mDensity->setFrameShape(ScanLineEdit::LineEditPanel);
  mDensity->setFrameShadow(ScanLineEdit::Sunken);
  layout17->addWidget(mDensity);
  layout18->addLayout(layout17);

  ScanItemWidgetLayout->addLayout(layout18, 0, 0);

  layout21 = new QVBoxLayout(0, 0, 6, "layout21");

  mLogarithmic = new ScanCheckBox(this, "bLogarithmic");
  layout21->addWidget(mLogarithmic);

  mIndependent = new ScanCheckBox(this, "mIndependent");
  layout21->addWidget(mIndependent);

  ScanItemWidgetLayout->addLayout(layout21, 1, 0);

  buttonGroup = new QButtonGroup(this, "buttonGroup");
  buttonGroup->setFrameShape(QFrame::StyledPanel);
  buttonGroup->setFrameShadow(QFrame::Sunken);
  buttonGroup->setLineWidth(2);
  buttonGroup->setExclusive(TRUE);
  buttonGroup->setColumnLayout(0, Qt::Vertical);
  buttonGroup->layout()->setSpacing(6);
  buttonGroup->layout()->setMargin(11);
  buttonGroupLayout = new QGridLayout(buttonGroup->layout());
  buttonGroupLayout->setAlignment(Qt::AlignTop);

  layout19 = new QVBoxLayout(0, 0, 6, "layout19");

  mRegularGridRadio = new ScanRadioButton(buttonGroup, "mRegularGridRadio");
  layout19->addWidget(mRegularGridRadio);

  randomeLabel = new QLabel(buttonGroup, "randomeLabel");
  randomeLabel->setFrameShadow(QLabel::Sunken);
  layout19->addWidget(randomeLabel);

  buttonGroupLayout->addMultiCellLayout(layout19, 0, 0, 0, 1);

  layout20 = new QVBoxLayout(0, 0, 6, "layout20");

  mUniformRadio = new ScanRadioButton(buttonGroup, "mUniformRadio");
  layout20->addWidget(mUniformRadio);

  mGaussianRadio = new ScanRadioButton(buttonGroup, "mNormalRadio");
  layout20->addWidget(mGaussianRadio);

  mPosGaussianRadio = new ScanRadioButton(buttonGroup, "mPosGaussianRadio");
  layout20->addWidget(mPosGaussianRadio);

  buttonGroupLayout->addLayout(layout20, 1, 1);
  QSpacerItem* spacer_4 = new QSpacerItem(20, 50, QSizePolicy::Expanding, QSizePolicy::Minimum);
  buttonGroupLayout->addItem(spacer_4, 1, 0);

  ScanItemWidgetLayout->addMultiCellWidget(buttonGroup, 0, 1, 1, 1);
  languageChange();
  resize(QSize(320, 162).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // tab order
  setTabOrder(mMin, mMax);
  setTabOrder(mMax, mDensity);
  setTabOrder(mDensity, mIndependent);
  setTabOrder(mIndependent, mLogarithmic);
  setTabOrder(mLogarithmic, mRegularGridRadio);
  setTabOrder(mRegularGridRadio, mUniformRadio);
  setTabOrder(mUniformRadio, mGaussianRadio);
  setTabOrder(mGaussianRadio, mPosGaussianRadio);

  connect(mMin, SIGNAL(textChanged(const QString&)), this, SLOT(MinValueChanged(const QString&)));
  connect(mMax, SIGNAL(textChanged(const QString&)), this, SLOT(MaxValueChanged(const QString&)));
  connect(mDensity, SIGNAL(textChanged(const QString&)), this, SLOT(DensityValueChanged(const QString&)));
  connect(mIndependent, SIGNAL(clicked()), this, SLOT(IndependentClicked()));
  connect(mLogarithmic, SIGNAL(clicked()), this, SLOT(LogarithmicClicked()));
  connect(mRegularGridRadio, SIGNAL(clicked()), this, SLOT(RegularGridClicked()));
  connect(mUniformRadio, SIGNAL(clicked()), this, SLOT(UniformClicked()));
  connect(mGaussianRadio, SIGNAL(clicked()), this, SLOT(GaussianClicked()));
  connect(mPosGaussianRadio, SIGNAL(clicked()), this, SLOT(PosGaussianClicked()));

  pParameter = NULL;
}

void ScanItemWidget::MaxValueChanged(const QString&)
{
  pParameter->setValue("max", mMax->text().toDouble());
  /*  for verfication
   if (pParameter->getIndex("max")==C_INVALID_INDEX)
    return;
   double max = pParameter->getValue("max");
  */
}

void ScanItemWidget::MinValueChanged(const QString&)
{
  pParameter->setValue("min", mMin->text().toDouble());
}

void ScanItemWidget::DensityValueChanged(const QString&)
{
  pParameter->setValue("incr", mDensity->text().toDouble());
  /*  for verfication
   if (pParameter->getIndex("incr")==C_INVALID_INDEX)
    return;
   double toDouble = pParameter->getValue("incr");
  */
}

void ScanItemWidget::IndependentClicked()
{
  pParameter->setValue("Indp", mIndependent->isChecked());
  /*  for verfication
   if (pParameter->getIndex("Indp")==C_INVALID_INDEX)
    return;
   bool Indp = pParameter->getValue("Indp");
  */
}

void ScanItemWidget::LogarithmicClicked()
{
  pParameter->setValue("log", mLogarithmic->isChecked());
  /*  for verfication
   if (pParameter->getIndex("log")==C_INVALID_INDEX)
    return;
   bool Indp = pParameter->getValue("log");
  */
}

void ScanItemWidget::RegularGridClicked()
{
  mMinLabel->setText(tr("Min"));
  mMaxLabel->setText(tr("Max"));
  pParameter->setValue("gridType", (C_INT32) SD_REGULAR);
}

void ScanItemWidget::UniformClicked()
{
  mMinLabel->setText(tr("Min"));
  mMaxLabel->setText(tr("Max"));
  pParameter->setValue("gridType", (C_INT32) SD_UNIFORM);
}

void ScanItemWidget::GaussianClicked()
{
  mMinLabel->setText(tr("Mean"));
  mMaxLabel->setText(tr("Std.Dev."));
  pParameter->setValue("gridType", (C_INT32) SD_GAUSS);
}

void ScanItemWidget::PosGaussianClicked()
{
  mMinLabel->setText(tr("Mean"));
  mMaxLabel->setText(tr("Std.Dev."));
  pParameter->setValue("gridType", (C_INT32) SD_BOLTZ);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScanItemWidget::~ScanItemWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void ScanItemWidget::ResetData()
{
  // clear the values of the variables
  mMax->setText("2.0");
  mMin->setText("1.0");
  mDensity->setText("2");
  mLogarithmic->setChecked(FALSE);
  mIndependent->setChecked(TRUE);
  mRegularGridRadio->setChecked(1);
  mGaussianRadio->setChecked(0);
  mUniformRadio->setChecked(0);
  mPosGaussianRadio->setChecked(0);
}

void ScanItemWidget::updateObject()
{
  mMax->setText(QString::number(pParameter->getValue("max")));
  mMin->setText(QString::number(pParameter->getValue("min")));
  mDensity->setText(QString::number(pParameter->getValue("incr")));
  mLogarithmic->setChecked(pParameter->getValue("log"));
  mIndependent->setChecked(pParameter->getValue("Indp"));
  switch (int(pParameter->getValue("gridType")))
    {
    case SD_REGULAR:
      mMinLabel->setText(tr("Min"));
      mMaxLabel->setText(tr("Max"));
      mRegularGridRadio->setChecked(1);
      break;
    case SD_UNIFORM:
      mMinLabel->setText(tr("Min"));
      mMaxLabel->setText(tr("Max"));
      mUniformRadio->setChecked(1);
      break;
    case SD_GAUSS:
      mMinLabel->setText(tr("Mean"));
      mMaxLabel->setText(tr("Std.Dev."));
      mGaussianRadio->setChecked(1);
      break;
    case SD_BOLTZ:
      mMinLabel->setText(tr("Mean"));
      mMaxLabel->setText(tr("Std.Dev."));
      mPosGaussianRadio->setChecked(1);
      break;
    }
}

void ScanItemWidget::InitializeParameterList()
{
  //name value type
  pParameter->add("max", mMax->text().toDouble(), CParameter::DOUBLE);
  pParameter->add("min", mMin->text().toDouble(), CParameter::DOUBLE);
  pParameter->add("incr", mDensity->text().toDouble(), CParameter::DOUBLE);
  pParameter->add("log", mLogarithmic->text().toUInt(), CParameter::BOOL);
  pParameter->add("Indp", mIndependent->text().toUInt(), CParameter::BOOL);

  if (mRegularGridRadio->isChecked())
    pParameter->add("gridType", SD_REGULAR, CParameter::INT);
  else
    if (mGaussianRadio->isChecked())
      pParameter->add("gridType", SD_GAUSS, CParameter::INT);
    else
      if (mUniformRadio->isChecked())
        pParameter->add("gridType", SD_UNIFORM, CParameter::INT);
      else
        if (mPosGaussianRadio->isChecked())
          pParameter->add("gridType", SD_BOLTZ, CParameter::INT);

  pParameter->add("value", 0, CParameter::DOUBLE);
}

void ScanItemWidget::loadObject()
{
  if (!pParameter)
    return;
  ResetData();
  InitializeParameterList();

  int i = 0;
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ScanItemWidget::languageChange()
{
  setCaption(tr("ScanItemWidget"));
  mDensityLabel->setText(tr("Density"));
  mMaxLabel->setText(tr("Max"));
  mMinLabel->setText(tr("Min"));
  mDensity->setText(QString::null);
  mIndependent->setText(tr("          Master"));
  mLogarithmic->setText(tr("          Logarithmic"));
  buttonGroup->setTitle(QString::null);
  mGaussianRadio->setText(tr("Normal"));
  mUniformRadio->setText(tr("Uniform"));
  mPosGaussianRadio->setText(tr("Pos. Normal"));
  mRegularGridRadio->setText(tr("Regular Grid"));
  randomeLabel->setText(tr("Random"));
}
