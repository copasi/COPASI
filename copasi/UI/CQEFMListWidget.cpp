// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMListWidget.h"

#include "elementaryFluxModes/CEFMTask.h"

CQEFMListWidget::CQEFMListWidget(QWidget* parent, const char* name) :
  QWidget(parent),
  mpTask(NULL),
  mpProxyModel(NULL),
  mpFluxModeDM(NULL)
{
  setObjectName(QString::fromUtf8(name));
  setupUi(this);

  mpEFMTable->verticalHeader()->hide();
  mpEFMTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpEFMTable->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  //Create Source Data Model.
  mpFluxModeDM = new CQFluxModeDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

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
