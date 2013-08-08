#include <qgraphicsitem.h>
#include <qgraphicseffect.h>

#include <qlayout/qanimationwindow.h>
#include <qlayout/qlayoutscene.h>
#include <qlayout/qcopasieffect.h>
#include <report/CCopasiObjectName.h>
#include <report/CCopasiRootContainer.h>
#include <resourcesUI/CQIconResource.h>

qreal linear(qreal a, qreal b, qreal t)
{
    return a * (1 - t) + b * t;
}

/** 
 * Interpolate between a, and b
 * 
 * 0.0 <= t <= 1.0
 */
QColor interpolate(const QColor &a, const QColor &b, float t)
{
  int ah, as, av, aa;
  a.getHsv(&ah, &as, &av, &aa);

  int bh, bs, bv, ba;
  b.getHsv(&bh, &bs, &bv, &ba);

  int rh, rs, rv, ra;
  rh = linear(ah, bh, t);
  rs = linear(as, bs, t);
  rv = linear(av, bv, t);
  ra = linear(aa, ba, t);
    
  return QColor::fromHsv(rh, rs, rv, ra);
}

class QEffectDescription
{
public:
  enum Mode
  {
    DropShadow,
    Colorize,
    Scale
  };

  QEffectDescription(const std::string& cn)
    : mCN(cn)
    , mStartColor(Qt::white)
    , mEndColor(Qt::red)
    , mScaleStart(0.5)
    , mScaleEnd(2.0)
    , mMode(Scale)
  {
  }

  const std::string& getCN()const
  {
    return mCN;
  }

  void applyToScene(QLayoutScene& scene, qreal t)
  {
    QGraphicsItem *item = scene.getItemFor(mCN);
    if (item == NULL)
      return;
    switch(mMode)
    {
    default:
    case DropShadow:
      {
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(&scene);
        effect->setColor(interpolate(mStartColor, mEndColor, t));
        effect->setBlurRadius(25);
        effect->setEnabled(true);
        effect->setOffset(0);
        item->setGraphicsEffect(effect);
      }
      break;
    case Colorize:
      {
        QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(&scene);
        effect->setColor(interpolate(mStartColor, mEndColor, t));
        effect->setStrength(1);
        effect->setEnabled(true);
        item->setGraphicsEffect(effect);
      }
      break;
    case Scale:
      {
        QCopasiEffect* effect = new QCopasiEffect();
        effect->setScale(linear(mScaleStart, mScaleEnd, t));
        effect->setEnabled(true);
        item->setGraphicsEffect(effect);
      }
      break;
    }
  }

protected:
  std::string mCN;
  QColor mStartColor;
  QColor mEndColor;
  qreal  mScaleStart;
  qreal mScaleEnd;
  Mode mMode;
};

class QCopasiAnimation
{
public: 
  virtual ~QCopasiAnimation()
  {
    std::vector<QEffectDescription*>::iterator it = mEntries.begin();
    while(it != mEntries.end())
    {
      delete *it;
      ++it;
    }
    mEntries.clear();
  }
  
  virtual void initialize(const CCopasiDataModel &model) = 0;
  virtual void getScales(std::vector<qreal>& scales, int step) //= 0;
  {
    scales.clear();
    std::vector<QEffectDescription*>::iterator it = mEntries.begin();
    while(it != mEntries.end())
    {
      scales.push_back(step/100.0);
      ++it;
    }
  }
  virtual void applyToScene(QLayoutScene& scene, int step) 
  {
    std::vector<qreal> scales; getScales(scales, step);
    if (scales.size() != mEntries.size())
      return;
    for (size_t i = 0; i < scales.size(); ++i)
    {
      mEntries[i]->applyToScene(scene, scales[i]);
    }
  }
protected:
  std::vector<QEffectDescription*> mEntries;
};
#include <model/CModel.h>
#include <trajectory/CTrajectoryTask.h>
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
    
    double max = mGlobalScaling ?getMax(series) : 0;
    
    for (size_t i = 0; i < mEntries.size(); ++i)
    {
      if (!mGlobalScaling)
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
  const CCopasiDataModel* mpDataModel;
  std::map<std::string, std::string> keyMap;
  bool mGlobalScaling;
};
/*
void applyEffect(QLayoutScene& scene, const std::string& cn, int step, int vis)
{
  QGraphicsItem *item = scene.getItemFor(cn);
  if (item == NULL)
    return;

  if (vis==1)
  {
    QCopasiEffect* effect = new QCopasiEffect();
    effect->setScale(step/50.0);
    effect->setEnabled(true);
    item->setGraphicsEffect(effect);
  }
  if (vis==2)
  {
    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(&scene);
    effect->setColor(QColor(step/100.0*255, 0, 0));
    effect->setStrength(1);
    effect->setEnabled(true);
    item->setGraphicsEffect(effect);
  }
  if (vis==3)
  {
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(&scene);
    effect->setColor(QColor(step/100.0*255, 0, 0));
    effect->setBlurRadius(step);
    effect->setEnabled(true);
    effect->setOffset(0);
    item->setGraphicsEffect(effect);
  }
}*/

QAnimationWindow::QAnimationWindow ()
  : mAnimation(NULL)
{
  setupUi(this);    
  setWindowIcon(CQIconResource::icon(CQIconResource::copasi));
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
  this->graphicsView->invalidateScene();

  mAnimation = new QTimeCourseAnimation();
  mAnimation->initialize(*dataModel);

}



void QAnimationWindow::slotShowStep(int step)
{
  statusBar()->message(QString("Displaying step %1").arg(step), 1000);

  if (mAnimation == NULL) return;
  mAnimation->applyToScene(*mpScene, step);
  //applyEffect(*mpScene,  "CN=Root,Model=BorisEJB,Vector=Compartments[compartment],Vector=Metabolites[MKKK]", step,1);
  //applyEffect(*mpScene,  "CN=Root,Model=BorisEJB,Vector=Compartments[compartment],Vector=Metabolites[MKKK_P]", step,2);
  //applyEffect(*mpScene,  "CN=Root,Model=BorisEJB,Vector=Compartments[compartment],Vector=Metabolites[MKK]", step,3);
  //applyEffect(*mpScene,  "CN=Root,Model=BorisEJB,Vector=Compartments[compartment],Vector=Metabolites[MKK_P]", step,1);
  //applyEffect(*mpScene,  "CN=Root,Model=BorisEJB,Vector=Compartments[compartment],Vector=Metabolites[MKK_PP]", step,2);
  //applyEffect(*mpScene,  "CN=Root,Model=BorisEJB,Vector=Reactions[J0]", step,2);
  //applyEffect(*mpScene,  "CN=Root,Model=BorisEJB,Vector=Reactions[J2]", step,3);
  mpScene->update();
}
