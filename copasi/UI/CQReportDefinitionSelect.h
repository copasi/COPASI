// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
  CQReportDefinitionSelect(QWidget * parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

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
