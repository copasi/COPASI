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

#ifndef CQEFMWIDGET_H
#define CQEFMWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQEFMWidget.h"
#include "copasi/UI/TaskWidget.h"

class CQEFMWidget : public TaskWidget, public Ui::CQEFMWidget
{
  Q_OBJECT

public:
  CQEFMWidget(QWidget* parent = 0, const char* name = 0);
  ~CQEFMWidget();

  virtual bool runTask();
  virtual bool saveTaskProtected();
  virtual bool loadTaskProtected();
  virtual bool taskFinishedEvent();

protected slots:
};

#endif // CQEFMWIDGET_H
