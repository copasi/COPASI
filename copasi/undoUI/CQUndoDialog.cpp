// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQUndoDialog.h"
#include "CQUndoDM.h"

CQUndoDialog::CQUndoDialog(CDataModel * pDataModel, QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  mpUndoDM(NULL)
{
  setupUi(this);

  mpUndoDM = new CQUndoDM(this, pDataModel, mpTableView);
  mpTableView->setModel(mpUndoDM);

  mpTableView->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
  mpTableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

CQUndoDialog::~CQUndoDialog()
{}
