// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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
  setLayout(new QHBoxLayout);
  setFrameShape(QFrame::Box);
  layout()->setContentsMargins(2, 2, 2, 2);
  //layout()->setSpacing(0);
  //layout()->setMargin(0);
  QFrame* pFrame = new QFrame(NULL);
  pFrame->setLayout(new QVBoxLayout);
  pFrame->layout()->setContentsMargins(2, 2, 2, 2);
  mpLabel = new QLabel(NULL);
  mpLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  pFrame->layout()->addWidget(mpLabel);
  mpQSlider = new QSlider(Qt::Horizontal);
  mpQSlider->setFocusPolicy(Qt::WheelFocus);
  mpQSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
#ifdef WIN32
  mpQSlider->setMinimumHeight(10);
#endif
  pFrame->layout()->addWidget(mpQSlider);
  layout()->addWidget(pFrame);

  pFrame = new QFrame(NULL);
  pFrame->setLayout(new QVBoxLayout);
  pFrame->layout()->setContentsMargins(2, 2, 2, 2);

  mpCloseButton = new QToolButton(NULL);
  mpCloseButton->setIcon(CQIconResource::icon(CQIconResource::editDelete));
  pFrame->layout()->addWidget(mpCloseButton);

  mpEditButton = new QToolButton(NULL);
  mpEditButton->setIcon(CQIconResource::icon(CQIconResource::edit));
  pFrame->layout()->addWidget(mpEditButton);

  layout()->addWidget(pFrame);

  if (!mpCSlider->compile())
    {
      mpQSlider->setEnabled(false);
    }

  updateSliderData();
  mpCloseButton->setToolTip(tr("Remove Slider"));
  mpEditButton->setToolTip(tr("Edit Slider"));

  connect(mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
  connect(mpQSlider, SIGNAL(sliderReleased()), this, SLOT(qSliderReleased()));
  connect(mpQSlider, SIGNAL(sliderPressed()), this, SLOT(qSliderPressed()));
  connect(mpCloseButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
  connect(mpEditButton, SIGNAL(clicked()), this, SLOT(editButtonClicked()));

  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

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
  if (mpCSlider)
    {
      //mpCSlider->compile();
      mpQSlider->setMinimum(0);
      mpQSlider->setMaximum(mpCSlider->getTickNumber());
      mpQSlider->setTickInterval(1);
      mpQSlider->setSingleStep(1);
      mpQSlider->setPageStep(mpCSlider->getTickFactor());
      disconnect(mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
      mpQSlider->setValue(calculatePositionFromValue(mpCSlider->getSliderValue()));
      connect(mpQSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
      updateLabel();

      if (mpQSlider->isEnabled() == false)
        {
          if (mpCSlider->getSliderObject() != NULL)
            {
              mpQSlider->setEnabled(true);
            }
        }

      update();
    }
}

C_FLOAT64 CopasiSlider::value() const
{
  return mpCSlider->getSliderValue();
}

void CopasiSlider::setValue(C_FLOAT64 value)
{

  // we set the value ourselves so that listviews can do the
  // update of the dependent values as well as taking the framework into
  // consideration

  // first we set the slider value without actually writing to the underlying object
  mpCSlider->setSliderValue(value, false);
  /* reget value in case it was outside range and got set to minValue or
   * maxValue */
  value = mpCSlider->getSliderValue();

  // now we handle writing to the object ourselves
  CCopasiObject * pObject = const_cast< CCopasiObject * >(object());

  if (pObject == NULL) return;

  if (pObject->isValueDbl())
    pObject->setObjectValue(value);
  else if (pObject->isValueInt())
    pObject->setObjectValue((C_INT32) floor(value + 0.5));
  else if (pObject->isValueBool())
    pObject->setObjectValue(value != 0.0);

  // recalculate all other dependent values
  mpDM->refreshInitialValues();

  mpQSlider->setValue(calculatePositionFromValue(value));

  updateLabel();
}

unsigned C_INT32 CopasiSlider::minorMajorFactor() const
{
  return mpCSlider->getTickFactor();
}

void CopasiSlider::setMinorMajorFactor(unsigned C_INT32 factor)
{
  mpCSlider->setTickFactor(factor);
  mpQSlider->setPageStep(mpQSlider->singleStep()*factor);
}

C_FLOAT64 CopasiSlider::minorTickInterval() const
{
  return (C_FLOAT64)(mpCSlider->getMaxValue() - mpCSlider->getMinValue()) / ((C_FLOAT64)mpCSlider->getTickNumber());
}

void CopasiSlider::setNumMinorTicks(unsigned C_INT32 numMinorTicks)
{
  mpCSlider->setTickNumber(numMinorTicks);
  // set maxValue and value of slider
  mpQSlider->setMaximum(numMinorTicks);
  mpQSlider->setValue(calculatePositionFromValue(mpCSlider->getSliderValue()));
}

unsigned C_INT32 CopasiSlider::numMinorTicks() const
{
  return mpCSlider->getTickNumber();
}

C_FLOAT64 CopasiSlider::minValue() const
{
  return mpCSlider->getMinValue();
}

C_FLOAT64 CopasiSlider::maxValue() const
{
  return mpCSlider->getMaxValue();
}

const CCopasiObject* CopasiSlider::object() const
{
  return mpCSlider->getSliderObject();
}

void CopasiSlider::setObject(const CCopasiObject * object)
{
  mpCSlider->setSliderObject(object);
  updateSliderData();
}

void CopasiSlider::setMaxValue(C_FLOAT64 value)
{
  mpCSlider->setMaxValue(value);

  mpQSlider->setValue(calculatePositionFromValue(mpCSlider->getSliderValue()));

  updateLabel();
}

void CopasiSlider::setMinValue(C_FLOAT64 value)
{
  mpCSlider->setMinValue(value);

  mpQSlider->setValue(calculatePositionFromValue(mpCSlider->getSliderValue()));

  updateLabel();
}

void CopasiSlider::updateLabel()
{
  double minValue, maxValue, currValue;
  minValue = mpCSlider->getMinValue();
  maxValue = mpCSlider->getMaxValue();
  currValue = mpCSlider->getSliderValue();
  const CCopasiObject* object = mpCSlider->getSliderObject();
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

      if (mValueOutOfRange)
        {
          labelString += " (Value out of range!)";
        }
    }
  else
    {
      labelString += "Object not available!";
    }

  mpLabel->setText(labelString);
}

void CopasiSlider::sliderValueChanged(int value)
{
  mpCSlider->setSliderValue(calculateValueFromPosition(value), false);

  updateLabel();

  emit valueChanged(mpCSlider->getSliderValue());
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
  return mpCSlider->getSliderType();
}

void CopasiSlider::setType(CSlider::Type type)
{
  mpCSlider->setSliderType(type);
}

void CopasiSlider::updateValue(bool modifyRange, bool updateDependencies)
{
  double value = mpCSlider->getSliderValue();
  double maxValue = mpCSlider->getMaxValue();
  double minValue = mpCSlider->getMinValue();

  if ((value > maxValue) || (value < minValue))
    {
      if (!modifyRange)
        {
          mValueOutOfRange = true;
        }
      else
        {
          mValueOutOfRange = false;
          mpCSlider->resetRange();
        }
    }

  // now we handle writing to the object ourselves
  CCopasiObject* pObject = const_cast< CCopasiObject * >(object());

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
  return mpCSlider;
}

C_FLOAT64 CopasiSlider::calculateValueFromPosition(int position)
{
  double value;
  double exponent;

  switch (mpCSlider->getScaling())
    {
      case CSlider::linear:
        value = mpCSlider->getMinValue() + position * minorTickInterval();
        break;

      case CSlider::logarithmic:
        exponent = (((double)position) * log10(mpCSlider->getMaxValue() / mpCSlider->getMinValue())) / mpCSlider->getTickNumber();
        value = mpCSlider->getMinValue() * pow(10.0, exponent);
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

  switch (mpCSlider->getScaling())
    {
      case CSlider::linear:
        position = (int)floor(((value - mpCSlider->getMinValue()) / minorTickInterval()) + 0.5);
        break;

      case CSlider::logarithmic:
        position = (int)floor((mpCSlider->getTickNumber() * (log10(value / mpCSlider->getMinValue()) / log10(mpCSlider->getMaxValue() / mpCSlider->getMinValue()))) + 0.5);
        break;

      default:
        position = 0;
    }

  return position;
}

void CopasiSlider::resetValue()
{
  setValue(originalValue());
}

C_FLOAT64 CopasiSlider::originalValue() const
{
  return mpCSlider->getOriginalValue();
}

void CopasiSlider::setOriginalValue(C_FLOAT64 value)
{
  mpCSlider->setOriginalValue(value);
}
/**
 * Checks whether the slider is actually valid.
 * This is mainly done by calling isValid on the underlying CSlider object.
 */
bool CopasiSlider::isValid() const
{
  return (mpCSlider != NULL && mpCSlider->isValid());
}
