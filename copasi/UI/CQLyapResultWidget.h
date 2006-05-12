/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapResultWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/12 13:49:16 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQLYAPRESULT_H
#define CQLYAPRESULT_H

#include "copasiWidget.h"
//#include "CopasiDataModel/CCopasiDataModel.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTextEdit;

class CQLyapResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQLyapResultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQLyapResultWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    bool loadFromBackend();
    //bool saveToBackend();
    //std::string objKey;

    //QGridLayout* mWidgetLayout;
    //QHBoxLayout* stateLayout;
    QVBoxLayout* parentLayout;
    //    StateSubwidget* mCentralWidgetSteady;
    //    TimeSeriesSubWidget* mCentralWidgetTime;
  };

#endif
