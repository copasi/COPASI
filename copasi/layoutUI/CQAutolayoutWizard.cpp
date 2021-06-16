// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQAutolayoutWizard.h"

#include <QCheckBox>
#include <QFrame>
#include <QLabel>
#include <QtCore/QList>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QStringList>

#include <assert.h>
#include <map>

#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor which in addition to the attributes of the original class
 * also takes a string which is the key of the object that is represented
 * by the item.
 */
CQModelElementTreeWidgetItem::CQModelElementTreeWidgetItem(const QStringList & strings, const std::string& key, int type) :
  QTreeWidgetItem(strings, type)
  , mKey(key)
{
}

/**
 * Returns a const reference to the key of the object.
 */
const std::string& CQModelElementTreeWidgetItem::getKey() const
{
  return this->mKey;
}

/**
 * Returns a pointer to the COPASI object
 * represented by this item.
 */
CDataObject* CQModelElementTreeWidgetItem::getObject() const
{
  CDataObject* pObject = NULL;

  if (!this->mKey.empty())
    {
      pObject = CRootContainer::getKeyFactory()->get(this->mKey);
    }

  return pObject;
}

// Error dialog if nothing has been selected int the tree

CQNoSelectionErrorWizardPage::CQNoSelectionErrorWizardPage():
  QWizardPage()
{
  this->setTitle(tr("No selection Error"));
  QVBoxLayout* pLayout = new QVBoxLayout;
  this->setLayout(pLayout);
  QLabel* pLabel = new QLabel("<font color='red'>Please go back to the selection page and select some model elements for which to create a layout.</font>");
  QFont font = pLabel->font();
  font.setBold(true);
  font.setPointSize(font.pointSize() * 2);
  pLabel->setFont(font);
  pLabel->setWordWrap(true);
  pLayout->addWidget(pLabel);
}

bool CQNoSelectionErrorWizardPage::isComplete() const
{
  return false;
}

// Selection Page

CQSelectionWizardPage::CQSelectionWizardPage(const CModel& model) :
  QWizardPage()
  , mCreateCompartmentElements(false)
  , mpSelectionTree(new QTreeWidget)
  , mpCompartmentsItem(new QTreeWidgetItem((QTreeWidget*)NULL, QStringList(QString(tr("Compartments")))))
  , mpReactionsItem(new QTreeWidgetItem((QTreeWidget*)NULL, QStringList(QString(tr("Reactions")))))
{
  this->setTitle(tr("Model Element Selection"));
  this->setSubTitle("Please select the model elements for which you want to create layout elements.\nPlease Note the the \"All ...\" elements only turn their immediate children on or off.");
  QVBoxLayout* pLayout = new QVBoxLayout;
  this->setLayout(pLayout);
  pLayout->addWidget(this->mpSelectionTree);
  this->fillTree(model);
  QCheckBox* pCheckBox = new QCheckBox("create compartment elements");
  pCheckBox->setChecked(false);
  connect(pCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotCreateCompartments(int)));
  pLayout->addWidget(pCheckBox);
  this->mpSelectionTree->setColumnCount(1);
  this->mpSelectionTree->setHeaderLabel(tr("Elements"));
  // add a top level element for the compartments
  // add a top level element for the reactions
  QList<QTreeWidgetItem*> items;
  items.append(this->mpCompartmentsItem);
  items.append(this->mpReactionsItem);
  this->mpSelectionTree->insertTopLevelItems(0, items);
  connect(this->mpSelectionTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(slotItemChanged(QTreeWidgetItem*, int)));
}

void CQSelectionWizardPage::slotItemChanged(QTreeWidgetItem* pItem, int /*column*/)
{
  disconnect(this->mpSelectionTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(slotItemChanged(QTreeWidgetItem*, int)));
  QTreeWidgetItem* pParent = pItem->parent();
  assert(pParent != NULL);
  bool found = false;

  if (this->mpCompartmentsItem->childCount() > 0)
    {
      // check if it was the "All compartments" entry
      QTreeWidgetItem* pChild = this->mpCompartmentsItem->child(0);

      if (pItem == pChild)
        {
          // we have to select or deselect all immediate children
          found = true;
          unsigned int i = 0, iMax = pItem->childCount();
          Qt::CheckState state = pItem->checkState(0);

          while (i < iMax)
            {
              pItem->child(i)->setCheckState(0, state);
              ++i;
            }
        }
      else
        {
          // check if it was one of the compartments entries
          // the "All metabolite" entry, or one of the metabolites
          int i = 0, iMax = pChild->childCount();
          QTreeWidgetItem* pAll = NULL;

          while (i < iMax && !found)
            {
              if (pItem == pChild->child(i))
                {
                  // it is a compartment node
                  // , we might have to change the state of the parent
                  found = true;
                  unsigned int j = 0, jMax = pParent->childCount();
                  bool allSelected = true;
                  bool allUnselected = true;

                  while (j < jMax && (allSelected == true || allUnselected == true))
                    {
                      if (pParent->child(j)->checkState(0) == Qt::Checked)
                        {
                          allUnselected = false;
                        }
                      else if (pParent->child(j)->checkState(0) == Qt::Unchecked)
                        {
                          allSelected = false;
                        }
                      else
                        {
                          allSelected = false;
                          allUnselected = false;
                        }

                      ++j;
                    }

                  if (allSelected == true)
                    {
                      pParent->setCheckState(0, Qt::Checked);
                    }
                  else if (allUnselected == true)
                    {
                      pParent->setCheckState(0, Qt::Unchecked);
                    }
                  else
                    {
                      pParent->setCheckState(0, Qt::PartiallyChecked);
                    }
                }
              else
                {
                  pAll = pChild->child(i)->child(0);

                  if (pAll != NULL)
                    {
                      if (pItem == pAll)
                        {
                          // we have to select or deselect all immediate children
                          found = true;
                          unsigned int j = 0, jMax = pItem->childCount();
                          Qt::CheckState state = pItem->checkState(0);

                          while (j < jMax)
                            {
                              pItem->child(j)->setCheckState(0, state);
                              ++j;
                            }
                        }
                      else if (pAll == pParent)
                        {
                          found = true;
                          // a metabolites selection status has changed
                          // we have to change the state of the parent
                          unsigned int j = 0, jMax = pParent->childCount();
                          bool allSelected = true;
                          bool allUnselected = true;

                          while (j < jMax && (allSelected == true || allUnselected == true))
                            {
                              if (pParent->child(j)->checkState(0) == Qt::Checked)
                                {
                                  allUnselected = false;
                                }
                              else if (pParent->child(j)->checkState(0) == Qt::Unchecked)
                                {
                                  allSelected = false;
                                }
                              else
                                {
                                  allSelected = false;
                                  allUnselected = false;
                                }

                              ++j;
                            }

                          if (allSelected == true)
                            {
                              pParent->setCheckState(0, Qt::Checked);
                            }
                          else if (allUnselected == true)
                            {
                              pParent->setCheckState(0, Qt::Unchecked);
                            }
                          else
                            {
                              pParent->setCheckState(0, Qt::PartiallyChecked);
                            }
                        }
                    }
                }

              ++i;
            }
        }
    }

  if (!found && this->mpReactionsItem->childCount() > 0)
    {
      // check if it was the "All reactions" entry
      QTreeWidgetItem* pChild = this->mpReactionsItem->child(0);

      if (pItem == pChild)
        {
          // we have to select or deselect all immediate children
          found = true;
          unsigned int j = 0, jMax = pItem->childCount();
          Qt::CheckState state = pItem->checkState(0);

          while (j < jMax)
            {
              pItem->child(j)->setCheckState(0, state);
              ++j;
            }
        }
      else
        {
          // check if it was one of the reaction entries
          int i = 0, iMax = pChild->childCount();

          while (i < iMax && !found)
            {
              if (pItem == pChild->child(i))
                {
                  found = true;
                  // it is a reaction node
                  // , we might have to change the state of the parent
                  unsigned int j = 0, jMax = pParent->childCount();
                  bool allSelected = true;
                  bool allUnselected = true;

                  while (j < jMax && (allSelected == true || allUnselected == true))
                    {
                      if (pParent->child(j)->checkState(0) == Qt::Checked)
                        {
                          allUnselected = false;
                        }
                      else if (pParent->child(j)->checkState(0) == Qt::Unchecked)
                        {
                          allSelected = false;
                        }
                      else
                        {
                          allSelected = false;
                          allUnselected = false;
                        }

                      ++j;
                    }

                  if (allSelected == true)
                    {
                      pParent->setCheckState(0, Qt::Checked);
                    }
                  else if (allUnselected == true)
                    {
                      pParent->setCheckState(0, Qt::Unchecked);
                    }
                  else
                    {
                      pParent->setCheckState(0, Qt::PartiallyChecked);
                    }
                }

              ++i;
            }
        }
    }

  assert(found == true);
  connect(this->mpSelectionTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(slotItemChanged(QTreeWidgetItem*, int)));
}

// is called when the state of the compartment layout creation checkbox changes
void CQSelectionWizardPage::slotCreateCompartments(int state)
{
  // set the flags on the compartment items and the All items in compartments
  // to be checkable but leave them unchecked
  disconnect(this->mpSelectionTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(slotItemChanged(QTreeWidgetItem*, int)));

  if (state == Qt::Checked)
    {
      this->mCreateCompartmentElements = true;
      QTreeWidgetItem* pItem = this->mpCompartmentsItem->child(0);

      if (pItem != NULL)
        {
          pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
          pItem->setCheckState(0, Qt::Unchecked);
          // now we do the same on all the children of this item
          unsigned int i = 0, iMax = pItem->childCount();

          while (i < iMax)
            {
              pItem->child(i)->setFlags(pItem->child(i)->flags() | Qt::ItemIsUserCheckable);
              pItem->child(i)->setCheckState(0, Qt::Unchecked);
              ++i;
            }
        }
    }
  else
    {
      this->mCreateCompartmentElements = false;
      this->mpCompartmentsItem->setFlags(this->mpCompartmentsItem->flags() & (~Qt::ItemIsUserCheckable));
      this->mpCompartmentsItem->setData(0, Qt::CheckStateRole, QVariant());
      QTreeWidgetItem* pItem = this->mpCompartmentsItem->child(0);

      if (pItem != NULL)
        {
          pItem->setFlags(pItem->flags() & (~Qt::ItemIsUserCheckable));
          pItem->setData(0, Qt::CheckStateRole, QVariant());
          // now we do the same on all the children of this item
          unsigned int i = 0, iMax = pItem->childCount();

          while (i < iMax)
            {
              pItem->child(i)->setFlags(pItem->child(i)->flags() & (~Qt::ItemIsUserCheckable));
              pItem->child(i)->setData(0, Qt::CheckStateRole, QVariant());
              ++i;
            }
        }
    }

  connect(this->mpSelectionTree, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(slotItemChanged(QTreeWidgetItem*, int)));
}

// fills the selection tree with elements from the model
void CQSelectionWizardPage::fillTree(const CModel& model)
{
  const CDataVectorNS < CCompartment >& compartments = model.getCompartments();
  const CDataVector< CMetab >& metabs = model.getMetabolites();
  const CDataVectorNS < CReaction >& reactions = model.getReactions();

  if (compartments.size() > 0 && metabs.size() > 0)
    {
      // make all items checkable but the ones for the compartments
      // and the ones for All compartments
      // check all checkable items

      // add the compartments
      // first we have to add two items to the top level items that we can use to
      // specify that we want to select all children in a list
      QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList(QString(tr("All Compartments"))));
      pItem->setFlags(pItem->flags() & (!Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
      this->mpCompartmentsItem->addChild(pItem);
      // add all compartments to the item
      QList<QTreeWidgetItem*> children, children2;
      size_t i = 0, iMax = compartments.size();
      QTreeWidgetItem *pChild1;
      const CCompartment* pCompartment = NULL;
      QTreeWidgetItem *pItem2 = NULL, *pItem3 = NULL;
      const CDataVectorNS<CMetab>* pMetabs = NULL;
      unsigned int j, jMax;
      const CMetab* pMetab = NULL;

      while (i < iMax)
        {
          pCompartment = &compartments[i];
          assert(pCompartment != NULL);
          pChild1 = new CQModelElementTreeWidgetItem(QStringList(QString(pCompartment->getObjectDisplayName().c_str())), pCompartment->getKey());
          pChild1->setFlags(pChild1->flags() & (!Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
          // add an item to select all children
          pMetabs = &pCompartment->getMetabolites();
          assert(pMetabs != NULL);

          if (pMetabs->size() > 0)
            {
              pItem2 = new QTreeWidgetItem(QStringList(QString(tr("All Metabolites in Compartment"))));
              pItem2->setFlags(pItem2->flags() | (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
              pItem2->setCheckState(0, Qt::Checked);
              pChild1->addChild(pItem2);
              // now we add all metabolites
              j = 0;
              jMax = pMetabs->size();

              while (j < jMax)
                {
                  pMetab = &pMetabs->operator[](j);
                  assert(pMetab != NULL);
                  pItem3 = new CQModelElementTreeWidgetItem(QStringList(QString(pMetab->getObjectDisplayName().c_str())), pMetab->getKey());
                  pItem3->setFlags(pItem3->flags() | (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
                  pItem3->setCheckState(0, Qt::Checked);
                  children2.append(pItem3);
                  ++j;
                }

              pItem2->addChildren(children2);
              children2.clear();
            }

          children.append(pChild1);
          ++i;
        }

      pItem->addChildren(children);

      if (reactions.size() > 0)
        {
          // top level item to select all reactions
          pItem = new QTreeWidgetItem(QStringList(QString(tr("All Reactions"))));
          pItem->setFlags(pItem->flags() | (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
          pItem->setCheckState(0, Qt::Checked);
          this->mpReactionsItem->addChild(pItem);
          // now we add all reactions
          i = 0;
          iMax = reactions.size();
          const CReaction* pReaction = NULL;

          while (i < iMax)
            {
              pReaction = &reactions[i];
              assert(pReaction != NULL);
              pChild1 = new CQModelElementTreeWidgetItem(QStringList(QString(pReaction->getObjectDisplayName().c_str())), pReaction->getKey());
              pChild1->setFlags(pChild1->flags() | (Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
              pChild1->setCheckState(0, Qt::Checked);
              // TODO add the substrates and products to the reactions
              children2.append(pChild1);
              ++i;
            }

          pItem->addChildren(children2);
        }
    }
}

/**
 * Checks which elements have been selected in the tree
 * and fills the containers that are passed in with those
 * elements.
 */
void CQSelectionWizardPage::fillContainers(std::set<const CCompartment*>& compartments, std::set<const CReaction*>& reactions, std::set<const CMetab*>& species) const
{
  // clear all containers
  compartments.clear();
  reactions.clear();
  species.clear();

  if (this->mpCompartmentsItem->childCount() > 0)
    {
      QTreeWidgetItem* pItem = this->mpCompartmentsItem->child(0);
      unsigned int i = 0, iMax = pItem->childCount();
      unsigned int j, jMax;
      const CMetab* pMetab = NULL;
      QTreeWidgetItem *pItem2 = NULL, *pChild = NULL, *pChild2 = NULL;
      const CCompartment* pCompartment = NULL;
      CQModelElementTreeWidgetItem* pModelItem = NULL;

      while (i < iMax)
        {
          pChild = pItem->child(i);
          assert(pChild != NULL);

          if ((pChild->flags() & Qt::ItemIsUserCheckable) && pChild->checkState(0) == Qt::Checked)
            {
              pModelItem = dynamic_cast<CQModelElementTreeWidgetItem*>(pItem->child(i));
              assert(pModelItem != NULL);
              pCompartment = dynamic_cast<const CCompartment*>(pModelItem->getObject());
              assert(pCompartment != NULL);
              compartments.insert(pCompartment);
            }

          pItem2 = pChild->child(0);

          // get the All species item
          if (pItem2 == NULL)
            {
              ++i;
              continue;
            }

          j = 0;
          jMax = pItem2->childCount();

          while (j < jMax)
            {
              pChild2 = pItem2->child(j);

              if ((pChild2->flags() & Qt::ItemIsUserCheckable) && pChild2->checkState(0) == Qt::Checked)
                {
                  pModelItem = dynamic_cast<CQModelElementTreeWidgetItem*>(pItem2->child(j));
                  assert(pModelItem != NULL);
                  pMetab = dynamic_cast<const CMetab*>(pModelItem->getObject());
                  assert(pMetab != NULL);
                  species.insert(pMetab);
                }

              ++j;
            }

          ++i;
        }

      // now we add the reactions
    }

  if (this->mpReactionsItem->childCount() > 0)
    {
      // there should be only one child (All reactions)
      assert(this->mpReactionsItem->childCount() == 1);
      QTreeWidgetItem* pItem = this->mpReactionsItem->child(0), *pChild = NULL;
      CQModelElementTreeWidgetItem* pModelItem = NULL;
      unsigned int i = 0, iMax;
      iMax = pItem->childCount();
      const CReaction* pReaction = NULL;

      while (i < iMax)
        {
          pChild = pItem->child(i);

          if ((pChild->flags() & Qt::ItemIsUserCheckable) && pChild->checkState(0) == Qt::Checked)
            {
              pModelItem = dynamic_cast<CQModelElementTreeWidgetItem*>(pChild);
              assert(pModelItem != NULL);
              pReaction = dynamic_cast<const CReaction*>(pModelItem->getObject());
              assert(pReaction != NULL);
              reactions.insert(pReaction);
            }

          ++i;
        }
    }
}

// this is the page where one can select the side compounds
// constructor which takes a string that is displayed for the item
// and the key of a model object
CQSideCompoundWizardPage::CQListWidgetModelItem::CQListWidgetModelItem(const QString& text, const std::string& key):
  QListWidgetItem(text)
  , mKey(key)
{
}

// returns the key of the associated model object
const std::string& CQSideCompoundWizardPage::CQListWidgetModelItem::getKey() const
{
  return this->mKey;
}

CDataObject* CQSideCompoundWizardPage::CQListWidgetModelItem::getObject() const
{
  CDataObject* pObject = NULL;

  if (!this->mKey.empty())
    {
      pObject = CRootContainer::getKeyFactory()->get(this->mKey);
    }

  return pObject;
}

// default constructor
CQSideCompoundWizardPage::CQSideCompoundWizardPage() :
  QWizardPage()
  , mpSpeciesList(new QListWidget)
  , mpSideCompoundList(new QListWidget)
  , mpAddButton(new QPushButton(">>"))
  , mpRemoveButton(new QPushButton("<<"))
{
  this->setTitle("Side Compounds");
  this->setSubTitle("Please select the species that you want to be considered as side compounds in the layout.\n\nSide compounds can be duplicated for each reaction they occur in and they might be treated differently by the layout algorithm.");
  // the page should contain two lists
  // and the user can push elements back and forth
  // between the lists
  this->mpSpeciesList->setSelectionMode(QAbstractItemView::ExtendedSelection);
  this->mpSideCompoundList->setSelectionMode(QAbstractItemView::ExtendedSelection);
  QHBoxLayout* pLayout = new QHBoxLayout;
  this->setLayout(pLayout);
  QFrame* pFrame = new QFrame;
  QVBoxLayout* pLayout2 = new QVBoxLayout;
  pFrame->setLayout(pLayout2);
  pLayout2->addWidget(new QLabel("Species"));
  pLayout2->addWidget(this->mpSpeciesList);
  pLayout->addWidget(pFrame);
  pLayout2 = new QVBoxLayout;
  pFrame = new QFrame;
  pFrame->setLayout(pLayout2);
  pLayout2->addStretch();
  this->mpAddButton->setEnabled(false);
  this->mpRemoveButton->setEnabled(false);
  pLayout2->addWidget(this->mpAddButton);
  pLayout2->addSpacing(20);
  pLayout2->addWidget(this->mpRemoveButton);
  pLayout2->addStretch();
  pLayout->addWidget(pFrame);
  pFrame = new QFrame;
  pLayout2 = new QVBoxLayout;
  pFrame->setLayout(pLayout2);
  pLayout2->addWidget(new QLabel("Side-Species"));
  pLayout2->addWidget(this->mpSideCompoundList);
  pLayout->addWidget(pFrame);
  connect(this->mpAddButton, SIGNAL(clicked()), this, SLOT(slotAddButtonClicked()));
  connect(this->mpRemoveButton, SIGNAL(clicked()), this, SLOT(slotRemoveButtonClicked()));
  connect(this->mpSpeciesList, SIGNAL(itemSelectionChanged()), this, SLOT(slotSpeciesSelectionChanged()));
  connect(this->mpSideCompoundList, SIGNAL(itemSelectionChanged()), this, SLOT(slotSideCompoundSelectionChanged()));
}

bool CQSideCompoundWizardPage::alphaSorter::operator()(const CMetab* pM1, const CMetab* pM2) const
{
  return (pM1->getObjectDisplayName() < pM2->getObjectDisplayName());
}

/**
 * Fills the given set with the side compounds that
 * have been selected by the user.
 */
void CQSideCompoundWizardPage::getSideCompounds(std::set<const CMetab*>& sideCompounds) const
{
  sideCompounds.clear();
  unsigned int i, iMax = this->mpSideCompoundList->count();
  const CQListWidgetModelItem* pItem = NULL;
  const CMetab* pMetab = NULL;

  for (i = 0; i < iMax; ++i)
    {
      pItem = dynamic_cast<const CQListWidgetModelItem*>(this->mpSideCompoundList->item(i));
      assert(pItem != NULL);
      pMetab = dynamic_cast<const CMetab*>(pItem->getObject());
      sideCompounds.insert(pMetab);
    }
}

/**
 * Passes the species that have been selected by the user
 * for use in the layout to the page.
 * These species are used to fill the list on the left.
 */
void CQSideCompoundWizardPage::setSpeciesList(const std::set<const CMetab*>& metabs)
{
  this->mSortedSpecies.clear();
  this->mSortedSpecies.insert(metabs.begin(), metabs.end());
  std::set<std::string> keys;

  this->mpSpeciesList->clear();
  std::set<const CMetab*, alphaSorter>::const_iterator it = this->mSortedSpecies.begin(), endit = this->mSortedSpecies.end();
  QList<QListWidgetItem*> itemList;
  int i, iMax;

  while (it != endit)
    {
      std::string displayName = (*it)->getObjectDisplayName();
      keys.insert((*it)->getKey());
      // if the item is already marked as a side compound, we don't
      // have to add it to the species list
      itemList = this->mpSideCompoundList->findItems(displayName.c_str(), Qt::MatchExactly);
      i = 0;
      iMax = itemList.size();
      bool found = false;

      while (i < iMax)
        {
          if (static_cast<const CQListWidgetModelItem*>(itemList[i])->getKey() == (*it)->getKey())
            {
              found = true;
            }

          ++i;
        }

      if (found == false)
        {
          // the item is not a side compound, so we add it to the species list
          this->mpSpeciesList->addItem(new CQListWidgetModelItem(displayName.c_str(), (*it)->getKey()));
        }

      ++it;
    }

  // now we have to go through the side compounds again and check
  // if all the names that are in there are also in the sorted name list
  // If not, we have to delete the item from the side compounds
  iMax = this->mpSideCompoundList->count() - 1;
  std::set<std::string>::const_iterator end = keys.end();
  QListWidgetItem* pItem = NULL;

  while (iMax > 0)
    {
      if (keys.find(static_cast<const CQListWidgetModelItem*>(this->mpSideCompoundList->item(iMax))->getKey()) == end)
        {
          pItem = this->mpSideCompoundList->takeItem(iMax);

          if (pItem != NULL)
            {
              delete pItem;
            }
        }

      --iMax;
    }
}

// called when the add button was clicked
void CQSideCompoundWizardPage::slotAddButtonClicked()
{
  // move the selected items from the species list to the side compound list
  QList<QListWidgetItem*> selection = this->mpSpeciesList->selectedItems();
  //  insert the items into the side compound list in the correct order
  //  and remove them from the species list
  //  the items should be selected in the side compound list
  int index = 0;
  QList<QListWidgetItem*>::iterator it = selection.begin(), endit = selection.end();

  while (it != endit)
    {
      while (index < this->mpSideCompoundList->count() && static_cast<CQListWidgetModelItem*>(this->mpSideCompoundList->item(index))->getObject()->getObjectDisplayName() < static_cast<CQListWidgetModelItem*>(*it)->getObject()->getObjectDisplayName())
        {
          ++index;
        }

      if (index == this->mpSideCompoundList->count())
        {
          // we add all items at the end
          while (it != endit)
            {
              this->mpSpeciesList->takeItem(this->mpSpeciesList->row(*it));
              this->mpSideCompoundList->addItem((*it));
              ++it;
            }
        }

      // now we insert items until the item is not at the right place
      while (it != endit && static_cast<CQListWidgetModelItem*>(this->mpSideCompoundList->item(index))->getObject()->getObjectDisplayName() > static_cast<CQListWidgetModelItem*>(*it)->getObject()->getObjectDisplayName())
        {
          this->mpSpeciesList->takeItem(this->mpSpeciesList->row(*it));
          this->mpSideCompoundList->insertItem(index, *it);
          ++it;
        }
    }

  // TODO set the newly added items as selected
  // TODO disconnect and reconnect the slot that listend to the selection change
  // TODO and emit the signal after changing the selection
  this->mpSpeciesList->update();
}

// called when the remove button was clicked
void CQSideCompoundWizardPage::slotRemoveButtonClicked()
{
  // move the selected items from the side compound list to the species list
  QList<QListWidgetItem*> selection = this->mpSideCompoundList->selectedItems();
  // insert the items into the species list in the correct order
  // and remove them from the side compound list
  // the items should be selected in the species list
  QList<QListWidgetItem*>::iterator it = selection.begin(), endit = selection.end();
  int index = 0;

  while (it != endit)
    {
      while (index < this->mpSpeciesList->count() && static_cast<CQListWidgetModelItem*>(this->mpSpeciesList->item(index))->getObject()->getObjectDisplayName() < static_cast<CQListWidgetModelItem*>(*it)->getObject()->getObjectDisplayName())
        {
          ++index;
        }

      if (index == this->mpSpeciesList->count())
        {
          // we add all items at the end
          while (it != endit)
            {
              this->mpSideCompoundList->takeItem(this->mpSideCompoundList->row(*it));
              this->mpSpeciesList->addItem((*it));
              ++it;
            }

          break;
        }

      // now we insert items until the item is not at the right place
      while (it != endit && static_cast<CQListWidgetModelItem*>(this->mpSpeciesList->item(index))->getObject()->getObjectDisplayName() > static_cast<CQListWidgetModelItem*>(*it)->getObject()->getObjectDisplayName())
        {
          this->mpSideCompoundList->takeItem(this->mpSideCompoundList->row(*it));
          this->mpSpeciesList->insertItem(index, *it);
          ++it;
        }
    }

  // TODO set the newly added items as selected
  // TODO disconnect and reconnect the slot that listend to the selection change
  // TODO and emit the signal after changing the selection
  this->mpSideCompoundList->update();
}

// called when the selection in the species list changes
void CQSideCompoundWizardPage::slotSpeciesSelectionChanged()
{
  // if something is selected
  // delete the selection in the side compound list
  // if nothing is selected deactive the add button, else active the add
  // button
  QList<QListWidgetItem*> selection = this->mpSpeciesList->selectedItems();

  if (selection.size() == 0)
    {
      this->mpAddButton->setEnabled(false);
    }
  else
    {
      this->mpAddButton->setEnabled(true);
      this->mpSideCompoundList->clearSelection();
    }
}

// called when the side compounds selection changes
void CQSideCompoundWizardPage::slotSideCompoundSelectionChanged()
{
  // if something is selected, delete the selection in the
  // species list and active the remove button
  // else deactivate the remove button
  QList<QListWidgetItem*> selection = this->mpSideCompoundList->selectedItems();

  if (selection.size() == 0)
    {
      this->mpRemoveButton->setEnabled(false);
    }
  else
    {
      this->mpRemoveButton->setEnabled(true);
      this->mpSpeciesList->clearSelection();
    }
}

// Now comes the wizard itself

/**
 * Constructor needs a const reference to
 * a COPASI model.
 */
CQAutolayoutWizard::CQAutolayoutWizard(const CModel& model, QWidget * parent , Qt::WindowFlags flags):
  QWizard(parent, flags)
  , mModel(model)
  , mLastPageId(CQAutolayoutWizard::NO_PAGE)
{
  this->setOptions(this->options() | QWizard::HaveFinishButtonOnEarlyPages);
  this->setOptions(this->options() & ~QWizard::NoCancelButton);
  this->setWindowTitle(tr("Autolayout Wizard"));
  this->setPage(SELECTION_PAGE_ID, this->createSelectionPage());
  this->setPage(NO_SELECTION_ERROR_PAGE_ID, this->createErrorPage());
  this->setPage(SIDE_COMPOUND_PAGE_ID, this->createSideCompoundPage());
  //this->setPage(LAYOUT_PARAMETER_PAGE_ID,this->createLayoutParameterPage());
  connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotCurrentIdChanged(int)));
}

// Destructor
CQAutolayoutWizard::~CQAutolayoutWizard()
{
  // do nothing
}

// creates the first page for the wizard
// This is the page where the user selects the model elements
QWizardPage* CQAutolayoutWizard::createSelectionPage()
{
  return new CQSelectionWizardPage(this->mModel);
}

// creates the second page for the wizard
// here the user can decide if certain species should be
// treated as side components
QWizardPage* CQAutolayoutWizard::createSideCompoundPage()
{
  return new CQSideCompoundWizardPage;
}

// creates the third page for the wizard
// here the user can make settings for the layout
// algorithm
QWizardPage* CQAutolayoutWizard::createLayoutParameterPage()
{
  return new CQLayoutParametersWizardPage;
}

// creates the error page for the wizard
// where the user is asked to please select element for the layout
QWizardPage* CQAutolayoutWizard::createErrorPage()
{
  return new CQNoSelectionErrorWizardPage;
}

void CQAutolayoutWizard::done(int result)
{
  // depending on the result, I have to update
  // the selections
  if (result == QDialog::Accepted)
    {
      // right now, the dialog can only be ended on the second page,
      // so in theory we only have to update the side compounds
      // But I would like to change the wizard so that the user is
      // not forced to go through all pages and that he can close the
      // wizard at each step
      if (this->currentId() == CQAutolayoutWizard::SELECTION_PAGE_ID)
        {
          static_cast<CQSelectionWizardPage*>(this->currentPage())->fillContainers(this->mCompartments, this->mReactions, this->mSpecies);
        }
      else if (this->currentId() == CQAutolayoutWizard::SIDE_COMPOUND_PAGE_ID)
        {
          static_cast<CQSideCompoundWizardPage*>(this->currentPage())->getSideCompounds(this->mSideSpecies);
        }
      else if (this->currentId() == CQAutolayoutWizard::LAYOUT_PARAMETER_PAGE_ID)
        {
          // do nothing right now
        }

      // make sure that the side species container does not contain
      // any species that is not in the species container
      std::set<const CMetab*>::iterator it = this->mSideSpecies.begin(), endit = this->mSideSpecies.end(), speciesEnd = this->mSpecies.end();

      while (it != endit)
        {
          if (this->mSpecies.find(*it) == speciesEnd)
            {
              // remove the item from the side species
              // this is not very efficient, but should be ok since this code
              // is probably not critical
              this->mSideSpecies.erase(*it);
              // back to start
              it = this->mSideSpecies.begin();
              endit = this->mSideSpecies.end();
              continue;
            }

          ++it;
        }
    }
  else
    {
      this->mCompartments.clear();
      this->mReactions.clear();
      this->mSpecies.clear();
      this->mSideSpecies.clear();
    }

  this->QWizard::done(result);
}

void CQAutolayoutWizard::slotCurrentIdChanged(int id)
{
  // if the last id was the id of the selection widget, we
  // have to store the selection data
  if (this->mLastPageId == CQAutolayoutWizard::SELECTION_PAGE_ID)
    {
      // this is now done in the nextId method
      //static_cast<CQSelectionWizardPage*>(this->page(CQAutolayoutWizard::SELECTION_PAGE_ID))->fillContainers(this->mCompartments,this->mReactions,this->mSpecies);
    }
  // if the last id is that of the side compound page,
  // we have to save the side compounds
  else if (this->mLastPageId == CQAutolayoutWizard::SIDE_COMPOUND_PAGE_ID)
    {
      static_cast<CQSideCompoundWizardPage*>(this->page(CQAutolayoutWizard::SIDE_COMPOUND_PAGE_ID))->getSideCompounds(this->mSideSpecies);
    }

  // if we are in the side compound page,
  // we have to update the species
  if (id == CQAutolayoutWizard::SIDE_COMPOUND_PAGE_ID)
    {
      static_cast<CQSideCompoundWizardPage*>(this->page(CQAutolayoutWizard::SIDE_COMPOUND_PAGE_ID))->setSpeciesList(this->mSpecies);
    }

  this->mLastPageId = (PageOrder)id;
}

int CQAutolayoutWizard::nextId() const
{
  PageOrder nextPage = NO_PAGE;

  switch (this->currentId())
    {
      case SELECTION_PAGE_ID:
        static_cast<CQSelectionWizardPage*>(this->currentPage())->fillContainers(this->mCompartments, this->mReactions, this->mSpecies);

        if (this->mCompartments.empty() && this->mSpecies.empty())
          {
            nextPage = NO_SELECTION_ERROR_PAGE_ID;
          }
        else
          {
            nextPage = SIDE_COMPOUND_PAGE_ID;
          }

        break;

      case NO_SELECTION_ERROR_PAGE_ID:
        break;

      case SIDE_COMPOUND_PAGE_ID:
        //nextPage=LAYOUT_PARAMETER_PAGE_ID;
        break;

      case LAYOUT_PARAMETER_PAGE_ID:
        break;
    }

  return nextPage;
}
