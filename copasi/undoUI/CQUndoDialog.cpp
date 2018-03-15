// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQUndoDM.h"
#include "CQUndoDialog.h"

#include "copasi/CopasiDataModel/CDataModel.h"

CQUndoDialog::CQUndoDialog(CDataModel * pDataModel, QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  mpDataModel(pDataModel),
  mpUndoDM(NULL),
  mChangeSet()
{
  setupUi(this);

  mpUndoDM = new CQUndoDM(this, mpDataModel, mpTableView);
  mpTableView->setModel(mpUndoDM);

  mpTableView->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
  mpTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
  mpTableView->selectRow(mpDataModel->getUndoStack()->currentIndex());
}

CQUndoDialog::~CQUndoDialog()
{}

const CUndoData::ChangeSet & CQUndoDialog::getChangeSet() const
{
  return mChangeSet;
}

void CQUndoDialog::accept()
{
  QModelIndexList SelectedIndeces = mpTableView->selectionModel()->selectedRows();
  CUndoStack * pUndoStack = mpDataModel->getUndoStack();

  if (!SelectedIndeces.empty())
    {
      size_t Index = SelectedIndeces.at(0).row();

      if (Index <= pUndoStack->currentIndex() &&
          pUndoStack->currentIndex() != C_INVALID_INDEX) Index--;

      mChangeSet = pUndoStack->setCurrentIndex(Index);
    }

  QDialog::accept();
}
