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
  public:
    static int maxMinWidth;
    static int maxMinHeight;
    static int realMinWidth;
    static int realMinHeight;
  private:
    bool bInitialized;
  };

#endif // !defined(COPASI_WIDGET_H)
