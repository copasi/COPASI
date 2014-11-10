// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtGui/QHeaderView>
#include <QtGui/QClipboard>
#include <QtGui/QKeyEvent>

#include "qtUtilities.h"
#include "copasi.h"
#include "CQMessageBox.h"

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#ifdef COPASI_UNDO
#include "copasiui3window.h"
#endif

/*
 *  Constructs a CQEventsWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEventsWidget::CQEventsWidget(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  //Create Source Data Model.
  mpEventDM = new CQEventDM(this);

  //Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);

  mpTblEvents->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblEvents->verticalHeader()->hide();
  mpTblEvents->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);

  // Connect the table widget
  connect(mpEventDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpEventDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));

#ifdef COPASI_UNDO
  CopasiUI3Window *  pWindow = dynamic_cast<CopasiUI3Window * >(parent->parent());
  mpEventDM->setUndoStack(pWindow->getUndoStack());
  connect(mpEventDM, SIGNAL(changeWidget(const size_t&)), this, SLOT(slotChangeWidget(const size_t&)));
#endif
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
  mpEventDM->insertRow();
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
  const QItemSelectionModel * pSelectionModel = mpTblEvents->selectionModel();

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

bool CQEventsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

bool CQEventsWidget::leave()
{
  return true;
}

bool CQEventsWidget::enterProtected()
{
  if (mpTblEvents->selectionModel() != NULL)
    {
      disconnect(mpTblEvents->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
    }

  mpProxyModel->setSourceModel(mpEventDM);
  //Set Model for the TableView
  mpTblEvents->setModel(NULL);
  mpTblEvents->setModel(mpProxyModel);
  connect(mpTblEvents->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
          this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
  updateDeleteBtns();
  mpTblEvents->resizeColumnsToContents();

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

void CQEventsWidget::slotSelectionChanged(const QItemSelection& C_UNUSED(selected),
    const QItemSelection& C_UNUSED(deselected))
{
  updateDeleteBtns();
}

void CQEventsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                 const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblEvents->resizeColumnsToContents();
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

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  std::string key = pModel->getEvents()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}

void CQEventsWidget::keyPressEvent(QKeyEvent* ev)
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
  QRegExp regExp(mpLEFilter->text() + "|New Event", Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}

#ifdef COPASI_UNDO
void CQEventsWidget:: slotChangeWidget(const size_t & id)
{
  mpListView->switchToOtherWidget(id, "");
}
#endif
