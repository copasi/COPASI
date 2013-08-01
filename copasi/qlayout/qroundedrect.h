#ifndef QROUNDED_RECT
#define QROUNDED_RECT

#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>

class QPainter;

class QRoundedRect : public QGraphicsRectItem
{
public:
  QRoundedRect(qreal x, qreal y, qreal w, qreal h, qreal rx=0, qreal ry=0);
	virtual ~QRoundedRect();
protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option=new QStyleOptionGraphicsItem() ,QWidget *widget=0);

  qreal mRx;
  qreal mRy;
};

#endif