/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:51 $
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
#include "qobjectlist.h"
#include "qtooltip.h"
#include "qpopupmenu.h"
#include "report/CCopasiObject.h"
#include "model/CCompartment.h"
#include "report/CCopasiObjectName.h"
#include <iostream>
#include <sstream>

#include "mathematics.h"

#include "report/CCopasiObjectReference.h"

C_INT32 SliderDialog::numMappings = 2;
C_INT32 SliderDialog::folderMappings[][2] = {
      {23, 23}, {231, 23}
    };

SliderDialog::SliderDialog(QWidget* parent): QDialog(parent),
    runTaskButton(NULL),
    autoRunCheckBox(NULL),
    scrollView(NULL),
    sliderBox(NULL),
    contextMenu(NULL),
    currSlider(NULL),
    currentFolderId(0)
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

  this->contextMenu = new QPopupMenu(this);
  this->contextMenu->insertItem("Add New Slider", this, SLOT(createNewSlider()));
  this->contextMenu->insertItem("Remove Slider", this, SLOT(removeSlider()));
  this->contextMenu->insertItem("Edit Slider", this, SLOT(editSlider()));

  connect(autoRunCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleRunButtonState(bool)));
  this->sliderMap[23] = std::vector< CopasiSlider* >();
  this->setCurrentFolderId(-1);
  this->init();
}

void SliderDialog::contextMenuEvent(QContextMenuEvent* e)
{
  QWidget* widget = this->childAt(e->pos());
  if (dynamic_cast<QLabel*>(widget) || dynamic_cast<QSlider*>(widget))
    {
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(1), true);
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(2), true);
      this->currSlider = dynamic_cast<CopasiSlider*>(widget->parent());
    }
  else
    {
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(1), false);
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(2), false);
    }
  this->contextMenu->popup(e->globalPos());
}

void SliderDialog::createNewSlider()
{
  this->currSlider = NULL;
}

void SliderDialog::removeSlider()
{
  if (this->currSlider)
    {
      std::vector<CopasiSlider*>::iterator it = this->sliderMap[this->currentFolderId].begin();
      std::vector<CopasiSlider*>::iterator endPos = this->sliderMap[this->currentFolderId].end();
      while (it != endPos)
        {
          if ((*it) == this->currSlider)
            {
              this->sliderMap[this->currentFolderId].erase(it);
              break;
            }
          ++it;
        }
      this->sliderBox->layout()->remove(this->currSlider);
      delete this->currSlider;
      this->currSlider = NULL;
    }
}

void SliderDialog::editSlider()
{
  this->currSlider = NULL;
}

void SliderDialog::toggleRunButtonState(bool notState)
{
  this->runTaskButton->setEnabled(!notState);
}

SliderDialog::~SliderDialog()
{
  std::map<C_INT32, std::vector< CopasiSlider* > >::iterator it = this->sliderMap.begin();
  std::map<C_INT32, std::vector< CopasiSlider* > >::iterator endPos = this->sliderMap.end();
  while (it != endPos)
    {
      std::vector<CopasiSlider*>::iterator it2 = it->second.begin();
      std::vector<CopasiSlider*>::iterator endPos2 = it->second.end();
      while (it2 != endPos2)
        {
          delete (*it2);
          ++it2;
        }
      ++it;
    }
  delete this->runTaskButton;
  delete this->autoRunCheckBox;
  delete this->sliderBox;
  delete this->scrollView;
}

void SliderDialog::init()
{
  CCompartment* comp = new CCompartment();
  comp->setVolume(1.0);
  CCopasiObject* o = (CCopasiObject*)comp->getObject(CCopasiObjectName("Reference=Volume"));
  this->addSlider(o, 23);
}

void SliderDialog::addSlider(CCopasiObject* object, C_INT32 folderId)
{
  // check if there already is a slider for this  object
  unsigned int counter;
  unsigned int maxCount = this->sliderMap[this->currentFolderId].size();
  bool found = false;
  for (counter = 0; counter < maxCount;++counter)
    {
      if (object == this->sliderMap[this->currentFolderId][counter]->object())
        {
          found = true;
          break;
        }
    }
  if (folderId == -1 || found) return;
  CopasiSlider* cslider = new CopasiSlider(object, this->sliderBox);
  cslider->setHidden(true);
  this->sliderMap[folderId].push_back(cslider);
  if (folderId == this->currentFolderId)
    {
      ((QVBoxLayout*)this->sliderBox->layout())->insertWidget(this->sliderBox->children()->count() - 2, cslider);
      cslider->setHidden(false);
    }
}

void SliderDialog::setCurrentFolderId(C_INT32 id)
{
  id = this->mapFolderId2EntryId(id);
  if (id == this->currentFolderId) return;
  if (id == -1)
    {
      this->setEnabled(false);
    }
  else
    {
      this->setEnabled(true);
      // remove all slider objects from the layout
      unsigned int counter;
      unsigned int maxCount = this->sliderMap[this->currentFolderId].size();
      for (counter = 0; counter < maxCount;++counter)
        {
          CopasiSlider* s = this->sliderMap[this->currentFolderId][counter];
          s->setHidden(true);
          this->sliderBox->layout()->remove(s);
        }
      this->currentFolderId = id;
      // add the new set of sliders to the layout
      maxCount = this->sliderMap[this->currentFolderId].size();
      for (counter = 0; counter < maxCount;++counter)
        {
          CopasiSlider* s = this->sliderMap[this->currentFolderId][counter];
          // check if any object values have changed and set the slider
          // accordingly if possible
          if (!(s->ensureConsistency()))
            {
              s->setEnabled(false);
            }
          s->setHidden(false);
          ((QVBoxLayout*)this->sliderBox->layout())->insertWidget(this->sliderBox->children()->count() - 2, s);
        }
    }
}

C_INT32 SliderDialog::mapFolderId2EntryId(C_INT32 folderId) const
  {
    C_INT32 id = -1;
    int counter;
    for (counter = 0; counter < SliderDialog::numMappings;++counter)
      {
        if (SliderDialog::folderMappings[counter][0] == folderId)
          {
            id = SliderDialog::folderMappings[counter][1];
            break;
          }
      }
    return id;
  }

/* ----------------- CopasiSlider ----------------*/

CopasiSlider::CopasiSlider(CCopasiObject* object, QWidget* parent): QVBox(parent), cobject(object), typeVar(undefined), minValueVar(0.0), maxValueVar(0.0), factorVar(1.0), slider(NULL), label(NULL)
{
  this->label = new QLabel(this);
  this->label->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  this->slider = new QSlider(Qt::Horizontal, this);
  this->slider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  this->updateSliderData();

  connect(this->slider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
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
      double value = 0.0;
      if (this->cobject->isValueDbl())
        {
          value = *(double*)(((CCopasiObjectReference<C_FLOAT64>*)this->cobject)->getReference());
        }
      else if (this->cobject->isValueInt())
        {
          //value = *(int*)this->cobject->getReference();
          value = *(int*)(((CCopasiObjectReference<C_INT32>*)this->cobject)->getReference());
        }
      this->minValueVar = 0.0;
      this->maxValueVar = 2.0 * value;
      this->factorVar = value / 5.0;
      this->slider->setMinValue(0);
      this->slider->setMaxValue((int)floor((this->maxValueVar / this->factorVar) + 0.5));
      this->slider->setTickInterval(1);
      this->slider->setValue((int)floor((value / this->factorVar) + 0.5));
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
  this->slider->setValue((int)floor(((value - this->minValueVar) / this->factorVar) + 0.5));
  if (this->typeVar == intType)
    {
      int* reference = (int*)(((CCopasiObjectReference<C_INT32>*)this->cobject)->getReference());

      *reference = (int)floor(value + 0.5);
    }
  else if (this->typeVar == doubleType)
    {
      double* reference = (double*)(((CCopasiObjectReference<C_FLOAT64>*)this->cobject)->getReference());

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
  this->slider->setMaxValue(this->slider->minValue() + (int)floor(numTicks + 0.5));
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
  this->slider->setMaxValue((int)floor(numTicks + 0.5));
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
  this->slider->setMaxValue((int)floor(numTicks + 0.5));
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
  this->label->setText(labelString.c_str());
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
      int* reference = (int*)(((CCopasiObjectReference<C_INT32>*)this->cobject)->getReference());

      *reference = (int)floor(v + 0.5);
    }
  else if (this->typeVar == doubleType)
    {
      double* reference = (double*)(((CCopasiObjectReference<C_FLOAT64>*)this->cobject)->getReference());

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

bool CopasiSlider::ensureConsistency()
{
  bool success = true;
  double objectValue;
  // check if the slider setting reflects the value of the object with some
  // small tolerance that depends on the range of the slider.
  // if the error is smaller than the size of the ticks, leave it.
  if (this->typeVar == intType)
    {
      int* reference = (int*)(((CCopasiObjectReference<C_INT32>*)this->cobject)->getReference());

      objectValue = (double)(*reference);
    }
  else if (this->typeVar == doubleType)
    {
      double* reference = (double*)(((CCopasiObjectReference<C_FLOAT64>*)this->cobject)->getReference());
      objectValue = *reference;
    }
  double difference = fabs(objectValue - this->value());
  if (difference > (this->factorVar / 2.0))
    {
      // If the slider value and the object value differ, see if the object value
      // is within the range of the slider and set it, else return false
      if ((objectValue > (this->minValueVar - (this->factorVar / 2.0))) && (objectValue < this->maxValueVar + (this->factorVar / 2.0)))
        {
          // adjust slider value setting
          int tick = (int)floor(((objectValue - this->minValueVar) / this->factorVar) + 0.5);
          if (tick < 0) tick = 0;
          if (tick > this->slider->maxValue()) tick = this->slider->maxValue();
          this->slider->setValue(tick);
        }
      else
        {
          // could not update settings without changing the range of the
          // slider
          success = false;
        }
    }

  return success;
}
