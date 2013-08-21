// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QSTYLED_GRAPHICS_ITEM
#define QSTYLED_GRAPHICS_ITEM

#include <QGraphicsItemGroup>
#include <qlayout/qcopasigraphicsitem.h>

class CLGraphicalObject;
class CLStyle;
class CLRenderResolver;
class QMouseEvent;
class QStyledGraphicsItem : public QObject, public QCopasiGraphicsItem, public QGraphicsItemGroup
{
  Q_OBJECT
public:
  QStyledGraphicsItem(const CLGraphicalObject* go, const CLRenderResolver* resolver = NULL);
  virtual ~QStyledGraphicsItem();
protected:
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  bool mWasMoved;
};

#endif
