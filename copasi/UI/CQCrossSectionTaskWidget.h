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

/*
 *  Created by Paul on 5/21/10.
 */

#ifndef CQCROSSSECTIONTASKWIDGET_H
#define CQCROSSSECTIONTASKWIDGET_H

//#include <QtCore/QVariant>

#include "ui_CQCrossSectionTaskWidget.h"

#include "copasi/UI/TaskWidget.h"

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
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);

protected:
  void commitInput();
  virtual bool saveTaskProtected();
  virtual bool loadTaskProtected();
  virtual bool taskFinishedEvent();

protected slots:

private:
  void init();
  void destroy();
  void showUnits();

  void updateValues();

  void setSingleObject(const CDataObject * pSingleVariable);

  const CDataObject * mpSingleVariable;
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
