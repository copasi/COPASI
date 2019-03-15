// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <QPushButton>

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

  mpButtonBox->button(QDialogButtonBox::Cancel)->setDefault(true);
  mpButtonBox->button(QDialogButtonBox::Cancel)->setAutoDefault(true);

  mpUndoDM = new CQUndoDM(this, mpDataModel, mpTableView);
  mpTableView->setModel(mpUndoDM);

  mpTableView->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
  mpTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
  mpTableView->selectRow(mpDataModel->getUndoStack()->currentIndex());
}

CQUndoDialog::~CQUndoDialog()
{}

const CUndoData::CChangeSet & CQUndoDialog::getChangeSet() const
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
