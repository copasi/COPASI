// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SliderDialog.cpp,v $
//   $Revision: 1.83.4.6 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/11/12 19:38:00 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
#include "DataModelGUI.h"
#include "copasiui3window.h"
#include "CQTrajectoryWidget.h"
#include "SteadyStateWidget.h"
#include "ScanWidget.h"
#include "CQMCAWidget.h"
#include "SliderSettingsDialog.h"
#include "CQMessageBox.h"
#include "CopasiSlider.h"
#include "listviews.h"
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
#include "CCopasiSelectionDialog.h"

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
    mSliderMap(),
    mTaskMap(),
    mCurrentFolderId(0),
    mSliderValueChanged(false),
    mSliderPressed(false),
    mFramework(0)
{
  QVBoxLayout* pMainLayout = new QVBoxLayout(this);
  this->setLayout(pMainLayout);
  pMainLayout->setContentsMargins(5, 5, 5, 5);
  QHBoxLayout* pLayout2 = new QHBoxLayout(0);
  pLayout2->setContentsMargins(3, 3, 3, 3);
  pLayout2->addStretch();
  this->mpNewSliderButton = new QPushButton(0);
  this->mpNewSliderButton->setText("new sliders");
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
  // allow the user to create more than one slider
  std::vector<const CCopasiObject*> objects = CCopasiSelectionDialog::getObjectVector(this,
      CQSimpleSelectionTree::InitialTime |
      CQSimpleSelectionTree::Parameters);
  std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
  std::vector<const CCopasiObject*>::const_iterator it = objects.begin(), endit = objects.end();
  bool yesToAll = false;
  bool noToAll = false;
  // create the sliders for all the selected objects

  // first we need the task object because we need it later to associate the
  // later with the correct task
  CCopasiObject* object = (CCopasiObject*)getTaskForFolderId(mCurrentFolderId);

  if (!object) return;

  CCopasiObject* pTmpObject = NULL;

  while (it != endit)
    {
      // create a new slider
      assert((*it) != NULL);
      pTmpObject = const_cast<CCopasiObject*>(determineCorrectObjectForSlider(*it));

      CSlider* pCSlider = new CSlider("slider", (*CCopasiRootContainer::getDatamodelList())[0]);

      if (pCSlider)
        {
          pCSlider->setSliderObject(pTmpObject);
          pCSlider->setAssociatedEntityKey(object->getKey());
          // check if a slider for that object already exists and if so, prompt
          // the user what to do
          CSlider* pEquivalentSlider = equivalentSliderExists(pCSlider);

          if (pEquivalentSlider != NULL)
            {
              CopasiSlider* pCopasiSlider = NULL;

              // if the user has specified yesToAll, we reset the ranges of all
              // duplicate sliders
              if (yesToAll)
                {
                  pEquivalentSlider->resetRange();
                  // update the slider widget
                  pCopasiSlider = findCopasiSliderForCSlider(pEquivalentSlider);
                  assert(pCopasiSlider != NULL);

                  if (pCopasiSlider != NULL)
                    {
                      pCopasiSlider->updateSliderData();
                    }
                }
              // if the user has not specified noToAll, we need to prompt
              else if (!noToAll)
                {
                  QMessageBox::StandardButton result = CQMessageBox::information(NULL, "Slider Exists",
                                                       "A slider for this object already exists.\n\nDo you want to reset the range of the slider?",
                                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::YesToAll | QMessageBox::NoToAll, QMessageBox::No);

                  // check the answer and maybe set some flags
                  switch (result)
                    {
                      case QMessageBox::YesToAll:
                        // set the flag
                        yesToAll = true;
                      case QMessageBox::Yes:
                        // reset the range
                        pEquivalentSlider->resetRange();
                        // update the slider widget
                        pCopasiSlider = findCopasiSliderForCSlider(pEquivalentSlider);
                        assert(pCopasiSlider != NULL);

                        if (pCopasiSlider != NULL)
                          {
                            pCopasiSlider->updateSliderData();
                          }

                        break;
                      case QMessageBox::NoToAll:
                        // set the flag
                        noToAll = true;
                      case QMessageBox::No:
                        // do nothing else
                        break;
                      default:
                        // do nothing
                        break;
                    }
                }

              delete pCSlider;
            }
          else
            {
              pCSlider->resetRange();
              addSlider(pCSlider);
            }
        }

      ++it;
    }

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
      mpSliderBox->layout()->remove(pSlider);
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
  if (mpParentWindow == NULL)
    return;

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
      setCurrentSlider(new CopasiSlider(pSlider, mpParentWindow->getDataModel(), mpSliderBox));
      mpCurrSlider->installEventFilter(this);
      mpCurrSlider->setHidden(true);
      mpCurrSlider->updateSliderData();
      mSliderMap[mCurrentFolderId].push_back(mpCurrSlider);
      mpSliderBox->layout()->addWidget(mpCurrSlider);
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
  if (mpParentWindow == NULL)
    return;

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
              setCurrentSlider(new CopasiSlider((*pVector)[i], mpParentWindow->getDataModel(), mpSliderBox));
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
      static_cast<QBoxLayout*>(mpSliderBox->layout())->insertWidget(0, widget);
      setCurrentSlider(dynamic_cast<CopasiSlider*>(widget));

      if (mpCurrSlider)
        {
          // check if the slider value is determined by an expression
          CModelEntity* pME = dynamic_cast<CModelEntity*>(this->mpCurrSlider->object()->getObjectParent());

          if (pME != NULL)
            {
              if (!pME->getInitialExpression().empty())
                {
                  // we have to disable the slider widget and set a tooltip
                  // that explains why this slider is disabled
                  if (this->mpCurrSlider->isEnabled())
                    {
                      this->mpCurrSlider->setEnabled(false);
                      this->mpCurrSlider->setToolTip("This value is determined by an initial expression.");
                    }
                }
              else
                {
                  // if the slider is disabled, we have to enable it and delete the tooltip
                  if (!this->mpCurrSlider->isEnabled())
                    {
                      this->mpCurrSlider->setEnabled(true);
                      this->mpCurrSlider->setToolTip("");
                    }

                }
            }

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
  if (mpParentWindow != NULL &&
      mTaskMap.find(mCurrentFolderId) != mTaskMap.end())
    {
      setEnabled(false);
      updateAllSliders();
      // commit possible changes to the task widget before running the task
      CopasiWidget* pWidget = mpParentWindow->getMainWidget()->findWidgetFromId(mCurrentFolderId);
      assert(pWidget != NULL);
      pWidget->leave();
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
  // this method might not always do what we want
  // e.g. if we change a volume via a slider, the initial amount/concentrations
  // of the species are updated automatically, but if there is a slider for the
  // automatically updated value and we changed that value as well together with
  // the volume, the change of amount/concentration is probably lost depending on
  // the order of the sliders
  // We need to do this in two rounds, first we set all the new values
  //
  // To solve this, I added a new argument to updateValue that determines if the call also updates the dependencies.
  // Here we do not let the updateValue call update the dependencies, but we take care of this ourselves
  // with a call to ListView::refreshInitialValues
  if (mCurrentFolderId == -1) return;

  bool autoModify = mpAutoModifyRangesCheckBox->isChecked();
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];
  unsigned int i, maxCount = v.size();

  for (i = 0; i < maxCount; ++i)
    {
      CopasiSlider* pCopasiSlider = dynamic_cast<CopasiSlider*>(v[i]);

      if (pCopasiSlider)
        {
          pCopasiSlider->updateValue(autoModify, false);
        }
    }

  if (maxCount > 0)
    {
      if (mpParentWindow != NULL)
        mpParentWindow->getDataModel()->refreshInitialValues();

      // now we need to go through the slider again and make sure that
      // they actually display the updated values
      for (i = 0; i < maxCount; ++i)
        {
          CopasiSlider* pCopasiSlider = dynamic_cast<CopasiSlider*>(v[i]);

          if (pCopasiSlider)
            {
              pCopasiSlider->updateSliderData();
            }
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
      mpSliderBox->layout()->remove(widget);
    }
}

std::vector<CSlider*>* SliderDialog::getCSlidersForCurrentFolderId()
{
  CCopasiObject* object = (CCopasiObject*)getTaskForFolderId(mCurrentFolderId);

  if (!object) return NULL;

  std::vector<CSlider*>* pVector = new std::vector<CSlider*>();

  try
    {
      pVector = getCSlidersForObject(object, pVector);
    }

  catch (...) {}

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

// This method check if the given object is a reference to the initial amount or the initial concentration
// of a metabolite. Then it checks the current framework and the metabolite if a slider to the object
// is actually allowed and if it isn't, it will return the correct object
const CCopasiObject* SliderDialog::determineCorrectObjectForSlider(const CCopasiObject* pObject)
{
  const CCopasiObject* pResult = NULL;

  if (pObject == NULL)
    {
      pResult = NULL;
    }
  else
    {
      CMetab* pMetab = dynamic_cast<CMetab*>((pObject)->getObjectParent());
      // we just assume the object is correct for the framework
      // this saves some additional test later on
      pResult = pObject;

      if (pMetab != NULL)
        {
          // now we have to check if the framework is the concentrations framework
          // and if we are actually allowed to change the concentration on a metabolite
          if (mFramework == 0)
            {
              // we are in the concentrations framework
              //
              // sometimes it is not allowed to change the concentration of a metabolite
              // because it would change the volume of the compartment
              if (pMetab->isInitialConcentrationChangeAllowed() && pObject == pMetab->getInitialValueReference())
                {
                  // if the current object is for the concentration, we return a new object to the amount
                  pResult = pMetab->getInitialConcentrationReference();
                  assert(pResult != NULL);
                }
            }
          else
            {
              // we are in the particle number framework
              // if the object is for the amount, we leave it, otherwise we
              // return a new object for the amount
              if (pObject == pMetab->getInitialConcentrationReference())
                {
                  pResult = pMetab->getInitialValueReference();
                  assert(pResult != NULL);
                }

            }
        }
    }

  return pResult;
}

// sets the framework on the sliders dialog
// This leads to changed sliders for metabolites
// Because depending on the framework, we only allow sliders
// for amount or concentration, but not both for the same metabolite
void SliderDialog::setFramework(int framework)
{
  mFramework = framework;

  bool changed = false;
  // we go through the sliders and check if the slider for species amount
  // or concentration are still appropriate for the framework that has been set
  std::map<C_INT32, std::vector<QWidget*> >::iterator it = this->mSliderMap.begin(), endit = this->mSliderMap.end();
  std::vector<QWidget*>::iterator it2, endit2;
  CCopasiObject *pObject = NULL, *pTmpObject = NULL;
  CopasiSlider* pSlider = NULL;

  while (it != endit)
    {
      it2 = it->second.begin();
      endit2 = it->second.end();

      while (it2 != endit2)
        {
          pSlider = dynamic_cast<CopasiSlider*>(*it2);

          if (pSlider != NULL)
            {
              pObject = pSlider->object();
              assert(pObject != NULL);

              if (pObject != NULL)
                {
                  pTmpObject = const_cast<CCopasiObject*>(this->determineCorrectObjectForSlider(pObject));

                  if (pTmpObject != pObject)
                    {
                      // we have to recalculate the range
                      double oldMin = pSlider->minValue();
                      double oldMax = pSlider->maxValue();
                      double oldValue = pSlider->value();
                      // we have to set the new object on the slider
                      pSlider->setObject(pTmpObject);
                      double newValue =  pSlider->value();
                      double newMin = (oldMin / oldValue) * newValue;
                      double newMax = (oldMax / oldValue) * newValue;
                      pSlider->setMinValue(newMin);
                      pSlider->setMaxValue(newMax);
                      changed = true;
                    }
                }
            }

          ++it2;
        }

      ++it;
    }

  // we don't care if the change was for the current
  // task, we justm update if there was any change at all
  if (changed = true)
    {
      this->update();
    }
}

