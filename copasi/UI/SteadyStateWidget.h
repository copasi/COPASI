// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H

#include "copasi.h"

#include "copasi/UI/ui_SteadyStateWidget.h"

#include "copasi/UI/TaskWidget.h"

class SteadyStateWidget : public TaskWidget, public Ui::SteadyStateWidget
{
  Q_OBJECT

public:
  SteadyStateWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~SteadyStateWidget();

  virtual bool runTask();

protected slots:
  virtual void taskJacobianToggled();

protected:
  virtual bool loadTask();
  virtual bool saveTask();
  virtual bool taskFinishedEvent();

private:
  void init();

protected slots:
};

#endif // STEADYSTATEWIDGET_H
