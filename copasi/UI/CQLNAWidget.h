// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLNAWidget.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/14 15:10:06 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQLNAWIDGET_H
#define CQLNAWIDGET_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQLNAWidget.h"

class CQLNAWidget : public TaskWidget, public Ui::CQLNAWidget
{
  Q_OBJECT

public:
  CQLNAWidget(QWidget* parent = 0, const char* name = 0);
  ~CQLNAWidget();

  virtual bool runTask();

public slots:
  virtual void slotSteadyStateChecked();

protected:
  virtual CCopasiMethod * createMethod(const CCopasiMethod::SubType & type);
  virtual bool loadTask();
  virtual bool saveTask();
  virtual bool taskFinishedEvent();

protected slots:

private:
  void init();
  bool loadParameterTable();
  bool saveParameterTable();
};

#endif // CQLNAAWIDGET_H
