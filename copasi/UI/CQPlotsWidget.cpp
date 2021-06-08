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

#include "CQPlotsWidget.h"

#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plot/CPlotSpecification.h"
#include <copasi/commandline/CConfigurationFile.h>

/*
 *  Constructs a CQPlotsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQPlotsWidget::CQPlotsWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name)
{
  setupUi(this);
  //Create Source Data Model.
  mpPlotDM = new CQPlotDM(this, mpDataModel);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblPlots->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpTblPlots->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpTblPlots->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpTblPlots->verticalHeader()->hide();
  mpTblPlots->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  setFramework(mFramework);
  // Connect the table widget
  connect(mpPlotDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
  connect(mpPlotDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpBtnActivateAll, SIGNAL(pressed()), this, SLOT(slotBtnActivateAllClicked()));
  connect(mpBtnDeactivateAll, SIGNAL(pressed()), this, SLOT(slotBtnDeactivateAllClicked()));
  connect(mpTblPlots, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotSelectionChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQPlotsWidget::~CQPlotsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpPlotDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQPlotsWidget::slotBtnActivateAllClicked()
{
  assert(mpDataModel != NULL);

  if (!mpDataModel->getModel())
    return;

  for (size_t i = 0; i < mpDataModel->getPlotDefinitionList()->size(); i++)
    {
      CPlotSpecification *pPS = static_cast<CPlotSpecification *>(&mpDataModel->getPlotDefinitionList()->operator[](i));
      pPS->setActive(true);
    }

  mpTblPlots->doItemsLayout();
}

void CQPlotsWidget::slotBtnDeactivateAllClicked()
{
  assert(mpDataModel != NULL);

  if (!mpDataModel->getModel())
    return;

  for (size_t i = 0; i < mpDataModel->getPlotDefinitionList()->size(); i++)
    {
      CPlotSpecification *pPS = static_cast<CPlotSpecification *>(&mpDataModel->getPlotDefinitionList()->operator[](i));
      pPS->setActive(false);
    }

  mpTblPlots->doItemsLayout();
}

void CQPlotsWidget::slotBtnNewClicked()
{
  mpPlotDM->insertRow(mpPlotDM->rowCount() - 1, QModelIndex());
  updateDeleteBtns();
}

void CQPlotsWidget::slotBtnDeleteClicked()
{
  if (mpTblPlots->hasFocus())
    {deleteSelectedPlots();}

  updateDeleteBtns();
}

void CQPlotsWidget::deleteSelectedPlots()
{
  const QItemSelectionModel *pSelectionModel = mpTblPlots->selectionModel();
  QModelIndexList mappedSelRows;
  size_t i, imax = mpPlotDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpPlotDM->removeRows(mappedSelRows);
}

void CQPlotsWidget::slotBtnClearClicked()
{
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Plots?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpPlotDM->clear();
    }

  updateDeleteBtns();
}

bool CQPlotsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (!mIgnoreUpdates && isVisible())
    {
      enterProtected();
    }

  return true;
}

bool CQPlotsWidget::leaveProtected()
{
  return true;
}

bool CQPlotsWidget::enterProtected()
{
  QByteArray State = mpTblPlots->horizontalHeader()->saveState();
  blockSignals(true);

  mpPlotDM->setDataModel(mpDataModel);
  mpProxyModel->setSourceModel(mpPlotDM);
  //Set Model for the TableView
  mpTblPlots->setModel(NULL);
  mpTblPlots->setModel(mpProxyModel);
  connect(mpTblPlots->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
          this, SLOT(slotSelectionChanged()));

  updateDeleteBtns();
  mpTblPlots->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblPlots->resizeColumnsToContents();
    }

  setFramework(mFramework);
  emit initFilter();

  return true;
}

void CQPlotsWidget::updateDeleteBtns()
{
  bool selected = false;
  QModelIndexList selRows = mpTblPlots->selectionModel()->selectedRows();

  if (selRows.size() == 0)
    selected = false;
  else
    {
      if (selRows.size() == 1)
        {
          if (mpPlotDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
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

void CQPlotsWidget::slotSelectionChanged()
{
  updateDeleteBtns();
}

void CQPlotsWidget::dataChanged(const QModelIndex &C_UNUSED(topLeft),
                                const QModelIndex &C_UNUSED(bottomRight))
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblPlots->resizeColumnsToContents();
    }

  setFramework(mFramework);
  updateDeleteBtns();
}

void CQPlotsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (index.row() < 0)
    return;

  if (mpPlotDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  CDataVector < CPlotSpecification > * pVector = dynamic_cast< CDataVector < CPlotSpecification > * >(mpObject);

  if (pVector != NULL &&
      index.row() < pVector->size())
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::PlotDetail, pVector->operator [](index.row()).getCN());
    }
}

void CQPlotsWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C &&
           (ev->modifiers() & Qt::ControlModifier))
    {
      QModelIndexList selRows = mpTblPlots->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpPlotDM->columnCount(); ++x)
            {
              if (!mpTblPlots->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpPlotDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQPlotsWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter + "|New Plot");

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}

void CQPlotsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
}
