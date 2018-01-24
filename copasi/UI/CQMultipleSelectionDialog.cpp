// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQMultipleSelectionDialog.h"

CQMultipleSelectionDialog::CQMultipleSelectionDialog(QWidget * parent, Qt::WindowFlags f)
  : QDialog(parent, f)
  , mSelection()
{
  setupUi(this);
}

// virtual
CQMultipleSelectionDialog::~CQMultipleSelectionDialog()
{}

void CQMultipleSelectionDialog::setSelectionList(const QStringList & selectionList)
{
  mpListWidget->addItems(selectionList);
}

void 
CQMultipleSelectionDialog::setCurrentSelection(const QStringList & list)
{
  for (int i = 0; i < mpListWidget->count(); ++i)
  {
    QListWidgetItem* item = mpListWidget->item(i);
    item->setSelected(list.contains(item->text()));
  }
}

const QStringList & 
CQMultipleSelectionDialog::getSelection() const
{
  return mSelection;
}

// virtual
void CQMultipleSelectionDialog::accept()
{
  mSelection.clear();
  QList<QListWidgetItem *> selection = mpListWidget->selectedItems();
  foreach(QListWidgetItem* item, selection)
    mSelection << item->text();

  QDialog::accept();
}
