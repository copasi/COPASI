// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQTRAJECTORYWIDGET_H
#define CQTRAJECTORYWIDGET_H

#include <QtCore/QVariant>

#include "ui_CQTrajectoryWidget.h"

class CTrajectoryProblem;
class CQValidatorInt;
class CQValidatorDouble;

#include "TaskWidget.h"

#define TSMAX 10000000

class CQTrajectoryWidget : public TaskWidget, public Ui::CQTrajectoryWidget
{
  Q_OBJECT

public:
  CQTrajectoryWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQTrajectoryWidget();

  virtual bool runTask();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

public slots:
  void slotDuration();
  void slotIntervalSize();
  void slotIntervals();
  void updateIntervals();
  void slotOutputDelay(bool checked);

protected:
  virtual bool saveTask();
  virtual bool loadTask();
  virtual bool taskFinishedEvent();

protected slots:

private:
  CQValidatorInt * mpValidatorIntervals;
  CQValidatorDouble * mpValidatorDelay;
  CQValidatorDouble * mpValidatorIntervalSize;
  CQValidatorDouble * mpValidatorDuration;
  CTrajectoryProblem * mpTrajectoryProblem;

  void init();
  void destroy();
  void checkTimeSeries();
  void showUnits();
};

#endif // CQTRAJECTORYWIDGET_H
