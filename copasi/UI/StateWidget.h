/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/30 09:13:51 $
   End CVS Header */

#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
//class QPushButton;

class StateSubwidget;

class StateWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    StateWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~StateWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    //virtual void slotBtnCancelClicked();
    //virtual void slotBtnOKClicked();

  protected:
    bool loadFromBackend();
    bool saveToBackend();
    std::string objKey;

    QGridLayout* mWidgetLayout;

    StateSubwidget* mCentralWidget;
  };

#endif
