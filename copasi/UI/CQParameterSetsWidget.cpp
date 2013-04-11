// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

#include "CQParameterSetsWidget.h"

#include <QtGui/QHeaderView>
#include <QtGui/QClipboard>
#include <QtGui/QKeyEvent>

#include "copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "report/CReportTemplateVector.h"

/*
 *  Constructs a CQParameterSetsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQParameterSetsWidget::CQParameterSetsWidget(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpParameterSetsDM = new CQParameterSetsDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

  mpTblParameterSets->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblParameterSets->verticalHeader()->hide();
  mpTblParameterSets->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  setFramework(mFramework);

  // Connect the table widget
  connect(mpParameterSetsDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpParameterSetsDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
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
  mpParameterSetsDM->insertRow();
  updateDeleteBtns();
}

void CQParameterSetsWidget::slotBtnDeleteClicked()
{
  if (mpTblParameterSets->hasFocus())
    {deleteSelected();}

  updateDeleteBtns();
}

void CQParameterSetsWidget::deleteSelected()
{
  const QItemSelectionModel * pSelectionModel = mpTblParameterSets->selectionModel();

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

  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Reports?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpParameterSetsDM->clear();
    }

  updateDeleteBtns();
}

bool CQParameterSetsWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates)
    {
      return true;
    }

  if (objectType == ListViews::MODEL &&
      (action == ListViews::DELETE ||
       action == ListViews::ADD))
    {
      mpDataModel = NULL;
      mpObject = NULL;
      mKey = "";
    }

  return true;
}

bool CQParameterSetsWidget::leave()
{
  return true;
}

bool CQParameterSetsWidget::enterProtected()
{
  if (mpObject == NULL)
    {
      return false;
    }

  if (mpTblParameterSets->selectionModel() != NULL)
    {
      disconnect(mpTblParameterSets->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
    }

  mpParameterSetsDM->setListOfModelParameterSets(&static_cast< CModel * >(mpObject)->getModelParameterSets());
  mpProxyModel->setSourceModel(mpParameterSetsDM);

  //Set Model for the TableView
  mpTblParameterSets->setModel(NULL);
  mpTblParameterSets->setModel(mpProxyModel);
  connect(mpTblParameterSets->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
          this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
  updateDeleteBtns();
  mpTblParameterSets->resizeColumnsToContents();
  setFramework(mFramework);

  mpBtnNew->hide();

  return true;
}

void CQParameterSetsWidget::updateDeleteBtns()
{
  bool selected = false;

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

  mpBtnDelete->setEnabled(selected);

  if (mpProxyModel->rowCount() - 1)
    mpBtnClear->setEnabled(true);
  else
    mpBtnClear->setEnabled(false);
}

void CQParameterSetsWidget::slotSelectionChanged(const QItemSelection& C_UNUSED(selected),
    const QItemSelection& C_UNUSED(deselected))
{
  updateDeleteBtns();
}

void CQParameterSetsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                        const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblParameterSets->resizeColumnsToContents();
  setFramework(mFramework);
  updateDeleteBtns();
}

void CQParameterSetsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpParameterSetsDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  if (mpObject == NULL)
    {
      return;
    }

  std::string key = static_cast< CModel * >(mpObject)->getModelParameterSets()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQParameterSetsWidget::keyPressEvent(QKeyEvent* ev)
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
  QRegExp regExp(mpLEFilter->text() + "|New Report", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}

void CQParameterSetsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
}
