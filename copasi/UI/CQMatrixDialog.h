// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQMATRIXDIALOG_H
#define CQMATRIXDIALOG_H

#include <QtCore/QVariant>
#include "ui_CQMatrixDialog.h"

class CDataArray;

class CQMatrixDialog : public QDialog, public Ui::CQMatrixDialog
{
  Q_OBJECT

public:
  CQMatrixDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQMatrixDialog();

public slots:
  virtual void setArray(const CDataArray * tmp, bool single);

protected slots:
};

#endif // CQMATRIXDIALOG_H
