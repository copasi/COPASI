// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.cpp,v $
//   $Revision: 1.79 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/07/27 13:33:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <sstream>
#include <mathematics.h>

//Added by qt3to4:
#include <QContextMenuEvent>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QMenu>
#include <QScrollArea>

#include "SliderDialog.h"
#include "copasiui3window.h"
#include "CQTrajectoryWidget.h"
#include "SteadyStateWidget.h"
#include "ScanWidget.h"
#include "CQMCAWidget.h"
#include "SliderSettingsDialog.h"
#include "CQMessageBox.h"
#include "CopasiSlider.h"
#include "mathematics.h"
#include "qtUtilities.h"
#include "xml/CCopasiXMLInterface.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
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
C_INT32 SliderDialog::folderMappings[][2] =
{
  {21, 21}, {211, 21}, {23, 23}, {231, 23}, {24, 24} , {241, 24} , {31, 31}
};

//C_INT32 SliderDialog::numKnownTasks = 4;
//C_INT32 SliderDialog::[] = {21, 23, 24, 31};
//const char* SliderDialog::knownTaskNames[] = {"Steady State", "Time Course", "MCA" , "Scan"};

SliderDialog::SliderDialog(QWidget* parent, const char* name, bool modal, Qt::WFlags fl):
    QDialog(parent, name, modal, fl),
    mpParentWindow(NULL),
    mpRunTaskButton(NULL),
    mpNewSliderButton(NULL),
    mpAutoRunCheckBox(NULL),
    mpAutoModifyRangesCheckBox(NULL),
    mpScrollView(NULL),
    mpSliderBox(NULL),
    mpContextMenu(NULL),
    mpCurrSlider(NULL),
    mCurrentFolderId(0),
    mSliderValueChanged(false),
    mSliderPressed(false)
{
  setWindowFlags(windowFlags() | Qt::WStyle_StaysOnTop);
  QVBoxLayout* pMainLayout = new QVBoxLayout(this);
  this->setLayout(pMainLayout);
  pMainLayout->setContentsMargins(5, 5, 5, 5);
  QHBoxLayout* pLayout2 = new QHBoxLayout(0);
  pLayout2->setContentsMargins(3, 3, 3, 3);
  pLayout2->addStretch();
  this->mpNewSliderButton = new QPushButton(0);
  this->mpNewSliderButton->setText("new slider");
  this->mpNewSliderButton->setEnabled(true);
  pLayout2->addWidget(this->mpNewSliderButton);
  pLayout2->addStretch();
  pMainLayout->addLayout(pLayout2);

  this->mpScrollView = new QScrollArea(0);
  this->mpSliderBox = new QFrame(0);
  QVBoxLayout* pLayout3 = new QVBoxLayout(0);
  this->mpSliderBox->setLayout(pLayout3);
  this->mpScrollView->setWidget(this->mpSliderBox);
  this->mpScrollView->setWidgetResizable(true);
  pMainLayout->addWidget(this->mpScrollView);

  QHBoxLayout* pLayout1 = new QHBoxLayout(0);
  pLayout1->addStretch();
  this->mpAutoModifyRangesCheckBox = new QCheckBox(0);
  this->mpAutoModifyRangesCheckBox->setChecked(true);
  this->mpAutoModifyRangesCheckBox->setText("update ranges");
  pLayout1->addWidget(this->mpAutoModifyRangesCheckBox);
  pLayout1->addStretch();
  pMainLayout->addSpacing(10);
  pMainLayout->addLayout(pLayout1);

  pLayout1 = new QHBoxLayout(0);
  pLayout1->addStretch();
  this->mpAutoRunCheckBox = new QCheckBox(0);
  this->mpAutoRunCheckBox->setChecked(true);
  this->mpAutoRunCheckBox->setText("update automatically");
  pLayout1->addWidget(this->mpAutoRunCheckBox);
  pLayout1->addStretch();
  pMainLayout->addSpacing(10);
  pMainLayout->addLayout(pLayout1);

  pLayout2 = new QHBoxLayout(0);
  pLayout2->addStretch();
  this->mpRunTaskButton = new QPushButton(0);
  this->mpRunTaskButton->setText("run task");
  this->mpRunTaskButton->setEnabled(true);
  pLayout2->addWidget(this->mpRunTaskButton);
  pLayout2->addStretch();
  pMainLayout->addLayout(pLayout2);

  this->mpContextMenu = new QMenu(this);
  this->mpContextMenu->insertItem("Add New Slider", this, SLOT(createNewSlider()));
  this->mpContextMenu->insertItem("Remove Slider", this, SLOT(removeSlider()));
  this->mpContextMenu->insertItem("Edit Slider", this, SLOT(editSlider()));
  this->mpContextMenu->insertItem("Reset Value", this, SLOT(resetValue()));
  this->mpContextMenu->insertItem("Set new default value", this, SLOT(setDefault()));

  this->mSliderMap[ -1].push_back(new QLabel("<p>There are no sliders available for this task. If you select one of the tasks that supports sliders in the copasi object tree, this dialog will become active.</p>", mpSliderBox));

  this->mTaskMap[23] = &SliderDialog::runTimeCourse;
  this->mTaskMap[21] = &SliderDialog::runSteadyStateTask;
  this->mTaskMap[31] = &SliderDialog::runScanTask;
  this->mTaskMap[24] = &SliderDialog::runMCATask;

  connect(this->mpRunTaskButton, SIGNAL(clicked()), this, SLOT(runTask()));
  connect(this->mpNewSliderButton, SIGNAL(clicked()), this, SLOT(createNewSlider()));
  this->setCurrentFolderId(-1);
  init();
}

void SliderDialog::contextMenuEvent(QContextMenuEvent* e)
{
  CopasiSlider* pSlider = findCopasiSliderAtPosition(e->pos());

  if (pSlider)
    {
      mpContextMenu->setItemEnabled(mpContextMenu->idAt(0), false);
      mpContextMenu->setItemEnabled(mpContextMenu->idAt(1), true);
      mpContextMenu->setItemEnabled(mpContextMenu->idAt(2), true);
      setCurrentSlider(pSlider);
    }
  else
    {
      mpContextMenu->setItemEnabled(mpContextMenu->idAt(0), true);
      mpContextMenu->setItemEnabled(mpContextMenu->idAt(1), false);
      mpContextMenu->setItemEnabled(mpContextMenu->idAt(2), false);
    }

  mpContextMenu->popup(e->globalPos());
}

void SliderDialog::setCurrentSlider(CopasiSlider* pSlider)
{
  mpCurrSlider = pSlider;

  if (mpCurrSlider)
    {
      mpCurrSlider->setFocus();
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
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  pSettingsDialog->setModel((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
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
  if (mpCurrSlider)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      CCopasiVector<CSlider>* pSliderList = (*CCopasiRootContainer::getDatamodelList())[0]->getGUI()->getSliderList();
      unsigned int i, maxCount = pSliderList->size();

      for (i = 0; i < maxCount; ++i)
        {
          CSlider* pTmpSlider = (*pSliderList)[i];

          if (pTmpSlider == mpCurrSlider->getCSlider())
            {
              pSliderList->remove(i);
              break;
            }
        }

      deleteSlider(mpCurrSlider);
      mpCurrSlider = NULL;
    }
}

void SliderDialog::deleteSlider(CopasiSlider* pSlider)
{
  if (pSlider)
    {
      std::vector<QWidget*>* v = &mSliderMap[mCurrentFolderId];
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
      ((Q3VBoxLayout*)mpSliderBox->layout())->remove(pSlider);
      pdelete(pSlider);
    }
}

void SliderDialog::editSlider()
{
  SliderSettingsDialog* pSettingsDialog = new SliderSettingsDialog(this);
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  pSettingsDialog->setModel((*CCopasiRootContainer::getDatamodelList())[0]->getModel());
  // set the list of sliders that is already known
  CCopasiObject* object = (CCopasiObject*)getTaskForFolderId(mCurrentFolderId);

  if (!object) return;

  std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
  pSettingsDialog->setDefinedSliders(*pVector);

  //pSettingsDialog->disableObjectChoosing(true);

  pSettingsDialog->setSlider(mpCurrSlider->getCSlider());

  if (pSettingsDialog->exec() == QDialog::Accepted)
    {
      addSlider(pSettingsDialog->getSlider());
      mpCurrSlider->updateSliderData();
      /*
      if ((!mpCurrSlider->isEnabled()) && mpCurrSlider->getCSlider()->compile())
        {
          mpCurrSlider->setEnabled(true);
        }
        */
    }

  delete pSettingsDialog;
  delete pVector;
}

SliderDialog::~SliderDialog()
{
  delete mpRunTaskButton;
  delete mpAutoRunCheckBox;
  delete mpAutoModifyRangesCheckBox;
  delete mpSliderBox;
  delete mpScrollView;
  unsigned int i, j, maxWidgets, maxVectors = mSliderMap.size();

  for (i = 0; i < maxVectors; ++i)
    {
      std::vector<QWidget*> v = mSliderMap[i];
      maxWidgets = v.size();

      for (j = 0; j < maxWidgets; ++j)
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
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  SCopasiXMLGUI* pGUI = (*CCopasiRootContainer::getDatamodelList())[0]->getGUI();
  assert(pGUI);

  if (!equivalentSliderExists(pSlider))
    {
      pGUI->getSliderList()->add(pSlider, true);
    }

  CopasiSlider* tmp = findCopasiSliderForCSlider(pSlider);

  if (!tmp)
    {
      setCurrentSlider(new CopasiSlider(pSlider, mpSliderBox));
      mpCurrSlider->installEventFilter(this);
      mpCurrSlider->setHidden(true);
      mpCurrSlider->updateSliderData();
      mSliderMap[mCurrentFolderId].push_back(mpCurrSlider);
      ((Q3VBoxLayout*)mpSliderBox->layout())->add(mpCurrSlider);
      connect(mpCurrSlider, SIGNAL(valueChanged(double)), this , SLOT(sliderValueChanged()));
      connect(mpCurrSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
      connect(mpCurrSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
      connect(mpCurrSlider, SIGNAL(closeClicked(CopasiSlider*)), this, SLOT(removeSlider(CopasiSlider*)));
      connect(mpCurrSlider, SIGNAL(editClicked(CopasiSlider*)), this, SLOT(editSlider(CopasiSlider*)));
      mpCurrSlider->setHidden(false);
    }
  else
    {
      mpCurrSlider = tmp;
    }
}

CSlider* SliderDialog::equivalentSliderExists(CSlider* pCSlider)
{
  CSlider* pResult = NULL;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  SCopasiXMLGUI* pGUI = (*CCopasiRootContainer::getDatamodelList())[0]->getGUI();
  assert(pGUI);
  unsigned i, maxCount = pGUI->getSliderList()->size();

  for (i = 0; i < maxCount; ++i)
    {
      CSlider* pTmpSlider = (*(pGUI->getSliderList()))[i];

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
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];
  unsigned int i, maxCount = v.size();
  CopasiSlider* pTmpSlider;

  for (i = 0; i < maxCount; ++i)
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

  if (id == mCurrentFolderId) return;

  if (id == -1)
    {
      setEnabled(false);
    }
  else
    {
      setEnabled(true);
    }

  clearSliderBox();

  mCurrentFolderId = id;

  fillSliderBox();
}

void SliderDialog::fillSliderBox()
{
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];

  if (mCurrentFolderId != -1)
    {
      std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
      // maybe other program parts have added or deleted some sliders
      assert(pVector);
      unsigned int i, j, maxSliders, maxWidgets;
      maxWidgets = v.size();
      maxSliders = pVector->size();

      // add CopasiSlider for all CSliders that don't have one.
      bool issueWarning = false;

      for (i = 0; i < maxSliders; ++i)
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
              setCurrentSlider(new CopasiSlider((*pVector)[i], mpSliderBox));
              connect(mpCurrSlider, SIGNAL(valueChanged(double)), this , SLOT(sliderValueChanged()));
              connect(mpCurrSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
              connect(mpCurrSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
              connect(mpCurrSlider, SIGNAL(closeClicked(CopasiSlider*)), this, SLOT(removeSlider(CopasiSlider*)));
              connect(mpCurrSlider, SIGNAL(editClicked(CopasiSlider*)), this, SLOT(editSlider(CopasiSlider*)));
              mpCurrSlider->installEventFilter(this);
              mpCurrSlider->setHidden(true);
              mSliderMap[mCurrentFolderId].push_back(mpCurrSlider);
            }
        }

      // delete CopasiSliders which have no correponding CSlider
      for (j = 0; j < maxWidgets; ++j)
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

  v = mSliderMap[mCurrentFolderId];
  unsigned int i, maxCount = v.size();

  for (i = maxCount; i != 0; --i)
    {
      QWidget* widget = v[i - 1];
      widget->setHidden(true);
      ((Q3VBoxLayout*)mpSliderBox->layout())->insertWidget(0, widget);
      setCurrentSlider(dynamic_cast<CopasiSlider*>(widget));

      if (mpCurrSlider)
        {
          mpCurrSlider->updateSliderData();
        }

      widget->setHidden(false);
    }
}

C_INT32 SliderDialog::mapFolderId2EntryId(C_INT32 folderId) const
{
  C_INT32 id = -1;
  int counter;

  for (counter = 0; counter < SliderDialog::numMappings; ++counter)
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
  if (mTaskMap.find(mCurrentFolderId) != mTaskMap.end())
    {
      setEnabled(false);
      updateAllSliders();
      ((this)->*(mTaskMap[mCurrentFolderId]))();
      updateAllSliders();
      setEnabled(true);
    }
}

void SliderDialog::sliderValueChanged()
{
  mSliderValueChanged = true;

  if ((!mSliderPressed) && mpAutoRunCheckBox->isChecked())
    {
      //runTask();
      mSliderValueChanged = false;
    }
}

void SliderDialog::sliderReleased()
{
  if (mSliderValueChanged && mpAutoRunCheckBox->isChecked())
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
  if (mpParentWindow)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mpParentWindow->getMainWidget()->getTrajectoryWidget()->enter((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Time-Course"]->getKey());
      mpParentWindow->getMainWidget()->getTrajectoryWidget()->runTask();
    }
}

void SliderDialog::runSteadyStateTask()
{
  if (mpParentWindow)
    {
      mpParentWindow->getMainWidget()->getSteadyStateWidget()->runTask();
    }
}

void SliderDialog::runScanTask()
{
  if (mpParentWindow)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mpParentWindow->getMainWidget()->getScanWidget()->enter((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Scan"]->getKey());
      mpParentWindow->getMainWidget()->getScanWidget()->runTask();
    }
}

void SliderDialog::runMCATask()
{
  if (mpParentWindow)
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mpParentWindow->getMainWidget()->getMCAWidget()->enter((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Metabolic Control Analysis"]->getKey());
      mpParentWindow->getMainWidget()->getMCAWidget()->runTask();
    }
}

void SliderDialog::closeEvent(QCloseEvent* e)
{
  QDialog::closeEvent(e);

  if (mpParentWindow)
    {
      mpParentWindow->slotShowSliders(false);
    }
}

CCopasiTask* SliderDialog::getTaskForFolderId(C_INT32 folderId)
{
  folderId = mapFolderId2EntryId(folderId);
  CCopasiTask* task = NULL;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  switch (folderId)
    {
      case 21:
        task = dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);
        break;
      case 23:
        task = dynamic_cast<CTrajectoryTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Time-Course"]);
        break;
      case 24:
        task = dynamic_cast<CMCATask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Metabolic Control Analysis"]);
        break;
      case 31:
        task = dynamic_cast<CScanTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Scan"]);
        break;
      default:
        task = NULL;
        break;
    }

  return task;
}

void SliderDialog::updateAllSliders()
{
  if (mCurrentFolderId == -1) return;

  bool autoModify = mpAutoModifyRangesCheckBox->isChecked();
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];
  unsigned int i, maxCount = v.size();

  for (i = 0; i < maxCount; ++i)
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
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  SCopasiXMLGUI* pGUI = pDataModel->getGUI();
  assert(pGUI);
  bool sliderDeleted = false;
  CCopasiVector<CSlider>* pSliderList = pGUI->getSliderList();
  assert(pSliderList);
  // go through the list in reverse so that items can be deleted
  unsigned int i, iMax = pSliderList->size();
  bool issueWarning = false;

  for (i = iMax; i > 0; --i)
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
          if (pSlider->getAssociatedEntityKey() == pDataModel->getModel()->getKey() || pSlider->getAssociatedEntityKey() == pObject->getKey())
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
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];
  unsigned int i, maxCount = v.size();

  for (i = 0; i < maxCount; ++i)
    {
      QWidget* widget = v[i];
      widget->setHidden(true);
      ((Q3VBoxLayout*)mpSliderBox->layout())->remove(widget);
    }
}

std::vector<CSlider*>* SliderDialog::getCSlidersForCurrentFolderId()
{
  CCopasiObject* object = (CCopasiObject*)getTaskForFolderId(mCurrentFolderId);

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
  mpCurrSlider->resetValue();
}

void SliderDialog::setDefault()
{
  mpCurrSlider->setOriginalValue(mpCurrSlider->value());
}

bool SliderDialog::sliderObjectChanged(CSlider* pSlider) const
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel* pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  std::vector<CCopasiContainer*> listOfContainers;
  listOfContainers.push_back(pModel);
  return !pSlider->compile(listOfContainers);
}

void SliderDialog::setParentWindow(CopasiUI3Window* pPW)
{
  mpParentWindow = pPW;
}
