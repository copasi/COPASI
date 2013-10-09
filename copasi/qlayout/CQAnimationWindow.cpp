// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsEffect>
#include <QtGui/QDockWidget>
#include <QtGui/QFileDialog>
#include <QtCore/QDateTime>
#include <QtGui/QToolBar>

#include <qlayout/CQAnimationWindow.h>
#include <qlayout/CQAnimationSettingsEditor.h>
#include <qlayout/CQCopasiAnimation.h>
#include <qlayout/CQLayoutScene.h>
#include <qlayout/CQCopasiEffect.h>
#include <qlayout/CQEffectDescription.h>

#include <layoutUI/CQSpringLayoutParameterWindow.h>
#include <layoutUI/CQLayoutThread.h>

#include <layout/CLayout.h>

#include <report/CCopasiObjectName.h>
#include <report/CCopasiRootContainer.h>
#include <resourcesUI/CQIconResource.h>

#include <model/CModel.h>
#include <model/CReaction.h>
#include <elementaryFluxModes/CEFMTask.h>
#include <elementaryFluxModes/CEFMProblem.h>
#include <elementaryFluxModes/CFluxMode.h>

class QConservedSpeciesAnimation : public CQCopasiAnimation
{
  virtual void initialize(const CCopasiDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CCopasiVector< CMetab > & metabs = model.getMetabolites();
    CCopasiVector< CMetab >::const_iterator it = metabs.begin();

    while (it != metabs.end())
      {
        mEntries.push_back(new CQEffectDescription((*it)->getCN()));
        ++it;
      }

    // initialize number of steps
    const CCopasiVector< CMoiety > & moieties = model.getMoieties();
    mNumSteps = moieties.size();
  }

  virtual void getScales(std::vector<qreal>& scales, int step)
  {
    if (mpDataModel == NULL) return;

    const CModel& model = *mpDataModel->getModel();
    const CCopasiVector< CMoiety > & moieties = model.getMoieties();
    mNumSteps = moieties.size();

    if (moieties.size() <= (size_t)step) return;

    const CMoiety* moiety = moieties[step];
    const std::vector<std::pair< C_FLOAT64, CMetab * > > &eqn = moiety->getEquation();
    std::map<std::string, double> cnValueMap;
    std::vector<std::pair< C_FLOAT64, CMetab * > >::const_iterator it = eqn.begin();

    while (it != eqn.end())
      {
        cnValueMap[(*it).second->getCN()] = (*it).first;
        ++it;
      }

    for (size_t i = 0; i < mEntries.size(); ++i)
      scales.push_back(cnValueMap[mEntries[i]->getCN()]);
  }
};

/**
 * Animation, that displays one fluxmode per frame
 */
class QFluxModeAnimation : public CQCopasiAnimation
{
public:
  virtual void initialize(const CCopasiDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CCopasiVector< CReaction > & reactions = model.getReactions();
    CCopasiVector< CReaction >::const_iterator it = reactions.begin();
    size_t count = 0;

    while (it != reactions.end())
      {
        mEntries.push_back(new CQEffectDescription((*it)->getCN(), CQEffectDescription::Colorize, Qt::black, Qt::red));
        indexMap[count] = (*it)->getCN();
        ++it;
        ++count;
      }

    // initialize number of steps
    CEFMTask *task = dynamic_cast< CEFMTask * >((*mpDataModel->getTaskList())["Elementary Flux Modes"]);

    if (task == NULL) return;

    const CEFMProblem* problem = dynamic_cast<const CEFMProblem*>(task->getProblem());

    if (problem == NULL) return;

    const std::vector< CFluxMode >& fluxModes = problem->getFluxModes();
    mNumSteps = fluxModes.size();
  }
  virtual void getScales(std::vector<qreal>& scales, int step)
  {
    if (mpDataModel == NULL) return;

    CEFMTask *task = dynamic_cast< CEFMTask * >((*mpDataModel->getTaskList())["Elementary Flux Modes"]);

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
      scales.push_back(cnValueMap[mEntries[i]->getCN()]);
  }

protected:
  std::map<size_t, std::string> indexMap;
};

#include <model/CModel.h>
#include <trajectory/CTrajectoryTask.h>
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

    CTrajectoryTask *task = dynamic_cast< CTrajectoryTask * >((*mpDataModel->getTaskList())["Time-Course"]);

    if (task == NULL) return;

    const CTimeSeries* series = &task->getTimeSeries();

    if (series == NULL) return;

    mNumSteps = series->getRecordedSteps();

    if (series->getRecordedSteps() < (size_t)step)
      return;

    double max = mMode == CQCopasiAnimation::Global ? getMax(series) : 0;

    for (size_t i = 0; i < mEntries.size(); ++i)
      {
        if (mMode == CQCopasiAnimation::Individual)
          max  = getMax(series, getIndex(series, mEntries[i]->getCN()));

        double value = getValue(series, mEntries[i]->getCN(), step);
        scales.push_back(value / max);
      }
  }

  virtual void initialize(const CCopasiDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CCopasiVector< CMetab > & metabs = model.getMetabolites();
    CCopasiVector< CMetab >::const_iterator it = metabs.begin();

    while (it != metabs.end())
      {
        mEntries.push_back(new CQEffectDescription((*it)->getCN(), CQEffectDescription::Scale));
        keyMap[(*it)->getCN()] = (*it)->getKey();
        ++it;
      }

    // initialize number of steps
    CTrajectoryTask *task = dynamic_cast< CTrajectoryTask * >((*mpDataModel->getTaskList())["Time-Course"]);

    if (task == NULL) return;

    const CTimeSeries* series = &task->getTimeSeries();

    if (series == NULL) return;

    mNumSteps = series->getRecordedSteps();
  }
protected:
  std::map<std::string, std::string> keyMap;
};

CQAnimationWindow::CQAnimationWindow(CLayout* layout, CCopasiDataModel* dataModel)
  : mpScene(NULL)
  , mpModel(NULL)
  , mpWindowMenu(NULL)
  , mAnimation(NULL)
#ifdef COPASI_AUTOLAYOUT
  , mpLayoutThread(NULL)
  , mpCopy(NULL)
#endif
{
  init();
  setScene(new CQLayoutScene(layout, dataModel), dataModel);
}

CQAnimationWindow::CQAnimationWindow()
  : mpScene(NULL)
  , mpModel(NULL)
  , mpWindowMenu(NULL)
  , mAnimation(NULL)
#ifdef COPASI_AUTOLAYOUT
  , mpLayoutThread(NULL)
  , mpCopy(NULL)
#endif
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

  QToolBar* selectToolbar = this->addToolBar("Select");
  graphicsView->fillSelectionToolBar(selectToolbar);

  QToolBar* viewToolBar = this->addToolBar("View");
  graphicsView->fillZoomTooBar(viewToolBar);

  mpWindowMenu = menuBar()->addMenu(tr("&Window"));

#ifdef COPASI_AUTOLAYOUT
  mpLayoutThread = new CQLayoutThread(this);
  connect(mpLayoutThread, SIGNAL(layoutFinished()), this, SLOT(slotStopLayout()));
  connect(mpLayoutThread, SIGNAL(layoutStateChanged(QSharedPointer<CLayoutState>)), this, SLOT(slotLayoutStateChanged(QSharedPointer<CLayoutState>)));

  QDockWidget* pParameterWindow = mpLayoutThread->getParameterWindow();
  addDockWidget(Qt::LeftDockWidgetArea, pParameterWindow);
  viewMenu->addSeparator();
  viewMenu->addAction(pParameterWindow->toggleViewAction());
#endif
  toggleUI(false);

#ifndef COPASI_AUTOLAYOUT
  actionAuto_Layout->setEnabled(false);
  actionRandomize_Layout->setEnabled(false);
#endif
}

void CQAnimationWindow::slotExportImage()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Export Image"),
                     "",
                     tr("PDF files (*.pdf);;Images (*.png *.xpm *.jpg);;All files (*.*)"));
  graphicsView->slotSaveToFile(fileName);
}

CQAnimationWindow::~CQAnimationWindow()
{

#ifdef COPASI_AUTOLAYOUT
  mpLayoutThread->terminateLayout();

  if (mpCopy != NULL)
    {
      delete mpCopy;
      mpCopy = NULL;
    }

#endif // COPASI_AUTOLAYOUT

  if (mAnimation != NULL)
    {
      delete mAnimation;
      mAnimation = NULL;
    }

  removeFromMainWindow();
}

void CQAnimationWindow::setScene(CQLayoutScene* scene, CCopasiDataModel* dataModel)
{
  mpModel = dataModel;
  mpScene = scene;
  this->graphicsView->setScene(mpScene);
  mpScene->recreate();
  graphicsView->setDataModel(dataModel, scene->getCurrentLayout());
  this->graphicsView->invalidateScene();
  //setAnimation(new QConservedSpeciesAnimation(), dataModel);
  //setAnimation(new QFluxModeAnimation(), dataModel);
  setAnimation(new QTimeCourseAnimation(), dataModel);
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
}

QMenu *CQAnimationWindow::getWindowMenu() const
{
  return mpWindowMenu;
}

void CQAnimationWindow::setAnimation(CQCopasiAnimation* animation, CCopasiDataModel* dataModel)
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
#ifdef COPASI_AUTOLAYOUT
  // stop the autolayout
  mpLayoutThread->stopLayout();
#endif // COPASI_AUTOLAYOUT
}

void CQAnimationWindow::slotEditSettings()
{
  CQAnimationSettingsEditor editor;
  editor.initFrom(mAnimation);

  if (editor.exec() == QDialog::Accepted)
    {
      editor.saveTo(mAnimation);
    }
}

void CQAnimationWindow::slotRandomizeLayout()
{

#ifdef COPASI_AUTOLAYOUT
  mpLayoutThread->stopLayout();
  mpLayoutThread->wait();
  mpLayoutThread->randomizeLayout(mpScene->getCurrentLayout());
#endif //COPASI_AUTOLAYOUT
}

#include <layout/CCopasiSpringLayout.h>
#include <layout/CLayoutEngine.h>

#include <QtCore/QAbstractEventDispatcher>
#include <QtCore/QAbstractEventDispatcher>

#include <QtCore/QTimer>

void CQAnimationWindow::slotStopLayout()
{
#ifdef COPASI_AUTOLAYOUT

  if (mpCopy != NULL)
    {
      delete mpCopy;
      mpCopy = NULL;
    }

#endif

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
#ifdef COPASI_AUTOLAYOUT
      mpLayoutThread->stopLayout();
#endif //COPASI_AUTOLAYOUT
    }
}

/// <summary>
/// Slots the auto layout.
/// </summary>
void CQAnimationWindow::slotAutoLayout()
{
#ifdef COPASI_AUTOLAYOUT

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

  mpCopy = new CLayout(*mpScene->getCurrentLayout());
  mpLayoutThread->createSpringLayout(mpCopy, 100000);

#endif //COPASI_AUTOLAYOUT
}
