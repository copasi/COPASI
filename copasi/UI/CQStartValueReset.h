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

#ifndef CQSTARTVALUERESET_H
#define CQSTARTVALUERESET_H

#include "ui_CQStartValueReset.h"

class CQStartValueReset : public QDialog, public Ui::CQStartValueReset
{
  Q_OBJECT

public:
  CQStartValueReset(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQStartValueReset();

  enum Result {MODEL = QDialog::Accepted + QDialog::Rejected + 1, RANDOM, SOLUTION};

protected slots:

private slots:
  void slotModel();
  void slotRandom();
  void slotSolution();
};

#endif // CQSTARTVALUERESET_H
