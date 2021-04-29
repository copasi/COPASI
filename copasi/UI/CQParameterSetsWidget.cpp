// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQParameterSetsWidget.h"

#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/commandline/CConfigurationFile.h"

/*
 *  Constructs a CQParameterSetsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQParameterSetsWidget::CQParameterSetsWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name)
{
  setupUi(this);
  //Create Source Data Model.
  mpParameterSetsDM = new CQParameterSetsDM(this);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblParameterSets->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpTblParameterSets->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpTblParameterSets->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpTblParameterSets->verticalHeader()->hide();
  mpTblParameterSets->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  setFramework(mFramework);
  // Connect the table widget
  connect(mpParameterSetsDM, SIGNAL(signalNotifyChanges(const CUndoData::CChangeSet &)),
          this, SLOT(slotNotifyChanges(const CUndoData::CChangeSet &)));
  connect(mpParameterSetsDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpTblParameterSets, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotSelectionChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQParameterSetsWidget::~CQParameterSetsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpParameterSetsDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQParameterSetsWidget::slotBtnNewClicked()
{
  mpParameterSetsDM->insertRow(mpParameterSetsDM->rowCount(), QModelIndex());
  updateDeleteBtns();

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblParameterSets->resizeColumnsToContents();
    }
}

void CQParameterSetsWidget::slotBtnDeleteClicked()
{
  if (mpTblParameterSets->hasFocus())
    {deleteSelected();}

  updateDeleteBtns();
}

void CQParameterSetsWidget::deleteSelected()
{
  const QItemSelectionModel *pSelectionModel = mpTblParameterSets->selectionModel();
  QModelIndexList mappedSelRows;
  size_t i, imax = mpParameterSetsDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpParameterSetsDM->removeRows(mappedSelRows);
}

void CQParameterSetsWidget::slotBtnClearClicked()
{
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Parameter Sets?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpParameterSetsDM->clear();
    }

  updateDeleteBtns();
}

bool CQParameterSetsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (objectType == ListViews::ObjectType::MODEL &&
      (action == ListViews::DELETE ||
       action == ListViews::ADD))
    {
      mpObject = NULL;
      mObjectCN.clear();
    }

  if (mIgnoreUpdates || !isVisible())
    {
      return true;
    }

  if (objectType == ListViews::ObjectType::MODEL ||
      objectType == ListViews::ObjectType::MODELPARAMETERSET)
    {
      enterProtected();
    }

  return true;
}

bool CQParameterSetsWidget::leaveProtected()
{
  return true;
}

bool CQParameterSetsWidget::enterProtected()
{
  if (mpObject == NULL)
    {
      if (mpDataModel != NULL)
        mpObject = &mpDataModel->getModel()->getModelParameterSets();

      if (mpObject == NULL)
        return false;
    }

  QByteArray State = mpTblParameterSets->horizontalHeader()->saveState();
  blockSignals(true);

  mpParameterSetsDM->setListOfModelParameterSets(dynamic_cast< CDataVectorN< CModelParameterSet > * >(mpObject));
  mpProxyModel->setSourceModel(mpParameterSetsDM);
  //Set Model for the TableView
  mpTblParameterSets->setModel(NULL);
  mpTblParameterSets->setModel(mpProxyModel);
  connect(mpTblParameterSets->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
          this, SLOT(slotSelectionChanged()));

  updateDeleteBtns();
  mpTblParameterSets->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblParameterSets->resizeColumnsToContents();
    }

  setFramework(mFramework);
  emit initFilter();

  return true;
}

void CQParameterSetsWidget::updateDeleteBtns()
{
  bool selected = false;

  if (mpTblParameterSets->selectionModel() != NULL)
    {
      QModelIndexList selRows = mpTblParameterSets->selectionModel()->selectedRows();

      if (selRows.size() == 0)
        selected = false;
      else
        {
          if (selRows.size() == 1)
            {
              if (mpParameterSetsDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
                selected = false;
              else
                selected = true;
            }
          else
            selected = true;
        }
    }

  mpBtnDelete->setEnabled(selected);

  if (mpProxyModel->rowCount() - 1)
    mpBtnClear->setEnabled(true);
  else
    mpBtnClear->setEnabled(false);
}

void CQParameterSetsWidget::slotSelectionChanged()
{
  updateDeleteBtns();
}

void CQParameterSetsWidget::dataChanged(const QModelIndex &C_UNUSED(topLeft),
                                        const QModelIndex &C_UNUSED(bottomRight))
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblParameterSets->resizeColumnsToContents();
    }

  setFramework(mFramework);
  updateDeleteBtns();
}

void CQParameterSetsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (index.row() < 0)
    return;

  if (mpParameterSetsDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  CDataVector < CModelParameterSet > * pVector = dynamic_cast< CDataVector < CModelParameterSet > * >(mpObject);

  if (pVector != NULL &&
      index.row() < pVector->size())
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::ParameterSetDetail, pVector->operator [](index.row()).getCN());
    }
}

void CQParameterSetsWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && (ev->modifiers() & Qt::ControlModifier))
    {
      QModelIndexList selRows = mpTblParameterSets->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpParameterSetsDM->columnCount(); ++x)
            {
              if (!mpTblParameterSets->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpParameterSetsDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQParameterSetsWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter);

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}

void CQParameterSetsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
}
