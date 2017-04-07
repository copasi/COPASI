// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QPen>
#include <QBrush>

#include <qlayout/CQStyledGraphicsItem.h>
#include <qlayout/CQRenderConverter.h>
#include <qlayout/CQLayoutScene.h>

#include "copasi.h"

#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>

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
