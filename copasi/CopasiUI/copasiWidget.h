// copasiWidget.h: interface for the CopasiWidget class.
//
//////////////////////////////////////////////////////////////////////

#if !defined COPASI_WIDGET_H
#define COPASI_WIDGET_H
#include "qwidget.h"

class CopasiWidget : public QWidget
  {
  public:
    CopasiWidget(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
    virtual ~CopasiWidget();
    void resizeEvent (QResizeEvent *);
  public slots:
    virtual void resize (int w, int h);
    void resize (const QSize &);
    virtual void setGeometry (int x, int y, int w, int h);
    virtual void setGeometry (const QRect &);
  public:
    static unsigned maxMinWidth;
    static unsigned maxMinHeight;
  };

#endif // !defined(COPASI_WIDGET_H)
