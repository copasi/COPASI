// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMoietiesTaskWidget.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/17 13:10:19 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQMOIETIESTASKWIDGET_H
#define CQMOIETIESTASKWIDGET_H

#include <qvariant.h>

#include "ui_CQMoietiesTaskWidget.h"
#include "TaskWidget.h"


class CQMoietiesTaskWidget : public TaskWidget, public Ui::CQMoietiesTaskWidget
{
  Q_OBJECT

public:
  CQMoietiesTaskWidget(QWidget* parent = 0, const char* name = 0);
  ~CQMoietiesTaskWidget();

  virtual bool runTask();
  virtual bool saveTask();
  virtual bool loadTask();
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);

protected:
  virtual bool taskFinishedEvent();

protected slots:

private:
  void init();
  void destroy();

};

#endif // CQMOIETIESTASKWIDGET_H
