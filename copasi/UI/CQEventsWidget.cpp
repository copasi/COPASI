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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQEventsWidget.h"

#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>

#include "qtUtilities.h"
#include "copasi/copasi.h"
#include "CQMessageBox.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include <copasi/commandline/CConfigurationFile.h>

#include "copasiui3window.h"

/*
 *  Constructs a CQEventsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEventsWidget::CQEventsWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name)
{
  setupUi(this);
  //Create Source Data Model.
  mpEventDM = new CQEventDM(this, mpDataModel);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblEvents->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpTblEvents->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpTblEvents->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpTblEvents->verticalHeader()->hide();
  mpTblEvents->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  // Connect the table widget
  connect(mpEventDM, SIGNAL(signalNotifyChanges(const CUndoData::CChangeSet &)),
          this, SLOT(slotNotifyChanges(const CUndoData::CChangeSet &)));
  connect(mpEventDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpTblEvents, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotSelectionChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQEventsWidget::~CQEventsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpEventDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQEventsWidget::slotBtnNewClicked()
{
  mpEventDM->insertRow(mpEventDM->rowCount() - 1, QModelIndex());
  updateDeleteBtns();
}

void CQEventsWidget::slotBtnDeleteClicked()
{
  if (mpTblEvents->hasFocus())
    {deleteSelectedEvents();}

  updateDeleteBtns();
}

void CQEventsWidget::deleteSelectedEvents()
{
  const QItemSelectionModel *pSelectionModel = mpTblEvents->selectionModel();
  QModelIndexList mappedSelRows;
  size_t i, imax = mpEventDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpEventDM->removeRows(mappedSelRows);
}

void CQEventsWidget::slotBtnClearClicked()
{
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Events?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpEventDM->clear();
    }

  updateDeleteBtns();
}

bool CQEventsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const CCommonName & cn)
{
  if (mIgnoreUpdates || !isVisible())
    {
      return true;
    }

  if (objectType == ListViews::ObjectType::MODEL ||
      objectType == ListViews::ObjectType::EVENT)
    {
      enterProtected();
    }

  return true;
}

bool CQEventsWidget::leaveProtected()
{
  return true;
}

CQBaseDataModel * CQEventsWidget::getCqDataModel()
{
  return mpEventDM;
}

bool CQEventsWidget::enterProtected()
{
  QByteArray State = mpTblEvents->horizontalHeader()->saveState();
  blockSignals(true);

  mpEventDM->setDataModel(mpDataModel);
  mpProxyModel->setSourceModel(mpEventDM);
  //Set Model for the TableView
  mpTblEvents->setModel(NULL);
  mpTblEvents->setModel(mpProxyModel);

  updateDeleteBtns();
  mpTblEvents->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblEvents->resizeColumnsToContents();
    }

  emit initFilter();

  return true;
}

void CQEventsWidget::updateDeleteBtns()
{
  bool selected = false;
  QModelIndexList selRows = mpTblEvents->selectionModel()->selectedRows();

  if (selRows.size() == 0)
    selected = false;
  else
    {
      if (selRows.size() == 1)
        {
          if (mpEventDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
            selected = false;
          else
            selected = true;
        }
      else
        selected = true;
    }

  mpBtnDelete->setEnabled(selected);

  if (mpProxyModel->rowCount() - 1)
    mpBtnClear->setEnabled(true);
  else
    mpBtnClear->setEnabled(false);
}

void CQEventsWidget::slotSelectionChanged()
{
  updateDeleteBtns();
}

void CQEventsWidget::dataChanged(const QModelIndex &C_UNUSED(topLeft),
                                 const QModelIndex &C_UNUSED(bottomRight))
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblEvents->resizeColumnsToContents();
    }

  updateDeleteBtns();
}

void CQEventsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (index.row() < 0)
    return;

  if (mpEventDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  CDataVector < CEvent > * pVector = dynamic_cast< CDataVector < CEvent > * >(mpObject);

  if (pVector != NULL &&
      index.row() < pVector->size())
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::EventDetail, pVector->operator [](index.row()).getCN());
    }
}

void CQEventsWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && (ev->modifiers() & Qt::ControlModifier))
    {
      QModelIndexList selRows = mpTblEvents->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpEventDM->columnCount(); ++x)
            {
              if (!mpTblEvents->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpEventDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQEventsWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter + "|New Event");

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}
