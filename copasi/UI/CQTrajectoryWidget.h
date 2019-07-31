// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

public slots:
  void slotDuration();
  void slotIntervalSize();
  void slotIntervals();
  void updateIntervals();
  void slotOutputDelay(bool checked);
  void slotAutomaticIntervals(bool checked);

  void slotOutputEvent(bool checked);
  void slotStartInSteadyState(bool checked);
  void slotSaveOutput(bool checked);

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
  CTrajectoryProblem * mpTrajectoryProblem;

  void init();
  void destroy();
  void checkTimeSeries();
  void showUnits();
};

#endif // CQTRAJECTORYWIDGET_H
