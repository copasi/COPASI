// copasiWidget.cpp: implementation of the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////

#include "copasiWidget.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CopasiWidget::maxMinWidth = 0;
int CopasiWidget::maxMinHeight = 0;

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, WFlags f)
    : QWidget (parent, name, f)
{}

CopasiWidget::~CopasiWidget()
{}

void CopasiWidget::resize (int w, int h)
{
  //need to calculate a minimum size for all widget
  /*
    if (w < maxMinWidth)
      w = maxMinWidth;
    else
      maxMinWidth = w;
    if (h < maxMinHeight)
      h = maxMinHeight;
    else
      maxMinHeight = h;
  */  QWidget::resize(w,  h);
}

void CopasiWidget::resizeEvent (QResizeEvent * event)
{
  int i = 0;
  int w = event->size().width();
  int h = event->size().height();

  /*  if (w < maxMinWidth)
      w = maxMinWidth;
    else
      maxMinWidth = w;
    if (h < maxMinHeight)
      h = maxMinHeight;
    else
      maxMinHeight = h;
  */
  if (w != 1) //if w==1 then means hide,
    QWidget::resizeEvent (event);
}
