/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ScanItemWidget.cpp,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/21 20:33:59 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 06/03 
Comment : Copasi ScanItemWidget including:
 
Contains: the sub scrollable widget inside the scanwidget
 
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#include <qvariant.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include "ScanItemWidget.h"
#include "ScanWidget.h"
#include "qtUtilities.h"
#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

/*
 *  Constructs a ScanItemWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */

int ScanItemWidget::labelMaxWidth = 0;

ScanItemWidget::ScanItemWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  pParameter = NULL;
  strDensityLabel = tr("Density");
  strMaxLabel = tr("Max");
  strMinLabel = tr("Min");
  strMeanLabel = tr("Mean");
  strSTDLabel = tr("Std.Dev.");

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

  isFirstWidget = false;
}

void ScanItemWidget::MaxValueChanged(const QString&)
{setParameterValue(pParameter, "max", mMax->text());}

void ScanItemWidget::MinValueChanged(const QString&)
{setParameterValue(pParameter, "min", mMin->text());}

void ScanItemWidget::DensityValueChanged(const QString&)
{setParameterValue(pParameter, "density", mDensity->text());}

void ScanItemWidget::IndependentClicked()
{
  if (isFirstWidget)
    mIndependent->setChecked(true);
  pParameter->setValue("indp", (bool) mIndependent->isChecked());
}

void ScanItemWidget::LogarithmicClicked()
{pParameter->setValue("log", (bool) mLogarithmic->isChecked());}

void ScanItemWidget::RegularGridClicked()
{
  mMinLabel->setText(strMinLabel);
  mMinLabel->setFixedWidth(labelMaxWidth);

  mMaxLabel->setText(strMaxLabel);
  mMaxLabel->setFixedWidth(labelMaxWidth);

  pParameter->setValue("gridType", (C_INT32) CScanProblem::SD_REGULAR);
}

void ScanItemWidget::UniformClicked()
{
  mMinLabel->setText(strMinLabel);
  mMinLabel->setFixedWidth(labelMaxWidth);

  mMaxLabel->setText(strMaxLabel);
  mMaxLabel->setFixedWidth(labelMaxWidth);

  pParameter->setValue("gridType", (C_INT32) CScanProblem::SD_UNIFORM);
}

void ScanItemWidget::GaussianClicked()
{
  mMinLabel->setText(strMeanLabel);
  mMinLabel->setFixedWidth(labelMaxWidth);

  mMaxLabel->setText(strSTDLabel);
  mMaxLabel->setFixedWidth(labelMaxWidth);
  pParameter->setValue("gridType", (C_INT32) CScanProblem::SD_GAUSS);
}

void ScanItemWidget::PosGaussianClicked()
{
  mMinLabel->setText(strMeanLabel);
  mMinLabel->setFixedWidth(labelMaxWidth);

  mMaxLabel->setText(strSTDLabel);
  mMaxLabel->setFixedWidth(labelMaxWidth);
  pParameter->setValue("gridType", (C_INT32) CScanProblem::SD_BOLTZ);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScanItemWidget::~ScanItemWidget()
{
  pObject = NULL; // cannot be deleted here
  // no need to delete child widgets, Qt does it all for us
}

void ScanItemWidget::ResetData()
{
  // clear the values of the variables
  mMax->setText("2.0");
  mMin->setText("1.0");
  mDensity->setText("2.0");
  mLogarithmic->setChecked(FALSE);
  // for the FirstWidget it is must be master
  mIndependent->setChecked(TRUE);
  mRegularGridRadio->setChecked(1);
  mGaussianRadio->setChecked(0);
  mUniformRadio->setChecked(0);
  mPosGaussianRadio->setChecked(0);
}

void ScanItemWidget::updateObject()
{
  mMax->setText(getParameterValue(pParameter, "max"));
  mMin->setText(getParameterValue(pParameter, "min"));
  mDensity-> setText(getParameterValue(pParameter, "density"));
  mLogarithmic->setChecked(* pParameter->getValue("log").pBOOL);
  mIndependent->setChecked(* pParameter->getValue("indp").pBOOL);
  switch (* pParameter->getValue("gridType").pINT)
    {
    case CScanProblem::SD_REGULAR:
      mMinLabel->setText(tr("Min"));
      mMaxLabel->setText(tr("Max"));
      mRegularGridRadio->setChecked(1);
      break;
    case CScanProblem::SD_UNIFORM:
      mMinLabel->setText(tr("Min"));
      mMaxLabel->setText(tr("Max"));
      mUniformRadio->setChecked(1);
      break;
    case CScanProblem::SD_GAUSS:
      mMinLabel->setText(tr("Mean"));
      mMaxLabel->setText(tr("Std.Dev."));
      mGaussianRadio->setChecked(1);
      break;
    case CScanProblem::SD_BOLTZ:
      mMinLabel->setText(tr("Mean"));
      mMaxLabel->setText(tr("Std.Dev."));
      mPosGaussianRadio->setChecked(1);
      break;
    }
}

void ScanItemWidget::InitializeParameterList()
{
  //name value type
  pParameter->addParameter("max", CCopasiParameter::DOUBLE);
  setParameterValue(pParameter, "max", mMax->text());
  pParameter->addParameter("min", CCopasiParameter::DOUBLE);
  setParameterValue(pParameter, "min", mMin->text());
  pParameter->addParameter("density", CCopasiParameter::UINT);
  setParameterValue(pParameter, "density", mDensity->text());
  pParameter->addParameter("log", CCopasiParameter::BOOL,
                           (bool) mLogarithmic->isChecked());
  pParameter->addParameter("indp", CCopasiParameter::BOOL,
                           (bool) mIndependent->isChecked());

  if (mRegularGridRadio->isChecked())
    pParameter->addParameter("gridType", CCopasiParameter::INT,
                             (C_INT32) CScanProblem::SD_REGULAR);
  else if (mGaussianRadio->isChecked())
    pParameter->addParameter("gridType", CCopasiParameter::INT,
                             (C_INT32) CScanProblem::SD_GAUSS);
  else if (mUniformRadio->isChecked())
    pParameter->addParameter("gridType", CCopasiParameter::INT,
                             (C_INT32) CScanProblem::SD_UNIFORM);
  else if (mPosGaussianRadio->isChecked())
    pParameter->addParameter("gridType", CCopasiParameter::INT,
                             (C_INT32) CScanProblem::SD_BOLTZ);

  pParameter->addParameter("incr", CCopasiParameter::DOUBLE, (C_FLOAT64) 0);
  pParameter->addParameter("ampl", CCopasiParameter::DOUBLE, (C_FLOAT64) 0);
}

void ScanItemWidget::loadObject()
{
  if (!pParameter)
    return;
  ResetData();
  InitializeParameterList();
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ScanItemWidget::languageChange()
{
  setCaption(tr("ScanItemWidget"));

  labelMaxWidth = fontMetrics().width(strSTDLabel);
  if (fontMetrics().width(strDensityLabel) > labelMaxWidth)
    labelMaxWidth = fontMetrics().width(strDensityLabel);

  mDensityLabel->setText(strDensityLabel);
  mDensityLabel->setFixedWidth(labelMaxWidth);

  mMaxLabel->setText(strMaxLabel);
  mMaxLabel->setFixedWidth(labelMaxWidth);

  mMinLabel->setText(strMinLabel);
  mMinLabel->setFixedWidth(labelMaxWidth);

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

void ScanItemWidget::setFirstWidget(bool isFirst)
{
  if (isFirst)
    {
      mIndependent->setChecked(true);
      pParameter->setValue("indp", (bool) mIndependent->isChecked());
    }
  isFirstWidget = isFirst;
}

void ScanItemWidget::mousePressEvent (QMouseEvent * e)
{QWidget::mousePressEvent(e);}

void ScanItemWidget::setScanObject(CCopasiParameterGroup* pNewParameter)
{pParameter = pNewParameter;}

CCopasiParameterGroup* ScanItemWidget::getScanObject()
{return pParameter;}

void ScanItemWidget::setCopasiObject(CCopasiObject* pNewObject)
{pObject = pNewObject;}

CCopasiObject* ScanItemWidget::getCopasiObject()
{return pObject;}
