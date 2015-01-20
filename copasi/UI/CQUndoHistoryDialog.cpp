// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);
  connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonClicked()));
  connect(undoButton, SIGNAL(clicked()), this, SLOT(undoButtonClicked()));

  mpUndoStack = undoStack;
  mNCol = 6; //total number of UNDO History column
// int count = mpUndoStack->count(); //number of command in unod stack

  // Create a new model
  // QStandardItemModel(int rows, int columns, QObject * parent = parent)
  mpModel = new QStandardItemModel(mpUndoStack->count(), mNCol, parent);

  // attach the model to the view
  mpUndoHistoryView->setModel(mpModel);

  //generate UNDO History data from undostack
  generateUndoData(mpUndoStack, mpUndoStack->count(), mNCol);
}

CQUndoHistoryDialog::~CQUndoHistoryDialog()
{
  pdelete(mpModel);
  // no need to delete child widgets, Qt does it all
}

void CQUndoHistoryDialog::closeButtonClicked()
{
  close();
}

void CQUndoHistoryDialog::undoButtonClicked()
{
  mSelectedIndex = 2; //TODO just a test
  mpUndoStack->setIndex(mSelectedIndex);
  //generate new UNDO History data from undostack
  generateUndoData(mpUndoStack, mpUndoStack->count(), mNCol);
}

void CQUndoHistoryDialog::generateUndoData(QUndoStack *undoStack, int commandCount, int nCol)
{
  // set the table header data
  for (int col = 0; col < nCol; col++)
    {
      switch (col)
        {
          case 0:
            mpModel->setHeaderData(0, Qt::Horizontal, QString("Entity Type"));
            break;

          case 1:
            mpModel->setHeaderData(1, Qt::Horizontal, QString("Name"));
            break;

          case 2:
            mpModel->setHeaderData(2, Qt::Horizontal, QString("Action"));
            break;

          case 3:
            mpModel->setHeaderData(3, Qt::Horizontal, QString("Property"));
            break;

          case 4:
            mpModel->setHeaderData(4, Qt::Horizontal, QString("New Value"));
            break;

          case 5:
            mpModel->setHeaderData(5, Qt::Horizontal, QString("Old Value"));
            break;
        }
    }

  for (int row = 0; row < commandCount; row++)
    {
      const QUndoCommand *cmd = undoStack->command(row);
      const CCopasiUndoCommand *cCommand = dynamic_cast<const CCopasiUndoCommand*>(cmd);
      // const UndoData *undoData =  cCommand->getUndoData();

      for (int col = 0; col < 6; col++)
        {
          QModelIndex index = mpModel->index(row, col, QModelIndex());

          switch (col)
            {
              case 0:
                mpModel->setData(index, QVariant(QString(FROM_UTF8(cCommand->getEntityType()))));
                break;

              case 1:
                mpModel->setData(index, QVariant(QString(FROM_UTF8(cCommand->getName()))));
                break;

              case 2:
                mpModel->setData(index, QVariant(QString(FROM_UTF8(cCommand->getAction()))));
                break;

              case 3:
                mpModel->setData(index, QVariant(QString(FROM_UTF8(cCommand->getProperty()))));
                break;

              case 4:
                mpModel->setData(index, QVariant(QString(FROM_UTF8(cCommand->getNewValue()))));
                break;

              case 5:
                mpModel->setData(index, QVariant(QString(FROM_UTF8(cCommand->getOldValue()))));
                break;
            }
        }
    }
}
