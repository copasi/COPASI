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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*
 *  CQFittingResult.h
 *  Created by Paul on 4/2/10.
 */

#ifndef CQFITTINGRESULT_H
#define CQFITTINGRESULT_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQFittingResult.h"
#include <copasi/parameterFitting/CExperimentSet.h>

class CFitTask;
class CFitProblem;
class COptMethod;
class QTreeWidget;

class CQFittingResult : public CopasiWidget, public Ui::CQFittingResult
{
  Q_OBJECT

public:
  CQFittingResult(QWidget* parent = 0, const char* name = 0);
  ~CQFittingResult();

protected:
  virtual bool enterProtected();
  virtual bool updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  virtual bool leaveProtected();

  void loadLog(const COptMethod * pMethod);

  void loadExperimentTab();
  void loadCrossValidationTab();

  void loadExperimentSetIntoTree(const CExperimentSet& Experiments, QTreeWidget* pTreeWidget);

protected slots:

private:
  const CFitTask * mpTask;
  const CFitProblem * mpProblem;

  void init();

private slots:
  void slotSave(void);
  void loadTab(int);
  void slotUpdateModel();
};

#endif // CQFITTINGRESULT_H
