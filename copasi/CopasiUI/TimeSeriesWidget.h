/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TimeSeriesWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/23 14:58:14 $
   End CVS Header */

#ifndef TSWIDGET_H
#define TSWIDGET_H

#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
//class QPushButton;

class TimeSeriesSubWidget;

class TimeSeriesWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    TimeSeriesWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~TimeSeriesWidget();

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

    QGridLayout* TimeSeriesWidgetLayout;

    TimeSeriesSubWidget* mCentralWidget;
  };

#endif
