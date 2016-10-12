// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
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

  QString getText() const;

  void setText(const QString& text);

};

#endif // CQTEXTDIALOG_H
