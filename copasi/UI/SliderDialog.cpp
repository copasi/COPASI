/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/01 14:50:51 $
   End CVS Header */

#include "SliderDialog.h"
#include "qhbox.h"
#include "qlistbox.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include "qstring.h"
#include "qslider.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qapplication.h"
#include "qfontmetrics.h"
#include "qpainter.h"
#include "qstyle.h"
#include "qobjectlist.h"
#include "qtooltip.h"
#include "report/CCopasiObject.h"
#include "model/CCompartment.h"
#include "report/CCopasiObjectName.h"
#include <iostream>
#include <sstream>

SliderDialog::SliderDialog(QWidget* parent): QDialog(parent),
    runTaskButton(NULL),
    autoRunCheckBox(NULL),
    scrollView(NULL),
    sliderBox(NULL)
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  this->scrollView = new QScrollView(this);
  this->scrollView->setResizePolicy(QScrollView::AutoOneFit);
  this->scrollView->setHScrollBarMode(QScrollView::AlwaysOff);
  this->sliderBox = new QVBox(0);
  this->sliderBox->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  this->sliderBox->layout()->setAutoAdd(false);
  ((QVBoxLayout*)this->sliderBox->layout())->addStretch();
  this->scrollView->addChild(this->sliderBox);
  mainLayout->addWidget(this->scrollView);

  QHBoxLayout* layout1 = new QHBoxLayout(0);
  layout1->addStretch();
  this->autoRunCheckBox = new QCheckBox(this);
  this->autoRunCheckBox->setChecked(true);
  this->autoRunCheckBox->setText("update automatically");
  layout1->addWidget(this->autoRunCheckBox);
  layout1->addStretch();
  mainLayout->addSpacing(10);
  mainLayout->addLayout(layout1);

  QHBoxLayout* layout2 = new QHBoxLayout(0);
  layout2->addStretch();
  this->runTaskButton = new QPushButton(this);
  this->runTaskButton->setText("run task");
  this->runTaskButton->setEnabled(false);
  layout2->addWidget(this->runTaskButton);
  layout2->addStretch();
  mainLayout->addLayout(layout2);

  connect(autoRunCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleRunButtonState(bool)));

  this->init();
}

void SliderDialog::toggleRunButtonState(bool notState)
{
  this->runTaskButton->setEnabled(!notState);
}

SliderDialog::~SliderDialog()
{
  delete this->runTaskButton;
  delete this->autoRunCheckBox;
  delete this->sliderBox;
  delete this->scrollView;
}

void SliderDialog::init()
{
  this->addSlider("Test Slider 1", 0, 10, 1);
  this->addSlider("Test Slider 2", 0, 10, 1);
  this->addSlider("Test Slider 3", 0, 10, 1);
  this->addSlider("Test Slider 4", 0, 10, 1);
  this->addSlider("Test Slider 5", 0, 10, 1);
}

void SliderDialog::addSlider(const QString& name, int min, int max, int tickInterval)
{
  /*
   CCompartment* comp=new CCompartment();
  comp->setVolume(100.0);
  CCopasiObject* o=comp->CCopasiContainer::getObject(CCopasiObjectName("Volume"));
  CopasiSlider* cslider=new CopasiSlider(o,this);
  */

  QVBox* box = new QVBox(this->sliderBox);
  ((QVBoxLayout*)this->sliderBox->layout())->insertWidget(this->sliderBox->children()->count() - 2, box);
  QLabel* label = new QLabel(name, box);
  label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  QSlider* slider = new QSlider(Qt::Horizontal, box);
  slider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  slider->setRange(min, max);
  slider->setValue((min + max) / 2);
  slider->setTickInterval(tickInterval);
}

CopasiSlider::CopasiSlider(CCopasiObject* object, QWidget* parent): QVBox(parent), cobject(object), typeVar(undefined), minValueVar(0.0), maxValueVar(0.0), factorVar(1.0), slider(NULL), label(NULL)
{
  this->label = new QLabel(this);
  this->slider = new QSlider(Qt::Horizontal, this);
  this->updateSliderData();
  connect(this->slider, SLOT(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
  std::cout << "Created copasi slider." << std::endl;
}

CopasiSlider::~CopasiSlider()
{
  delete this->slider;
  delete this->label;
}

void CopasiSlider::updateSliderData()
{
  if (this->cobject)
    {
      double value = *(double*)this->cobject->getReference();
      this->minValueVar = 0.0;
      this->maxValueVar = 2.0 * value;
      this->factorVar = value / 5.0;
      this->slider->setMinValue(0);
      this->slider->setMaxValue((int)this->maxValueVar);
      this->slider->setTickInterval(1);
      this->slider->setValue((int)this->minValueVar);
      if (this->cobject->isValueInt())
        {
          this->setType(intType);
          QToolTip::add(this->slider, "Int Tooltip");
        }
      else if (this->cobject->isValueDbl())
        {
          this->setType(doubleType);
          QToolTip::add(this->slider, "Double Tooltip");
        }
      else
        {
          this->setEnabled(false);
        }
    }
  this->updateLabel();
}

double CopasiSlider::value() const
  {
    return this->minValueVar + this->factorVar*this->slider->value();
  }

void CopasiSlider::setValue(double value)
{
  if (value < this->minValueVar)
    {
      value = this->minValueVar;
    }
  else if (value > this->maxValueVar)
    {
      value = this->maxValueVar;
    }
  this->slider->setValue((int)((value - this->minValueVar) / this->factorVar));
  if (this->typeVar == intType)
    {
      int* reference = (int*)this->cobject->getReference();

      *reference = (int)value;
    }
  else if (this->typeVar == doubleType)
    {
      double* reference = (double*)this->cobject->getReference();

      *reference = value;
    }
  this->updateLabel();
}

double CopasiSlider::tickInterval() const
  {
    return this->factorVar;
  }

void CopasiSlider::setTickInterval(double tickInterval)
{
  double numTicks = (this->maxValueVar - this->minValueVar) / tickInterval;
  this->factorVar = tickInterval;
  if ((numTicks / (int)numTicks) > 1.001)
    {
      numTicks = numTicks + 1.0;
    }
  this->maxValueVar = this->minValueVar + numTicks * this->factorVar;
  this->slider->setMaxValue(this->slider->minValue() + (int)numTicks);
}

double CopasiSlider::minValue() const
  {
    return this->minValueVar;
  }

double CopasiSlider::maxValue() const
  {
    return this->maxValueVar;
  }

CCopasiObject* CopasiSlider::object() const
  {
    return this->cobject;
  }

void CopasiSlider::setObject(CCopasiObject* object)
{
  this->cobject = object;
  this->updateSliderData();
}

void CopasiSlider::setMaxValue(double value)
{
  if (value <= minValueVar) return;
  double numTicks = (value - this->minValueVar) / this->factorVar;
  if ((numTicks / (int)numTicks) > 1.001)
    {
      numTicks = numTicks + 1.0;
    }
  this->slider->setMaxValue((int)numTicks);
  this->maxValueVar = this->minValueVar + this->factorVar * numTicks;
  if (this->value() > this->maxValueVar)
    {
      this->setValue(this->maxValueVar);
    }
  this->updateLabel();
}

void CopasiSlider::setMinValue(double value)
{
  if (value >= maxValueVar) return;
  double numTicks = (this->maxValueVar - value) / this->factorVar;
  if ((numTicks / (int)numTicks) > 1.001)
    {
      numTicks = numTicks + 1.0;
    }
  this->slider->setMaxValue((int)numTicks);
  this->minValueVar = value;
  this->setMaxValue(this->minValueVar + this->factorVar*numTicks);
  if (this->value() < this->minValueVar)
    {
      this->setValue(this->minValueVar);
    }
  this->updateLabel();
}

void CopasiSlider::updateLabel()
{
  std::string labelString = "";
  if (this->cobject)
    {
      labelString += this->cobject->getObjectName();
    }
  labelString += " : [";
  labelString += this->numberToString(this->minValueVar);
  labelString += "-";
  labelString += this->numberToString(this->maxValueVar);
  labelString += "] {";
  labelString += this->numberToString(this->value());
  labelString += "}";
  this->label->setText(labelString);
  std::cout << "Setting label string." << std::endl;
}

std::string CopasiSlider::numberToString(double number) const
  {
    std::ostringstream oss;
    oss << number;
    return oss.str();
  }

void CopasiSlider::sliderValueChanged(int value)
{
  double v = this->minValueVar + value * this->factorVar;
  if (this->typeVar == intType)
    {
      int* reference = (int*)this->cobject->getReference();

      *reference = (int)v;
    }
  else if (this->typeVar == doubleType)
    {
      double* reference = (double*)this->cobject->getReference();

      *reference = v;
    }
  this->updateLabel();
}

CopasiSlider::NumberType CopasiSlider::type() const
  {
    return this->typeVar;
  }

void CopasiSlider::setType(NumberType type)
{
  this->typeVar = type;
}
