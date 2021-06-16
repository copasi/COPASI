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

#include "CQFunctionsWidget.h"

#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/commandline/CConfigurationFile.h"

/*
 *  Constructs a CQFunctionsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFunctionsWidget::CQFunctionsWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name)
{
  setupUi(this);
  //Create Source Data Model.
  mpFunctionDM = new CQFunctionDM(this, mpDataModel);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblFunctions->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpTblFunctions->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpTblFunctions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpTblFunctions->verticalHeader()->hide();
  mpTblFunctions->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  // Connect the table widget
  connect(mpFunctionDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
  connect(mpFunctionDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFunctionsWidget::~CQFunctionsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpFunctionDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQFunctionsWidget::slotBtnNewClicked()
{
  mpFunctionDM->insertRow(mpFunctionDM->rowCount(), QModelIndex());
  updateDeleteBtns();
}

void CQFunctionsWidget::slotBtnDeleteClicked()
{
  if (mpTblFunctions->hasFocus())
    {deleteSelectedFunctions();}

  updateDeleteBtns();
}

void CQFunctionsWidget::deleteSelectedFunctions()
{
  const QItemSelectionModel *pSelectionModel = mpTblFunctions->selectionModel();
  QModelIndexList mappedSelRows;
  size_t i, imax = mpFunctionDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpFunctionDM->removeRows(mappedSelRows);
  updateDeleteBtns();
}

void CQFunctionsWidget::slotBtnClearClicked()
{
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all non-built-in, non-mass-acion, Functions?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      QModelIndexList mappedSelRows;
      size_t i, imax = mpFunctionDM->rowCount();

      for (i = 0; i < imax; i++)
        {
          mappedSelRows.append(mpFunctionDM->index((int) i, 0));
        }

      if (mappedSelRows.empty())
        return;

      mpFunctionDM->removeRows(mappedSelRows);
    }

  updateDeleteBtns();
}

bool CQFunctionsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (!mIgnoreUpdates && isVisible())
    {
      enterProtected();
    }

  return true;
}

bool CQFunctionsWidget::leaveProtected()
{
  return true;
}

bool CQFunctionsWidget::enterProtected()
{
  QByteArray State = mpTblFunctions->horizontalHeader()->saveState();
  blockSignals(true);

  mpFunctionDM->setDataModel(mpDataModel);
  mpProxyModel->setSourceModel(mpFunctionDM);
  //Set Model for the TableView
  mpTblFunctions->setModel(NULL);
  mpTblFunctions->setModel(mpProxyModel);

  updateDeleteBtns();
  mpTblFunctions->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblFunctions->resizeColumnsToContents();
    }

  emit initFilter();

  return true;
}

void CQFunctionsWidget::updateDeleteBtns()
{
  bool selected = false;
  QModelIndexList selRows = mpTblFunctions->selectionModel()->selectedRows();

  if (selRows.size() == 0)
    selected = false;
  else
    {
      if (selRows.size() == 1)
        {
          QModelIndex index = mpProxyModel->mapToSource(selRows[0]);

          if (mpFunctionDM->isDefaultRow(index) || mpFunctionDM->isFunctionReadOnly(index))
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

void CQFunctionsWidget::dataChanged(const QModelIndex &C_UNUSED(topLeft),
                                    const QModelIndex &C_UNUSED(bottomRight))
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblFunctions->resizeColumnsToContents();
    }

  updateDeleteBtns();
}

void CQFunctionsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (index.row() < 0)
    return;

  if (mpFunctionDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  CDataVector < CFunction > * pVector = dynamic_cast< CDataVector < CFunction > * >(mpObject);

  if (pVector != NULL &&
      index.row() < pVector->size())
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::FunctionDetail, pVector->operator [](index.row()).getCN());
    }
}

void CQFunctionsWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && (ev->modifiers() & Qt::ControlModifier))
    {
      QModelIndexList selRows = mpTblFunctions->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpFunctionDM->columnCount(); ++x)
            {
              if (!mpTblFunctions->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpFunctionDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQFunctionsWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter + "|New Function");

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}
