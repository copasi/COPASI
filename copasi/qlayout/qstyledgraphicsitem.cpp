// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qlayout/qstyledgraphicsitem.h>
#include <qlayout/qrenderconverter.h>
#include <qlayout/qlayoutscene.h>
#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>

#include <QPen>
#include <QBrush>

QStyledGraphicsItem::QStyledGraphicsItem(const CLGraphicalObject* go, const CLRenderResolver* resolver)
  : QCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(go) : NULL)
  , mWasMoved(false)
{
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);
  setData(COPASI_LAYOUT_KEY, QString(go->getKey().c_str()));
  QRenderConverter::fillGroupFromStyle(this, &go->getBoundingBox(), mpStyle, mpResolver);
}

QStyledGraphicsItem::~QStyledGraphicsItem()
{
}

void QStyledGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QLayoutScene * currentScene = dynamic_cast<QLayoutScene *>(scene());

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

QVariant QStyledGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  QLayoutScene * currentScene = dynamic_cast<QLayoutScene *>(scene());

  if (change == ItemPositionHasChanged && currentScene)
    {
      mWasMoved = true;
    }

  return QGraphicsItem::itemChange(change, value);
}
