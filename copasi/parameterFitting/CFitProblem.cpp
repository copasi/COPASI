// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.cpp,v $
//   $Revision: 1.55 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/01 16:59:18 $
// End CVS Header

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
    mpExperimentSet(NULL),
    mExperimentUpdateMethods(0, 0),
    mExperimentConstraints(0, 0),
    mExperimentDependentValues(0),
#ifdef COPASI_CROSSVALIDATION
    mpCrossValidationSet(NULL),
    mCrossValidationUpdateMethods(0, 0),
    mCrossValidationConstraints(0, 0),
    mCrossValidationDependentValues(0),
    mCrossValidationSolutionValue(mInfinity),
    mCrossValidationRMS(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationSD(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationObjective(mInfinity),
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
    mpExperimentSet(NULL),
    mExperimentUpdateMethods(0, 0),
    mExperimentConstraints(0, 0),
    mExperimentDependentValues(src.mExperimentDependentValues),
#ifdef COPASI_CROSSVALIDATION
    mpCrossValidationSet(NULL),
    mCrossValidationUpdateMethods(0, 0),
    mCrossValidationConstraints(0, 0),
    mCrossValidationDependentValues(src.mCrossValidationDependentValues),
    mCrossValidationSolutionValue(mInfinity),
    mCrossValidationRMS(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationSD(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mCrossValidationObjective(mInfinity),
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
  removeParameter("ObjectiveFunction");
  removeParameter("Maximize");

  CCopasiVectorN< CCopasiTask > * pTasks = NULL;
  if (CCopasiDataModel::Global)
    pTasks = CCopasiDataModel::Global->getTaskList();
  if (!pTasks)
    pTasks = dynamic_cast<CCopasiVectorN< CCopasiTask > *>(getObjectAncestor("Vector"));

  if (pTasks)
    {
      unsigned C_INT32 i, imax = pTasks->size();

      if (*mpParmSteadyStateKey == "")
        for (i = 0; i < imax; i++)
          if ((*pTasks)[i]->getType() == CCopasiTask::steadyState)
            {
              *mpParmSteadyStateKey = (*pTasks)[i]->getKey();
              break;
            }

      if (*mpParmTimeCourseKey == "")
        for (i = 0; i < imax; i++)
          if ((*pTasks)[i]->getType() == CCopasiTask::timeCourse)
            {
              *mpParmTimeCourseKey = (*pTasks)[i]->getKey();
              break;
            }
    }

  assertGroup("Experiment Set");

#ifdef COPASI_CROSSVALIDATION
  assertGroup("Cross Validation Set");
#endif // COPASI_CROSSVALIDATION

  elevateChildren();
}

bool CFitProblem::elevateChildren()
{
  // This call is necessarry since CFitProblem is derived from COptProblem.
  if (!COptProblem::elevateChildren()) return false;

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
        {
          if (CCopasiMessage::peekLastMessage().getNumber() == MCOptimization + 7)
            {
              mpSteadyState =
                static_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
              mpSteadyState->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
              mpTrajectory =
                static_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);
              mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
            }

          CCopasiMessage::getLastMessage();
        }

      if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::WARNING &&
          CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        return false;
    }

  std::vector< CCopasiContainer * > ContainerList;
  ContainerList.push_back(mpModel);

  CFitTask * pTask = dynamic_cast<CFitTask *>(getObjectParent());
  if (pTask)
    {
      ContainerList.push_back(pTask);
      ContainerList.push_back(mpSteadyState);
      ContainerList.push_back(mpTrajectory);
    }

  if (!mpExperimentSet->compile(ContainerList)) return false;

  // Build a matrix of experiment and experiment local items.
  mExperimentUpdateMethods.resize(mpExperimentSet->getExperimentCount(),
                                  mpOptItems->size());
  mExperimentUpdateMethods = NULL;
  mExperimentInitialRefreshes.resize(mpExperimentSet->getExperimentCount());

  std::vector< std::set< const CCopasiObject * > > ObjectSet;
  ObjectSet.resize(mpExperimentSet->getExperimentCount());

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  std::vector<COptItem * >::iterator itTmp;

  CFitItem * pItem;
  unsigned C_INT32 i, imax;
  unsigned C_INT32 j;
  unsigned C_INT32 Index;

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
            };
        }

      mpFisherMatrix->setAnnotationString(0, j, Annotation);
      mpFisherMatrix->setAnnotationString(1, j, Annotation);
      mpCorrelationMatrix->setAnnotationString(0, j, Annotation);
      mpCorrelationMatrix->setAnnotationString(1, j, Annotation);
    }

  for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
    mExperimentInitialRefreshes[i] = mpModel->buildInitialRefreshSequence(ObjectSet[i]);

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

  // Build a matrix of cross validation experiments  and local items.
  mCrossValidationUpdateMethods.resize(mpCrossValidationSet->getExperimentCount(),
                                       mpOptItems->size());
  mCrossValidationUpdateMethods = NULL;
  mCrossValidationInitialRefreshes.resize(mpCrossValidationSet->getExperimentCount());

  ObjectSet.clear();
  ObjectSet.resize(mpCrossValidationSet->getExperimentCount());

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
            };
        }
    }

  for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
    mCrossValidationInitialRefreshes[i] = mpModel->buildInitialRefreshSequence(ObjectSet[i]);

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

  mCrossValidationObjective = mInfinity;
  mThresholdCounter = 0;
#endif // COPASI_CROSSVALIDATION

  if (!mpSteadyState)
    {
      mpSteadyState =
        dynamic_cast< CSteadyStateTask * >((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);

      if (mpSteadyState == NULL) fatalError();

      setValue("Steady-State", mpSteadyState->getKey());
      mpSteadyState->initialize(CCopasiTask::NO_OUTPUT, NULL, NULL);
      ContainerList.push_back(mpSteadyState);
    }

  if (!mpTrajectory)
    {
      mpTrajectory =
        dynamic_cast< CTrajectoryTask * >((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);

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

  unsigned i, imax = mpExperimentSet->getExperimentCount();
  unsigned j;
  unsigned kmax;
  mCalculateValue = 0.0;

  CExperiment * pExp = NULL;

  C_FLOAT64 * Residuals = mResiduals.array();
  C_FLOAT64 * DependentValues = mExperimentDependentValues.array();
  UpdateMethod ** pUpdate = mExperimentUpdateMethods.array();
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

          mpModel->setInitialState(*mpInitialState);
          mpModel->updateInitialValues();

          // set the global and experiment local fit item values.
          for (itItem = mpOptItems->begin(); itItem != endItem; itItem++, pUpdate++)
            if (*pUpdate)
              (**pUpdate)(static_cast<CFitItem *>(*itItem)->getLocalValue());

          // Update initial values which changed due to the fit item values.
          itRefresh = mExperimentInitialRefreshes[i].begin();
          endRefresh = mExperimentInitialRefreshes[i].end();
          while (itRefresh != endRefresh)
            (**itRefresh++)();

          kmax = pExp->getNumDataRows();

          switch (pExp->getExperimentType())
            {
            case CCopasiTask::steadyState:
              // set independent data
              for (j = 0; j < kmax && Continue; j++) // For each data row;
                {
                  pExp->updateModelWithIndependentData(j);
                  Continue = mpSteadyState->process(true);

                  if (!Continue)
                    {
                      mFailedCounter++;
                      mCalculateValue = mInfinity;
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
                    if (*ppConstraint) (*ppConstraint)->calculateConstraintViolation();

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
                      // set independent data
                      pExp->updateModelWithIndependentData(j);
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

                  ppConstraintEnd = ppConstraint + mExperimentConstraints.numCols();
                  for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                    if (*ppConstraint) (*ppConstraint)->calculateConstraintViolation();

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
        }
    }

  catch (CCopasiException)
    {
      // We do not want to clog the message cue.
      CCopasiMessage::getLastMessage();

      mFailedCounter++;
      mCalculateValue = mInfinity;
      if (pExp) pExp->restoreModelIndependentData();
    }

  catch (...)
    {
      mFailedCounter++;
      mCalculateValue = mInfinity;
      if (pExp) pExp->restoreModelIndependentData();
    }

  if (isnan(mCalculateValue))
    mCalculateValue = mInfinity;

  if (mpCallBack) return mpCallBack->progress(mhCounter);

  return true;
}

bool CFitProblem::restore(const bool & updateModel)
{
  bool success = COptProblem::restore(updateModel);

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
    os << "Evaluations/Second [1/s]:\t" << mCounter / (C_FLOAT64) (CPUTime.getMilliSeconds() / 1e3) << std::endl;
    os << std::endl;

    std::vector< COptItem * >::const_iterator itItem =
      mpOptItems->begin();
    std::vector< COptItem * >::const_iterator endItem =
      mpOptItems->end();

    CFitItem * pFitItem;
    CExperiment * pExperiment;

    unsigned C_INT32 i, j;

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
                  dynamic_cast< CExperiment * >(GlobalKeys.get(pFitItem->getExperiment(j)));

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

        unsigned C_INT32 k, kmax = mpExperimentSet->getExperimentCount();

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
  unsigned C_INT32 i, imax = mSolutionVariables.size();
  unsigned C_INT32 j, jmax = mExperimentDependentValues.size();
  unsigned C_INT32 l;

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

  // Recalcuate the best solution.
  for (i = 0; i < imax; i++)
    (*mUpdateMethods[i])(mSolutionVariables[i]);

  mStoreResults = true;
  calculate();

  // Keep the results
  CVector< C_FLOAT64 > DependentValues = mExperimentDependentValues;

  if (mSolutionValue == mInfinity)
    return false;

  // The statistics need to be calculated for the result, i.e., now.
  mpExperimentSet->calculateStatistics();

  if (jmax)
    mRMS = sqrt(mSolutionValue / jmax);

  if (jmax > imax)
    mSD = sqrt(mSolutionValue / (jmax - imax));

#ifdef COPASI_CROSSVALIDATION
  calculateCrossValidation();

  mpCrossValidationSet->calculateStatistics();

  unsigned C_INT32 lmax = this->mCrossValidationDependentValues.size();

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
          (*mUpdateMethods[i])(Current * (1.0 + factor));
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

  // This is necessary so that CExperiment::printResult shows the correct data.
  calculate();
  mStoreResults = false;

  if (!CalculateFIM)
    {
      // Make sure the timer is acurate.
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

#ifdef XXXX
  /* int dgetrf_(integer *m,
   *             integer *n,
   *             doublereal *a,
   *             integer * lda,
   *             integer *ipiv,
   *             integer *info)
   *
   *  Purpose
   *  =======
   *
   *  DGETRF computes an LU factorization of a general M-by-N matrix A
   *  using partial pivoting with row interchanges.
   *
   *  The factorization has the form
   *     A = P * L * U
   *  where P is a permutation matrix, L is lower triangular with unit
   *  diagonal elements (lower trapezoidal if m > n), and U is upper
   *  triangular (upper trapezoidal if m < n).
   *
   *  This is the right-looking Level 3 BLAS version of the algorithm.
   *
   *  Arguments
   *  =========
   *
   *  m       (input) INTEGER
   *          The number of rows of the matrix A.  m >= 0.
   *
   *  n       (input) INTEGER
   *          The number of columns of the matrix A.  n >= 0.
   *
   *  a       (input/output) DOUBLE PRECISION array, dimension (lda,n)
   *          On entry, the m by n matrix to be factored.
   *          On exit, the factors L and U from the factorization
   *          A = P*L*U; the unit diagonal elements of L are not stored.
   *
   *  lda     (input) INTEGER
   *          The leading dimension of the array A.  lda >= max(1,m).
   *
   *  ipiv    (output) INTEGER array, dimension (min(m,n))
   *          The pivot indices; for 1 <= i <= min(m,n), row i of the
   *          matrix was interchanged with row ipiv(i).
   *
   *  info    (output) INTEGER
   *          = 0: successful exit
   *          < 0: if info = -k, the k-th argument had an illegal value
   *          > 0: if info = k, U(k,k) is exactly zero. The factorization
   *               has been completed, but the factor U is exactly
   *               singular, and division by zero will occur if it is used
   *               to solve a system of equations.
   */
  C_INT info = 0;
  C_INT N = imax;

  CVector< C_INT > ipiv(imax);

  dgetrf_(&N, &N, mCorrelation.array(), &N, ipiv.array(), &info);
  if (info)
    {
      mCorrelation = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  /* dgetri_(integer *n, doublereal *a, integer *lda, integer *ipiv,
   *         doublereal *work, integer *lwork, integer *info);
   *
   *
   *  Purpose
   *  =======
   *
   *  DGETRI computes the inverse of a matrix using the LU factorization
   *  computed by DGETRF.
   *
   *  This method inverts U and then computes inv(A) by solving the system
   *  inv(A)*L = inv(U) for inv(A).
   *
   *  Arguments
   *  =========
   *
   *  N       (input) INTEGER
   *          The order of the matrix A.  N >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the factors L and U from the factorization
   *          A = P*L*U as computed by DGETRF.
   *          On exit, if INFO = 0, the inverse of the original matrix A.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,N).
   *
   *  IPIV    (input) INTEGER array, dimension (N)
   *          The pivot indices from DGETRF; for 1<=i<=N, row i of the
   *          matrix was interchanged with row IPIV(i).
   *
   *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
   *          On exit, if INFO=0, then WORK(1) returns the optimal LWORK.
   *
   *  LWORK   (input) INTEGER
   *          The dimension of the array WORK.  LWORK >= max(1,N).
   *          For optimal performance LWORK >= N*NB, where NB is
   *          the optimal blocksize returned by ILAENV.
   *
   *          If LWORK = -1, then a workspace query is assumed; the routine
   *          only calculates the optimal size of the WORK array, returns
   *          this value as the first entry of the WORK array, and no error
   *          message related to LWORK is issued by XERBLA.
   *
   *  INFO    (output) INTEGER
   *          = 0:  successful exit
   *          < 0:  if INFO = -i, the i-th argument had an illegal value
   *          > 0:  if INFO = i, U(i,i) is exactly zero; the matrix is
   *                singular and its inverse could not be computed.
   *
   */

  C_INT lwork = -1; // Instruct dgesvd_ to determine work array size.
  CVector< C_FLOAT64 > work;
  work.resize(1);

  dgetri_(&N, mCorrelation.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mCorrelation = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  lwork = (C_INT) work[0];
  work.resize(lwork);

  dgetri_(&N, mCorrelation.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mCorrelation = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

#endif // XXXX

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
  C_INT N = imax;

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

#ifdef XXXX
  // We invert the Fisher information matrix with the help of singular
  // value decomposition.

  /* int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
   *            doublereal *a, integer *lda, doublereal *s, doublereal *u,
   *            integer *ldu, doublereal *vt, integer *ldvt,
   *            doublereal *work, integer *lwork, integer *info);
   *
   *
   *  Purpose
   *  =======
   *
   *  DGESVD computes the singular value decomposition (SVD) of a real
   *  M-by-N matrix A, optionally computing the left and/or right singular
   *  vectors. The SVD is written
   *
   *       A = U * SIGMA * transpose(V)
   *
   *  where SIGMA is an M-by-N matrix which is zero except for its
   *  min(m,n) diagonal elements, U is an M-by-M orthogonal matrix, and
   *  V is an N-by-N orthogonal matrix.  The diagonal elements of SIGMA
   *  are the singular values of A; they are real and non-negative, and
   *  are returned in descending order.  The first min(m,n) columns of
   *  U and V are the left and right singular vectors of A.
   *
   *  Note that the routine returns V**T, not V.
   *
   *  Arguments
   *  =========
   *
   *  JOBU    (input) CHARACTER*1
   *          Specifies options for computing all or part of the matrix U:
   *          = 'A':  all M columns of U are returned in array U:
   *          = 'S':  the first min(m,n) columns of U (the left singular
   *                  vectors) are returned in the array U;
   *          = 'O':  the first min(m,n) columns of U (the left singular
   *                  vectors) are overwritten on the array A;
   *          = 'N':  no columns of U (no left singular vectors) are
   *                  computed.
   *
   *  JOBVT   (input) CHARACTER*1
   *          Specifies options for computing all or part of the matrix
   *          V**T:
   *          = 'A':  all N rows of V**T are returned in the array VT;
   *          = 'S':  the first min(m,n) rows of V**T (the right singular
   *                  vectors) are returned in the array VT;
   *          = 'O':  the first min(m,n) rows of V**T (the right singular
   *                  vectors) are overwritten on the array A;
   *          = 'N':  no rows of V**T (no right singular vectors) are
   *                  computed.
   *
   *          JOBVT and JOBU cannot both be 'O'.
   *
   *  M       (input) INTEGER
   *          The number of rows of the input matrix A.  M >= 0.
   *
   *  N       (input) INTEGER
   *          The number of columns of the input matrix A.  N >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the M-by-N matrix A.
   *          On exit,
   *          if JOBU = 'O', A is overwritten with the first min(m,n)
   *                          columns of U (the left singular vectors,
   *                          stored columnwise);
   *          if JOBVT = 'O', A is overwritten with the first min(m,n)
   *                          rows of V**T (the right singular vectors,
   *                          stored rowwise);
   *          if JOBU .ne. 'O' and JOBVT .ne. 'O', the contents of A
   *                          are destroyed.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,M).
   *
   *  S       (output) DOUBLE PRECISION array, dimension (min(M,N))
   *          The singular values of A, sorted so that S(i) >= S(i+1).
   *
   *  U       (output) DOUBLE PRECISION array, dimension (LDU,UCOL)
   *          (LDU,M) if JOBU = 'A' or (LDU,min(M,N)) if JOBU = 'S'.
   *          If JOBU = 'A', U contains the M-by-M orthogonal matrix U;
   *          if JOBU = 'S', U contains the first min(m,n) columns of U
   *          (the left singular vectors, stored columnwise);
   *          if JOBU = 'N' or 'O', U is not referenced.
   *
   *  LDU     (input) INTEGER
   *          The leading dimension of the array U.  LDU >= 1; if
   *          JOBU = 'S' or 'A', LDU >= M.
   *
   *  VT      (output) DOUBLE PRECISION array, dimension (LDVT,N)
   *          If JOBVT = 'A', VT contains the N-by-N orthogonal matrix
   *          V**T;
   *          if JOBVT = 'S', VT contains the first min(m,n) rows of
   *          V**T (the right singular vectors, stored rowwise);
   *          if JOBVT = 'N' or 'O', VT is not referenced.
   *
   *  LDVT    (input) INTEGER
   *          The leading dimension of the array VT.  LDVT >= 1; if
   *          JOBVT = 'A', LDVT >= N; if JOBVT = 'S', LDVT >= min(M,N).
   *
   *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
   *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK;
   *          if INFO > 0, WORK(2:MIN(M,N)) contains the unconverged
   *          superdiagonal elements of an upper bidiagonal matrix B
   *          whose diagonal is in S (not necessarily sorted). B
   *          satisfies A = U * B * VT, so it has the same singular values
   *          as A, and singular vectors related by U and VT.
   *
   *  LWORK   (input) INTEGER
   *          The dimension of the array WORK.
   *          LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N)).
   *          For good performance, LWORK should generally be larger.
   *
   *          If LWORK = -1, then a workspace query is assumed; the routine
   *          only calculates the optimal size of the WORK array, returns
   *          this value as the first entry of the WORK array, and no error
   *          message related to LWORK is issued by XERBLA.
   *
   *  INFO    (output) INTEGER
   *          = 0:  successful exit.
   *          < 0:  if INFO = -i, the i-th argument had an illegal value.
   *          > 0:  if DBDSQR did not converge, INFO specifies how many
   *                superdiagonals of an intermediate bidiagonal form B
   *                did not converge to zero. See the description of WORK
   *                above for details.
   *
   */

  char job = 'A';
  C_INT info = 0;
  C_INT N = imax;

  CVector< C_FLOAT64 > S(imax);
  CMatrix< C_FLOAT64 > U(imax, imax);
  CMatrix< C_FLOAT64 > VT(imax, imax);

  C_INT lwork = -1; // Instruct dgesvd_ to determine work array size.
  CVector< C_FLOAT64 > work;
  work.resize(1);

  dgesvd_(&job, &job, &N, &N, mCorrelation.array(), &N, S.array(), U.array(),
          &N, VT.array(), &N, work.array(), &lwork, &info);

  if (info)
    {
      mCorrelation = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  lwork = (C_INT) work[0];
  work.resize(lwork);

  // This actually calculates the SVD of mCorrelation^T, since dgesvd uses
  // fortran notation, i.e., mCorrelation = V^T * B^T * U
  dgesvd_(&job, &job, &N, &N, mCorrelation.array(), &N, S.array(), U.array(),
          &N, VT.array(), &N, work.array(), &lwork, &info);

  // Even if info is not zero we are still able to invert
  if (info)
    {
      mCorrelation = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  // Now we invert the Fisher Information Matrix. Please note,
  // that we are calculating a pseudo inverse in the case that one or
  // more singular values are zero.

  mCorrelation = 0.0;
  for (i = 0; i < imax; i++)
    if (S[i] == 0.0)
      mCorrelation(i, i) = 0.0;
    else
      mCorrelation(i, i) = 1.0 / S[i];

  CMatrix< C_FLOAT64 > Tmp(imax, imax);

  char opN = 'N';

  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 0.0;

  dgemm_(&opN, &opN, &N, &N, &N, &Alpha, U.array(), &N,
         mCorrelation.array(), &N, &Beta, Tmp.array(), &N);

  dgemm_(&opN, &opN, &N, &N, &N, &Alpha, Tmp.array(), &N,
         VT.array(), &N, &Beta, mCorrelation.array(), &N);
#endif // XXXX

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
          mParameterSD[i] = mInfinity;
          tmp = 1.0;
          mCorrelation(i, i) = 1.0;
        }
    }

  for (i = 0; i < imax; i++)
    for (l = 0; l < imax; l++)
      mCorrelation(i, l) *= S[i] * S[l];

  // Make sure the timer is acurate.
  (*mCPUTime.getRefresh())();

  return true;
}

const C_FLOAT64 & CFitProblem::getRMS() const
{return mRMS;}

const C_FLOAT64 & CFitProblem::getStdDeviation() const
  {return mSD;}

const CVector< C_FLOAT64 > & CFitProblem::getVariableGradients() const
  {return mGradient;}

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
  C_FLOAT64 * pSolution = mSolutionVariables.array();
  C_FLOAT64 * pSolutionEnd = pSolution + mSolutionVariables.size();

  std::vector<COptItem *>::iterator itConstraint;
  std::vector<COptItem *>::iterator endConstraint = mpConstraintItems->end();

  std::vector< Refresh *>::const_iterator itRefresh;
  std::vector< Refresh *>::const_iterator endRefresh;

  // Reset the constraints memory
  for (itConstraint = mpConstraintItems->begin(); itConstraint != endConstraint; ++itConstraint)
    static_cast<CFitConstraint *>(*itConstraint)->setLocalValue(0.0);

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

          // Update the initial values
          itRefresh = mCrossValidationInitialRefreshes[i].begin();
          endRefresh = mCrossValidationInitialRefreshes[i].end();
          for (; itRefresh != endRefresh; ++itRefresh)
            (**itRefresh)();

          kmax = pExp->getNumDataRows();

          switch (pExp->getExperimentType())
            {
            case CCopasiTask::steadyState:
              // set independent data
              for (j = 0; j < kmax && Continue; j++) // For each data row;
                {
                  pExp->updateModelWithIndependentData(j);
                  Continue &= mpSteadyState->process(true);

                  if (!Continue)
                    {
                      CalculateValue = mInfinity;
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
                    if (*ppConstraint) (*ppConstraint)->checkConstraint();

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
                      // set independent data
                      pExp->updateModelWithIndependentData(j);
                      mpTrajectory->processStart(true);

                      if (pExp->getTimeData()[0] != mpModel->getInitialTime())
                        {
                          mpTrajectory->processStep(pExp->getTimeData()[0]);
                        }
                    }

                  if (mStoreResults)
                    CalculateValue += pExp->sumOfSquaresStore(j, DependentValues);
                  else
                    CalculateValue += pExp->sumOfSquares(j, Residuals);
                }

              // We check after each simulation whether the constraints are violated.
              // Make sure the constraint values are up to date.
              itRefresh = mCrossValidationConstraintRefreshes[i].begin();
              endRefresh = mCrossValidationConstraintRefreshes[i].end();
              for (; itRefresh != endRefresh; ++itRefresh)
                (**itRefresh)();

              ppConstraintEnd = ppConstraint + mCrossValidationConstraints.numCols();
              for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                if (*ppConstraint) (*ppConstraint)->checkConstraint();
              break;

            default:
              break;
            }

          // restore independent data
          pExp->restoreModelIndependentData();
        }
    }

  catch (CCopasiException)
    {
      // We do not want to clog the message cue.
      CCopasiMessage::getLastMessage();

      mFailedCounter++;
      CalculateValue = mInfinity;
      if (pExp) pExp->restoreModelIndependentData();
    }

  catch (...)
    {
      mFailedCounter++;
      CalculateValue = mInfinity;
      if (pExp) pExp->restoreModelIndependentData();
    }

  if (isnan(CalculateValue))
    CalculateValue = mInfinity;

  if (!checkFunctionalConstraints())
    CalculateValue = mInfinity;

  if (mpCallBack)
    Continue &= mpCallBack->progress(mhCounter);

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
