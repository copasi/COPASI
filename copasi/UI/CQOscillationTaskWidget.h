// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

  virtual bool runTask();
  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);

protected:
  virtual bool saveTask();
  virtual bool loadTask();

protected slots:

private:
  void init();
};

#endif
