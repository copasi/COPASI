/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SliderSettingsDialog.ui.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2006/04/07 07:19:46 $
   End CVS Header */

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

#include <qmessagebox.h>
#include <qvalidator.h>

#include <math.h>

#include "copasi.h"

#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"

#include "utilities/CSlider.h"

CSlider* SliderSettingsDialog::getSlider()
{
  return this->mpSlider;
}

void SliderSettingsDialog::setSlider(CSlider * slider)
{
  unsigned int i;
  unsigned int iMax = this->mDefinedSliders.size();
  bool found = false;
  for (i = 0; i < iMax;++i)
    {
      if (this->mDefinedSliders[i] == slider)
        {
          found = true;
          break;
        }
    }
  if (found)
    {
      this->mpSlider = slider;
      if (slider->getSliderObject())
        {
          this->mpObjectNameLineEdit->setText(FROM_UTF8(slider->getSliderObject()->getObjectDisplayName()));
        }
      else
        {
          this->mpObjectNameLineEdit->setText("Object not avalable!");
        }
      this->updateInputFields();
      this->updateInputFieldsValues();
    }
  else
    {
      this->mpSlider = NULL;
      this->mpObjectNameLineEdit->setText("NULL");
      this->mpObjectBrowseButton->show();
      this->updateInputFields();
    }
}

void SliderSettingsDialog::setDefinedSliders(std::vector<CSlider *> sliderVect)
{
  this->mDefinedSliders = sliderVect;
}

void SliderSettingsDialog::updateInputFieldsValues()
{
  if (this->mpSlider)
    {
      this->mValue = this->mpSlider->getSliderValue();
      this->mpObjectValueEdit->setText(QString::number(this->mValue));

      this->mOriginalValue = this->mpSlider->getOriginalValue();
      this->mpOriginalValueEdit->setText(QString::number(this->mOriginalValue));

      this->mMinValue = this->mpSlider->getMinValue();
      this->mpMinValueEdit->setText(QString::number(this->mMinValue));

      this->mMaxValue = this->mpSlider->getMaxValue();
      this->mpMaxValueEdit->setText(QString::number(this->mMaxValue));

      this->mNumMinorTicks = this->mpSlider->getTickNumber();
      this->mpNumMinorTicksEdit->setText(QString::number(this->mNumMinorTicks));

      this->mMinorMajorFactor = this->mpSlider->getTickFactor();
      this->mpMinorMajorFactorEdit->setText(QString::number(this->mMinorMajorFactor));

      this->numMinorTicksChanged();

      if (this->mpSlider->getScaling() == CSlider::logarithmic)
        {
          this->mpLogCheckBox->setChecked(true);
        }
      else
        {
          this->mpLogCheckBox->setChecked(false);
        }
    }
}

void SliderSettingsDialog::updateInputFields()
{
  // if the current slider is NULL, disable all input fields
  if (this->mpSlider)
    {
      mpObjectNameLineEdit->setEnabled(false);
      this->mpMaxValueEdit->setEnabled(true);
      this->mpMinValueEdit->setEnabled(true);
      this->mpMinorMajorFactorEdit->setEnabled(true);
      this->mpMinorTickSizeEdit->setEnabled(true);
      this->mpNumMinorTicksEdit->setEnabled(true);
      this->mpObjectValueEdit->setEnabled(true);
      this->mpLogCheckBox->setEnabled(true);
      this->mpOriginalValueEdit->setEnabled(true);
    }
  else
    {
      mpObjectNameLineEdit->setEnabled(true);
      this->mpMaxValueEdit->setEnabled(false);
      this->mpMinValueEdit->setEnabled(false);
      this->mpMinorMajorFactorEdit->setEnabled(false);
      this->mpMinorTickSizeEdit->setEnabled(false);
      this->mpNumMinorTicksEdit->setEnabled(false);
      this->mpObjectValueEdit->setEnabled(false);
      this->mpOriginalValueEdit->setEnabled(false);
      this->mpLogCheckBox->setEnabled(false);
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
  this->updateSlider();
  // close dialog with positive feedback
  done(QDialog::Accepted);
}

void SliderSettingsDialog::cancelButtonPressed()
{
  // close dialog, drop input
  this->close();
}

void SliderSettingsDialog::minorTickSizeChanged()
{
  // adjust numMinorTicks
  this->mMinorTickSize = this->mpMinorTickSizeEdit->text().toDouble();
  if (this->mMinorTickSize == 0.0)
    {
      this->mNumMinorTicks = 1;
    }
  else
    {
      this->mNumMinorTicks = (unsigned int)floor(((this->mMaxValue - this->mMinValue) / this->mMinorTickSize) + 0.5);
    }
  if (this->mNumMinorTicks == 0)
    {
      this->mNumMinorTicks = 1;
      this->mMinorTickSize = this->mMaxValue - this->mMinValue;
      this->mpMinorTickSizeEdit->setText(QString::number(this->mMinorTickSize));
    }
  this->mpNumMinorTicksEdit->setText(QString::number(this->mNumMinorTicks));
  this->mChanged = false;
}

void SliderSettingsDialog::numMinorTicksChanged()
{
  // adjust minorTickSize
  this->mNumMinorTicks = this->mpNumMinorTicksEdit->text().toUInt();
  if (this->mNumMinorTicks == 1)
    {
      this->mNumMinorTicks = 1;
      this->mpNumMinorTicksEdit->setText(QString::number(this->mNumMinorTicks));
    }
  this->mMinorTickSize = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;
  this->mpMinorTickSizeEdit->setText(QString::number(this->mMinorTickSize));
  this->mChanged = false;
}

void SliderSettingsDialog::minValueChanged()
{
  // check if it is smaller than the current value
  // if not, set it to the current value
  double value = mpMinValueEdit->text().toDouble();
  if ((value > this->mOriginalValue) &&
      (QMessageBox::warning(this, "Range to small.", "The minimum value you set is smaller than the default value\n of the slider. The new default will be set to the minimum.\n\n Do you want to procceed?", QMessageBox::Yes, QMessageBox::No | QMessageBox::Default) != QMessageBox::Yes)
)
    {
      this->mpMinValueEdit->setText(QString::number(this->mMinValue));
    }
  else
    {
      this->mOriginalValue = value;
      this->mpOriginalValueEdit->setText(QString::number(this->mOriginalValue));
      this->mMinValue = value;
      if (this->mMinValue > this->mMaxValue)
        {
          this->mMaxValue = this->mMinValue;
          this->mpMaxValueEdit->setText(QString::number(this->mMaxValue));
        }
      if (this->mMinValue > this->mValue)
        {
          this->mValue = this->mMinValue;
          this->mpObjectValueEdit->setText(QString::number(this->mValue));
        }
      this->mMinorTickSize = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;
      this->mpMinorTickSizeEdit->setText(QString::number(this->mMinorTickSize));
      if (this->mMinValue <= 0.0 && this->mpLogCheckBox->isChecked())
        {
          QMessageBox::critical(this, "wrong min value", "For logarithmic sliders, the minimum value may not be 0.0 or negative.\nPlease set the minimum value to some (possibly very small) positive number first.", QMessageBox::Ok | QMessageBox::Default , QMessageBox::NoButton);
          this->mpLogCheckBox->setChecked(false);
          this->mScaling = CSlider::linear;
        }
    }
  this->mChanged = false;
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if it is larget then the current value
  // else set it to the current value
  double value = mpMaxValueEdit->text().toDouble();
  if (value < this->mOriginalValue)
    {
      if (QMessageBox::warning(this, "Range to small.", "The maximum value you set is smaller than the default value\n of the slider. The new default will be set to the maximum.\n\n Do you want to procceed?", QMessageBox::Yes, QMessageBox::No | QMessageBox::Default) != QMessageBox::Yes)
        {
          this->mpMaxValueEdit->setText(QString::number(this->mMaxValue));
          this->mChanged = false;
          return;
        }
      this->mOriginalValue = value;
      this->mpOriginalValueEdit->setText(QString::number(this->mOriginalValue));
    }
  this->mMaxValue = value;
  if (this->mMinValue > this->mMaxValue)
    {
      this->mMinValue = this->mMaxValue;
      this->mpMinValueEdit->setText(QString::number(this->mMinValue));
    }
  if (this->mMaxValue < this->mValue)
    {
      this->mValue = this->mMaxValue;
      this->mpObjectValueEdit->setText(QString::number(this->mValue));
    }
  this->mMinorTickSize = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;
  this->mpMinorTickSizeEdit->setText(QString::number(this->mMinorTickSize));
  this->mChanged = false;
}

void SliderSettingsDialog::objectValueChanged()
{
  // check if the value is within range, else set a new range
  // get the value and set it in the current slider
  this->mValue = mpObjectValueEdit->text().toDouble();
  if (this->mValue > this->mMaxValue)
    {
      this->mMaxValue = this->mValue;
      this->mpMaxValueEdit->setText(QString::number(this->mMaxValue));
    }
  if (this->mValue < this->mMinValue)
    {
      this->mMinValue = this->mValue;
      this->mpMinValueEdit->setText(QString::number(this->mMinValue));
    }
  this->mChanged = false;
}

void SliderSettingsDialog::minorMajorFactorChanged()
{
  // get the value and set it in the current slider
  this->mMinorMajorFactor = this->mpMinorMajorFactorEdit->text().toUInt();
  this->mChanged = false;
}

void SliderSettingsDialog::init()
{
  this->mpSlider = NULL;
  this->mChanged = false;
  this->mScaling = CSlider::linear;
  this->mpExtendedOptionsButton->setText("Advanced >>");
  this->mpExtendedOptionsFrame->hide();
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
  this->updateInputFields();
}

void SliderSettingsDialog::browseButtonPressed()
{
  // open a selection dialog with single selection mode
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);
  browseDialog->setModel(mpModel);
  browseDialog->setSingleSelection(true);
  //browseDialog->enableExpertMode(false);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);
  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      CCopasiObject* object = selection->at(0);
      if (object && !object->isValueDbl() && !object->isValueInt())
        {
          QMessageBox::critical(this, "Invalid Object", "You chose an object that\ndoes not correspond to an integer or float value.\nPlease choose an object that corresponds to an integet or float value.", QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          this->mpSlider = NULL;
          this->mpObjectNameLineEdit->setText("");
          return;
        }
      /* Determine the associated entity key */
      CCopasiContainer * pAncestor = object->getObjectAncestor("Task");
      if (!pAncestor) pAncestor = object->getObjectAncestor("Model");

      if (!pAncestor)
        {
          QMessageBox::critical(this, "Invalid Object", "You chose an object that\ndoes cannot be used as a slider.\nPlease choose an object that corresponds to an integet or float value.", QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          this->mpSlider = NULL;
          this->mpObjectNameLineEdit->setText("");
          return;
        }

      // check if this object already has a slider object
      // if yes, call setSlider with the correct slider object
      // else create a new slider object for this object and add it to the sliders
      if (this->mpSlider && this->mpSlider->getSliderObject() == object) return;
      unsigned C_INT32 i;
      unsigned C_INT32 iMax = this->mDefinedSliders.size();
      unsigned C_INT32 found = iMax;
      unsigned C_INT32 sliderFound = iMax;
      for (i = 0; i < iMax;++i)
        {
          if (this->mDefinedSliders[i]->getSliderObject() == object)
            {
              found = i;
              if (sliderFound)
                {
                  break;
                }
            }
          if (this->mDefinedSliders[i] == this->mpSlider)
            {
              sliderFound = i;
              if (found)
                {
                  break;
                }
            }
        }
      if (this->mpSlider && (!sliderFound))
        {
          delete this->mpSlider;
          this->mpSlider = NULL;
        }
      if (found != iMax)
        {
          this->setSlider(this->mDefinedSliders[found]);
        }
      else
        {
          this->mpSlider = new CSlider();
          this->mpSlider->setSliderObject(object);

          if (pAncestor)
            this->mpSlider->setAssociatedEntityKey(pAncestor->getKey());

          this->mpSlider->resetRange();
          this->updateInputFields();
          this->updateInputFieldsValues();
        }
      this->mpObjectNameLineEdit->setText(FROM_UTF8(this->mpSlider->getSliderObject()->getObjectDisplayName()));
    }
  else
    {
      this->mpSlider = NULL;
      this->mpObjectNameLineEdit->setText("");
    }
}

void SliderSettingsDialog::setModel(CModel * model)
{
  this->mpModel = model;
}

void SliderSettingsDialog::disableObjectChoosing(bool disableChoosing)
{
  this->mpObjectBrowseButton->setHidden(disableChoosing);
}

void SliderSettingsDialog::updateSlider()
{
  if (this->mChanged)
    {
      this->updateInternalValues();
    }
  if (this->mpSlider)
    {
      if (this->mMinValue < this->mpSlider->getMaxValue())
        {
          this->mpSlider->setMinValue(this->mMinValue);
          this->mpSlider->setMaxValue(this->mMaxValue);
        }
      else
        {
          this->mpSlider->setMaxValue(this->mMaxValue);
          this->mpSlider->setMinValue(this->mMinValue);
        }
      this->mpSlider->setSliderValue(this->mValue);
      this->mpSlider->setTickNumber(this->mNumMinorTicks);
      this->mpSlider->setTickFactor(this->mMinorMajorFactor);
      this->mpSlider->setScaling((CSlider::Scale)this->mScaling);
      this->mpSlider->setOriginalValue(this->mOriginalValue);
    }
}

void SliderSettingsDialog::lineEditChanged()
{
  this->mChanged = true;
}

void SliderSettingsDialog::extendedOptionsClicked()
{
  if (this->mpExtendedOptionsFrame->isHidden())
    {
      this->mpExtendedOptionsButton->setText("Advanced <<");
      this->mpExtendedOptionsFrame->show();
    }
  else
    {
      this->mpExtendedOptionsButton->setText("Advanced >>");
      this->mpExtendedOptionsFrame->hide();
    }
}

void SliderSettingsDialog::logCheckBoxToggled(bool on)
{
  if (this->mChanged)
    {
      this->updateInternalValues();
    }
  this->mChanged = true;
  if (on)
    {
      // check if the minValue is 0.0 or negative if so, issue an error message and uncheck the checkbox again
      if (this->mMinValue <= 0.0)
        {
          QMessageBox::critical(this, "wrong min value", "For logarithmic sliders, the minimum value may not be 0.0 or negative.\nPlease set the minimum value to some (possibly very small) positive number first.", QMessageBox::Ok | QMessageBox::Default , QMessageBox::NoButton);
          this->mpLogCheckBox->setChecked(false);
          this->mScaling = CSlider::linear;
        }
      else
        {
          this->mScaling = CSlider::logarithmic;
        }
    }
  else
    {
      this->mScaling = CSlider::linear;
    }
}

void SliderSettingsDialog::globalCheckBoxToggled()
{
  if (this->mChanged)
    {
      this->updateInternalValues();
    }
}

void SliderSettingsDialog::updateInternalValues()
{
  objectValueChanged();
  originalValueChanged();
  minValueChanged();
  maxValueChanged();
  minorMajorFactorChanged();
  minorTickSizeChanged();
  numMinorTicksChanged();
}

void SliderSettingsDialog::originalValueChanged()
{
  // check if the value is within range, else set it to
  // set new values for the range
  this->mOriginalValue = mpOriginalValueEdit->text().toDouble();
  if (this->mOriginalValue > this->mMaxValue)
    {
      this->mMaxValue = this->mOriginalValue;
      this->mpMaxValueEdit->setText(QString::number(this->mMaxValue));
    }
  if (this->mOriginalValue < this->mMinValue)
    {
      this->mMinValue = this->mOriginalValue;
      this->mpMinValueEdit->setText(QString::number(this->mMinValue));
    }
  this->mChanged = false;
}
