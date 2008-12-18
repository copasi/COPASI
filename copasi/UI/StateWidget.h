// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateWidget.h,v $
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

#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include "UI/copasiWidget.h"
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class StateSubwidget;
class QPushButton;
class Q3HBoxLayout;
class Q3VBoxLayout;

class StateWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    QPushButton* setInitialState;

    StateWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
    ~StateWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    bool loadFromBackend();

  protected slots:
    //virtual void slotBtnCancelClicked();
    //virtual void slotBtnOKClicked();

  protected:
    bool saveToBackend();
    std::string objKey;

    Q3GridLayout* mWidgetLayout;
    Q3HBoxLayout* stateLayout;
    Q3VBoxLayout* parentLayout;
    StateSubwidget* mCentralWidget;
    bool mUpToDate;
  };

#endif
