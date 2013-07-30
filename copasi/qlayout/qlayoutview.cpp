#include <QWheelEvent>

#include <qlayout/qlayoutscene.h>
#include <qlayout/qlayoutview.h>

QLayoutView::~QLayoutView()
{
}

QLayoutView::QLayoutView(QLayoutScene *scene)
  : QGraphicsView(scene)
{
  setDragMode(QGraphicsView::ScrollHandDrag);
}

void QLayoutView::wheelEvent ( QWheelEvent* event )
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  double scaleFactor = 1.15;
  if(event->delta() > 0) {
    // Zoom in
    scale(scaleFactor, scaleFactor);
  } else {
    // Zooming out
    scale(1.0 / scaleFactor, 1.0 / scaleFactor);
  }
}
