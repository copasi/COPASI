// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMListWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/01 19:59:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMListWidget.h"

CQEFMListWidget::CQEFMListWidget(QWidget* parent, const char* name) :
    QWidget(parent, name),
    mpTask(NULL),
    mpProxyModel(NULL),
    mpFluxModeDM(NULL)
{
  setupUi(this);

  mpEFMTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpEFMTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpEFMTable->verticalHeader()->hide();
  mpEFMTable->setAlternatingRowColors(true);
  mpEFMTable->setSortingEnabled(true);
  mpEFMTable->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  //Create Source Data Model.
  mpFluxModeDM = new CQFluxModeDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setDynamicSortFilter(true);
  mpProxyModel->setFilterKeyColumn(COL_REACTION_EQUATION);

  mpProxyModel->setSourceModel(mpFluxModeDM);

  //Set Model for the TableView
  mpEFMTable->setModel(NULL);
  mpEFMTable->setModel(mpProxyModel);
  mpEFMTable->resizeColumnsToContents();

  connect(mpEditFilter, SIGNAL(textChanged(const QString &)), this, SLOT(slotFilterChanged()));
}

CQEFMListWidget::~CQEFMListWidget()
{
  // TODO Auto-generated destructor stub
}

void CQEFMListWidget::languageChange()
{
  retranslateUi(this);
}

bool CQEFMListWidget::loadResult(const CEFMTask * pTask)
{
  mpTask = pTask;

  mpFluxModeDM->setTask(mpTask);

  mpProxyModel->setSourceModel(mpFluxModeDM);

  //Set Model for the TableView
  mpEFMTable->setModel(NULL);
  mpEFMTable->setModel(mpProxyModel);
  mpEFMTable->resizeColumnsToContents();

  return true;
}

void CQEFMListWidget::slotFilterChanged()
{
  QRegExp regExp(mpEditFilter->text() , Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}
