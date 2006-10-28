/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CMCAResultWidget.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/28 00:26:44 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CMCAResultWidget_H__
#define CMCAResultWidget_H__

#include "UI/copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
//class QPushButton;

class CMCAResultSubwidget;

class CMCAResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CMCAResultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CMCAResultWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    bool loadFromBackend();
    bool saveToBackend();
    std::string objKey;

    QGridLayout* mWidgetLayout;

    CMCAResultSubwidget* mCentralWidget;
  };

#endif
