/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/slidersettingsdialog.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/06 19:31:09 $
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
}

void SliderSettingsDialog::setTask(C_INT32 taskId)
{
  // change the selected task in the TaskComboBox if possible
}

void SliderSettingsDialog::setTaskList(std::map<C_INT32, std::string> taskMap)
{
  this->taskDisplayMapping = taskMap;
}

void SliderSettingsDialog::setSliderMap(std::map<C_INT32 , std::vector<CopasiSlider *> > sliderMap)
{
  // fill the task ComboBox and the Object ComboBox
}

void SliderSettingsDialog::updateObjectBox()
{
  // check which task is currently selected and update the object combobox
}

void SliderSettingsDialog::updateSliderValues()
{
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

void SliderSettingsDialog::majorTickSizeChanged()
{
  // update numMajorTicks
}

void SliderSettingsDialog::minorTickSizeChanged()
{
  // update numMinorTicks
}

void SliderSettingsDialog::numMajorTicksChanged()
{
  // update majorTickSize
}

void SliderSettingsDialog::numMinorTicksChanged()
{
  //update minorTickSize
}

void SliderSettingsDialog::minValueChanged()
{
  // check if min<max, else switch both
  // update major and minorTickSize
  // check if value is within range, if not, set to sensible value
}

void SliderSettingsDialog::maxValueChanged()
{
  // check if min<max, else switch both
  // update major and minorTickSize
  // check if value is within range, if not, set to sensible value
}

void SliderSettingsDialog::objectValueChanged()
{
  // check if value is in the range, else expand range
}

void SliderSettingsDialog::init()
{
  QRegExp realRegExp = QRegExp("\\-?\\d+(\\.\\d+)?([eE]\\-?\\d+)?");
  QRegExp intRegExp = QRegExp("\\d+");
  objectValueEdit->setValidator(new QRegExpValidator(realRegExp, this));
  minValueEdit->setValidator(new QRegExpValidator(realRegExp, this));
  maxValueEdit->setValidator(new QRegExpValidator(realRegExp, this));
  minorTickSizeEdit->setValidator(new QRegExpValidator(realRegExp, this));
  majorTickSizeEdit->setValidator(new QRegExpValidator(realRegExp, this));
  numMinorTicksEdit->setValidator(new QRegExpValidator(intRegExp, this));
  numMajorTicksEdit->setValidator(new QRegExpValidator(intRegExp, this));
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
