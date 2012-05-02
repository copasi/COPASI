// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPlotsWidget.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/02 18:58:45 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQPlotsWidget.h"

#include <QtGui/QHeaderView>
#include <QtGui/QClipboard>
#include <QtGui/QKeyEvent>

#include "copasi.h"

#include "qtUtilities.h"
#include "CQMessageBox.h"

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"

/*
 *  Constructs a CQPlotsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQPlotsWidget::CQPlotsWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpPlotDM = new CQPlotDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

  mpTblPlots->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblPlots->verticalHeader()->hide();
  mpTblPlots->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  setFramework(mFramework);

  // Connect the table widget
  connect(mpPlotDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpPlotDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
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

void CQPlotsWidget::slotBtnNewClicked()
{
  mpPlotDM->insertRow();
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
  const QItemSelectionModel * pSelectionModel = mpTblPlots->selectionModel();

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

bool CQPlotsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

bool CQPlotsWidget::leave()
{
  return true;
}

bool CQPlotsWidget::enterProtected()
{
  if (mpTblPlots->selectionModel() != NULL)
    {
      disconnect(mpTblPlots->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
    }

  mpProxyModel->setSourceModel(mpPlotDM);
  //Set Model for the TableView
  mpTblPlots->setModel(NULL);
  mpTblPlots->setModel(mpProxyModel);
  connect(mpTblPlots->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
          this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
  updateDeleteBtns();
  mpTblPlots->resizeColumnsToContents();
  setFramework(mFramework);

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

void CQPlotsWidget::slotSelectionChanged(const QItemSelection& C_UNUSED(selected),
    const QItemSelection& C_UNUSED(deselected))
{
  updateDeleteBtns();
}

void CQPlotsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblPlots->resizeColumnsToContents();
  setFramework(mFramework);
  updateDeleteBtns();
}

void CQPlotsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpPlotDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (!pDataModel->getModel())
    return;

  CPlotSpecification *pPS = static_cast<CPlotSpecification *>(pDataModel->getPlotDefinitionList()->operator[](index.row()));
  const std::string key = static_cast<CCopasiParameter *>(pPS)->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQPlotsWidget::keyPressEvent(QKeyEvent* ev)
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
  QRegExp regExp(mpLEFilter->text() + "|New Plot", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}

void CQPlotsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);
}
