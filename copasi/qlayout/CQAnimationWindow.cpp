// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <limits>

#include <QGraphicsItem>
#include <QGraphicsEffect>
#include <QDockWidget>
#include <QFileDialog>
#include <QDateTime>
#include <QToolBar>
#include <QAbstractEventDispatcher>
#include <QTimer>

#include "copasi/qlayout/CQAnimationWindow.h"
#include "copasi/qlayout/CQAnimationSettingsEditor.h"
#include "copasi/qlayout/CQCopasiAnimation.h"
#include "copasi/qlayout/CQLayoutScene.h"
#include "copasi/qlayout/CQCopasiEffect.h"
#include "copasi/qlayout/CQEffectDescription.h"

#include "copasi/layoutUI/CQSpringLayoutParameterWindow.h"
#include "copasi/layoutUI/CQLayoutThread.h"

#include "copasi/layout/CLayout.h"
#include <copasi/layout/CCopasiSpringLayout.h>
#include <copasi/layout/CLayoutEngine.h>

#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CRootContainer.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"

#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/elementaryFluxModes/CEFMProblem.h"
#include "copasi/elementaryFluxModes/CFluxMode.h"

#include <copasi/report/CDataHandler.h>

#include <copasi/trajectory/CTrajectoryTask.h>

#include "copasi/resourcesUI/CQIconResource.h"

#include "CQElementProperties.h"

class QConservedSpeciesAnimation : public CQCopasiAnimation
{
  virtual void initialize(const CDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CDataVector< CMetab > & metabs = model.getMetabolites();
    CDataVector< CMetab >::const_iterator it = metabs.begin();

    while (it != metabs.end())
      {
        mEntries.push_back(CQEffectDescription(it->getCN()));
        ++it;
      }

    // initialize number of steps
    const CDataVector< CMoiety > & moieties = model.getMoieties();
    mNumSteps = moieties.size();
  }

  virtual void getScales(std::vector<qreal>& scales, int step)
  {
    if (mpDataModel == NULL) return;

    const CModel& model = *mpDataModel->getModel();
    const CDataVector< CMoiety > & moieties = model.getMoieties();
    mNumSteps = moieties.size();

    if (moieties.size() <= (size_t)step) return;

    const CMoiety* moiety = &moieties[step];
    const std::vector<std::pair< C_FLOAT64, CMetab * > > &eqn = moiety->getEquation();
    std::map<std::string, double> cnValueMap;
    std::vector<std::pair< C_FLOAT64, CMetab * > >::const_iterator it = eqn.begin();

    while (it != eqn.end())
      {
        cnValueMap[(*it).second->getCN()] = (*it).first;
        ++it;
      }

    for (size_t i = 0; i < mEntries.size(); ++i)
      scales.push_back(cnValueMap[mEntries[i].getCN()]);
  }
};

/**
 * Animation, that displays one fluxmode per frame
 */
class QFluxModeAnimation : public CQCopasiAnimation
{
public:
  virtual void initialize(const CDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CDataVector< CReaction > & reactions = model.getReactions();
    CDataVector< CReaction >::const_iterator it = reactions.begin();
    size_t count = 0;

    while (it != reactions.end())
      {
        mEntries.push_back(CQEffectDescription(it->getCN(), CQEffectDescription::Colorize, Qt::black, Qt::red));
        indexMap[count] = it->getCN();
        ++it;
        ++count;
      }

    // initialize number of steps
    const CEFMTask *task = dynamic_cast< const CEFMTask * >(&mpDataModel->getTaskList()->operator[]("Elementary Flux Modes"));

    if (task == NULL) return;

    const CEFMProblem* problem = dynamic_cast<const CEFMProblem*>(task->getProblem());

    if (problem == NULL) return;

    const std::vector< CFluxMode >& fluxModes = problem->getFluxModes();
    mNumSteps = fluxModes.size();
  }
  virtual void getScales(std::vector<qreal>& scales, int step)
  {
    if (mpDataModel == NULL) return;

    const CEFMTask *task = dynamic_cast< const CEFMTask * >(&mpDataModel->getTaskList()->operator[]("Elementary Flux Modes"));

    if (task == NULL) return;

    const CEFMProblem* problem = dynamic_cast<const CEFMProblem*>(task->getProblem());

    if (problem == NULL) return;

    const std::vector< CFluxMode >& fluxModes = problem->getFluxModes();
    mNumSteps = fluxModes.size();

    if (fluxModes.size() <= (size_t)step) return;

    const CFluxMode& mode = fluxModes[step];

    const std::vector< const CReaction * > &reordered = problem->getReorderedReactions();
    std::map<std::string, double> cnValueMap;

    CFluxMode::const_iterator modeIt = mode.begin();

    while (modeIt  != mode.end())
      {
        const size_t reactionIndex = (*modeIt).first;
        const double coefficient = (*modeIt).second;
        cnValueMap[reordered[reactionIndex]->getCN()] = qAbs(coefficient);
        ++modeIt;
      }

    for (size_t i = 0; i < mEntries.size(); ++i)
      scales.push_back(cnValueMap[mEntries[i].getCN()] == 0 ? 0.0 : 1.0);
  }

protected:
  std::map<size_t, std::string> indexMap;
};

/**
 * Animation that displays the concentrations per time
 */
class QTimeCourseAnimation : public CQCopasiAnimation
{
public:
  double getMax(const CTimeSeries* series, size_t index = C_INVALID_INDEX)
  {
    double max = 0;

    if (index != C_INVALID_INDEX)
      {
        for (size_t i = 0; i < series->getRecordedSteps(); ++i)
          {
            max = qMax(max, series->getData(i, index));
          }
      }
    else
      {

        for (size_t i = 0; i < series->getRecordedSteps(); ++i)
          {
            for (size_t j = 0; j < series->getNumVariables(); ++j)
              {
                max = qMax(max, series->getData(i, j));
              }
          }
      }

    return max;
  }

  size_t getIndex(const CTimeSeries*series, const std::string& cn)
  {
    const std::string& key = keyMap[cn];

    for (size_t i = 0; i < series->getNumVariables(); ++i)
      if (series->getKey(i) == key)
        return i;

    return C_INVALID_INDEX;
  }

  double getValue(const CTimeSeries* series, const std::string& cn, int step)
  {
    return series->getData(step, getIndex(series, cn));
  }

  virtual void getScales(std::vector<qreal>& scales, int step)
  {
    if (mpDataModel == NULL) return;

    const CTrajectoryTask *task = dynamic_cast< const CTrajectoryTask * >(&mpDataModel->getTaskList()->operator[]("Time-Course"));

    if (task == NULL) return;

    const CTimeSeries* series = &task->getTimeSeries();

    if (series == NULL) return;

    mNumSteps = series->getRecordedSteps();

    if (mNumSteps < step)
      return;

    double max = mMode == CQCopasiAnimation::Global ? getMax(series) : 0;

    for (size_t i = 0; i < mEntries.size(); ++i)
      {
        if (mMode == CQCopasiAnimation::Individual)
          max  = getMax(series, getIndex(series, mEntries[i].getCN()));

        double value = getValue(series, mEntries[i].getCN(), step);
        scales.push_back(value / max);
      }
  }

  virtual void initialize(const CDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CDataVector< CMetab > & metabs = model.getMetabolites();
    CDataVector< CMetab >::const_iterator it = metabs.begin();

    while (it != metabs.end())
      {
        mEntries.push_back(CQEffectDescription(it->getCN(), CQEffectDescription::Scale));
        keyMap[it->getCN()] = it->getKey();
        ++it;
      }

    // initialize number of steps
    const CTrajectoryTask *task = dynamic_cast< const CTrajectoryTask * >(&mpDataModel->getTaskList()->operator[]("Time-Course"));

    if (task == NULL) return;

    const CTimeSeries* series = &task->getTimeSeries();

    if (series == NULL) return;

    mNumSteps = series->getRecordedSteps();
  }
protected:
  std::map<std::string, std::string> keyMap;
};

/**
 * Animation that displays the selected elements per time
 */
class QCustomTimeCourseAnimation : public CQCopasiAnimation
{
  ~QCustomTimeCourseAnimation()
  {
    pdelete(mpDataHandler);
  }

  double getMax(const std::vector< std::vector< C_FLOAT64 > > & data, int index = -1)
  {
    double max = 0;

    if (index != -1)
      {
        for (size_t i = 0; i < data.size(); ++i)
          {
            max = qMax(max, data[i][index]);
          }
      }
    else
      {
        for (size_t j = 0; j < mEntries.size(); ++j)
          {
            index = getIndex(mEntries[j].getCN());

            for (size_t i = 0; i < data.size(); ++i)
              {
                max = qMax(max, data[i][index]);
              }
          }
      }

    return max;
  }

  int getIndex(const std::string& cn)
  {
    for (size_t i = 0; i < mCNs.size(); ++i)
      {
        if (mCNs[i] == cn)
          return i;
      }

    return -1;
  }

  virtual void getScales(std::vector< qreal >& scales, int step)
  {
    auto & data = mpDataHandler->getDuringData();
    mNumSteps = data.size();

    if (mNumSteps < step)
      return;

    double max = mMode == CQCopasiAnimation::Global ? getMax(data) : 0;

    for (size_t i = 0; i < mEntries.size(); ++i)
      {

        int index = getIndex(mEntries[i].getCN());

        if (index == C_INVALID_INDEX)
          {
            scales.push_back(std::numeric_limits< double >::quiet_NaN());
            continue;
          }

        if (mMode == CQCopasiAnimation::Individual)
          max = getMax(data, index);

        if (max == 0)
          max = 1;

        double value = data[step][index];
        scales.push_back(value / max);
      }
  }

  virtual void updateEntries(const std::vector< CQEffectDescription >& entries)
  {
    if (mpDataModel == NULL)
      return;

    // create data handler for it
    pdelete(mpDataHandler);
    mCNs.clear();

    mpDataHandler = new CDataHandler();

    // select elements to record

    for (auto & entry : entries)
      {
        mEntries.push_back(entry);
        mpDataHandler->addDuringName(entry.getDataCN());
        mCNs.push_back(entry.getCN());
      }

    // run task
    CTrajectoryTask & task = const_cast< CTrajectoryTask & >(
                               static_cast< const CTrajectoryTask & >((*mpDataModel->getTaskList())["Time-Course"]));
    task.initialize(CCopasiTask::OUTPUT_DURING, mpDataHandler, NULL);
    task.process(true);
    task.restore();

    mNumSteps = mpDataHandler->getDuringData().size();
  }

  virtual void initialize(const CDataModel & dataModel)
  {
    mpDataModel = &dataModel;

    setScaleMode(Individual);

    std::vector< CQEffectDescription > entries;

    const CModel & model = *dataModel.getModel();
    {
      const CDataVector< CMetab > & metabs = model.getMetabolites();
      CDataVector< CMetab >::const_iterator it = metabs.begin();

      while (it != metabs.end())
        {
          entries.push_back(CQEffectDescription(it->getCN(),
                                                it->getConcentrationReference()->getCN(),
                                                CQEffectDescription::Scale));
          ++it;
        }
    }
    // flux
    {
      const auto & reactions = model.getReactions();
      auto it = reactions.begin();

      while (it != reactions.end())
        {
          entries.push_back(CQEffectDescription(it->getCN(),
                                                it->getFluxReference()->getCN(),
                                                CQEffectDescription::Colorize));
          ++it;
        }
    }

    updateEntries(entries);
  }

protected:
  std::vector< std::string > mCNs;
  CDataHandler * mpDataHandler {NULL};
};

CQAnimationWindow::CQAnimationWindow(CLayout* layout, CDataModel* dataModel)
  : mpScene(NULL)
  , mpModel(NULL)
  , mpWindowMenu(NULL)
  , mAnimation(NULL)
  , mpLayoutThread(NULL)
  , mpCopy(NULL)
  , mpProperties(NULL)
{
  init();
  setScene(new CQLayoutScene(layout, dataModel), dataModel);
}

CQAnimationWindow::CQAnimationWindow()
  : mpScene(NULL)
  , mpModel(NULL)
  , mpWindowMenu(NULL)
  , mAnimation(NULL)
  , mpLayoutThread(NULL)
  , mpCopy(NULL)
  , mpProperties(NULL)
{
  init();
}

void CQAnimationWindow::init()
{
  setupUi(this);
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
  setUnifiedTitleAndToolBarOnMac(true);

  actionAuto_Layout->setIcon(CQIconResource::icon(CQIconResource::play));
  actionRandomize_Layout->setIcon(CQIconResource::icon(CQIconResource::roll));
  actionExport->setIcon(CQIconResource::icon(CQIconResource::fileExport));

  QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
  graphicsView->fillZoomMenu(viewMenu);

  QToolBar* actionToolbar = this->addToolBar("Actions");
  actionToolbar->addAction(actionExport);
  actionToolbar->addAction(actionAuto_Layout);
  actionToolbar->addAction(actionRandomize_Layout);

  QAction * actAnimation = new QAction(this);
  actAnimation->setIcon(CQIconResource::icon(CQIconResource::animation));
  actAnimation->setToolTip("Select animation to display on the layout");
  actAnimation->setMenu(new QMenu());
  actAnimation->menu()->addAction(actionView_Time_Course);
  actAnimation->menu()->addAction(actionView_Elementary_Modes);
  actAnimation->menu()->addAction(actionView_Conserved_Species);
  actAnimation->menu()->addAction(actionView_Custom_Time_Course);
  actAnimation->menu()->addSeparator();
  actAnimation->menu()->addAction(action_Settings);

  actionToolbar->addAction(actAnimation);

  QToolBar* selectToolbar = this->addToolBar("Select");
  graphicsView->fillSelectionToolBar(selectToolbar);

  QToolBar* viewToolBar = this->addToolBar("View");
  graphicsView->fillZoomTooBar(viewToolBar);

  mpWindowMenu = menuBar()->addMenu(tr("&Window"));

  mpLayoutThread = new CQLayoutThread(this);
  connect(mpLayoutThread, SIGNAL(layoutFinished()), this, SLOT(slotStopLayout()));
  connect(mpLayoutThread, SIGNAL(layoutStateChanged(QSharedPointer<CLayoutState>)), this, SLOT(slotLayoutStateChanged(QSharedPointer<CLayoutState>)));

  QDockWidget* pParameterWindow = mpLayoutThread->getParameterWindow();
  addDockWidget(Qt::LeftDockWidgetArea, pParameterWindow);

  QDockWidget * pPropertiesWindow = createPropertiesWidget();
  addDockWidget(Qt::RightDockWidgetArea, pPropertiesWindow);

  viewMenu->addSeparator();
  viewMenu->addAction(pParameterWindow->toggleViewAction());
  viewMenu->addAction(pPropertiesWindow->toggleViewAction());
  toggleUI(false);
}

void CQAnimationWindow::slotExportImage()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Export Image"),
                     "",
                     tr("PDF files (*.pdf);;SVG files (*.svg);;Images (*.png *.xpm *.jpg);;All files (*.*)"));
  graphicsView->slotSaveToFile(fileName);
}

CQAnimationWindow::~CQAnimationWindow()
{
  mpLayoutThread->terminateLayout();

  if (mpCopy != NULL)
    {
      delete mpCopy;
      mpCopy = NULL;
    }

  if (mAnimation != NULL)
    {
      delete mAnimation;
      mAnimation = NULL;
    }

  removeFromMainWindow();

  pdelete(mpScene);
  pdelete(mpLayoutThread);
}

void CQAnimationWindow::setScene(CQLayoutScene* scene, CDataModel* dataModel)
{
  mpModel = dataModel;

  if (mpScene != NULL && mpScene != scene)
    pdelete(mpScene);

  mpScene = scene;
  this->graphicsView->setScene(mpScene);
  mpScene->recreate();
  graphicsView->setDataModel(dataModel, scene->getCurrentLayout());
  this->graphicsView->invalidateScene();
  //setAnimation(new QConservedSpeciesAnimation(), dataModel);
  //setAnimation(new QFluxModeAnimation(), dataModel);
  setAnimation(new QTimeCourseAnimation(), dataModel);
  mpProperties->setScene(mpScene);
}

void CQAnimationWindow::slotSwitchAnimation()
{
  QAction *action = dynamic_cast<QAction *>(sender());

  if (action == NULL) return;

  if (action->text() == "View Time Course")
    {
      setAnimation(new QTimeCourseAnimation(), graphicsView->getDataModel());
    }
  else if (action->text() == "View Elementary Modes")
    {
      setAnimation(new QFluxModeAnimation(), graphicsView->getDataModel());
    }
  else if (action->text() == "View Conserved Species")
    {
      setAnimation(new QConservedSpeciesAnimation(), graphicsView->getDataModel());
    }
  else if (action->text() == "View Custom Time Course")
    {
      setAnimation(new QCustomTimeCourseAnimation(), graphicsView->getDataModel());
    }
}

QMenu *CQAnimationWindow::getWindowMenu() const
{
  return mpWindowMenu;
}

void CQAnimationWindow::setAnimation(CQCopasiAnimation* animation, CDataModel* dataModel)
{
  if (mAnimation != NULL)
    {
      mAnimation->removeFromScene(*mpScene);
      delete mAnimation;
    }

  mAnimation = animation;
  mAnimation->initialize(*dataModel);
  size_t numSteps = mAnimation->getNumSteps();

  if (numSteps > 0)
    {
      mpControls->setVisible(true);
      mpControls->setNumSteps(numSteps);
      slotShowStep(0);
    }
  else
    {
      mpControls->setVisible(false);
      statusBar()->showMessage("No data for the animation! Run task first, and load data.", 1000);
    }
}

void CQAnimationWindow::slotShowStep(int step)
{
  statusBar()->showMessage(QString("Displaying step %1").arg(step + 1), 1000);

  if (mAnimation == NULL) return;

  mAnimation->applyToScene(*mpScene, step);
  mpControls->setNumSteps(mAnimation->getNumSteps());
  mpScene->update();
}

void CQAnimationWindow::closeEvent(QCloseEvent * /*closeEvent*/)
{
  // stop the autolayout
  mpLayoutThread->stopLayout();

  removeFromMainWindow();
}

void CQAnimationWindow::slotEditSettings()
{
  CQAnimationSettingsEditor editor;
  editor.initFrom(mAnimation);

  if (editor.exec() == QDialog::Accepted)
    {
      mAnimation->removeFromScene(*mpScene);
      editor.saveTo(mAnimation);

      slotShowStep(0);
    }
}

void CQAnimationWindow::slotRandomizeLayout()
{
  mpLayoutThread->stopLayout();
  mpLayoutThread->wait();
  CLayoutState::tagLayout(mpScene->getCurrentLayout());
  mpLayoutThread->randomizeLayout(mpScene->getCurrentLayout());
}

void CQAnimationWindow::slotStopLayout()
{
  if (mpCopy != NULL)
    {
      delete mpCopy;
      mpCopy = NULL;
    }

  actionAuto_Layout->setChecked(false);
  actionAuto_Layout->setText("Run Auto Layout");
  actionAuto_Layout->setIcon(CQIconResource::icon(CQIconResource::play));
}

void CQAnimationWindow::slotLayoutStateChanged(QSharedPointer<CLayoutState> state)
{
  state->applyTo(mpScene->getCurrentLayout());
  mpScene->recreate();
}

void CQAnimationWindow::toggleUI(bool isPlaying)
{
  if (isPlaying)
    {
      actionAuto_Layout->setChecked(true);
      actionAuto_Layout->setText("Stop Auto Layout");
      actionAuto_Layout->setIcon(CQIconResource::icon(CQIconResource::pause));
    }
  else
    {
      mpLayoutThread->stopLayout();
    }
}

QDockWidget * CQAnimationWindow::createPropertiesWidget()
{
  QDockWidget * pDockProperties = new QDockWidget(this);
  pDockProperties->setWindowTitle("E&lement Properties");
  mpProperties = new CQElementProperties(this);
  connect(this->graphicsView, SIGNAL(renderInformationChanged()), mpProperties, SLOT(slotRenderInformationChanged()));
  pDockProperties->setWidget(mpProperties);
  pDockProperties->setVisible(false);
  return pDockProperties;
}

/// <summary>
/// Slots the auto layout.
/// </summary>
void CQAnimationWindow::slotAutoLayout()
{
  if (sender() != NULL && !actionAuto_Layout->isChecked())
    {
      mpLayoutThread->stopLayout();
      return;
    }

  toggleUI(true);

  // work on a copy!
  CLayoutState::tagLayout(mpScene->getCurrentLayout());

  if (mpCopy != NULL)
    {
      delete mpCopy;
      mpCopy = NULL;
    }

  mpCopy = new CLayout(*mpScene->getCurrentLayout(), NO_PARENT);
  mpLayoutThread->createSpringLayout(mpCopy, 100000);
}
