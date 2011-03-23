// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.cpp,v $
//   $Revision: 1.66.2.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/23 15:26:25 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CFitProblem.h"
#include "CFitItem.h"
#include "CFitTask.h"
#include "CExperimentSet.h"
#include "CExperiment.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"
#include "utilities/CAnnotatedMatrix.h"

#include "blaswrap.h"           //use blas
#include "clapackwrap.h"        //use CLAPACK

//  Default constructor
CFitProblem::CFitProblem(const CCopasiTask::Type & type,
                         const CCopasiContainer * pParent):
    COptProblem(type, pParent),
    mpParmSteadyStateCN(NULL),
    mpParmTimeCourseCN(NULL),
    mpExperimentSet(NULL),
    mpSteadyState(NULL),
    mpTrajectory(NULL),
    mExperimentUpdateMethods(0, 0),
    mExperimentUndoMethods(0, 0),
    mExperimentConstraints(0, 0),
    mExperimentDependentValues(0),
#ifdef COPASI_CROSSVALIDATION
    mpCrossValidationSet(NULL),
    mCrossValidationUpdateMethods(0, 0),
    mCrossValidationConstraints(0, 0),
    mCrossValidationDependentValues(0),
    mCrossValidationSolutionValue(mWorstValue),
    mCrossValidationRMS(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationSD(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationObjective(mWorstValue),
    mThresholdCounter(0),
#endif // COPASI_CROSSVALIDATION
    mpTrajectoryProblem(NULL),
    mpInitialState(NULL),
    mResiduals(0),
    mRMS(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mSD(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mParameterSD(0),
    mFisher(0, 0),
    mpFisherMatrixInterface(NULL),
    mpFisherMatrix(NULL),
    mCorrelation(0, 0),
    mpCorrelationMatrixInterface(NULL),
    mpCorrelationMatrix(NULL)
{
  initObjects();
  initializeParameter();
}

// copy constructor
CFitProblem::CFitProblem(const CFitProblem& src,
                         const CCopasiContainer * pParent):
    COptProblem(src, pParent),
    mpParmSteadyStateCN(NULL),
    mpParmTimeCourseCN(NULL),
    mpExperimentSet(NULL),
    mpSteadyState(NULL),
    mpTrajectory(NULL),
    mExperimentUpdateMethods(0, 0),
    mExperimentUndoMethods(0, 0),
    mExperimentConstraints(0, 0),
    mExperimentDependentValues(src.mExperimentDependentValues),
#ifdef COPASI_CROSSVALIDATION
    mpCrossValidationSet(NULL),
    mCrossValidationUpdateMethods(0, 0),
    mCrossValidationConstraints(0, 0),
    mCrossValidationDependentValues(src.mCrossValidationDependentValues),
    mCrossValidationSolutionValue(mWorstValue),
    mCrossValidationRMS(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationSD(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationObjective(mWorstValue),
    mThresholdCounter(0),
#endif // COPASI_CROSSVALIDATION
    mpTrajectoryProblem(NULL),
    mpInitialState(NULL),
    mResiduals(src.mResiduals),
    mRMS(src.mRMS),
    mSD(src.mSD),
    mParameterSD(src.mParameterSD),
    mFisher(src.mFisher),
    mpFisherMatrixInterface(NULL),
    mpFisherMatrix(NULL),
    mCorrelation(src.mCorrelation),
    mpCorrelationMatrixInterface(NULL),
    mpCorrelationMatrix(NULL)
{
  initObjects();
  initializeParameter();
}

// Destructor
CFitProblem::~CFitProblem()
{
  pdelete(mpTrajectoryProblem);
  pdelete(mpInitialState);
  pdelete(mpFisherMatrixInterface);
  pdelete(mpFisherMatrix);
  pdelete(mpCorrelationMatrixInterface);
  pdelete(mpCorrelationMatrix);
}

void CFitProblem::initObjects()
{
#ifdef COPASI_CROSSVALIDATION
  addObjectReference("Cross Validation Solution", mCrossValidationSolutionValue, CCopasiObject::ValueDbl);
  addObjectReference("Cross Validation Objective", mCrossValidationObjective, CCopasiObject::ValueDbl);
#endif // COPASI_CROSSVALIDATION

  mpFisherMatrixInterface = new CCopasiMatrixInterface< CMatrix< C_FLOAT64 > >(&mFisher);
  mpFisherMatrix = new CArrayAnnotation("Fisher Information Matrix", this, mpFisherMatrixInterface, false);
  mpFisherMatrix->setDescription("Fisher Information Matrix");
  mpFisherMatrix->setDimensionDescription(0, "Parameters");
  mpFisherMatrix->setDimensionDescription(1, "Parameters");
  mpFisherMatrix->setMode(CArrayAnnotation::STRINGS);

  mpCorrelationMatrixInterface = new CCopasiMatrixInterface< CMatrix< C_FLOAT64 > >(&mCorrelation);
  mpCorrelationMatrix = new CArrayAnnotation("Correlation Matrix", this, mpCorrelationMatrixInterface, false);
  mpCorrelationMatrix->setDescription("Correlation Matrix");
  mpCorrelationMatrix->setDimensionDescription(0, "Parameters");
  mpCorrelationMatrix->setDimensionDescription(1, "Parameters");
  mpCorrelationMatrix->setMode(CArrayAnnotation::STRINGS);
}

void CFitProblem::initializeParameter()
{
  removeParameter("Subtask");
  mpParmSubtaskCN = NULL;
  removeParameter("ObjectiveExpression");
  mpParmObjectiveExpression = NULL;
  *mpParmMaximize = false;

  mpParmSteadyStateCN =
    assertParameter("Steady-State", CCopasiParameter::CN, CCopasiObjectName(""))->getValue().pCN;
  mpParmTimeCourseCN =
    assertParameter("Time-Course", CCopasiParameter::CN, CCopasiObjectName(""))->getValue().pCN;

  assertGroup("Experiment Set");

#ifdef COPASI_CROSSVALIDATION
  assertGroup("Cross Validation Set");
#endif // COPASI_CROSSVALIDATION

  elevateChildren();
}

bool CFitProblem::elevateChildren()
{
  // This call is necessary since CFitProblem is derived from COptProblem.
  if (!COptProblem::elevateChildren()) return false;

  // Due to a naming conflict the following parameters may have been overwritten during
  // the load of a CopasiML file we replace them with default values if that was the case.
  mpParmSteadyStateCN =
    assertParameter("Steady-State", CCopasiParameter::CN, CCopasiObjectName(""))->getValue().pCN;
  mpParmTimeCourseCN =
    assertParameter("Time-Course", CCopasiParameter::CN, CCopasiObjectName(""))->getValue().pCN;

  CCopasiVectorN< CCopasiTask > * pTasks = NULL;
  CCopasiDataModel* pDataModel = getObjectDataModel();

  if (pDataModel)
    pTasks = pDataModel->getTaskList();

  if (pTasks == NULL)
    pTasks = dynamic_cast<CCopasiVectorN< CCopasiTask > *>(getObjectAncestor("Vector"));

  if (pTasks)
    {
      size_t i, imax = pTasks->size();

      if (!mpParmSteadyStateCN->compare(0, 5 , "Task_") ||
          *mpParmSteadyStateCN == "")
        for (i = 0; i < imax; i++)
          if ((*pTasks)[i]->getType() == CCopasiTask::steadyState)
            {
              *mpParmSteadyStateCN = (*pTasks)[i]->getCN();
              break;
            }

      if (!mpParmTimeCourseCN->compare(0, 5 , "Task_") ||
          *mpParmTimeCourseCN == "")
        for (i = 0; i < imax; i++)
          if ((*pTasks)[i]->getType() == CCopasiTask::timeCourse)
            {
              *mpParmTimeCourseCN = (*pTasks)[i]->getCN();
              break;
            }
    }

  std::map<std::string, std::string> ExperimentMap;
  CCopasiParameterGroup * pGroup;
  CExperiment * pExperiment;

  std::vector<CCopasiParameter *> * pExperiments =
    getGroup("Experiment Set")->CCopasiParameter::getValue().pGROUP;
  std::vector<CCopasiParameter *>::iterator itExp;
  std::vector<CCopasiParameter *>::iterator endExp;

  for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
    if ((pGroup = dynamic_cast< CCopasiParameterGroup * >(*itExp)) != NULL &&
        pGroup->getParameter("Key") != NULL)
      ExperimentMap[*pGroup->getValue("Key").pKEY] = (*itExp)->getObjectName();

  mpExperimentSet =
    elevate<CExperimentSet, CCopasiParameterGroup>(getGroup("Experiment Set"));

  if (!mpExperimentSet) return false;

  std::map<std::string, std::string>::iterator itMap;
  std::map<std::string, std::string>::iterator endMap;

  for (itMap = ExperimentMap.begin(), endMap = ExperimentMap.end(); itMap != endMap; ++itMap)
    {
      pExperiment = mpExperimentSet->getExperiment(itMap->second);
      itMap->second = pExperiment->CCopasiParameter::getKey();
      pExperiment->setValue("Key", itMap->second);
    }

#ifdef COPASI_CROSSVALIDATION
  std::map<std::string, std::string> CrossValidationMap;

  pExperiments =
    getGroup("Cross Validation Set")->CCopasiParameter::getValue().pGROUP;

  for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
    if ((pGroup = dynamic_cast< CCopasiParameterGroup * >(*itExp)) != NULL &&
        pGroup->getParameter("Key") != NULL)
      CrossValidationMap[*pGroup->getValue("Key").pKEY] = (*itExp)->getObjectName();

  // This intermediate elevation step should be not needed but Viusal C fails when directly
  // going to the CCrossValidationSet.
  elevate< CExperimentSet, CCopasiParameterGroup >(getGroup("Cross Validation Set"));
  mpCrossValidationSet =
    elevate< CCrossValidationSet, CCopasiParameterGroup >(getGroup("Cross Validation Set"));

  if (!mpCrossValidationSet) return false;

  for (itMap = CrossValidationMap.begin(), endMap = CrossValidationMap.end(); itMap != endMap; ++itMap)
    {
      pExperiment = mpCrossValidationSet->getExperiment(itMap->second);
      itMap->second = pExperiment->CCopasiParameter::getKey();
      pExperiment->setValue("Key", itMap->second);
    }

#endif // COPASI_CROSSVALIDATION

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  for (; it != end; ++it)
    {
      if (!((*it) = elevate<CFitItem, COptItem>(*it)))
        return false;

      pExperiments =
        (*it)->getParameter("Affected Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(ExperimentMap[*(*itExp)->getValue().pKEY]);

#ifdef COPASI_CROSSVALIDATION
      pExperiments =
        (*it)->getParameter("Affected Cross Validation Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(CrossValidationMap[*(*itExp)->getValue().pKEY]);

#endif // COPASI_CROSSVALIDATION
    }

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  for (; it != end; ++it)
    {
      if (!((*it) = elevate<CFitConstraint, COptItem>(*it)))
        return false;

      pExperiments =
        (*it)->getParameter("Affected Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(ExperimentMap[*(*itExp)->getValue().pKEY]);

#ifdef COPASI_CROSSVALIDATION
      pExperiments =
        (*it)->getParameter("Affected Cross Validation Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(CrossValidationMap[*(*itExp)->getValue().pKEY]);

#endif // COPASI_CROSSVALIDATION
    }

  return true;
}

bool CFitProblem::setModel(CModel * pModel)
{return COptProblem::setModel(pModel);}

bool CFitProblem::setCallBack(CProcessReport * pCallBack)
{return COptProblem::setCallBack(pCallBack);}

bool CFitProblem::initialize()
{
  mHaveStatistics = false;

  if (!COptProblem::initialize())
    {
      while (CCopasiMessage::peekLastMessage().getNumber() == MCOptimization + 5 ||
             CCopasiMessage::peekLastMessage().getNumber() == MCOptimization + 7)
        CCopasiMessage::getLastMessage();

      if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::WARNING &&
          CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        return false;
    }

  std::vector< CCopasiContainer * > ContainerList;
  ContainerList.push_back(getObjectAncestor("Vector"));
  CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);
  mpSteadyState =
    dynamic_cast< CSteadyStateTask * >(pDataModel->ObjectFromName(ContainerList, *mpParmSteadyStateCN));

  if (mpSteadyState == NULL)
    mpSteadyState =
      static_cast<CSteadyStateTask *>((*pDataModel->getTaskList())["Steady-State"]);

  // We only need to initialize the steady-state task if steady-state data is present.
  if (mpExperimentSet->hasDataForTaskType(CCopasiTask::steadyState))
    {
      mpSteadyState->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
    }

  mpTrajectory =
    dynamic_cast< CTrajectoryTask * >(pDataModel->ObjectFromName(ContainerList, *mpParmTimeCourseCN));

  if (mpTrajectory == NULL)
    mpTrajectory =
      static_cast<CTrajectoryTask *>((*pDataModel->getTaskList())["Time-Course"]);

  // We only need to initialize the trajectory task if time course data is present.
  if (mpExperimentSet->hasDataForTaskType(CCopasiTask::timeCourse))
    {
      mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
    }

  ContainerList.clear();

  ContainerList.push_back(mpModel);

  CFitTask * pTask = dynamic_cast<CFitTask *>(getObjectParent());

  if (pTask)
    {
      ContainerList.push_back(pTask);
      ContainerList.push_back(mpSteadyState);
      ContainerList.push_back(mpTrajectory);
    }

  if (!mpExperimentSet->compile(ContainerList)) return false;

  // Initialize the object set which the experiment independent objects.
  std::vector< std::set< const CCopasiObject * > > ObjectSet;
  ObjectSet.resize(mpExperimentSet->getExperimentCount());
  size_t i, imax;

  for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
    {
      ObjectSet[i] = mpExperimentSet->getExperiment(i)->getIndependentObjects();
    }

  // Build a matrix of experiment and experiment local items.
  mExperimentUpdateMethods.resize(mpExperimentSet->getExperimentCount(),
                                  mpOptItems->size());
  mExperimentUpdateMethods = NULL;

  // Build a matrix of experiment and experiment local undo items.
  mExperimentUndoMethods.resize(mpExperimentSet->getExperimentCount(),
                                mpOptItems->size());
  mExperimentUndoMethods = NULL;

  mExperimentInitialRefreshes.resize(mpExperimentSet->getExperimentCount());

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  std::vector<COptItem * >::iterator itTmp;

  CFitItem * pItem;
  size_t j;
  size_t Index;

  imax = mSolutionVariables.size();

  mFisher.resize(imax, imax);
  mpFisherMatrix->resize();
  mCorrelation.resize(imax, imax);
  mpCorrelationMatrix->resize();

  for (j = 0; it != end; ++it, j++)
    {
      pItem = static_cast<CFitItem *>(*it);
      pItem->updateBounds(mpOptItems->begin());

      std::string Annotation = pItem->getObjectDisplayName();

      imax = pItem->getExperimentCount();

      if (imax == 0)
        {
          for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
            {
              mExperimentUpdateMethods(i, j) = pItem->COptItem::getUpdateMethod();
              ObjectSet[i].insert(pItem->getObject());
            }
        }
      else
        {
          Annotation += "; {" + pItem->getExperiments() + "}";

          for (i = 0; i < imax; i++)
            {
              if ((Index = mpExperimentSet->keyToIndex(pItem->getExperiment(i))) == C_INVALID_INDEX)
                return false;

              mExperimentUpdateMethods(Index, j) = pItem->COptItem::getUpdateMethod();
              ObjectSet[Index].insert(pItem->getObject());

              // We need to undo the changes for all non affected experiments.
              // We can do that by adding the update method with the current model value to
              mExperimentUndoMethods(Index, j) = pItem->COptItem::getUpdateMethod();
            };
        }

      mpFisherMatrix->setAnnotationString(0, j, Annotation);
      mpFisherMatrix->setAnnotationString(1, j, Annotation);
      mpCorrelationMatrix->setAnnotationString(0, j, Annotation);
      mpCorrelationMatrix->setAnnotationString(1, j, Annotation);
    }

  // Create a joined sequence of update methods for parameters and independent values.
  for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
    {
      mExperimentInitialRefreshes[i] = mpModel->buildInitialRefreshSequence(ObjectSet[i]);
    }

  // Build a matrix of experiment and constraint items;
  mExperimentConstraints.resize(mpExperimentSet->getExperimentCount(),
                                mpConstraintItems->size());
  mExperimentConstraints = NULL;
  mExperimentConstraintRefreshes.resize(mpExperimentSet->getExperimentCount());
  ObjectSet.clear();
  ObjectSet.resize(mpExperimentSet->getExperimentCount());

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  CFitConstraint * pConstraint;
  std::set< const CCopasiObject * >::const_iterator itDepend;
  std::set< const CCopasiObject * >::const_iterator endDepend;

  for (j = 0; it != end; ++it, j++)
    {
      pConstraint = static_cast<CFitConstraint *>(*it);
      itDepend = pConstraint->getDirectDependencies().begin();
      endDepend = pConstraint->getDirectDependencies().end();
      imax = pConstraint->getExperimentCount();

      if (imax == 0)
        {
          for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
            {
              mExperimentConstraints(i, j) = pConstraint;
              ObjectSet[i].insert(itDepend, endDepend);
            }
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpExperimentSet->keyToIndex(pConstraint->getExperiment(i))) == C_INVALID_INDEX)
                return false;

              mExperimentConstraints(Index, j) = pConstraint;
              ObjectSet[Index].insert(itDepend, endDepend);
            };
        }
    }

  for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
    mExperimentConstraintRefreshes[i] = CCopasiObject::buildUpdateSequence(ObjectSet[i], mpModel->getUptoDateObjects());

  mExperimentDependentValues.resize(mpExperimentSet->getDataPointCount());

#ifdef COPASI_CROSSVALIDATION

  if (!mpCrossValidationSet->compile(ContainerList)) return false;

  // Initialize the object set which the experiment independent objects.
  ObjectSet.clear();
  ObjectSet.resize(mpCrossValidationSet->getExperimentCount());

  for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
    {
      ObjectSet[i] = mpCrossValidationSet->getExperiment(i)->getIndependentObjects();
    }

  // Build a matrix of cross validation experiments  and local items.
  mCrossValidationUpdateMethods.resize(mpCrossValidationSet->getExperimentCount(),
                                       mpOptItems->size());
  mCrossValidationUpdateMethods = NULL;

  // Build a matrix of experiment and experiment local undo items.
  mCrossValidationUndoMethods.resize(mpCrossValidationSet->getExperimentCount(),
                                     mpOptItems->size());
  mCrossValidationUndoMethods = NULL;

  mCrossValidationInitialRefreshes.resize(mpCrossValidationSet->getExperimentCount());

  it = mpOptItems->begin();
  end = mpOptItems->end();

  for (j = 0; it != end; ++it, j++)
    {
      pItem = static_cast<CFitItem *>(*it);
      pItem->updateBounds(mpOptItems->begin());

      imax = pItem->getCrossValidationCount();

      if (imax == 0)
        {
          for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
            {
              mCrossValidationUpdateMethods(i, j) = pItem->COptItem::getUpdateMethod();
              ObjectSet[i].insert(pItem->getObject());
            }
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpCrossValidationSet->keyToIndex(pItem->getCrossValidation(i))) == C_INVALID_INDEX)
                return false;

              mCrossValidationUpdateMethods(Index, j) = pItem->COptItem::getUpdateMethod();
              ObjectSet[Index].insert(pItem->getObject());

              // We need to undo the changes for all non affected cross validations.
              // We can do that by adding the update method with the current model value to
              mCrossValidationUndoMethods(Index, j) = pItem->COptItem::getUpdateMethod();
            };
        }
    }

  // Create a joined sequence of update methods for parameters and independent values.
  for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
    {
      mCrossValidationInitialRefreshes[i] = mpModel->buildInitialRefreshSequence(ObjectSet[i]);
    }

  // Build a matrix of cross validation experiments and constraint items;
  mCrossValidationConstraints.resize(mpCrossValidationSet->getExperimentCount(),
                                     mpConstraintItems->size());
  mCrossValidationConstraints = NULL;
  mCrossValidationConstraintRefreshes.resize(mpCrossValidationSet->getExperimentCount());
  ObjectSet.clear();
  ObjectSet.resize(mpCrossValidationSet->getExperimentCount());

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  for (j = 0; it != end; ++it, j++)
    {
      pConstraint = static_cast<CFitConstraint *>(*it);

      imax = pConstraint->getCrossValidationCount();

      if (imax == 0)
        {
          for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
            {
              mCrossValidationConstraints(i, j) = pConstraint;
              ObjectSet[i].insert(pConstraint->getObject());
            }
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpCrossValidationSet->keyToIndex(pConstraint->getCrossValidation(i))) == C_INVALID_INDEX)
                return false;

              mCrossValidationConstraints(Index, j) = pConstraint;
              ObjectSet[Index].insert(pConstraint->getObject());
            };
        }
    }

  for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
    mCrossValidationConstraintRefreshes[i] = CCopasiObject::buildUpdateSequence(ObjectSet[i], mpModel->getUptoDateObjects());

  mCrossValidationDependentValues.resize(mpCrossValidationSet->getDataPointCount());

  mCrossValidationObjective = mWorstValue;
  mThresholdCounter = 0;
#endif // COPASI_CROSSVALIDATION

  if (!mpSteadyState)
    {
      mpSteadyState =
        dynamic_cast< CSteadyStateTask * >((*pDataModel->getTaskList())["Steady-State"]);

      if (mpSteadyState == NULL) fatalError();

      setValue("Steady-State", mpSteadyState->getKey());
      mpSteadyState->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
      ContainerList.push_back(mpSteadyState);
    }

  if (!mpTrajectory)
    {
      mpTrajectory =
        dynamic_cast< CTrajectoryTask * >((*pDataModel->getTaskList())["Time-Course"]);

      if (mpTrajectory == NULL) fatalError();

      setValue("Time-Course", mpTrajectory->getKey());
      mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
      ContainerList.push_back(mpTrajectory);
    }

  pdelete(mpTrajectoryProblem);
  mpTrajectoryProblem =
    new CTrajectoryProblem(*static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem()));

  static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem())->setStepNumber(1);

  pdelete(mpInitialState);
  mpInitialState = new CState(mpModel->getInitialState());

  return true;
}

bool CFitProblem::restoreTrajectoryProblem()
{
  if (mpTrajectoryProblem)
    *mpTrajectory->getProblem() = *mpTrajectoryProblem;

  pdelete(mpTrajectoryProblem);
  pdelete(mpInitialState);

  return true;
}

bool CFitProblem::checkFunctionalConstraints()
{
  std::vector< COptItem * >::const_iterator it = mpConstraintItems->begin();
  std::vector< COptItem * >::const_iterator end = mpConstraintItems->end();

  mConstraintCounter++;

  for (; it != end; ++it)
    if (static_cast<CFitConstraint *>(*it)->getConstraintViolation() > 0.0)
      {
        mFailedConstraintCounter++;
        return false;
      }

  return true;
}

bool CFitProblem::calculate()
{
  mCounter += 1;
  bool Continue = true;

  size_t i, imax = mpExperimentSet->getExperimentCount();
  size_t j;
  size_t kmax;
  mCalculateValue = 0.0;

  CExperiment * pExp = NULL;

  C_FLOAT64 * Residuals = mResiduals.array();
  C_FLOAT64 * DependentValues = mExperimentDependentValues.array();

  UpdateMethod ** pUpdate = mExperimentUpdateMethods.array();
  UpdateMethod ** pUndo =  mExperimentUndoMethods.array();

  std::vector<COptItem *>::iterator itItem;
  std::vector<COptItem *>::iterator endItem = mpOptItems->end();

  std::vector<COptItem *>::iterator itConstraint;
  std::vector<COptItem *>::iterator endConstraint = mpConstraintItems->end();

  std::vector< Refresh *>::const_iterator itRefresh;
  std::vector< Refresh *>::const_iterator endRefresh;

  // Reset the constraints memory
  for (itConstraint = mpConstraintItems->begin(); itConstraint != endConstraint; ++itConstraint)
    static_cast<CFitConstraint *>(*itConstraint)->resetConstraintViolation();

  CFitConstraint **ppConstraint = mExperimentConstraints.array();
  CFitConstraint **ppConstraintEnd;

  try
    {
      for (i = 0; i < imax && Continue; i++) // For each experiment
        {
          pExp = mpExperimentSet->getExperiment(i);

          // Set the model to its original state.
          mpModel->setInitialState(*mpInitialState);
          mpModel->updateInitialValues();

          // set the global and experiment local fit item values.
          for (itItem = mpOptItems->begin(); itItem != endItem; itItem++, pUpdate++)
            if (*pUpdate)
              (**pUpdate)(static_cast<CFitItem *>(*itItem)->getLocalValue());

          kmax = pExp->getNumDataRows();

          switch (pExp->getExperimentType())
            {
              case CCopasiTask::steadyState:

                // set independent data
                for (j = 0; j < kmax && Continue; j++) // For each data row;
                  {
                    pExp->updateModelWithIndependentData(j);

                    // We need to apply the parameter and independent
                    // value updates as one unit.
                    itRefresh = mExperimentInitialRefreshes[i].begin();
                    endRefresh = mExperimentInitialRefreshes[i].end();

                    while (itRefresh != endRefresh)
                      (**itRefresh++)();

                    Continue = mpSteadyState->process(true);

                    if (!Continue)
                      {
                        mFailedCounter++;
                        mCalculateValue = mWorstValue;
                        break;
                      }

                    // We check after each simulation whether the constraints are violated.
                    // Make sure the constraint values are up to date.
                    itRefresh = mExperimentConstraintRefreshes[i].begin();
                    endRefresh = mExperimentConstraintRefreshes[i].end();

                    for (; itRefresh != endRefresh; ++itRefresh)
                      (**itRefresh)();

                    ppConstraint = mExperimentConstraints[i];
                    ppConstraintEnd = ppConstraint + mExperimentConstraints.numCols();

                    for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                      if (*ppConstraint)(*ppConstraint)->calculateConstraintViolation();

                    if (mStoreResults)
                      mCalculateValue += pExp->sumOfSquaresStore(j, DependentValues);
                    else
                      mCalculateValue += pExp->sumOfSquares(j, Residuals);
                  }

                break;

              case CCopasiTask::timeCourse:

                for (j = 0; j < kmax && Continue; j++) // For each data row;
                  {
                    if (j)
                      {
                        mpTrajectory->processStep(pExp->getTimeData()[j]);
                      }
                    else
                      {
                        // Set independent data. A time course only has one set of
                        // independent data.
                        pExp->updateModelWithIndependentData(0);

                        // We need to apply the parameter and independent
                        // value updates as one unit.
                        itRefresh = mExperimentInitialRefreshes[i].begin();
                        endRefresh = mExperimentInitialRefreshes[i].end();

                        while (itRefresh != endRefresh)
                          (**itRefresh++)();

                        mpTrajectory->processStart(true);

                        if (pExp->getTimeData()[0] != mpModel->getInitialTime())
                          {
                            mpTrajectory->processStep(pExp->getTimeData()[0]);
                          }
                      }

                    // We check after each simulation step whether the constraints are violated.
                    // Make sure the constraint values are up to date.
                    itRefresh = mExperimentConstraintRefreshes[i].begin();
                    endRefresh = mExperimentConstraintRefreshes[i].end();

                    for (; itRefresh != endRefresh; ++itRefresh)
                      (**itRefresh)();

                    ppConstraint = mExperimentConstraints[i];
                    ppConstraintEnd = ppConstraint + mExperimentConstraints.numCols();

                    for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                      if (*ppConstraint)(*ppConstraint)->calculateConstraintViolation();

                    if (mStoreResults)
                      mCalculateValue += pExp->sumOfSquaresStore(j, DependentValues);
                    else
                      mCalculateValue += pExp->sumOfSquares(j, Residuals);
                  }

                break;

              default:
                break;
            }

          // restore independent data
          pExp->restoreModelIndependentData();

          // restore experiment local values
          const C_FLOAT64 *pOriginal = mOriginalVariables.array();
          const C_FLOAT64 *pOriginalEnd = pOriginal + mOriginalVariables.size();
          bool RefreshNeeded = false;

          // set the global and experiment local fit item values.
          for (; pOriginal != pOriginalEnd; pOriginal++, pUndo++)
            if (*pUndo)
              {
                (**pUndo)(*pOriginal);
                RefreshNeeded = true;
              }

          if (RefreshNeeded)
            {
              // Update initial values which changed due to the fit item values.
              itRefresh = mExperimentInitialRefreshes[i].begin();
              endRefresh = mExperimentInitialRefreshes[i].end();

              while (itRefresh != endRefresh)
                (**itRefresh++)();
            }
        }
    }

  catch (CCopasiException)
    {
      // We do not want to clog the message cue.
      CCopasiMessage::getLastMessage();

      mFailedCounter++;
      mCalculateValue = mWorstValue;

      if (pExp)
        {
          pExp->restoreModelIndependentData();

          // Update initial values which changed due to the fit item values.
          itRefresh = mExperimentInitialRefreshes[i].begin();
          endRefresh = mExperimentInitialRefreshes[i].end();

          while (itRefresh != endRefresh)
            (**itRefresh++)();
        }
    }

  catch (...)
    {
      mFailedCounter++;
      mCalculateValue = mWorstValue;

      if (pExp)
        {
          pExp->restoreModelIndependentData();
          // Update initial values which changed due to the fit item values.
          itRefresh = mExperimentInitialRefreshes[i].begin();
          endRefresh = mExperimentInitialRefreshes[i].end();

          while (itRefresh != endRefresh)
            (**itRefresh++)();
        }
    }

  if (isnan(mCalculateValue))
    mCalculateValue = mWorstValue;

  if (mpCallBack) return mpCallBack->progressItem(mhCounter);

  return true;
}

bool CFitProblem::restore(const bool & updateModel)
{
  bool success = true;

  if (mpTrajectory != NULL)
    success &= mpTrajectory->restore();

  if (mpSteadyState != NULL)
    success &= mpSteadyState->restore();

  success &= COptProblem::restore(updateModel);

  return success;
}

void CFitProblem::print(std::ostream * ostream) const
{*ostream << *this;}

void CFitProblem::printResult(std::ostream * ostream) const
{
  std::ostream & os = *ostream;

  if (mSolutionVariables.size() == 0)
    {
      return;
    }

  os << "Objective Function Value:\t" << mSolutionValue << std::endl;
  os << "Standard Deviation:\t" << mSD << std::endl;

  CCopasiTimeVariable CPUTime = const_cast<CFitProblem *>(this)->mCPUTime.getElapsedTime();

  os << "Function Evaluations:\t" << mCounter << std::endl;
  os << "CPU Time [s]:\t"
  << CCopasiTimeVariable::LL2String(CPUTime.getSeconds(), 1) << "."
  << CCopasiTimeVariable::LL2String(CPUTime.getMilliSeconds(true), 3) << std::endl;
  os << "Evaluations/Second [1/s]:\t" << mCounter / (C_FLOAT64)(CPUTime.getMilliSeconds() / 1e3) << std::endl;
  os << std::endl;

  std::vector< COptItem * >::const_iterator itItem =
    mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    mpOptItems->end();

  CFitItem * pFitItem;
  CExperiment * pExperiment;

  size_t i, j;

  os << "\tParameter\tValue\tGradient\tStandard Deviation" << std::endl;

  for (i = 0; itItem != endItem; ++itItem, i++)
    {
      os << "\t" << (*itItem)->getObjectDisplayName();
      pFitItem = static_cast<CFitItem *>(*itItem);

      if (pFitItem->getExperimentCount() != 0)
        {
          os << " (";

          for (j = 0; j < pFitItem->getExperimentCount(); j++)
            {
              if (j) os << ", ";

              pExperiment =
                dynamic_cast< CExperiment * >(CCopasiRootContainer::getKeyFactory()->get(pFitItem->getExperiment(j)));

              if (pExperiment)
                os << pExperiment->getObjectName();
            }

          os << ")";
        }

      if (mHaveStatistics)
        {
          os << ":\t" << mSolutionVariables[i];
          os << "\t" << mGradient[i];
          os << "\t" << mParameterSD[i];
        }
      else
        {
          os << ":\t" << std::numeric_limits<C_FLOAT64>::quiet_NaN();
          os << "\t" << std::numeric_limits<C_FLOAT64>::quiet_NaN();
          os << "\t" << std::numeric_limits<C_FLOAT64>::quiet_NaN();
        }

      os << std::endl;
    }

  os << std::endl;

  if (mHaveStatistics)
    {
      os << "Parameter Interdependence:" << std::endl;
      os << "  " << mFisher << std::endl;

      size_t k, kmax = mpExperimentSet->getExperimentCount();

      for (k = 0; k < kmax; k++)
        {
          mpExperimentSet->getExperiment(k)->printResult(ostream);
          os << std::endl;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const CFitProblem & o)
{
  os << "Problem Description:" << std::endl;

  os << "Subtask: " << std::endl;

  if (o.mpSteadyState)
    o.mpSteadyState->getDescription().print(&os);

  if (o.mpTrajectory)
    o.mpTrajectory->getDescription().print(&os);

  if (!o.mpTrajectory && !o.mpSteadyState)
    os << "No Subtask specified.";

  os << std::endl;

  os << "List of Fitting Items:" << std::endl;

  std::vector< COptItem * >::const_iterator itItem =
    o.mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    o.mpOptItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << *static_cast<CFitItem *>(*itItem) << std::endl;

  itItem = o.mpConstraintItems->begin();
  endItem = o.mpConstraintItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << *static_cast<CFitItem *>(*itItem) << std::endl;

  return os;
}

bool CFitProblem::createObjectiveFunction()
{return true;}

bool CFitProblem::setResidualsRequired(const bool & required)
{
  if (required)
    mResiduals.resize(mpExperimentSet->getDataPointCount());
  else
    mResiduals.resize(0);

  return true;
}

const CVector< C_FLOAT64 > & CFitProblem::getResiduals() const
{return mResiduals;}

bool CFitProblem::calculateStatistics(const C_FLOAT64 & factor,
                                      const C_FLOAT64 & resolution)
{
  // Set the current values to the solution values.
  size_t i, imax = mSolutionVariables.size();
  size_t j, jmax = mExperimentDependentValues.size();
  size_t l;

  mRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

#ifdef COPASI_CROSSVALIDATION
  mCrossValidationRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mCrossValidationSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();
#endif // COPASI_CROSSVALIDATION

  mParameterSD.resize(imax);
  mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mGradient.resize(imax);
  mGradient = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  // Recalculate the best solution.
  for (i = 0; i < imax; i++)
    (*mUpdateMethods[i])(mSolutionVariables[i]);

  mStoreResults = true;
  calculate();

  // Make sure the timer is accurate.
  (*mCPUTime.getRefresh())();

  if (mSolutionValue == mWorstValue)
    return false;

  if (*mpParmCalculateStatistics)
    {

      // Keep the results
      CVector< C_FLOAT64 > DependentValues = mExperimentDependentValues;

      // The statistics need to be calculated for the result, i.e., now.
      mpExperimentSet->calculateStatistics();

      if (jmax)
        mRMS = sqrt(mSolutionValue / jmax);

      if (jmax > imax)
        mSD = sqrt(mSolutionValue / (jmax - imax));

#ifdef COPASI_CROSSVALIDATION
      calculateCrossValidation();

      mpCrossValidationSet->calculateStatistics();

      size_t lmax = this->mCrossValidationDependentValues.size();

      if (lmax)
        mCrossValidationRMS = sqrt(mCrossValidationSolutionValue / lmax);

      if (lmax > imax)
        mCrossValidationSD = sqrt(mCrossValidationSolutionValue / (lmax - imax));

#endif // COPASI_CROSSVALIDATION

      mHaveStatistics = true;

      CMatrix< C_FLOAT64 > dyp;
      bool CalculateFIM = true;

      try
        {
          dyp.resize(imax, jmax);
        }

      catch (CCopasiException Exception)
        {
          CalculateFIM = false;
        }

      C_FLOAT64 Current;
      C_FLOAT64 Delta;

      // Calculate the gradient
      for (i = 0; i < imax; i++)
        {
          Current = mSolutionVariables[i];

          if (fabs(Current) > resolution)
            {
              (*mUpdateMethods[i])(Current *(1.0 + factor));
              Delta = 1.0 / (Current * factor);
            }
          else
            {
              (*mUpdateMethods[i])(resolution);
              Delta = 1.0 / resolution;
            }

          calculate();

          mGradient[i] = (mCalculateValue - mSolutionValue) * Delta;

          if (CalculateFIM)
            for (j = 0; j < jmax; j++)
              dyp(i, j) = (mExperimentDependentValues[j] - DependentValues[j]) * Delta;

          // Restore the value
          (*mUpdateMethods[i])(Current);
        }

      if (!CalculateFIM)
        {
          // Make sure the timer is accurate.
          (*mCPUTime.getRefresh())();

          CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 13);
          return false;
        }

      // Construct the fisher information matrix
      for (i = 0; i < imax; i++)
        for (l = 0; l <= i; l++)
          {
            C_FLOAT64 & tmp = mFisher(i, l);

            tmp = 0.0;

            for (j = 0; j < jmax; j++)
              tmp += dyp(i, j) * dyp(l, j);

            tmp *= 2.0;

            if (l != i)
              mFisher(l, i) = tmp;
          }

      mCorrelation = mFisher;

      // The Fisher Information matrix is a symmetric positive semidefinit matrix.

      /* int dpotrf_(char *uplo, integer *n, doublereal *a,
       *             integer *lda, integer *info);
       *
       *
       *  Purpose
       *  =======
       *
       *  DPOTRF computes the Cholesky factorization of a real symmetric
       *  positive definite matrix A.
       *
       *  The factorization has the form
       *     A = U**T * U, if UPLO = 'U', or
       *     A = L  * L**T, if UPLO = 'L',
       *  where U is an upper triangular matrix and L is lower triangular.
       *
       *  This is the block version of the algorithm, calling Level 3 BLAS.
       *
       *  Arguments
       *  =========
       *
       *  UPLO    (input) CHARACTER*1
       *          = 'U':  Upper triangle of A is stored;
       *          = 'L':  Lower triangle of A is stored.
       *
       *  N       (input) INTEGER
       *          The order of the matrix A.  N >= 0.
       *
       *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
       *          On entry, the symmetric matrix A.  If UPLO = 'U', the leading
       *          N-by-N upper triangular part of A contains the upper
       *          triangular part of the matrix A, and the strictly lower
       *          triangular part of A is not referenced.  If UPLO = 'L', the
       *          leading N-by-N lower triangular part of A contains the lower
       *          triangular part of the matrix A, and the strictly upper
       *          triangular part of A is not referenced.
       *
       *          On exit, if INFO = 0, the factor U or L from the Cholesky
       *          factorization A = U**T*U or A = L*L**T.
       *
       *  LDA     (input) INTEGER
       *          The leading dimension of the array A.  LDA >= max(1,N).
       *
       *  INFO    (output) INTEGER
       *          = 0:  successful exit
       *          < 0:  if INFO = -i, the i-th argument had an illegal value
       *          > 0:  if INFO = i, the leading minor of order i is not
       *                positive definite, and the factorization could not be
       *                completed.
       *
       */

      char U = 'U';
      C_INT info = 0;
      C_INT N = (C_INT) imax;

      dpotrf_(&U, &N, mCorrelation.array(), &N, &info);

      if (info)
        {
          mCorrelation = std::numeric_limits<C_FLOAT64>::quiet_NaN();
          mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

          CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 12);

          return false;
        }

      /* int dpotri_(char *uplo, integer *n, doublereal *a,
       *             integer *lda, integer *info);
       *
       *
       *  Purpose
       *  =======
       *
       *  DPOTRI computes the inverse of a real symmetric positive definite
       *  matrix A using the Cholesky factorization A = U**T*U or A = L*L**T
       *  computed by DPOTRF.
       *
       *  Arguments
       *  =========
       *
       *  UPLO    (input) CHARACTER*1
       *          = 'U':  Upper triangle of A is stored;
       *          = 'L':  Lower triangle of A is stored.
       *
       *  N       (input) INTEGER
       *          The order of the matrix A.  N >= 0.
       *
       *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
       *          On entry, the triangular factor U or L from the Cholesky
       *          factorization A = U**T*U or A = L*L**T, as computed by
       *          DPOTRF.
       *          On exit, the upper or lower triangle of the (symmetric)
       *          inverse of A, overwriting the input factor U or L.
       *
       *  LDA     (input) INTEGER
       *          The leading dimension of the array A.  LDA >= max(1,N).
       *
       *  INFO    (output) INTEGER
       *          = 0:  successful exit
       *          < 0:  if INFO = -i, the i-th argument had an illegal value
       *          > 0:  if INFO = i, the (i,i) element of the factor U or L is
       *                zero, and the inverse could not be computed.
       *
       */

      dpotri_(&U, &N, mCorrelation.array(), &N, &info);

      if (info)
        {
          mCorrelation = std::numeric_limits<C_FLOAT64>::quiet_NaN();
          mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

          CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

          return false;
        }

      // Assure that the inverse is completed.

      for (i = 0; i < imax; i++)
        for (l = 0; l < i; l++)
          mCorrelation(l, i) = mCorrelation(i, l);

      CVector< C_FLOAT64 > S(imax);

      // rescale the lower bound of the covariant matrix to have unit diagonal
      for (i = 0; i < imax; i++)
        {
          C_FLOAT64 & tmp = S[i];

          if (mCorrelation(i, i) > 0.0)
            {
              tmp = 1.0 / sqrt(mCorrelation(i, i));
              mParameterSD[i] = mSD / tmp;
            }
          else if (mCorrelation(i, i) < 0.0)
            {
              tmp = 1.0 / sqrt(- mCorrelation(i, i));
              mParameterSD[i] = mSD / tmp;
            }
          else
            {
              mParameterSD[i] = mWorstValue;
              tmp = 1.0;
              mCorrelation(i, i) = 1.0;
            }
        }

      for (i = 0; i < imax; i++)
        for (l = 0; l < imax; l++)
          mCorrelation(i, l) *= S[i] * S[l];

      // This is necessary so that CExperiment::printResult shows the correct data.
      calculate();

      // Make sure the timer is accurate.
      (*mCPUTime.getRefresh())();
    }

  mStoreResults = false;

  return true;
}

const C_FLOAT64 & CFitProblem::getRMS() const
{return mRMS;}

const C_FLOAT64 & CFitProblem::getStdDeviation() const
{return mSD;}

const CVector< C_FLOAT64 > & CFitProblem::getVariableStdDeviations() const
{return mParameterSD;}

CArrayAnnotation & CFitProblem::getFisherInformation() const
{return *mpFisherMatrix;}

CArrayAnnotation & CFitProblem::getCorrelations() const
{return *mpCorrelationMatrix;}

const CExperimentSet & CFitProblem::getExperiementSet() const
{return *mpExperimentSet;}

#ifdef COPASI_CROSSVALIDATION
const CCrossValidationSet & CFitProblem::getCrossValidationSet() const
{return *mpCrossValidationSet;}

bool CFitProblem::setSolution(const C_FLOAT64 & value,
                              const CVector< C_FLOAT64 > & variables)
{
  bool Continue = COptProblem::setSolution(value, variables);

  if (Continue && mpCrossValidationSet->getExperimentCount() > 0)
    Continue = calculateCrossValidation();

  return Continue;
}

const C_FLOAT64 & CFitProblem::getCrossValidationSolutionValue() const
{return mCrossValidationSolutionValue;}

const C_FLOAT64 & CFitProblem::getCrossValidationRMS() const
{return mCrossValidationRMS;}

const C_FLOAT64 & CFitProblem::getCrossValidationSD() const
{return mCrossValidationSD;}

bool CFitProblem::calculateCrossValidation()
{
  mCounter += 1;
  bool Continue = true;

  unsigned i, imax = mpCrossValidationSet->getExperimentCount();
  unsigned j;
  unsigned kmax;
  C_FLOAT64 CalculateValue = 0.0;

  CExperiment * pExp = NULL;

  C_FLOAT64 * Residuals = NULL;
  C_FLOAT64 * DependentValues = mCrossValidationDependentValues.array();

  UpdateMethod ** pUpdate = mCrossValidationUpdateMethods.array();
  UpdateMethod ** pUndo =  mCrossValidationUndoMethods.array();

  C_FLOAT64 * pSolution = mSolutionVariables.array();
  C_FLOAT64 * pSolutionEnd = pSolution + mSolutionVariables.size();

  std::vector<COptItem *>::iterator itConstraint;
  std::vector<COptItem *>::iterator endConstraint = mpConstraintItems->end();

  std::vector< Refresh *>::const_iterator itRefresh;
  std::vector< Refresh *>::const_iterator endRefresh;

  // Reset the constraints memory
  for (itConstraint = mpConstraintItems->begin(); itConstraint != endConstraint; ++itConstraint)
    static_cast<CFitConstraint *>(*itConstraint)->resetConstraintViolation();

  CFitConstraint **ppConstraint = mCrossValidationConstraints.array();
  CFitConstraint **ppConstraintEnd;

  try
    {
      for (i = 0; i < imax && Continue; i++) // For each CrossValidation
        {
          pExp = mpCrossValidationSet->getExperiment(i);

          mpModel->setInitialState(*mpInitialState);
          mpModel->updateInitialValues();

          // set the global and CrossValidation local fit item values.
          for (; pSolution != pSolutionEnd; pSolution++, pUpdate++)
            if (*pUpdate)
              (**pUpdate)(*pSolution);

          kmax = pExp->getNumDataRows();

          switch (pExp->getExperimentType())
            {
              case CCopasiTask::steadyState:

                // set independent data
                for (j = 0; j < kmax && Continue; j++) // For each data row;
                  {
                    pExp->updateModelWithIndependentData(j);

                    // We need to apply the parameter and independent
                    // value updates as one unit.
                    itRefresh = mCrossValidationInitialRefreshes[i].begin();
                    endRefresh = mCrossValidationInitialRefreshes[i].end();

                    for (; itRefresh != endRefresh; ++itRefresh)
                      (**itRefresh)();

                    Continue &= mpSteadyState->process(true);

                    if (!Continue)
                      {
                        CalculateValue = mWorstValue;
                        break;
                      }

                    // We check after each simulation whether the constraints are violated.
                    // Make sure the constraint values are up to date.
                    itRefresh = mCrossValidationConstraintRefreshes[i].begin();
                    endRefresh = mCrossValidationConstraintRefreshes[i].end();

                    for (; itRefresh != endRefresh; ++itRefresh)
                      (**itRefresh)();

                    ppConstraint = mCrossValidationConstraints[i];
                    ppConstraintEnd = ppConstraint + mCrossValidationConstraints.numCols();

                    for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                      if (*ppConstraint)(*ppConstraint)->checkConstraint();

                    if (mStoreResults)
                      CalculateValue += pExp->sumOfSquaresStore(j, DependentValues);
                    else
                      CalculateValue += pExp->sumOfSquares(j, Residuals);
                  }

                break;

              case CCopasiTask::timeCourse:

                for (j = 0; j < kmax && Continue; j++) // For each data row;
                  {
                    if (j)
                      {
                        mpTrajectory->processStep(pExp->getTimeData()[j]);
                      }
                    else
                      {
                        // Set independent data. A time course only has one set of
                        // independent data.
                        pExp->updateModelWithIndependentData(0);

                        // We need to apply the parameter and independent
                        // value updates as one unit.
                        itRefresh = mCrossValidationInitialRefreshes[i].begin();
                        endRefresh = mCrossValidationInitialRefreshes[i].end();

                        for (; itRefresh != endRefresh; ++itRefresh)
                          (**itRefresh)();

                        mpTrajectory->processStart(true);

                        if (pExp->getTimeData()[0] != mpModel->getInitialTime())
                          {
                            mpTrajectory->processStep(pExp->getTimeData()[0]);
                          }
                      }

                    // We check after each simulation whether the constraints are violated.
                    // Make sure the constraint values are up to date.
                    itRefresh = mCrossValidationConstraintRefreshes[i].begin();
                    endRefresh = mCrossValidationConstraintRefreshes[i].end();

                    for (; itRefresh != endRefresh; ++itRefresh)
                      (**itRefresh)();

                    ppConstraintEnd = ppConstraint + mCrossValidationConstraints.numCols();

                    for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                      if (*ppConstraint)(*ppConstraint)->checkConstraint();

                    if (mStoreResults)
                      CalculateValue += pExp->sumOfSquaresStore(j, DependentValues);
                    else
                      CalculateValue += pExp->sumOfSquares(j, Residuals);
                  }

                break;

              default:
                break;
            }

          // restore independent data
          pExp->restoreModelIndependentData();

          // restore experiment local values
          const C_FLOAT64 *pOriginal = mOriginalVariables.array();
          const C_FLOAT64 *pOriginalEnd = pOriginal + mOriginalVariables.size();
          bool RefreshNeeded = false;

          // set the global and experiment local fit item values.
          for (; pOriginal != pOriginalEnd; pOriginal++, pUndo++)
            if (*pUndo)
              {
                (**pUndo)(*pOriginal);
                RefreshNeeded = true;
              }

          if (RefreshNeeded)
            {
              // Update initial values which changed due to the fit item values.
              itRefresh = mCrossValidationInitialRefreshes[i].begin();
              endRefresh = mCrossValidationInitialRefreshes[i].end();

              while (itRefresh != endRefresh)
                (**itRefresh++)();
            }
        }
    }

  catch (CCopasiException)
    {
      // We do not want to clog the message cue.
      CCopasiMessage::getLastMessage();

      mFailedCounter++;
      CalculateValue = mWorstValue;

      if (pExp)
        {
          pExp->restoreModelIndependentData();

          // Update initial values which changed due to the fit item values.
          itRefresh = mCrossValidationInitialRefreshes[i].begin();
          endRefresh = mCrossValidationInitialRefreshes[i].end();

          while (itRefresh != endRefresh)
            (**itRefresh++)();
        }
    }

  catch (...)
    {
      mFailedCounter++;
      CalculateValue = mWorstValue;

      if (pExp)
        {
          pExp->restoreModelIndependentData();

          // Update initial values which changed due to the fit item values.
          itRefresh = mCrossValidationInitialRefreshes[i].begin();
          endRefresh = mCrossValidationInitialRefreshes[i].end();

          while (itRefresh != endRefresh)
            (**itRefresh++)();
        }
    }

  if (isnan(CalculateValue))
    CalculateValue = mWorstValue;

  if (!checkFunctionalConstraints())
    CalculateValue = mWorstValue;

  if (mpCallBack)
    Continue &= mpCallBack->progressItem(mhCounter);

  C_FLOAT64 CurrentObjective =
    (1.0 - mpCrossValidationSet->getWeight()) * mSolutionValue
    + mpCrossValidationSet->getWeight() * CalculateValue * mpCrossValidationSet->getDataPointCount() / mpExperimentSet->getDataPointCount();

  if (CurrentObjective > mCrossValidationObjective)
    mThresholdCounter++;
  else
    {
      mThresholdCounter = 0;
      mCrossValidationObjective = CurrentObjective;
      mCrossValidationSolutionValue = CalculateValue;
    }

  Continue &= (mThresholdCounter < mpCrossValidationSet->getThreshold());

  return Continue;
}
#endif // COPASI_CROSSVALIDATION
