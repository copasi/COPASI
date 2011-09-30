// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLNAWidget.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:37 $
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

/*
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <Qt3Support/Q3ButtonGroup>
#include <QtGui/QCheckBox>
#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3GridLayout>
#include <QtGui/QSpacerItem>
#include <Qt3Support/Q3VBoxLayout>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3VBoxLayout>
#include <Q3Frame>
 */

#include "ui_CQLNAWidget.h"

#include "TaskWidget.h"

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
