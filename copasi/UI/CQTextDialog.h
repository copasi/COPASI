// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTextDialog.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:37 $
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

#include <QtCore/QVariant>

#include "ui_CQTextDialog.h"

class CQTextDialog : public QDialog, public Ui::CQTextDialog
{
  Q_OBJECT

public:
  CQTextDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQTextDialog();

  QString getText();
};

#endif // CQTEXTDIALOG_H
