// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionsWidget.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/03/16 14:52:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

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

  //Create Data Models for the 4 tables
  mpReactionDM = new CQReactionDM(this);

  mpTblReactions->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

  // Connect the table widget
  connect(mpReactionDM, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQReactionsWidget::~CQReactionsWidget()
{
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

  int delRow = mpTblReactions->selectionModel()->selectedIndexes().value(0).row();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  QString reactionList = "Are you sure you want to delete listed REACTION(S) ?\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedMetabList = "Following SPECIES reference above REACTION(S) and will be deleted -\n";
  QString effectedReacList = "Following REACTION(S) reference above REACTION(S) and will be deleted -\n";
  QString effectedValueList = "Following MODEL VALUE(S) reference above REACTION(S) and will be deleted -\n";

  bool compartmentFound = false;
  bool metabFound = false;
  bool reacFound = false;
  bool valueFound = false;

  CReaction * pReaction = pModel->getReactions()[delRow];

  reactionList.append(FROM_UTF8(pReaction->getObjectName()));
  reactionList.append(", ");

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(pReaction->getDeletedObjects(),
                                      Reactions, Metabolites, Compartments, Values);

  if (Reactions.size() > 0)
    {
      reacFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();

      for (it = Reactions.begin(); it != itEnd; ++it)
        {
          effectedReacList.append(FROM_UTF8((*it)->getObjectName()));
          effectedReacList.append(", ");
        }

      effectedReacList.remove(effectedReacList.length() - 2, 2);
      effectedReacList.append("  ---> ");
      effectedReacList.append(FROM_UTF8(pReaction->getObjectName()));
      effectedReacList.append("\n");
    }

  if (Metabolites.size() > 0)
    {
      metabFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();

      for (it = Metabolites.begin(); it != itEnd; ++it)
        {
          effectedMetabList.append(FROM_UTF8((*it)->getObjectName()));
          effectedMetabList.append(", ");
        }

      effectedMetabList.remove(effectedMetabList.length() - 2, 2);
      effectedMetabList.append("  ---> ");
      effectedMetabList.append(FROM_UTF8(pReaction->getObjectName()));
      effectedMetabList.append("\n");
    }

  if (Values.size() > 0)
    {
      valueFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();

      for (it = Values.begin(); it != itEnd; ++it)
        {
          effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
          effectedValueList.append(", ");
        }

      effectedValueList.remove(effectedValueList.length() - 2, 2);
      effectedValueList.append("  ---> ");
      effectedValueList.append(FROM_UTF8(pReaction->getObjectName()));
      effectedValueList.append("\n");
    }

  if (Compartments.size() > 0)
    {
      compartmentFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();

      for (it = Compartments.begin(); it != itEnd; ++it)
        {
          effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
          effectedCompartmentList.append(", ");
        }

      effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
      effectedCompartmentList.append("  ---> ");
      effectedCompartmentList.append(FROM_UTF8(pReaction->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  reactionList.remove(reactionList.length() - 2, 2);

  QString msg = reactionList;

  if (compartmentFound)
    {
      msg.append("\n \n");
      msg.append(effectedCompartmentList);
    }

  if (metabFound)
    {
      msg.append("\n \n");
      msg.append(effectedMetabList);
    }

  if (reacFound)
    {
      msg.append("\n \n");
      msg.append(effectedReacList);
    }

  if (valueFound)
    {
      msg.append("\n \n");
      msg.append(effectedValueList);
    }

  C_INT32 choice = 0;
  //if (metabFound || reacFound || valueFound || compartmentFound)
  choice = CQMessageBox::question(this,
                                  "CONFIRM DELETE",
                                  msg,
                                  QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);

  if (choice == QMessageBox::Ok)
    {
      if (mpTblReactions->hasFocus())
        {
          mpReactionDM->removeRow(delRow);
          protectedNotify(ListViews::REACTION, ListViews::DELETE, "");
        }
    }
}

void CQReactionsWidget::slotBtnNewClicked()
{
  if (mpReactionDM->insertRow())
    {
      mpTblReactions->resizeColumnsToContents();
      protectedNotify(ListViews::REACTION, ListViews::ADD, "");;
    }
}

void CQReactionsWidget::slotBtnClearClicked()
{

  int ret = QMessageBox::question(this, tr("Confirm Delete"), "Delete all Reactions?",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (ret == QMessageBox::Yes)
    {mpReactionDM->clear();}
}

bool CQReactionsWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CQReactionsWidget::leave()
{
  mpReactionDM->removeLastRowIfEmpty();
  return true;
}

bool CQReactionsWidget::enter(const std::string & C_UNUSED(key))
{
  //Set Model for the TableView
  mpTblReactions->setModel(NULL);
  mpTblReactions->setModel(mpReactionDM);
  mpReactionDM->insertRow();
  mpTblReactions->resizeColumnsToContents();

  return true;
}

void CQReactionsWidget::dataChanged(const QModelIndex& topLeft,
                                    const QModelIndex& C_UNUSED(bottomRight))
{
  if (mpReactionDM == topLeft.model())
    {
      if (topLeft.row() == (mpReactionDM->rowCount() - 1))
        //If edit was done on last row, insert a new empty row.
        {
          mpReactionDM->insertRow();
          mpTblReactions->resizeColumnsToContents();
        }
    }

  protectedNotify(ListViews::REACTION, ListViews::CHANGE, "");
  protectedNotify(ListViews::MODEL, ListViews::CHANGE, "");
}

void CQReactionsWidget::slotDoubleClicked(const QModelIndex index)
{
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
