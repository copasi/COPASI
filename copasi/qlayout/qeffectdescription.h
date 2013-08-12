#ifndef QEFFECT_DESCRIPTION_H
#define QEFFECT_DESCRIPTION_H

#include <qcolor.h>
#include <string>

#include <qlayout/qlayoutscene.h>

class QEffectDescription
{
public:
  enum Mode
  {
    DropShadow,
    Colorize,
    Scale
  };

  QEffectDescription(const std::string& cn, qreal startScale, qreal endScale);
  QEffectDescription(const std::string& cn, Mode mode = Colorize, const QColor &startColor=Qt::white, const QColor& endColor=Qt::red);

  const std::string& getCN()const;
  void setCN(const std::string& cn);

  const QColor& getStartColor() const;
  void setStartColor(const QColor& color);

  const QColor& getEndColor() const;
  void setEndColor(const QColor& color);

  qreal getScaleStart() const;
  void setScaleStart(qreal scale);

  qreal getScaleEnd() const;
  void setScaleEnd(qreal scale);

  Mode getMode() const;
  void setMode(Mode mode);

  virtual void removeFromScene(QLayoutScene& scene);

  void applyToScene(QLayoutScene& scene, qreal t);

protected:
  std::string mCN;
  QColor mStartColor;
  QColor mEndColor;
  qreal  mScaleStart;
  qreal mScaleEnd;
  Mode mMode;
};

#endif // QEFFECT_DESCRIPTION_H