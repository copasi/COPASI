// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingResultTab1.h,v $
//   $Revision: 1.7.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:53 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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


private:
  void init();

};

#endif // CQFITTINGRESULTTAB1_H
