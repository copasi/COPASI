#include <qlayout/qstyledgraphicsitem.h>
#include <qlayout/qrenderconverter.h>
#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>

#include <QPen>
#include <QBrush>

QStyledGraphicsItem::QStyledGraphicsItem(const CLGraphicalObject* go, const CLRenderResolver* resolver)
  : QCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(go) : NULL)
{
  QRenderConverter::fillGroupFromStyle(this, &go->getBoundingBox(), mpStyle, mpResolver);
  //addToGroup(
  //  new QGraphicsRectItem(
  //  go->getBoundingBox().getPosition().getX(), 
  //    go->getBoundingBox().getPosition().getY(), 
  //    go->getBoundingBox().getDimensions().getWidth(), 
  //    go->getBoundingBox().getDimensions().getHeight()
  //  ));    
  //addRect(QRectF(
  //    
  //    ), QPen(Qt::black), QBrush(Qt::darkGreen) );
  //
}


QStyledGraphicsItem::~QStyledGraphicsItem()
{
}
