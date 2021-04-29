// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQUnitsWidget.h"

#include <QHeaderView>
#include <QClipboard>
#include <QKeyEvent>

#include "copasi/copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"
#include <copasi/commandline/CConfigurationFile.h>
/*
 *  Constructs a CQUnitsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQUnitsWidget::CQUnitsWidget(QWidget *parent, const char *name)
  : CopasiWidget(parent, name)
{
  setupUi(this);
  //Create Source Data Model.
  mpUnitDM = new CQUnitDM(this, mpDataModel);
  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);
  mpProxyModel->sort(COL_NAME_UNITS);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblUnits->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpTblUnits->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpTblUnits->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpTblUnits->verticalHeader()->hide();
  mpTblUnits->sortByColumn(COL_NAME_UNITS, Qt::AscendingOrder);
  setFramework(mFramework);
  // Connect the table widget
  connect(mpUnitDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
  connect(mpUnitDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpTblUnits, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotSelectionChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQUnitsWidget::~CQUnitsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpUnitDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQUnitsWidget::slotBtnNewClicked()
{
  mpUnitDM->insertRow(mpUnitDM->rowCount() - 1, QModelIndex());
  updateDeleteBtns();
}

void CQUnitsWidget::slotBtnDeleteClicked()
{
  if (mpTblUnits->hasFocus())
    {deleteSelectedUnits();}

  updateDeleteBtns();
}

void CQUnitsWidget::deleteSelectedUnits()
{
  const QItemSelectionModel *pSelectionModel = mpTblUnits->selectionModel();
  QModelIndexList mappedSelRows;
  size_t i, imax = mpUnitDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpUnitDM->removeRows(mappedSelRows);
}

void CQUnitsWidget::slotBtnClearClicked()
{
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all unused or non-built-in Units?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      QModelIndexList mappedSelRows;
      size_t i, imax = mpUnitDM->rowCount();

      for (i = 0; i < imax; i++)
        {
          mappedSelRows.append(mpUnitDM->index((int) i, 0));
        }

      if (mappedSelRows.empty())
        return;

      mpUnitDM->removeRows(mappedSelRows);
    }

  updateDeleteBtns();
}

bool CQUnitsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

bool CQUnitsWidget::leaveProtected()
{
  return true;
}

bool CQUnitsWidget::enterProtected()
{
  QByteArray State = mpTblUnits->horizontalHeader()->saveState();
  blockSignals(true);

  mpUnitDM->setDataModel(mpDataModel);
  mpProxyModel->setSourceModel(mpUnitDM);
  //Set Model for the TableView
  mpTblUnits->setModel(NULL);
  mpTblUnits->setModel(mpProxyModel);

  updateDeleteBtns();
  mpTblUnits->horizontalHeader()->restoreState(State);
  blockSignals(false);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblUnits->resizeColumnsToContents();
    }

  setFramework(mFramework);
  emit initFilter();

  return true;
}

void CQUnitsWidget::updateDeleteBtns()
{
  bool selected = false;
  QModelIndexList selRows = mpTblUnits->selectionModel()->selectedRows();

  if (selRows.size() == 0)
    selected = false;
  else
    {
      if (selRows.size() == 1)
        {
          if (mpUnitDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
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

void CQUnitsWidget::slotSelectionChanged()
{
  updateDeleteBtns();
}

void CQUnitsWidget::dataChanged(const QModelIndex &C_UNUSED(topLeft),
                                const QModelIndex &C_UNUSED(bottomRight))
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblUnits->resizeColumnsToContents();
    }

  setFramework(mFramework);
  updateDeleteBtns();
}

void CQUnitsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (index.row() < 0)
    return;

  if (mpUnitDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  CDataVector < CUnitDefinition > * pVector = dynamic_cast< CDataVector < CUnitDefinition > * >(mpObject);

  if (pVector != NULL &&
      index.row() < pVector->size())
    {
      mpListView->switchToOtherWidget(ListViews::WidgetType::UnitDetail, pVector->operator [](index.row()).getCN());
    }
}

void CQUnitsWidget::keyPressEvent(QKeyEvent *ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && (ev->modifiers() & Qt::ControlModifier))
    {
      QModelIndexList selRows = mpTblUnits->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpUnitDM->columnCount(); ++x)
            {
              if (!mpTblUnits->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpUnitDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQUnitsWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter + "|New Unit");

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}

void CQUnitsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
}
