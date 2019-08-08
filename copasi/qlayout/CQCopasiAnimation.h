// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifndef Q_COPASI_ANIMATION_H
#define Q_COPASI_ANIMATION_H

#include <vector>
#include <string>

#include <copasi/qlayout/CQLayoutScene.h>
#include <copasi/CopasiDataModel/CDataModel.h>

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
  virtual void initialize(const CDataModel &model) = 0;
  virtual void getScales(std::vector<qreal>& scales, int step); //= 0;
  virtual void applyToScene(CQLayoutScene& scene, int step);
  virtual int getNumSteps();
  ScaleMode getScaleMode() const;
  void setScaleMode(ScaleMode mode);
  std::vector<CQEffectDescription*>& getEntries();
protected:
  std::vector<CQEffectDescription*> mEntries;
  const CDataModel* mpDataModel;
  ScaleMode mMode;
  int mNumSteps; // populate with the number of steps
};

#endif //Q_COPASI_ANIMATION_H
