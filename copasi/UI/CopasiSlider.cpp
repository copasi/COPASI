// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>

#include <QtGui/QLabel>
#include <QtCore/QString>
#include <QtGui/QSlider>
#include <QtGui/QPixmap>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QToolTip>

#include "copasi.h"

#include "CopasiSlider.h"
#include "listviews.h"
#include "qtUtilities.h"
#include "DataModelGUI.h"
#include "resourcesUI/CQIconResource.h"

CopasiSlider::CopasiSlider(CSlider* pSlider, DataModelGUI * pDM, QWidget* parent):
  QFrame(parent),
  mpCSlider(pSlider),
  mpQSlider(NULL),
  mpLabel(NULL),
  mpCloseButton(NULL),
  mpEditButton(NULL),
  mValueOutOfRange(false),
  mpDM(pDM)
{
  this->setLayout(new QHBoxLayout);
  this->setFrameShape(QFrame::Box);
  this->layout()->setContentsMargins(2, 2, 2, 2);
  //this->layout()->setSpacing(0);
  //this->layout()->setMargin(0);
  QFrame* pFrame = new QFrame(NULL);
  pFrame->setLayout(new QVBoxLayout);
  pFrame->layout()->setContentsMargins(2, 2, 2, 2);
  this->mpLabel = new QLabel(NULL);
  this->mpLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  pFrame->layout()->addWidget(this->mpLabel);
  this->mpQSlider = new QSlider(Qt::Horizontal);
  mpQSlider->setFocusPolicy(Qt::WheelFocus);
  this->mpQSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
#ifdef WIN32
  this->mpQSlider->setMinimumHeight(10);
#endif
  pFrame->layout()->addWidget(this->mpQSlider);
  this->layout()->addWidget(pFrame);

  pFrame = new QFrame(NULL);
  pFrame->setLayout(new QVBoxLayout);
  pFrame->layout()->setContentsMargins(2, 2, 2, 2);

  this->mpCloseButton = new QToolButton(NULL);
  this->mpCloseButton->setIcon(CQIconResource::icon(CQIconResource::editDelete));
  pFrame->layout()->addWidget(this->mpCloseButton);

  this->mpEditButton = new QToolButton(NULL);
  this->mpEditButton->setIcon(CQIconResource::icon(CQIconResource::edit));
  pFrame->layout()->addWidget(this->mpEditButton);

  this->layout()->addWidget(pFrame);

  if (!this->mpCSlider->compile())
    {
      this->mpQSlider->setEnabled(false);
    }

  this->updateSliderData();
  this->mpCloseButton->setToolTip(tr("remove slider"));
  this->mpEditButton->setToolTip(tr("edit slider"));

  connect(this->mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
  connect(this->mpQSlider, SIGNAL(sliderReleased()), this, SLOT(qSliderReleased()));
  connect(this->mpQSlider, SIGNAL(sliderPressed()), this, SLOT(qSliderPressed()));
  connect(this->mpCloseButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
  connect(this->mpEditButton, SIGNAL(clicked()), this, SLOT(editButtonClicked()));

  // We need to assure that the slider is compiled
  if (mpCSlider) mpCSlider->compile();
}

CopasiSlider::~CopasiSlider()
{}

void CopasiSlider::focusSlider()
{
  if (mpQSlider == NULL) return;

  mpQSlider->setFocus(Qt::OtherFocusReason);
}

void CopasiSlider::updateSliderData()
{
  if (this->mpCSlider)
    {
      //mpCSlider->compile();
      this->mpQSlider->setMinimum(0);
      this->mpQSlider->setMaximum(this->mpCSlider->getTickNumber());
      this->mpQSlider->setTickInterval(1);
      this->mpQSlider->setSingleStep(1);
      this->mpQSlider->setPageStep(this->mpCSlider->getTickFactor());
      disconnect(this->mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
      this->mpQSlider->setValue(this->calculatePositionFromValue(this->mpCSlider->getSliderValue()));
      connect(this->mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
      this->updateLabel();

      if (this->mpQSlider->isEnabled() == false)
        {
          if (this->mpCSlider->getSliderObject() != NULL)
            {
              this->mpQSlider->setEnabled(true);
            }
        }

      this->update();
    }
}

C_FLOAT64 CopasiSlider::value() const
{
  return this->mpCSlider->getSliderValue();
}

void CopasiSlider::setValue(C_FLOAT64 value)
{

  // we set the value ourselves so that listviews can do the
  // update of the dependent values as well as taking the framework into
  // consideration

  // first we set the slider value without actually writing to the underlying object
  this->mpCSlider->setSliderValue(value, false);
  /* reget value in case it was outside range and got set to minValue or
   * maxValue */
  value = this->mpCSlider->getSliderValue();

  // now we handle writing to the object ourselves
  CCopasiObject* pObject = this->object();

  if (pObject == NULL) return;

  if (pObject->isValueDbl())
    pObject->setObjectValue(value);
  else if (pObject->isValueInt())
    pObject->setObjectValue((C_INT32) floor(value + 0.5));
  else if (pObject->isValueBool())
    pObject->setObjectValue(value != 0.0);

  // recalculate all other dependent values
  mpDM->refreshInitialValues();

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
  this->mpQSlider->setPageStep(this->mpQSlider->singleStep()*factor);
}

C_FLOAT64 CopasiSlider::minorTickInterval() const
{
  return (C_FLOAT64)(this->mpCSlider->getMaxValue() - this->mpCSlider->getMinValue()) / ((C_FLOAT64)this->mpCSlider->getTickNumber());
}

void CopasiSlider::setNumMinorTicks(unsigned C_INT32 numMinorTicks)
{
  this->mpCSlider->setTickNumber(numMinorTicks);
  // set maxValue and value of slider
  this->mpQSlider->setMaximum(numMinorTicks);
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
    }
  else
    {
      labelString += "Object not available!";
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

void CopasiSlider::updateValue(bool modifyRange, bool updateDependencies)
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

  // now we handle writing to the object ourselves
  CCopasiObject* pObject = this->object();

  if (pObject == NULL) return;

  if (pObject->isValueDbl())
    pObject->setObjectValue(value);
  else if (pObject->isValueInt())
    pObject->setObjectValue((C_INT32) floor(value + 0.5));
  else if (pObject->isValueBool())
    pObject->setObjectValue(value != 0.0);

  // recalculate all other dependent values
  if (updateDependencies)
    {
      mpDM->refreshInitialValues();
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
        exponent = (((double)position) * log10(this->mpCSlider->getMaxValue() / this->mpCSlider->getMinValue())) / this->mpCSlider->getTickNumber();
        value = this->mpCSlider->getMinValue() * pow(10.0, exponent);
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
        position = (int)floor(((value - this->mpCSlider->getMinValue()) / this->minorTickInterval()) + 0.5);
        break;

      case CSlider::logarithmic:
        position = (int)floor((this->mpCSlider->getTickNumber() * (log10(value / this->mpCSlider->getMinValue()) / log10(this->mpCSlider->getMaxValue() / this->mpCSlider->getMinValue()))) + 0.5);
        break;

      default:
        position = 0;
    }

  return position;
}

void CopasiSlider::resetValue()
{
  this->setValue(this->originalValue());
}

C_FLOAT64 CopasiSlider::originalValue() const
{
  return this->mpCSlider->getOriginalValue();
}

void CopasiSlider::setOriginalValue(C_FLOAT64 value)
{
  this->mpCSlider->setOriginalValue(value);
}
/**
 * Checks whether the slider is actually valid.
 * This is mainly done by calling isValid on the underlying CSlider object.
 */
bool CopasiSlider::isValid() const
{
  return (this->mpCSlider != NULL && this->mpCSlider->isValid());
}
