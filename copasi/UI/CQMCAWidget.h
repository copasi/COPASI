// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQMCAWIDGET_H
#define CQMCAWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQMCAWidget.h"

class CQMCAWidget : public TaskWidget, public Ui::CQMCAWidget
{
  Q_OBJECT

public:
  CQMCAWidget(QWidget* parent = 0, const char* name = 0);
  ~CQMCAWidget();

  virtual bool runTask();

public slots:
  virtual void slotSteadyStateChecked();

protected:
  virtual bool loadTask();
  virtual bool saveTask();
  virtual bool taskFinishedEvent();

protected slots:

private:
  void init();
  bool loadParameterTable();
  bool saveParameterTable();
};

#endif // CQMCAWIDGET_H
