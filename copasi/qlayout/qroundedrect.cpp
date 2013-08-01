#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

#include <qlayout/qroundedrect.h>

QRoundedRect::QRoundedRect(qreal x, qreal y, qreal w, qreal h, qreal rx, qreal ry)
  : QGraphicsRectItem(x, y, w, h)
  , mRx(rx)
  , mRy(ry)
{
}

QRoundedRect ::~QRoundedRect()
{
}

void QRoundedRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->save();
  painter->setPen(pen());
  painter->setBrush(brush());
  painter->drawRoundedRect(rect(), mRx, mRy);
  painter->restore();
}
