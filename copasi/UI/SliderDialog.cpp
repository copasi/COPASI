/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/11/05 16:18:39 $
   End CVS Header */

#include <iostream>
#include <sstream>
#include <mathematics.h>

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

#include "SliderDialog.h"
#include "copasiui3window.h"
#include "TrajectoryWidget.h"
#include "slidersettingsdialog.h"
#include "DataModelGUI.h"
#include "CopasiSlider.h"
#include "mathematics.h"

#include "qtUtilities.h"

C_INT32 SliderDialog::numMappings = 2;
C_INT32 SliderDialog::folderMappings[][2] = {
      {23, 23}, {231, 23}
    };

C_INT32 SliderDialog::numKnownTasks = 1;
C_INT32 SliderDialog::knownTaskIDs[] = {23};
char* SliderDialog::knownTaskNames[] = {"Time Course"};

SliderDialog::SliderDialog(QWidget* parent, DataModelGUI* dataModel): QDialog(parent),
    runTaskButton(NULL),
    autoRunCheckBox(NULL),
    scrollView(NULL),
    sliderBox(NULL),
    contextMenu(NULL),
    currSlider(NULL),
    currentFolderId(0),
    mpDataModel(dataModel)
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
  connect(runTaskButton, SIGNAL(clicked()), this, SLOT(runTask()));
  this->sliderMap[23] = std::vector< CopasiSlider* >();
  this->taskMap[23] = &SliderDialog::runTimeCourse;
  this->setCurrentFolderId(-1);
  this->init();
}

void SliderDialog::setDataModel(DataModelGUI* dataModel)
{
  this->mpDataModel = dataModel;
}

void SliderDialog::contextMenuEvent(QContextMenuEvent* e)
{
  QWidget* widget = this->childAt(e->pos());
  if (dynamic_cast<QLabel*>(widget) || dynamic_cast<QSlider*>(widget))
    {
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(0), false);
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(1), true);
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(2), true);
      this->currSlider = dynamic_cast<CopasiSlider*>(widget->parent());
    }
  else
    {
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(0), true);
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(1), false);
      this->contextMenu->setItemEnabled(this->contextMenu->idAt(2), false);
    }
  this->contextMenu->popup(e->globalPos());
}

void SliderDialog::createNewSlider()
{
  SliderSettingsDialog* pSettingsDialog = new SliderSettingsDialog(this);
  pSettingsDialog->setModel(this->mpDataModel->getModel());
  // set the list of sliders that is already known
  pSettingsDialog->setDefinedSliders(this->sliderMap[this->currentFolderId]);

  if (pSettingsDialog->exec() == QDialog::Accepted)
    {
      this->currSlider = pSettingsDialog->getSlider();
      if (this->currSlider)
        {
          std::vector<CopasiSlider*>::iterator it = this->sliderMap[this->currentFolderId].begin();
          std::vector<CopasiSlider*>::iterator endPos = this->sliderMap[this->currentFolderId].end();
          bool found = false;
          while (it != endPos)
            {
              if ((*it) == this->currSlider)
                {
                  found = true;
                  break;
                }
              ++it;
            }
          if (!found)
            {
              // add the new slider
              this->addSlider(this->currSlider, this->currentFolderId);
            }
          else
            {
              // update the slider
              this->currSlider->update();
            }
        }
    }
  else
    {
      this->currSlider = NULL;
    }
  delete pSettingsDialog;
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
  SliderSettingsDialog* pSettingsDialog = new SliderSettingsDialog(this);
  pSettingsDialog->setModel(this->mpDataModel->getModel());
  // set the list of sliders that is already known
  pSettingsDialog->setDefinedSliders(this->sliderMap[this->currentFolderId]);

  pSettingsDialog->disableObjectChoosing(true);
  pSettingsDialog->setSlider(this->currSlider);
  pSettingsDialog->exec();
  delete pSettingsDialog;
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
{}

void SliderDialog::addSlider(CopasiSlider* slider, C_INT32 folderId)
{
  // check if there already is a slider for this  object
  unsigned int counter;
  unsigned int maxCount = this->sliderMap[this->currentFolderId].size();
  bool found = false;
  CCopasiObject* object = slider->object();
  for (counter = 0; counter < maxCount;++counter)
    {
      if (object == this->sliderMap[this->currentFolderId][counter]->object())
        {
          found = true;
          break;
        }
    }
  if (folderId == -1 || found) return;
  slider->reparent(this->sliderBox, 0, QPoint(0, 0));
  slider->setHidden(true);
  this->sliderMap[folderId].push_back(slider);
  if (folderId == this->currentFolderId)
    {
      ((QVBoxLayout*)this->sliderBox->layout())->insertWidget(this->sliderBox->children()->count() - 2, slider);
      slider->setHidden(false);
    }
  connect(slider, SIGNAL(valueChanged(double)), this , SLOT(sliderValueChanged()));
}

void SliderDialog::setCurrentFolderId(C_INT32 id)
{
  id = this->mapFolderId2EntryId(id);
  if (id == this->currentFolderId) return;
  if (id == -1)
    {
      this->currentFolderId = -1;
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

void SliderDialog::runTask()
{
  if (this->taskMap.find(this->currentFolderId) != this->taskMap.end())
    {
      this->setEnabled(false);
      ((this)->*(this->taskMap[this->currentFolderId]))();
      this->setEnabled(true);
    }
}

void SliderDialog::sliderValueChanged()
{
  if (this->autoRunCheckBox->isChecked())
    {
      this->runTask();
    }
}

void SliderDialog::runTimeCourse()
{
  CopasiUI3Window* p = dynamic_cast<CopasiUI3Window*>(this->parent());
  if (p)
    {
      p->getTrajectoryWidget()->runTrajectoryTask();
    }
}

void SliderDialog::closeEvent(QCloseEvent* e)
{
  QDialog::closeEvent(e);
  CopasiUI3Window* p = dynamic_cast<CopasiUI3Window*>(this->parent());
  if (p)
    {
      p->slotToggleSliders();
    }
}
