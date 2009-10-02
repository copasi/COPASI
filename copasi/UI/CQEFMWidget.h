// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMWidget.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/02 16:25:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEFMWIDGET_H
#define CQEFMWIDGET_H

#include <qvariant.h>

#include "copasi/UI/ui_CQEFMWidget.h"
#include "copasi/UI/TaskWidget.h"

class CQEFMWidget : public TaskWidget, public Ui::CQEFMWidget
{
  Q_OBJECT

public:
  CQEFMWidget(QWidget* parent = 0, const char* name = 0);
  ~CQEFMWidget();

  virtual bool runTask();
  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected slots:
  virtual void languageChange();
};

#endif // CQEFMWIDGET_H
