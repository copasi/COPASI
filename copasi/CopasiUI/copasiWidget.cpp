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
      if (minimumSizeHint().width() + 200 > realMinWidth)
        realMinWidth = minimumSizeHint().width() + 200;
      if (minimumSizeHint().height() > realMinHeight)
        realMinHeight = minimumSizeHint().height();
      if ((tmpW != realMinWidth) || (tmpH != realMinHeight))
        {
          QWidget* qParent = topLevelWidget();
          qParent->setMinimumSize(realMinWidth, realMinHeight);
          qParent->resize(realMinWidth, realMinHeight);
        }
      return;
    }
  //after initialization
  //realMinWidth and realMinHeight are set,
  //   QWidget* qParent=topLevelWidget();
  //    QWidget::resize(topLevelWidget()->width(), topLevelWidget()->height());
  QWidget::resize(w, h);
}

void CopasiWidget::resizeEvent (QResizeEvent * event)
{
  int w = event->size().width();
  int h = event->size().height();
  // if (w<realMinWidth)
  //  w=realMinWidth;
  // if (h<realMinHeight)
  //  h=realMinHeight;
  resize(w, h);
  // QWidget::resizeEvent (event);
}
