/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/slidersettingsdialog.ui.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/11/08 16:46:19 $
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

#include <cmath>

CopasiSlider* SliderSettingsDialog::getSlider()
{
  return this->mpSlider;
}

void SliderSettingsDialog::setSlider(CopasiSlider * slider)
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
      this->mpObjectNameLineEdit->setText(FROM_UTF8(slider->object()->getCN()));
      this->mpObjectBrowseButton->hide();
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

void SliderSettingsDialog::setDefinedSliders(std::vector<CopasiSlider *> sliderVect)
{
  this->mDefinedSliders = sliderVect;
}

void SliderSettingsDialog::updateInputFieldsValues()
{
  this->mValue = this->mpSlider->value();
  this->mpObjectValueEdit->setText(QString::number(this->mValue));

  this->mMinValue = this->mpSlider->minValue();
  this->mpMinValueEdit->setText(QString::number(this->mMinValue));

  this->mMaxValue = this->mpSlider->maxValue();
  this->mpMaxValueEdit->setText(QString::number(this->mMaxValue));

  this->mNumMinorTicks = this->mpSlider->numMinorTicks();
  this->mpNumMinorTicksEdit->setText(QString::number(this->mNumMinorTicks));

  this->mMinorMajorFactor = this->mpSlider->minorMajorFactor();
  this->mpMinorMajorFactorEdit->setText(QString::number(this->mMinorMajorFactor));

  this->numMinorTicksChanged();
}

void SliderSettingsDialog::updateInputFields()
{
  // if the current slider is NULL, disable all input fields
  if (this->mpSlider)
    {
      this->mpMaxValueEdit->setEnabled(true);
      this->mpMinValueEdit->setEnabled(true);
      this->mpMinorMajorFactorEdit->setEnabled(true);
      this->mpMinorTickSizeEdit->setEnabled(true);
      this->mpNumMinorTicksEdit->setEnabled(true);
      this->mpObjectValueEdit->setEnabled(true);
    }
  else
    {
      this->mpMaxValueEdit->setEnabled(false);
      this->mpMinValueEdit->setEnabled(false);
      this->mpMinorMajorFactorEdit->setEnabled(false);
      this->mpMinorTickSizeEdit->setEnabled(false);
      this->mpNumMinorTicksEdit->setEnabled(false);
      this->mpObjectValueEdit->setEnabled(false);
    }
}

void SliderSettingsDialog::okButtonPressed()
{
  // only noew change underlying slider
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
}

void SliderSettingsDialog::numMinorTicksChanged()
{
  // adjust minorTickSize
  this-> mNumMinorTicks = this->mpNumMinorTicksEdit->text().toUInt();
  if (this->mNumMinorTicks == 1)
    {
      this->mNumMinorTicks = 1;
      this->mpNumMinorTicksEdit->setText(QString::number(this->mNumMinorTicks));
    }
  this->mMinorTickSize = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;
  this->mpMinorTickSizeEdit->setText(QString::number(this->mMinorTickSize));
}

void SliderSettingsDialog::minValueChanged()
{
  // check if it is smaller than the current value
  // if not, set it to the current value
  this->mMinValue = mpMinValueEdit->text().toDouble();
  if (this->mMinValue > this->mValue)
    {
      this->mMinValue = this->mValue;
      this->mpMinValueEdit->setText(QString::number(this->mMinValue));
    }
  this->mMinorTickSize = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;
  this->mpMinorTickSizeEdit->setText(QString::number(this->mMinorTickSize));
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if it is larget then the current value
  // else set it to the current value
  this->mMaxValue = mpMaxValueEdit->text().toDouble();
  if (this->mMaxValue < this->mValue)
    {
      this->mMaxValue = this->mValue;
      this->mpMaxValueEdit->setText(QString::number(this->mMaxValue));
    }
  this->mMinorTickSize = (this->mMaxValue - this->mMinValue) / this->mNumMinorTicks;
  this->mpMinorTickSizeEdit->setText(QString::number(this->mMinorTickSize));
}

void SliderSettingsDialog::objectValueChanged()
{
  // check if the value is within range, else set it to
  // the closest border of the range
  // get the value and set it in the current slider
  this->mValue = mpObjectValueEdit->text().toDouble();
  if (this->mValue > this->mMaxValue)
    {
      this->mValue = this->mMaxValue;
      this->mpObjectValueEdit->setText(QString::number(this->mValue));
    }
  if (this->mValue < this->mMinValue)
    {
      this->mValue = this->mMinValue;
      this->mpObjectValueEdit->setText(QString::number(this->mValue));
    }
}

void SliderSettingsDialog::minorMajorFactorChanged()
{
  // get the value and set it in the current slider
  this->mMinorMajorFactor = this->mpMinorMajorFactorEdit->text().toUInt();
}

void SliderSettingsDialog::init()
{
  mpObjectValueEdit->setValidator(new QDoubleValidator(this));
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
  SimpleSelectionDialog* browseDialog = new SimpleSelectionDialog(this);
  browseDialog->setModel(mpModel);
  browseDialog->setSingleSelection(true);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);
  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      CCopasiObject* object = selection->at(0);
      // check if this object already has a slider object
      // if yes, call setSlider with the correct slider object
      // else create a new slider object for this object and add it to the sliders
      if (this->mpSlider && this->mpSlider->object() == object) return;
      unsigned C_INT32 i;
      unsigned C_INT32 iMax = this->mDefinedSliders.size();
      unsigned C_INT32 found = iMax;
      unsigned C_INT32 sliderFound = iMax;
      for (i = 0; i < iMax;++i)
        {
          if (this->mDefinedSliders[i]->object() == object)
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
          this->mpSlider = new CopasiSlider(object, NULL);
          this->updateInputFields();
          this->updateInputFieldsValues();
        }
      this->mpObjectNameLineEdit->setText(FROM_UTF8(this->mpSlider->object()->getCN()));
    }
  else
    {
      this->mpSlider = NULL;
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
  if (this->mpSlider)
    {
      if (this->mMinValue < this->mpSlider->maxValue())
        {
          this->mpSlider->setMinValue(this->mMinValue);
          this->mpSlider->setMaxValue(this->mMaxValue);
        }
      else
        {
          this->mpSlider->setMaxValue(this->mMaxValue);
          this->mpSlider->setMinValue(this->mMinValue);
        }
      this->mpSlider->setValue(this->mValue);
      this->mpSlider->setNumMinorTicks(this->mNumMinorTicks);
      this->mpSlider->setMinorMajorFactor(this->mMinorMajorFactor);
    }
}
