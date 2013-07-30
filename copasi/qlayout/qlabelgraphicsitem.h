#ifndef QLABEL_GRAPHICS_ITEM
#define QLABEL_GRAPHICS_ITEM

#include <QGraphicsTextItem>
#include <qlayout/qcopasigraphicsitem.h>

class CLTextGlyph;
class CLStyle;
class QLabelGraphicsItem : public QGraphicsTextItem, public QCopasiGraphicsItem
{
	Q_OBJECT
public:
  QLabelGraphicsItem(const CLTextGlyph* textGlyph, const CLRenderResolver* resolver=NULL);
	virtual ~QLabelGraphicsItem();
};

#endif