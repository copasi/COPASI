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
void CopasiWidget::resizeEvent (QResizeEvent * event)
{
  int i = 0;
  QWidget::resizeEvent (event);
}

void CopasiWidget::resize (const QSize & newSize)
{
  int i = 0;
  QWidget::resize(newSize);
}
void CopasiWidget::setGeometry (int x, int y, int w, int h)
{
  int i = 0;
  QWidget::setGeometry(x, y, w, h);
}
void CopasiWidget::setGeometry (const QRect & rect)
{
  int i = 0;
  QWidget::setGeometry(rect);
}
