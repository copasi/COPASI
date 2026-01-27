// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  Created by Paul on 08/05/11.
 */

#ifndef CQOSCILLATIONTASKWIDGET_H
#define CQOSCILLATIONTASKWIDGET_H

#include <QtCore/QVariant>

#include "ui_CQOscillationTaskWidget.h"

#include "TaskWidget.h"

class CQOscillationTaskWidget : public TaskWidget, public Ui::CQOscillationTaskWidget
{
  Q_OBJECT

public:
  CQOscillationTaskWidget(QWidget* parent = 0, const char* name = 0);
  virtual ~CQOscillationTaskWidget();

  bool runTask() override;

protected:
  bool saveTaskProtected() override;
  bool loadTaskProtected() override;

protected slots:

private:
  void init();
};

#endif
