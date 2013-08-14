#include <qlayout/qlabelgraphicsitem.h>
#include <qlayout/qrenderconverter.h>
#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>

QLabelGraphicsItem::QLabelGraphicsItem(const CLTextGlyph* textGlyph, const CLRenderResolver* resolver)
  : QGraphicsTextItem(textGlyph->getText().c_str())
  , QCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(textGlyph) : NULL)
{
  //setTextInteractionFlags(Qt::TextEditorInteraction);
  //setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  
  setPos(textGlyph->getBoundingBox().getPosition().getX(),
    textGlyph->getBoundingBox().getPosition().getY());

  QRenderConverter::applyStyle(this, &textGlyph->getBoundingBox(), mpStyle == NULL ? NULL : mpStyle->getGroup(), mpResolver);

}

QLabelGraphicsItem::~QLabelGraphicsItem()
{
}
