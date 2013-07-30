#ifndef QRENDER_CONVERTER_H
#define QRENDER_CONVERTER_H


class CLStyle;
class CLRenderResolver;
class CLBoundingBox;
#include <QGraphicsItemGroup>

class QRenderConverter
{
public:
  static void fillGroupFromStyle(QGraphicsItemGroup *group, const CLBoundingBox* bounds, const CLStyle *style, const CLRenderResolver* resolver);
};

#endif