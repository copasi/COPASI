// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

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

  std::map< std::string, C_INT32 > mSubtaskMap;

  virtual bool saveTask();
  virtual bool loadTask();

protected slots:

  void slotPageChange(QWidget * currentPage);
  void slotExpressionValid(bool valid);
  void slotSubtaskChanged(const QString & subtask);

private:
  void init();
  void destroy();
};

#endif // CQOPTIMIZATIONWIDGET_H
