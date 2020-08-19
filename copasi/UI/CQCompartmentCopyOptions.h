// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COMPARTMENTCOPYOPTIONS_H
#define COMPARTMENTCOPYOPTIONS_H

#include "ui_CQCompartmentCopyOptions.h"

class CQCompartmentCopyOptions : public QDialog, public Ui::CQCompartmentCopyOptions
{
  Q_OBJECT

public:
  CQCompartmentCopyOptions(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQCompartmentCopyOptions();

  enum Result {COMP = QDialog::Accepted + QDialog::Rejected + 1, SPECIES, INTREAC, ALLREAC};

protected slots:

private slots:
  void slotCompartment();
  void slotAndSpecies();
  void slotAndIntReactions();
  void slotAndAllReactions();
};

#endif // COMPARTMENTCOPYOPTIONS_H
