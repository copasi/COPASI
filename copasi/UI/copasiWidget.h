/********************************************************
    Author: Liang Xu
    Version : 1.xx  <first>
    Description: 
    Date: 04/03 
    Comment : CopasiWidget: Provide base class for all widget: for resizable/minimize
    Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#if !defined COPASI_WIDGET_H
#define COPASI_WIDGET_H
#include "qwidget.h"

class ListViews;

class CopasiWidget : public QWidget
  {
  public:
    CopasiWidget(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
    virtual ~CopasiWidget();
    virtual void resizeEvent (QResizeEvent *);
  public slots:
    virtual void resize (int w, int h);
  private:
    static int realMinWidth;
    static int realMinHeight;
    static ListViews* pListView;
  private:
    bool bInitialized;
    bool bSetMinSize;
  };

#endif // !defined(COPASI_WIDGET_H)
