#ifndef QCONNECTION_GRAPHICS_ITEM
#define QCONNECTION_GRAPHICS_ITEM

#include <QGraphicsItemGroup>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>
#include <layout/CLCurve.h>
#include <qlayout/qcopasigraphicsitem.h>

class CLGlyphWithCurve;
class CLStyle;
class QConnectionGraphicsItem : public QObject, public QCopasiGraphicsItem, public QGraphicsItemGroup
{
  Q_OBJECT
public:
  QConnectionGraphicsItem(const CLGlyphWithCurve* glyph, const CLRenderResolver* resolver=NULL);
  virtual ~QConnectionGraphicsItem();
  static QPainterPath* getPath(const CLCurve& curve);

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option=new QStyleOptionGraphicsItem() ,QWidget *widget=0);

};

#endif