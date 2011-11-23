// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTSSAWidget.h,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/11/23 14:15:20 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTSSAWIDGET_H
#define CQTSSAWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTSSAWidget.h"

class CTSSAProblem;
class CQValidatorInt;
class CQValidatorDouble;

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
  virtual bool taskFinishedEvent();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:

private:
  CTSSAProblem * mpTSSAProblem;
  CQValidatorDouble * mpValidatorDuration;
  CQValidatorDouble * mpValidatorIntervalSize;
  CQValidatorDouble * mpValidatorDelay;
  CQValidatorInt * mpValidatorIntervals;

  void init();
  void destroy();
};

#endif // CQTSSAWIDGET_H
