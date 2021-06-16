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

#include "CQReportsWidget.h"

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
 *  Constructs a CQReportsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQReportsWidget::CQReportsWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name)
{
  setupUi(this);
  //Create Source Data Model.
  mpReportDM = new CQReportDM(this, mpDataModel);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblReports->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
  mpTblReports->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
  mpTblReports->verticalHeader()->hide();
  mpTblReports->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  setFramework(mFramework);
  // Connect the table widget
  connect(mpReportDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
  connect(mpReportDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpTblReports, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotSelectionChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQReportsWidget::~CQReportsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpReportDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQReportsWidget::slotBtnNewClicked()
{
  mpReportDM->insertRow(mpReportDM->rowCount() - 1, QModelIndex());
  updateDeleteBtns();
}

void CQReportsWidget::slotBtnDeleteClicked()
{
  if (mpTblReports->hasFocus())
    {deleteSelectedReports();}

  updateDeleteBtns();
}

void CQReportsWidget::deleteSelectedReports()
{
  const QItemSelectionModel *pSelectionModel = mpTblReports->selectionModel();
  QModelIndexList mappedSelRows;
  size_t i, imax = mpReportDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpReportDM->removeRows(mappedSelRows);
}

void CQReportsWidget::slotBtnClearClicked()
{
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Reports?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpReportDM->clear();
    }

  updateDeleteBtns();
}

bool CQReportsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (!mIgnoreUpdates && isVisible())
    {
      enterProtected();
    }

  return true;
}

bool CQReportsWidget::leaveProtected()
{
  return true;
}

bool CQReportsWidget::enterProtected()
{
  QByteArray State = mpTblReports->horizontalHeader()->saveState();
  blockSignals(true);

  mpReportDM->setDataModel(mpDataModel);
  mpProxyModel->setSourceModel(mpReportDM);
  //Set Model for the TableView
  mpTblReports->setModel(NULL);
  mpTblReports->setModel(mpProxyModel);

  updateDeleteBtns();
  mpTblReports->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblReports->resizeColumnsToContents();
    }

  setFramework(mFramework);
  emit initFilter();

  return true;
}

void CQReportsWidget::updateDeleteBtns()
{
  bool selected = false;
  QModelIndexList selRows = mpTblReports->selectionModel()->selectedRows();

  if (selRows.size() == 0)
    selected = false;
  else
    {
      if (selRows.size() == 1)
        {
          if (mpReportDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
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

void CQReportsWidget::slotSelectionChanged()
{
  updateDeleteBtns();
}

void CQReportsWidget::dataChanged(const QModelIndex &C_UNUSED(topLeft),
                                  const QModelIndex &C_UNUSED(bottomRight))
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblReports->resizeColumnsToContents();
    }

  setFramework(mFramework);
  updateDeleteBtns();
}

void CQReportsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (index.row() < 0)
    return;

  if (mpReportDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  CDataVector < CReportDefinition > * pVector = dynamic_cast< CDataVector < CReportDefinition > * >(mpObject);

  if (pVector != NULL &&
      index.row() < pVector->size())
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::ReportTemplateDetail, pVector->operator [](index.row()).getCN());
    }
}

void CQReportsWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && (ev->modifiers() & Qt::ControlModifier))
    {
      QModelIndexList selRows = mpTblReports->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpReportDM->columnCount(); ++x)
            {
              if (!mpTblReports->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpReportDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQReportsWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter + "|New Report");

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}

void CQReportsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
}
