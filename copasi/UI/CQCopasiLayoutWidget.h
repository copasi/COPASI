// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQCopasiLayoutWidget.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2007/02/26 10:31:08 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQCLAYOUTW_H
#define CQCLAYOUTW_H

#include <qaction.h>
#include <qpushbutton.h>

//#include <qvbox.h>
#include "UI/copasiWidget.h"
//#include "mathematics.h"
#include "layoutUI/CQLayoutMainWindow.h"

class QGridLayout;
//class QLineEdit;
class QLabel;
class QTabWidget;

class CQCopasiLayoutWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQCopasiLayoutWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQCopasiLayoutWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    void displayNetworkWidget();

  protected:

    void loadFromBackend();
    void saveToBackend();

    QGridLayout* mWidgetLayout;

    QLabel* mLabelTitle;
    QPushButton* mShowNetworkButton;

    QTabWidget* mpTab;

  private:
    QAction *mDisplayNetwork;
    CQLayoutMainWindow *pWin;
  };

#endif
