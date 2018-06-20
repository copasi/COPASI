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
  virtual bool loadTaskProtected();
  virtual bool saveTaskProtected();
  virtual bool taskFinishedEvent();

protected slots:

  void slotDelayChecked();

private:
  void init();
};

#endif // CQLYAPWIDGET_H
