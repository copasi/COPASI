/****************************************************************************
 **  $ CopasiUI/FunctionWidget.h               
 **  $ Author  : Mrinmayee  Kulkarni
 **  
 ** This is the header file for the Function Widget, i.e the First level 
 ** widget which shows the table of function names and types
 *****************************************************************************/

#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <qtable.h>
#include "copasi.h"
#include "copasiWidget.h"

class QTable;
class MyTable;

class FunctionWidget : public CopasiWidget
  {
    Q_OBJECT

  protected:
    MyTable *table;
    bool binitialized;
    std::vector<std::string> mKeys;

  public:
    FunctionWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void resizeEvent(QResizeEvent * re);

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

    virtual void slotTableSelectionChanged();
    virtual void tableValueChanged(int, int);

  private:
    void fillTable();
    void createNewObject();
  };

#endif
