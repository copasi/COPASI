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
  if (w < maxMinWidth)
    w = maxMinWidth;
  else
    maxMinWidth = w;
  if (h < maxMinHeight)
    h = maxMinHeight;
  else
    maxMinHeight = h;
  QWidget::resize(w, h);
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
