// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationResult.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/02/01 16:49:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQOPTIMIZATIONRESULT_H
#define CQOPTIMIZATIONRESULT_H

#include <qvariant.h>
#include "copasiWidget.h"
#include "ui_CQOptimizationResult.h"

class COptTask;
class COptProblem;

class CQOptimizationResult : public CopasiWidget, public Ui::CQOptimizationResult
{
  Q_OBJECT

public:
  CQOptimizationResult(QWidget* parent = 0, const char* name = 0);
  ~CQOptimizationResult();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

private:
  const COptProblem * mpProblem;
  const COptTask * mpTask;

  void init();

private slots:
  void slotSave(void);
  void slotUpdateModel();
};

#endif // CQOPTIMIZATIONRESULT_H
