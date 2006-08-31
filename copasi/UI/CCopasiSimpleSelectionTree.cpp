/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/08/31 15:45:46 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CCopasiSimpleSelectionTree.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "utilities/CCopasiParameter.h"
#include "utilities/CCopasiParameterGroup.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObjectName.h"
#include "qtUtilities.h"

CCopasiSimpleSelectionTree::CCopasiSimpleSelectionTree(QWidget* parent, const char* name, WFlags fl): QListView(parent, name, fl), mpOutputVector(NULL)
{
  this->setSelectionMode(QListView::Extended);
  this->setSortColumn(-1);
  this->setRootIsDecorated(true);
  this->addColumn("");
  this->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, this->sizePolicy().hasHeightForWidth()));
  this->expertSubtree = new QListViewItem(this, "expert");

#ifdef COPASI_DEBUG
  this->matrixSubtree = new QListViewItem(this, "matrices");
#endif // COPASI_DEBUG

  this->modelValueSubtree = new QListViewItem(this, "global parameters");
  this->valueSubtree = new QListViewItem(this->modelValueSubtree, "transient values");
  this->initialValueSubtree = new QListViewItem(this->modelValueSubtree, "initial values");

  this->reactionSubtree = new QListViewItem(this, "reactions");
  this->particleFluxSubtree = new QListViewItem(this->reactionSubtree, "particle fluxes");
  this->concentrationFluxSubtree = new QListViewItem(this->reactionSubtree, "concentration fluxes");
  this->reactionParameterSubtree = new QListViewItem(this->reactionSubtree, "reaction parameters");

  this->metaboliteSubtree = new QListViewItem(this, "metabolites");
  this->transientParticleNumberSubtree = new QListViewItem(this->metaboliteSubtree, "transient particle numbers");
  this->transientConcentrationSubtree = new QListViewItem(this->metaboliteSubtree, "transient concentrations");
  this->initialParticleNumberSubtree = new QListViewItem(this->metaboliteSubtree, "initial particle numbers");
  this->initialConcentrationSubtree = new QListViewItem(this->metaboliteSubtree, "initial concentrations");

  this->compartmentSubtree = new QListViewItem(this, "compartments");
  //this->volumeSubtree = new QListViewItem(this->compartmentSubtree, "transient volumes");
  //this->initialVolumeSubtree = new QListViewItem(this->compartmentSubtree, "initial volumes");
  this->volumeSubtree = new QListViewItem(this->compartmentSubtree, "volumes");

  this->timeSubtree = new QListViewItem(this, "time");

  //TODO enable initial values for compartments and global parameters when we need them.
}

CCopasiSimpleSelectionTree::~CCopasiSimpleSelectionTree()
{}

void CCopasiSimpleSelectionTree::populateTree(const CModel * model)
{
  if (!model) return;

  QListViewItem* item = new QListViewItem(this->timeSubtree, "Model Time");
  this->treeItems[item] =
    const_cast< CCopasiObject * >(model->getObject(CCopasiObjectName("Reference=Time")));

  item = new QListViewItem(this->timeSubtree, "Model Initial Time");
  this->treeItems[item] =
    const_cast< CCopasiObject * >(model->getObject(CCopasiObjectName("Reference=Initial Time")));

  item = new QListViewItem(this->timeSubtree, "cpu time");
  CCopasiObject* obj =
    const_cast< CCopasiObject * >(CCopasiContainer::Root->getObject(CCopasiObjectName("Timer=CPU Time")));
  this->treeItems[item] = obj;

  item = new QListViewItem(this->timeSubtree, "real time");
  obj =
    const_cast< CCopasiObject * >(CCopasiContainer::Root->getObject(CCopasiObjectName("Timer=Wall Clock Time")));
  this->treeItems[item] = obj;

  // find all metabolites and create items in the metabolite subtree
  const CCopasiVector<CMetab>& metabolites = model->getMetabolites();
  unsigned int counter;
  unsigned int maxCount = metabolites.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CMetab* metab = metabolites[counter - 1];
      std::string name = metab->getObjectName();
      bool unique = this->isMetaboliteNameUnique(name, metabolites);
      if (!unique)
        {
          const CCompartment* comp = metab->getCompartment();
          if (comp)
            {
              name = name + "(" + comp->getObjectName() + ")";
            }
        }
      name = "[" + name + "]";
      item = new QListViewItem(this->initialConcentrationSubtree,
                               FROM_UTF8((name + "(t=0)")));
      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=InitialConcentration"));
      item = new QListViewItem(this->transientConcentrationSubtree,
                               FROM_UTF8((name + "(t)")));
      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=Concentration"));
      item = new QListViewItem(initialParticleNumberSubtree,
                               FROM_UTF8((name + "(t=0)")));

      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=InitialParticleNumber"));
      item = new QListViewItem(this->transientParticleNumberSubtree,
                               FROM_UTF8((name + "(t)")));
      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=ParticleNumber"));
    }

  // find all reactions and create items in the reaction subtree
  const CCopasiVectorNS<CReaction>& reactions = model->getReactions();
  maxCount = reactions.size();
  for (counter = maxCount; counter != 0; --counter)
    {
      const CReaction* react = reactions[counter - 1];
      std::string name = react->getObjectName();
      name = "flux(" + name + ")";
      item = new QListViewItem(this->concentrationFluxSubtree,
                               FROM_UTF8(name));
      treeItems[item] = (CCopasiObject*)react->getObject(CCopasiObjectName("Reference=Flux"));
      item = new QListViewItem(this->particleFluxSubtree,
                               FROM_UTF8(("particle_" + name)));
      treeItems[item] = (CCopasiObject*)react->getObject(CCopasiObjectName("Reference=ParticleFlux"));
      // create items for the reaction parameters
      item = new QListViewItem(this->reactionParameterSubtree,
                               FROM_UTF8(react->getObjectName()));
      const CCopasiParameterGroup& parameters = react->getParameters();
      unsigned int j;
      unsigned int numParameters = parameters.size();
      for (j = numParameters; j != 0; --j)
        {
          CCopasiParameter* parameter = ((CCopasiParameterGroup&)parameters).getParameter(j - 1);
          QListViewItem* parameterItem =
            new QListViewItem(item,
                              FROM_UTF8(parameter->getObjectName()));
          treeItems[parameterItem] = (CCopasiObject*)(parameter->getObject(CCopasiObjectName("Reference=Value")));
        }
    }

  // find all global parameters aka model variables
  const CCopasiVector<CModelValue>& objects = model->getModelValues();
  maxCount = objects.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CModelEntity* object = objects[counter - 1];
      std::string name = object->getObjectName();

      item = new QListViewItem(this->initialValueSubtree,
                               FROM_UTF8((name + "(t=0)")));
      treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=InitialValue"));

      item = new QListViewItem(this->valueSubtree,
                               FROM_UTF8(name + "(t)"));
      treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=Value"));

      //item = new QListViewItem(this->valueRateSubtree,
      //                         FROM_UTF8(("d(" + name + ")/dt")));
      //treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=Rate"));
    }

  // find all compartments
  const CCopasiVector<CCompartment>& objects2 = model->getCompartments();
  maxCount = objects2.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CModelEntity* object = objects2[counter - 1];
      std::string name = object->getObjectName();

      //item = new QListViewItem(this->initialVolumeSubtree,
      //                         FROM_UTF8((name + "(t=0)")));
      //treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=InitialVolume"));

      item = new QListViewItem(this->volumeSubtree,
                               FROM_UTF8(name /*+ "(t)"*/));
      treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=Volume"));

      //item = new QListViewItem(this->volumeRateSubtree,
      //                         FROM_UTF8(("d(" + name + ")/dt")));
      //treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=Rate"));
    }

#ifdef COPASI_DEBUG

  // experimental annotated matrix
  item = new QListViewItem(this->matrixSubtree, "stoichiometric matrix");
  CCopasiObject* object = (CCopasiObject*)model->getObject(CCopasiObjectName("Array=Stoichiometry(ann)"));
  treeItems[item] = object;
#endif // COPASI_DEBUG

  if (this->selectionMode() == QListView::NoSelection)
    {
      // see if some objects are there, if yes set to single selection
      QListViewItemIterator it = QListViewItemIterator(this);
      while (it.current())
        {
          if (this->treeItems.find(it.current()) != this->treeItems.end())
            {
              this->setSelectionMode(QListView::Single);
              this->setCurrentItem(it.current());
              it.current()->setSelected(true);
              QListViewItem* parent = it.current()->parent();
              while (parent)
                {
                  parent->setOpen(true);
                  parent = parent->parent();
                }
              break;
            }
          ++it;
        }
    }
}

bool CCopasiSimpleSelectionTree::treeHasSelection()
{
  bool hasSelection = false;
  QListViewItemIterator it(this);
  while (it.current())
    {
      if (it.current()->isSelected())
        {
          hasSelection = true;
          break;
        }
      ++it;
    }
  return hasSelection;
}

std::vector<CCopasiObject*>* CCopasiSimpleSelectionTree::getTreeSelection()
{
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  if (this->selectionMode() == QListView::Single && this->selectedItem())
    {
      selection->push_back(this->treeItems[this->selectedItem()]);
    }
  else
    {
      // go through the whole tree and check for selected items.
      // if the selected item has children, add all children that are leaves
      // and are connected to an object.
      // If the item is a leave and is connected to an object, add it directly
      QListViewItemIterator it(this);
      QListViewItem* currentItem = it.current();
      while (currentItem)
        {
          if (currentItem->isSelected())
            {
              if (currentItem->childCount() == 0)
                {
                  if (this->treeItems.find(currentItem) != this->treeItems.end())
                    {
                      selection->push_back(this->treeItems[currentItem]);
                    }
                }
              else
                {
                  QListViewItemIterator it2(currentItem);
                  QListViewItem* tmpItem = it2.current();
                  QListViewItem* Ancestor;

                  while (tmpItem)
                    {
                      if ((tmpItem->childCount() == 0) &&
                          (this->treeItems.find(tmpItem) != this->treeItems.end()))
                        {
                          selection->push_back(this->treeItems[tmpItem]);
                        }
                      ++it2;
                      tmpItem = it2.current();
                      if (!tmpItem) break;

                      // We continue as long as the current item is an
                      // ancestor of the tmp item, i.e., it is in the branch
                      // originating from current item.
                      for (Ancestor = tmpItem->parent();
                           Ancestor != currentItem && Ancestor;
                           Ancestor = Ancestor->parent());
                      if (!Ancestor) break;
                    }
                }
            }
          ++it;
          currentItem = it.current();
        }
    }
  return selection;
}

bool CCopasiSimpleSelectionTree::isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites)
{
  bool unique = true;
  bool found = false;
  unsigned int counter;
  for (counter = 0; counter < metabolites.size();++counter)
    {
      const std::string& thisName = metabolites[counter]->getObjectName();
      if (name == thisName)
        {
          if (found)
            {
              unique = false;
              break;
            }
          found = true;
        }
    }
  return unique;
}

QListViewItem * CCopasiSimpleSelectionTree::findListViewItem(const CCopasiObject * object)
{
  QListViewItem* item = NULL;
  std::map<QListViewItem*, CCopasiObject*>::iterator it = this->treeItems.begin();
  std::map<QListViewItem*, CCopasiObject*>::iterator endPos = this->treeItems.end();
  while (it != endPos)
    {
      if (it->second == object)
        {
          item = it->first;
          break;
        }
      ++it;
    }
  return item;
}

void CCopasiSimpleSelectionTree::selectObjects(std::vector<CCopasiObject *> * objects)
{
  // clear selection on tree and select new objects
  this->clearSelection();
  unsigned int i;
  unsigned int iMax = objects->size();
  if ((this->selectionMode() == QListView::Single || this->selectionMode() == QListView::NoSelection) && iMax > 1)
    {
      iMax = 1;
    }
  for (i = 0; i < iMax;++i)
    {
      CCopasiObject* object = objects->at(i);
      QListViewItem* item = this->findListViewItem(object);
      if (!item && this->expertSubtree)
        {
          // add the item to the expert branch
          item = new QListViewItem(this->expertSubtree,
                                   FROM_UTF8(object->getObjectDisplayName()));
          treeItems[item] = object;
        }
      // open the whole branch that contains item.
      QListViewItem* parent = item->parent();
      if (parent && !(parent->isOpen()))
        {
          while (parent)
            {
              parent->setOpen(true);
              parent = parent->parent();
            }
        }
      this->setSelected(item, true);
    }
}

void CCopasiSimpleSelectionTree::commitClicked()
{
  if (this->mpOutputVector)
    {
      std::vector<CCopasiObject*>* treeSelection = this->getTreeSelection();
      this->mpOutputVector->assign(treeSelection->begin(), treeSelection->end());
      std::vector<CCopasiObject*>::iterator it = this->mpOutputVector->begin();
      while (it != this->mpOutputVector->end())
        {
          if (*it == NULL)
            {
              it = this->mpOutputVector->erase(it);
            }
          else
            {
              ++it;
            }
        }
      delete treeSelection;
    }
}

void CCopasiSimpleSelectionTree::setOutputVector(std::vector<CCopasiObject*>* outputVector)
{
  this->mpOutputVector = outputVector;
  if (this->mpOutputVector)
    {
      this->selectObjects(this->mpOutputVector);
    }
}

CCopasiRuleExpressionSelectionTree::CCopasiRuleExpressionSelectionTree(QWidget* parent, const char* name, WFlags fl): CCopasiSimpleSelectionTree(parent, name, fl)
{
  this->takeItem(this->expertSubtree);
  pdelete(this->expertSubtree);
#ifdef COPASI_DEBUG
  this->takeItem(this->matrixSubtree);
  pdelete(this->matrixSubtree);
#endif
  this->takeItem(this->reactionSubtree);
  pdelete(this->reactionSubtree);
  this->metaboliteSubtree->takeItem(this->initialParticleNumberSubtree);
  pdelete(this->initialParticleNumberSubtree);
  this->metaboliteSubtree->takeItem(this->initialConcentrationSubtree);
  pdelete(this->initialConcentrationSubtree);
  this->metaboliteSubtree->takeItem(this->transientParticleNumberSubtree);
  pdelete(this->transientParticleNumberSubtree);
  this->modelValueSubtree->takeItem(this->initialValueSubtree);
  pdelete(this->initialValueSubtree);
}

void CCopasiRuleExpressionSelectionTree::populateTree(const CModel* model)
{
  if (!model) return;

  QListViewItem* item = new QListViewItem(this->timeSubtree, "Model Time");
  this->treeItems[item] =
    const_cast< CCopasiObject * >(model->getObject(CCopasiObjectName("Reference=Time")));

  // find all metabolites and create items in the metabolite subtree
  const CCopasiVector<CMetab>& metabolites = model->getMetabolites();
  unsigned int counter;
  unsigned int maxCount = metabolites.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CMetab* metab = metabolites[counter - 1];
      std::string name = metab->getObjectName();
      bool unique = this->isMetaboliteNameUnique(name, metabolites);
      if (!unique)
        {
          const CCompartment* comp = metab->getCompartment();
          if (comp)
            {
              name = name + "(" + comp->getObjectName() + ")";
            }
        }
      name = "[" + name + "]";
      item = new QListViewItem(this->transientConcentrationSubtree,
                               FROM_UTF8((name + "(t)")));
      treeItems[item] = (CCopasiObject*)metab->getObject(CCopasiObjectName("Reference=Concentration"));
    }

  // find all reactions and create items in the reaction subtree
  /*
  const CCopasiVectorNS<CReaction>& reactions = model->getReactions();
  maxCount = reactions.size();
  for (counter = maxCount; counter != 0; --counter)
    {
      const CReaction* react = reactions[counter - 1];
      std::string name = react->getObjectName();
      name = "flux(" + name + ")";
      item = new QListViewItem(this->concentrationFluxSubtree,
                               FROM_UTF8(name));
      treeItems[item] = (CCopasiObject*)react->getObject(CCopasiObjectName("Reference=Flux"));
      item = new QListViewItem(this->particleFluxSubtree,
                               FROM_UTF8(("particle_" + name)));
    }
  */
  // find all global parameters aka model variables
  const CCopasiVector<CModelValue>& objects = model->getModelValues();
  maxCount = objects.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CModelEntity* object = objects[counter - 1];
      std::string name = object->getObjectName();

      item = new QListViewItem(this->valueSubtree,
                               FROM_UTF8(name + "(t)"));
      treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=Value"));
    }

  // find all compartments
  const CCopasiVector<CCompartment>& objects2 = model->getCompartments();
  maxCount = objects2.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CModelEntity* object = objects2[counter - 1];
      std::string name = object->getObjectName();

      item = new QListViewItem(this->volumeSubtree,
                               FROM_UTF8(name /*+ "(t)"*/));
      treeItems[item] = (CCopasiObject*)object->getObject(CCopasiObjectName("Reference=Volume"));
    }

  if (this->selectionMode() == QListView::NoSelection)
    {
      // see if some objects are there, if yes set to single selection
      QListViewItemIterator it = QListViewItemIterator(this);
      while (it.current())
        {
          if (this->treeItems.find(it.current()) != this->treeItems.end())
            {
              this->setSelectionMode(QListView::Single);
              this->setCurrentItem(it.current());
              it.current()->setSelected(true);
              QListViewItem* parent = it.current()->parent();
              while (parent)
                {
                  parent->setOpen(true);
                  parent = parent->parent();
                }
              break;
            }
          ++it;
        }
    }
}
