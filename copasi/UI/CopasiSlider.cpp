/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CopasiSlider.cpp,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/03/23 18:58:37 $
   End CVS Header */

#include <math.h>

#include "qlabel.h"
#include "qstring.h"
#include "qslider.h"
#include "qpixmap.h"
#include "qtoolbutton.h"
#include "qvbox.h"
#include "qtooltip.h"

#include "CopasiSlider.h"
#include "qtUtilities.h"

#include "icons/closeSlider.xpm"
#include "icons/editSlider.xpm"

CopasiSlider::CopasiSlider(CSlider* pSlider, QWidget* parent): QHBox(parent), mpCSlider(pSlider) , mpQSlider(NULL), mpLabel(NULL), mpCloseButton(NULL), mpEditButton(NULL), mValueOutOfRange(false)
{
  this->setFrameShape(QFrame::Box);
  this->setSpacing(2);
  this->setMargin(2);
  QVBox* sliderLayout = new QVBox(this);
  this->mpLabel = new QLabel(sliderLayout);
  this->mpLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  this->mpQSlider = new QSlider(Qt::Horizontal, sliderLayout);
  this->mpQSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

  QVBox* buttonLayout = new QVBox(this);
  buttonLayout->setSpacing(0);
  QPixmap icons[2] = {closeSlider, editSlider};
  this->mpCloseButton = new QToolButton(buttonLayout);
  this->mpCloseButton->setPixmap(icons[0]);
  this->mpCloseButton->setFixedSize(13, 13);
  this->mpEditButton = new QToolButton(buttonLayout);
  this->mpEditButton->setPixmap(icons[1]);
  this->mpEditButton->setFixedSize(13, 13);
  this->updateSliderData();
  QToolTip::add(this->mpCloseButton, tr("remove slider"));
  QToolTip::add(this->mpEditButton, tr("edit slider"));
  connect(this->mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
  connect(this->mpQSlider, SIGNAL(sliderReleased()), this, SLOT(qSliderReleased()));
  connect(this->mpQSlider, SIGNAL(sliderPressed()), this, SLOT(qSliderPressed()));
  connect(this->mpCloseButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
  connect(this->mpEditButton, SIGNAL(clicked()), this, SLOT(editButtonClicked()));
}

CopasiSlider::~CopasiSlider()
{}

void CopasiSlider::updateSliderData()
{
  if (this->mpCSlider)
    {
      mpCSlider->compile();
      this->mpQSlider->setMinValue(0);
      this->mpQSlider->setMaxValue(this->mpCSlider->getTickNumber());
      this->mpQSlider->setTickInterval(1);
      this->mpQSlider->setLineStep(1);
      this->mpQSlider->setPageStep(this->mpCSlider->getTickFactor());
      disconnect(this->mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
      this->mpQSlider->setValue(this->calculatePositionFromValue(this->mpCSlider->getSliderValue()));
      connect(this->mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
      this->updateLabel();
    }
}

C_FLOAT64 CopasiSlider::value() const
  {
    return this->mpCSlider->getSliderValue();
  }

void CopasiSlider::setValue(C_FLOAT64 value)
{
  this->mpCSlider->setSliderValue(value);

  /* reget value in case it was outside range and got set to minValue or
   * maxValue */
  value = this->mpCSlider->getSliderValue();

  this->mpQSlider->setValue(this->calculatePositionFromValue(value));

  this->updateLabel();
}

unsigned C_INT32 CopasiSlider::minorMajorFactor() const
  {
    return this->mpCSlider->getTickFactor();
  }

void CopasiSlider::setMinorMajorFactor(unsigned C_INT32 factor)
{
  this->mpCSlider->setTickFactor(factor);
  this->mpQSlider->setPageStep(this->mpQSlider->lineStep()*factor);
}

C_FLOAT64 CopasiSlider::minorTickInterval() const
  {
    return (C_FLOAT64)(this->mpCSlider->getMaxValue() - this->mpCSlider->getMinValue()) / ((C_FLOAT64)this->mpCSlider->getTickNumber());
  }

void CopasiSlider::setNumMinorTicks(unsigned C_INT32 numMinorTicks)
{
  this->mpCSlider->setTickNumber(numMinorTicks);
  // set maxValue and value of slider
  this->mpQSlider->setMaxValue(numMinorTicks);
  this->mpQSlider->setValue(this->calculatePositionFromValue(this->mpCSlider->getSliderValue()));
}

unsigned C_INT32 CopasiSlider::numMinorTicks() const
  {
    return this->mpCSlider->getTickNumber();
  }

C_FLOAT64 CopasiSlider::minValue() const
  {
    return this->mpCSlider->getMinValue();
  }

C_FLOAT64 CopasiSlider::maxValue() const
  {
    return this->mpCSlider->getMaxValue();
  }

CCopasiObject* CopasiSlider::object() const
  {
    return this->mpCSlider->getSliderObject();
  }

void CopasiSlider::setObject(CCopasiObject* object)
{
  this->mpCSlider->setSliderObject(object);
  this->updateSliderData();
}

void CopasiSlider::setMaxValue(C_FLOAT64 value)
{
  this->mpCSlider->setMaxValue(value);

  this->mpQSlider->setValue(this->calculatePositionFromValue(this->mpCSlider->getSliderValue()));

  this->updateLabel();
}

void CopasiSlider::setMinValue(C_FLOAT64 value)
{
  this->mpCSlider->setMinValue(value);

  this->mpQSlider->setValue(this->calculatePositionFromValue(this->mpCSlider->getSliderValue()));

  this->updateLabel();
}

void CopasiSlider::updateLabel()
{
  double minValue, maxValue, currValue;
  minValue = this->mpCSlider->getMinValue();
  maxValue = this->mpCSlider->getMaxValue();
  currValue = this->mpCSlider->getSliderValue();
  CCopasiObject* object = this->mpCSlider->getSliderObject();

  QString labelString = "";
  if (object)
    {
      labelString += FROM_UTF8(object->getObjectDisplayName(true, true));
    }
  labelString += " : [";
  labelString += QString::number(minValue);
  labelString += "-";
  labelString += QString::number(maxValue);
  labelString += "] {";
  labelString += QString::number(currValue);
  labelString += "}";
  if (this->mValueOutOfRange)
    {
      labelString += " (Value out of range!)";
    }
  this->mpLabel->setText(labelString);
}

void CopasiSlider::sliderValueChanged(int value)
{
  this->mpCSlider->setSliderValue(this->calculateValueFromPosition(value), false);

  this->updateLabel();

  emit valueChanged(this->mpCSlider->getSliderValue());
}

void CopasiSlider::qSliderReleased()
{
  emit sliderReleased();
}

void CopasiSlider::qSliderPressed()
{
  emit sliderPressed();
}

CSlider::Type CopasiSlider::type() const
  {
    return this->mpCSlider->getSliderType();
  }

void CopasiSlider::setType(CSlider::Type type)
{
  this->mpCSlider->setSliderType(type);
}

void CopasiSlider::updateValue(bool modifyRange)
{
  double value = this->mpCSlider->getSliderValue();
  double maxValue = this->mpCSlider->getMaxValue();
  double minValue = this->mpCSlider->getMinValue();

  if ((value > maxValue) || (value < minValue))
    {
      if (!modifyRange)
        {
          this->mValueOutOfRange = true;
        }
      else
        {
          this->mValueOutOfRange = false;
          this->mpCSlider->resetRange();
        }
    }

  this->mpCSlider->writeToObject();
}

void CopasiSlider::closeButtonClicked()
{
  emit closeClicked(this);
}

void CopasiSlider::editButtonClicked()
{
  emit editClicked(this);
}

CSlider* CopasiSlider::getCSlider() const
  {
    return this->mpCSlider;
  }

C_FLOAT64 CopasiSlider::calculateValueFromPosition(int position)
{
  double value;
  double exponent;
  switch (this->mpCSlider->getScaling())
    {
    case CSlider::linear:
      value = this->mpCSlider->getMinValue() + position * this->minorTickInterval();
      break;
    case CSlider::logarithmic:
      exponent = (log10(this->mpCSlider->getMaxValue() - this->mpCSlider->getMinValue()) * position) / this->mpCSlider->getTickNumber();
      value = this->mpCSlider->getMinValue() + (pow(10, exponent)) - 1;
      break;
    default:
      value = 0.0;
      break;
    }
  return value;
}

int CopasiSlider::calculatePositionFromValue(C_FLOAT64 value)
{
  int position;
  switch (this->mpCSlider->getScaling())
    {
    case CSlider::linear:
      position = (int)floor(((this->mpCSlider->getSliderValue() - this->mpCSlider->getMinValue()) / this->minorTickInterval()) + 0.5);
      break;
    case CSlider::logarithmic:

      position = (int)floor((log10(value + 1 - this->mpCSlider->getMinValue()) * this->mpCSlider->getTickNumber()) / (log10(this->mpCSlider->getMaxValue() - this->mpCSlider->getMinValue())));
      break;
    default:
      position = 0;
    }
  return position;
}
