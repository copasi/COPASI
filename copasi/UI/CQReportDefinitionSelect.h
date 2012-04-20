// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReportDefinitionSelect.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/20 16:26:55 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQReportDefinitionSelect
#define COPASI_CQReportDefinitionSelect

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQReportDefinitionSelect.h"

class CReport;
class ListViews;

class CQReportDefinitionSelect: public QDialog, public Ui::CQReportDefinitionSelect
{
  Q_OBJECT

public:
  CQReportDefinitionSelect(QWidget * parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQReportDefinitionSelect();

  void cleanup();

  void setReport(CReport* newReport);

  void loadReportDefinitionVector();

public slots:
  int exec();

protected slots:
  void accept();
  void reject();
  void slotEdit();
  void slotBrowse();

private:
  ListViews * mpListView;
  CReport * mpReport;
  bool mShow;
};

#endif // COPASI_CQReportDefinitionSelect
