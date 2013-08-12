#include <qgraphicsitem.h>
#include <qgraphicseffect.h>
#include <QFileDialog>

#include <qlayout/qcopasianimation.h>
#include <qlayout/qanimationsettingseditor.h>
#include <qlayout/qanimationwindow.h>
#include <qlayout/qlayoutscene.h>
#include <qlayout/qcopasieffect.h>
#include <qlayout/qeffectdescription.h>
#include <report/CCopasiObjectName.h>
#include <report/CCopasiRootContainer.h>
#include <resourcesUI/CQIconResource.h>

#include <model/CModel.h>
#include <model/CReaction.h>
#include <elementaryFluxModes/CEFMTask.h>
#include <elementaryFluxModes/CEFMProblem.h>
#include <elementaryFluxModes/CFluxMode.h>

class QConservedSpeciesAnimation : public QCopasiAnimation
{
  virtual void initialize(const CCopasiDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CCopasiVector< CMetab > & metabs = model.getMetabolites();
    CCopasiVector< CMetab >::const_iterator it = metabs.begin();
    while(it != metabs.end())
    {
      mEntries.push_back(new QEffectDescription((*it)->getCN()));
      //keyMap[(*it)->getCN()] = (*it)->getKey();
      ++it;
    }
  }

  virtual void getScales(std::vector<qreal>& scales, int step)
  {
   if (mpDataModel == NULL) return;
   const CModel& model = *mpDataModel->getModel();
   const CCopasiVector< CMoiety > & moieties = model.getMoieties();
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
class QFluxModeAnimation : public QCopasiAnimation
{
public:
  virtual void initialize(const CCopasiDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CCopasiVector< CReaction > & reactions = model.getReactions();
    CCopasiVector< CReaction >::const_iterator it = reactions.begin();
    size_t count = 0;
    while(it != reactions.end())
    {
      mEntries.push_back(new QEffectDescription((*it)->getCN(), QEffectDescription::Colorize));
      indexMap[count] = (*it)->getCN();
      ++it;
      ++count;
    }
  }
  virtual void getScales(std::vector<qreal>& scales, int step)
  {
    if (mpDataModel == NULL) return;
    CEFMTask *task = dynamic_cast< CEFMTask * >((*mpDataModel->getTaskList())["Elementary Flux Modes"]);
    if (task == NULL) return;
    const CEFMProblem* problem = dynamic_cast<const CEFMProblem*>(task->getProblem());
    if (problem == NULL) return;
    const std::vector< CFluxMode >& fluxModes = problem->getFluxModes();
    if (fluxModes.size() <= (size_t)step) return;
    const CFluxMode& mode = fluxModes[step];

    const std::vector< const CReaction * > &reordered = problem->getReorderedReactions();
    std::map<std::string, double> cnValueMap;
    
    CFluxMode::const_iterator modeIt = mode.begin();
    while (modeIt  != mode.end())
    {
      const size_t reactionIndex = (*modeIt).first;
      const double coefficient = (*modeIt).second;
      cnValueMap[reordered[reactionIndex]->getCN()] = coefficient;
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
class QTimeCourseAnimation : public QCopasiAnimation
{
public: 
  double getMax(const CTimeSeries* series, size_t index=C_INVALID_INDEX)
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
    const CTimeSeries* series = &task->getTimeSeries();
    if (series->getRecordedSteps() < (size_t)step)
      return;
    
    double max = mMode == QCopasiAnimation::Global ? getMax(series) : 0;
    
    for (size_t i = 0; i < mEntries.size(); ++i)
    {
      if (mMode == QCopasiAnimation::Individual)
        max  = getMax(series, getIndex(series, mEntries[i]->getCN()));
      double value = getValue(series, mEntries[i]->getCN(), step);
      scales.push_back(value/max);
    }
  }

  virtual void initialize(const CCopasiDataModel &dataModel)
  {
    mpDataModel = &dataModel;
    const CModel& model = *dataModel.getModel();
    const CCopasiVector< CMetab > & metabs = model.getMetabolites();
    CCopasiVector< CMetab >::const_iterator it = metabs.begin();
    while(it != metabs.end())
    {
      mEntries.push_back(new QEffectDescription((*it)->getCN()));
      keyMap[(*it)->getCN()] = (*it)->getKey();
      ++it;
    }

  }
protected: 
  std::map<std::string, std::string> keyMap;  
};

QAnimationWindow::QAnimationWindow ()
  : mAnimation(NULL)
{
  setupUi(this);    
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
  setUnifiedTitleAndToolBarOnMac(true);

  QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
  graphicsView->fillZoomMenu(viewMenu);

  QToolBar* viewToolBar = this->addToolBar("View");
  graphicsView->fillZoomTooBar(viewToolBar);
  QToolBar* selectToolbar = this->addToolBar("Select");
  graphicsView->fillSelectionToolBar(selectToolbar);

  mpWindowMenu = menuBar()->addMenu(tr("&Window"));

  addToMainWindow();
}


void QAnimationWindow::slotExportImage()
{
   QString fileName = QFileDialog::getSaveFileName(this, tr("Export Image"),
                            "",
                            tr("PDF files (*.pdf);;Images (*.png *.xpm *.jpg);;All files (*.*)"));
   graphicsView->slotSaveToFile(fileName);
}

QAnimationWindow::~QAnimationWindow ()
{
  if (mAnimation)
  delete mAnimation;
}

void QAnimationWindow::setScene(QLayoutScene* scene, CCopasiDataModel* dataModel)
{
  mpScene = scene;
  this->graphicsView->setScene(mpScene);
  mpScene->recreate();
  graphicsView->setDataModel(dataModel);
  this->graphicsView->invalidateScene();

  //setAnimation(new QConservedSpeciesAnimation(), dataModel);
  //setAnimation(new QFluxModeAnimation(), dataModel);
  setAnimation(new QTimeCourseAnimation(), dataModel);
}

void QAnimationWindow::slotSwitchAnimation()
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



QMenu *QAnimationWindow::getWindowMenu() const
{
  return mpWindowMenu;
}

void QAnimationWindow::setAnimation(QCopasiAnimation* animation, CCopasiDataModel* dataModel)
{
  if (mAnimation != NULL)
  {
    mAnimation->removeFromScene(*mpScene);
    delete mAnimation;    
  }
  mAnimation = animation;
  mAnimation->initialize(*dataModel);
}

void QAnimationWindow::slotShowStep(int step)
{
  statusBar()->message(QString("Displaying step %1").arg(step), 1000);

  if (mAnimation == NULL) return;
    
  mAnimation->applyToScene(*mpScene, step);  
  mpScene->update();
}

void QAnimationWindow::closeEvent(QCloseEvent *closeEvent)
{
  removeFromMainWindow();
}

void QAnimationWindow::slotEditSettings()
{
  QAnimationSettingsEditor editor;
  editor.initFrom(mAnimation);
  if (editor.exec() == QDialog::Accepted)
  {
    editor.saveTo(mAnimation);
  }
}
