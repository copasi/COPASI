// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  Created by Paul on 5/21/10.
 */

#ifndef CQCROSSSECTIONTASKWIDGET_H
#define CQCROSSSECTIONTASKWIDGET_H

//#include <QtCore/QVariant>

#include "ui_CQCrossSectionTaskWidget.h"

#include "UI/TaskWidget.h"

class CCrossSectionProblem;
class CQValidatorInt;
class CQValidatorDouble;

class CQCrossSectionTaskWidget : public TaskWidget, public Ui::CQCrossSectionTaskWidget
{
  Q_OBJECT

public:
  CQCrossSectionTaskWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQCrossSectionTaskWidget();

  virtual bool runTask();
  //virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  void commitInput();
  virtual bool saveTask();
  virtual bool loadTask();
//  virtual bool taskFinishedEvent();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:

private:
  void init();
  void destroy();

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
