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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQEXPERIMENTSELECTION_H
#define CQEXPERIMENTSELECTION_H

#include <QtCore/QVariant>
#include <QDialog>

#include "ui_CQExperimentSelection.h"

class QComboBox;
class CExperimentSet;

class CQExperimentSelection : public QDialog, public Ui::CQExperimentSelection
{
  Q_OBJECT

public:
  CQExperimentSelection(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());
  ~CQExperimentSelection();

  virtual void load(QComboBox * pBox, const CExperimentSet * pExperimentSet);
  void setSingleSelection(bool isSingleSelection);

protected:
  QComboBox * mpBox;
  bool mIsSingleSelection {false };

protected slots:

  void slotBtnOK();
  void slotBtnCancel();
  void slotBtnAll();
  void slotBtnNone();

private:
  void init();
};

#endif // CQEXPERIMENTSELECTION_H
