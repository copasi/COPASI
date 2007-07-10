// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.cpp,v $
//   $Revision: 1.66.2.2.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/07/10 18:30:38 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <sstream>
#include <mathematics.h>

#include <qhbox.h>
#include <qvbox.h>
#include <qlistbox.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qslider.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qobjectlist.h>
#include <qtooltip.h>
#include <qpopupmenu.h>
#include <qlayout.h>

#include "SliderDialog.h"
#include "copasiui3window.h"
#include "CQTrajectoryWidget.h"
#include "SteadyStateWidget.h"
#include "ScanWidget.h"
#include "SliderSettingsDialog.h"
#include "CQMessageBox.h"
#include "CopasiSlider.h"
#include "mathematics.h"
#include "qtUtilities.h"
#include "xml/CCopasiXMLInterface.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiProblem.h"
#include "report/CCopasiObjectName.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "scan/CScanTask.h"
#include "utilities/CSlider.h"
#include "model/CModel.h"

C_INT32 SliderDialog::numMappings = 7;
C_INT32 SliderDialog::folderMappings[][2] = {
      {21, 21}, {211, 21}, {23, 23}, {231, 23}, {24, 24} , {241, 24} , {31, 31}
    };

C_INT32 SliderDialog::numKnownTasks = 4;
C_INT32 SliderDialog::knownTaskIDs[] = {21, 23, 24, 31};
char* SliderDialog::knownTaskNames[] = {"Steady State", "Time Course", "MCA" , "Scan"};

SliderDialog::SliderDialog(QWidget* parent, const char* name, bool modal, WFlags fl):
    QDialog(parent, name, modal, fl),
    pParentWindow(NULL),
    runTaskButton(NULL),
    newSliderButton(NULL),
    autoRunCheckBox(NULL),
    mpAutoModifyRangesCheckBox(NULL),
    scrollView(NULL),
    sliderBox(NULL),
    contextMenu(NULL),
    currSlider(NULL),
    currentFolderId(0),
    mSliderValueChanged(false),
    mSliderPressed(false)
{
  setWFlags(getWFlags() | WStyle_StaysOnTop);
  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setMargin(5);
  QHBoxLayout* layout2 = new QHBoxLayout(0);
  layout2->setMargin(3);
  layout2->addStretch();
  newSliderButton = new QPushButton(this);
  newSliderButton->setText("new slider");
  newSliderButton->setEnabled(true);
  layout2->addWidget(newSliderButton);
  layout2->addStretch();
  mainLayout->addLayout(layout2);

  scrollView = new QScrollView(this);
  scrollView->setResizePolicy(QScrollView::AutoOneFit);
  sliderBox = new QVBox(0);
  sliderBox->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  sliderBox->layout()->setAutoAdd(false);
  scrollView->addChild(sliderBox);
  mainLayout->addWidget(scrollView);

  QHBoxLayout* layout1 = new QHBoxLayout(0);
  layout1->addStretch();
  mpAutoModifyRangesCheckBox = new QCheckBox(this);
  mpAutoModifyRangesCheckBox->setChecked(true);
  mpAutoModifyRangesCheckBox->setText("update ranges");
  layout1->addWidget(mpAutoModifyRangesCheckBox);
  layout1->addStretch();
  mainLayout->addSpacing(10);
  mainLayout->addLayout(layout1);

  layout1 = new QHBoxLayout(0);
  layout1->addStretch();
  autoRunCheckBox = new QCheckBox(this);
  autoRunCheckBox->setChecked(true);
  autoRunCheckBox->setText("update automatically");
  layout1->addWidget(autoRunCheckBox);
  layout1->addStretch();
  mainLayout->addSpacing(10);
  mainLayout->addLayout(layout1);

  layout2 = new QHBoxLayout(0);
  layout2->addStretch();
  runTaskButton = new QPushButton(this);
  runTaskButton->setText("run task");
  runTaskButton->setEnabled(true);
  layout2->addWidget(runTaskButton);
  layout2->addStretch();
  mainLayout->addLayout(layout2);

  contextMenu = new QPopupMenu(this);
  contextMenu->insertItem("Add New Slider", this, SLOT(createNewSlider()));
  contextMenu->insertItem("Remove Slider", this, SLOT(removeSlider()));
  contextMenu->insertItem("Edit Slider", this, SLOT(editSlider()));
  contextMenu->insertItem("Reset Value", this, SLOT(resetValue()));
  contextMenu->insertItem("Set new default value", this, SLOT(setDefault()));

  sliderMap[ -1].push_back(new QLabel("<p>There are no sliders available for this task. If you select one of the tasks that supports sliders in the copasi object tree, this dialog will become active.</p>", sliderBox));

  taskMap[23] = &SliderDialog::runTimeCourse;
  taskMap[21] = &SliderDialog::runSteadyStateTask;
  taskMap[31] = &SliderDialog::runScanTask;

  connect(runTaskButton, SIGNAL(clicked()), this, SLOT(runTask()));
  connect(newSliderButton, SIGNAL(clicked()), this, SLOT(createNewSlider()));
  setCurrentFolderId(-1);
  init();
}

void SliderDialog::contextMenuEvent(QContextMenuEvent* e)
{
  CopasiSlider* pSlider = findCopasiSliderAtPosition(e->pos());
  if (pSlider)
    {
      contextMenu->setItemEnabled(contextMenu->idAt(0), false);
      contextMenu->setItemEnabled(contextMenu->idAt(1), true);
      contextMenu->setItemEnabled(contextMenu->idAt(2), true);
      setCurrentSlider(pSlider);
    }
  else
    {
      contextMenu->setItemEnabled(contextMenu->idAt(0), true);
      contextMenu->setItemEnabled(contextMenu->idAt(1), false);
      contextMenu->setItemEnabled(contextMenu->idAt(2), false);
    }
  contextMenu->popup(e->globalPos());
}

void SliderDialog::setCurrentSlider(CopasiSlider* pSlider)
{
  currSlider = pSlider;
  if (currSlider)
    {
      currSlider->setFocus();
    }
}

CopasiSlider* SliderDialog::findCopasiSliderAtPosition(const QPoint& p)
{
  QWidget* pWidget = childAt(p);
  CopasiSlider* pSlider = NULL;
  while (pWidget && pWidget != this && !pSlider)
    {
      pSlider = dynamic_cast<CopasiSlider*>(pWidget);
      pWidget = (QWidget*)pWidget->parent();
    }
  return pSlider;
}

void SliderDialog::createNewSlider()
{
  SliderSettingsDialog* pSettingsDialog = new SliderSettingsDialog(this);
  pSettingsDialog->setModel(CCopasiDataModel::Global->getModel());
  // set the list of sliders that is already known
  std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
  pSettingsDialog->setDefinedSliders(*pVector);

  if (pSettingsDialog->exec() == QDialog::Accepted)
    {
      CSlider* pCSlider = pSettingsDialog->getSlider();
      if (pCSlider)
        {
          if (equivalentSliderExists(pCSlider))
            {
              CQMessageBox::information(NULL, "Slider Exists",
                                        "A slider for this object already exists. Please edit the corresponding slider.",
                                        QMessageBox::Ok | QMessageBox::Default , QMessageBox::NoButton);
              delete pCSlider;
            }
          else
            addSlider(pCSlider);
        }
    }
  else
    {
      setCurrentSlider(NULL);
    }

  delete pSettingsDialog;
  delete pVector;
}

void SliderDialog::removeSlider()
{
  if (currSlider)
    {
      CCopasiVector<CSlider>* pSliderList = CCopasiDataModel::Global->getGUI()->pSliderList;
      unsigned int i, maxCount = pSliderList->size();
      for (i = 0; i < maxCount;++i)
        {
          CSlider* pTmpSlider = (*pSliderList)[i];
          if (pTmpSlider == currSlider->getCSlider())
            {
              pSliderList->remove(i);
              break;
            }
        }
      deleteSlider(currSlider);
      currSlider = NULL;
    }
}

void SliderDialog::deleteSlider(CopasiSlider* pSlider)
{
  if (pSlider)
    {
      std::vector<QWidget*>* v = &sliderMap[currentFolderId];
      std::vector<QWidget*>::iterator it = v->begin();
      std::vector<QWidget*>::iterator end = v->end();
      while (it != end)
        {
          if (*it == pSlider)
            {
              break;
            }
          ++it;
        }
      assert(it != end);
      v->erase(it);
      ((QVBoxLayout*)sliderBox->layout())->remove(pSlider);
      pdelete(pSlider);
    }
}

void SliderDialog::editSlider()
{
  SliderSettingsDialog* pSettingsDialog = new SliderSettingsDialog(this);
  pSettingsDialog->setModel(CCopasiDataModel::Global->getModel());
  // set the list of sliders that is already known
  CCopasiObject* object = (CCopasiObject*)getTaskForFolderId(currentFolderId);
  if (!object) return;
  std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
  pSettingsDialog->setDefinedSliders(*pVector);

  //pSettingsDialog->disableObjectChoosing(true);

  pSettingsDialog->setSlider(currSlider->getCSlider());
  if (pSettingsDialog->exec() == QDialog::Accepted)
    {
      addSlider(pSettingsDialog->getSlider());
      currSlider->updateSliderData();
      /*
      if ((!currSlider->isEnabled()) && currSlider->getCSlider()->compile())
        {
          currSlider->setEnabled(true);
        }
        */
    }
  delete pSettingsDialog;
  delete pVector;
}

SliderDialog::~SliderDialog()
{
  delete runTaskButton;
  delete autoRunCheckBox;
  delete mpAutoModifyRangesCheckBox;
  delete sliderBox;
  delete scrollView;
  unsigned int i, j, maxWidgets, maxVectors = sliderMap.size();
  for (i = 0; i < maxVectors;++i)
    {
      std::vector<QWidget*> v = sliderMap[i];
      maxWidgets = v.size();
      for (j = 0; j < maxWidgets;++j)
        {
          pdelete(v[j]);
        }
    }
}

void SliderDialog::init()
{}

void SliderDialog::addSlider(CSlider* pSlider)
{
  // check if there already is a slider for this  object
  SCopasiXMLGUI* pGUI = CCopasiDataModel::Global->getGUI();
  assert(pGUI);
  if (!equivalentSliderExists(pSlider))
    {
      pGUI->pSliderList->add(pSlider, true);
    }
  CopasiSlider* tmp = findCopasiSliderForCSlider(pSlider);
  if (!tmp)
    {
      setCurrentSlider(new CopasiSlider(pSlider, sliderBox));
      currSlider->installEventFilter(this);
      currSlider->setHidden(true);
      currSlider->updateSliderData();
      sliderMap[currentFolderId].push_back(currSlider);
      ((QVBoxLayout*)sliderBox->layout())->add(currSlider);
      connect(currSlider, SIGNAL(valueChanged(double)), this , SLOT(sliderValueChanged()));
      connect(currSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
      connect(currSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
      connect(currSlider, SIGNAL(closeClicked(CopasiSlider*)), this, SLOT(removeSlider(CopasiSlider*)));
      connect(currSlider, SIGNAL(editClicked(CopasiSlider*)), this, SLOT(editSlider(CopasiSlider*)));
      currSlider->setHidden(false);
    }
  else
    {
      currSlider = tmp;
    }
}

CSlider* SliderDialog::equivalentSliderExists(CSlider* pCSlider)
{
  CSlider* pResult = NULL;
  SCopasiXMLGUI* pGUI = CCopasiDataModel::Global->getGUI();
  assert(pGUI);
  unsigned i, maxCount = pGUI->pSliderList->size();
  for (i = 0; i < maxCount;++i)
    {
      CSlider* pTmpSlider = (*(pGUI->pSliderList))[i];
      if (pTmpSlider->getSliderObject() == pCSlider->getSliderObject() && pTmpSlider->getAssociatedEntityKey() == pCSlider->getAssociatedEntityKey())
        {
          pResult = pTmpSlider;
          break;
        }
    }
  return pResult;
}

CopasiSlider* SliderDialog::findCopasiSliderForCSlider(CSlider* pCSlider)
{
  CopasiSlider* pResult = NULL;
  std::vector<QWidget*> v = sliderMap[currentFolderId];
  unsigned int i, maxCount = v.size();
  CopasiSlider* pTmpSlider;
  for (i = 0; i < maxCount;++i)
    {
      pTmpSlider = dynamic_cast<CopasiSlider*>(v[i]);
      if (!pTmpSlider) break;
      if (pTmpSlider->getCSlider() == pCSlider)
        {
          pResult = pTmpSlider;
          break;
        }
    }
  return pResult;
}

void SliderDialog::setCurrentFolderId(C_INT32 id)
{
  id = mapFolderId2EntryId(id);
  if (id == currentFolderId) return;
  if (id == -1)
    {
      setEnabled(false);
    }
  else
    {
      setEnabled(true);
    }

  clearSliderBox();

  currentFolderId = id;

  fillSliderBox();
}

void SliderDialog::fillSliderBox()
{
  std::vector<QWidget*> v = sliderMap[currentFolderId];
  if (currentFolderId != -1)
    {
      std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
      // maybe other program parts have added or deleted some sliders
      assert(pVector);
      unsigned int i, j, maxSliders, maxWidgets;
      maxWidgets = v.size();
      maxSliders = pVector->size();
      SCopasiXMLGUI* pGUI = CCopasiDataModel::Global->getGUI();
      assert(pGUI);
      // add CopasiSlider for all CSliders that don't have one.
      bool issueWarning = false;
      for (i = 0; i < maxSliders;++i)
        {
          bool found = false;
          if (!(*pVector)[i]->compile())
            {
              issueWarning = true;
            }
          for (j = 0; j < maxWidgets; j++)
            {
              CopasiSlider* pTmpSlider = dynamic_cast<CopasiSlider*>(v[j]);
              if (!pTmpSlider) break;
              if (pTmpSlider->getCSlider() == (*pVector)[i])
                {
                  found = true;
                  break;
                }
            }
          if (!found)
            {
              setCurrentSlider(new CopasiSlider((*pVector)[i], sliderBox));
              connect(currSlider, SIGNAL(valueChanged(double)), this , SLOT(sliderValueChanged()));
              connect(currSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
              connect(currSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
              connect(currSlider, SIGNAL(closeClicked(CopasiSlider*)), this, SLOT(removeSlider(CopasiSlider*)));
              connect(currSlider, SIGNAL(editClicked(CopasiSlider*)), this, SLOT(editSlider(CopasiSlider*)));
              currSlider->installEventFilter(this);
              currSlider->setHidden(true);
              sliderMap[currentFolderId].push_back(currSlider);
            }
        }
      // delete CopasiSliders which have no correponding CSlider
      for (j = 0; j < maxWidgets;++j)
        {
          bool found = false;
          for (i = 0; i < maxSliders; i++)
            {
              CopasiSlider* pTmpSlider = dynamic_cast<CopasiSlider*>(v[j]);
              if (!pTmpSlider) break;
              if (pTmpSlider->getCSlider() == (*pVector)[i])
                {
                  found = true;
                  break;
                }
            }
          if (!found)
            {
              CopasiSlider* pTmpSlider = dynamic_cast<CopasiSlider*>(v[j]);
              assert(pTmpSlider);
              deleteSlider(pTmpSlider);
            }
        }
      if (issueWarning)
        {
          CQMessageBox::information(NULL, "Invalid Slider",
                                    "One or more sliders are invalid and have been disabled!",
                                    QMessageBox::Ok, QMessageBox::NoButton);
        }

      delete pVector;
    }
  v = sliderMap[currentFolderId];
  unsigned int i, maxCount = v.size();
  for (i = maxCount; i != 0;--i)
    {
      QWidget* widget = v[i - 1];
      widget->setHidden(true);
      ((QVBoxLayout*)sliderBox->layout())->insertWidget(0, widget);
      setCurrentSlider(dynamic_cast<CopasiSlider*>(widget));
      if (currSlider)
        {
          currSlider->updateSliderData();
        }
      widget->setHidden(false);
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
  if (taskMap.find(currentFolderId) != taskMap.end())
    {
      setEnabled(false);
      updateAllSliders();
      ((this)->*(taskMap[currentFolderId]))();
      updateAllSliders();
      setEnabled(true);
    }
}

void SliderDialog::sliderValueChanged()
{
  mSliderValueChanged = true;
  if ((!mSliderPressed) && autoRunCheckBox->isChecked())
    {
      //runTask();
      mSliderValueChanged = false;
    }
}

void SliderDialog::sliderReleased()
{
  if (mSliderValueChanged && autoRunCheckBox->isChecked())
    {
      runTask();
      mSliderValueChanged = false;
    }
  mSliderPressed = false;
}

void SliderDialog::sliderPressed()
{
  mSliderPressed = true;
}

void SliderDialog::runTimeCourse()
{
  if (pParentWindow)
    {
      pParentWindow->getTrajectoryWidget()->enter((*CCopasiDataModel::Global->getTaskList())["Time-Course"]->getKey());
      pParentWindow->getTrajectoryWidget()->runTask();
    }
}

void SliderDialog::runSteadyStateTask()
{
  if (pParentWindow)
    {
      pParentWindow->getSteadyStateWidget()->runTask();
    }
}

void SliderDialog::runScanTask()
{
  if (pParentWindow)
    {
      pParentWindow->getScanWidget()->enter((*CCopasiDataModel::Global->getTaskList())["Scan"]->getKey());
      pParentWindow->getScanWidget()->runTask();
    }
}

void SliderDialog::closeEvent(QCloseEvent* e)
{
  QDialog::closeEvent(e);
  if (pParentWindow)
    {
      pParentWindow->slotToggleSliders();
    }
}

CCopasiTask* SliderDialog::getTaskForFolderId(C_INT32 folderId)
{
  folderId = mapFolderId2EntryId(folderId);
  CCopasiTask* task = NULL;
  switch (folderId)
    {
    case 21:
      task = dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
      break;
    case 23:
      task = dynamic_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);
      break;
    case 24:
      task = dynamic_cast<CMCATask *>((*CCopasiDataModel::Global->getTaskList())["Metabolic Control Analysis"]);
      break;
    case 31:
      task = dynamic_cast<CScanTask *>((*CCopasiDataModel::Global->getTaskList())["Scan"]);
      break;
    default:
      task = NULL;
      break;
    }
  return task;
}

void SliderDialog::updateAllSliders()
{
  if (currentFolderId == -1) return;

  bool autoModify = mpAutoModifyRangesCheckBox->isChecked();
  std::vector<QWidget*> v = sliderMap[currentFolderId];
  unsigned int i, maxCount = v.size();
  for (i = 0; i < maxCount;++i)
    {
      CopasiSlider* pCopasiSlider = dynamic_cast<CopasiSlider*>(v[i]);
      if (pCopasiSlider)
        {
          pCopasiSlider->updateValue(autoModify);
        }
    }
}

void SliderDialog::removeSlider(CopasiSlider* slider)
{
  setCurrentSlider(slider);
  removeSlider();
}

void SliderDialog::editSlider(CopasiSlider* slider)
{
  setCurrentSlider(slider);
  editSlider();
}

std::vector<CSlider*>* SliderDialog::getCSlidersForObject(CCopasiObject* pObject, std::vector<CSlider*>* pVector) const
  {
    SCopasiXMLGUI* pGUI = CCopasiDataModel::Global->getGUI();
    assert(pGUI);
    bool sliderDeleted = false;
    CCopasiVector<CSlider>* pSliderList = pGUI->pSliderList;
    assert(pSliderList);
    // go through the list in reverse so that items can be deleted
    unsigned int i, iMax = pSliderList->size();
    bool issueWarning = false;
    for (i = iMax;i > 0;--i)
      {
        CSlider* pSlider = (*pSliderList)[i - 1];
        if (sliderObjectChanged(pSlider))
          {
            if (!sliderDeleted)
              {
                CQMessageBox::information(NULL, "Missing slider objects",
                                          "One or more objects that had sliders defined have been deleted. Sliders will therefore be deleted as well.",
                                          QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
              }
            pSliderList->remove(i - 1);
            sliderDeleted = true;
          }
        else
          {
            if (pSlider->getAssociatedEntityKey() == CCopasiDataModel::Global->getModel()->getKey() || pSlider->getAssociatedEntityKey() == pObject->getKey())
              {
                if (!pSlider->compile())
                  {
                    issueWarning = true;
                  }
                pVector->insert(pVector->begin(), pSlider);
              }
          }
      }
    return pVector;
  }

void SliderDialog::clearSliderBox()
{
  std::vector<QWidget*> v = sliderMap[currentFolderId];
  unsigned int i, maxCount = v.size();
  for (i = 0; i < maxCount;++i)
    {
      QWidget* widget = v[i];
      widget->setHidden(true);
      ((QVBoxLayout*)sliderBox->layout())->remove(widget);
    }
}

std::vector<CSlider*>* SliderDialog::getCSlidersForCurrentFolderId()
{
  CCopasiObject* object = (CCopasiObject*)getTaskForFolderId(currentFolderId);
  if (!object) return NULL;
  std::vector<CSlider*>* pVector = new std::vector<CSlider*>();
  pVector = getCSlidersForObject(object, pVector);
  return pVector;
}

bool SliderDialog::eventFilter(QObject*, QEvent* event)
{
  QMouseEvent* pQME = dynamic_cast<QMouseEvent*>(event);
  if (pQME && pQME->type() == QEvent::MouseButtonPress && pQME->button() == Qt::LeftButton)
    {
      CopasiSlider* pSlider = findCopasiSliderAtPosition(mapFromGlobal(pQME->globalPos()));
      assert(pSlider);
      setCurrentSlider(pSlider);
    }
  return false;
}

void SliderDialog::resetValue()
{
  currSlider->resetValue();
}

void SliderDialog::setDefault()
{
  currSlider->setOriginalValue(currSlider->value());
}

bool SliderDialog::sliderObjectChanged(CSlider* pSlider) const
  {
    CModel* pModel = CCopasiDataModel::Global->getModel();
    std::vector<CCopasiContainer*> listOfContainers;
    listOfContainers.push_back(pModel);
    return !pSlider->compile(listOfContainers);
  }

void SliderDialog::setParentWindow(CopasiUI3Window* pPW)
{
  pParentWindow = pPW;
}
