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

class QRenderConverter
{
public:
  static void fillGroupFromStyle(QGraphicsItemGroup *group, const CLBoundingBox* bounds, const CLStyle *style, const CLRenderResolver* resolver);
  static void applyStyle(QGraphicsTextItem *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver);
  static void applyStyle(QGraphicsPathItem *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver, QGraphicsItemGroup* itemGroup);
  static void applyStyle(QGraphicsItemGroup *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver);
  static void setBackground(QGraphicsScene *scene, const std::string& fill, const CLRenderResolver* resolver);

};

#endif