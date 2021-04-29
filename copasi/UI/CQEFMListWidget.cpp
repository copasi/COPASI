// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMListWidget.h"

#include "copasi/elementaryFluxModes/CEFMTask.h"
#include <copasi/core/CRootContainer.h>
#include <copasi/commandline/CConfigurationFile.h>
#include <copasi/UI/copasiWidget.h>

CQEFMListWidget::CQEFMListWidget(QWidget *parent, const char *name) :
  QWidget(parent),
  mpTask(NULL),
  mpProxyModel(NULL),
  mpFluxModeDM(NULL)
{
  setObjectName(QString::fromUtf8(name));
  setupUi(this);
  mpEFMTable->verticalHeader()->hide();

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpEFMTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpEFMTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
  mpEFMTable->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif

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

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpEFMTable->resizeColumnsToContents();
    }

  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)), this, SLOT(slotFilterChanged()));
}

CQEFMListWidget::~CQEFMListWidget()
{
  // TODO Auto-generated destructor stub
  pdelete(mpProxyModel);
}

bool CQEFMListWidget::loadResult(const CEFMTask *pTask)
{
  QByteArray State = mpEFMTable->horizontalHeader()->saveState();
  blockSignals(true);

  mpTask = pTask;
  mpFluxModeDM->setTask(mpTask);
  mpProxyModel->setSourceModel(mpFluxModeDM);
  //Set Model for the TableView
  mpEFMTable->setModel(NULL);
  mpEFMTable->setModel(mpProxyModel);

  mpEFMTable->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpEFMTable->resizeColumnsToContents();
    }

  emit initFilter();

  return true;
}

void CQEFMListWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  CopasiWidget::setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter);

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}
