#ifndef QCOPASI_EFFECT_H
#define QCOPASI_EFFECT_H

#include <qgraphicseffect.h>

class QPainter; 

class QCopasiEffect : public QGraphicsEffect
{
  Q_OBJECT
public: 
  QCopasiEffect();
  virtual ~QCopasiEffect();
  void setScale(qreal scale);

protected:
  void draw(QPainter* painter);

  qreal mScale;
};

#endif // QCOPASI_EFFECT_H