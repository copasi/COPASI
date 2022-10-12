// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQ_SEDML_IMPORT_DIALOG_H

#include <QDialog>

#include <copasi/sedml/SEDMLUtils.h>

#include "copasi/UI/ui_CQSEDMLImportDialog.h"

class CQSEDMLImportDialog : public QDialog, public Ui::CQSEDMLImportDialog
{
  Q_OBJECT

public:
  CQSEDMLImportDialog(QWidget * parent = NULL);
  virtual ~CQSEDMLImportDialog();
  void loadSedML(SedmlInfo & info);

  SedmlImportOptions getOptions();

public slots:
  void slotReportSelected(const QString & report);
  void slotTaskSelected(const QString & task);
  void slotBrowseReportfile();

private:
  SedmlInfo mInfo;
};


#endif // CQ_SEDML_IMPORT_DIALOG_H
