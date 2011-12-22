// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SteadyStateWidget.h,v $
//   $Revision: 1.43 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/12/22 19:51:58 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef STEADYSTATEWIDGET_H
#define STEADYSTATEWIDGET_H

#include "copasi.h"

#include "copasi/UI/ui_SteadyStateWidget.h"

#include "copasi/UI/TaskWidget.h"

class SteadyStateWidget : public TaskWidget, public Ui::SteadyStateWidget
{
  Q_OBJECT

public:
  SteadyStateWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0);
  ~SteadyStateWidget();

  virtual bool runTask();

protected slots:
  virtual void taskJacobianToggled();

protected:
  virtual bool loadTask();
  virtual bool saveTask();
  virtual bool taskFinishedEvent();


  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

private:
  void init();

protected slots:
};

#endif // STEADYSTATEWIDGET_H
