// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/SliderSettingsDialog.ui.h,v $
//   $Revision: 1.29.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/04/30 15:08:52 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include <qvalidator.h>

#include <math.h>

#include "copasi.h"

#include "UI/qtUtilities.h"
#include "UI/CCopasiSelectionDialog.h"
#include "UI/CQMessageBox.h"

#include "utilities/CSlider.h"

CSlider* SliderSettingsDialog::getSlider()
{
  return mpSlider;
}

void SliderSettingsDialog::setSlider(CSlider * slider)
{
  unsigned int i;
  unsigned int iMax = mDefinedSliders.size();
  bool found = false;
  for (i = 0; i < iMax;++i)
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
          mpObjectNameLineEdit->setText("Object not avalable!");
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
      mpObjectValueEdit->setText(QString::number(mValue));

      mOriginalValue = mpSlider->getOriginalValue();
      mpOriginalValueEdit->setText(QString::number(mOriginalValue));

      mMinValue = mpSlider->getMinValue();
      mpMinValueEdit->setText(QString::number(mMinValue));

      mMaxValue = mpSlider->getMaxValue();
      mpMaxValueEdit->setText(QString::number(mMaxValue));

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
  // uneccesary focusLost signal
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
      mpMinorTickSizeEdit->setText(QString::number(mMinorTickSize));
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
  mpMinorTickSizeEdit->setText(QString::number(mMinorTickSize));
  mChanged = NONE;
}

void SliderSettingsDialog::minValueChanged()
{
  // check if it is smaller than the current value
  // if not, set it to the current value
  double value = mpMinValueEdit->text().toDouble();
  if ((value > mOriginalValue) &&
      (CQMessageBox::question(this, "Default value out of range.",
                              "The minimum value you set is larger than the default value of the slider. The new default will be set to the minimum. Do you want to procceed?",
                              QMessageBox::Yes, QMessageBox::No | QMessageBox::Default | QMessageBox::Escape) != 0)
)
    {
      mpMinValueEdit->setText(QString::number(mMinValue));
    }
  else
    {
      mOriginalValue = value;
      mpOriginalValueEdit->setText(QString::number(mOriginalValue));
      mMinValue = value;
      if (mMinValue > mMaxValue)
        {
          mMaxValue = mMinValue;
          mpMaxValueEdit->setText(QString::number(mMaxValue));
        }
      if (mMinValue > mValue)
        {
          mValue = mMinValue;
          mpObjectValueEdit->setText(QString::number(mValue));
        }
      mMinorTickSize = (mMaxValue - mMinValue) / mNumMinorTicks;
      mpMinorTickSizeEdit->setText(QString::number(mMinorTickSize));
      if (mMinValue <= 0.0 && mpLogCheckBox->isChecked())
        {
          CQMessageBox::information(this, "Incorrect min value",
                                    "For logarithmic sliders, the minimum value may not be 0.0 or negative. Please set the minimum value to some (possibly very small) positive number first.",
                                    QMessageBox::Ok | QMessageBox::Default , QMessageBox::NoButton);
          mpLogCheckBox->setChecked(false);
          mScaling = CSlider::linear;
        }
    }
  mChanged = NONE;
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if it is larget then the current value
  // else set it to the current value
  double value = mpMaxValueEdit->text().toDouble();
  if (value < mOriginalValue)
    {
      if (CQMessageBox::question(this, "Default value out of range.",
                                 "The maximum value you set is smaller than the default value of the slider. The new default will be set to the maximum. Do you want to procceed?",
                                 QMessageBox::Yes, QMessageBox::No | QMessageBox::Default | QMessageBox::Escape) != 0)
        {
          mpMaxValueEdit->setText(QString::number(mMaxValue));
          mChanged = NONE;
          return;
        }
      mOriginalValue = value;
      mpOriginalValueEdit->setText(QString::number(mOriginalValue));
    }
  mMaxValue = value;
  if (mMinValue > mMaxValue)
    {
      mMinValue = mMaxValue;
      mpMinValueEdit->setText(QString::number(mMinValue));
    }
  if (mMaxValue < mValue)
    {
      mValue = mMaxValue;
      mpObjectValueEdit->setText(QString::number(mValue));
    }
  mMinorTickSize = (mMaxValue - mMinValue) / mNumMinorTicks;
  mpMinorTickSizeEdit->setText(QString::number(mMinorTickSize));
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
      mpMaxValueEdit->setText(QString::number(mMaxValue));
    }
  if (mValue < mMinValue)
    {
      mMinValue = mValue;
      mpMinValueEdit->setText(QString::number(mMinValue));
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
  mpExtendedOptionsButton->setText("Advanced >>");
  mpExtendedOptionsFrame->hide();
  mpObjectValueEdit->setValidator(new QDoubleValidator(this));
  mpOriginalValueEdit->setValidator(new QDoubleValidator(this));
  mpMinValueEdit->setValidator(new QDoubleValidator(this));
  mpMaxValueEdit->setValidator(new QDoubleValidator(this));
  mpMinorTickSizeEdit->setValidator(new QDoubleValidator(this));
  QIntValidator* v = new QIntValidator(this);
  v->setBottom(0);
  mpNumMinorTicksEdit->setValidator(v);
  v = new QIntValidator(this);
  v->setBottom(0);
  mpMinorMajorFactorEdit->setValidator(v);
  updateInputFields();
}

void SliderSettingsDialog::browseButtonPressed()
{
  const CCopasiObject * pObject =
    CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::NUMERIC);

  if (pObject)
    {
      if (!pObject->isValueDbl() && !pObject->isValueInt())
        {
          CQMessageBox::information(this, "Invalid Object",
                                    "You chose an object that does not correspond to an integer or float value. Please choose an object that corresponds to an integet or float value.",
                                    QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          mpSlider = NULL;
          mpObjectNameLineEdit->setText("");
          return;
        }

      /* Determine the associated entity key */
      CCopasiContainer * pAncestor = pObject->getObjectAncestor("Task");
      if (!pAncestor) pAncestor = pObject->getObjectAncestor("Model");

      if (!pAncestor)
        {
          CQMessageBox::information(this, "Invalid Object",
                                    "You chose an object that cannot be used as a slider. Please choose an other object.",
                                    QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          mpSlider = NULL;
          mpObjectNameLineEdit->setText("");
          return;
        }

      // We do not have a slider therefore we create one.
      if (mpSlider == NULL)
        {
          mpSlider = new CSlider;
          mpSlider->setSliderObject(const_cast< CCopasiObject * >(pObject));

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
      unsigned C_INT32 i, iMax = mDefinedSliders.size();

      for (i = 0; i < iMax;++i)
        if (mDefinedSliders[i]->getSliderObject() == pObject)
          break;

      // A slider with the new object exists we switch to it.
      if (i != iMax)
        setSlider(mDefinedSliders[i]);
      else // We need to change the object an reinitialize the slider
        {
          mpSlider->setSliderObject(const_cast< CCopasiObject * >(pObject));

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

void SliderSettingsDialog::extendedOptionsClicked()
{
  if (mpExtendedOptionsFrame->isHidden())
    {
      mpExtendedOptionsButton->setText("Advanced <<");
      mpExtendedOptionsFrame->show();
    }
  else
    {
      mpExtendedOptionsButton->setText("Advanced >>");
      mpExtendedOptionsFrame->hide();
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
          CQMessageBox::information(this, "Incorrect min value",
                                    "For logarithmic sliders, the minimum value may not be 0.0 or negative. Please set the minimum value to some (possibly very small) positive number first.",
                                    QMessageBox::Ok | QMessageBox::Default , QMessageBox::NoButton);
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
      mpMaxValueEdit->setText(QString::number(mMaxValue));
    }
  if (mOriginalValue < mMinValue)
    {
      mMinValue = mOriginalValue;
      mpMinValueEdit->setText(QString::number(mMinValue));
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
