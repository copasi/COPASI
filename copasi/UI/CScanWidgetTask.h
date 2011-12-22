// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetTask.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:57 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/*
 All rights reserved.
 */

#ifndef CSCANWIDGETTASK_H
#define CSCANWIDGETTASK_H

#include "copasi/UI/ui_CScanWidgetTask.h"

#include "scan/CScanProblem.h"

class CScanWidgetTask: public QWidget, public Ui::CScanWidgetTask
{
  Q_OBJECT

public:
  CScanWidgetTask(QWidget *parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CScanWidgetTask();

  virtual void load(const CScanProblem * pg);
  virtual bool save(CScanProblem * pg) const;

protected:
  CCopasiObject* mpObject;
  const CModel* mpModel;

private:
  void init();

private slots:
  virtual void typeChanged(int n);
};

#endif // CSCANWIDGETTASK_H
