// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/06/07 14:01:52 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQFITTINGRESULTTAB1_H
#define CQFITTINGRESULTTAB1_H

#include <qvariant.h>

#include "ui_CQFittingResultTab1.h"

class CFitProblem;

class CQFittingResultTab1 : public QWidget, public Ui::CQFittingResultTab1
{
  Q_OBJECT

public:
  CQFittingResultTab1(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
  ~CQFittingResultTab1();

  void load(const CFitProblem * pProblem);

protected slots:
  virtual void languageChange();

private:
  void init();

};

#endif // CQFITTINGRESULTTAB1_H
