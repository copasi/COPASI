/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/slidersettingsdialog.ui.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/03 14:58:07 $
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
      this->mpObjectLabel->setText(FROM_UTF8(slider->object()->getCN()));
      this->mpObjectBrowseButton->hide();
      this->updateInputFields();
      this->updateInputFieldsValues();
    }
  else
    {
      this->mpSlider = NULL;
      this->mpObjectLabel->setText("NULL");
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
  this->mpObjectValueEdit->setText(QString::number(this->mpSlider->value()));
  this->mpMinValueEdit->setText(QString::number(this->mpSlider->minValue()));
  this->mpMaxValueEdit->setText(QString::number(this->mpSlider->maxValue()));
  this->mpMinorTickSizeEdit->setText(QString::number(this->mpSlider->minorTickInterval()));
  this->mpMinorMajorFactorEdit->setText(QString::number(this->mpSlider->minorMajorFactor()));
  this->minorTickSizeChanged();
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
  // close dialog with positive feedback
  // fill output structure
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
  double value = this->mpMinorTickSizeEdit->text().toDouble();
  this->mpSlider->setMinorTickInterval(value);
  value = (this->mpSlider->maxValue() - this->mpSlider->minValue()) / value;
  if (value < 1.0)
    {
      value = this->mpSlider->maxValue() - this->mpSlider->minValue();
      this->mpSlider->setMinorTickInterval(value);
      this->mpMinorTickSizeEdit->setText(QString::number(value));
      value = 1.0;
    }
  this->mpNumMinorTicksEdit->setText(QString::number(value));
}

void SliderSettingsDialog::numMinorTicksChanged()
{
  // adjust minorTickSize
  double value = this->mpNumMinorTicksEdit->text().toDouble();
  if (value < 1.0)
    {
      value = 1.0;
      this->mpNumMinorTicksEdit->setText(QString::number(value));
    }
  value = (this->mpSlider->maxValue() - this->mpSlider->minValue()) / value;
  this->mpSlider->setMinorTickInterval(value);
  this->mpMinorTickSizeEdit->setText(QString::number(value));
}

void SliderSettingsDialog::minValueChanged()
{
  // check if it is smaller than the current value
  // if not, set it to the current value
  double value = mpMinValueEdit->text().toDouble();
  if (value > this->mpSlider->value())
    {
      value = this->mpSlider->value();
      this->mpMinValueEdit->setText(QString::number(value));
    }
  this->mpSlider->setMinValue(value);
  // adjust tickIntervalSize
  value = this->mpNumMinorTicksEdit->text().toDouble();
  value = (this->mpSlider->maxValue() - this->mpSlider->minValue()) / value;
  this->mpSlider->setMinorTickInterval(value);
  this->mpMinorTickSizeEdit->setText(QString::number(value));
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if it is larget then the current value
  // else set it to the current value
  double value = mpMaxValueEdit->text().toDouble();
  if (value < this->mpSlider->value())
    {
      value = this->mpSlider->value();
      this->mpMaxValueEdit->setText(QString::number(value));
    }
  this->mpSlider->setMaxValue(value);
  // adjust tickIntervalSize
  value = this->mpNumMinorTicksEdit->text().toDouble();
  value = (this->mpSlider->maxValue() - this->mpSlider->minValue()) / value;
  this->mpSlider->setMinorTickInterval(value);
  this->mpMinorTickSizeEdit->setText(QString::number(value));
}

void SliderSettingsDialog::objectValueChanged()
{
  // check if the value is within range, else set it to
  // the closest border of the range
  // get the value and set it in the current slider
  double value = mpObjectValueEdit->text().toDouble();
  if (value > this->mpSlider->maxValue())
    {
      value = this->mpSlider->maxValue();
      this->mpObjectValueEdit->setText(QString::number(value));
    }
  if (value < this->mpSlider->minValue())
    {
      value = this->mpSlider->minValue();
      this->mpObjectValueEdit->setText(QString::number(value));
    }
  this->mpSlider->setValue(value);
}

void SliderSettingsDialog::minorMajorFactorChanged()
{
  // get the value and set it in the current slider
  int value = this->mpMinorMajorFactorEdit->text().toInt();
  this->mpSlider->setMinorMajorFactor(value);
}

void SliderSettingsDialog::init()
{
  mpObjectValueEdit->setValidator(new QDoubleValidator(this));
  mpMinValueEdit->setValidator(new QDoubleValidator(this));
  mpMaxValueEdit->setValidator(new QDoubleValidator(this));
  mpMinorTickSizeEdit->setValidator(new QDoubleValidator(this));
  mpNumMinorTicksEdit->setValidator(new QDoubleValidator(this));
  QIntValidator* v = new QIntValidator(this);
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
      bool found = false;
      bool sliderFound = false;
      for (i = 0; i < iMax;++i)
        {
          if (this->mDefinedSliders[i]->object() == object)
            {
              found = true;
              if (sliderFound)
                {
                  break;
                }
            }
          if (this->mDefinedSliders[i] == this->mpSlider)
            {
              sliderFound = true;
              if (found)
                {
                  break;
                }
            }
        }
      if (this->mpSlider && (!sliderFound))
        {
          delete this->mpSlider;
        }
      if (found)
        {
          this->setSlider(this->mDefinedSliders[i]);
        }
      else
        {
          this->mpSlider = new CopasiSlider(object, NULL);
          this->updateInputFields();
          this->updateInputFieldsValues();
        }
    }
  this->mpObjectNameLineEdit->setText(FROM_UTF8(this->mpSlider->object()->getCN()));
}

void SliderSettingsDialog::setModel(CModel * model)
{
  this->mpModel = model;
}
