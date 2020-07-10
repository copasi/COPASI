// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H

#include "copasi/copasi.h"

#include "copasi/UI/ui_SteadyStateWidget.h"

#include "copasi/UI/TaskWidget.h"

class SteadyStateWidget : public TaskWidget, public Ui::SteadyStateWidget
{
  Q_OBJECT

public:
  SteadyStateWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~SteadyStateWidget();

  virtual bool runTask();

protected slots:
  virtual void taskJacobianToggled();

protected:
  virtual bool loadTaskProtected();
  virtual bool saveTaskProtected();
  virtual bool taskFinishedEvent();

private:
  void init();

protected slots:
};

#endif // STEADYSTATEWIDGET_H
