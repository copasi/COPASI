// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#ifndef COPASI_CQReportTemplateSelect
#define COPASI_CQReportTemplateSelect

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQReportTemplateSelect.h"

class CReport;
class ListViews;

class CQReportTemplateSelect: public QDialog, public Ui::CQReportTemplateSelect
{
  Q_OBJECT

public:
  CQReportTemplateSelect(QWidget * parent = 0, Qt::WindowFlags f = 0);

  virtual ~CQReportTemplateSelect();

  void cleanup();

  void setReport(CReport* newReport);

  void loadReportTemplateVector();

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

#endif // COPASI_CQReportTemplateSelect
