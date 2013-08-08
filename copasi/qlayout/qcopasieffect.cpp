#include <qlayout/qcopasieffect.h>

#include <QPainter>
#include <qgraphicseffect.h>

QCopasiEffect::QCopasiEffect()
  :mScale(1.0)
{
}

QCopasiEffect::~QCopasiEffect()
{
}

void QCopasiEffect::setScale(qreal scale)
{
  mScale = scale;
}

void QCopasiEffect::draw(QPainter* painter)
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
