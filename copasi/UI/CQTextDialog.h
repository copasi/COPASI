// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTextDialog.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/05/16 15:57:45 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQTEXTDIALOG_H
#define CQTEXTDIALOG_H

#include <qvariant.h>

#include "ui_CQTextDialog.h"

class CQTextDialog : public QDialog, public Ui::CQTextDialog
{
  Q_OBJECT

public:
  CQTextDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQTextDialog();

  QString getText();

protected slots:
  virtual void languageChange();
};

#endif // CQTEXTDIALOG_H
