/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiSlider.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/11/08 16:46:19 $
   End CVS Header */

#include <cmath>

#include "qlabel.h"
#include "qstring.h"
#include "qslider.h"

#include "CopasiSlider.h"
#include "qtUtilities.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiObjectReference.h"

CopasiSlider::CopasiSlider(CCopasiObject* object, QWidget* parent): QVBox(parent), mpObject(object), mTypeVar(undefined), mMinValue(0.0), mMaxValue(0.0), mNumMinorTicks(100), mMinorMajorFactor(10), mpSlider(NULL), mpLabel(NULL)
{
  this->mpLabel = new QLabel(this);
  this->mpLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  this->mpSlider = new QSlider(Qt::Horizontal, this);
  this->mpSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  this->updateSliderData();

  connect(this->mpSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
}

CopasiSlider::~CopasiSlider()
{
  delete this->mpSlider;
  delete this->mpLabel;
}

void CopasiSlider::updateSliderData()
{
  if (this->mpObject)
    {
      this->mValue = 0.0;
      if (this->mpObject->isValueDbl())
        {
          this->mValue = *(double*)(((CCopasiObjectReference<C_FLOAT64>*)this->mpObject)->getReference());
        }
      else if (this->mpObject->isValueInt())
        {
          //value = *(int*)this->mpObject->getReference();
          this->mValue = *(int*)(((CCopasiObjectReference<C_INT32>*)this->mpObject)->getReference());
        }
      this->mMinValue = 0.0;
      this->mMaxValue = 2.0 * this->mValue;
      this->mpSlider->setMinValue(0);
      this->mpSlider->setMaxValue(this->mNumMinorTicks);
      this->mpSlider->setTickInterval(1);
      this->mpSlider->setLineStep(1);
      this->mpSlider->setPageStep(this->mMinorMajorFactor);
      this->mTickInterval = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;
      this->mpSlider->setValue((int)floor(((this->mValue - this->mMinValue) / this->mTickInterval) + 0.5));
      if (this->mpObject->isValueInt())
        {
          this->setType(intType);
          //QToolTip::add(this->mpSlider, "Int Tooltip");
        }
      else if (this->mpObject->isValueDbl())
        {
          this->setType(doubleType);
          //QToolTip::add(this->mpSlider, "Double Tooltip");
        }
      else
        {
          this->setEnabled(false);
        }
    }
  this->updateLabel();
}

double CopasiSlider::value() const
  {
    return this->mValue;
  }

void CopasiSlider::setValue(double value)
{
  if (value < this->mMinValue)
    {
      value = this->mMinValue;
    }
  else if (value > this->mMaxValue)
    {
      value = this->mMaxValue;
    }
  this->mValue = value;
  this->mpSlider->setValue((int)floor(((this->mValue - this->mMinValue) / this->mTickInterval) + 0.5));
  if (this->mTypeVar == intType)
    {
      int* reference = (int*)(((CCopasiObjectReference<C_INT32>*)this->mpObject)->getReference());

      *reference = (int)floor(this->mValue + 0.5);
    }
  else if (this->mTypeVar == doubleType)
    {
      double* reference = (double*)(((CCopasiObjectReference<C_FLOAT64>*)this->mpObject)->getReference());

      *reference = this->mValue;
    }
  this->updateLabel();
}

unsigned int CopasiSlider::minorMajorFactor() const
  {
    return this->mMinorMajorFactor;
  }

void CopasiSlider::setMinorMajorFactor(unsigned int factor)
{
  this->mMinorMajorFactor = factor;
  this->mpSlider->setPageStep(this->mpSlider->lineStep()*this->mMinorMajorFactor);
}

double CopasiSlider::minorTickInterval() const
  {
    return (this->mMaxValue - this->mMinValue) / ((double)this->mNumMinorTicks);
  }

void CopasiSlider::setNumMinorTicks(unsigned int numMinorTicks)
{
  this->mNumMinorTicks = numMinorTicks;
  // set maxValue and value of slider
  this->mpSlider->setMaxValue(numMinorTicks);
  this->mpSlider->setValue((int)floor(((this->mValue - this->mMinValue) / this->mTickInterval) + 0.5));
}

unsigned int CopasiSlider::numMinorTicks() const
  {
    return this->mNumMinorTicks;
  }

double CopasiSlider::minValue() const
  {
    return this->mMinValue;
  }

double CopasiSlider::maxValue() const
  {
    return this->mMaxValue;
  }

CCopasiObject* CopasiSlider::object() const
  {
    return this->mpObject;
  }

void CopasiSlider::setObject(CCopasiObject* object)
{
  this->mpObject = object;
  this->updateSliderData();
}

void CopasiSlider::setMaxValue(double value)
{
  if (value <= mMinValue) return;

  this->mMaxValue = value;

  this->mTickInterval = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;

  if (this->value() > this->mMaxValue)
    {
      this->setValue(this->mMaxValue);
    }

  this->mpSlider->setValue((int)floor(((this->mValue - this->mMinValue) / this->mTickInterval) + 0.5));

  this->updateLabel();
}

void CopasiSlider::setMinValue(double value)
{
  if (value >= mMaxValue) return;

  this->mMinValue = value;

  this->mTickInterval = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;

  if (this->value() < this->mMinValue)
    {
      this->setValue(this->mMinValue);
    }

  this->mpSlider->setValue((int)floor(((this->mValue - this->mMinValue) / this->mTickInterval) + 0.5));

  this->updateLabel();
}

void CopasiSlider::updateLabel()
{
  QString labelString = "";
  if (this->mpObject)
    {
      labelString += FROM_UTF8(this->mpObject->getObjectName());
    }
  labelString += " : [";
  labelString += QString::number(this->mMinValue);
  labelString += "-";
  labelString += QString::number(this->mMaxValue);
  labelString += "] {";
  labelString += QString::number(this->value());
  labelString += "}";
  this->mpLabel->setText(labelString);
}

void CopasiSlider::sliderValueChanged(int value)
{
  this->mValue = this->mMinValue + value * this->mTickInterval;
  if (this->mTypeVar == intType)
    {
      int* reference = (int*)(((CCopasiObjectReference<C_INT32>*)this->mpObject)->getReference());

      *reference = (int)floor(this->mValue + 0.5);
    }
  else if (this->mTypeVar == doubleType)
    {
      double* reference = (double*)(((CCopasiObjectReference<C_FLOAT64>*)this->mpObject)->getReference());

      *reference = this->mValue;
    }
  this->updateLabel();

  emit valueChanged(this->mValue);
}

CopasiSlider::NumberType CopasiSlider::type() const
  {
    return this->mTypeVar;
  }

void CopasiSlider::setType(NumberType type)
{
  this->mTypeVar = type;
}
