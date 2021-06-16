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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQLayoutsWidget.h"

#include <iostream>

#include "CQMessageBox.h"
#include "CQLayoutsDM.h"
#include "CQSortFilterProxyModel.h"
#include "CQPushButtonDelegate.h"

#include "listviews.h"
#include "qtUtilities.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/layout/CLayout.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include <copasi/commandline/CConfigurationFile.h>
#include "copasi/core/CRootContainer.h"

#include <copasi/layout/CCopasiSpringLayout.h>

#if WITH_LEGACY_OPENGL
#include "copasi/layoutUI/CQNewMainWindow.h"
#endif

#ifndef DISABLE_QT_LAYOUT_RENDERING
# include <copasi/qlayout/CQAnimationWindow.h>
#endif //DISABLE_QT_LAYOUT_RENDERING

#include "copasi/layoutUI/CQAutolayoutWizard.h"

#include <copasi/UI/copasiui3window.h>

#include <sstream>

CQLayoutsWidget::CQLayoutsWidget(QWidget *parent)
  : CopasiWidget(parent)
{
  setupUi(this);
  // Create Source Data Model.
  mpLayoutsDM = new CQLayoutsDM(this);
  // Create the Proxy Model for sorting/filtering and set its properties.
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(-1);
  mpProxyModel->setSourceModel(mpLayoutsDM);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  mpTblLayouts->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
#endif

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
      mpTblLayouts->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
      mpTblLayouts->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif
    }

  mpTblLayouts->verticalHeader()->hide();
  mpTblLayouts->sortByColumn(COL_ROW_NUMBER, Qt::AscendingOrder);
  mpTblLayouts->setModel(mpProxyModel);
  mpPushButtonDelegate = new CQPushButtonDelegate(CQIconResource::icon(CQIconResource::unknown), QString(), CQPushButtonDelegate::PushButton, this);
  mpTblLayouts->setItemDelegateForColumn(COL_SHOW, mpPushButtonDelegate);
  // Connect the table widget
  connect(mpLayoutsDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const CCommonName &)),
          this, SLOT(protectedNotify(ListViews::ObjectType, ListViews::Action, const CCommonName &)));
  connect(mpLayoutsDM, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
          this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(initFilter()), this, SLOT(slotFilterChanged()));
  connect(mpLEFilter, SIGNAL(textChanged(const QString &)),
          this, SLOT(slotFilterChanged()));
  connect(mpPushButtonDelegate, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotShowLayout(const QModelIndex &)));
  connect(mpTblLayouts, SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotSelectionChanged()));
}

// virtual
CQLayoutsWidget::~CQLayoutsWidget()
{
  pdelete(mpProxyModel);
}

// virtual
bool CQLayoutsWidget::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (!mIgnoreUpdates)
    {
      enterProtected();
    }

  return true;
}

// virtual
bool CQLayoutsWidget::leaveProtected()
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
  const QItemSelectionModel *pSelectionModel = mpTblLayouts->selectionModel();
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
  assert(mpDataModel != NULL);
  CListOfLayouts *pListOfLayouts = mpDataModel->getListOfLayouts();

  for (; it != end; ++it)
    {
      LayoutWindowMap::iterator itWindow = mLayoutWindowMap.find((*pListOfLayouts)[it->row()].getKey());

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
  QByteArray State = mpTblLayouts->horizontalHeader()->saveState();
  blockSignals(true);

  assert(mpDataModel != NULL);
  CListOfLayouts *pListOfLayouts = mpDataModel->getListOfLayouts();
  mpLayoutsDM->setListOfLayouts(pListOfLayouts);

  // check if we have at least a compartment
  // that we can lay out.

  if (mpDataModel != NULL &&
      mpDataModel->getModel() != NULL &&
      mpDataModel->getModel()->getCompartments().size() > 0)
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
      LayoutWindowMap::iterator pos = mLayoutWindowMap.find(it->getKey());

      // if this layout does not have an entry in the layout window map, add one
      if (pos == mLayoutWindowMap.end())
        {
          mLayoutWindowMap.insert(std::pair<std::string, LayoutWindow *>(it->getKey(), (LayoutWindow *)NULL));
        }
    }

  updateDeleteBtns();
  mpTblLayouts->horizontalHeader()->restoreState(State);
  blockSignals(false);

  dataChanged(QModelIndex(), QModelIndex());
  emit initFilter();

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

bool hasLayout(const CListOfLayouts &layouts, const std::string &name)
{
  for (size_t i = 0; i < layouts.size(); ++i)
    {
      const CLayout *layout = &layouts[i];
      const std::string &current = layout->getObjectName();

      if (current == name)
        return true;
    }

  return false;
}

// virtual
void CQLayoutsWidget::slotBtnNewClicked()
{
  const CModel *pModel = mpDataModel->getModel();
  assert(pModel != NULL);
  std::string name = "COPASI autolayout";
  int ncount = 1;

  while (hasLayout(*(mpDataModel->getListOfLayouts()), name))
    {
      std::stringstream str;
      str << "COPASI autolayout " << ncount++;
      name = str.str();
    }

  CQAutolayoutWizard pWizard(*pModel);

  if (pWizard.exec() != QDialog::Accepted)
    return;

  // add the layout to the datamodel
  std::map<std::string, std::string> m;
  CListOfLayouts *pListOfLayouts = mpDataModel->getListOfLayouts();
  // create the random layout
  CCopasiSpringLayout::Parameters p;
  CLayout *pLayout = CCopasiSpringLayout::createLayout(
                       mpDataModel, pWizard.getSelectedCompartments(),
                       pWizard.getSelectedReactions(),
                       pWizard.getSelectedMetabolites(),
                       pWizard.getSideMetabolites(),
                       &p);
  pLayout->setObjectName(name);
  pListOfLayouts->addLayout(pLayout, m);
  // update the table
  mpLayoutsDM->insertRows(mpLayoutsDM->rowCount(), 1);
  dataChanged(QModelIndex(), QModelIndex());
  LayoutWindow *window = createLayoutWindow(pListOfLayouts->size() - 1, pLayout);
#ifndef DISABLE_QT_LAYOUT_RENDERING
  CQAnimationWindow *pAnim = dynamic_cast<CQAnimationWindow *>(window);

  if (pAnim != NULL)
    {
      pAnim->show();
      // now we create the spring layout
      pAnim->slotAutoLayout();
    }
  else
#endif //DISABLE_QT_LAYOUT_RENDERING
#if WITH_LEGACY_OPENGL
    CQNewMainWindow * pWin = dynamic_cast< CQNewMainWindow * >(window);

  if (pWin != NULL)
    {
      pWin->updateRenderer();
      pWin->setMode();
      // show the new layout
      pWin->show();
      pWin->redrawNow();
      // now we create the spring layout
      pWin->slotRunSpringLayout();
    }
  else
#endif // WITH_LEGACY_OPENGL
    {
      delete pLayout;
    }
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
  int ret = CQMessageBox::question(this, tr("Confirm Delete"), "Delete all Layouts?",
                                   QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpLayoutsDM->clear();
      deleteLayoutWindows();
    }
}

// virtual
void CQLayoutsWidget::slotSelectionChanged()
{
  updateDeleteBtns();
}

// virtual
void CQLayoutsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);
  int row = index.row();

  if (row >= mpLayoutsDM->rowCount() || row < 0) return;

  slotShowLayout(index);
}

// virtual
void CQLayoutsWidget::dataChanged(const QModelIndex & /* topLeft */,
                                  const QModelIndex & /* bottomRight */)
{
  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpTblLayouts->resizeColumnsToContents();
    }

  updateDeleteBtns();
  showButtons();
}

// virtual
void CQLayoutsWidget::slotFilterChanged()
{
  QString Filter = mpLEFilter->text();

  setFilterExpression(mpProxyModel, Filter.isEmpty(), Filter);

  while (mpProxyModel->canFetchMore(QModelIndex()))
    mpProxyModel->fetchMore(QModelIndex());
}

/**
 * This creates a new layout window and return a pointer to it.
 * In case of an error, NULL is returned.
 */
CQLayoutsWidget::LayoutWindow *CQLayoutsWidget::createLayoutWindow(int row, CLayout *pLayout)
{
  if (pLayout == NULL || row < 0) return NULL;

  LayoutWindow *pWin = NULL;
#ifndef DISABLE_QT_LAYOUT_RENDERING
#  if WITH_LEGACY_OPENGL

  if (CRootContainer::getConfiguration()->useOpenGL())
    {
      pWin = new CQNewMainWindow(mpDataModel);
      (static_cast<CQNewMainWindow *>(pWin))->slotLayoutChanged(row);
    }
  else
#endif
    {
      pWin = new CQAnimationWindow(pLayout, mpDataModel);
    }

#else
  pWin = new CQNewMainWindow(mpDataModel);
  (static_cast<CQNewMainWindow *>(pWin))->slotLayoutChanged(row);
#endif //DISABLE_QT_LAYOUT_RENDERING
  std::string title = "COPASI Diagram: "  + pLayout->getObjectName();
  pWin->setWindowTitle(title.c_str());
  pWin->addToMainWindow();
  pWin->resize(900, 600);
  mLayoutWindowMap[pLayout->getKey()] = pWin;
  return pWin;
}

void CQLayoutsWidget::slotShowLayout(const QModelIndex &index)
{
  int row = index.row();
  assert(mpDataModel != NULL);
  CListOfLayouts *pListOfLayouts = mpDataModel->getListOfLayouts();
  CLayout *pLayout = &pListOfLayouts->operator[](row);
  std::string Key = pLayout->getKey();

  if (pLayout != NULL)
    {
      // check if we already have a widget for the layout
      // if yes, open it, else create one and add it to the map
      LayoutWindow *pLayoutWindow = NULL;
      LayoutWindowMap::iterator pos = mLayoutWindowMap.find(Key);

      if (pos != mLayoutWindowMap.end())
        {
          pLayoutWindow = pos->second;
        }

      if (pLayoutWindow == NULL)
        {
          pLayoutWindow = createLayoutWindow(row, pLayout);
          // need to add it to the list, so the window can be deleted later
          mLayoutWindowMap[pLayout->getKey()] = pLayoutWindow;
        }

      if (pLayoutWindow != NULL)
        {
#if WITH_LEGACY_OPENGL
          CQNewMainWindow *cqWin = dynamic_cast<CQNewMainWindow *>(pLayoutWindow);

          if (cqWin != NULL)
            {
              cqWin ->slotLayoutChanged(row);
              cqWin ->setMode();
            }

#endif

          pLayoutWindow->show();
          pLayoutWindow->showNormal();
          pLayoutWindow->activateWindow();
          pLayoutWindow->addToMainWindow();
        }
    }
  else
    {
      //std::cerr << "Could not find layout." << std::endl;
    }
}
