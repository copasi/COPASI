// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
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
  CQCompartmentCopyOptions(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
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
