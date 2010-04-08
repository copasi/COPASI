// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/21 15:21:13 $
// End CVS Header
// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 *  CQFittingResult.h
 *  Created by Paul on 4/2/10.
 */

#ifndef CQFITTINGRESULT_H
#define CQFITTINGRESULT_H

#include <qvariant.h>

#include "ui_CQFittingResult.h"

class CFitTask;
class CFitProblem;

#include "CQArrayAnnotationsWidget.h"
#include "CQFittingResultTab1.h"
#include "copasiWidget.h"

class CQFittingResult : public CopasiWidget, public Ui::CQFittingResult
{
  Q_OBJECT

public:
  CQFittingResult(QWidget* parent = 0, const char* name = 0);
  ~CQFittingResult();

  virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
  virtual bool leave();

protected:
  virtual bool enterProtected();

protected slots:
  virtual void languageChange();

private:
  const CFitTask * mpTask;
  const CFitProblem * mpProblem;

  void init();

private slots:
  void slotSave();

};

#endif // CQFITTINGRESULT_H
