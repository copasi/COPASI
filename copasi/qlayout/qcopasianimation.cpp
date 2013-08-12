#include <qlayout/qcopasianimation.h>
#include <qlayout/qeffectdescription.h>

QCopasiAnimation::QCopasiAnimation()
  : mMode(QCopasiAnimation::Global)
{
}

QCopasiAnimation::~QCopasiAnimation()
{
  std::vector<QEffectDescription*>::iterator it = mEntries.begin();
  while(it != mEntries.end())
  {
    delete *it;
    ++it;
  }
  mEntries.clear();
}
std::vector<QEffectDescription*>& QCopasiAnimation::getEntries()
{
  return mEntries;
}
void QCopasiAnimation::removeFromScene(QLayoutScene& scene)
{
  std::vector<QEffectDescription*>::iterator it = mEntries.begin();
  while(it != mEntries.end())
  {
    (*it)->removeFromScene(scene);
    ++it;
  }
}

void QCopasiAnimation::getScales(std::vector<qreal>& scales, int step) //= 0;
{
  scales.clear();
  std::vector<QEffectDescription*>::iterator it = mEntries.begin();
  while(it != mEntries.end())
  {
    scales.push_back(step/100.0);
    ++it;
  }
}
void QCopasiAnimation::applyToScene(QLayoutScene& scene, int step) 
{
  std::vector<qreal> scales; getScales(scales, step);
  if (scales.size() != mEntries.size())
    return;
  for (size_t i = 0; i < scales.size(); ++i)
  {
    mEntries[i]->applyToScene(scene, scales[i]);
  }
}

QCopasiAnimation::ScaleMode QCopasiAnimation::getScaleMode() const
{
  return mMode;
}

void QCopasiAnimation::setScaleMode(QCopasiAnimation::ScaleMode mode)
{
  mMode = mode;
}
