#include <qgraphicsitem.h>
#include <qpen.h>
#include <qfont.h>
#include <QFontMetrics>

#include <qlayout/qrenderconverter.h>
#include <qlayout/qroundedrect.h>
#include <layout/CLStyle.h>
#include <layout/CLEllipse.h>
#include <layout/CLRectangle.h>
#include <layout/CLImage.h>
#include <layout/CLPolygon.h>
#include <layout/CLText.h>
#include <layout/CLCurve.h>
#include <layout/CLLinearGradient.h>
#include <layout/CLRadialGradient.h>
#include <layout/CLRenderResolver.h>
#include <layout/CLGraphicalPrimitive1D.h>

QColor getColor(const CLColorDefinition* cd)
{
  if (cd == NULL) return QColor();
  return QColor::fromRgb(cd->getRed(), cd->getGreen(), cd->getBlue(), cd->getAlpha());
}

QColor getColor(const std::string& color, const CLRenderResolver* resolver)
{
  if (resolver->getColorDefinition(color)==NULL && resolver->getGradientBase(color) == NULL)
  {
    CLColorDefinition cd;cd.setColorValue(color);
    return getColor(&cd);
  }
  return getColor(resolver->getColorDefinition(color));
}

QLinearGradient* getLinearGradient(const CLLinearGradient* linear, const CLBoundingBox* bounds, const CLRenderResolver* resolver)
{
  double x1 = bounds->getPosition().getX() + linear->getXPoint1().getAbsoluteValue()  + (linear->getXPoint1().getRelativeValue() / 100.0 * bounds->getDimensions().getWidth());
  double y1 = bounds->getPosition().getY() +linear->getYPoint1().getAbsoluteValue()  + (linear->getYPoint1().getRelativeValue() / 100.0 * bounds->getDimensions().getHeight());
  double x2 = bounds->getPosition().getX() + linear->getXPoint2().getAbsoluteValue()  + (linear->getXPoint2().getRelativeValue() / 100.0 * bounds->getDimensions().getWidth());
  double y2 = bounds->getPosition().getY() + linear->getYPoint2().getAbsoluteValue()  + (linear->getYPoint2().getRelativeValue() / 100.0 * bounds->getDimensions().getHeight());

  QLinearGradient* result = new QLinearGradient(x1, y1, x2, y2);
  switch (linear->getSpreadMethod())
  {
  case CLGradientBase::REFLECT:
    result->setSpread(QConicalGradient::ReflectSpread);
    break;
  case CLGradientBase::REPEAT:
    result->setSpread(QConicalGradient::RepeatSpread);
    break;
  case CLGradientBase::PAD:
    result->setSpread(QConicalGradient::PadSpread);
    break;
  default:
    break;
  }

  for (size_t i = 0; i < linear->getNumGradientStops(); ++i)
  {
    const CLGradientStop* stop = linear->getGradientStop(i);
    result->setColorAt(stop->getOffset().getAbsoluteValue()+ stop->getOffset().getRelativeValue() / 100.0, getColor(stop->getStopColor(), resolver));
  }
  return result;

}

QRadialGradient* getRadialGradient(const CLRadialGradient* radial, const CLBoundingBox* bounds, const CLRenderResolver* resolver)
{
  double cx = radial->getCenterX().getAbsoluteValue()  + radial->getCenterX().getRelativeValue() / 100.0 * bounds->getDimensions().getWidth();
  double cy = radial->getCenterY().getAbsoluteValue()  + radial->getCenterY().getRelativeValue() / 100.0 * bounds->getDimensions().getHeight();
  double fx = radial->getFocalPointX().getAbsoluteValue()  + radial->getFocalPointX().getRelativeValue() / 100.0 * bounds->getDimensions().getWidth();
  double fy = radial->getFocalPointY().getAbsoluteValue()  + radial->getFocalPointY().getRelativeValue() / 100.0 * bounds->getDimensions().getHeight();
  double rx = radial->getRadius().getAbsoluteValue()  + radial->getRadius().getRelativeValue() / 100.0 * bounds->getDimensions().getWidth();
  double ry = radial->getRadius().getAbsoluteValue()  + radial->getRadius().getRelativeValue() / 100.0 * bounds->getDimensions().getHeight();

  QRadialGradient* result = new QRadialGradient(cx, cy, rx, fx, fy);
  switch (radial->getSpreadMethod())
  {
  case CLGradientBase::REFLECT:
    result->setSpread(QConicalGradient::ReflectSpread);
    break;
  case CLGradientBase::REPEAT:
    result->setSpread(QConicalGradient::RepeatSpread);
    break;
  case CLGradientBase::PAD:
    result->setSpread(QConicalGradient::PadSpread);
    break;
  default:
    break;
  }

  for (size_t i = 0; i < radial->getNumGradientStops(); ++i)
  {
    const CLGradientStop* stop = radial->getGradientStop(i);
    result->setColorAt(stop->getOffset().getAbsoluteValue() + stop->getOffset().getRelativeValue() / 100.0, getColor(stop->getStopColor(), resolver));
  }
  return result;
}


QGradient* getGradient(const CLGradientBase* base, const CLBoundingBox* bounds, const CLRenderResolver* resolver)
{
  const CLLinearGradient* linear = dynamic_cast<const CLLinearGradient*>(base);
  if (linear != NULL)
    return getLinearGradient(linear, bounds, resolver);
  const CLRadialGradient* radial = dynamic_cast<const CLRadialGradient*>(base);
  if (radial != NULL)
    return getRadialGradient(radial, bounds, resolver);
  return NULL;

}

QFont* getFont(const CLText *item,const CLGroup *group, const CLRenderResolver* resolver, const CLBoundingBox *pBB)
{
  QString font("Verdana"); double fontSize=10, weight=50; bool italic=false;
  if (item != NULL && item->isSetFontFamily())
    font = item->getFontFamily().c_str();
  else if (group != NULL && group->isSetFontFamily())
    font = group->getFontFamily().c_str();

  if (item != NULL && item->isSetFontSize())
    fontSize = item->getFontSize().getAbsoluteValue() + item->getFontSize().getRelativeValue()/100.0 * pBB->getDimensions().getHeight();
  else if (group != NULL && group->isSetFontSize())
    fontSize = group->getFontSize().getAbsoluteValue() + group->getFontSize().getRelativeValue()/100.0 * pBB->getDimensions().getHeight();

  if (item != NULL && item->isSetFontWeight())
    switch(item->getFontWeight())
  {
    case CLText::WEIGHT_BOLD:
      weight = QFont::Bold;
      break;
    case CLText::WEIGHT_NORMAL:
    default:
      weight = QFont::Normal;
      break;
  }
  else if (group != NULL && group->isSetFontWeight())
    switch(group->getFontWeight())
  {
    case CLText::WEIGHT_BOLD:
      weight = QFont::Bold;
      break;
    case CLText::WEIGHT_NORMAL:
    default:
      weight = QFont::Normal;
      break;
  }

  if (item != NULL && item->isSetFontStyle())
    switch (item->getFontStyle())
  {
    case CLText::STYLE_ITALIC:
      italic = true;
      break;

  }
  else if (group != NULL && group->isSetFontStyle())
    switch (group->getFontStyle())
  {
    case CLText::STYLE_ITALIC:
      italic = true;
      break;

  }

  QFont *result = new QFont(font, -1, weight, italic);
  result->setPixelSizeFloat(fontSize);
  return result;
}

QBrush* getBrush(const CLGraphicalPrimitive2D *item,const CLGroup *group, const CLRenderResolver* resolver, const CLBoundingBox *pBB)
{
  QColor color;
  if (item != NULL && item->isSetFill())
  {
    const CLColorDefinition* cd = resolver->getColorDefinition(item->getFillColor());
    if (cd != NULL)
    {
      return new QBrush( getColor(cd));
    }
    else
    {
      const CLGradientBase* base = resolver->getGradientBase(item->getFillColor());
      if (base != NULL)
      {
        return new QBrush(*getGradient(base, pBB, resolver));
      }
    }
  } 
  else if (group != NULL && group->isSetFill())
  {
    const CLColorDefinition* cd = resolver->getColorDefinition(group->getFillColor());
    if (cd != NULL)
    {
      return new QBrush( getColor(cd));
    }
    else
    {
      const CLGradientBase* base = resolver->getGradientBase(group->getFillColor());
      if (base != NULL)
      {
        return new QBrush(*getGradient(base, pBB, resolver));
      }
    }
  }
  return new QBrush();
}

QPen* getPen(const CLGraphicalPrimitive1D *item,const CLGroup *group, const CLRenderResolver* resolver, const CLBoundingBox *pBB)
{
  QColor color; double width;
  if (item != NULL && item->isSetStroke())
  {
    const CLColorDefinition* cd = resolver->getColorDefinition(item->getStroke());
    if (cd != NULL)
    {
      color = getColor(cd);
    }
  } 
  else if (group != NULL && group->isSetStroke())
  {
    const CLColorDefinition* cd = resolver->getColorDefinition(group->getStroke());
    if (cd != NULL)
    {
      color = getColor(cd);
    }
  }

  if (item != NULL && item->isSetStrokeWidth())
  {
    width = item->getStrokeWidth();
  }
  else if (group != NULL && group->isSetStrokeWidth())
  {
    width = group->getStrokeWidth();
  }

  if (item != NULL && item->isSetDashArray())
  {

  }
  else if (group != NULL && group->isSetDashArray())
  {
  }

  return new QPen(color, width);


}

void fillItemFromEllipse(QGraphicsItemGroup *item, const CLBoundingBox *pBB,const CLEllipse *pEllipse, const CLGroup *group, const CLRenderResolver* resolver)
{
  double x = pBB->getPosition().getX() + pEllipse->getCX().getAbsoluteValue() + pEllipse->getCX().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
  double y = pBB->getPosition().getY() + pEllipse->getCY().getAbsoluteValue() + pEllipse->getCY().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();
  double z = pBB->getPosition().getZ() + pEllipse->getCZ().getAbsoluteValue() + pEllipse->getCZ().getRelativeValue() / 100.0 * pBB->getDimensions().getDepth();
  double rx = pEllipse->getRX().getAbsoluteValue() + pEllipse->getRX().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
  double ry = pEllipse->getRY().getAbsoluteValue() + pEllipse->getRY().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();

  QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(
    x-rx, y-ry, rx*2, ry*2 );
  QPen *pen = getPen(pEllipse, group, resolver, pBB);
  ellipseItem->setPen(*pen);
  delete pen;
  QBrush *brush = getBrush(pEllipse, group, resolver, pBB);
  ellipseItem->setBrush(*brush);
  delete brush;
  item->addToGroup(ellipseItem);
}

void fillItemFromRectangle(QGraphicsItemGroup *item, const CLBoundingBox *pBB,const CLRectangle *pRect, const CLGroup *group, const CLRenderResolver* resolver)
{
  double x = pBB->getPosition().getX() + pRect->getX().getAbsoluteValue() + pRect->getX().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
  double y = pBB->getPosition().getY() + pRect->getY().getAbsoluteValue() + pRect->getY().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();
  double w = pRect->getWidth().getAbsoluteValue() + pRect->getWidth().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
  double h = pRect->getHeight().getAbsoluteValue() + pRect->getHeight().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();
  double rx = pRect->getRadiusX().getAbsoluteValue() + pRect->getRadiusX().getRelativeValue() / 100.0 * pBB->getDimensions().getWidth();
  double ry = pRect->getRadiusY().getAbsoluteValue() + pRect->getRadiusY().getRelativeValue() / 100.0 * pBB->getDimensions().getHeight();

  QGraphicsRectItem* result = new QRoundedRect(
    x,y,w,h,rx,ry);
  QPen *pen = getPen(pRect, group, resolver, pBB);  
  result->setPen(*pen);
  delete pen;
  QBrush *brush = getBrush(pRect, group, resolver, pBB);
  result->setBrush(*brush);
  delete brush;
  item->addToGroup(result);
}

void fillItemFromGroup(QGraphicsItemGroup *item, const CLBoundingBox *bounds,const CLGroup *group, const CLRenderResolver* resolver)
{
  if (group == NULL) 
    return;
  size_t numElements = group->getNumElements();

  if (numElements == 0)
  {
    return;
  }

  for (size_t i = 0; i < numElements; ++i)
  {
    const CCopasiObject* object = group->getElement(i);
    const CLEllipse* ellipse = dynamic_cast<const CLEllipse*>(group->getElement(i));
    const CLRectangle* rect = dynamic_cast<const CLRectangle*>(group->getElement(i));
    const CLPolygon* poly = dynamic_cast<const CLPolygon*>(group->getElement(i));
    const CLCurve* curve = dynamic_cast<const CLCurve*>(group->getElement(i));
    const CLText* text = dynamic_cast<const CLText*>(group->getElement(i));
    const CLImage* image = dynamic_cast<const CLImage*>(group->getElement(i));

    if (ellipse != NULL)
    {
      fillItemFromEllipse(item,bounds, ellipse, group, resolver);      
    }
    else if (rect != NULL)
    {
      fillItemFromRectangle(item,bounds, rect, group, resolver);      
    }

  }

}

void QRenderConverter::applyStyle(QGraphicsPathItem* item, const CLBoundingBox* bounds, const CLGroup *group, const CLRenderResolver* resolver)
{
  if (resolver == NULL || group == NULL || bounds == NULL || item == NULL) 
    return;

  QPen *pen = getPen(NULL, group, resolver, bounds);  
  item->setPen(*pen);
  delete pen;  

}

void QRenderConverter::applyStyle(QGraphicsItemGroup *group, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver)
{
  if (resolver == NULL || style == NULL || bounds == NULL || group== NULL) 
    return;
  for (int i = 0; i < group->childItems().size(); ++i)
  {
  }
}

void QRenderConverter::applyStyle(QGraphicsTextItem *item, const CLBoundingBox* bounds, const CLGroup *style, const CLRenderResolver* resolver)
{
  if (resolver == NULL || style == NULL || bounds == NULL || item == NULL) 
    return;
  
  item->setDefaultTextColor(getColor(style->getFillColor(), resolver));
  QFont *font = getFont(NULL, style, resolver, bounds);

  if (font != NULL)
  {
    item->setFont(*font);
    if (style->isSetTextAnchor() || style->isSetVTextAnchor())
    {
      QFontMetricsF fm(*font);
      //qreal width=fm.width(item->toPlainText()) + 1;  
      qreal width = item->boundingRect().width();
      qreal height = item->boundingRect().height();
      QPointF pos = item->pos();
      
      if (style->isSetTextAnchor() && width  > 0)
      {
        switch(style->getTextAnchor())
        {
        case CLText::ANCHOR_MIDDLE:
          pos.setX(bounds->getPosition().getX() + (bounds->getDimensions().getWidth() - width )/2.0);
          break;
        case CLText::ANCHOR_END:
          pos.setX(bounds->getPosition().getX() + bounds->getDimensions().getWidth() - width );
          break;
        case CLText::ANCHOR_START:
        default:
          break;
        }        
      }

      if (style->isSetVTextAnchor() && height > 0)
      {
        switch (style->getVTextAnchor())
        {
        case CLText::ANCHOR_MIDDLE:
          pos.setY(bounds->getPosition().getY()+(bounds->getDimensions().getHeight()-height)/2.0);
          break;
        case CLText::ANCHOR_BOTTOM:
          pos.setY(bounds->getPosition().getY()+(bounds->getDimensions().getHeight()-height));
          break;
        case CLText::ANCHOR_TOP:          
        default:
          break;
        }
      }

      item->setPos(pos);        
    }
    delete font;
  }

}

void QRenderConverter::fillGroupFromStyle(QGraphicsItemGroup *group, const CLBoundingBox *bounds, const CLStyle *style, const CLRenderResolver* resolver)
{
  if (resolver == NULL || style == NULL|| bounds == NULL || group == NULL) 
    return;
  fillItemFromGroup(group, bounds, style->getGroup(), resolver);
}
