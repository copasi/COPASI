#include <qlayout/qlabelgraphicsitem.h>
#include <layout/CLGlyphs.h>
#include <layout/CLRenderResolver.h>

QLabelGraphicsItem::QLabelGraphicsItem(const CLTextGlyph* textGlyph, const CLRenderResolver* resolver)
  : QGraphicsTextItem(textGlyph->getText().c_str())
  , QCopasiGraphicsItem(resolver, resolver != NULL ? resolver->resolveStyle(textGlyph) : NULL)
{
  //setTextInteractionFlags(Qt::TextEditorInteraction);
  //setFlag(QGraphicsItem::ItemIsMovable);
  
  setPos(textGlyph->getBoundingBox().getPosition().getX(),
    textGlyph->getBoundingBox().getPosition().getY());
}

QLabelGraphicsItem::~QLabelGraphicsItem()
{
}
