#include <qlayout/qstyledgraphicsitem.h>
#include <qlayout/qrenderconverter.h>
#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>

#include <QPen>
#include <QBrush>

QStyledGraphicsItem::QStyledGraphicsItem(const CLGraphicalObject* go, const CLRenderResolver* resolver)
  : QCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(go) : NULL)
{
  //setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  QRenderConverter::fillGroupFromStyle(this, &go->getBoundingBox(), mpStyle, mpResolver);

}


QStyledGraphicsItem::~QStyledGraphicsItem()
{
}
