// copasiWidget.cpp: implementation of the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////

#include "copasiWidget.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, WFlags f)
    : QWidget (parent, name, f)
{
  // maxMinWidth=0;
  // maxMinHeight=0;
}

CopasiWidget::~CopasiWidget()
{}

void CopasiWidget::resize (int w, int h)
{
  /* if (w<CopasiWidget::maxMinWidth)
    w=CopasiWidget::maxMinWidth;
   else
    CopasiWidget::maxMinWidth=w;
   if (h<CopasiWidget::maxMinHeight)
    h=CopasiWidget::maxMinHeight;
   else
    CopasiWidget::maxMinHeight=h;
  */ QWidget::resize(w, h);
}
void CopasiWidget::resizeEvent (QResizeEvent *)
{
  int i = 0;
}

void CopasiWidget::resize (const QSize &)
{
  int i = 0;
}
void CopasiWidget::setGeometry (int x, int y, int w, int h)
{
  int i = 0;
}
void CopasiWidget::setGeometry (const QRect &)
{
  int i = 0;
}
