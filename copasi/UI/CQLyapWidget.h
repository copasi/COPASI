// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQLYAPWIDGET_H
#define CQLYAPWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQLyapWidget.h"

class CQLyapWidget : public TaskWidget, public Ui::CQLyapWidget
{
  Q_OBJECT

public:
  CQLyapWidget(QWidget* parent = 0, const char* name = 0);
  ~CQLyapWidget();

  virtual bool runTask();

protected:
  virtual bool loadTask();
  virtual bool saveTask();
  virtual bool taskFinishedEvent();

protected slots:

  void slotDelayChecked();

private:
  void init();
};

#endif // CQLYAPWIDGET_H
