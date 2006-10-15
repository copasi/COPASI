/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TimeSeriesWidget.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:34 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TSWIDGET_H
#define TSWIDGET_H

#include "CopasiUI/copasiWidget.h"

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

    QGridLayout* mWidgetLayout;

    TimeSeriesSubWidget* mCentralWidget;
  };

#endif
