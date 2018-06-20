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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQTSSAWIDGET_H
#define CQTSSAWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQTSSAWidget.h"

class CTSSATask;
class CTSSAProblem;
class CTSSAMethod;
class CQValidatorInt;
class CQValidatorDouble;

class CQTSSAWidget : public TaskWidget, public Ui::CQTSSAWidget
{
  Q_OBJECT

public:
  CQTSSAWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQTSSAWidget();

  virtual bool runTask();

public slots:
  void slotDuration();
  void slotIntervalSize();
  void slotIntervals();

protected:
  virtual bool saveTaskProtected();
  virtual bool loadTaskProtected();
  virtual bool taskFinishedEvent();

protected slots:

private:
  CTSSATask* mpCTSSATask;
  CTSSAProblem* mpTSSAProblem;
  CTSSAMethod* mpTSSMethod;
  CQTSSAResultSubWidget* mpTSSResultSubWidget;

  CQValidatorDouble* mpValidatorDuration;
  CQValidatorDouble* mpValidatorIntervalSize;
  CQValidatorDouble* mpValidatorDelay;
  CQValidatorInt* mpValidatorIntervals;

  void init();
  void destroy();
};

#endif // CQTSSAWIDGET_H
