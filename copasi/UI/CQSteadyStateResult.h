// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSteadyStateResult.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:16 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQSteadyStateResult
#define COPASI_CQSteadyStateResult

#include <qvariant.h>
#include "copasiWidget.h"
#include "ui_CQSteadyStateResult.h"

class CSteadyStateTask;
class CSteadyStateProblem;

class CQSteadyStateResult : public CopasiWidget, public Ui::CQSteadyStateResult
{
  Q_OBJECT

public:
  CQSteadyStateResult(QWidget* parent = 0, const char* name = 0);
  ~CQSteadyStateResult();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

  void loadResult();

protected:
  virtual bool enterProtected();

protected slots:

private:
  const CSteadyStateProblem * mpProblem;
  const CSteadyStateTask * mpTask;
  bool mUpToDate;

  void init();

private slots:
  void slotSave(void);
  void slotUpdateModel();
};

#endif // COPASI_CQSteadyStateResult
