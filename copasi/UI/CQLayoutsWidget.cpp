// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLayoutsWidget.cpp,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:00 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQLayoutsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qregexp.h>
#include <qvalidator.h>

#include <iostream>

#include "CQMessageBox.h"
#include "CQLayoutsDM.h"
#include "CQSortFilterProxyModel.h"
#include "CQPushButtonDelegate.h"

#include "listviews.h"
#include "qtUtilities.h"
#include "copasi/layout/CLayout.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

#ifdef USE_CRENDER_EXTENSION
# include "copasi/layoutUI/CQNewMainWindow.h"
#else
# include "copasi/layoutUI/CQLayoutMainWindow.h"
#endif // USE_CRENDER_EXTENSION

#ifdef COPASI_AUTOLAYOUT
# include "copasi/layoutUI/CQAutolayoutWizard.h"
#endif // COPASI_AUTOLAYOUT


CQLayoutsWidget::CQLayoutsWidget(QWidget* parent)
    : CopasiWidget(parent)
{
  setupUi(this);

#ifndef COPASI_AUTOLAYOUT
  mpBtnNew->hide();
#endif

  // Create Source Data Model.
  mpLayoutsDM = new CQLayoutsDM(this);

  // Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);
  mpProxyModel->setSourceModel(mpLayoutsDM);

  mpTblLayouts->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblLayouts->verticalHeader()->hide();
  mpTblLayouts->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  mpTblLayouts->setModel(mpProxyModel);

  mpPushButtonDelegate = new CQPushButtonDelegate(QIcon(), QString(), this);

  mpTblLayouts->setItemDelegateForColumn(COL_SHOW, mpPushButtonDelegate);

  // Connect the table widget
  connect(mpLayoutsDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const std::string)));
  connect(mpLayoutsDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
          this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpPushButtonDelegate, SIGNAL(clicked(int)), this, SLOT(slotShowLayout(int)));
}

// virtual
CQLayoutsWidget::~CQLayoutsWidget()
{}

// virtual
bool CQLayoutsWidget::update(ListViews::ObjectType /* objectType */, ListViews::Action /* action */, const std::string & /* key */)
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

// virtual
bool CQLayoutsWidget::leave()
{
  return true;
}

void CQLayoutsWidget::deleteLayoutWindows()
{
  LayoutWindowMap::iterator it = mLayoutWindowMap.begin(), endit = mLayoutWindowMap.end();

  while (it != endit)
    {
      delete it->second;
      ++it;
    }

  mLayoutWindowMap.clear();
}

void CQLayoutsWidget::deleteSelectedLayouts()
{
  const QItemSelectionModel * pSelectionModel = mpTblLayouts->selectionModel();

  QModelIndexList mappedSelRows;
  size_t i, imax = mpLayoutsDM->rowCount();

  for (i = 0; i < imax; i++)
    {
      if (pSelectionModel->isRowSelected((int) i, QModelIndex()))
        {
          mappedSelRows.append(mpProxyModel->mapToSource(mpProxyModel->index((int) i, 0)));
        }
    }

  if (mappedSelRows.empty()) return;

  // We need to make sure that we remove the window mapped for each layout
  QModelIndexList::const_iterator it = mappedSelRows.begin();
  QModelIndexList::const_iterator end = mappedSelRows.end();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CListOfLayouts * pListOfLayouts = (*CCopasiRootContainer::getDatamodelList())[0]->getListOfLayouts();

  for (; it != end; ++it)
    {
      LayoutWindowMap::iterator itWindow = mLayoutWindowMap.find((*pListOfLayouts)[it->row()]->getKey());

      if (itWindow != mLayoutWindowMap.end())
        {
          mLayoutWindowMap.erase(itWindow);
          delete itWindow->second;
        }
    }

  mpLayoutsDM->removeRows(mappedSelRows);
}


void CQLayoutsWidget::updateDeleteBtns()
{
  mpBtnDelete->setEnabled(mpTblLayouts->selectionModel()->selectedRows().size() > 0);
  mpBtnClear->setEnabled(mpProxyModel->rowCount() > 0);
}

// virtual
bool CQLayoutsWidget::enterProtected()
{
  if (mpTblLayouts->selectionModel() != NULL)
    {
      disconnect(mpTblLayouts->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
                 this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));
    }


  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CListOfLayouts * pListOfLayouts = (*CCopasiRootContainer::getDatamodelList())[0]->getListOfLayouts();
  mpLayoutsDM->setListOfLayouts(pListOfLayouts);

  // check if we have at least a compartment
  // that we can lay out.
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];

  if (pDataModel != NULL &&
      pDataModel->getModel() != NULL &&
      pDataModel->getModel()->getCompartments().size() > 0)
    {
      mpBtnNew->setEnabled(true);
    }
  else
    {
      mpBtnNew->setEnabled(false);
    }

  // We need to make sure that we have a window mapped for each layout
  CListOfLayouts::const_iterator it = pListOfLayouts->begin();
  CListOfLayouts::const_iterator end = pListOfLayouts->end();

  for (; it != end; ++it)
    {
      LayoutWindowMap::iterator pos = mLayoutWindowMap.find((*it)->getKey());

      // if this layout does not have an entry in the layout window map, add one
      if (pos == mLayoutWindowMap.end())
        {
          mLayoutWindowMap.insert(std::pair<std::string, LayoutWindow*>((*it)->getKey(), NULL));
        }

    }

  connect(mpTblLayouts->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
          this, SLOT(slotSelectionChanged(const QItemSelection&, const QItemSelection&)));

  dataChanged(QModelIndex(), QModelIndex());

  return true;
}


void CQLayoutsWidget::showButtons()
{
  int i, imax = mpLayoutsDM->rowCount();

  for (i = 0; i < imax; ++i)
    {
      this->mpTblLayouts->openPersistentEditor(mpProxyModel->index(i, COL_SHOW, QModelIndex()));
    }
}


// virtual
void CQLayoutsWidget::slotBtnNewClicked()
{
#ifdef COPASI_AUTOLAYOUT
  CLayout* pLayout = new CLayout("COPASI autolayout");
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  const CModel* pModel = pDataModel->getModel();
  assert(pModel != NULL);
  CQAutolayoutWizard* pWizard = new CQAutolayoutWizard(*pModel);

  if (pWizard->exec() == QDialog::Accepted)
    {
      // add the layout to the datamodel
      std::map<std::string, std::string> m;

      CListOfLayouts * pListOfLayouts = pDataModel->getListOfLayouts();
      pListOfLayouts->addLayout(pLayout, m);

      // update the table
      mpLayoutsDM->insertRows(pListOfLayouts->size() - 1, 1);
      dataChanged(QModelIndex(), QModelIndex());

      CQNewMainWindow* pWin = createLayoutWindow(pListOfLayouts->size() - 1, pLayout);
      assert(pWin != NULL);

      if (pWin != NULL)
        {
          // create the random layout
          pWin->createRandomLayout(pWizard->getSelectedCompartments(), pWizard->getSelectedReactions(), pWizard->getSelectedMetabolites(), pWizard->getSideMetabolites());
          pWin->updateRenderer();
          // show the new layout
          pWin->show();
          pWin->redrawNow();
          // now we create the spring layout
          pWin->createSpringLayout(1000, 1);
        }

    }
  else
    {
      delete pLayout;
    }

#endif // COPASI_AUTOLAYOUT
}

// virtual
void CQLayoutsWidget::slotBtnDeleteClicked()
{
  if (mpTblLayouts->hasFocus())
    {deleteSelectedLayouts();}
}


// virtual
void CQLayoutsWidget::slotBtnClearClicked()
{
  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Layouts?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpLayoutsDM->clear();
      deleteLayoutWindows();
    }
}

// virtual
void CQLayoutsWidget::slotSelectionChanged(const QItemSelection & /* selected */,
    const QItemSelection & /* deselected */)
{
  updateDeleteBtns();
}


// virtual
void CQLayoutsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  int row = index.row();

  if (row >= mpLayoutsDM->rowCount() || row < 0) return;

  slotShowLayout(row);
}

// virtual
void CQLayoutsWidget::dataChanged(const QModelIndex & /* topLeft */,
                                  const QModelIndex & /* bottomRight */)
{
  mpTblLayouts->resizeColumnsToContents();
  updateDeleteBtns();
  showButtons();
}

// virtual
void CQLayoutsWidget::slotFilterChanged()
{
  QRegExp regExp(mpLEFilter->text(), Qt::CaseInsensitive, QRegExp::RegExp);
  mpProxyModel->setFilterRegExp(regExp);
}


/**
 * This creates a new layout window and return a pointer to it.
 * In case of an error, NULL is returned.
 */
CQLayoutsWidget::LayoutWindow * CQLayoutsWidget::createLayoutWindow(int row, CLayout* pLayout)
{
  if (pLayout == NULL || row < 0) return NULL;

#ifdef USE_CRENDER_EXTENSION
  LayoutWindow * pWin = new CQNewMainWindow((*CCopasiRootContainer::getDatamodelList())[0]);
  pWin->slotLayoutChanged(row);
#else
  LayoutWindow * pWin = new CQLayoutMainWindow(pLayout);
#endif // USE_CRENDER_EXTENSION

  pWin->setWindowTitle(pLayout->getObjectName().c_str());
  pWin->resize(900, 600);
  mLayoutWindowMap[pLayout->getKey()] = pWin;

  return pWin;
}

void CQLayoutsWidget::slotShowLayout(int row)
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CListOfLayouts* pListOfLayouts = (*CCopasiRootContainer::getDatamodelList())[0]->getListOfLayouts();

  CLayout* pLayout = (* pListOfLayouts)[row];
  std::string Key = pLayout->getKey();

  if (pLayout != NULL)
    {
      // check if we already have a widget for the layout
      // if yes, open it, else create one and add it to the map
      LayoutWindow * pLayoutWindow = NULL;

      LayoutWindowMap::iterator pos = mLayoutWindowMap.find(Key);

      if (pos != mLayoutWindowMap.end())
        {
          pLayoutWindow = pos->second;
        }

      if (pLayoutWindow == NULL)
        {
          pLayoutWindow = createLayoutWindow(row, pLayout);
        }

      if (pLayoutWindow != NULL)
        {
#ifdef USE_CRENDER_EXTENSION
          pLayoutWindow->slotLayoutChanged(row);
#endif // USE_CRENDER_EXTENSION
          pLayoutWindow->show();
          pLayoutWindow->showNormal();
          pLayoutWindow->setActiveWindow();
        }
    }
  else
    {
      //std::cerr << "Could not find layout." << std::endl;
    }
}

