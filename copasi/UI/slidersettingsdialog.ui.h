/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/slidersettingsdialog.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/07 16:59:54 $
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

void SliderSettingsDialog::setSlider(C_INT32 taskId, CopasiSlider * slider)
{
  // check if this slider is in the vector belonging to the given task id
  if (this->sliderMap.find(taskId) != this->sliderMap->end())
    {
      std::vector< CopasiSlider* >::const_iterator it = this->sliderMap[taskId]->begin();
      std::vector< CopasiSlider* >::const_iterator endPos = this->sliderMap[taskId]->end();
      bool found = false;
      while (it != endPos)
        {
          if ((*it) == slider)
            {
              this->setTask(taskId);
              this->setObject(slider->object());
              break;
            }
          ++it;
        }
    }
}

void SliderSettingsDialog::setTask(C_INT32 taskId)
{
  // change the selected task in the TaskComboBox if possible
  std::string name = this->taskDisplayMapping[taskId];
  unsigned int counter;
  unsigned int maxCount = this->taskComboBox->count();
  for (counter = 0; counter < maxCount;++counter)
    {
      if (this->taskComboBox->text(counter) == name)
        {
          break;
        }
    }
  this->taskComboBox->setCurrentItem(counter);
}

void SliderSettingsDialog::setTaskList(std::map<C_INT32, std::string> taskMap)
{
  this->taskDisplayMapping = taskMap;
}

void SliderSettingsDialog::setSliderMap(std::map<C_INT32 , std::vector<CopasiSlider *> > sliderMap)
{
  // fill the task ComboBox and the Object ComboBox
  this->sliderMap = sliderMap;
}

void SliderSettingsDialog::updateObjectBox()
{
  // check which task is currently selected and update the object combobox
}

void SliderSettingsDialog::updateSliderValues()
{}

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

void SliderSettingsDialog::majorTickSizeChanged()
{
  // update numMajorTicks
  this->majorTickSizeVar = this->text2Double(this->majorTickSizeEdit->getText());
  if (this->majorTickSizeVar == 0.0)
    {
      this->majorTickSizeVar = 1.0;
      this->majorTickSizeEdit->setText("1.0");
    }
  if (this->majorTickSizeVar < this->minorTickSizeVar)
    {
      this->majorTickSizeVar = this->minorTickSizeVar;
      this->majorTickSizeEdit->setText(this->double2Text(this->majorTickSizeVar));
    }
  this->numMajorTicksVar = (this->maxValueVar - this->minValueVar) / this->majorTickSizeVar;
  this->numMajorTicksEdit->setText(this->double2Text(this->numMajorTicksVar));
}

void SliderSettingsDialog::minorTickSizeChanged()
{
  // update numMinorTicks
  this->minorTickSizeVar = this->text2Double(this->minorTickSizeEdit->getText());
  if (this->minorTickSizeVar == 0.0)
    {
      this->minorTickSizeVar = 1.0;
      this->minorTickSizeEdit->setText("1.0");
    }
  if (this->minorTickSizeVar > this->majorTickSizeVar)
    {
      this->minorTickSizeVar = this->majorTickSizeVar;
      this->minorTickSizeEdit->setText(this->double2Text(this->minorTickSizeVar));
    }
  this->numMajorTicksVar = (this->maxValueVar - this->minValueVar) / this->majorTickSizeVar;
  this->numMajorTicksEdit->setText(this->double2Text(this->numMajorTicksVar));
}

void SliderSettingsDialog::numMajorTicksChanged()
{
  // update majorTickSize
  this->numMajorTicksVar = this->text2Double(this->numMajorTicksEdit->getText());
  if (this->numMajorTicksVar == 0.0)
    {
      this->numMajorTicksVar = 1.0;
      this->numMajorTicksEdit->setText("1.0");
    }
  if (this->numMajorTicksVar > this->numMinorTicksVar)
    {
      this->numMajorTicksVar = this->numMinorTicksVar;
      this->numMajorTicksEdit->setText(this->double2Text(this->numMajorTicksVar));
    }
  this->majorTicksSizeVar = (this->maxValueVar - this->minValueVar) / this->numMajorTicksVar;
  this->majorTickSizeEdit->setText(this->double2Text(this->majorTickSizeVar));
}

void SliderSettingsDialog::numMinorTicksChanged()
{
  //update minorTickSize
  this->numMinorTicksVar = this->text2Double(this->numMinorTicksEdit->getText());
  if (this->numMinorTicksVar == 0.0)
    {
      this->numMinorTicksVar = 1.0;
      this->numMinorTicksEdit->setText("1.0");
    }
  if (this->numMinorTicksVar < this->numMajorTicksVar)
    {
      this->numMinorTicksVar = this->numMajorTicksVar;
      this->numMinorTicksEdit->setText(this->double2Text(this->numMinorTicksVar));
    }
  this->minorTicksSizeVar = (this->maxValueVar - this->minValueVar) / this->numMinorTicksVar;
  this->minorTickSizeEdit->setText(this->double2Text(this->minorTickSizeVar));
}

void SliderSettingsDialog::minValueChanged()
{
  // check if min<max, else switch both
  // update major and minorTickSize

  this->minValueVar = this->text2Double(this->minValueEdit());
  if (this->minValueVar > this->maxValueVar)
    {
      double tmp = this->minValueVar;
      this->minValueVar = this->maxValueVar;
      this->maxValueVar = tmp;
      this->minValueEdit->setText(this->double2Text(this->minValueVar));
      this->maxValueEdit->setText(this->double2Text(this->maxValueVar));
    }
  this->numMajorTicksVar = (this->maxValueVar - this->minValueVar) / this->majorTickSizeVar;
  this->numMajorTicksEdit->setText(this->double2Text(this->numMajorTicksVar));
  this->numMinorTicksVar = (this->maxValueVar - this->minValueVar) / this->minorTickSizeVar;
  this->numMinorTicksEdit->setText(this->double2Text(this->numMinorTicksVar));
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if min<max, else switch both
  // update major and minorTickSize

  this->maxValueVar = this->text2Double(this->maxValueEdit());
  if (this->minValueVar > this->maxValueVar)
    {
      double tmp = this->minValueVar;
      this->minValueVar = this->maxValueVar;
      this->maxValueVar = tmp;
      this->minValueEdit->setText(this->double2Text(this->minValueVar));
      this->maxValueEdit->setText(this->double2Text(this->maxValueVar));
    }
  this->numMajorTicksVar = (this->maxValueVar - this->minValueVar) / this->majorTickSizeVar;
  this->numMajorTicksEdit->setText(this->double2Text(this->numMajorTicksVar));
  this->numMinorTicksVar = (this->maxValueVar - this->minValueVar) / this->minorTickSizeVar;
  this->numMinorTicksEdit->setText(this->double2Text(this->numMinorTicksVar));
}

void SliderSettingsDialog::objectValueChanged()
{
  // check if value is in the range, else expand range
  this->objectValueVar = this->text2Double(this->objectValueEdit->text());
  if (this->objectValueVar < this - < minValueVar || this->objectValueVar > this->maxValueVar)
    {
    }
}

void SliderSettingsDialog::init()
{
  objectValueEdit->setValidator(new QDoubleValidator(this));
  minValueEdit->setValidator(new QDoubleValidator(this));
  maxValueEdit->setValidator(new QDoubleValidator(this));
  minorTickSizeEdit->setValidator(new QDoubleValidator(this));
  majorTickSizeEdit->setValidator(new QDoubleValidator(this));
  numMinorTicksEdit->setValidator(new QDoubleValidator(this));
  numMajorTicksEdit->setValidator(new QDoubleValidator(this));
}

const std::string& SliderSettingsDialog::int2Text(int i)
{
  this->outStream.clear();
  this->outStream << i;
  return this->outStream.str();
}

const std::string& SliderSettingsDialog::double2Text(double d)
{
  this->outStream.clear();
  this->outStream << d;
  return this->outStream.str();
}

double SliderSettingsDialog::text2Double(const std::string & text)
{
  double d = atof(text.c_str());
  return d;
}

int SliderSettingsDialog::text2Int(const std::string & text)
{
  int i = atol(text.c_str());
  return i;
}

void SliderSettingsDialog::browseButtonPressed()
{
  // open a selection dialog with single selection mode
  SimpleSelectionDialog browseDialog = new SimpleSelectionDialog(this);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);
  browseDialog->exec();
  delete browseDialog;
}

void SliderSettingsDialog::setObject(CCopasiObject * object)
{
  // find the object in the objectComboBox and make it the current item
  std::string name = this->object->getCN();
  unsigned int counter;
  unsigned int maxCount = this->objectComboBox->count();
  for (counter = 0; counter < maxCount;++counter)
    {
      if (this->objectComboBox->text(counter) == name)
        {
          break;
        }
    }
  this->taskComboBox->setCurrentItem(counter);
}
