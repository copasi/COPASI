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

#ifndef Q_COPASI_ANIMATION_H
#define Q_COPASI_ANIMATION_H

#include <vector>
#include <string>

#include <copasi/qlayout/CQLayoutScene.h>
#include <copasi/CopasiDataModel/CDataModel.h>

class CQEffectDescription;

/**
 * Class for COPASI Animations to display task results onto the
 * graphical diagram.
 */
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

  /**
   * Removes the effect from the scene
   */
  virtual void removeFromScene(CQLayoutScene& scene);

  /**
   * Initializes the animation with elements from the given
   * data model
   */
  virtual void initialize(const CDataModel &model) = 0;

  /**
   * if supported, updated the entries to the ones given
   *
   * @param entries new entries to be used
   */
  virtual void updateEntries(const std::vector< CQEffectDescription > & entries);

  virtual void getScales(std::vector<qreal>& scales, int step); //= 0;

  virtual void applyToScene(CQLayoutScene& scene, int step);

  /**
   * @return the number of data points collected from the task
   */
  virtual int getNumSteps();

  /**
   * @return the scale mode (individual or global) selected
   */
  ScaleMode getScaleMode() const;

  /**
   * Changes the scale mode to the selected one
   */
  void setScaleMode(ScaleMode mode);

  /**
   * @return the vector of all effect descriptions
   */
  std::vector<CQEffectDescription>& getEntries();

protected:

  std::vector<CQEffectDescription> mEntries;
  const CDataModel* mpDataModel;
  ScaleMode mMode;
  int mNumSteps; // populate with the number of steps
};

#endif //Q_COPASI_ANIMATION_H
