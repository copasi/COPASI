// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQTIMESENSWIDGET_H
#define CQTIMESENSWIDGET_H

#include <QtCore/QVariant>

#include "ui_CQTimeSensWidget.h"

class CTimeSensProblem;
class CQValidatorInt;
class CQValidatorDouble;

#include "TaskWidget.h"

#define TSMAX 10000000

class CQTimeSensWidget : public TaskWidget, public Ui::CQTimeSensWidget
{
  Q_OBJECT

public:
  CQTimeSensWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQTimeSensWidget();

  virtual bool runTask();

public slots:
  void slotDuration();
  void slotIntervalSize();
  void slotIntervals();
  void updateIntervals();
  void slotOutputDelay(bool checked);
  void slotAutomaticIntervals(bool checked);

  void slotAddParameter();
  void slotRemoveParameter();
  void slotAddTarget();
  void slotRemoveTarget();

protected:
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool saveTaskProtected();
  virtual bool loadTaskProtected();
  virtual bool taskFinishedEvent();

protected slots:

private:
  CQValidatorInt * mpValidatorIntervals;
  CQValidatorDouble * mpValidatorDelay;
  CQValidatorDouble * mpValidatorIntervalSize;
  CQValidatorDouble * mpValidatorDuration;
  CTimeSensProblem  * mpTimeSensProblem;

  void init();
  void destroy();
  void checkTimeSeries();
  void showUnits();
};

#endif // CQTIMESENSWIDGET_H
