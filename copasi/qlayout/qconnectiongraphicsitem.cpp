#include <qpainter.h>

#include <qlayout/qconnectiongraphicsitem.h>
#include <layout/CLGlyphs.h>
#include <layout/CLReactionGlyph.h>
#include <layout/CLRenderResolver.h>

QPainterPath* QConnectionGraphicsItem::getPath(const CLCurve& curve)
{
  QPainterPath* result = new QPainterPath();
  for (size_t i = 0; i < curve.getNumCurveSegments(); ++i)
  {
    auto segment = curve.getSegmentAt(i);    
    auto path =  QPainterPath(
      QPointF(
      segment->getStart().getX(),
      segment->getStart().getY()));
    if (segment->isBezier())
    {
      path.cubicTo(
        segment->getBase1().getX(), segment->getBase1().getY(),
        segment->getBase2().getX(), segment->getBase2().getY(),
        segment->getEnd().getX(), segment->getEnd().getY()
        );
    }
    else 
    {
      path.lineTo(segment->getEnd().getX(), segment->getEnd().getY());
    }
    result->addPath(path);
  }
  return result;
}

void QConnectionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
  painter->save();
  QGraphicsItemGroup::paint(painter, option, widget);
  painter->restore();
}

QConnectionGraphicsItem::QConnectionGraphicsItem(const CLGlyphWithCurve* curveGlyph, const CLRenderResolver* resolver)
  : QCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(curveGlyph) : NULL)
{
  QPainterPath& path = *getPath(curveGlyph->getCurve());
  QGraphicsPathItem* item = new QGraphicsPathItem(path);
  item->setPen(QPen(Qt::gray, 4));
  addToGroup(item);

  const CLReactionGlyph* reaction = dynamic_cast<const CLReactionGlyph*>(curveGlyph);  
  if (reaction != NULL)
  {
    auto list = reaction->getListOfMetabReferenceGlyphs();
    for(auto it = list.begin(); it != list.end(); ++it)
    {
      path = *getPath((*it)->getCurve());
      item = new QGraphicsPathItem(path);
      item->setPen(QPen(Qt::gray, 4));
      addToGroup(item);
    }
  }
}

QConnectionGraphicsItem::~QConnectionGraphicsItem()
{
}
