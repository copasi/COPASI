/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiSlider.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/02/25 15:15:58 $
   End CVS Header */

#include <cmath>

#include "qlabel.h"
#include "qstring.h"
#include "qslider.h"
#include "qpixmap.h"
#include "qtoolbutton.h"
#include "qvbox.h"

#include "CopasiSlider.h"
#include "qtUtilities.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CCopasiParameterGroup.h"
#include "report/CCopasiObjectName.h"

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
      CCopasiObject* object = this->mpCSlider->getSliderObject();
      this->mpCSlider->setSliderValue(0.0);
      if (object->isValueDbl())
        {
          this->mpCSlider->setSliderValue(*(double*)object->getReference());
        }
      else if (object->isValueInt())
        {
          this->mpCSlider->setSliderValue((double)(*(int*)object->getReference()));
        }
      this->mpCSlider->setMinValue(0.0);
      this->mpCSlider->setMaxValue(2*this->mpCSlider->getSliderValue());
      this->mpCSlider->setTickNumber(100);
      this->mpCSlider->setTickFactor(10);
      this->mpQSlider->setMinValue(0);
      this->mpQSlider->setMaxValue(100);
      this->mpQSlider->setTickInterval(1);
      this->mpQSlider->setLineStep(1);
      this->mpQSlider->setPageStep(10);
      this->mpQSlider->setValue((int)floor(((this->mpCSlider->getSliderValue()) / this->minorTickInterval()) + 0.5));
      this->updateLabel();
    }
}

C_FLOAT64 CopasiSlider::value() const
  {
    return this->mpCSlider->getSliderValue();
  }

void CopasiSlider::setValue(C_FLOAT64 value)
{
  double minValue, maxValue, tickInterval, tickNumber;
  minValue = this->mpCSlider->getMinValue();
  maxValue = this->mpCSlider->getMaxValue();
  tickNumber = this->mpCSlider->getTickNumber();
  tickInterval = (maxValue - minValue) / tickNumber;
  CSlider::Type type = this->mpCSlider->getSliderType();
  CCopasiObject* object = this->mpCSlider->getSliderObject();

  if (value < minValue)
    {
      value = minValue;
    }
  else if (value > maxValue)
    {
      value = maxValue;
    }
  this->mpCSlider->setSliderValue(value);
  this->mpQSlider->setValue((int)floor(((value - minValue) / tickInterval) + 0.5));
  if (type == CSlider::Integer || type == CSlider::UnsignedInteger)
    {
      C_INT32* reference = (C_INT32*)(((CCopasiObjectReference<C_INT32>*)object)->getReference());

      *reference = (C_INT32)floor(value + 0.5);
    }
  else if (type == CSlider::Float || type == CSlider::UnsignedFloat)
    {
      C_FLOAT64* reference = (C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)object)->getReference());

      *reference = value;
    }
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
  this->mpQSlider->setValue((int)floor(((this->mpCSlider->getSliderValue() - this->mpCSlider->getMinValue()) / this->minorTickInterval()) + 0.5));
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
  double minValue = this->mpCSlider->getMinValue();
  if (value <= minValue) return;

  this->mpCSlider->setMaxValue(value);

  double maxValue = this->mpCSlider->getMaxValue();
  if (this->mpCSlider->getSliderValue() > maxValue)
    {
      this->mpCSlider->setSliderValue(maxValue);
    }

  this->mpQSlider->setValue((int)floor(((this->mpCSlider->getSliderValue() - minValue) / this->minorTickInterval()) + 0.5));

  this->updateLabel();
}

void CopasiSlider::setMinValue(C_FLOAT64 value)
{
  if (value >= this->mpCSlider->getMaxValue()) return;

  this->mpCSlider->setMinValue(value);

  double minValue = this->mpCSlider->getMinValue();
  if (this->mpCSlider->getSliderValue() < minValue)
    {
      this->mpCSlider->setSliderValue(minValue);
    }

  this->mpQSlider->setValue((int)floor(((this->mpCSlider->getSliderValue() - minValue) / this->minorTickInterval()) + 0.5));

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
  double currValue, minValue, tickInterval;
  minValue = this->mpCSlider->getMinValue();
  tickInterval = this->minorTickInterval();
  currValue = minValue + value * tickInterval;
  CSlider::Type type = this->mpCSlider->getSliderType();
  CCopasiObject* object = this->mpCSlider->getSliderObject();

  if (type == CSlider::Integer || type == CSlider::UnsignedInteger)
    {
      C_INT32* reference = (C_INT32*)(((CCopasiObjectReference<C_INT32>*)object)->getReference());

      *reference = (C_INT32)floor(currValue + 0.5);
    }
  else if (type == CSlider::Float || type == CSlider::UnsignedFloat)
    {
      if (object->isReference() && object->getObjectParent())
        {
          object->getObjectParent()
          ->setValueOfNamedReference(object->getObjectName() , currValue);
        }
      else
        {
          C_FLOAT64* reference = (C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)object)->getReference());

          *reference = currValue;
        }
    }
  this->updateLabel();

  emit valueChanged(currValue);
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
  CCopasiObject* object = this->mpCSlider->getSliderObject();
  double currValue = this->mpCSlider->getSliderValue();
  double value, minValue, maxValue;
  maxValue = this->mpCSlider->getMaxValue();
  minValue = this->mpCSlider->getMinValue();

  if (object->isValueDbl())
    {
      value = *(double*)object->getReference();
    }
  else if (object->isValueInt())
    {
      value = (double)(*(int*)object->getReference());
    }
  if (value != currValue)
    {
      if ((value > maxValue) || (value < minValue))
        {
          if (!modifyRange)
            {
              this->mValueOutOfRange = true;
            }
          else
            {
              this->mValueOutOfRange = false;
              if (value < minValue)
                {
                  this->setMinValue(value / 2.0);
                }
              else
                {
                  this->setMaxValue(value*2.0);
                }
            }
        }
      this->setValue(value);
    }
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
