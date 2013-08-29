// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qpainter.h>

#include <qlayout/CQConnectionGraphicsItem.h>
#include <qlayout/CQStyledGraphicsItem.h>
#include <qlayout/CQRenderConverter.h>
#include <qlayout/CQLayoutScene.h>
#include <layout/CLGlyphs.h>
#include <layout/CLReactionGlyph.h>
#include <layout/CLRenderResolver.h>

QSharedPointer<QPainterPath> CQConnectionGraphicsItem::getPath(const CLCurve& curve)
{
  QSharedPointer<QPainterPath> result = QSharedPointer<QPainterPath>(new QPainterPath());

  for (size_t i = 0; i < curve.getNumCurveSegments(); ++i)
    {
      const CLLineSegment* segment = curve.getSegmentAt(i);
      QPainterPath path = QPainterPath(
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

void CQConnectionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->save();
  QGraphicsItemGroup::paint(painter, option, widget);
  painter->restore();
}

void CQConnectionGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  CQLayoutScene * currentScene = dynamic_cast<CQLayoutScene *>(scene());

  if (mWasMoved && currentScene)
    {
      QPointF currentPos = pos();
      currentScene->updatePosition(data(COPASI_LAYOUT_KEY).toString(), currentPos);
      mWasMoved = false;
    }
  else
    {
      QGraphicsItem::mouseReleaseEvent(event);
    }
}

QVariant CQConnectionGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  CQLayoutScene * currentScene = dynamic_cast<CQLayoutScene *>(scene());

  if (change == ItemPositionHasChanged && currentScene)
    {
      mWasMoved = true;
    }

  return QGraphicsItem::itemChange(change, value);
}

CQConnectionGraphicsItem::CQConnectionGraphicsItem(const CLGlyphWithCurve* curveGlyph, const CLRenderResolver* resolver)
  : CQCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(curveGlyph) : NULL)
  , mWasMoved(false)
{
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);
  setData(COPASI_LAYOUT_KEY, QString(curveGlyph->getKey().c_str()));

  QSharedPointer<QPainterPath> path = getPath(curveGlyph->getCurve());
  QGraphicsPathItem* item;
  QGraphicsItemGroup* itemGroup;

  if (curveGlyph->getCurve().getNumCurveSegments() > 0)
    {
      item = new QGraphicsPathItem(*path);
      itemGroup = new QGraphicsItemGroup();
      itemGroup->addToGroup(item);

      if (mpStyle != NULL)
        CQRenderConverter::applyStyle(item, &curveGlyph->getBoundingBox(), mpStyle->getGroup(), resolver, itemGroup);

      addToGroup(itemGroup);
    }

  const CLReactionGlyph* reaction = dynamic_cast<const CLReactionGlyph*>(curveGlyph);

  if (reaction != NULL)
    {
      const CCopasiVector<CLMetabReferenceGlyph> & list = reaction->getListOfMetabReferenceGlyphs();

      for (CCopasiVector<CLMetabReferenceGlyph>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
          const CLMetabReferenceGlyph* metab = *it;
          const CLStyle *style = resolver->resolveStyle(metab);

          if (metab->getCurve().getNumCurveSegments() > 0)
            {
              path = getPath(metab->getCurve());
              item = new QGraphicsPathItem(*path);
              itemGroup = new QGraphicsItemGroup();
              itemGroup->addToGroup(item);
              CQRenderConverter::applyStyle(item, &metab->getBoundingBox(), style == NULL ?
                                            mpStyle == NULL ? NULL :  mpStyle->getGroup()
                                              : style->getGroup(), resolver, itemGroup);
              addToGroup(itemGroup);
            }
        }
    }

  const CLGeneralGlyph* general = dynamic_cast<const CLGeneralGlyph*>(curveGlyph);

  if (general != NULL)
    {
      const CCopasiVector<CLReferenceGlyph> & list = general->getListOfReferenceGlyphs();

      for (CCopasiVector<CLReferenceGlyph>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
          const CLReferenceGlyph* glyph = *it;
          const CLStyle *style = resolver->resolveStyle(glyph);

          if (glyph ->getCurve().getNumCurveSegments() > 0)
            {
              path = getPath(glyph ->getCurve());
              item = new QGraphicsPathItem(*path);
              itemGroup = new QGraphicsItemGroup();
              itemGroup->addToGroup(item);
              CQRenderConverter::applyStyle(item, &glyph ->getBoundingBox(), style == NULL ?
                                            mpStyle == NULL ? NULL :  mpStyle->getGroup()
                                              : style->getGroup(), resolver, itemGroup);
              addToGroup(itemGroup);
            }
        }
    }

  // add decorations on reactions
  itemGroup = new QGraphicsItemGroup();
  CQRenderConverter::fillGroupFromStyle(itemGroup, &curveGlyph->getBoundingBox(), mpStyle, resolver);

  if (itemGroup->childItems().size() > 0)
    addToGroup(itemGroup);
  else
    delete itemGroup;
}

CQConnectionGraphicsItem::~CQConnectionGraphicsItem()
{
}
