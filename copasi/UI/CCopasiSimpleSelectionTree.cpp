// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CCopasiSimpleSelectionTree.cpp,v $
//   $Revision: 1.26.4.10.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/01/29 20:25:22 $
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

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CAnnotatedMatrix.h"
#include "utilities/CCopasiTask.h"
#include "steadystate/CMCAMethod.h"
#include "steadystate/CSteadyStateTask.h"
#include "sensitivities/CSensProblem.h"

/// Standard constructor
CCopasiSimpleSelectionTree::CCopasiSimpleSelectionTree(QWidget* parent, const char* name, WFlags fl): QListView(parent, name, fl), mpOutputVector(NULL)
{
  setSelectionMode(QListView::Extended);
  setSortColumn(-1);
  setRootIsDecorated(true);
  addColumn("");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, sizePolicy().hasHeightForWidth()));
  mpExpertSubtree = new QListViewItem(this, "Expert");

  mpResultMatrixSubtree = new QListViewItem(this, "Results");
  mpResultSteadyStateSubtree = new QListViewItem(mpResultMatrixSubtree, "Steady State");
  mpResultSensitivitySubtree = new QListViewItem(mpResultMatrixSubtree, "Sensitivity");
  mpResultMCASubtree = new QListViewItem(mpResultMatrixSubtree, "Metabolic Control Analysis");

  mpModelMatrixSubtree = new QListViewItem(this, "Matrices");

  mpModelQuantitySubtree = new QListViewItem(this, "Global Quantities");
  mpModelQuantityRateSubtree =
    new QListViewItem(mpModelQuantitySubtree, "Rates");
  mpModelQuantityTransientValueSubtree =
    new QListViewItem(mpModelQuantitySubtree, "Transient Values");
  mpModelQuantityInitialValueSubtree =
    new QListViewItem(mpModelQuantitySubtree, "Initial Values");

  mpReactionSubtree = new QListViewItem(this, "Reactions");
  mpReactionFluxNumberSubtree =
    new QListViewItem(mpReactionSubtree, "Fluxes (Particle Numbers)");
  mpReactionFluxConcentrationSubtree =
    new QListViewItem(mpReactionSubtree, "Fluxes (Concentration)");
  mpReactionParameterSubtree =
    new QListViewItem(mpReactionSubtree, "Reaction Parameters");

  mpMetaboliteSubtree = new QListViewItem(this, "Species");
  mpMetaboliteRateNumberSubtree =
    new QListViewItem(mpMetaboliteSubtree, "Rates (Particle Numbers)");
  mpMetaboliteRateConcentrationSubtree =
    new QListViewItem(mpMetaboliteSubtree, "Rates (Concentrations)");
  mpMetaboliteTransientNumberSubtree =
    new QListViewItem(mpMetaboliteSubtree, "Transient Particle Numbers");
  mpMetaboliteTransientConcentrationSubtree =
    new QListViewItem(mpMetaboliteSubtree, "Transient Concentrations");
  mpMetaboliteInitialNumberSubtree =
    new QListViewItem(mpMetaboliteSubtree, "Initial Particle Numbers");
  mpMetaboliteInitialConcentrationSubtree =
    new QListViewItem(mpMetaboliteSubtree, "Initial Concentrations");

  mpCompartmentSubtree = new QListViewItem(this, "Compartments");
  mpCompartmentRateSubtree =
    new QListViewItem(mpCompartmentSubtree, "Rates");
  mpCompartmentTransientVolumeSubtree =
    new QListViewItem(mpCompartmentSubtree, "Transient Volumes");
  mpCompartmentInitialVolumeSubtree =
    new QListViewItem(mpCompartmentSubtree, "Initial Volumes");

  mpTimeSubtree = new QListViewItem(this, "Time");
}

/// Destructor
CCopasiSimpleSelectionTree::~CCopasiSimpleSelectionTree()
{}

/*
 * build the population tree
 */
void CCopasiSimpleSelectionTree::populateTree(const CModel * pModel,
    const ObjectClasses & classes)
{
  if (!pModel) return;

  const CCopasiObject * pObject;
  QListViewItem * pItem;

  // find all kinds of time
  pObject = pModel->getObject(CCopasiObjectName("Reference=Time"));
  if (filter(classes, pObject))
    {
      pItem = new QListViewItem(mpTimeSubtree, "Model Time");
      treeItems[pItem] = pObject;
    }

  pObject = pModel->getObject(CCopasiObjectName("Reference=Initial Time"));
  if (filter(classes, pObject))
    {
      pItem = new QListViewItem(mpTimeSubtree, "Model Initial Time");
      treeItems[pItem] = pObject;
    }

  pObject = CCopasiContainer::Root->getObject(CCopasiObjectName("Timer=CPU Time"));
  if (filter(classes, pObject))
    {
      pItem = new QListViewItem(mpTimeSubtree, "cpu time");
      treeItems[pItem] = pObject;
    }

  pObject = CCopasiContainer::Root->getObject(CCopasiObjectName("Timer=Wall Clock Time"));
  if (filter(classes, pObject))
    {
      pItem = new QListViewItem(mpTimeSubtree, "real time");
      treeItems[pItem] = pObject;
    }

  removeEmptySubTree(&mpTimeSubtree);

  // find all species (aka metabolites) and create items in the metabolite subtree
  const CCopasiVector<CMetab>& metabolites = pModel->getMetabolites();
  unsigned int counter;
  unsigned int maxCount = metabolites.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CMetab* metab = metabolites[counter - 1];
      std::string name = metab->getObjectName();
      bool unique = isMetaboliteNameUnique(name, metabolites);
      if (!unique)
        {
          const CCompartment* comp = metab->getCompartment();
          if (comp)
            {
              name = name + "(" + comp->getObjectName() + ")";
            }
        }

      pObject = metab->getObject(CCopasiObjectName("Reference=InitialParticleNumber"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteInitialNumberSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getObject(CCopasiObjectName("Reference=ParticleNumber"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteTransientNumberSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      if (metab->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = metab->getObject(CCopasiObjectName("Reference=ParticleNumberRate"));
          if (filter(classes, pObject))
            {
              pItem = new QListViewItem(mpMetaboliteRateNumberSubtree, FROM_UTF8("d(" + name + ")/dt"));
              treeItems[pItem] = pObject;
            }
        }

      name = "[" + name + "]"; // Concentration
      pObject = metab->getObject(CCopasiObjectName("Reference=InitialConcentration"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteInitialConcentrationSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getObject(CCopasiObjectName("Reference=Concentration"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpMetaboliteTransientConcentrationSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      if (metab->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = metab->getObject(CCopasiObjectName("Reference=Rate"));
          if (filter(classes, pObject))
            {
              pItem = new QListViewItem(mpMetaboliteRateConcentrationSubtree, FROM_UTF8("d(" + name + ")/dt"));
              treeItems[pItem] = pObject;
            }
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
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpReactionFluxConcentrationSubtree, FROM_UTF8(name));
          treeItems[pItem] = pObject;
        }

      pObject = react->getObject(CCopasiObjectName("Reference=ParticleFlux"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpReactionFluxNumberSubtree, FROM_UTF8("particle " + name));
          treeItems[pItem] = pObject;
        }

      // create items for the reaction parameters
      pItem = new QListViewItem(mpReactionParameterSubtree,
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
          if (filter(classes, pObject))
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

  // find all global parameters (aka model values) variables
  const CCopasiVector<CModelValue>& objects = pModel->getModelValues();
  maxCount = objects.size();
  for (counter = maxCount; counter != 0;--counter)
    {
      const CModelEntity* object = objects[counter - 1];
      std::string name = object->getObjectName();

      pObject = object->getObject(CCopasiObjectName("Reference=InitialValue"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpModelQuantityInitialValueSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = object->getObject(CCopasiObjectName("Reference=Value"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpModelQuantityTransientValueSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      if (object->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = object->getObject(CCopasiObjectName("Reference=Rate"));
          if (filter(classes, pObject))
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
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpCompartmentInitialVolumeSubtree, FROM_UTF8(name + "(t=0)"));
          treeItems[pItem] = pObject;
        }

      pObject = object->getObject(CCopasiObjectName("Reference=Volume"));
      if (filter(classes, pObject))
        {
          pItem = new QListViewItem(mpCompartmentTransientVolumeSubtree, FROM_UTF8(name + "(t)"));
          treeItems[pItem] = pObject;
        }

      if (object->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = object->getObject(CCopasiObjectName("Reference=Rate"));
          if (filter(classes, pObject))
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

  //
  pObject = pModel->getObject(CCopasiObjectName("Reference=Quantity Conversion Factor"));
  if (filter(classes, pObject))
    {
      pItem = new QListViewItem(this, "Quantity Conversion Factor");
      treeItems[pItem] = pObject;
    }

  // find all model matrices
  const CMatrix<C_FLOAT64> &StoiMatrix = pModel->getStoi();
  if (StoiMatrix.array())
    {
      pObject = pModel->getObject(CCopasiObjectName("Array=Stoichiometry(ann)"));
      //std::cout << "isArray? : " << pObject->isArray() << std::endl;
      if (filter(classes, pObject))
        {
          //      pItem = new QListViewItem(matrixSubtree, "Stoichiometry(ann)");
          pItem = new QListViewItem(mpModelMatrixSubtree, FROM_UTF8(pObject->getObjectName()));
          treeItems[pItem] = pObject;
        }
    }

  const CMatrix<C_FLOAT64> &RedStoiMatrix = pModel->getRedStoi();
  if (RedStoiMatrix.array())
    {
      pObject = pModel->getObject(CCopasiObjectName("Array=Reduced stoichiometry(ann)"));
      if (filter(classes, pObject))
        {
          //      pItem = new QListViewItem(matrixSubtree, "Reduced stoichiometry(ann)");
          pItem = new QListViewItem(mpModelMatrixSubtree, FROM_UTF8(pObject->getObjectName()));
          treeItems[pItem] = pObject;
        }
    }

  const CMatrix<C_FLOAT64> &LinkMatrix = pModel->getL0();
  if (LinkMatrix.array())
    {
      pObject = pModel->getObject(CCopasiObjectName("Array=Link matrix(ann)"));
      if (filter(classes, pObject))
        {
          //      pItem = new QListViewItem(matrixSubtree, "Link matrix(ann)");
          pItem = new QListViewItem(mpModelMatrixSubtree, FROM_UTF8(pObject->getObjectName()));
          treeItems[pItem] = pObject;
        }
    }

  removeEmptySubTree(&mpModelMatrixSubtree);

  // find all result matrices
  // Metabolic Control Analysis
  CCopasiTask *task;

  // MCA
  task = dynamic_cast<CCopasiTask*>((*CCopasiDataModel::Global->getTaskList())["Metabolic Control Analysis"]);
  try
    {
      if (task && task->updateMatrices())
        {
          //for mca the result is in the method
          CMCAMethod* pMethod = dynamic_cast<CMCAMethod *>(task->getMethod());
          //           if (pMethod->getSteadyStateStatus() == CSteadyStateMethod::found)
          //             std::cout << "Steady-State exists" << std::endl;
          //           else
          //             std::cout << "NOT EXISTS" << std::endl;

          const CCopasiContainer::objectMap * pObjects = & pMethod->getObjects();
          CCopasiContainer::objectMap::const_iterator its = pObjects->begin();
          CArrayAnnotation *ann;
          for (; its != pObjects->end(); ++its)
            {
              //              std::cout << "Name = " << its->second->getObjectName() << std::endl;
              //              std::cout << "Type = " << its->second->getObjectType() << std::endl;
              ann = dynamic_cast<CArrayAnnotation*>(its->second);
              if (!ann) continue;

              //std::cout << "8 - Name : " << ann->getObjectName() << " - Type : " << ann->getObjectType() << std::endl;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QListViewItem(this->mpResultMCASubtree, FROM_UTF8(ann->getObjectName()));
                  treeItems[pItem] = ann;
                }
            }
        }
    }
  catch (...)
  {}

  // Steady State
  task = dynamic_cast<CCopasiTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
  try
    {
      if (task && task->updateMatrices())
        {
          //for steady state the results are in the task
          const CCopasiContainer::objectMap * pObjects = & task->getObjects();
          CCopasiContainer::objectMap::const_iterator its = pObjects->begin();
          CArrayAnnotation *ann;
          for (; its != pObjects->end(); ++its)
            {
              //              std::cout << "Name = " << its->second->getObjectName() << std::endl;
              //              std::cout << "Type = " << its->second->getObjectType() << std::endl;
              ann = dynamic_cast<CArrayAnnotation*>(its->second);
              if (!ann) continue;
              //     std::cout << "9 - Name : " << ann->getObjectName() << " - Type : " << ann->getObjectType() << std::endl;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QListViewItem(this->mpResultSteadyStateSubtree, FROM_UTF8(ann->getObjectName()));
                  treeItems[pItem] = ann;
                }
            }
        }
    }
  catch (...)
  {}

  // Sensitivities
  task = dynamic_cast<CCopasiTask *>((*CCopasiDataModel::Global->getTaskList())["Sensitivities"]);
  try
    {
      if (task && task->updateMatrices())
        {
          //for sensitivities the result is in the problem
          CSensProblem *sens = dynamic_cast<CSensProblem *>(task->getProblem());

          const CCopasiContainer::objectMap * pObjects = & sens->getObjects();
          CCopasiContainer::objectMap::const_iterator its = pObjects->begin();
          CArrayAnnotation *ann;
          for (; its != pObjects->end(); ++its)
            {
              //              std::cout << "Name = " << its->second->getObjectName() << std::endl;
              //              std::cout << "Type = " << its->second->getObjectType() << std::endl;
              ann = dynamic_cast<CArrayAnnotation*>(its->second);
              if (!ann) continue;
              //     std::cout << "10 - Name : " << ann->getObjectName() << " - Type : " << ann->getObjectType() << std::endl;

              //std::cout << "isArray? : " << ann->isArray() << std::endl;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QListViewItem(this->mpResultSensitivitySubtree, FROM_UTF8(ann->getObjectName()));
                  treeItems[pItem] = (CCopasiObject *) ann;
                }
            }
        }
    }
  catch (...)
  {}

  removeEmptySubTree(&mpResultMCASubtree);
  removeEmptySubTree(&mpResultSensitivitySubtree);
  removeEmptySubTree(&mpResultSteadyStateSubtree);
  removeEmptySubTree(&mpResultMatrixSubtree);

  // combine all
  if (selectionMode() == QListView::NoSelection)
    {
      // see if some objects are there, if yes set to single selection
      QListViewItemIterator it = QListViewItemIterator(this);
      while (it.current())
        {
          if (treeItems.find(it.current()) != treeItems.end())
            {
              setSelectionMode(QListView::Single);
              setCurrentItem(it.current());
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
  std::map< std::string, const CCopasiObject * > SelectionMap;

  if (selectionMode() == QListView::Single && selectedItem())
    {
      selection->push_back(treeItems[selectedItem()]);
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
                  if (treeItems.find(currentItem) != treeItems.end())
                    SelectionMap[treeItems[currentItem]->getObjectDisplayName()] = treeItems[currentItem];
                }
              else
                {
                  QListViewItemIterator it2(currentItem);
                  QListViewItem* tmpItem = it2.current();
                  QListViewItem* Ancestor;

                  while (tmpItem)
                    {
                      if ((tmpItem->childCount() == 0) &&
                          (treeItems.find(tmpItem) != treeItems.end()))
                        SelectionMap[treeItems[tmpItem]->getObjectDisplayName()] = treeItems[tmpItem];

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

      // Copy the selection set to the selection
      selection->resize(SelectionMap.size());
      std::vector< const CCopasiObject * >::iterator itSelection = selection->begin();
      std::map< std::string, const CCopasiObject * >::const_iterator itSet = SelectionMap.begin();
      std::map< std::string, const CCopasiObject * >::const_iterator endSet = SelectionMap.end();
      for (; itSet != endSet; ++itSet, ++itSelection)
        *itSelection = itSet->second;
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
  std::map< QListViewItem *, const CCopasiObject * >::iterator it = treeItems.begin();
  std::map< QListViewItem *, const CCopasiObject * >::iterator endPos = treeItems.end();
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
  clearSelection();
  unsigned int i;
  unsigned int iMax = objects->size();
  if ((selectionMode() == QListView::Single || selectionMode() == QListView::NoSelection) && iMax > 1)
    {
      iMax = 1;
    }
  for (i = 0; i < iMax;++i)
    {
      const CCopasiObject * object = objects->at(i);
      QListViewItem* item = findListViewItem(object);
      if (!item && mpExpertSubtree)
        {
          // add the item to the expert branch
          item = new QListViewItem(mpExpertSubtree,
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
      setSelected(item, true);
    }
}

void CCopasiSimpleSelectionTree::commitClicked()
{
  if (mpOutputVector)
    {
      std::vector< const CCopasiObject * >* treeSelection = getTreeSelection();
      mpOutputVector->assign(treeSelection->begin(), treeSelection->end());
      std::vector< const CCopasiObject * >::iterator it = mpOutputVector->begin();
      while (it != mpOutputVector->end())
        {
          if (*it == NULL)
            {
              it = mpOutputVector->erase(it);
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
  mpOutputVector = outputVector;
  if (mpOutputVector)
    {
      selectObjects(mpOutputVector);
    }
}

// static
bool CCopasiSimpleSelectionTree::filter(const ObjectClasses & classes, const CCopasiObject * pObject)
{
  if (pObject == NULL)
    return false;

  if (classes & AnyObject)
    return true;

  // Check whether the value is of the desired numeric type.
  if ((classes & NumericValues) &&
      (pObject->isValueDbl() ||
       pObject->isValueInt() ||
       pObject->isArray()))
    return true;

  const CCopasiObject * pCheckedObject = pObject;

  // Elements of an array are checked as the array itself.
  if (pObject->getObjectParent()->isArray())
    pCheckedObject = pObject->getObjectParent();

  const std::string ObjectName = pObject->getObjectName();

  // CModelEntity needs to be check more thoroughly
  const CModelEntity * pEntity =
    dynamic_cast< const CModelEntity * >(pCheckedObject->getObjectParent());

  if (pEntity)
    {
      CModelEntity::Status Status = pEntity->getStatus();

      if ((classes & InitialTime) &&
          Status == CModelEntity::TIME &&
          !static_cast<const CModel *>(pEntity)->isAutonomous() &&
          ObjectName == "Initial Time")
        return true;

      if ((classes & Parameters) &&
          Status != CModelEntity::TIME &&
          Status != CModelEntity::ASSIGNMENT &&
          ObjectName.compare(0, 7, "Initial") == 0)
        return true;

      if ((classes & Variables) &&
          Status != CModelEntity::TIME &&
          Status != CModelEntity::ASSIGNMENT &&
          (ObjectName == "Value" ||
           ObjectName == "Volume" ||
           ObjectName == "ParticleNumber" ||
           ObjectName == "Concentration"))
        return true;

      if ((classes & ObservedConstants) &&
          ((Status == CModelEntity::TIME &&
            (ObjectName == "Quantity Conversion Factor" ||
             pCheckedObject->isArray())) ||
           (Status == CModelEntity::ASSIGNMENT &&
            ObjectName.compare(0, 7, "Initial") == 0)))
        return true;

      if ((classes & Time) &&
          Status == CModelEntity::TIME &&
          ObjectName == "Time")
        return true;

      if ((classes & ObservedValues) &&
          ((Status != CModelEntity::TIME &&
            Status != CModelEntity::ASSIGNMENT &&
            (ObjectName.find("Rate") != std::string::npos ||
             ObjectName == "TransitionTime")) ||
           (Status == CModelEntity::ASSIGNMENT &&
            (ObjectName == "Value" ||
             ObjectName == "Volume" ||
             ObjectName == "ParticleNumber" ||
             ObjectName == "Concentration"))))
        return true;
    }

  // Descendants of CReaction need to be check more thoroughly
  const CReaction * pReaction =
    dynamic_cast< const CReaction * >(pCheckedObject->getObjectAncestor("Reaction"));

  if (pReaction)
    {
      if ((classes & Parameters) &&
          pReaction->isLocalParameter(pCheckedObject->getObjectParent()->getObjectName()))
        return true;

      if ((classes & ObservedValues) &&
          ObjectName.find("Flux") != std::string::npos)
        return true;
    }

  const CCopasiTask * pTask =
    dynamic_cast<const CCopasiTask *>(pCheckedObject->getObjectAncestor("Task"));

  if (pTask)
    {
      // TODO we need to filter out non results
      if ((classes & Results) &&
          (pCheckedObject->isValueDbl() ||
           pCheckedObject->isValueInt() ||
           pCheckedObject->isArray()))
        return true;
    }

  // All tests failed
  return false;
}

/*
 * remove all empty subtree
 */
void CCopasiSimpleSelectionTree::removeEmptySubTree(QListViewItem ** ppSubTree)
{
  if ((*ppSubTree)->childCount() == 0)
    pdelete(*ppSubTree);
}
