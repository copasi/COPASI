#ifndef QRENDER_CONVERTER_H
#define QRENDER_CONVERTER_H


class CLStyle;
class CLGroup;
class CLRenderResolver;
class CLBoundingBox;
#include <QGraphicsItemGroup>

class QRenderConverter
{
public:
  static void fillGroupFromStyle(QGraphicsItemGroup *group, const CLBoundingBox* bounds, const CLStyle *style, const CLRenderResolver* resolver);
  static void applyStyle(QGraphicsTextItem *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver);
  static void applyStyle(QGraphicsPathItem *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver);
  static void applyStyle(QGraphicsItemGroup *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver);
};

#endif