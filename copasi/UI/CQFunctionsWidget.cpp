// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFunctionsWidget.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/07/05 17:34:42 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QHeaderView>
#include <QClipboard>

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "function/CFunctionDB.h"

#include "CQFunctionsWidget.h"
#include "qtUtilities.h"
#include "copasi.h"
#include "CQMessageBox.h"

/*
 *  Constructs a CQFunctionsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFunctionsWidget::CQFunctionsWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpFunctionDM = new CQFunctionDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

  mpTblFunctions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblFunctions->verticalHeader()->hide();
  mpTblFunctions->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  // Connect the table widget
  connect(mpFunctionDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpFunctionDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
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
  mpFunctionDM->insertRow();
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
  const QItemSelectionModel * pSelectionModel = mpTblFunctions->selectionModel();

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
}

void CQFunctionsWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Functions?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpFunctionDM->clear();
    }

  updateDeleteBtns();
}

bool CQFunctionsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

bool CQFunctionsWidget::leave()
{
  return true;
}

bool CQFunctionsWidget::enterProtected()
{
  if (mpTblFunctions->selectionModel() != NULL)
    {
      disconnect(mpTblFunctions->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
    }

  mpProxyModel->setSourceModel(mpFunctionDM);
  //Set Model for the TableView
  mpTblFunctions->setModel(NULL);
  mpTblFunctions->setModel(mpProxyModel);
  connect(mpTblFunctions->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
          this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
  updateDeleteBtns();
  mpTblFunctions->resizeColumnsToContents();

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
          if (mpFunctionDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
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

void CQFunctionsWidget::slotSelectionChanged(const QItemSelection& C_UNUSED(selected),
    const QItemSelection& C_UNUSED(deselected))
{
  updateDeleteBtns();
}

void CQFunctionsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                    const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblFunctions->resizeColumnsToContents();
  updateDeleteBtns();
}

void CQFunctionsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpFunctionDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  std::string key = CCopasiRootContainer::getFunctionList()->loadedFunctions()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(0, key);
}

void CQFunctionsWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && ev->modifiers() & Qt::ControlModifier)
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
  QRegExp regExp(mpLEFilter->text() + "|New Function", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}
