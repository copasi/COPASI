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

#ifndef TIMESERIESSUBWIDGET_H
#define TIMESERIESSUBWIDGET_H

#include <qvariant.h>

#include "ui_TimeSeriesSubwidget.h"

#include "CTimeSeriesTable.h"
#include "copasi.h"

class TimeSeriesSubWidget : public CopasiWidget, public Ui::TimeSeriesSubWidget
{
  Q_OBJECT

public:
  TimeSeriesSubWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~TimeSeriesSubWidget();

  void displayOptimizationTab(bool displayOptTab);
  void setFramework(const int & framework);

public slots:
  virtual CTimeSeriesTable * table();

protected slots:
  virtual void languageChange();

  void saveDataToFile();
  virtual void init();


private:
  int mFramework;

};

#endif // TIMESERIESSUBWIDGET_H
