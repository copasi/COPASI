// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "SliderSettingsDialog.h"

#include <QValidator>

#include <cmath>

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"
#include "CQMessageBox.h"
#include "CQValidator.h"

#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/utilities/CSlider.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

SliderSettingsDialog::SliderSettingsDialog(QWidget* pParent) :
  QDialog(pParent),
  mChanged(),
  mMinorTickSize(),
  mMaxValue(),
  mMinValue(),
  mValue(),
  mLoadedValue(),
  mOriginalValue(),
  mMinorMajorFactor(),
  mNumMinorTicks(),
  mDefinedSliders(),
  mpSlider(NULL),
  mCurrentTaskId(),
  mpModel(NULL),
  mScaling()
{
  setupUi(this);
  this->init();
}

SliderSettingsDialog::~SliderSettingsDialog()
{
}

CSlider* SliderSettingsDialog::getSlider()
{
  return mpSlider;
}

void SliderSettingsDialog::setSlider(CSlider * slider)
{
  size_t i;
  size_t iMax = mDefinedSliders.size();
  bool found = false;

  for (i = 0; i < iMax; ++i)
    {
      if (mDefinedSliders[i] == slider)
        {
          found = true;
          break;
        }
    }

  if (found)
    {
      mpSlider = slider;

      if (slider->getSliderObject())
        {
          mpObjectNameLineEdit->setText(FROM_UTF8(slider->getSliderObject()->getObjectDisplayName()));
        }
      else
        {
          mpObjectNameLineEdit->setText("Object not available!");
        }

      updateInputFields();
      updateInputFieldsValues();
    }
  else
    {
      mpSlider = NULL;
      mpObjectNameLineEdit->setText("NULL");
      mpObjectBrowseButton->show();
      updateInputFields();
    }
}

void SliderSettingsDialog::setDefinedSliders(std::vector<CSlider *> sliderVect)
{
  mDefinedSliders = sliderVect;
}

void SliderSettingsDialog::updateInputFieldsValues()
{
  if (mpSlider)
    {
      mValue = mpSlider->getSliderValue();
      mLoadedValue = mValue;
      mpObjectValueEdit->setText(convertToQString(mValue));

      mOriginalValue = mpSlider->getOriginalValue();
      mpOriginalValueEdit->setText(convertToQString(mOriginalValue));

      mMinValue = mpSlider->getMinValue();
      mpMinValueEdit->setText(convertToQString(mMinValue));

      mMaxValue = mpSlider->getMaxValue();
      mpMaxValueEdit->setText(convertToQString(mMaxValue));

      mNumMinorTicks = mpSlider->getTickNumber();
      mpNumMinorTicksEdit->setText(QString::number(mNumMinorTicks));

      mMinorMajorFactor = mpSlider->getTickFactor();
      mpMinorMajorFactorEdit->setText(QString::number(mMinorMajorFactor));

      numMinorTicksChanged();

      if (mpSlider->getScaling() == CSlider::logarithmic)
        {
          mpLogCheckBox->setChecked(true);
        }
      else
        {
          mpLogCheckBox->setChecked(false);
        }
    }
}

void SliderSettingsDialog::updateInputFields()
{
  // if the current slider is NULL, disable all input fields
  if (mpSlider)
    {
      mpObjectNameLineEdit->setEnabled(false);
      mpMaxValueEdit->setEnabled(true);
      mpMinValueEdit->setEnabled(true);
      mpMinorMajorFactorEdit->setEnabled(true);
      mpMinorTickSizeEdit->setEnabled(true);
      mpNumMinorTicksEdit->setEnabled(true);
      mpObjectValueEdit->setEnabled(true);
      mpLogCheckBox->setEnabled(true);
      mpOriginalValueEdit->setEnabled(true);
    }
  else
    {
      mpObjectNameLineEdit->setEnabled(true);
      mpMaxValueEdit->setEnabled(false);
      mpMinValueEdit->setEnabled(false);
      mpMinorMajorFactorEdit->setEnabled(false);
      mpMinorTickSizeEdit->setEnabled(false);
      mpNumMinorTicksEdit->setEnabled(false);
      mpObjectValueEdit->setEnabled(false);
      mpOriginalValueEdit->setEnabled(false);
      mpLogCheckBox->setEnabled(false);
    }
}

void SliderSettingsDialog::okButtonPressed()
{
  // disconnect all signal receivers from
  // the min and max value edit fields
  // otherwise, they would generate an
  // unnecessary focusLost signal
  disconnect(mpMinValueEdit, 0, 0, 0);
  disconnect(mpMaxValueEdit, 0, 0, 0);
  // only now change underlying slider
  updateSlider();
  // close dialog with positive feedback
  done(QDialog::Accepted);
}

void SliderSettingsDialog::cancelButtonPressed()
{
  // close dialog, drop input
  close();
}

void SliderSettingsDialog::minorTickSizeChanged()
{
  // adjust numMinorTicks
  mMinorTickSize = mpMinorTickSizeEdit->text().toDouble();

  if (mMinorTickSize == 0.0)
    {
      mNumMinorTicks = 1;
    }
  else
    {
      mNumMinorTicks = (unsigned int)floor(((mMaxValue - mMinValue) / mMinorTickSize) + 0.5);
    }

  if (mNumMinorTicks == 0)
    {
      mNumMinorTicks = 1;
      mMinorTickSize = mMaxValue - mMinValue;
      mpMinorTickSizeEdit->setText(convertToQString(mMinorTickSize));
    }

  mpNumMinorTicksEdit->setText(QString::number(mNumMinorTicks));
  mChanged = NONE;
}

void SliderSettingsDialog::numMinorTicksChanged()
{
  // adjust minorTickSize
  mNumMinorTicks = mpNumMinorTicksEdit->text().toUInt();

  if (mNumMinorTicks == 1)
    {
      mNumMinorTicks = 1;
      mpNumMinorTicksEdit->setText(QString::number(mNumMinorTicks));
    }

  mMinorTickSize = (mMaxValue - mMinValue) / mNumMinorTicks;
  mpMinorTickSizeEdit->setText(convertToQString(mMinorTickSize));
  mChanged = NONE;
}

void SliderSettingsDialog::minValueChanged()
{
  // check if it is smaller than the current value
  // if not, set it to the current value
  double value = mpMinValueEdit->text().toDouble();

  if ((value > mOriginalValue) &&
      (CQMessageBox::question(this, "Current value out of range.",
                              "The minimum value you set is larger than the current value of the slider. The current value will be set to the minimum. Do you want to proceed?",
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Ok)
     )
    {
      mpMinValueEdit->setText(convertToQString(mMinValue));
    }
  else
    {
      mOriginalValue = value;
      mpOriginalValueEdit->setText(convertToQString(mOriginalValue));
      mMinValue = value;

      if (mMinValue > mMaxValue)
        {
          mMaxValue = mMinValue;
          mpMaxValueEdit->setText(convertToQString(mMaxValue));
        }

      if (mMinValue > mValue)
        {
          mValue = mMinValue;
          mpObjectValueEdit->setText(convertToQString(mValue));
        }

      mMinorTickSize = (mMaxValue - mMinValue) / mNumMinorTicks;
      mpMinorTickSizeEdit->setText(convertToQString(mMinorTickSize));

      if (mMinValue <= 0.0 && mpLogCheckBox->isChecked())
        {
          //CQMessageBox::information(this, "Incorrect min value",
          //                          "For logarithmic sliders, the minimum value may not be 0.0 or negative. Please set the minimum value to some (possibly very small) positive number first.",
          //                          QMessageBox::Ok, QMessageBox::Ok);
          mpLogCheckBox->setChecked(false);
          mScaling = CSlider::linear;
        }
    }

  mChanged = NONE;
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if it is larger then the current value
  // else set it to the current value
  double value = mpMaxValueEdit->text().toDouble();

  if (value < mOriginalValue)
    {
      if (CQMessageBox::question(this, "Current value out of range.",
                                 "The maximum value you set is smaller than the current value of the slider. The current value will be set to the maximum. Do you want to proceed?",
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Ok)
        {
          mpMaxValueEdit->setText(convertToQString(mMaxValue));
          mChanged = NONE;
          return;
        }

      mOriginalValue = value;
      mpOriginalValueEdit->setText(convertToQString(mOriginalValue));
    }

  mMaxValue = value;

  if (mMinValue > mMaxValue)
    {
      mMinValue = mMaxValue;
      mpMinValueEdit->setText(convertToQString(mMinValue));
    }

  if (mMaxValue < mValue)
    {
      mValue = mMaxValue;
      mpObjectValueEdit->setText(convertToQString(mValue));
    }

  mMinorTickSize = (mMaxValue - mMinValue) / mNumMinorTicks;
  mpMinorTickSizeEdit->setText(convertToQString(mMinorTickSize));
  mChanged = NONE;
}

void SliderSettingsDialog::objectValueChanged()
{
  // check if the value is within range, else set a new range
  // get the value and set it in the current slider
  mValue = mpObjectValueEdit->text().toDouble();

  if (mValue > mMaxValue)
    {
      mMaxValue = mValue;
      mpMaxValueEdit->setText(convertToQString(mMaxValue));
    }

  if (mValue < mMinValue)
    {
      mMinValue = mValue;
      mpMinValueEdit->setText(convertToQString(mMinValue));
    }

  mChanged = NONE;
}

void SliderSettingsDialog::minorMajorFactorChanged()
{
  // get the value and set it in the current slider
  mMinorMajorFactor = mpMinorMajorFactorEdit->text().toUInt();
  mChanged = NONE;
}

void SliderSettingsDialog::init()
{
  mpSlider = NULL;
  mChanged = NONE;
  mScaling = CSlider::linear;
  mpObjectBrowseButton->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpExtendedOptionsButton->setText("Advanced >>");
  hideOptionsControls();
  this->setFixedSize(minimumSizeHint());

  mpObjectValueEdit->setValidator(new CQValidatorDouble(mpObjectValueEdit));
  mpOriginalValueEdit->setValidator(new CQValidatorDouble(mpOriginalValueEdit));
  mpMinValueEdit->setValidator(new CQValidatorDouble(mpMinValueEdit));
  mpMaxValueEdit->setValidator(new CQValidatorDouble(mpMaxValueEdit));
  mpMinorTickSizeEdit->setValidator(new CQValidatorDouble(mpMinorTickSizeEdit));

  CQValidatorInt * pValidator = new CQValidatorInt(mpNumMinorTicksEdit);
  pValidator->setRange(0, std::numeric_limits< int >::max());
  mpNumMinorTicksEdit->setValidator(pValidator);

  pValidator = new CQValidatorInt(mpMinorMajorFactorEdit);
  pValidator->setRange(0, std::numeric_limits< int >::max());
  mpMinorMajorFactorEdit->setValidator(pValidator);

  updateInputFields();
}

void SliderSettingsDialog::browseButtonPressed()
{
  const CDataObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this,
        CQSimpleSelectionTree::InitialTime |
        CQSimpleSelectionTree::Parameters);

  if (pObject)
    {
      if (!pObject->hasFlag(CDataObject::ValueDbl) && !pObject->hasFlag(CDataObject::ValueInt))
        {
          CQMessageBox::information(this, "Invalid Object",
                                    "You chose an object that does not correspond to an integer or float value. Please choose an object that corresponds to an integet or float value.",
                                    QMessageBox::Ok, QMessageBox::Ok);
          mpSlider = NULL;
          mpObjectNameLineEdit->setText("");
          return;
        }

      /* Determine the associated entity key */
      CDataContainer * pAncestor = pObject->getObjectAncestor("Task");

      if (!pAncestor) pAncestor = pObject->getObjectAncestor("Model");

      if (!pAncestor)
        {
          CQMessageBox::information(this, "Invalid Object",
                                    "You chose an object that cannot be used as a slider. Please choose an other object.",
                                    QMessageBox::Ok, QMessageBox::Ok);
          mpSlider = NULL;
          mpObjectNameLineEdit->setText("");
          return;
        }

      // We do not have a slider therefore we create one.
      if (mpSlider == NULL)
        {
          // temporarily add the slider the the first datamodel
          mpSlider = new CSlider("slider", pObject->getObjectDataModel());
          mpSlider->setSliderObject(const_cast< CDataObject * >(pObject));

          if (pAncestor)
            mpSlider->setAssociatedEntityKey(pAncestor->getKey());

          mpSlider->resetRange();
          updateInputFields();
          updateInputFieldsValues();

          mpObjectNameLineEdit->setText(FROM_UTF8(mpSlider->getSliderObject()->getObjectDisplayName()));
          return;
        }

      // If the object of an existing slider has not changed we have nothing to do
      if (mpSlider->getSliderObject() == pObject)
        return;

      // Check whether a slider with the object already exists
      size_t i, iMax = mDefinedSliders.size();

      for (i = 0; i < iMax; ++i)
        if (mDefinedSliders[i]->getSliderObject() == pObject)
          break;

      // A slider with the new object exists we switch to it.
      if (i != iMax)
        setSlider(mDefinedSliders[i]);
      else // We need to change the object an reinitialize the slider
        {
          mpSlider->setSliderObject(const_cast< CDataObject * >(pObject));

          if (pAncestor)
            mpSlider->setAssociatedEntityKey(pAncestor->getKey());

          mpSlider->resetRange();
          updateInputFields();
          updateInputFieldsValues();
        }

      mpObjectNameLineEdit->setText(FROM_UTF8(mpSlider->getSliderObject()->getObjectDisplayName()));
    }
}

void SliderSettingsDialog::setModel(CModel * model)
{
  mpModel = model;
}

void SliderSettingsDialog::disableObjectChoosing(bool disableChoosing)
{
  mpObjectBrowseButton->setHidden(disableChoosing);
}

void SliderSettingsDialog::updateSlider()
{
  updateInternalValues();

  if (mpSlider)
    {
      if (mMinValue < mpSlider->getMaxValue())
        {
          mpSlider->setMinValue(mMinValue);
          mpSlider->setMaxValue(mMaxValue);
        }
      else
        {
          mpSlider->setMaxValue(mMaxValue);
          mpSlider->setMinValue(mMinValue);
        }

      mpSlider->setSliderValue(mValue);
      mpSlider->setTickNumber(mNumMinorTicks);
      mpSlider->setTickFactor(mMinorMajorFactor);
      mpSlider->setScaling((CSlider::Scale)mScaling);
      mpSlider->setOriginalValue(mOriginalValue);
    }
}

bool SliderSettingsDialog::needRun()
{
  return mValue != mLoadedValue;
}

void SliderSettingsDialog::extendedOptionsClicked()
{
  if (mpExtendedOptionsButton->text() == "Advanced >>")
    {
      mpExtendedOptionsButton->setText("Advanced <<");
      showOptionsControls();
      this->setFixedSize(minimumSizeHint());
    }
  else
    {
      mpExtendedOptionsButton->setText("Advanced >>");
      hideOptionsControls();
      int heightChange = mpOptionsGridLayout->geometry().height();
      QSize size = this->size() - QSize(0, heightChange);
      this->setFixedSize(size);
    }
}

void SliderSettingsDialog::logCheckBoxToggled(bool on)
{
  updateInternalValues();
  mChanged = LOGARITHMIC;

  if (on)
    {
      // check if the minValue is 0.0 or negative if so, issue an error message and uncheck the checkbox again
      if (mMinValue <= 0.0)
        {
          //CQMessageBox::information(this, "Incorrect min value",
          //                          "For logarithmic sliders, the minimum value may not be 0.0 or negative. Please set the minimum value to some (possibly very small) positive number first.",
          //                          QMessageBox::Ok, QMessageBox::Ok);
          mpLogCheckBox->setChecked(false);
          mScaling = CSlider::linear;
        }
      else
        {
          mScaling = CSlider::logarithmic;
        }
    }
  else
    {
      mScaling = CSlider::linear;
    }
}

void SliderSettingsDialog::globalCheckBoxToggled()
{
  updateInternalValues();
}

void SliderSettingsDialog::updateInternalValues()
{
  switch (mChanged)
    {
      case VALUE:
        objectValueChanged();
        break;

      case ORIGVAL:
        originalValueChanged();
        break;

      case MIN:
        minValueChanged();
        break;

      case MAX:
        maxValueChanged();
        break;

      case TICKFACTOR:
        minorMajorFactorChanged();
        break;

      case TICKSIZE:
        minorTickSizeChanged();
        break;

      case NUMTICKS:
        numMinorTicksChanged();
        break;

      default:
        break;
    }
}

void SliderSettingsDialog::originalValueChanged()
{
  // check if the value is within range, else set it to
  // set new values for the range
  mOriginalValue = mpOriginalValueEdit->text().toDouble();

  if (mOriginalValue > mMaxValue)
    {
      mMaxValue = mOriginalValue;
      mpMaxValueEdit->setText(convertToQString(mMaxValue));
    }

  if (mOriginalValue < mMinValue)
    {
      mMinValue = mOriginalValue;
      mpMinValueEdit->setText(convertToQString(mMinValue));
    }

  mChanged = NONE;
}

void SliderSettingsDialog::minValueTextChanged()
{
  mChanged = MIN;
}

void SliderSettingsDialog::maxValueTextChanged()
{
  mChanged = MAX;
}

void SliderSettingsDialog::numTicksTextChanged()
{
  mChanged = NUMTICKS;
}

void SliderSettingsDialog::tickSizeTextChanged()
{
  mChanged = TICKSIZE;
}

void SliderSettingsDialog::tickFactorTextChanged()
{
  mChanged = TICKFACTOR;
}

void SliderSettingsDialog::origValueTextChanged()
{
  mChanged = ORIGVAL;
}

void SliderSettingsDialog::valueTextChanged()
{
  mChanged = VALUE;
}

void SliderSettingsDialog::showOptionsControls()
{
  mpNumMinorTicksLabel->show();
  mpNumMinorTicksEdit->show();
  mpMinorTickSizeLabel->show();
  mpMinorTickSizeEdit->show();

  mpMinorMajorFactorLabel->show();
  mpMinorMajorFactorEdit->show();
  mpOriginalValueLabel->show();
  mpOriginalValueEdit->show();

  mpObjectValueLabel->show();
  mpObjectValueEdit->show();
}

void SliderSettingsDialog::hideOptionsControls()
{
  mpNumMinorTicksLabel->hide();
  mpNumMinorTicksEdit->hide();
  mpMinorTickSizeLabel->hide();
  mpMinorTickSizeEdit->hide();

  mpMinorMajorFactorLabel->hide();
  mpMinorMajorFactorEdit->hide();
  mpOriginalValueLabel->hide();
  mpOriginalValueEdit->hide();

  mpObjectValueLabel->hide();
  mpObjectValueEdit->hide();
}
