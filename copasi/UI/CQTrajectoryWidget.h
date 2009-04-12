// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTrajectoryWidget.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/04/12 19:55:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTRAJECTORYWIDGET_H
#define CQTRAJECTORYWIDGET_H

#include <qvariant.h>

#include "ui_CQTrajectoryWidget.h"
/*
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <QLabel>
#include <Q3Frame>

class CTrajectoryProblem;
class CQValidatorInt;
class CQValidatorDouble;

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <Qt3Support/Q3HBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
 */

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
  ~CQTrajectoryWidget();

  virtual bool runTask();

public slots:
  void slotDuration();
  void slotIntervalSize();
  void slotIntervals();
  void updateIntervals();
  void slotOutputDelay(bool checked);

protected:
  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:
  virtual void languageChange();

private:
  CQValidatorInt * mpValidatorIntervals;
  CQValidatorDouble * mpValidatorDelay;
  CQValidatorDouble * mpValidatorIntervalSize;
  CQValidatorDouble * mpValidatorDuration;
  CTrajectoryProblem * mpTrajectoryProblem;

  void init();
  void destroy();
  void checkTimeSeries();
};

#endif // CQTRAJECTORYWIDGET_H
