/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/12/09 15:49:53 $
   End CVS Header */

#include "CCopasiSimpleSelectionTree.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "utilities/CCopasiParameter.h"
#include "utilities/CCopasiParameterGroup.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "qtUtilities.h"

CCopasiSimpleSelectionTree::CCopasiSimpleSelectionTree(QWidget* parent, const char* name, WFlags fl)
{
  this->setSelectionMode(QListView::Single);
  this->setSortColumn(-1);
  this->setRootIsDecorated(true);
  this->reactionSubtree = new QListViewItem(this, "reactions");
  this->particleFluxSubtree = new QListViewItem(this->reactionSubtree, "particle fluxes");
  this->concentrationFluxSubtree = new QListViewItem(this->reactionSubtree, "concentration fluxes");

  this->metaboliteSubtree = new QListViewItem(this, "metabolites");
  this->reactionParameterSubtree = new QListViewItem(this->reactionSubtree, "reaction parameters");
  this->transientParticleNumberSubtree = new QListViewItem(this->metaboliteSubtree, "transient particle numbers");
  this->transientConcentrationSubtree = new QListViewItem(this->metaboliteSubtree, "transient concentrations");
  this->initialParticleNumberSubtree = new QListViewItem(this->metaboliteSubtree, "initial particle numbers");
  this->initialConcentrationSubtree = new QListViewItem(this->metaboliteSubtree, "initial concentrations");

  this->timeSubtree = new QListViewItem(this, "time");
  this->expertSubtree = new QListViewItem(this, "expert");
}

CCopasiSimpleSelectionTree::~CCopasiSimpleSelectionTree()
{
  this->clearTree();
  delete this->timeSubtree;
  delete this->concentrationFluxSubtree;
  delete this->particleFluxSubtree;
  delete this->reactionParameterSubtree;
  delete this->initialConcentrationSubtree;
  delete this->initialParticleNumberSubtree;
  delete this->transientParticleNumberSubtree;
  delete this->transientConcentrationSubtree;
  delete this->metaboliteSubtree;
  delete this->reactionSubtree;
  delete this->expertSubtree;
}

void CCopasiSimpleSelectionTree::populateTree(CModel * model)
{
  if (!model) return;
  // find all metabolites and create items in the metabolite subtree
  QListViewItem* item = new QListViewItem(this->timeSubtree, "time");
  this->treeItems[item] = (CCopasiObject*)model->getObject(CCopasiObjectName("Reference=Time"));
  const CCopasiVector<CMetab>& metabolites = model->getMetabolites();
  unsigned int counter;
  unsigned int maxCount = metabolites.size();
  for (counter = 0; counter < maxCount;++counter)
    {
      const CMetab* metab = metabolites[counter];
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
  for (counter = 0; counter < maxCount;++counter)
    {
      const CReaction* react = reactions[counter];
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
      for (j = 0; j < numParameters;++j)
        {
          CCopasiParameter* parameter = ((CCopasiParameterGroup&)parameters).getParameter(j);
          QListViewItem* parameterItem =
            new QListViewItem(item,
                              FROM_UTF8(parameter->getObjectName()));
          treeItems[parameterItem] = (CCopasiObject*)parameter;
        }
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
                  while (tmpItem)
                    {
                      if ((tmpItem->childCount() == 0) && (this->treeItems.find(tmpItem) != this->treeItems.end()))
                        {
                          selection->push_back(this->treeItems[currentItem]);
                        }
                      ++it2;
                      tmpItem = it2.current();
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

void CCopasiSimpleSelectionTree::clearTree()
{
  QListViewItem* child = this->timeSubtree->firstChild();
  QListViewItem* nextSibling;
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->concentrationFluxSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->particleFluxSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->initialConcentrationSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->initialParticleNumberSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->transientParticleNumberSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->transientConcentrationSubtree->firstChild();
  while (child)
    {
      nextSibling = child->nextSibling();
      delete child;
      child = nextSibling;
    }
  child = this->reactionParameterSubtree->firstChild();
  while (child)
    {
      nextSibling = child->firstChild();
      if (!nextSibling)
        {
          nextSibling = child->nextSibling();
          delete child;
        }
      child = nextSibling;
    }
  child = this->expertSubtree->firstChild();
  while (child)
    {
      nextSibling = child->firstChild();
      if (!nextSibling)
        {
          nextSibling = child->nextSibling();
          delete child;
        }
      child = nextSibling;
    }
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
      if (!item)
        {
          // add the item to the expert branch
          item = new QListViewItem(this->expertSubtree,
                                   FROM_UTF8(object->getObjectDisplayName()));
          treeItems[item] = object;
        }
      item->setSelected(true);
    }
}
