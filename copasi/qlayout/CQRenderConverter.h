// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QRENDER_CONVERTER_H
#define QRENDER_CONVERTER_H

class CLStyle;
class CLGroup;
class CLRenderResolver;
class CLBoundingBox;
class QGraphicsScene;
class QGraphicsItemGroup;

#include <QGraphicsItemGroup>

#include <string>

class CQRenderConverter
{
public:
  static void fillGroupFromStyle(QGraphicsItemGroup *group, const CLBoundingBox* bounds, const CLStyle *style, const CLRenderResolver* resolver);
  static bool applyStyle(QGraphicsTextItem *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver);
  static bool applyStyle(QGraphicsPathItem *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver, QGraphicsItemGroup* itemGroup);
  static bool applyStyle(QGraphicsItemGroup *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver);
  static void setBackground(QGraphicsScene *scene, const std::string& fill, const CLRenderResolver* resolver);
};

#endif
