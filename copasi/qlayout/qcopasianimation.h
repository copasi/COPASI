// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef Q_COPASI_ANIMATION_H
#define Q_COPASI_ANIMATION_H

#include <vector>
#include <string>

#include <qlayout/qlayoutscene.h>
#include <CopasiDataModel/CCopasiDataModel.h>

class CQEffectDescription;
class CQCopasiAnimation
{
public:
  enum ScaleMode
  {
    Global,
    Individual
  };

  CQCopasiAnimation();
  virtual ~CQCopasiAnimation();
  virtual void removeFromScene(CQLayoutScene& scene);
  virtual void initialize(const CCopasiDataModel &model) = 0;
  virtual void getScales(std::vector<qreal>& scales, int step); //= 0;
  virtual void applyToScene(CQLayoutScene& scene, int step);
  virtual int getNumSteps();
  ScaleMode getScaleMode() const;
  void setScaleMode(ScaleMode mode);
  std::vector<CQEffectDescription*>& getEntries();
protected:
  std::vector<CQEffectDescription*> mEntries;
  const CCopasiDataModel* mpDataModel;
  ScaleMode mMode;
  int mNumSteps; // populate with the number of steps
};

#endif //Q_COPASI_ANIMATION_H
