#include <qgraphicsitem.h>
#include <qpen.h>

#include <qlayout/qrenderconverter.h>
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

QBrush* getBrush(const CLGraphicalPrimitive2D *item,const CLGroup *group, const CLRenderResolver* resolver, const CLBoundingBox *pBB)
{
  QColor color;
  if (item->isSetFill())
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
  else if (group->isSetFill())
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
  if (item->isSetStroke())
  {
    const CLColorDefinition* cd = resolver->getColorDefinition(item->getStroke());
    if (cd != NULL)
    {
      color = getColor(cd);
    }
  } 
  else if (group->isSetStroke())
  {
    const CLColorDefinition* cd = resolver->getColorDefinition(group->getStroke());
    if (cd != NULL)
    {
      color = getColor(cd);
    }
  }

  if (item->isSetStrokeWidth())
  {
    width = item->getStrokeWidth();
  }
  else if (group->isSetStrokeWidth())
  {
    width = group->getStrokeWidth();
  }

  if (item->isSetDashArray())
  {

  }
  else if (group->isSetDashArray())
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

  QGraphicsRectItem* result = new QGraphicsRectItem(
        x,y,w,h);
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

  for (size_t i = 0; i < group->getNumElements(); ++i)
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

void QRenderConverter::fillGroupFromStyle(QGraphicsItemGroup *group, const CLBoundingBox *bounds, const CLStyle *style, const CLRenderResolver* resolver)
{
  if (resolver == NULL || style == NULL) 
    return;
  fillItemFromGroup(group, bounds, style->getGroup(), resolver);
}
