// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QROUNDED_RECT
#define QROUNDED_RECT

#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>

class QPainter;

class CQRoundedRect : public QGraphicsRectItem
{
public:
  CQRoundedRect(qreal x, qreal y, qreal w, qreal h, qreal rx = 0, qreal ry = 0);
  virtual ~CQRoundedRect();
protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem(), QWidget *widget = 0);

  qreal mRx;
  qreal mRy;
};

#endif
