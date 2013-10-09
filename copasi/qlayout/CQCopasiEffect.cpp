// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qlayout/CQCopasiEffect.h>

#include <QtGui/QPainter>
#include <QtGui/QGraphicsEffect>

CQCopasiEffect::CQCopasiEffect()
  : mScale(1.0)
{
}

CQCopasiEffect::~CQCopasiEffect()
{
}

void CQCopasiEffect::setScale(qreal scale)
{
  mScale = scale;
}

void CQCopasiEffect::draw(QPainter* painter)
{
  QPoint offset;
  const QPixmap pixmap = sourcePixmap(Qt::DeviceCoordinates, &offset);

  if (pixmap.isNull())
    return;

  painter->save();
  painter->setWorldTransform(QTransform());
  QRectF rect = pixmap.rect();

  QTransform trans = QTransform::fromScale(mScale, mScale);
  QPixmap transformed = pixmap.transformed(trans, Qt::SmoothTransformation);
  QRectF transRect = transformed.rect();

  QPointF newOffset = offset + (rect.center() - transRect.center());

  painter->drawPixmap(newOffset, transformed);
  painter->restore();
}
