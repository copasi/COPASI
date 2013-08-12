#include <qgraphicsitem.h>
#include <qgraphicseffect.h>

#include <qlayout/qeffectdescription.h>
#include <qlayout/qcopasieffect.h>

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

QEffectDescription::QEffectDescription(const std::string& cn, Mode mode, const QColor &startColor, const QColor& endColor)
  : mCN(cn)
  , mStartColor(startColor)
  , mEndColor(endColor)
  , mScaleStart(0.5)
  , mScaleEnd(2.0)
  , mMode(mode)
{
}

QEffectDescription::QEffectDescription(const std::string& cn, qreal startScale, qreal endScale)
  : mCN(cn)
  , mStartColor(Qt::white)
  , mEndColor(Qt::red)
  , mScaleStart(startScale)
  , mScaleEnd(endScale)
  , mMode(Scale)
{
}

const std::string& QEffectDescription::getCN()const
{
  return mCN;
}

const QColor& QEffectDescription::getStartColor() const
{
  return mStartColor;
}

const QColor& QEffectDescription::getEndColor() const
{
  return mEndColor;
}

qreal QEffectDescription::getScaleStart() const
{
  return mScaleStart;
}

qreal QEffectDescription::getScaleEnd() const
{
  return mScaleEnd;
}

QEffectDescription::Mode QEffectDescription::getMode() const
{
  return mMode;
}
void QEffectDescription::setMode(QEffectDescription::Mode mode)
{
  mMode = mode;
}

void QEffectDescription::removeFromScene(QLayoutScene& scene)
{
  QGraphicsItem *item = scene.getItemFor(mCN);
  if (item == NULL)
    return;
  QGraphicsEffect* effect = item->graphicsEffect();
  if (effect == NULL)
    return;
  effect->setEnabled(false);    
}

void QEffectDescription::applyToScene(QLayoutScene& scene, qreal t)
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


void QEffectDescription::setCN(const std::string& cn)
{
  mCN = cn;
}

void QEffectDescription::setStartColor(const QColor& color)
{
  mStartColor = color;
}

void QEffectDescription::setEndColor(const QColor& color)
{
  mEndColor = color;
}

void QEffectDescription::setScaleStart(qreal scale)
{
  mScaleStart = scale;
}

void QEffectDescription::setScaleEnd(qreal scale)
{
  mScaleEnd = scale;
}

