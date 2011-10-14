// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapWidget.h,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/14 15:25:00 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQLYAPWIDGET_H
#define CQLYAPWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQLyapWidget.h"

class CQLyapWidget : public TaskWidget, public Ui::CQLyapWidget
{
  Q_OBJECT

public:
  CQLyapWidget(QWidget* parent = 0, const char* name = 0);
  ~CQLyapWidget();

  virtual bool runTask();

protected:
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
  virtual bool loadTask();
  virtual bool saveTask();
  virtual bool taskFinishedEvent();

protected slots:

  void slotDelayChecked();

private:
  void init();
};

#endif // CQLYAPWIDGET_H
