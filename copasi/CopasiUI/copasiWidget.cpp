// copasiWidget.cpp: implementation of the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////

#include "copasiWidget.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CopasiWidget::maxMinWidth = 0;
int CopasiWidget::maxMinHeight = 0;
int CopasiWidget::realMinHeight = 0;
int CopasiWidget::realMinWidth = 0;

CopasiWidget::CopasiWidget(QWidget * parent, const char * name, WFlags f)
    : QWidget (parent, name, f)
{
  bInitialized = false;
}

CopasiWidget::~CopasiWidget()
{}

void CopasiWidget::resize (int w, int h)
{
  if (!bInitialized)
    {
      bInitialized = true;
      int tmpW = realMinWidth;
      int tmpH = realMinHeight;
      int t = sizeHint().width();
      t = sizeHint().height();
      if (minimumSizeHint().width() > realMinWidth)
        realMinWidth = minimumSizeHint().width();
      if (minimumSizeHint().height() > realMinHeight)
        realMinHeight = minimumSizeHint().height();
      if ((tmpW != realMinWidth) || (tmpH != realMinHeight))
        {
          QWidget* qParent = topLevelWidget();
          qParent->resize(realMinWidth, realMinHeight);
        }
      //;
      //  if (realMinHeight>Height)
      //   realMinHeight
    }
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
  */  QWidget::resize(minimumSizeHint().width(),  minimumSizeHint().height());
}

void CopasiWidget::resizeEvent (QResizeEvent * event)
{
  //  int i = 0;
  //  int w = event->size().width();
  //  int h = event->size().height();
  resize(0, 0);
  //  if (w!=1) //if w==1 then means hide,
  // QWidget::resizeEvent (event);
}
