// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QCOPASI_EFFECT_H
#define QCOPASI_EFFECT_H

#include <qgraphicseffect.h>

class QPainter;

class CQCopasiEffect : public QGraphicsEffect
{
  Q_OBJECT
public:
  CQCopasiEffect();
  virtual ~CQCopasiEffect();
  void setScale(qreal scale);

protected:
  void draw(QPainter* painter);

  qreal mScale;
};

#endif // QCOPASI_EFFECT_H
