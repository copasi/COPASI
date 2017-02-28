// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QCOPASI_EFFECT_H
#define QCOPASI_EFFECT_H

#include <QGraphicsEffect>

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
