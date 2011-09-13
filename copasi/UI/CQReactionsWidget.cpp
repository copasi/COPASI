// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionsWidget.cpp,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/13 19:21:57 $
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

#include "CQReactionsWidget.h"
#include "qtUtilities.h"
#include "copasi.h"
#include "CQMessageBox.h"

/*
 *  Constructs a CQReactionsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQReactionsWidget::CQReactionsWidget(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpReactionDM = new CQReactionDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

  mpTblReactions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblReactions->verticalHeader()->hide();
  mpTblReactions->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  setFramework(mFramework);

  // Connect the table widget
  connect(mpReactionDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpReactionDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQReactionsWidget::~CQReactionsWidget()
{
  pdelete(mpProxyModel);
  pdelete(mpReactionDM);
  // no need to delete child widgets, Qt does it all for us
}

void CQReactionsWidget::slotBtnNewClicked()
{
  mpReactionDM->insertRow();
  updateDeleteBtns();
}

void CQReactionsWidget::slotBtnDeleteClicked()
{
  if (mpTblReactions->hasFocus())
    {deleteSelectedReactions();}

  updateDeleteBtns();
}

void CQReactionsWidget::deleteSelectedReactions()
{
  const QItemSelectionModel * pSelectionModel = mpTblReactions->selectionModel();

  QModelIndexList mappedSelRows;
  size_t i, imax = mpReactionDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty())
    {return;}

  mpReactionDM->removeRows(mappedSelRows);
}

void CQReactionsWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Reactions?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpReactionDM->clear();
    }

  updateDeleteBtns();
}

bool CQReactionsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

bool CQReactionsWidget::leave()
{
  return true;
}

bool CQReactionsWidget::enterProtected()
{
  if (mpTblReactions->selectionModel() != NULL)
    {
      disconnect(mpTblReactions->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
    }

  mpProxyModel->setSourceModel(mpReactionDM);
  //Set Model for the TableView
  mpTblReactions->setModel(NULL);
  mpTblReactions->setModel(mpProxyModel);
  connect(mpTblReactions->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
          this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
  updateDeleteBtns();
  mpTblReactions->resizeColumnsToContents();
  setFramework(mFramework);

  return true;
}

void CQReactionsWidget::updateDeleteBtns()
{
  bool selected = false;

  QModelIndexList selRows = mpTblReactions->selectionModel()->selectedRows();

  if (selRows.size() == 0)
    selected = false;
  else
    {
      if (selRows.size() == 1)
        {
          if (mpReactionDM->isDefaultRow(mpProxyModel->mapToSource(selRows[0])))
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

void CQReactionsWidget::slotSelectionChanged(const QItemSelection& C_UNUSED(selected),
    const QItemSelection& C_UNUSED(deselected))
{
  updateDeleteBtns();
}

void CQReactionsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                    const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblReactions->resizeColumnsToContents();
  setFramework(mFramework);
  updateDeleteBtns();
}

void CQReactionsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpReactionDM->isDefaultRow(index))
    {
      slotBtnNewClicked();
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  std::string key = pModel->getReactions()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQReactionsWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
  else if (ev->key() == Qt::Key_C && ev->modifiers() & Qt::ControlModifier)
    {
      QModelIndexList selRows = mpTblReactions->selectionModel()->selectedRows(0);

      if (selRows.empty())
        {return;}

      QString str;
      QModelIndexList::const_iterator i;

      for (i = selRows.begin(); i != selRows.end(); ++i)
        {
          for (int x = 0; x < mpReactionDM->columnCount(); ++x)
            {
              if (!mpTblReactions->isColumnHidden(x))
                {
                  if (!str.isEmpty())
                    str += "\t";

                  str += mpReactionDM->index(mpProxyModel->mapToSource(*i).row(), x).data().toString();
                }
            }

          str += "\n";
        }

      QApplication::clipboard()->setText(str);
    }
}

void CQReactionsWidget::slotFilterChanged()
{
  QRegExp regExp(mpLEFilter->text() + "|New Reaction", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}

void CQReactionsWidget::setFramework(int framework)
{
  CopasiWidget::setFramework(framework);

  switch (mFramework)
    {
      case 0:
        mpTblReactions->showColumn(COL_FLUX);
        mpTblReactions->hideColumn(COL_PARTICLE_FLUX);
        break;

      case 1:
        mpTblReactions->hideColumn(COL_FLUX);
        mpTblReactions->showColumn(COL_PARTICLE_FLUX);
        break;
    }
}
