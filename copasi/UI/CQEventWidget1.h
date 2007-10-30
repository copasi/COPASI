// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventWidget1.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/30 16:08:52 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef EVENT_WIDGET1_H
#define EVENT_WIDGET1_H

#include "UI/copasiWidget.h"

//class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
//class QCheckBox;
//class QComboBox;
//class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class MyLineEdit;

class CEvent;

class CQEventWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQEventWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQEventWidget1();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();
    virtual void slotBtnNewClicked();
    virtual void slotBtnDeleteClicked();

    virtual void slotNameChanged();

  protected:
    bool loadFromEvent(const CEvent* pEvent);
    bool saveToEvent();

    std::string objKey;

    QGridLayout* EventWidget1Layout;
    QHBoxLayout* Layout1;
    QLabel* TextLabel4;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QPushButton* newReaction;
    QPushButton* deleteReaction;
    QFrame* Line2;
    QLineEdit* LineEdit1;
  };

#endif
