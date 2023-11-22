// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

#include <QMenu>

#include "copasi/copasi.h"

#include "CQSimpleSelectionTree.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/utilities/CExpressionGenerator.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CDataTimer.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "qtUtilities.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataArray.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/steadystate/CMCAMethod.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/sensitivities/CSensProblem.h"
#include "copasi/timesens/CTimeSensProblem.h"
#include "copasi/tssanalysis/CCSPMethod.h"
#include "copasi/tssanalysis/CTSSATask.h"

CQSimpleSelectionTree::CQSimpleSelectionTree(QWidget *parent)
  : QTreeWidget(parent)
  , mpOutputVector(NULL)
  , mpExpressionGenerator(NULL)
  , mAllowExpressions(false)
{
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setSortingEnabled(true);
  sortByColumn(0, Qt::AscendingOrder);
  setHeaderLabels(QStringList("Sort"));
  setRootIsDecorated(true);
  setSizePolicy(QSizePolicy((QSizePolicy::Policy)7, (QSizePolicy::Policy)7));
  mpInformationSubtree = new QTreeWidgetItem(this, QStringList("Information"));
  mpExpertSubtree = new QTreeWidgetItem(this, QStringList("Expert"));
  mpResultMatrixSubtree = new QTreeWidgetItem(this, QStringList("Results"));
  mpResultSteadyStateSubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Steady State"));
#ifdef WITH_ANALYTICS
  mpResultAnalyticsSubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Analytics"));
#endif // WITH_ANALYTICS
  mpResultSensitivitySubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Sensitivity"));
  mpResultTimeSensitivitySubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Time-Course Sensitivity"));
  mpResultMCASubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Metabolic Control Analysis"));
  mpResultTSSASubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Time Scale Separation Analysis"));
  mpResultLNASubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Linear Noise Approximation"));
  mpResultLyapunovSubtree = new QTreeWidgetItem(mpResultMatrixSubtree, QStringList("Lyapunov Exponents"));
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

  connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem *, int)));

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &QWidget::customContextMenuRequested, this, &CQSimpleSelectionTree::slotCustomContextMenuRequested);
}

/// Destructor
CQSimpleSelectionTree::~CQSimpleSelectionTree()
{}

/*
 * build the population tree
 */
void CQSimpleSelectionTree::populateTree(const CModel *pModel,
    const ObjectClasses & classes)
{
  if (!pModel) return;

  populateInformation(pModel->getObjectDataModel(), classes);

  const CDataObject *pObject;
  QTreeWidgetItem *pItem;
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

  pObject = CObjectInterface::DataObject(pModel->getObjectFromCN(CCommonName("Timer=CPU Time")));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("CPU time"));
      treeItems[pItem] = pObject;
    }

  pObject = CObjectInterface::DataObject(pModel->getObjectFromCN(CCommonName("Timer=Wall Clock Time")));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("real time"));
      treeItems[pItem] = pObject;
    }

  // find all species (aka metabolites) and create items in the metabolite subtree
  const CDataVector<CMetab> &metabolites = pModel->getMetabolites();
  size_t counter;
  size_t maxCount = metabolites.size();

  for (counter = maxCount; counter != 0; --counter)
    {
      const CMetab *metab = &metabolites[counter - 1];
      std::string name = metab->getObjectName();
      bool unique = isMetaboliteNameUnique(name, metabolites);

      if (!unique)
        {
          const CCompartment *comp = metab->getCompartment();

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

      if (metab->getStatus() != CModelEntity::Status::ASSIGNMENT)
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

      if (metab->getStatus() != CModelEntity::Status::ASSIGNMENT)
        {
          pObject = metab->getConcentrationRateReference();

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(mpMetaboliteRateConcentrationSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = pObject;
            }
        }
    }

  // find all reactions and create items in the reaction subtree
  const CDataVectorNS<CReaction> &reactions = pModel->getReactions();
  maxCount = reactions.size();

  for (counter = maxCount; counter != 0; --counter)
    {
      const CReaction *react = &reactions[counter - 1];
      std::string name = "flux(" + react->getObjectName() + ")";
      pObject = static_cast< const CDataObject * >(react->getObject(CCommonName("Reference=Flux")));

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpReactionFluxConcentrationSubtree, QStringList(FROM_UTF8(name)));
          treeItems[pItem] = pObject;
        }

      pObject = static_cast< const CDataObject * >(react->getObject(CCommonName("Reference=ParticleFlux")));

      if (filter(classes, pObject))
        {
          pItem = new QTreeWidgetItem(mpReactionFluxNumberSubtree, QStringList(FROM_UTF8("particle " + name)));
          treeItems[pItem] = pObject;
        }

      // create items for the reaction parameters
      pItem = new QTreeWidgetItem(mpReactionParameterSubtree,
                                  QStringList(FROM_UTF8(react->getObjectName())));
      const CCopasiParameterGroup &Parameters = react->getParameters();
      size_t j;
      size_t numParameters = Parameters.size();

      for (j = numParameters; j != 0; --j)
        {
          const CCopasiParameter *pParameter = Parameters.getParameter(j - 1);

          // We skip local parameters which ar covered by global parameters
          if (!react->isLocalParameter(pParameter->getObjectName()))
            continue;

          pObject = static_cast< const CDataObject * >(pParameter->getObject(CCommonName("Reference=Value")));

          if (filter(classes, pObject))
            {
              QTreeWidgetItem *pParameterItem =
                new QTreeWidgetItem(pItem, QStringList(FROM_UTF8(pParameter->getObjectName())));
              treeItems[pParameterItem] = pObject;
            }
        }

      removeEmptySubTree(&pItem);
    }

  // find all global parameters (aka model values) variables
  const CDataVector<CModelValue> &objects = pModel->getModelValues();
  maxCount = objects.size();

  for (counter = maxCount; counter != 0; --counter)
    {
      const CModelEntity *object = &objects[counter - 1];
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

      if (object->getStatus() != CModelEntity::Status::ASSIGNMENT)
        {
          pObject = object->getRateReference();

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(mpModelQuantityRateSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = pObject;
            }
        }
    }

  // find all compartments
  const CDataVector<CCompartment> &objects2 = pModel->getCompartments();
  maxCount = objects2.size();

  for (counter = maxCount; counter != 0; --counter)
    {
      const CModelEntity *object = &objects2[counter - 1];
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

      if (object->getStatus() != CModelEntity::Status::ASSIGNMENT)
        {
          pObject = object->getRateReference();

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(mpCompartmentRateSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = pObject;
            }
        }
    }

  pObject = static_cast< const CDataObject * >(pModel->getObject(CCommonName("Reference=Avogadro Constant")));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(this, QStringList("Avogadro Constant"));
      treeItems[pItem] = pObject;
    }

  pObject = static_cast< const CDataObject * >(pModel->getObject(CCommonName("Reference=Quantity Conversion Factor")));

  if (filter(classes, pObject))
    {
      pItem = new QTreeWidgetItem(this, QStringList("Quantity Conversion Factor"));
      treeItems[pItem] = pObject;
    }

  // find all model matrices
  const CMatrix<C_FLOAT64> &StoiMatrix = pModel->getStoi();

  if (StoiMatrix.array())
    {
      pObject = static_cast< const CDataObject * >(pModel->getObject(CCommonName("Array=Stoichiometry(ann)")));

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
      pObject = static_cast< const CDataObject * >(pModel->getObject(CCommonName("Array=Reduced stoichiometry(ann)")));

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
      pObject = static_cast< const CDataObject * >(pModel->getObject(CCommonName("Array=Link matrix(ann)")));

      if (filter(classes, pObject))
        {
          //      pItem = new QListViewItem(matrixSubtree, "Link matrix(ann)");
          pItem = new QTreeWidgetItem(mpModelMatrixSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
          treeItems[pItem] = pObject;
        }
    }

  // find all result matrices
  // Metabolic Control Analysis
  CCopasiTask *task;
  CDataModel *pDataModel = pModel->getObjectDataModel();
  assert(pDataModel != NULL);
  // MCA
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Metabolic Control Analysis"));

  try
    {
      if (task && task->updateMatrices())
        {
          //for mca the result is in the method
          CMCAMethod *pMethod = dynamic_cast<CMCAMethod *>(task->getMethod());
          const CDataContainer::objectMap *pObjects = & pMethod->getObjects();
          CDataContainer::objectMap::const_iterator its = pObjects->begin();
          CDataArray *ann;

          for (; its != pObjects->end(); ++its)
            {
              ann = dynamic_cast<CDataArray *>(*its);

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
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Time Scale Separation Analysis"));

  try
    {
      if (task && task->updateMatrices())
        {
          CTSSAMethod *pMethod = dynamic_cast<CTSSAMethod *>(task->getMethod());

          if (pMethod->getSubType() == CTaskEnum::Method::tssCSP)
            {
              const CDataContainer::objectMap *pObjects = & pMethod->getObjects();
              CDataContainer::objectMap::const_iterator its = pObjects->begin();
              CDataArray *ann;

              for (; its != pObjects->end(); ++its)
                {
                  ann = dynamic_cast<CDataArray *>(*its);

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

#ifdef WITH_ANALYTICS
  // ANALYTICS
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Analytics"));

  try
    {
      const CDataContainer::objectMap *pObjects = & task->getObjects();
      CDataContainer::objectMap::const_iterator its = pObjects->begin();

      for (; its != pObjects->end(); ++its)
        {
          const CDataObject *pObject = (const CDataObject *)(*its);
          std::string name = pObject->getObjectName();
          //std::cout << name << "   " << (name.find("Statistics") != std::string::npos) << std::endl;

          if (!pObject) continue;

          if ((name.find("max") != std::string::npos  || name.find("min") != std::string::npos) && filter(classes, pObject)) \
            //if ((name.find("Statistics") != std::string::npos) == 1 && filter(classes, pObject))
            {
              // std::cout << name << std::endl;
              pItem = new QTreeWidgetItem(this->mpResultAnalyticsSubtree, QStringList(FROM_UTF8(name)));
              treeItems[pItem] = pObject;
            }
        }
    }
  catch (...)
    {}

#endif //WITH_ANALYTICS
  // Steady State
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Steady-State"));

  try
    {
      if (task && task->updateMatrices())
        {
          //for steady state the results are in the task
          const CDataContainer::objectMap *pObjects = & task->getObjects();
          CDataContainer::objectMap::const_iterator its = pObjects->begin();
          CDataArray *ann;
          CEigen* pEigen;

          for (; its != pObjects->end(); ++its)
            {
              ann = dynamic_cast<CDataArray *>(*its);

              //if (!ann) continue;
              if (ann && !ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QTreeWidgetItem(this->mpResultSteadyStateSubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                  treeItems[pItem] = ann;
                }

              pEigen = dynamic_cast<CEigen*>(*its); //not the most straight forward way, testing all children

              if (pEigen && (classes & (Results | AnyObject)) && pEigen->getObjectName() == "Eigenvalues of reduced system Jacobian")
                {
                  //add a subtree for all the functions calculated from the reduced jacobian eigenvectors
                  QTreeWidgetItem* pSubtree  = new QTreeWidgetItem(this->mpResultSteadyStateSubtree, QStringList("Properties of reduced model jacobian Eigenvalues"));

                  //loop over children of CEigen object
                  const CDataContainer::objectMap *pO = & pEigen->getObjects();
                  CDataContainer::objectMap::const_iterator itss = pO->begin();

                  for (; itss != pO->end(); ++itss)
                    {
                      if (filter(NumericValues, *itss)) // for now from this specific subtree we only add numeric values.
                        {
                          if ((*itss)->getObjectName(). substr(0, 6) == "Vector")
                            continue;

                          pItem = new QTreeWidgetItem(pSubtree, QStringList(FROM_UTF8((*itss)->getObjectName())));
                          treeItems[pItem] = *itss;
                        }
                    }
                }
            }
        }
    }
  catch (...)
    {}

  // Sensitivities
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Sensitivities"));

  try
    {
      if (task && task->updateMatrices())
        {
          //for sensitivities the result is in the problem
          CSensProblem *sens = dynamic_cast<CSensProblem *>(task->getProblem());
          const CDataContainer::objectMap *pObjects = & sens->getObjects();
          CDataContainer::objectMap::const_iterator its = pObjects->begin();
          CDataArray *ann;

          for (; its != pObjects->end(); ++its)
            {
              ann = dynamic_cast<CDataArray *>(*its);

              if (!ann) continue;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QTreeWidgetItem(this->mpResultSensitivitySubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                  treeItems[pItem] = (CDataObject *) ann;
                }
            }
        }
    }
  catch (...)
    {}

  // Time-Course Sensitivities
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Time-Course Sensitivities"));

  try
    {
      if (task && task->updateMatrices())
        {
          //for sensitivities the result is in the problem
          CTimeSensProblem *sens = dynamic_cast<CTimeSensProblem *>(task->getProblem());
          const CDataContainer::objectMap *pObjects = & sens->getObjects();
          CDataContainer::objectMap::const_iterator its = pObjects->begin();
          CDataArray *ann;

          for (; its != pObjects->end(); ++its)
            {
              ann = dynamic_cast<CDataArray *>(*its);

              if (!ann) continue;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QTreeWidgetItem(this->mpResultTimeSensitivitySubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                  treeItems[pItem] = (CDataObject *) ann;
                }
            }
        }
    }
  catch (...)
    {}

  // LNA
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Linear Noise Approximation"));

  try
    {
      if (task && task->updateMatrices())
        {
          const CDataContainer::objectMap *pObjects = & task->getMethod()->getObjects();
          CDataContainer::objectMap::const_iterator its = pObjects->begin();
          CDataArray *ann;

          for (; its != pObjects->end(); ++its)
            {
              ann = dynamic_cast<CDataArray *>(*its);

              if (!ann) continue;

              if (!ann->isEmpty() && filter(classes, ann))
                {
                  pItem = new QTreeWidgetItem(this->mpResultLNASubtree, QStringList(FROM_UTF8(ann->getObjectName())));
                  treeItems[pItem] = (CDataObject *) ann;
                }
            }
        }
    }
  catch (...)
    {}

  // Lyapunov Exponents
  task = dynamic_cast<CCopasiTask *>(&pDataModel->getTaskList()->operator[]("Lyapunov Exponents"));

  try
    {
      if (task && task->updateMatrices())
        {
          const CDataObject * pObject = static_cast< const CDataObject * >(task->getObject(std::string("Reference=Average divergence")));

          if (filter(classes, pObject))
            {
              pItem = new QTreeWidgetItem(this->mpResultLyapunovSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
              treeItems[pItem] = pObject;
            }

          for (int i = 0; i < 4; ++i)
            {
              std::ostringstream sss;
              sss << "Exponent " << i + 1;

              pObject = static_cast< const CDataObject * >(task->getObject("Reference=" + sss.str()));

              if (filter(classes, pObject))
                {
                  pItem = new QTreeWidgetItem(this->mpResultLyapunovSubtree, QStringList(FROM_UTF8(sss.str())));
                  treeItems[pItem] = pObject;
                }
            }
        }
    }
  catch (...)
    {}

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
              QTreeWidgetItem *parent = (*it)->parent();

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

  removeAllEmptySubTrees();
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

void CQSimpleSelectionTree::populateTree(const std::vector< const CDataObject * > &objectList)
{
  QTreeWidgetItem *pItem;
  // We add all objects to the appropriate subtree;
  std::vector< const CDataObject * >::const_iterator it = objectList.begin();
  std::vector< const CDataObject * >::const_iterator end = objectList.end();
  const CReaction *pReaction = NULL;
  const CMetab *pMetab = NULL;
  const CCompartment *pCompartment = NULL;
  const CModelValue *pModelValue = NULL;
  const CModel *pModel = NULL;
  std::map< const CDataObject *, QTreeWidgetItem * > Object2Subtree;

  // We currently only deal with descendants of the Model.
  for (; it != end; ++it)
    {
      if ((pReaction = static_cast< CReaction * >((*it)->getObjectAncestor("Reaction"))) != NULL)
        {
          std::string name = "flux(" + pReaction->getObjectName() + ")";

          if ((*it) == pReaction->getFluxReference())
            {
              pItem = new QTreeWidgetItem(mpReactionFluxConcentrationSubtree, QStringList(FROM_UTF8(name)));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pReaction->getParticleFluxReference())
            {
              pItem = new QTreeWidgetItem(mpReactionFluxNumberSubtree, QStringList(FROM_UTF8("particle " + name)));
              treeItems[pItem] = *it;
            }
          else
            {
              // We must have a reaction parameter which are in a subtree with the reaction name.
              // 1) Find or Create a subtree
              std::map< const CDataObject *, QTreeWidgetItem * >::iterator Found = Object2Subtree.find(pReaction);

              if (Found == Object2Subtree.end())
                {
                  Found = Object2Subtree.insert(std::make_pair(pReaction,
                                                new QTreeWidgetItem(mpReactionParameterSubtree,
                                                    QStringList(FROM_UTF8(pReaction->getObjectName()))))).first;
                }

              // 2) Add the parameter to the subtree
              pItem = new QTreeWidgetItem(Found->second, QStringList(FROM_UTF8((*it)->getObjectName())));
              treeItems[pItem] = *it;
            }
        }
      else if ((pMetab = static_cast< CMetab * >((*it)->getObjectAncestor("Metabolite"))) != NULL)
        {
          pModel = static_cast< CModel * >(pMetab->getObjectAncestor("Model"));
          std::string name = pMetab->getObjectName();

          if (!isMetaboliteNameUnique(name, pModel->getMetabolites()))
            {
              pCompartment = pMetab->getCompartment();

              if (pCompartment)
                {
                  name = name + "(" + pCompartment->getObjectName() + ")";
                }
            }

          if ((*it) == pMetab->getInitialValueReference())
            {
              pItem = new QTreeWidgetItem(mpMetaboliteInitialNumberSubtree, QStringList(FROM_UTF8(name + "(t=0)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pMetab->getValueReference())
            {
              pItem = new QTreeWidgetItem(mpMetaboliteTransientNumberSubtree, QStringList(FROM_UTF8(name + "(t)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pMetab->getRateReference())
            {
              pItem = new QTreeWidgetItem(mpMetaboliteRateNumberSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pMetab->getInitialConcentrationReference())
            {
              pItem = new QTreeWidgetItem(mpMetaboliteInitialConcentrationSubtree, QStringList(FROM_UTF8("[" + name + "](t=0)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pMetab->getConcentrationReference())
            {
              pItem = new QTreeWidgetItem(mpMetaboliteTransientConcentrationSubtree, QStringList(FROM_UTF8("[" + name + "](t)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pMetab->getConcentrationRateReference())
            {
              pItem = new QTreeWidgetItem(mpMetaboliteRateConcentrationSubtree, QStringList(FROM_UTF8("d([" + name + "])/dt")));
              treeItems[pItem] = *it;
            }
        }
      else if ((pCompartment = static_cast< CCompartment * >((*it)->getObjectAncestor("Compartment"))) != NULL)
        {
          std::string name = pCompartment->getObjectName();

          if ((*it) == pCompartment->getInitialValueReference())
            {
              pItem = new QTreeWidgetItem(mpCompartmentInitialVolumeSubtree, QStringList(FROM_UTF8(name + "(t=0)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pCompartment->getValueReference())
            {
              pItem = new QTreeWidgetItem(mpCompartmentTransientVolumeSubtree, QStringList(FROM_UTF8(name + "(t)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pCompartment->getRateReference())
            {
              pItem = new QTreeWidgetItem(mpCompartmentRateSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = *it;
            }
        }
      else if ((pModelValue = static_cast< CModelValue * >((*it)->getObjectAncestor("ModelValue"))) != NULL)
        {
          std::string name = pModelValue->getObjectName();

          if ((*it) == pModelValue->getInitialValueReference())
            {
              pItem = new QTreeWidgetItem(mpModelQuantityInitialValueSubtree, QStringList(FROM_UTF8(name + "(t=0)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pModelValue->getValueReference())
            {
              pItem = new QTreeWidgetItem(mpModelQuantityTransientValueSubtree, QStringList(FROM_UTF8(name + "(t)")));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pModelValue->getRateReference())
            {
              pItem = new QTreeWidgetItem(mpModelQuantityRateSubtree, QStringList(FROM_UTF8("d(" + name + ")/dt")));
              treeItems[pItem] = *it;
            }
        }
      else if ((pModel = static_cast< CModel * >((*it)->getObjectAncestor("Model"))) != NULL)
        {
          if ((*it) == pModel->getValueReference())
            {
              pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("Model Time"));
              treeItems[pItem] = *it;
            }
          else if ((*it) == pModel->getInitialValueReference())
            {
              pItem = new QTreeWidgetItem(mpTimeSubtree, QStringList("Model Initial Time"));
              treeItems[pItem] = *it;
            }
          else if ((*it)->getObjectType() == "Reaction")
            {
              pItem = new QTreeWidgetItem(mpReactionSubtree, QStringList(FROM_UTF8((*it)->getObjectName())));
              treeItems[pItem] = *it;
            }
          else if ((*it)->getObjectType() == "Metabolite")
            {
              pMetab = static_cast< CMetab * >((*it)->getObjectAncestor("Metabolite"));
              pModel = static_cast< CModel * >(pMetab->getObjectAncestor("Model"));
              std::string name = pMetab->getObjectName();

              if (!isMetaboliteNameUnique(name, pModel->getMetabolites()))
                {
                  pCompartment = pMetab->getCompartment();

                  if (pCompartment)
                    {
                      name = name + "(" + pCompartment->getObjectName() + ")";
                    }
                }

              pItem = new QTreeWidgetItem(mpMetaboliteSubtree, QStringList(FROM_UTF8(name)));
              treeItems[pItem] = *it;
            }
          else if ((*it)->getObjectType() == "Compartment")
            {
              pItem = new QTreeWidgetItem(mpCompartmentSubtree, QStringList(FROM_UTF8((*it)->getObjectName())));
              treeItems[pItem] = *it;
            }
          else if ((*it)->getObjectType() == "ModelValue")
            {
              pItem = new QTreeWidgetItem(mpModelQuantitySubtree, QStringList(FROM_UTF8((*it)->getObjectName())));
              treeItems[pItem] = *it;
            }
        }
    }

  // Remove all empty subtrees
  removeAllEmptySubTrees();
}

void CQSimpleSelectionTree::populateInformation(CDataModel * pDataModel, const ObjectClasses & classes)
{
  /*
    <Object cn="CN=Root,CN=Information,Reference=User Email"/>
    <Object cn="CN=Root,CN=Information,Reference=User Family Name"/>
    <Object cn="CN=Root,CN=Information,Reference=User Given Name"/>
    <Object cn="CN=Root,CN=Information,Reference=User Organization"/>
    <Object cn="CN=Root,CN=Information,Reference=COPASI Version"/>
    <Object cn="CN=Root,CN=Information,Timer=Current Date/Time"/>
    <Object cn="CN=Root,CN=Information,Reference=File Name"/>
  */

  const CDataObject * pObject = CObjectInterface::DataObject(pDataModel->getObject(CCommonName("CN=Information,Reference=User Email")));

  if (filter(classes, pObject))
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem(mpInformationSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
      treeItems[pItem] = pObject;
    }

  pObject = CObjectInterface::DataObject(pDataModel->getObject(CCommonName("CN=Information,Reference=User Family Name")));

  if (filter(classes, pObject))
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem(mpInformationSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
      treeItems[pItem] = pObject;
    }

  pObject = CObjectInterface::DataObject(pDataModel->getObject(CCommonName("CN=Information,Reference=User Given Name")));

  if (filter(classes, pObject))
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem(mpInformationSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
      treeItems[pItem] = pObject;
    }

  pObject = CObjectInterface::DataObject(pDataModel->getObject(CCommonName("CN=Information,Reference=User Organization")));

  if (filter(classes, pObject))
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem(mpInformationSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
      treeItems[pItem] = pObject;
    }

  pObject = CObjectInterface::DataObject(pDataModel->getObject(CCommonName("CN=Information,Reference=COPASI Version")));

  if (filter(classes, pObject))
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem(mpInformationSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
      treeItems[pItem] = pObject;
    }

  pObject = CObjectInterface::DataObject(pDataModel->getObject(CCommonName("CN=Information,Timer=Current Date/Time")));

  if (filter(classes, pObject))
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem(mpInformationSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
      treeItems[pItem] = pObject;
    }

  pObject = CObjectInterface::DataObject(pDataModel->getObject(CCommonName("CN=Information,Reference=File Name")));

  if (filter(classes, pObject))
    {
      QTreeWidgetItem * pItem = new QTreeWidgetItem(mpInformationSubtree, QStringList(FROM_UTF8(pObject->getObjectName())));
      treeItems[pItem] = pObject;
    }
}

void CQSimpleSelectionTree::slotItemDoubleClicked(QTreeWidgetItem * item, int column)
{
  if (!treeHasSelection()) item->setSelected(true);

  if (item->childCount() == 0)
    emit selectionCommitted();
}

void CQSimpleSelectionTree::slotExpressionOperationClicked(QAction* action)
{
  mpExpressionGenerator = new CExpressionGenerator(
    TO_UTF8(action->property("expression_type").toString()),
    TO_UTF8(action->property("object_selection").toString()),
    TO_UTF8(action->text()));
  emit selectionCommitted();
}

void CQSimpleSelectionTree::slotCustomContextMenuRequested(const QPoint & pos)
{
  if (!mAllowExpressions)
    return;

  auto * item = this->itemAt(pos);

  if (item == NULL)
    return;

  auto * parent = item->parent();

  if (parent == NULL)
    return;

  std::string parentsName = TO_UTF8(parent->text(0));

  if (parentsName != "Compartments" && parentsName != "Species" && parentsName != "Reactions" && parentsName != "Global Quantities")
    return;

  std::string name = TO_UTF8(item->text(0));

  QMenu * menu = new QMenu(this);

  menu->setProperty("name", item->text(0));

  for (auto & entry : CExpressionGenerator::getSupportedOperations())
    {
      auto * action = menu->addAction(FROM_UTF8(entry));
      action->setProperty("expression_type", parent->text(0));
      action->setProperty("object_selection", item->text(0));
    }

  menu->popup(this->mapToGlobal(pos));
  connect(menu, &QMenu::triggered, this, &CQSimpleSelectionTree::slotExpressionOperationClicked);
}

std::vector<const CDataObject * > *CQSimpleSelectionTree::getTreeSelection()
{
  std::vector<const CDataObject * > *selection = new std::vector<const CDataObject * >();
  std::map< std::string, const CDataObject * > SelectionMap;

  if (mAllowExpressions && mpExpressionGenerator != NULL)
    {
      selection->push_back(mpExpressionGenerator);
      return selection;
    }

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
      QTreeWidgetItem *currentItem = *it;

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
                  QTreeWidgetItem *tmpItem = *it2;
                  QTreeWidgetItem *Ancestor;

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
      std::vector< const CDataObject * >::iterator itSelection = selection->begin();
      std::map< std::string, const CDataObject * >::const_iterator itSet = SelectionMap.begin();
      std::map< std::string, const CDataObject * >::const_iterator endSet = SelectionMap.end();

      for (; itSet != endSet; ++itSet, ++itSelection)
        *itSelection = itSet->second;
    }

  return selection;
}

bool CQSimpleSelectionTree::isMetaboliteNameUnique(const std::string &name, const CDataVector<CMetab> &metabolites)
{
  bool unique = true;
  bool found = false;
  size_t counter;

  for (counter = 0; counter < metabolites.size(); ++counter)
    {
      const std::string &thisName = metabolites[counter].getObjectName();

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

QTreeWidgetItem *CQSimpleSelectionTree::findListViewItem(const CDataObject *object)
{
  QTreeWidgetItem *item = NULL;
  std::map< QTreeWidgetItem *, const CDataObject * >::iterator it = treeItems.begin();
  std::map< QTreeWidgetItem *, const CDataObject * >::iterator endPos = treeItems.end();

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

void CQSimpleSelectionTree::selectObjects(std::vector< const CDataObject * > *objects)
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
      const CDataObject *object = objects->at(i);
      QTreeWidgetItem *item = findListViewItem(object);

      if (!item && mpExpertSubtree)
        {
          // add the item to the expert branch
          item = new QTreeWidgetItem(mpExpertSubtree,
                                     QStringList(FROM_UTF8(object->getObjectDisplayName())));
          treeItems[item] = object;
        }

      // open the whole branch that contains item.
      QTreeWidgetItem *parent = item->parent();

      if (parent && !(parent->isExpanded()))
        {
          while (parent)
            {
              parent->setExpanded(true);
              parent = parent->parent();
            }
        }

      item->setSelected(true);
    }

  removeEmptySubTree(&mpExpertSubtree);
}

void CQSimpleSelectionTree::commitClicked()
{
  if (mpOutputVector)
    {
      std::vector< const CDataObject * > *treeSelection = getTreeSelection();
      mpOutputVector->assign(treeSelection->begin(), treeSelection->end());
      std::vector< const CDataObject * >::iterator it = mpOutputVector->begin();

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

void CQSimpleSelectionTree::setOutputVector(std::vector< const CDataObject * > *outputVector)
{
  mpOutputVector = outputVector;

  if (mpOutputVector)
    {
      selectObjects(mpOutputVector);
    }
}

void CQSimpleSelectionTree::setAllowExpressions(bool allowExpressions)
{
  mAllowExpressions = allowExpressions;
}

// static
bool CQSimpleSelectionTree::filter(const ObjectClasses &classes, const CDataObject *pObject)
{
  if (pObject == NULL)
    return false;

  if (classes & AnyObject)
    return true;

  // Check whether the value is of the desired numeric type.
  if ((classes & NumericValues) &&
      (pObject->hasFlag(CDataObject::ValueDbl) ||
       pObject->hasFlag(CDataObject::ValueInt) ||
       pObject->hasFlag(CDataObject::ValueInt64) ||
       pObject->hasFlag(CDataObject::Array)))
    return true;

  const CDataObject *pCheckedObject = pObject;

  // Elements of an array are checked as the array itself.
  if (pObject->getObjectParent()->hasFlag(CDataObject::Array))
    pCheckedObject = pObject->getObjectParent();

  const std::string ObjectName = pObject->getObjectName();
  // CModelEntity needs to be check more thoroughly
  const CModelEntity *pEntity =
    dynamic_cast< const CModelEntity * >(pCheckedObject->getObjectParent());

  if (pEntity)
    {
      CModelEntity::Status Status = pEntity->getStatus();

      if ((classes & InitialTime) &&
          Status == CModelEntity::Status::TIME &&
          ObjectName == "Initial Time")
        return true;

      if ((classes & Parameters) &&
          Status != CModelEntity::Status::TIME &&
          Status != CModelEntity::Status::ASSIGNMENT &&
          ObjectName.compare(0, 7, "Initial") == 0 &&
          pEntity->getInitialExpression() == "")
        return true;

      if ((classes & Variables) &&
          Status != CModelEntity::Status::TIME &&
          Status != CModelEntity::Status::ASSIGNMENT &&
          (ObjectName == "Value" ||
           ObjectName == "Volume" ||
           ObjectName == "ParticleNumber" ||
           ObjectName == "Concentration"))
        return true;

      if ((classes & EventTarget) &&
          Status != CModelEntity::Status::TIME &&
          Status != CModelEntity::Status::ASSIGNMENT &&
          (ObjectName == "Value" ||
           ObjectName == "Volume" ||
           ObjectName == "Concentration" ||
           ObjectName == "ParticleNumber"))
        return true;

      if ((classes & ObservedConstants) &&
          ((Status == CModelEntity::Status::TIME &&
            (ObjectName == "Avogadro Constant" ||
             ObjectName == "Quantity Conversion Factor")) ||
           // TODO Until we have not changed to named array elements we do not support matrix elements
           //            || pCheckedObject->hasFlag(CDataObject::Array))) ||
           (Status == CModelEntity::Status::ASSIGNMENT &&
            ObjectName.compare(0, 7, "Initial") == 0) ||
           ((Status == CModelEntity::Status::ODE ||
             Status == CModelEntity::Status::REACTIONS ||
             Status == CModelEntity::Status::FIXED) &&
            ObjectName.compare(0, 7, "Initial") == 0 &&
            pEntity->getInitialExpression() != "")))
        return true;

      if ((classes & Time) &&
          Status == CModelEntity::Status::TIME &&
          ObjectName == "Time")
        return true;

      if ((classes & ObservedValues) &&
          ((Status != CModelEntity::Status::TIME &&
            Status != CModelEntity::Status::ASSIGNMENT &&
            (ObjectName.find("Rate") != std::string::npos ||
             ObjectName == "TransitionTime")) ||
           (Status == CModelEntity::Status::ASSIGNMENT &&
            (ObjectName == "Value" ||
             ObjectName == "Volume" ||
             ObjectName == "ParticleNumber" ||
             ObjectName == "Concentration"))))
        return true;
    }

  // Descendants of CReaction need to be checked more thoroughly
  const CReaction *pReaction =
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

  const CCopasiTask *pTask =
    dynamic_cast<const CCopasiTask *>(pCheckedObject->getObjectAncestor("Task"));

  if (pTask)
    {
      // TODO we need to filter out non results
      if ((classes & Results) &&
          (pCheckedObject->hasFlag(CDataObject::ValueDbl) ||
           pCheckedObject->hasFlag(CDataObject::ValueInt) ||
           pCheckedObject->hasFlag(CDataObject::ValueInt64) ||
           pCheckedObject->hasFlag(CDataObject::Array)))
        return true;
    }

  // All tests failed
  return false;
}

/*
 * remove all empty subtree
 */
void CQSimpleSelectionTree::removeEmptySubTree(QTreeWidgetItem **ppSubTree)
{
  if (ppSubTree != NULL &&
      *ppSubTree != NULL &&
      (*ppSubTree)->childCount() == 0)
    pdelete(*ppSubTree);
}

void CQSimpleSelectionTree::removeAllEmptySubTrees()
{
  removeEmptySubTree(&mpTimeSubtree);
  removeEmptySubTree(&mpMetaboliteInitialNumberSubtree);
  removeEmptySubTree(&mpMetaboliteTransientNumberSubtree);
  removeEmptySubTree(&mpMetaboliteRateNumberSubtree);
  removeEmptySubTree(&mpMetaboliteInitialConcentrationSubtree);
  removeEmptySubTree(&mpMetaboliteTransientConcentrationSubtree);
  removeEmptySubTree(&mpMetaboliteRateConcentrationSubtree);
  removeEmptySubTree(&mpMetaboliteSubtree);
  removeEmptySubTree(&mpReactionFluxNumberSubtree);
  removeEmptySubTree(&mpReactionFluxConcentrationSubtree);
  removeEmptySubTree(&mpReactionParameterSubtree);
  removeEmptySubTree(&mpReactionSubtree);
  removeEmptySubTree(&mpModelQuantityRateSubtree);
  removeEmptySubTree(&mpModelQuantityInitialValueSubtree);
  removeEmptySubTree(&mpModelQuantityTransientValueSubtree);
  removeEmptySubTree(&mpModelQuantitySubtree);
  removeEmptySubTree(&mpCompartmentRateSubtree);
  removeEmptySubTree(&mpCompartmentInitialVolumeSubtree);
  removeEmptySubTree(&mpCompartmentTransientVolumeSubtree);
  removeEmptySubTree(&mpCompartmentSubtree);
  removeEmptySubTree(&mpModelMatrixSubtree);
  removeEmptySubTree(&mpResultMCASubtree);
  removeEmptySubTree(&mpResultTSSASubtree);
  removeEmptySubTree(&mpResultLNASubtree);
  removeEmptySubTree(&mpResultLyapunovSubtree);
  removeEmptySubTree(&mpResultSensitivitySubtree);
  removeEmptySubTree(&mpResultTimeSensitivitySubtree);
  removeEmptySubTree(&mpResultSteadyStateSubtree);
#ifdef WITH_ANALYTICS
  removeEmptySubTree(&mpResultAnalyticsSubtree);
#endif // WITH_ANALYTICS
  removeEmptySubTree(&mpResultMatrixSubtree);
  removeEmptySubTree(&mpTimeSubtree);
  removeEmptySubTree(&mpInformationSubtree);
}
