// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.cpp,v $
//   $Revision: 1.26 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/03 17:40:33 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CCopasiSimpleSelectionTree.h"
#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CReaction.h"
#include "utilities/CCopasiParameter.h"
#include "utilities/CCopasiParameterGroup.h"
#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiTimer.h"
#include "report/CCopasiObjectName.h"
#include "qtUtilities.h"

CCopasiSimpleSelectionTree::CCopasiSimpleSelectionTree(QWidget* parent, const char* name, WFlags fl): QListView(parent, name, fl), mpOutputVector(NULL)
{
  this->setSelectionMode(QListView::Extended);
  this->setSortColumn(-1);
  this->setRootIsDecorated(true);
  this->addColumn("");
  this->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, this->sizePolicy().hasHeightForWidth()));
  this->mpExpertSubtree = new QListViewItem(this, "Expert");

#ifdef COPASI_DEBUG
  this->matrixSubtree = new QListViewItem(this, "Matrices");
#endif // COPASI_DEBUG

  this->mpModelQuantitySubtree = new QListViewItem(this, "Global Quantities");
  this->mpModelQuantityRateSubtree =
    new QListViewItem(this->mpModelQuantitySubtree, "Rates");
  this->mpModelQuantityTransientValueSubtree =
    new QListViewItem(this->mpModelQuantitySubtree, "Transient Values");
  this->mpModelQuantityInitialValueSubtree =
    new QListViewItem(this->mpModelQuantitySubtree, "Initial Values");

  this->mpReactionSubtree = new QListViewItem(this, "Reactions");
  this->mpReactionFluxNumberSubtree =
    new QListViewItem(this->mpReactionSubtree, "Fluxes (Particle Numbers)");
  this->mpReactionFluxConcentrationSubtree =
    new QListViewItem(this->mpReactionSubtree, "Fluxes (Concentration)");
  this->mpReactionParameterSubtree =
    new QListViewItem(this->mpReactionSubtree, "Reaction Parameters");

  this->mpMetaboliteSubtree = new QListViewItem(this, "Species");
  this->mpMetaboliteRateNumberSubtree =
    new QListViewItem(this->mpMetaboliteSubtree, "Rates (Particle Numbers)");
  this->mpMetaboliteRateConcentrationSubtree =
    new QListViewItem(this->mpMetaboliteSubtree, "Rates (Concentrations)");
  this->mpMetaboliteTransientNumberSubtree =
    new QListViewItem(this->mpMetaboliteSubtree, "Transient Particle Numbers");
  this->mpMetaboliteTransientConcentrationSubtree =
    new QListViewItem(this->mpMetaboliteSubtree, "Transient Concentrations");
  this->mpMetaboliteInitialNumberSubtree =
    new QListViewItem(this->mpMetaboliteSubtree, "Initial Particle Numbers");
  this->mpMetaboliteInitialConcentrationSubtree =
    new QListViewItem(this->mpMetaboliteSubtree, "Initial Concentrations");

  this->mpCompartmentSubtree = new QListViewItem(this, "Compartments");
  this->mpCompartmentRateSubtree =
    new QListViewItem(this->mpCompartmentSubtree, "Rates");
  this->mpCompartmentTransientVolumeSubtree =
    new QListViewItem(this->mpCompartmentSubtree, "Transient Volumes");
  this->mpCompartmentInitialVolumeSubtree =
    new QListViewItem(this->mpCompartmentSubtree, "Initial Volumes");

  this->mpTimeSubtree = new QListViewItem(this, "Time");

  //TODO enable initial values for compartments and global parameters when we need them.
}

CCopasiSimpleSelectionTree::~CCopasiSimpleSelectionTree()
{}

void CCopasiSimpleSelectionTree::populateTree(const CModel * pModel,
    const SelectionFlag & flag)
{
  if (!pModel) return;

  const CCopasiObject * pObject;
  QListViewItem * pItem;
  pObject = pModel->getObject(CCopasiObjectName("Reference=Time"));
  if (filter(flag, pObject))
    {
      pItem = new QListViewItem(this->mpTimeSubtree, "Model Time");
      treeItems[pItem] = pObject;
    }

  pObject = pModel->getObject(CCopasiObjectName("Reference=Initial Time"));
  if (filter(flag, pObject))
    {
      pItem = new QListViewItem(this->mpTimeSubtree, "Model Initial Time");
      treeItems[pItem] = pObject;
    }

  pObject = CCopasiContainer::Root->getObject(CCopasiObjectName("Timer=CPU Time"));
  if (filter(flag, pObject))
    {
      pItem = new QListViewItem(this->mpTimeSubtree, "cpu time");
      treeItems[pItem] = pObject;
    }

  pObject = CCopasiContainer::Root->getObject(CCopasiObjectName("Timer=Wall Clock Time"));
  if (filter(flag, pObject))
    {
      pItem = new QListViewItem(this->mpTimeSubtree, "real time");
      treeItems[pItem] = pObject;
    }

  removeEmptySubTree(&mpTimeSubtree);

  // find all metabolites and create items in the metabolite subtree
  const CCopasiVector<CMetab>& metabolites = pModel->getMetabolites();
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

      pObject = metab->getObject(CCopasiObjectName("Reference=InitialParticleNumber"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteInitialNumberSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getObject(CCopasiObjectName("Reference=ParticleNumber"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteTransientNumberSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getObject(CCopasiObjectName("Reference=ParticleNumberRate"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteRateNumberSubtree, FROM_UTF8("d(" + name + ")/dt"));
          treeItems[pItem] = pObject;
        }

      name = "[" + name + "]"; // Concentration
      pObject = metab->getObject(CCopasiObjectName("Reference=InitialConcentration"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteInitialConcentrationSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getObject(CCopasiObjectName("Reference=Concentration"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteTransientConcentrationSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getObject(CCopasiObjectName("Reference=Rate"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteRateConcentrationSubtree, FROM_UTF8("d(" + name + ")/dt"));
          treeItems[pItem] = pObject;
        }
    }

  removeEmptySubTree(&mpMetaboliteInitialNumberSubtree);
  removeEmptySubTree(&mpMetaboliteTransientNumberSubtree);
  removeEmptySubTree(&mpMetaboliteRateNumberSubtree);
  removeEmptySubTree(&mpMetaboliteInitialConcentrationSubtree);
  removeEmptySubTree(&mpMetaboliteTransientConcentrationSubtree);
  removeEmptySubTree(&mpMetaboliteRateConcentrationSubtree);
  removeEmptySubTree(&mpMetaboliteSubtree);

  // find all reactions and create items in the reaction subtree
  const CCopasiVectorNS<CReaction>& reactions = pModel->getReactions();
  maxCount = reactions.size();
  for (counter = maxCount; counter != 0; --counter)
    {
      const CReaction* react = reactions[counter - 1];
      std::string name = "flux(" + react->getObjectName() + ")";

      pObject = react->getObject(CCopasiObjectName("Reference=Flux"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpReactionFluxConcentrationSubtree, FROM_UTF8(name));
          treeItems[pItem] = pObject;
        }

      pObject = react->getObject(CCopasiObjectName("Reference=ParticleFlux"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpReactionFluxNumberSubtree, FROM_UTF8("particle " + name));
          treeItems[pItem] = pObject;
        }

      // create items for the reaction parameters

      pItem = new QListViewItem(this->mpReactionParameterSubtree,
                                FROM_UTF8(react->getObjectName()));
      const CCopasiParameterGroup & Parameters = react->getParameters();
      unsigned int j;
      unsigned int numParameters = Parameters.size();
      for (j = numParameters; j != 0; --j)
        {
          const CCopasiParameter * pParameter = Parameters.getParameter(j - 1);

          // We skip local parameters which ar covered by global parameters
          if (!react->isLocalParameter(pParameter->getObjectName()))
            continue;

          pObject = pParameter->getObject(CCopasiObjectName("Reference=Value"));
          if (filter(flag, pObject))
            {
              QListViewItem * pParameterItem =
                new QListViewItem(pItem, FROM_UTF8(pParameter->getObjectName()));
              treeItems[pParameterItem] = pObject;
            }
        }

      removeEmptySubTree(&pItem);
    }

  removeEmptySubTree(&mpReactionFluxNumberSubtree);
  removeEmptySubTree(&mpReactionFluxConcentrationSubtree);
  removeEmptySubTree(&mpReactionParameterSubtree);
  removeEmptySubTree(&mpReactionSubtree);

  // find all global parameters aka pModel variables
  const CCopasiVector<CModelValue>& objects = pModel->getModelValues();
  maxCount = objects.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CModelEntity* object = objects[counter - 1];
      std::string name = object->getObjectName();

      pObject = object->getObject(CCopasiObjectName("Reference=InitialValue"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpModelQuantityInitialValueSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = object->getObject(CCopasiObjectName("Reference=Value"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpModelQuantityTransientValueSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      if (object->getStatus() == CModelEntity::ODE)
        {
          pObject = object->getObject(CCopasiObjectName("Reference=Rate"));
          if (filter(flag, pObject))
            {
              pItem = new QListViewItem(mpModelQuantityRateSubtree, FROM_UTF8("d(" + name + ")/dt"));
              treeItems[pItem] = pObject;
            }
        }
    }

  removeEmptySubTree(&mpModelQuantityRateSubtree);
  removeEmptySubTree(&mpModelQuantityInitialValueSubtree);
  removeEmptySubTree(&mpModelQuantityTransientValueSubtree);
  removeEmptySubTree(&mpModelQuantitySubtree);

  // find all compartments
  const CCopasiVector<CCompartment>& objects2 = pModel->getCompartments();
  maxCount = objects2.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CModelEntity* object = objects2[counter - 1];
      std::string name = object->getObjectName();

      pObject = object->getObject(CCopasiObjectName("Reference=InitialVolume"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpCompartmentInitialVolumeSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = object->getObject(CCopasiObjectName("Reference=Volume"));
      if (filter(flag, pObject))
        {
          pItem = new QListViewItem(mpCompartmentTransientVolumeSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      if (object->getStatus() == CModelEntity::ODE)
        {
          pObject = object->getObject(CCopasiObjectName("Reference=Rate"));
          if (filter(flag, pObject))
            {
              pItem = new QListViewItem(mpCompartmentRateSubtree, FROM_UTF8("d(" + name + ")/dt"));
              treeItems[pItem] = pObject;
            }
        }
    }

  removeEmptySubTree(&mpCompartmentRateSubtree);
  removeEmptySubTree(&mpCompartmentInitialVolumeSubtree);
  removeEmptySubTree(&mpCompartmentTransientVolumeSubtree);
  removeEmptySubTree(&mpCompartmentSubtree);

  pObject = pModel->getObject(CCopasiObjectName("Reference=Quantity Conversion Factor"));
  if (filter(flag, pObject))
    {
      pItem = new QListViewItem(this, "Quantity Conversion Factor");
      treeItems[pItem] = pObject;
    }

#ifdef COPASI_DEBUG

  // experimental annotated matrix
  pItem = new QListViewItem(this->matrixSubtree, "stoichiometric matrix");
  CCopasiObject* object = (CCopasiObject*)pModel->getObject(CCopasiObjectName("Array=Stoichiometry(ann)"));
  treeItems[pItem] = object;
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

std::vector<const CCopasiObject * > * CCopasiSimpleSelectionTree::getTreeSelection()
{
  std::vector<const CCopasiObject * > * selection = new std::vector<const CCopasiObject * >();
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
  std::map< QListViewItem *, const CCopasiObject * >::iterator it = this->treeItems.begin();
  std::map< QListViewItem *, const CCopasiObject * >::iterator endPos = this->treeItems.end();
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

void CCopasiSimpleSelectionTree::selectObjects(std::vector< const CCopasiObject * > * objects)
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
      const CCopasiObject * object = objects->at(i);
      QListViewItem* item = this->findListViewItem(object);
      if (!item && this->mpExpertSubtree)
        {
          // add the item to the expert branch
          item = new QListViewItem(this->mpExpertSubtree,
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
      std::vector< const CCopasiObject * >* treeSelection = this->getTreeSelection();
      this->mpOutputVector->assign(treeSelection->begin(), treeSelection->end());
      std::vector< const CCopasiObject * >::iterator it = this->mpOutputVector->begin();
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

void CCopasiSimpleSelectionTree::setOutputVector(std::vector< const CCopasiObject * > * outputVector)
{
  this->mpOutputVector = outputVector;
  if (this->mpOutputVector)
    {
      this->selectObjects(this->mpOutputVector);
    }
}

// static
bool CCopasiSimpleSelectionTree::filter(const SelectionFlag & flag, const CCopasiObject * pObject)
{
  if (pObject == NULL)
    return false;

  if (flag == NO_RESTRICTION)
    return true;

  // Check whether the value is of the desired numeric type.
  if (flag & NUMERIC)
    {
      if (!pObject->isValueDbl() && !pObject->isValueInt())
        return false;
    }
  else if ((flag & BASE_DOUBLE) && !pObject->isValueDbl())
    return false;
  else if ((flag & BASE_INTEGER) && !pObject->isValueInt())
    return false;

  if (pObject->isReference())
    {
      // CModelEntity needs to be check more thoroughly
      const CModelEntity * pEntity =
        dynamic_cast< const CModelEntity * >(pObject->getObjectParent());

      if (pEntity)
        {
          // CModelEntity::ASSIGNMENT may have no intitial value or rate
          if (pEntity->getStatus() == CModelEntity::ASSIGNMENT &&
              (pObject->getObjectName().compare(0, 7, "Initial") == 0 ||
               pObject->getObjectName().find("Rate") != std::string::npos))
            return false;

          // CModelEntity::FIXED may have no rate
          if (pEntity->getStatus() == CModelEntity::FIXED &&
              pObject->getObjectName().find("Rate") != std::string::npos)
            return false;

          // CModelEntity are handled differently dependent on the type
          // of EXPRESSION.
          if (flag & BASE_EXPRESSION)
            {
              // TRANSIENT_EXPRESSION
              if (flag & BASE_TRANSIENT)
                {
                  if (pEntity->getStatus() == CModelEntity::FIXED &&
                      pObject->getObjectName().compare(0, 7, "Initial") == 0)
                    return false;
                }
              // INITIAL_EXPRESSION
              else if (flag & BASE_INITIAL)
                {
                  if (pEntity->getStatus() != CModelEntity::ASSIGNMENT &&
                      (pObject->getObjectName().compare(0, 7, "Initial") != 0 &&
                       pObject->getObjectName() != "Quantity Conversion Factor"))
                    return false;
                }

              // Everything else is allowed in EXPRESSION
              return true;
            }

          // INITIAL_VALUE
          if ((flag & BASE_INITIAL)
              && pObject->getObjectName().compare(0, 7, "Initial") != 0)
            return false;

          // TRANSIENT_VALUE
          if ((flag & BASE_TRANSIENT)
              && pObject->getObjectName().compare(0, 7, "Initial") == 0)
            return false;

          // This CModelEntity is valid.
          return true;
        }

      // CReaction needs to be check more thoroughly
      const CReaction * pReaction =
        dynamic_cast< const CReaction * >(pObject->getObjectParent());

      if (pReaction)
        {
          // These are transient values which may be used in expressions.
          if ((flag & BASE_INITIAL) &&
              !(flag & BASE_EXPRESSION))
            return false;

          // Every other value of CReaction is valid.
          return true;
        }

      // Reaction Parameters
      pReaction =
        dynamic_cast< const CReaction * >(pObject->getObjectAncestor("Reaction"));

      if (pReaction)
        {
          // Local reaction parameters may not be used in any expression in the model.
          if ((flag & BASE_GLOBAL))
            return false;

          // These are initial values which may be used in expressions.
          if (!(flag & BASE_EXPRESSION) &&
              (flag & BASE_TRANSIENT))
            return false;

          return true;
        }
    }
  // CCopasiTimer may not be used in the model.
  else if (dynamic_cast< const CCopasiTimer * >(pObject) &&
           (flag & BASE_MODEL))
    return false;

  // All tests passed :)
  return true;
}

void CCopasiSimpleSelectionTree::removeEmptySubTree(QListViewItem ** ppSubTree)
{
  if ((*ppSubTree)->childCount() == 0)
    pdelete(*ppSubTree);
}
