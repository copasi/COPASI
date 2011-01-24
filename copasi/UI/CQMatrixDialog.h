// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMatrixDialog.h,v $
//   $Revision: 1.6.2.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/01/24 17:00:14 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQMATRIXDIALOG_H
#define CQMATRIXDIALOG_H

#include <qvariant.h>
#include "ui_CQMatrixDialog.h"

class CArrayAnnotation;

class CQMatrixDialog : public QDialog, public Ui::CQMatrixDialog
{
  Q_OBJECT

public:
  CQMatrixDialog(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQMatrixDialog();

public slots:
  virtual void setArray(const CArrayAnnotation * tmp, bool single);

protected slots:
  virtual void languageChange();

};

#endif // CQMATRIXDIALOG_H
