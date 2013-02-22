// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQNameSelectionDialog.h"

CQNameSelectionDialog::CQNameSelectionDialog(QWidget * parent, Qt::WindowFlags f):
  QDialog(parent, f),
  mSelection()
{
  setupUi(this);
}

// virtual
CQNameSelectionDialog::~CQNameSelectionDialog()
{}

void CQNameSelectionDialog::setSelectionList(const QStringList & selectionList)
{
  mpSelectionBox->addItems(selectionList);
}

const QString & CQNameSelectionDialog::getSelection() const
{
  return mSelection;
}

// virtual
void CQNameSelectionDialog::accept()
{
  mSelection = mpSelectionBox->currentText();

  QDialog::accept();
}
