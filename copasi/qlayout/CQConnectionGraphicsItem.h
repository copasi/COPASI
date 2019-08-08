// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QCONNECTION_GRAPHICS_ITEM
#define QCONNECTION_GRAPHICS_ITEM

#include <QGraphicsItemGroup>
#include <QPainterPath>
#include <QtCore/QSharedPointer>
#include <QStyleOptionGraphicsItem>
#include <copasi/layout/CLCurve.h>
#include <copasi/qlayout/CQCopasiGraphicsItem.h>

class CLGlyphWithCurve;
class CLStyle;
class CQConnectionGraphicsItem : public QObject, public CQCopasiGraphicsItem, public QGraphicsItemGroup
{
  Q_OBJECT
public:
  CQConnectionGraphicsItem(const CLGlyphWithCurve* glyph, const CLRenderResolver* resolver = NULL);
  virtual ~CQConnectionGraphicsItem();
  static QSharedPointer<QPainterPath> getPath(const CLCurve& curve);
  virtual QPainterPath shape() const;
  void setUseFullShape(bool useFullShape);
protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem() , QWidget *widget = 0);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
  bool mWasMoved;
  bool mUseFullShape;
  QPainterPath mShape;
  QPainterPath mFullShape;
};

#endif
