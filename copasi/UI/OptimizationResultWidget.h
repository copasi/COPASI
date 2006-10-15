/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/OptimizationResultWidget.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef OPTIMIZATIONWIDGET4_H
#define OPTIMIZATIONWIDGET4_H

#include "CopasiUI/copasiWidget.h"
#include "CopasiUI/TimeSeriesSubwidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "optimization/COptProblem.h"
#include "optimization/COptTask.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class StateSubwidget;
class TimeSeriesSubWidget;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class OptimizationWidget;
class QTextEdit;

class OptimizationResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    QPushButton* setInitialState;

    OptimizationResultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0, const int comingFrom = 0);
    ~OptimizationResultWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  public slots:
    virtual void runSetInitialState();

  protected slots:
    //virtual void slotBtnCancelClicked();
    //virtual void slotBtnOKClicked();

  protected:
    bool loadFromBackend();
    bool saveToBackend();
    std::string objKey;

    QGridLayout* mWidgetLayout;
    QHBoxLayout* stateLayout;
    QVBoxLayout* parentLayout;
    StateSubwidget* mCentralWidgetSteady;
    TimeSeriesSubWidget* mCentralWidgetTime;
  };

#endif
