/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/StateWidget.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/16 15:34:40 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class StateSubwidget;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class StateWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    QPushButton* setInitialState;

    StateWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~StateWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    bool loadFromBackend();

  public slots:
    virtual void runSetInitialState();

  protected slots:
    //virtual void slotBtnCancelClicked();
    //virtual void slotBtnOKClicked();

  protected:
    bool saveToBackend();
    std::string objKey;

    QGridLayout* mWidgetLayout;
    QHBoxLayout* stateLayout;
    QVBoxLayout* parentLayout;
    StateSubwidget* mCentralWidget;
    bool mUpToDate;
  };

#endif
