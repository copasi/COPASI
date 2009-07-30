// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSAWidget.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/30 16:35:24 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTSSAWIDGET_H
#define CQTSSAWIDGET_H

#include <qvariant.h>
#include "TaskWidget.h"

#include "ui_CQTSSAWidget.h"

class CTSSAProblem;
class CQValidatorInt;
class CQValidatorDouble;
/*
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include "TaskWidget.h"
 */

#define TSSAMAX 10000000

class CQTSSAWidget : public TaskWidget, public Ui::CQTSSAWidget
{
  Q_OBJECT

public:
  CQTSSAWidget(QWidget* parent = 0, const char* name = 0);
  ~CQTSSAWidget();

  virtual bool runTask();

public slots:
  void slotDuration();
  void slotIntervalSize();
  void slotIntervals();

protected:
  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:
  virtual void languageChange();

private:
  CTSSAProblem * mpTSSAProblem;
  CQValidatorDouble * mpValidatorDuration;
  CQValidatorDouble * mpValidatorIntervalSize;
  CQValidatorDouble * mpValidatorDelay;
  CQValidatorInt * mpValidatorIntervals;

  void init();
  void destroy();
  void checkTimeSeries();
};

#endif // CQTSSAWIDGET_H
