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

#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

#include <copasi/qlayout/CQRoundedRect.h>

CQRoundedRect::CQRoundedRect(qreal x, qreal y, qreal w, qreal h, qreal rx, qreal ry)
  : QGraphicsRectItem(x, y, w, h)
  , mRx(rx)
  , mRy(ry)
{
}

CQRoundedRect ::~CQRoundedRect()
{
}

void CQRoundedRect::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
  painter->save();
  painter->setPen(pen());
  painter->setBrush(brush());
  painter->drawRoundedRect(rect(), mRx, mRy);
  painter->restore();
}
