// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  Created by Paul on 5/21/10.
 */

#ifndef CQANALYTICSWIDGET_H
#define CQANALYTICSWIDGET_H

//#include <QtCore/QVariant>

#include "ui_CQAnalyticsWidget.h"

#include "UI/TaskWidget.h"

class CCrossSectionProblem;
class CQValidatorInt;
class CQValidatorDouble;

class CQAnalyticsWidget : public TaskWidget, public Ui::CQAnalyticsWidget
{
  Q_OBJECT

public:
  CQAnalyticsWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQAnalyticsWidget();

  virtual bool runTask();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  void commitInput();
  virtual bool saveTask();
  virtual bool loadTask();
  virtual bool taskFinishedEvent();

protected slots:

private:
  void init();
  void destroy();
  void showUnits();

  void updateValues();

  void setSingleObject(const CCopasiObject * pSingleVariable);

  const CCopasiObject * mpSingleVariable;
  CCrossSectionProblem * mpCrossSectionProblem;

  CQValidatorInt * mpValidatorLC;
  CQValidatorDouble * mpValidatorTime;
  CQValidatorDouble * mpValidatorTolerance;
  CQValidatorInt * mpValidatorOutLC;
  CQValidatorDouble * mpValidatorOutTime;
  CQValidatorDouble * mpValidatorOutTolerance;
  CQValidatorDouble * mpValidatorCrossing;

private slots:

  void slotChooseVariable();
  void slotValueRate();
  void slotUpdateCrossings(bool);
  void slotUpdateConvergence(bool);

  void slotOutputDelay(bool);
  void slotOutputCrossings(bool);
  void slotOutputConvergence(bool);

  void slotUpdateTime();
  void slotUpdateConvergenceTolerance();
  void slotUpdateCrossingsLimit();

  void slotOutputConvergenceTolerance();
  void slotOutputCrossingsLimit();
  void slotOutputDelayTime();
};

#endif
