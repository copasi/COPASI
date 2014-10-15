// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQLNAWIDGET_H
#define CQLNAWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQLNAWidget.h"

class CQLNAWidget : public TaskWidget, public Ui::CQLNAWidget
{
  Q_OBJECT

public:
  CQLNAWidget(QWidget* parent = 0, const char* name = 0);
  ~CQLNAWidget();

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

#endif // CQLNAAWIDGET_H
