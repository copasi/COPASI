// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQMOIETIESTASKWIDGET_H
#define CQMOIETIESTASKWIDGET_H

#include <QtCore/QVariant>

#include "ui_CQMoietiesTaskWidget.h"
#include "TaskWidget.h"

class CQMoietiesTaskWidget : public TaskWidget, public Ui::CQMoietiesTaskWidget
{
  Q_OBJECT

public:
  CQMoietiesTaskWidget(QWidget* parent = 0, const char* name = 0);
  ~CQMoietiesTaskWidget();

  virtual bool runTask();
  virtual bool saveTask();
  virtual bool loadTask();

protected:
  virtual bool taskFinishedEvent();

protected slots:

private:
  void init();
  void destroy();
};

#endif // CQMOIETIESTASKWIDGET_H
