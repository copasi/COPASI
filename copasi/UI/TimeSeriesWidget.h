// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TimeSeriesWidget.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:58:29 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef TSWIDGET_H
#define TSWIDGET_H

#include "UI/copasiWidget.h"
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
//class QPushButton;

class TimeSeriesSubWidget;

class TimeSeriesWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    TimeSeriesWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~TimeSeriesWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    virtual void setFramework(int framework);

  protected slots:
    //virtual void slotBtnCancelClicked();
    //virtual void slotBtnOKClicked();

  public:
    bool loadFromBackend();
    bool saveToBackend();

  protected:
    std::string objKey;
    Q3GridLayout* mWidgetLayout;
    TimeSeriesSubWidget* mCentralWidget;
  };

#endif
