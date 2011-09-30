// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQMatrixDialog.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:40 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQMATRIXDIALOG_H
#define CQMATRIXDIALOG_H

#include <QtCore/QVariant>
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

};

#endif // CQMATRIXDIALOG_H
