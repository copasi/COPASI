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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQFITTINGRESULTTAB1_H
#define CQFITTINGRESULTTAB1_H

#include <QtCore/QVariant>

#include "ui_CQFittingResultTab1.h"

class CFitProblem;

class CQFittingResultTab1 : public QWidget, public Ui::CQFittingResultTab1
{
  Q_OBJECT

public:
  CQFittingResultTab1(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQFittingResultTab1();

  void load(const CFitProblem * pProblem);

protected slots:

private:
  void init();
};

#endif // CQFITTINGRESULTTAB1_H
