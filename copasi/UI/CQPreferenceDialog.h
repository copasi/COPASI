// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPreferenceDialog.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/12/09 16:41:49 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPREFERENCEDIALOG_H
#define CQPREFERENCEDIALOG_H

#include "copasi/UI/ui_CQPreferenceDialog.h"

class CQPreferenceDialog : public QDialog, public Ui::CQPreferenceDialog
{
  Q_OBJECT

public:
  CQPreferenceDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQPreferenceDialog();

private:
  void init();

protected slots:
  virtual void languageChange();

private slots:
  virtual void slotBtnOk();
  virtual void slotBtnCancel();
  virtual void slotItemDoubleClicked(QTreeWidgetItem*, int);
};

#endif // CQPREFERENCEDIALOG_H
