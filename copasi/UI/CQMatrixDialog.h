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

#ifndef CQMATRIXDIALOG_H
#define CQMATRIXDIALOG_H

#include <QtCore/QVariant>
#include "ui_CQMatrixDialog.h"

class CDataArray;

class CQMatrixDialog : public QDialog, public Ui::CQMatrixDialog
{
  Q_OBJECT

public:
  CQMatrixDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQMatrixDialog();

public slots:
  virtual void setArray(const CDataArray * tmp, bool single);

protected slots:
};

#endif // CQMATRIXDIALOG_H
