// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include <copasi/qlayout/CQCopasiAnimation.h>
#include <copasi/qlayout/CQEffectDescription.h>

CQCopasiAnimation::CQCopasiAnimation():
  mEntries(),
  mpDataModel(NULL),
  mMode(CQCopasiAnimation::Global),
  mNumSteps(0)
{}

CQCopasiAnimation::~CQCopasiAnimation()
{
  mEntries.clear();
}

std::vector<CQEffectDescription>& CQCopasiAnimation::getEntries()
{
  return mEntries;
}

int CQCopasiAnimation::getNumSteps()
{
  return mNumSteps;
}

void CQCopasiAnimation::removeFromScene(CQLayoutScene& scene)
{
  std::vector<CQEffectDescription>::iterator it = mEntries.begin();

  while (it != mEntries.end())
    {
      (*it).removeFromScene(scene);
      ++it;
    }
}

void CQCopasiAnimation::updateEntries(const std::vector< CQEffectDescription > & entries)
{
}

void CQCopasiAnimation::getScales(std::vector< qreal > & scales, int step) //= 0;
{
  scales.clear();
  std::vector<CQEffectDescription>::iterator it = mEntries.begin();

  while (it != mEntries.end())
    {
      scales.push_back(step / 100.0);
      ++it;
    }
}

void CQCopasiAnimation::applyToScene(CQLayoutScene& scene, int step)
{
  std::vector<qreal> scales; getScales(scales, step);

  if (scales.size() != mEntries.size())
    return;

  for (size_t i = 0; i < scales.size(); ++i)
    {
      mEntries[i].applyToScene(scene, scales[i]);
    }
}

CQCopasiAnimation::ScaleMode CQCopasiAnimation::getScaleMode() const
{
  return mMode;
}

void CQCopasiAnimation::setScaleMode(CQCopasiAnimation::ScaleMode mode)
{
  mMode = mode;
}
