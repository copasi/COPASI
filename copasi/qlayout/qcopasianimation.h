#ifndef Q_COPASI_ANIMATION_H
#define Q_COPASI_ANIMATION_H

#include <vector>
#include <string>

#include <qlayout/qlayoutscene.h>
#include <CopasiDataModel/CCopasiDataModel.h>

class QEffectDescription;
class QCopasiAnimation
{
public: 
  enum ScaleMode
  {
    Global, 
    Individual
  };

  QCopasiAnimation();
  virtual ~QCopasiAnimation();
  virtual void removeFromScene(QLayoutScene& scene);
  virtual void initialize(const CCopasiDataModel &model) = 0;
  virtual void getScales(std::vector<qreal>& scales, int step); //= 0;
  virtual void applyToScene(QLayoutScene& scene, int step);
  ScaleMode getScaleMode() const;
  void setScaleMode(ScaleMode mode);
  std::vector<QEffectDescription*>& getEntries();
protected:
  std::vector<QEffectDescription*> mEntries;
  const CCopasiDataModel* mpDataModel;
  ScaleMode mMode;
};


#endif //Q_COPASI_ANIMATION_H