// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

class CConfigurationFile;

class CQPreferenceDialog : public QDialog, public Ui::CQPreferenceDialog
{
  Q_OBJECT

public:
  CQPreferenceDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQPreferenceDialog();

private:
  void init();

protected slots:

private slots:
  virtual void slotBtnOk();
  virtual void slotBtnCancel();

private:
  CConfigurationFile * mpConfiguration;
};

#endif // CQPREFERENCEDIALOG_H
