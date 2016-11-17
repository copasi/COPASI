// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
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

private slots:
  virtual void slotBtnOk();
  virtual void slotBtnCancel();
};

#endif // CQPREFERENCEDIALOG_H
