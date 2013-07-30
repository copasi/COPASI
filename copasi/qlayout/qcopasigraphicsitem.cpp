#include <qlayout/qcopasigraphicsitem.h>
#include <layout/CLStyle.h>
#include <layout/CLRenderResolver.h>

QCopasiGraphicsItem::~QCopasiGraphicsItem()
{

}


QCopasiGraphicsItem::QCopasiGraphicsItem(const CLRenderResolver* resolver, const CLStyle* style)
  : mpStyle(style)
  , mpResolver(resolver)
{
  
}

void QCopasiGraphicsItem::setResolver(const CLRenderResolver* resolver)
{
  mpResolver = resolver;
}

const CLRenderResolver* QCopasiGraphicsItem::getResolver() const
{
  return mpResolver;
}


void QCopasiGraphicsItem::setStyle(const CLStyle* style)
{
  mpStyle = style;
}

const CLStyle* QCopasiGraphicsItem::getStyle() const
{
  return mpStyle;
}
