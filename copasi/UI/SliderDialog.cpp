// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <sstream>

//Added by qt3to4:
#include <QContextMenuEvent>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QtCore/QEvent>

#include "copasi/UI/SliderDialog.h"
#include "copasi/UI/DataModelGUI.h"
#include "copasi/UI/copasiui3window.h"
#include "copasi/UI/CQTrajectoryWidget.h"
#include "copasi/UI/SteadyStateWidget.h"
#include "copasi/UI/ScanWidget.h"
#include "copasi/UI/CQMCAWidget.h"
#include "copasi/UI/CQLNAWidget.h"
#include "copasi/UI/CQFittingWidget.h"
#include "copasi/UI/CQOptimizationWidget.h"
#include "copasi/UI/SliderSettingsDialog.h"
#include "copasi/UI/CQMessageBox.h"
#include "copasi/UI/CopasiSlider.h"
#include "copasi/UI/listviews.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/crosssection/CCrossSectionTask.h"
#include "copasi/UI/CQCrossSectionTaskWidget.h"

#include "copasi/lna/CLNATask.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/utilities/CSlider.h"
#include "copasi/model/CModel.h"
#include "copasi/UI/CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

size_t SliderDialog::numMappings = 14;

ListViews::WidgetType SliderDialog::folderMappings[][2] =
{
  {ListViews::WidgetType::SteadyState, ListViews::WidgetType::SteadyState},
  {ListViews::WidgetType::SteadyStateResult, ListViews::WidgetType::SteadyState},
  {ListViews::WidgetType::TimeCourse, ListViews::WidgetType::TimeCourse},
  {ListViews::WidgetType::TimeCourseResult, ListViews::WidgetType::TimeCourse},
  {ListViews::WidgetType::MetabolicControlAnalysis, ListViews::WidgetType::MetabolicControlAnalysis},
  {ListViews::WidgetType::MetabolicControlAnalysisResult, ListViews::WidgetType::MetabolicControlAnalysis},
  {ListViews::WidgetType::ParameterScan, ListViews::WidgetType::ParameterScan},
  {ListViews::WidgetType::Optimization, ListViews::WidgetType::Optimization},
  {ListViews::WidgetType::OptimizationResult, ListViews::WidgetType::Optimization},
  {ListViews::WidgetType::ParameterEstimation, ListViews::WidgetType::ParameterEstimation},
  {ListViews::WidgetType::ParameterEstimationResult, ListViews::WidgetType::ParameterEstimation},
  {ListViews::WidgetType::LinearNoiseApproximation, ListViews::WidgetType::LinearNoiseApproximation},
  {ListViews::WidgetType::CrossSection, ListViews::WidgetType::CrossSection},
  {ListViews::WidgetType::CrossSectionResult, ListViews::WidgetType::CrossSection}
};

//size_t SliderDialog::numKnownTasks = 4;
//size_t SliderDialog::[] = {21, 23, 24, 31};
//const char* SliderDialog::knownTaskNames[] = {"Steady State", "Time Course", "MCA" , "Scan"};

SliderDialog::SliderDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl):
  CWindowInterface(parent, fl),
  mpParentWindow(NULL),
  mpContextMenu(NULL),
  mpCurrSlider(NULL),
  mSliderMap(),
  mTaskMap(),
  mInitialValueMap(),
  mCurrentFolderId(ListViews::WidgetType::COPASI),
  mSliderValueChanged(false),
  mSliderPressed(false),
  mFramework(0),
  mChanged(false)
{
#ifndef Darwin
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
#endif // not Darwin

  setupUi(this);

  setObjectName(QString::fromUtf8(name));
  setWindowTitle("Slider Window");

  mpSliderBox->layout()->addItem(new QSpacerItem(0, 5, QSizePolicy::Minimum, QSizePolicy::Expanding));

  this->mpContextMenu = new QMenu(this);
  mpaCreateNewSlider = this->mpContextMenu->addAction("Add New Slider", this, SLOT(createNewSlider()));
  mpaRemoveSlider = this->mpContextMenu->addAction("Remove Slider", this, SLOT(removeSlider()));
  mpaEditSlider = this->mpContextMenu->addAction("Edit Slider", this, SLOT(editSlider()));
  mpaResetValue = this->mpContextMenu->addAction("Reset Value", this, SLOT(resetValue()));
  mpaSetDefault = this->mpContextMenu->addAction("Set new default value", this, SLOT(setDefault()));

  this->mSliderMap[ListViews::WidgetType::NotFound].push_back(new QLabel("<p>There are no sliders available for this task. If you select one of the tasks that supports sliders in the copasi object tree, this dialog will become active.</p>", mpSliderBox));

  this->mTaskMap[ListViews::WidgetType::TimeCourse] = &SliderDialog::runTimeCourse;
  this->mTaskMap[ListViews::WidgetType::SteadyState] = &SliderDialog::runSteadyStateTask;
  this->mTaskMap[ListViews::WidgetType::ParameterScan] = &SliderDialog::runScanTask;
  this->mTaskMap[ListViews::WidgetType::MetabolicControlAnalysis] = &SliderDialog::runMCATask;
  this->mTaskMap[ListViews::WidgetType::LinearNoiseApproximation] = &SliderDialog::runLNATask;
  this->mTaskMap[ListViews::WidgetType::ParameterEstimation] = &SliderDialog::runParameterEstimationTask;
  this->mTaskMap[ListViews::WidgetType::Optimization] = &SliderDialog::runOptimizationTask;
  this->mTaskMap[ListViews::WidgetType::CrossSection] = &SliderDialog::runCrossSectionTask;

  connect(this->mpRunTaskButton, SIGNAL(clicked()), this, SLOT(runTask()));
  connect(this->mpNewSliderButton, SIGNAL(clicked()), this, SLOT(createNewSlider()));
  connect(this->mpRestoreButton, SIGNAL(clicked()), this, SLOT(restoreDefaults()));

  this->setCurrentFolderId(ListViews::WidgetType::NotFound);
  init();
}

void SliderDialog::contextMenuEvent(QContextMenuEvent* e)
{
  CopasiSlider* pSlider = findCopasiSliderAtPosition(e->pos());

  if (pSlider)
    {
      mpaCreateNewSlider->setEnabled(false);
      mpaRemoveSlider->setEnabled(true);
      mpaEditSlider->setEnabled(true);
      setCurrentSlider(pSlider);
    }
  else
    {
      mpaCreateNewSlider->setEnabled(true);
      mpaRemoveSlider->setEnabled(false);
      mpaEditSlider->setEnabled(false);
    }

  mpContextMenu->popup(e->globalPos());
}

void SliderDialog::setCurrentSlider(CopasiSlider* pSlider)
{
  mpCurrSlider = pSlider;

  if (mpCurrSlider && isVisible())
    {
      mpCurrSlider->focusSlider();
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
  std::vector<const CDataObject*> objects = CCopasiSelectionDialog::getObjectVector(this,
      CQSimpleSelectionTree::InitialTime |
      CQSimpleSelectionTree::Parameters);
  std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
  std::vector<const CDataObject*>::const_iterator it = objects.begin(), endit = objects.end();
  bool yesToAll = false;
  bool noToAll = false;
  // create the sliders for all the selected objects

  // first we need the task object because we need it later to associate the
  // later with the correct task
  CDataObject* object = (CDataObject*)getTaskForFolderId(mCurrentFolderId);

  if (!object) return;

  CDataObject* pTmpObject = NULL;

  while (it != endit)
    {
      // create a new slider
      assert((*it) != NULL);
      pTmpObject = const_cast<CDataObject*>(determineCorrectObjectForSlider(*it));

      CDataModel * pDataModel = pTmpObject->getObjectDataModel();
      assert(pDataModel != NULL);

      CSlider* pCSlider = new CSlider("slider", pDataModel);

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
                  QMessageBox::StandardButton result = CQMessageBox::information(this, "Slider Exists",
                                                       "A slider for this object already exists.\n\nDo you want to reset the range of the slider?",
                                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::YesToAll | QMessageBox::NoToAll, QMessageBox::No);

                  // check the answer and maybe set some flags
                  switch (result)
                    {
                      case QMessageBox::YesToAll:
                      case QMessageBox::Yes:
                        // set the flag
                        yesToAll = (result == QMessageBox::YesToAll);

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
                        break;

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
              CObjectInterface::ContainerList listOfContainers;
              assert(CRootContainer::getDatamodelList()->size() > 0);
              listOfContainers.push_back(pDataModel->getModel());
              pCSlider->compile(listOfContainers);
              pCSlider->resetRange();
              addSlider(pCSlider);
              mChanged = true;
            }
        }

      ++it;
    }

  delete pVector;
}

void SliderDialog::restoreDefaults()
{
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];
  std::vector<double> tmpVec = mInitialValueMap[mCurrentFolderId];
  size_t maxcount = v.size();
  CopasiSlider* pTmpSlider;

  for (int i = 0; (size_t) i < maxcount; ++i)
    {
      pTmpSlider = dynamic_cast<CopasiSlider*>(v[i]);
      pTmpSlider->setValue(tmpVec[i]);
    }

  runTask();
}

void SliderDialog::removeSlider()
{
  removeSlider(mCurrentFolderId);
}

void
SliderDialog::removeSlider(ListViews::WidgetType folderId)
{
  if (mpCurrSlider)
    {

      if (mpCurrSlider->getCSlider())
        {
          CDataModel* pDataModel = mpCurrSlider->getCSlider()->getObjectDataModel();
          assert(pDataModel != NULL);
          CDataVector<CSlider>* pSliderList = pDataModel->getGUI()->getSliderList();
          int i, maxCount = (int)pSliderList->size();

          for (i = maxCount - 1; i >= 0; --i)
            {
              CSlider* pTmpSlider = &pSliderList->operator[](i);

              if (pTmpSlider == mpCurrSlider->getCSlider())
                {
                  pSliderList->remove(i);
                  mpCurrSlider->setCSlider(NULL);
                  break;
                }
            }
        }

      deleteSlider(mpCurrSlider, folderId);
      mpCurrSlider = NULL;
    }
}

void
SliderDialog::deleteSlider(CopasiSlider* pSlider, ListViews::WidgetType folderId)
{
  if (pSlider)
    {
      std::vector<QWidget*>* v = &mSliderMap[folderId];
      std::vector<QWidget*>::iterator it = v->begin();
      std::vector<QWidget*>::iterator end = v->end();

      std::vector<double>* valVec = &mInitialValueMap[mCurrentFolderId];
      std::vector<double>::iterator itVal = valVec->begin();
      std::vector<double>::iterator itValEnd = valVec->end();

      while (it != end)
        {
          if (*it == pSlider)
            {
              break;
            }

          ++it;

          if (itVal != itValEnd)
            ++itVal;
        }

      if (it != end)
        v->erase(it);

      if (itVal != itValEnd)
        valVec->erase(itVal);

      mpSliderBox->layout()->removeWidget(pSlider);
      pdelete(pSlider);
      mChanged = true;
    }
}

void SliderDialog::deleteSlider(CopasiSlider* pSlider)
{
  deleteSlider(pSlider, mCurrentFolderId);
}

void SliderDialog::editSlider()
{
  SliderSettingsDialog* pSettingsDialog = new SliderSettingsDialog(this);
  // set the list of sliders that is already known
  CDataObject* object = (CDataObject*)getTaskForFolderId(mCurrentFolderId);

  if (!object) return;

  CDataModel * pDataModel = object->getObjectDataModel();
  assert(pDataModel != NULL);
  pSettingsDialog->setModel(pDataModel->getModel());

  std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
  pSettingsDialog->setDefinedSliders(*pVector);

  //pSettingsDialog->disableObjectChoosing(true);

  pSettingsDialog->setSlider(mpCurrSlider->getCSlider());

  bool needRun = false;

  if (pSettingsDialog->exec() == QDialog::Accepted)
    {
      addSlider(pSettingsDialog->getSlider());
      mpCurrSlider->updateSliderData();

      needRun = pSettingsDialog->needRun();

      /*
      if ((!mpCurrSlider->isEnabled()) && mpCurrSlider->getCSlider()->compile())
        {
          mpCurrSlider->setEnabled(true);
        }
        */
    }

  delete pSettingsDialog;
  delete pVector;

  if (needRun)
    {
      if (mpAutoRunCheckBox->isChecked())
        {
          runTask();
        }
      else
        {
          updateAllSliders();
        }
    }
}

SliderDialog::~SliderDialog()
{
  this->clear();
  removeFromMainWindow(mpParentWindow);
  delete mpRunTaskButton;
  delete mpAutoRunCheckBox;
  delete mpAutoModifyRangesCheckBox;
  delete mpSliderBox;
  delete mpScrollView;
}

void SliderDialog::clear()
{
  this->clearSliderBox();
  size_t j, maxWidgets;

  std::map< ListViews::WidgetType, std::vector< QWidget* > >::iterator it = mSliderMap.begin();

  while (it != mSliderMap.end())
    {
      std::vector<QWidget*> v = it->second;
      maxWidgets = v.size();

      for (j = 0; j < maxWidgets; ++j)
        {
          pdelete(v[j]);
        }

      ++it;
    }

  this->mSliderMap.clear();
  this->mInitialValueMap.clear();
}

void SliderDialog::init()
{}

void SliderDialog::addSlider(CSlider* pSlider)
{
  if (mpParentWindow == NULL)
    return;

  // check if there already is a slider for this  object
  CDataModel * pDataModel = pSlider->getObjectDataModel();
  assert(pDataModel != NULL);
  SCopasiXMLGUI* pGUI = pDataModel->getGUI();
  assert(pGUI);

  if (!equivalentSliderExists(pSlider))
    {
      CObjectInterface::ContainerList listOfContainers;
      assert(CRootContainer::getDatamodelList()->size() > 0);
      listOfContainers.push_back(pDataModel->getModel());
      pSlider->compile(listOfContainers);
      pGUI->getSliderList()->add(pSlider, true);
    }

  CopasiSlider* tmp = findCopasiSliderForCSlider(pSlider);

  if (!tmp)
    {
      setCurrentSlider(new CopasiSlider(pSlider, mpParentWindow->getDataModel(), mpSliderBox));
      mpCurrSlider->installEventFilter(this);
      mpCurrSlider->setHidden(true);
      mpCurrSlider->updateSliderData();
      // make sure the slider points to the correct object
      // for the currently set framework
      this->setCorrectSliderObject(this->mpCurrSlider);
      mSliderMap[mCurrentFolderId].push_back(mpCurrSlider);
      mInitialValueMap[mCurrentFolderId].push_back(mpCurrSlider->value());
      QBoxLayout* layout = static_cast<QBoxLayout*>(mpSliderBox->layout());
      int childCount = layout->count() - 1;
      layout->insertWidget(childCount, mpCurrSlider);
      connect(mpCurrSlider, SIGNAL(valueChanged(double)), this, SLOT(sliderValueChanged()));
      connect(mpCurrSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
      connect(mpCurrSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
      connect(mpCurrSlider, SIGNAL(closeClicked(CopasiSlider*)), this, SLOT(removeSlider(CopasiSlider*)));
      connect(mpCurrSlider, SIGNAL(editClicked(CopasiSlider*)), this, SLOT(editSlider(CopasiSlider*)));
      mpCurrSlider->setHidden(false);
      mChanged = true;
    }
  else
    {
      mpCurrSlider = tmp;
    }
}

CSlider* SliderDialog::equivalentSliderExists(CSlider* pCSlider)
{
  CSlider* pResult = NULL;
  CDataModel * pDataModel = pCSlider->getObjectDataModel();
  assert(pDataModel != NULL);
  SCopasiXMLGUI* pGUI = pDataModel->getGUI();
  assert(pGUI);
  size_t i, maxCount = pGUI->getSliderList()->size();

  for (i = 0; i < maxCount; ++i)
    {
      CSlider* pTmpSlider = &pGUI->getSliderList()->operator[](i);

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
  size_t i, maxCount = v.size();
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

void SliderDialog::setCurrentFolderId(ListViews::WidgetType id)
{
  id = mapFolderId2EntryId(id);

  if (id == mCurrentFolderId) return;

  if (id == ListViews::WidgetType::NotFound || !this->mpParentWindow->isEnabled())
    {
      setEnabled(false);
    }
  else
    {
      setEnabled(true);
    }

  clearSliderBox();
  mCurrentFolderId = id;

  // Set appropriate window title
  if (id == ListViews::WidgetType::NotFound)
    {
      setWindowTitle("No Task selected");
    }
  else
    {
      QString thisWindowTitle = FROM_UTF8(std::string(ListViews::WidgetName[id] + " Sliders"));

      setWindowTitle(thisWindowTitle);
    }

  fillSliderBox();
}

CSlider *SliderDialog::getCSliderForCopasiSlider(std::vector<CSlider*>& v, QWidget* slider)
{
  CopasiSlider* pTmpSlider = dynamic_cast<CopasiSlider*>(slider);

  if (!pTmpSlider) return NULL;

  std::vector<CSlider*>::const_iterator it;

  for (it = v.begin(); it != v.end(); ++it)
    {
      if (pTmpSlider->getCSlider() == *it)
        {
          return *it;
        }
    }

  return NULL;
}

CopasiSlider *SliderDialog::getCopasiSliderForCSlider(std::vector<QWidget*>& v, CSlider* slider)
{
  std::vector<QWidget*>::const_iterator it;

  for (it = v.begin(); it != v.end(); ++it)
    {
      CopasiSlider* pTmpSlider = dynamic_cast<CopasiSlider*>(*it);

      if (!pTmpSlider) break;

      if (pTmpSlider->getCSlider() == slider)
        {
          return pTmpSlider;
        }
    }

  return NULL;
}

void SliderDialog::createSlidersForFolder(std::vector<QWidget*>& v)
{
  if (mCurrentFolderId == ListViews::WidgetType::NotFound)
    return;

  std::vector<CSlider*>* pVector = getCSlidersForCurrentFolderId();
  std::vector<CSlider*>::const_iterator it;
  std::vector<QWidget*>::const_iterator wIt;
  // maybe other program parts have added or deleted some sliders
  assert(pVector);

  // add CopasiSlider for all CSliders that don't have one.
  bool issueWarning = false;

  for (it = pVector->begin(); it != pVector->end(); ++it)
    {
      //bool found = false;

      // check whether we have a slider
      CopasiSlider* pTmpSlider = getCopasiSliderForCSlider(v, *it);

      if (pTmpSlider != NULL) continue;

      // if not create one
      setCurrentSlider(new CopasiSlider(*it, mpParentWindow->getDataModel(), mpSliderBox));
      // make sure the slider points to the correct object
      // for the currently set framework
      this->setCorrectSliderObject(this->mpCurrSlider);
      connect(mpCurrSlider, SIGNAL(valueChanged(double)), this, SLOT(sliderValueChanged()));
      connect(mpCurrSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
      connect(mpCurrSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
      connect(mpCurrSlider, SIGNAL(closeClicked(CopasiSlider*)), this, SLOT(removeSlider(CopasiSlider*)));
      connect(mpCurrSlider, SIGNAL(editClicked(CopasiSlider*)), this, SLOT(editSlider(CopasiSlider*)));
      mpCurrSlider->installEventFilter(this);
      mpCurrSlider->setHidden(true);
      mSliderMap[mCurrentFolderId].push_back(mpCurrSlider);
      mInitialValueMap[mCurrentFolderId].push_back(mpCurrSlider->value());
    }

  // delete CopasiSliders which have no corresponding CSlider
  for (wIt = v.begin(); wIt != v.end(); ++wIt)
    {
      bool found = getCSliderForCopasiSlider(*pVector, *wIt) != NULL;

      if (!found)
        {
          CopasiSlider* pTmpSlider = dynamic_cast<CopasiSlider*>(*wIt);
          assert(pTmpSlider);
          deleteSlider(pTmpSlider);
          mChanged = true;
        }
    }

  if (issueWarning)
    {
      CQMessageBox::information(this, "Invalid Slider",
                                "One or more sliders are invalid and have been disabled!",
                                QMessageBox::Ok, QMessageBox::NoButton);
    }

  delete pVector;
}

void SliderDialog::fillSliderBox()
{
  if (mpParentWindow == NULL)
    return;

  deleteInvalidSliders();
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];

  createSlidersForFolder(v);

  v = mSliderMap[mCurrentFolderId];
  size_t i, maxCount = v.size();

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

ListViews::WidgetType SliderDialog::mapFolderId2EntryId(ListViews::WidgetType folderId) const
{
  ListViews::WidgetType id = ListViews::WidgetType::NotFound;
  size_t counter;

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
  if (mpParentWindow == NULL
      || !isEnabled()
      || !mpParentWindow->isEnabled()
      || mTaskMap.find(mCurrentFolderId) == mTaskMap.end())
    return;

  updateAllSliders();

  TaskWidget* pWidget = dynamic_cast<TaskWidget*>(mpParentWindow->getMainWidget()->findWidgetFromId(mCurrentFolderId));
  assert(pWidget != NULL);

  if (pWidget == NULL) return;

  // commit possible changes to the task widget before running the task
  pWidget->leave();

  // execute task
  ((this)->*(mTaskMap[mCurrentFolderId]))();
}

void SliderDialog::sliderValueChanged()
{
  mSliderValueChanged = true;

  if ((!mSliderPressed) && mpAutoRunCheckBox->isChecked()
      && CRootContainer::getConfiguration()->useAdvancedSliders())
    {
      CopasiSlider* slider = dynamic_cast<CopasiSlider*>(sender());

      if (slider != NULL && slider != mpCurrSlider)
        setCurrentSlider(slider);

      mSliderValueChanged = false;
      runTask();
    }
}

void SliderDialog::sliderReleased()
{
  if (mSliderValueChanged && mpAutoRunCheckBox->isChecked())
    {
      mSliderValueChanged = false;
      runTask();
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
      CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
      assert(pDataModel != NULL);
      mpParentWindow->getMainWidget()->getTrajectoryWidget()->enter(pDataModel->getTaskList()->operator[]("Time-Course").getCN());
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
      CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
      assert(pDataModel != NULL);
      mpParentWindow->getMainWidget()->getScanWidget()->enter(pDataModel->getTaskList()->operator[]("Scan").getCN());
      mpParentWindow->getMainWidget()->getScanWidget()->runTask();
    }
}

void SliderDialog::runMCATask()
{
  if (mpParentWindow)
    {
      CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
      assert(pDataModel != NULL);
      mpParentWindow->getMainWidget()->getMCAWidget()->enter(pDataModel->getTaskList()->operator[]("Metabolic Control Analysis").getCN());
      mpParentWindow->getMainWidget()->getMCAWidget()->runTask();
    }
}

void SliderDialog::runLNATask()
{
  if (mpParentWindow)
    {
      CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
      assert(pDataModel != NULL);
      mpParentWindow->getMainWidget()->getLNAWidget()->enter(pDataModel->getTaskList()->operator[]("Linear Noise Approximation").getCN());
      mpParentWindow->getMainWidget()->getLNAWidget()->runTask();
    }
}

void SliderDialog::runParameterEstimationTask()
{
  if (mpParentWindow)
    {
      CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
      assert(pDataModel != NULL);
      mpParentWindow->getMainWidget()->getFittingWidget()->enter(pDataModel->getTaskList()->operator[]("Parameter Estimation").getCN());
      mpParentWindow->getMainWidget()->getFittingWidget()->runTask();
    }
}

void SliderDialog::runCrossSectionTask()
{
  if (mpParentWindow)
    {
      CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
      assert(pDataModel != NULL);
      mpParentWindow->getMainWidget()->getCrossSectionWidget()->enter(pDataModel->getTaskList()->operator[]("Cross Section").getCN());
      mpParentWindow->getMainWidget()->getCrossSectionWidget()->runTask();
    }
}

void SliderDialog::runOptimizationTask()
{
  if (mpParentWindow)
    {
      CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
      assert(pDataModel != NULL);
      mpParentWindow->getMainWidget()->getOptimizationWidget()->enter(pDataModel->getTaskList()->operator[]("Optimization").getCN());
      mpParentWindow->getMainWidget()->getOptimizationWidget()->runTask();
    }
}

void SliderDialog::closeEvent(QCloseEvent* e)
{
  CWindowInterface::closeEvent(e);

  if (mpParentWindow)
    {
      mpParentWindow->slotShowSliders(false);
    }
}

CCopasiTask* SliderDialog::getTaskForFolderId(ListViews::WidgetType folderId)
{
  folderId = mapFolderId2EntryId(folderId);
  CCopasiTask* task = NULL;
  CDataModel * pDataModel = mpParentWindow->getMainWidget()->getDataModel();
  assert(pDataModel != NULL);

  switch (folderId)
    {
      case ListViews::WidgetType::SteadyState:
        task = dynamic_cast<CSteadyStateTask *>(&pDataModel->getTaskList()->operator[]("Steady-State"));
        break;

      case ListViews::WidgetType::TimeCourse:
        task = dynamic_cast<CTrajectoryTask *>(&pDataModel->getTaskList()->operator[]("Time-Course"));
        break;

      case ListViews::WidgetType::MetabolicControlAnalysis:
        task = dynamic_cast<CMCATask *>(&pDataModel->getTaskList()->operator[]("Metabolic Control Analysis"));
        break;

      case ListViews::WidgetType::ParameterScan:
        task = dynamic_cast<CScanTask *>(&pDataModel->getTaskList()->operator[]("Scan"));
        break;

      case ListViews::WidgetType::LinearNoiseApproximation:
        task = dynamic_cast<CLNATask *>(&pDataModel->getTaskList()->operator[]("Linear Noise Approximation"));
        break;

      case ListViews::WidgetType::ParameterEstimation:
        task = dynamic_cast<CFitTask *>(&pDataModel->getTaskList()->operator[]("Parameter Estimation"));
        break;

      case ListViews::WidgetType::Optimization:
        task = dynamic_cast<COptTask *>(&pDataModel->getTaskList()->operator[]("Optimization"));
        break;

      case ListViews::WidgetType::CrossSection:
        task = dynamic_cast<CCrossSectionTask *>(&pDataModel->getTaskList()->operator[]("Cross Section"));
        break;

      default:
        task = NULL;
        break;
    }

  return task;
}

void SliderDialog::updateAllSliders()
{
  if (!isVisible())
    {
      return;
    }

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
  if (mCurrentFolderId == ListViews::WidgetType::NotFound) return;

  bool autoModify = mpAutoModifyRangesCheckBox->isChecked();
  this->deleteInvalidSliders();
  std::vector<QWidget*> v = mSliderMap[mCurrentFolderId];
  std::vector<QWidget*>::iterator wit = v.begin(), wendit = v.end();

  if (!v.empty())
    {
      // We make sure that all initial values of the model are up to date
      // before we update the sliders.
      if (mpParentWindow != NULL)
        mpParentWindow->getDataModel()->refreshInitialValues();

      // We go through the sliders and make sure that
      // that the  model values are updated.
      wit = v.begin();
      wendit = v.end();
      CopasiSlider* pCopasiSlider = NULL;

      while (wit != wendit)
        {
          pCopasiSlider = dynamic_cast<CopasiSlider*>(*wit);

          if (pCopasiSlider)
            {
              pCopasiSlider->updateValue(autoModify, false);
              pCopasiSlider->updateSliderData();
            }

          ++wit;
        }

      // We make sure that all dependent initial values of the model are up to date.
      // Please note that this is context sensitive, i.e., concentration and particle numbers
      // are dealt with correctly.
      if (mpParentWindow != NULL)
        mpParentWindow->getDataModel()->refreshInitialValues();
    }
}

void SliderDialog::removeSlider(CopasiSlider* slider)
{
  setCurrentSlider(slider);
  removeSlider(mCurrentFolderId);
}

void SliderDialog::removeSlider(CopasiSlider* slider, ListViews::WidgetType folderId)
{
  setCurrentSlider(slider);
  removeSlider(folderId);
}

void SliderDialog::editSlider(CopasiSlider* slider)
{
  setCurrentSlider(slider);
  editSlider();
}

std::vector<CSlider*>* SliderDialog::getCSlidersForObject(CDataObject* pObject, std::vector<CSlider*>* pVector) const
{
  CDataModel * pDataModel = pObject->getObjectDataModel();
  assert(pDataModel != NULL);
  SCopasiXMLGUI* pGUI = pDataModel->getGUI();
  assert(pGUI);
  bool sliderDeleted = false;
  CDataVector<CSlider>* pSliderList = pGUI->getSliderList();
  assert(pSliderList);
  // go through the list in reverse so that items can be deleted
  size_t i, iMax = pSliderList->size();
  bool issueWarning = false;

  for (i = iMax; i > 0; --i)
    {
      CSlider* pSlider = &pSliderList->operator[](i - 1);

      if (sliderObjectChanged(pSlider))
        {
          if (!sliderDeleted)
            {
              CQMessageBox::information(const_cast< SliderDialog * >(this), "Missing slider objects",
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
              CObjectInterface::ContainerList ListOfContainer;
              ListOfContainer.push_back(pSlider->getObjectDataModel());

              if (!pSlider->compile(ListOfContainer))
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
  std::vector<QWidget*>::const_reverse_iterator it;

  for (it = v.rbegin(); it != v.rend(); ++it)
    {
      QWidget* widget = *it;
      widget->setHidden(true);
      mpSliderBox->layout()->removeWidget(widget);
    }
}

std::vector<CSlider*>* SliderDialog::getCSlidersForCurrentFolderId()
{
  CDataObject* object = (CDataObject*)getTaskForFolderId(mCurrentFolderId);

  if (!object) return NULL;

  std::vector<CSlider*>* pVector = new std::vector<CSlider*>();

  try
    {
      pVector = getCSlidersForObject(object, pVector);
    }

  catch (...) {}

  return pVector;
}

void SliderDialog::changeEvent(QEvent *event)
{
  if (event->type() == QEvent::EnabledChange && isEnabled() && mpCurrSlider != NULL)
    {
      setFocus(Qt::OtherFocusReason);
      mpScrollView->setFocus(Qt::OtherFocusReason);
      mpSliderBox->setFocus(Qt::OtherFocusReason);
      mpCurrSlider->focusSlider();
    }
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
  CDataModel * pDataModel = pSlider->getObjectDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);
  CObjectInterface::ContainerList listOfContainers;
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
const CDataObject* SliderDialog::determineCorrectObjectForSlider(const CDataObject* pObject)
{
  const CDataObject* pResult = NULL;

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
              if (pMetab->isInitialValueChangeAllowed((CCore::Framework) mFramework) &&
                  pObject == pMetab->getInitialValueReference())
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
              if (pMetab->isInitialValueChangeAllowed((CCore::Framework) mFramework) &&
                  pObject == pMetab->getInitialConcentrationReference())
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
  std::map<ListViews::WidgetType, std::vector<QWidget*> >::iterator it = this->mSliderMap.begin(), endit = this->mSliderMap.end();
  std::vector<QWidget*>::iterator it2, endit2;
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
              const CDataObject* pTmpObj = pSlider->object();
              this->setCorrectSliderObject(pSlider);

              if (pSlider->object() != pTmpObj && !changed)
                {
                  changed = true;
                }
            }

          ++it2;
        }

      ++it;
    }

  // we don't care if the change was for the current
  // task, we just update if there was any change at all
  if (changed == true)
    {
      this->update();
    }
}

/**
 * Takes a CopasiSlider object and checks if the associated model object
 * fits the currently set framework. If not, the slider object and the values are adjusted.
 *
 * On success, true is returned.
 */
bool SliderDialog::setCorrectSliderObject(CopasiSlider* pSlider)
{
  if (pSlider == NULL)
    return false;

  const CDataObject *pObject = NULL, *pTmpObject = NULL;
  pObject = pSlider->object();

  if (pObject == NULL)
    return false;

  pTmpObject = const_cast<CDataObject*>(this->determineCorrectObjectForSlider(pObject));

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
    }

  return true;
}

void SliderDialog::showEvent(QShowEvent* pEvent)
{
  // make sure only valid sliders are shown
  updateAllSliders();
  this->CWindowInterface::showEvent(pEvent);
}

void
SliderDialog::deleteInvalidSliders()
{
  bool sliderDeleted = false;
  std::map< ListViews::WidgetType, std::vector< QWidget* > >::iterator it = mSliderMap.begin();

  for (; it != mSliderMap.end(); ++it)
    {
      if (it->first == ListViews::WidgetType::NotFound)
        continue;

      sliderDeleted |= deleteInvalidSlidersFromFolder(it->first);
    }

  if (sliderDeleted)
    {
      CQMessageBox::information(this, "Invalid Slider",
                                "One or more sliders were invalid and have been deleted!",
                                QMessageBox::Ok, QMessageBox::NoButton);
    }
}

bool
SliderDialog::deleteInvalidSlidersFromFolder(ListViews::WidgetType folderId)
{
  std::vector<QWidget*> &v = mSliderMap[folderId];
  std::vector<QWidget*>::iterator wit = v.begin(), wendit = v.end();
  bool sliderDeleted = false;
  CopasiSlider* pCopasiSlider = NULL;

  std::vector<CopasiSlider*> invalidSliders;

  for (; wit != wendit; ++wit)
    {
      pCopasiSlider = dynamic_cast<CopasiSlider*>(*wit);

      if (pCopasiSlider && !pCopasiSlider->isValid())
        {
          invalidSliders.push_back(pCopasiSlider);
          continue;
        }
    }

  std::vector<CopasiSlider*>::iterator it = invalidSliders.begin();

  for (; it != invalidSliders.end(); ++it)
    {
      (*it)->setParent(NULL);
      removeSlider(*it, folderId);
      sliderDeleted = true;
    }

  return sliderDeleted;
}

/**
 * Resets the SliderDialog to its initial state.
 * It basically calls clear and readds the Label
 * for the task widgets that don't support sliders.
 */
void SliderDialog::reset()
{
  this->clear();
  assert(this->mSliderMap[ListViews::WidgetType::NotFound].size() == 0);
  this->mSliderMap[ListViews::WidgetType::NotFound].push_back(new QLabel("<p>There are no sliders available for this task.<br>If you select one of the tasks that supports<br>sliders in the copasi object tree, this dialog<br>will become active.</p>", NULL));
}

/**
 * Returns whether the slider dialog contains changes.
 */
bool SliderDialog::isChanged() const
{
  return this->mChanged;
}

void SliderDialog::setChanged(bool changed)
{
  this->mChanged = changed;
}

QMenu *SliderDialog::getWindowMenu() const
{
  return mpWindowMenu;
}
