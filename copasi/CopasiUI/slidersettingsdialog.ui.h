/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/slidersettingsdialog.ui.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/02 17:01:32 $
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
  if (this->sliderMap.find(taskId) != this->sliderMap.end())
    {
      std::vector< CopasiSlider* > &sliderVec = this->sliderMap[taskId];
      std::vector< CopasiSlider* >::iterator it = sliderVec.begin();
      std::vector< CopasiSlider* >::iterator endPos = sliderVec.end();
      bool found = false;
      while (it != endPos)
        {
          if ((*it) == slider)
            {
              this->setTask(taskId);
              this->setObject(slider->object());
              found = true;
              break;
            }
          ++it;
        }
    }
}

void SliderSettingsDialog::setTask(C_INT32 taskId)
{
  // change the selected task in the TaskComboBox if possible
  this->mCurrentTaskId = taskId;
  std::string name = this->taskDisplayMap[this->mCurrentTaskId];
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
  this->taskDisplayMap = taskMap;
}

void SliderSettingsDialog::setSliderMap(std::map<C_INT32 , std::vector<CopasiSlider *> > sliderMap)
{
  // fill the task ComboBox and the Object ComboBox
  this->sliderMap = sliderMap;

  std::map<C_INT32, std::vector<CopasiSlider* > >::iterator it = this->sliderMap.begin();
  std::map<C_INT32, std::vector<CopasiSlider* > >::iterator endPos = this->sliderMap.end();
  while (it != endPos)
    {
      //      std::cout << it->first << ":" << this->taskDisplayMap[it->first] << std::endl;
      if (this->taskDisplayMap.find(it->first) != this->taskDisplayMap.end())
        {
          this->taskComboBox->insertItem(this->taskDisplayMap[it->first]);
        }
      ++it;
    }
  this->updateObjectBox();
}

void SliderSettingsDialog::updateObjectBox()
{
  // check which task is currently selected and update the object combobox
  C_INT32 currentTask = -1;
  if (this->taskComboBox->count() == 0) return;
  std::string text = this->taskComboBox->text(this->taskComboBox->currentItem()).latin1();
  std::map<C_INT32, std::string>::iterator it = this->taskDisplayMap.begin();
  std::map<C_INT32, std::string>::iterator endPos = this->taskDisplayMap.end();
  while (it != endPos)
    {
      if (it->second == text)
        {
          currentTask = it->first;
          break;
        }
    }
  // clear the combo box
  this->objectComboBox->setListBox(new QListBox());
  if (currentTask != -1 && this->sliderMap.find(currentTask) != this->sliderMap.end())
    {
      std::vector<CopasiSlider*> sliderVect = this->sliderMap[currentTask];
      unsigned int i;
      unsigned int maxCount = sliderVect.size();
      for (i = 0; i < maxCount;++i)
        {
          this->objectComboBox->insertItem(sliderVect[i]->object()->getCN());
        }
    }
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
  this->majorTickSizeVar = this->text2Double(this->majorTickSizeEdit->text());
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
  this->numMajorSteps = (this->maxValueVar - this->minValueVar) / this->majorTickSizeVar;
  this->numMajorTicksEdit->setText(this->double2Text(this->numMajorSteps));
}

void SliderSettingsDialog::minorTickSizeChanged()
{
  // update numMinorTicks
  this->minorTickSizeVar = this->text2Double(this->minorTickSizeEdit->text());
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
  this->numMinorSteps = (this->maxValueVar - this->minValueVar) / this->minorTickSizeVar;
  this->numMinorTicksEdit->setText(this->double2Text(this->numMinorSteps));
}

void SliderSettingsDialog::numMajorTicksChanged()
{
  // update majorTickSize
  this->numMajorSteps = this->text2Double(this->numMajorTicksEdit->text());
  if (this->numMajorSteps == 0.0)
    {
      this->numMajorSteps = 1.0;
      this->numMajorTicksEdit->setText("1.0");
    }
  if (this->numMajorSteps > this->numMinorSteps)
    {
      this->numMajorSteps = this->numMinorSteps;
      this->numMajorTicksEdit->setText(this->double2Text(this->numMajorSteps));
    }
  this->majorTickSizeVar = (this->maxValueVar - this->minValueVar) / this->numMajorSteps;
  this->majorTickSizeEdit->setText(this->double2Text(this->majorTickSizeVar));
}

void SliderSettingsDialog::numMinorTicksChanged()
{
  //update minorTickSize
  this->numMinorSteps = this->text2Double(this->numMinorTicksEdit->text());
  if (this->numMinorSteps == 0.0)
    {
      this->numMinorSteps = 1.0;
      this->numMinorTicksEdit->setText("1.0");
    }
  if (this->numMinorSteps < this->numMajorSteps)
    {
      this->numMinorSteps = this->numMajorSteps;
      this->numMinorTicksEdit->setText(this->double2Text(this->numMinorSteps));
    }
  this->minorTickSizeVar = (this->maxValueVar - this->minValueVar) / this->numMinorSteps;
  this->minorTickSizeEdit->setText(this->double2Text(this->minorTickSizeVar));
}

void SliderSettingsDialog::minValueChanged()
{
  // check if min<max, else switch both
  // update major and minorTickSize

  this->minValueVar = this->text2Double(this->minValueEdit->text());
  if (this->minValueVar > this->maxValueVar)
    {
      double tmp = this->minValueVar;
      this->minValueVar = this->maxValueVar;
      this->maxValueVar = tmp;
      this->minValueEdit->setText(this->double2Text(this->minValueVar));
      this->maxValueEdit->setText(this->double2Text(this->maxValueVar));
    }
  this->numMajorSteps = (this->maxValueVar - this->minValueVar) / this->majorTickSizeVar;
  this->numMajorTicksEdit->setText(this->double2Text(this->numMajorSteps));
  this->numMinorSteps = (this->maxValueVar - this->minValueVar) / this->minorTickSizeVar;
  this->numMinorTicksEdit->setText(this->double2Text(this->numMinorSteps));
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if min<max, else switch both
  // update major and minorTickSize

  this->maxValueVar = this->text2Double(this->maxValueEdit->text());
  if (this->minValueVar > this->maxValueVar)
    {
      double tmp = this->minValueVar;
      this->minValueVar = this->maxValueVar;
      this->maxValueVar = tmp;
      this->minValueEdit->setText(this->double2Text(this->minValueVar));
      this->maxValueEdit->setText(this->double2Text(this->maxValueVar));
    }
  this->numMajorSteps = (this->maxValueVar - this->minValueVar) / this->majorTickSizeVar;
  this->numMajorTicksEdit->setText(this->double2Text(this->numMajorSteps));
  this->numMinorSteps = (this->maxValueVar - this->minValueVar) / this->minorTickSizeVar;
  this->numMinorTicksEdit->setText(this->double2Text(this->numMinorSteps));
}

void SliderSettingsDialog::objectValueChanged()
{
  // check if value is in the range, else expand range
  this->objectValueVar = this->text2Double(this->objectValueEdit->text());
  if (this->objectValueVar < this->minValueVar || this->objectValueVar > this->maxValueVar)
  {}
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

const std::string SliderSettingsDialog::int2Text(int i)
{
  this->outStream.clear();
  this->outStream << i;
  return this->outStream.str();
}

const std::string SliderSettingsDialog::double2Text(double d)
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
  SimpleSelectionDialog* browseDialog = new SimpleSelectionDialog(this);
  browseDialog->setModel(mpModel);
  browseDialog->setSingleSelection(true);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);
  if (browseDialog->exec() == QDialog::Accepted && selection->size() != 0)
    {
      CCopasiObject* object = selection[0];
      // check if this object already has a slider object in this task
      // if yes, call setSlider with the correct slider object
      // else create a new slider object for this object and add it to the sliders for the current task
      int found = -1;
      std::vector<CopasiSlider*> sliderVect = this->sliderMap[this->mCurrentTaskId];
      unsigned int i;
      unsigned int iMax = sliderVect.size();
      for (i = 0; i < iMax;++i)
        {
          if (sliderVect[i]->object() == object)
            {
              found = i;
              break;
            }
        }
      if (found != -1)
        {
          this->setSlider(this->mCurrentTask, this->sliderVect[found]);
        }
      else
      {}
    }
  delete browseDialog;
}

void SliderSettingsDialog::setObject(CCopasiObject * object)
{
  // find the object in the objectComboBox and make it the current item
  if (!object) return;

  std::string name = object->getCN();
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

void SliderSettingsDialog::setModel(CModel * model)
{
  this->mpModel = model;
}
