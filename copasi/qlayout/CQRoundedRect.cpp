// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

#include <qlayout/CQRoundedRect.h>

CQRoundedRect::CQRoundedRect(qreal x, qreal y, qreal w, qreal h, qreal rx, qreal ry)
  : QGraphicsRectItem(x, y, w, h)
  , mRx(rx)
  , mRy(ry)
{
}

CQRoundedRect ::~CQRoundedRect()
{
}

void CQRoundedRect::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
  painter->save();
  painter->setPen(pen());
  painter->setBrush(brush());
  painter->drawRoundedRect(rect(), mRx, mRy);
  painter->restore();
}
