#ifndef QSTYLED_GRAPHICS_ITEM
#define QSTYLED_GRAPHICS_ITEM

#include <QGraphicsItemGroup>
#include <qlayout/qcopasigraphicsitem.h>

class CLGraphicalObject;
class CLStyle;
class CLRenderResolver;
class QStyledGraphicsItem : public QObject, public QCopasiGraphicsItem, public QGraphicsItemGroup
{
	Q_OBJECT
public:
	QStyledGraphicsItem(const CLGraphicalObject* go, const CLRenderResolver* resolver=NULL);
	virtual ~QStyledGraphicsItem();

};

#endif