// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQUpdateAvogadro
#define COPASI_CQUpdateAvogadro

#include "copasi/UI/ui_CQUpdateAvogadro.h"

class CQUpdateAvogadro : public QDialog, public Ui::CQUpdateAvogadro
{
  Q_OBJECT

public:
  CQUpdateAvogadro(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  virtual ~CQUpdateAvogadro();
  int getSelection() const;
  void setSelection(int selection);
};

#endif // COPASI_CQUpdateAvogadro
