// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

#include "CQMultipleSelectionDialog.h"

CQMultipleSelectionDialog::CQMultipleSelectionDialog(QWidget * parent, Qt::WindowFlags f)
  : QDialog(parent, f)
  , mSelection()
{
  setupUi(this);
  mpLabel->setVisible(false);
}

// virtual
CQMultipleSelectionDialog::~CQMultipleSelectionDialog()
{}

void CQMultipleSelectionDialog::setSelectionList(const QStringList & selectionList)
{
  mpListWidget->addItems(selectionList);
}

void CQMultipleSelectionDialog::setLabel(const QString& label)
{
  mpLabel->setText(label);
  mpLabel->setVisible(!label.isEmpty());
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

QStringList CQMultipleSelectionDialog::getSelection(QWidget * parent, const QString & title, const QString & label, const QStringList & strings, const QStringList * currentSelection, bool * ok, Qt::WindowFlags flags)
{
  CQMultipleSelectionDialog dlg(parent, flags);
  dlg.setWindowTitle(title);
  dlg.setLabel(label);
  dlg.setSelectionList(strings);
  QStringList oldSelection;
  if (currentSelection)
  {
    oldSelection = *currentSelection;
    dlg.setCurrentSelection(oldSelection);
  }

  bool accepted = dlg.exec() == QDialog::Accepted;
  
  if (ok)
    *ok = accepted;
  
  if (accepted)
    return dlg.getSelection();
  
  return oldSelection;
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
