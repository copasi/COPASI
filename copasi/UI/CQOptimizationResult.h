// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQOPTIMIZATIONRESULT_H
#define CQOPTIMIZATIONRESULT_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQOptimizationResult.h"

class COptTask;
class COptProblem;
class COptMethod;

class CQOptimizationResult : public CopasiWidget, public Ui::CQOptimizationResult
{
  Q_OBJECT

public:
  CQOptimizationResult(QWidget* parent = 0, const char* name = 0);
  ~CQOptimizationResult();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  void loadLog(const COptMethod * pMethod);

protected slots:

private:
  const COptProblem * mpProblem;
  const COptTask * mpTask;

  void init();

private slots:
  void slotSave(void);
  void loadTab(int);
  void slotUpdateModel();
};

#endif // CQOPTIMIZATIONRESULT_H
