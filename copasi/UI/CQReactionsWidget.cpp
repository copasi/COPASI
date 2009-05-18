// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionsWidget.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/05/18 10:53:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <QHeaderView>

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
  mpProxyModel->setDynamicSortFilter(true);
  mpProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
  mpProxyModel->setFilterKeyColumn(COL_NAME_REACTIONS);

  mpTblReactions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblReactions->verticalHeader()->hide();

  setFramework(mFramework);

  // Connect the table widget
  connect(mpReactionDM, SIGNAL(notifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)),
          this, SLOT(slotNotifyGUI(ListViews::ObjectType, ListViews::Action, const std::string)));
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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQReactionsWidget::languageChange()
{
  retranslateUi(this);
}

void CQReactionsWidget::slotBtnDeleteClicked()
{
  if (mpTblReactions->hasFocus())
    {deleteSelectedReaction();}
}

void CQReactionsWidget::deleteSelectedReaction()
{
  if (mpTblReactions->selectionModel()->selectedIndexes().empty())
    {return;}

//  QModelIndex &i = mpProxyModel->mapToSource(mpTblReactions->selectionModel()->selectedIndexes().value(0));
  QModelIndex i = mpProxyModel->mapToSource(mpTblReactions->selectionModel()->selectedIndexes().value(0));
  int delRow = i.row();

  if (mpReactionDM->isDefaultRow(i))
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  CReaction * pReaction = pModel->getReactions()[delRow];

  if (pReaction == NULL)
    return;

  QMessageBox::StandardButton choice =
    CQMessageBox::confirmDelete(NULL, pModel, "reaction",
                                FROM_UTF8(pReaction->getObjectName()),
                                pReaction->getDeletedObjects());

  if (choice == QMessageBox::Ok)
    {
      if (mpTblReactions->hasFocus())
        {
          mpReactionDM->removeRow(delRow);
          protectedNotify(ListViews::REACTION, ListViews::DELETE, "");
        }
    }
}

void CQReactionsWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Reactions?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {
      mpReactionDM->clear();
      protectedNotify(ListViews::REACTION, ListViews::DELETE, "");
    }
}

bool CQReactionsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CQReactionsWidget::leave()
{
  return true;
}

bool CQReactionsWidget::enter(const std::string & C_UNUSED(key))
{
  mpProxyModel->setSourceModel(mpReactionDM);
  //Set Model for the TableView
  mpTblReactions->setModel(NULL);
  mpTblReactions->setModel(mpProxyModel);
  mpTblReactions->resizeColumnsToContents();
  setFramework(mFramework);

  return true;
}

void CQReactionsWidget::dataChanged(const QModelIndex& C_UNUSED(topLeft),
                                    const QModelIndex& C_UNUSED(bottomRight))
{
  mpTblReactions->resizeColumnsToContents();
  setFramework(mFramework);
}

void CQReactionsWidget::slotNotifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  protectedNotify(objectType, action, key);
}

void CQReactionsWidget::slotDoubleClicked(const QModelIndex proxyIndex)
{
  QModelIndex index = mpProxyModel->mapToSource(proxyIndex);

  if (mpReactionDM->isDefaultRow(index))
    return;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  std::string key = pModel->getReactions()[index.row()]->getKey();

  if (CCopasiRootContainer::getKeyFactory()->get(key))
    mpListView->switchToOtherWidget(0, key);
}

void CQReactionsWidget::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Delete)
    slotBtnDeleteClicked();
}

void CQReactionsWidget::slotFilterChanged()
{
  QRegExp regExp(mpLEFilter->text() + "|No Name", Qt::CaseInsensitive, QRegExp::RegExp);
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
