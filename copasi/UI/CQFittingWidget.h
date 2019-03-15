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

#ifndef CQFITTINGWIDGET_H
#define CQFITTINGWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQFittingWidget.h"

class CExperimentSet;
class CQFittingItemWidget;
class CCrossValidationSet;

class CQFittingWidget : public TaskWidget, public Ui::CQFittingWidget
{
  Q_OBJECT

public:
  CQFittingWidget(QWidget* parent = 0, const char* name = 0);
  ~CQFittingWidget();

  virtual bool runTask();

public slots:
  void slotParameterNumberChanged(int number);
  void slotConstraintNumberChanged(int number);

protected:
  CQFittingItemWidget * mpCurrentList;
  CExperimentSet * mpExperimentSet;
  std::map<std::string, std::string> mExperimentKeyMap;
  CCrossValidationSet * mpCrossValidationSet;
  std::map<std::string, std::string> mCrossValidationKeyMap;
  size_t mnParamterSetsBeforeRun;

  virtual bool saveTaskProtected();
  virtual bool loadTaskProtected();
  virtual bool taskFinishedEvent();

protected slots:

  void slotExperimentData();
  void slotPageChange(QWidget * currentPage);
  void slotPageIndexChange(int currentIndex);
  void slotCrossValidationData();

private:
  void init();
  void destroy();
};

#endif // CQFITTINGWIDGET_H
