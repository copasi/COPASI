// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQStartValueReset.h,v $
//   $Revision: 1.4.2.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/01/31 17:34:08 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQSTARTVALUERESET_H
#define CQSTARTVALUERESET_H

#include "ui_CQStartValueReset.h"

class CQStartValueReset : public QDialog, public Ui::CQStartValueReset
{
  Q_OBJECT

public:
  CQStartValueReset(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
  ~CQStartValueReset();

  enum Result {MODEL = QDialog::Accepted + QDialog::Rejected + 1, RANDOM, SOLUTION};

protected slots:
  virtual void languageChange();

private slots:
  void slotModel();
  void slotRandom();
  void slotSolution();

};

#endif // CQSTARTVALUERESET_H
