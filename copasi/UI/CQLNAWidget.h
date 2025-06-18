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

  bool runTask() override;

public slots:
  virtual void slotSteadyStateChecked();

protected:
  bool loadTaskProtected() override;
  bool saveTaskProtected() override;
  bool taskFinishedEvent() override;

protected slots:

private:
  void init();
};

#endif // CQLNAAWIDGET_H
