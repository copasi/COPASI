// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CQSimpleSelectionTree.h"
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
#include "report/CCopasiRootContainer.h"
#include "utilities/CAnnotatedMatrix.h"
#include "utilities/CCopasiTask.h"
#include "steadystate/CMCAMethod.h"
#include "steadystate/CSteadyStateTask.h"
#include "sensitivities/CSensProblem.h"
#include "tssanalysis/CCSPMethod.h"
#include "tssanalysis/CTSSATask.h"

CQSimpleSelectionTree::CQSimpleSelectionTree(QWidget* parent):
  QTreeWidget(parent), mpOutputVector(NULL)
{
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setSortingEnabled(true);
  sortByColumn(0, Qt::AscendingOrder);
  setHeaderLabels(QStringList("Sort"));
  setRootIsDecorated(true);
  setSizePolicy(QSizePolicy((QSizePolicy::Policy)7, (QSizePolicy::Policy)7));
  mpExpertSubtree = new QTreeWidgetItem(this, QStringList("Expert"));

  mpResultMatrixSubtree = new QTreeWidgetItem(this, QStringList("Results"));
  mpResultSteadyStateSubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Steady State"));
  mpResultSensitivitySubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Sensitivity"));
  mpResultMCASubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Metabolic Control Analysis"));
  mpResultTSSASubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Time Scale Separation Analysis"));

  mpModelMatrixSubtree = new QTreeWidgetItem(this, QStringList("Matrices"));

  mpModelQuantitySubtree = new QTreeWidgetItem(this, QStringList("Global Quantities"));
  mpModelQuantityRateSubtree =
    new QTreeWidgetItem(mpModelQuantitySubtree, QStringList("Rates"));
  mpModelQuantityTransientValueSubtree =
    new QTreeWidgetItem(mpModelQuantitySubtree, QStringList("Transient Values"));
  mpModelQuantityInitialValueSubtree =
    new QTreeWidgetItem(mpModelQuantitySubtree, QStringList("Initial Values"));

  mpReactionSubtree = new QTreeWidgetItem(this, QStringList("Reactions"));
  mpReactionFluxNumberSubtree =
    new QTreeWidgetItem(mpReactionSubtree, QStringList("Fluxes (Particle Numbers)"));
  mpReactionFluxConcentrationSubtree =
    new QTreeWidgetItem(mpReactionSubtree, QStringList("Fluxes (Amount)"));
  mpReactionParameterSubtree =
    new QTreeWidgetItem(mpReactionSubtree, QStringList("Reaction Parameters"));

  mpMetaboliteSubtree = new QTreeWidgetItem(this, QStringList("Species"));
  mpMetaboliteRateNumberSubtree =
    new QTreeWidgetItem(mpMetaboliteSubtree, QStringList("Rates (Particle Numbers)"));
  mpMetaboliteRateConcentrationSubtree =
    new QTreeWidgetItem(mpMetaboliteSubtree, QStringList("Rates (Concentrations)"));
  mpMetaboliteTransientNumberSubtree =
    new QTreeWidgetItem(mpMetaboliteSubtree, QStringList("Transient Particle Numbers"));
  mpMetaboliteTransientConcentrationSubtree =
    new QTreeWidgetItem(mpMetaboliteSubtree, QStringList("Transient Concentrations"));
  mpMetaboliteInitialNumberSubtree =
    new QTreeWidgetItem(mpMetaboliteSubtree, QStringList("Initial Particle Numbers"));
  mpMetaboliteInitialConcentrationSubtree =
    new QTreeWidgetItem(mpMetaboliteSubtree, QStringList("Initial Concentrations"));

  mpCompartmentSubtree = new QTreeWidgetItem(this, QStringList("Compartments"));
  mpCompartmentRateSubtree =
    new QTreeWidgetItem(mpCompartmentSubtree, QStringList("Rates"));
  mpCompartmentTransientVolumeSubtree =
    new QTreeWidgetItem(mpCompartmentSubtree, QStringList("Transient Volumes"));
  mpCompartmentInitialVolumeSubtree =
    new QTreeWidgetItem(mpCompartmentSubtree, QStringList("Initial Volumes"));

  mpTimeSubtree = new QTreeWidgetItem(this, QStringList("Time"));
}

/// Destructor
CQSimpleSelectionTree::~CQSimpleSelectionTree()
{}

/*
 * build the population tree
 */
void CQSimpleSelectionTree::populateTree(const CModel * pModel,
    const ObjectClasses & classes)
{
  if (!pModel) return;

  const CCopasiObject * pObject;
  QTreeWidgetItem * pItem;

  // find all kinds of time
  pObject = pModel->getValueReference();

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("Model Time"));
      treeItems[pItem] = pObject;
    }

  pObject = pModel->getInitialValueReference();

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("Model Initial Time"));
      treeItems[pItem] = pObject;
    }

  pObject = pModel->getObjectDataModel()->getDataObject(CCopasiObjectName("Timer=CPU Time"));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("CPU time"));
      treeItems[pItem] = pObject;
    }

  pObject = pModel->getObjectDataModel()->getDataObject(CCopasiObjectName("Timer=Wall Clock Time"));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("real time"));
      treeItems[pItem] = pObject;
    }

  removeEmptySubTree(&mpTimeSubtree);

  // find all species (aka metabolites) and create items in the metabolite subtree
  const CCopasiVector<CMetab>& metabolites = pModel->getMetabolites();
  size_t counter;
  size_t maxCount = metabolites.size();

  for (counter = maxCount; counter != 0; --counter)
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

      pObject = metab->getInitialValueReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpMetaboliteInitialNumberSubtree, QStringList(FROM_UTF8(name + "(t=0)")));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getValueReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpMetaboliteTransientNumberSubtree, QStringList(FROM_UTF8(name + "(t)")));
          treeItems[pItem] = pObject;
        }

      if (metab->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = metab->getRateReference();

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(mpMetaboliteRateNumberSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = pObject;
            }
        }

      name = "[" + name + "]"; // Concentration
      pObject = metab->getInitialConcentrationReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpMetaboliteInitialConcentrationSubtree, QStringList(FROM_UTF8(name + "(t=0)")));
          treeItems[pItem] = pObject;
        }

      pObject = metab->getConcentrationReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpMetaboliteTransientConcentrationSubtree, QStringList(FROM_UTF8(name + "(t)")));
          treeItems[pItem] = pObject;
        }

      if (metab->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = metab->getConcentrationRateReference();

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(mpMetaboliteRateConcentrationSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
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

      pObject = static_cast< const CCopasiObject * >(react->getObject(CCopasiObjectName("Reference=Flux")));

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpReactionFluxConcentrationSubtree, QStringList(FROM_UTF8(name)));
          treeItems[pItem] = pObject;
        }

      pObject = static_cast< const CCopasiObject * >(react->getObject(CCopasiObjectName("Reference=ParticleFlux")));

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpReactionFluxNumberSubtree, QStringList(FROM_UTF8("particle " + name)));
          treeItems[pItem] = pObject;
        }

      // create items for the reaction parameters

      pItem = new QTreeWidgetItem(mpReactionParameterSubtree,
                                  QStringList(FROM_UTF8(react->getObjectName())));
      const CCopasiParameterGroup & Parameters = react->getParameters();
      size_t j;
      size_t numParameters = Parameters.size();

      for (j = numParameters; j != 0; --j)
        {
          const CCopasiParameter * pParameter = Parameters.getParameter(j - 1);

          // We skip local parameters which ar covered by global parameters
          if (!react->isLocalParameter(pParameter->getObjectName()))
            continue;

          pObject = static_cast< const CCopasiObject * >(pParameter->getObject(CCopasiObjectName("Reference=Value")));

          if (filter(classes, pObject))
            {
              QTreeWidgetItem * pParameterItem =
                new QTreeWidgetItem(pItem, QStringList(FROM_UTF8(pParameter->getObjectName())));
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

  for (counter = maxCount; counter != 0; --counter)
    {
      const CModelEntity* object = objects[counter - 1];
      std::string name = object->getObjectName();

      pObject = object->getInitialValueReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpModelQuantityInitialValueSubtree, QStringList(FROM_UTF8(name + "(t=0)")));
          treeItems[pItem] = pObject;
        }

      pObject = object->getValueReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpModelQuantityTransientValueSubtree, QStringList(FROM_UTF8(name + "(t)")));
          treeItems[pItem] = pObject;
        }

      if (object->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = object->getRateReference();

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(mpModelQuantityRateSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
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

  for (counter = maxCount; counter != 0; --counter)
    {
      const CModelEntity* object = objects2[counter - 1];
      std::string name = object->getObjectName();

      pObject = object->getInitialValueReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpCompartmentInitialVolumeSubtree, QStringList(FROM_UTF8(name + "(t=0)")));
          treeItems[pItem] = pObject;
        }

      pObject = object->getValueReference();

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpCompartmentTransientVolumeSubtree, QStringList(FROM_UTF8(name + "(t)")));
          treeItems[pItem] = pObject;
        }

      if (object->getStatus() != CModelEntity::ASSIGNMENT)
        {
          pObject = object->getRateReference();

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(mpCompartmentRateSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = pObject;
            }
        }
    }

  removeEmptySubTree(&mpCompartmentRateSubtree);
  removeEmptySubTree(&mpCompartmentInitialVolumeSubtree);
  removeEmptySubTree(&mpCompartmentTransientVolumeSubtree);
  removeEmptySubTree(&mpCompartmentSubtree);

  pObject = static_cast< const CCopasiObject * >(pModel->getObject(CCopasiObjectName("Reference=Avogadro Constant")));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(this, QStringList("Avogadro Constant"));
      treeItems[pItem] = pObject;
    }

  pObject = static_cast< const CCopasiObject * >(pModel->getObject(CCopasiObjectName("Reference=Quantity Conversion Factor")));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(this, QStringList("Quantity Conversion Factor"));
      treeItems[pItem] = pObject;
    }

  // find all model matrices
  const CMatrix<C_FLOAT64> &StoiMatrix = pModel->getStoi();

  if (StoiMatrix.array())
    {
      pObject = static_cast< const CCopasiObject * >(pModel->getObject(CCopasiObjectName("Array=Stoichiometry(ann)")));

      if (filter(classes, pObject))
        {
          //      pItem = new QListViewItem(matrixSubtree, "Stoichiometry(ann)");
          pItem = new QTreeWidgetItem(mpModelMatrixSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
          treeItems[pItem] = pObject;
        }
    }

  const CMatrix<C_FLOAT64> &RedStoiMatrix = pModel->getRedStoi();

  if (RedStoiMatrix.array())
    {
      pObject = static_cast< const CCopasiObject * >(pModel->getObject(CCopasiObjectName("Array=Reduced stoichiometry(ann)")));

      if (filter(classes, pObject))
        {
          //      pItem = new QListViewItem(matrixSubtree, "Reduced stoichiometry(ann)");
          pItem = new QTreeWidgetItem(mpModelMatrixSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
          treeItems[pItem] = pObject;
        }
    }

  const CMatrix<C_FLOAT64> &LinkMatrix = pModel->getL0();

  if (LinkMatrix.array())
    {
      pObject = static_cast< const CCopasiObject * >(pModel->getObject(CCopasiObjectName("Array=Link matrix(ann)")));

      if (filter(classes, pObject))
        {
          //      pItem = new QListViewItem(matrixSubtree, "Link matrix(ann)");
          pItem = new QTreeWidgetItem(mpModelMatrixSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
          treeItems[pItem] = pObject;
        }
    }

  removeEmptySubTree(&mpModelMatrixSubtree);

  // find all result matrices
  // Metabolic Control Analysis
  CCopasiTask *task;
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  // MCA
  task = dynamic_cast<CCopasiTask*>((*pDataModel->getTaskList())["Metabolic Control Analysis"]);

  try
    {
      if (task && task->updateMatrices())
        {
          //for mca the result is in the method
          CMCAMethod* pMethod = dynamic_cast<CMCAMethod *>(task->getMethod());

          const CCopasiContainer::objectMap * pObjects = & pMethod->getObjects();
          CCopasiContainer::objectMap::const_iterator its = pObjects->begin();
          CArrayAnnotation *ann;

          for (; its != pObjects->end(); ++its)
            {
              ann = dynamic_cast<CArrayAnnotation*>(its->second);

              if (!ann) continue;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QTreeWidgetItem(this->mpResultMCASubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                  treeItems[pItem] = ann;
                }
            }
        }
    }
  catch (...)
    {}

// TSSA
  task = dynamic_cast<CCopasiTask*>((*pDataModel->getTaskList())["Time Scale Separation Analysis"]);

  try
    {
      if (task && task->updateMatrices())
        {

          CTSSAMethod* pMethod = dynamic_cast<CTSSAMethod *>(task->getMethod());

          if (pMethod->getSubType() == CTSSAMethod::tssCSP)
            {
              const CCopasiContainer::objectMap * pObjects = & pMethod->getObjects();
              CCopasiContainer::objectMap::const_iterator its = pObjects->begin();
              CArrayAnnotation *ann;

              for (; its != pObjects->end(); ++its)
                {
                  ann = dynamic_cast<CArrayAnnotation*>(its->second);

                  if (!ann) continue;

                  if (ann->getObjectName() == "Fast Participation Index")
                    if (!ann->isEmpty() && filter(classes, ann))
                      {
                        pItem = new QTreeWidgetItem(this->mpResultTSSASubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                        treeItems[pItem] = ann;
                      }

                  if (ann->getObjectName() == "Slow Participation Index")
                    if (!ann->isEmpty() && filter(classes, ann))
                      {
                        pItem = new QTreeWidgetItem(this->mpResultTSSASubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                        treeItems[pItem] = ann;
                      }

                  if (ann->getObjectName() == "Importance Index")
                    if (!ann->isEmpty() && filter(classes, ann))
                      {
                        pItem = new QTreeWidgetItem(this->mpResultTSSASubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                        treeItems[pItem] = ann;
                      }
                }
            }
        }
    }
  catch (...)
    {}

  // Steady State
  task = dynamic_cast<CCopasiTask *>((*pDataModel->getTaskList())["Steady-State"]);

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
              ann = dynamic_cast<CArrayAnnotation*>(its->second);

              if (!ann) continue;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QTreeWidgetItem(this->mpResultSteadyStateSubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                  treeItems[pItem] = ann;
                }
            }
        }
    }
  catch (...)
    {}

  // Sensitivities
  task = dynamic_cast<CCopasiTask *>((*pDataModel->getTaskList())["Sensitivities"]);

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
              ann = dynamic_cast<CArrayAnnotation*>(its->second);

              if (!ann) continue;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QTreeWidgetItem(this->mpResultSensitivitySubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                  treeItems[pItem] = (CCopasiObject *) ann;
                }
            }
        }
    }
  catch (...)
    {}

  removeEmptySubTree(&mpResultMCASubtree);
  removeEmptySubTree(&mpResultTSSASubtree);
  removeEmptySubTree(&mpResultSensitivitySubtree);
  removeEmptySubTree(&mpResultSteadyStateSubtree);
  removeEmptySubTree(&mpResultMatrixSubtree);

  if (selectionMode() == QAbstractItemView::NoSelection)
    {
      // see if some objects are there, if yes set to single selection
      QTreeWidgetItemIterator it(this);

      while (*it)
        {
          if (treeItems.find(*it) != treeItems.end())
            {
              setSelectionMode(QAbstractItemView::SingleSelection);
              setCurrentItem(*it);
              (*it)->setSelected(true);
              QTreeWidgetItem* parent = (*it)->parent();

              while (parent)
                {
                  parent->setExpanded(true);
                  parent = parent->parent();
                }

              break;
            }

          ++it;
        }
    }
}

bool CQSimpleSelectionTree::treeHasSelection()
{
  bool hasSelection = false;
  QTreeWidgetItemIterator it(this);

  while (*it)
    {
      if ((*it)->isSelected())
        {
          hasSelection = true;
          break;
        }

      ++it;
    }

  return hasSelection;
}

std::vector<const CCopasiObject * > * CQSimpleSelectionTree::getTreeSelection()
{
  std::vector<const CCopasiObject * > * selection = new std::vector<const CCopasiObject * >();
  std::map< std::string, const CCopasiObject * > SelectionMap;

  if (selectedItems().isEmpty())
    return selection;

  if (selectionMode() == QAbstractItemView::SingleSelection)
    {
      selection->push_back(treeItems[selectedItems()[0]]);
    }
  else
    {
      // go through the whole tree and check for selected items.
      // if the selected item has children, add all children that are leaves
      // and are connected to an object.
      // If the item is a leave and is connected to an object, add it directly
      QTreeWidgetItemIterator it(this);
      QTreeWidgetItem* currentItem = *it;

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
                  QTreeWidgetItemIterator it2(currentItem);
                  QTreeWidgetItem* tmpItem = *it2;
                  QTreeWidgetItem* Ancestor;

                  while (tmpItem)
                    {
                      if ((tmpItem->childCount() == 0) &&
                          (treeItems.find(tmpItem) != treeItems.end()))
                        SelectionMap[treeItems[tmpItem]->getObjectDisplayName()] = treeItems[tmpItem];

                      ++it2;
                      tmpItem = *it2;

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
          currentItem = *it;
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

bool CQSimpleSelectionTree::isMetaboliteNameUnique(const std::string & name, const CCopasiVector<CMetab> & metabolites)
{
  bool unique = true;
  bool found = false;
  size_t counter;

  for (counter = 0; counter < metabolites.size(); ++counter)
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

QTreeWidgetItem * CQSimpleSelectionTree::findListViewItem(const CCopasiObject * object)
{
  QTreeWidgetItem* item = NULL;
  std::map< QTreeWidgetItem *, const CCopasiObject * >::iterator it = treeItems.begin();
  std::map< QTreeWidgetItem *, const CCopasiObject * >::iterator endPos = treeItems.end();

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

void CQSimpleSelectionTree::selectObjects(std::vector< const CCopasiObject * > * objects)
{
  // clear selection on tree and select new objects
  clearSelection();
  size_t i;
  size_t iMax = objects->size();

  if ((selectionMode() == QAbstractItemView::SingleSelection || selectionMode() == QAbstractItemView::NoSelection) && iMax > 1)
    {
      iMax = 1;
    }

  for (i = 0; i < iMax; ++i)
    {
      const CCopasiObject * object = objects->at(i);
      QTreeWidgetItem* item = findListViewItem(object);

      if (!item && mpExpertSubtree)
        {
          // add the item to the expert branch
          item = new QTreeWidgetItem(mpExpertSubtree,
                                     QStringList(FROM_UTF8(object->getObjectDisplayName())));
          treeItems[item] = object;
        }

      // open the whole branch that contains item.
      QTreeWidgetItem* parent = item->parent();

      if (parent && !(parent->isExpanded()))
        {
          while (parent)
            {
              parent->setExpanded(true);
              parent = parent->parent();
            }
        }

      setCurrentItem(item);
    }

  removeEmptySubTree(&mpExpertSubtree);
}

void CQSimpleSelectionTree::commitClicked()
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

void CQSimpleSelectionTree::setOutputVector(std::vector< const CCopasiObject * > * outputVector)
{
  mpOutputVector = outputVector;

  if (mpOutputVector)
    {
      selectObjects(mpOutputVector);
    }
}

// static
bool CQSimpleSelectionTree::filter(const ObjectClasses & classes, const CCopasiObject * pObject)
{
  if (pObject == NULL)
    return false;

  if (classes & AnyObject)
    return true;

  // Check whether the value is of the desired numeric type.
  if ((classes & NumericValues) &&
      (pObject->isValueDbl() ||
       pObject->isValueInt() ||
       pObject->isValueInt64() ||
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
          ObjectName.compare(0, 7, "Initial") == 0 &&
          pEntity->getInitialExpression() == "")
        return true;

      if ((classes & Variables) &&
          Status != CModelEntity::TIME &&
          Status != CModelEntity::ASSIGNMENT &&
          (ObjectName == "Value" ||
           ObjectName == "Volume" ||
           ObjectName == "ParticleNumber" ||
           ObjectName == "Concentration"))
        return true;

      if ((classes & EventTarget) &&
          Status != CModelEntity::TIME &&
          Status != CModelEntity::ASSIGNMENT &&
          (ObjectName == "Value" ||
           ObjectName == "Volume" ||
           ObjectName == "Concentration"))
        return true;

      if ((classes & ObservedConstants) &&
          ((Status == CModelEntity::TIME &&
            (ObjectName == "Avogadro Constant" ||
             ObjectName == "Quantity Conversion Factor")) ||
           // TODO Until we have not changed to named array elements we do not support matrix elements
           //            || pCheckedObject->isArray())) ||
           (Status == CModelEntity::ASSIGNMENT &&
            ObjectName.compare(0, 7, "Initial") == 0) ||
           ((Status == CModelEntity::ODE ||
             Status == CModelEntity::REACTIONS ||
             Status == CModelEntity::FIXED) &&
            ObjectName.compare(0, 7, "Initial") == 0 &&
            pEntity->getInitialExpression() != "")))
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
           pCheckedObject->isValueInt64() ||
           pCheckedObject->isArray()))
        return true;
    }

  // All tests failed
  return false;
}

/*
 * remove all empty subtree
 */
void CQSimpleSelectionTree::removeEmptySubTree(QTreeWidgetItem ** ppSubTree)
{
  if (ppSubTree != NULL &&
      *ppSubTree != NULL &&
      (*ppSubTree)->childCount() == 0)
    pdelete(*ppSubTree);
}
