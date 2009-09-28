// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationWidget.h,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/09/28 18:13:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQOPTIMIZATIONWIDGET_H
#define CQOPTIMIZATIONWIDGET_H

#include <qvariant.h>
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
  CQFittingItemWidget * mpConstraints;
  CQFittingItemWidget * mpParameters;
  QColor mChangedColor;
  QColor mSavedColor;
  bool mTypeChanged;
  QHBoxLayout * mpConstraintPageLayout;
  QHBoxLayout * mpParameterPageLayout;

  std::map< std::string, C_INT32 > mSubtaskMap;

  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:
  virtual void languageChange();

  void slotPageChange(QWidget * currentPage);
  void slotExpressionValid(bool valid);
  void slotSubtaskChanged(const QString & subtask);

private:
  void init();
  void destroy();
};

#endif // CQOPTIMIZATIONWIDGET_H
