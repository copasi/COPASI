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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQOPTIMIZATIONWIDGET_H
#define CQOPTIMIZATIONWIDGET_H

#include <QtCore/QVariant>
#include "TaskWidget.h"

#include "ui_CQOptimizationWidget.h"

class CQFittingItemWidget;

#include <QVBoxLayout>
#include <QHBoxLayout>

class CQOptimizationWidget : public TaskWidget, public Ui::CQOptimizationWidget
{
  Q_OBJECT

public:
  CQOptimizationWidget(QWidget* parent = 0, const char* name = 0);
  ~CQOptimizationWidget();

  virtual bool runTask();
  bool isSteadyState();

public slots:
  void slotParameterNumberChanged(int number);
  void slotConstraintNumberChanged(int number);
  virtual void slotEditExpression();

protected:
  CQFittingItemWidget * mpCurrentList;
  QColor mChangedColor;
  QColor mSavedColor;
  bool mTypeChanged;

  std::map< std::string, size_t > mSubtaskMap;

  virtual bool saveTaskProtected();
  virtual bool loadTaskProtected();

protected slots:

  void slotPageChange(QWidget * currentPage);
  void slotPageIndexChange(int currentIndex);
  void slotExpressionValid(bool valid);
  void slotSubtaskChanged(const QString & subtask);

private:
  void init();
  void destroy();
};

#endif // CQOPTIMIZATIONWIDGET_H
