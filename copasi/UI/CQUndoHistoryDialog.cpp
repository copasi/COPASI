// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQUndoHistoryDialog.cpp
 *
 *  Created on: 10 Dec 2014
 *      Author: dada
 */

#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QUndoStack>
#include <QPushButton>
#include <QDialogButtonBox>

#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/undoFramework/CCopasiUndoCommand.h"
#include "copasi/undoFramework/CreateNewCompartmentCommand.h"
#include "copasi/undoFramework/CreateNewEventCommand.h"
#include "copasi/undoFramework/UndoData.h"
#include "copasi/undoFramework/UndoCompartmentData.h"
#include "copasi/undoFramework/UndoEventData.h"
#include "CQUndoHistoryDialog.h"

/*
 *  Constructs a CQUndoHistoryDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQUndoHistoryDialog::CQUndoHistoryDialog(QWidget* parent, QUndoStack *undoStack, const char* name, bool modal, Qt::WindowFlags fl)
  : QDialog(parent, fl)
  , mpUndoStack(undoStack)
  , mNCol(7) //total number of UNDO History columns
  , mpModel(new QStandardItemModel(mpUndoStack->count(), mNCol, parent))
  , mSelectedIndex(0)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);

  connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(slotUndo()));

  // attach the model to the view
  mpUndoHistoryView->setModel(mpModel);

  //generate UNDO History data from undostack
  generateUndoData(mpUndoStack, mpUndoStack->count(), mNCol);
}

CQUndoHistoryDialog::~CQUndoHistoryDialog()
{
  pdelete(mpModel);
}

void
CQUndoHistoryDialog::slotUndo()
{
  QModelIndexList indexList = mpUndoHistoryView->selectionModel()->selectedRows();

  if (indexList.isEmpty())
    return;

  int selectedRow = indexList.at(0).row();

  int currentIndex = mpUndoStack->index();

  if (selectedRow < currentIndex)
    {

      QMessageBox::StandardButton choice = CQMessageBox::question(this,
                                           QString("Undo Actions"),
                                           "Warning!! All actions up to the selected row will be undone, continue?",
                                           QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

      if (choice != QMessageBox::Yes)
        return;
    }
  else
    {
      QMessageBox::StandardButton choice = CQMessageBox::question(this,
                                           QString("Redo Actions"),
                                           "Warning!! All actions up to the selected row will be redone, continue?",
                                           QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

      if (choice != QMessageBox::Yes)
        return;

      selectedRow++;
    }

  mpUndoStack->setIndex(selectedRow);

  close();
}

void CQUndoHistoryDialog::generateUndoData(QUndoStack *undoStack, int commandCount, int nCol)
{
  // set the table header data
  mpModel->setHeaderData(0, Qt::Horizontal, QString("Action"));
  mpModel->setHeaderData(1, Qt::Horizontal, QString("Entity Type"));
  mpModel->setHeaderData(2, Qt::Horizontal, QString("Name"));
  mpModel->setHeaderData(3, Qt::Horizontal, QString("Action"));
  mpModel->setHeaderData(4, Qt::Horizontal, QString("Property"));
  mpModel->setHeaderData(5, Qt::Horizontal, QString("New Value"));
  mpModel->setHeaderData(6, Qt::Horizontal, QString("Old Value"));

  for (int row = 0; row < commandCount; ++row)
    {
      const QUndoCommand *cmd = undoStack->command(row);
      const CCopasiUndoCommand *cCommand = dynamic_cast<const CCopasiUndoCommand*>(cmd);

      if (cCommand == NULL) continue;

      mpModel->setData(mpModel->index(row, 0, QModelIndex()), QVariant(row < mpUndoStack->index() ? "Undo" : "Redo"));

      mpModel->setData(mpModel->index(row, 1, QModelIndex()), QVariant(FROM_UTF8(cCommand->getEntityType())));
      mpModel->setData(mpModel->index(row, 2, QModelIndex()), QVariant(FROM_UTF8(cCommand->getName())));
      mpModel->setData(mpModel->index(row, 3, QModelIndex()), QVariant(FROM_UTF8(cCommand->getAction())));
      mpModel->setData(mpModel->index(row, 4, QModelIndex()), QVariant(FROM_UTF8(cCommand->getProperty())));
      mpModel->setData(mpModel->index(row, 5, QModelIndex()), QVariant(FROM_UTF8(cCommand->getNewValue())));
      mpModel->setData(mpModel->index(row, 6, QModelIndex()), QVariant(FROM_UTF8(cCommand->getOldValue())));
    }

  mpUndoHistoryView->selectRow(mpUndoStack->index());
}
