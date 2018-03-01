// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQSteadyStateResult
#define COPASI_CQSteadyStateResult

#include <QtCore/QVariant>
#include "copasiWidget.h"
#include "copasi/UI/ui_CQSteadyStateResult.h"

class CSteadyStateTask;
class CSteadyStateProblem;

class CQSteadyStateResult : public CopasiWidget, public Ui::CQSteadyStateResult
{
  Q_OBJECT

public:
  CQSteadyStateResult(QWidget* parent = 0, const char* name = 0);
  ~CQSteadyStateResult();

  void loadResult();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

protected slots:

private:
  const CSteadyStateProblem * mpProblem;
  CSteadyStateTask * mpTask;
  bool mUpToDate;

  void init();

private slots:
  void slotSave(void);
  void slotUpdateModel();
};

#endif // COPASI_CQSteadyStateResult
