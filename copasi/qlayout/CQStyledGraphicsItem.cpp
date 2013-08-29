// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qlayout/CQStyledGraphicsItem.h>
#include <qlayout/CQRenderConverter.h>
#include <qlayout/CQLayoutScene.h>
#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>

#include <QPen>
#include <QBrush>

CQStyledGraphicsItem::CQStyledGraphicsItem(const CLGraphicalObject* go, const CLRenderResolver* resolver)
  : CQCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(go) : NULL)
  , mWasMoved(false)
{
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);
  setData(COPASI_LAYOUT_KEY, QString(go->getKey().c_str()));
  CQRenderConverter::fillGroupFromStyle(this, &go->getBoundingBox(), mpStyle, mpResolver);
}

CQStyledGraphicsItem::~CQStyledGraphicsItem()
{
}

void CQStyledGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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

QVariant CQStyledGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  CQLayoutScene * currentScene = dynamic_cast<CQLayoutScene *>(scene());

  if (change == ItemPositionHasChanged && currentScene)
    {
      mWasMoved = true;
    }

  return QGraphicsItem::itemChange(change, value);
}
