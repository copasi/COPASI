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
#include "listviews.h"

class DataModel;

class CopasiWidget : public QWidget
  {
  public:
    CopasiWidget(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
    virtual void resizeEvent (QResizeEvent *);
    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  public slots:
    virtual void resize (int w, int h);
  private:
    static int realMinWidth;
    static int realMinHeight;
  private:
    bool bInitialized;
    bool bSetMinSize;

  protected:
    static DataModel* dataModel;
    ListViews* pListView;
  };

#endif // !defined(COPASI_WIDGET_H)
