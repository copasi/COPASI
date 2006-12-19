/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.cpp,v $
   $Revision: 1.42 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/19 17:19:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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
    mStoreResults(false),
    mHaveStatistics(false),
    mGradient(0),
    mRMS(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mSD(std::numeric_limits<C_FLOAT64>::quiet_NaN()),
    mParameterSD(0),
    mFisher(0, 0)
{
#ifdef COPASI_CROSSVALIDATION
  initObjects();
#endif // COPASI_CROSSVALIDATION
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
    mStoreResults(src.mStoreResults),
    mHaveStatistics(src.mHaveStatistics),
    mGradient(src.mGradient),
    mRMS(src.mRMS),
    mSD(src.mSD),
    mParameterSD(src.mParameterSD),
    mFisher(src.mFisher)
{
#ifdef COPASI_CROSSVALIDATION
  initObjects();
#endif // COPASI_CROSSVALIDATION
  initializeParameter();
}

// Destructor
CFitProblem::~CFitProblem()
{
  pdelete(mpTrajectoryProblem);
  pdelete(mpInitialState);
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
              mpSteadyState->initialize(CCopasiTask::NO_OUTPUT, NULL);
              mpTrajectory =
                static_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);
              mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL);
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

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  std::vector<COptItem * >::iterator itTmp;

  CFitItem * pItem;
  unsigned C_INT32 i, imax;
  unsigned C_INT32 j;
  unsigned C_INT32 Index;

  for (j = 0; it != end; ++it, j++)
    {
      pItem = static_cast<CFitItem *>(*it);
      pItem->updateBounds(mpOptItems->begin());

      imax = pItem->getExperimentCount();
      if (imax == 0)
        {
          for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
            mExperimentUpdateMethods(i, j) = pItem->COptItem::getUpdateMethod();
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpExperimentSet->keyToIndex(pItem->getExperiment(i))) == C_INVALID_INDEX)
                return false;
              mExperimentUpdateMethods(Index, j) = pItem->COptItem::getUpdateMethod();
            };
        }
    }

  // Build a matrix of experiment and constraint items;
  mExperimentConstraints.resize(mpExperimentSet->getExperimentCount(),
                                mpConstraintItems->size());
  mExperimentConstraints = NULL;

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  CFitConstraint * pConstraint;

  for (j = 0; it != end; ++it, j++)
    {
      pConstraint = static_cast<CFitConstraint *>(*it);

      imax = pConstraint->getExperimentCount();
      if (imax == 0)
        {
          for (i = 0, imax = mpExperimentSet->getExperimentCount(); i < imax; i++)
            mExperimentConstraints(i, j) = pConstraint;
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpExperimentSet->keyToIndex(pConstraint->getExperiment(i))) == C_INVALID_INDEX)
                return false;
              mExperimentConstraints(Index, j) = pConstraint;
            };
        }
    }

  mExperimentDependentValues.resize(mpExperimentSet->getDataPointCount());

#ifdef COPASI_CROSSVALIDATION
  if (!mpCrossValidationSet->compile(ContainerList)) return false;

  // Build a matrix of cross validation experiments  and local items.
  mCrossValidationUpdateMethods.resize(mpCrossValidationSet->getExperimentCount(),
                                       mpOptItems->size());
  mCrossValidationUpdateMethods = NULL;

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
            mCrossValidationUpdateMethods(i, j) = pItem->COptItem::getUpdateMethod();
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpCrossValidationSet->keyToIndex(pItem->getCrossValidation(i))) == C_INVALID_INDEX)
                return false;
              mCrossValidationUpdateMethods(Index, j) = pItem->COptItem::getUpdateMethod();
            };
        }
    }

  // Build a matrix of cross validation experiments and constraint items;
  mCrossValidationConstraints.resize(mpCrossValidationSet->getExperimentCount(),
                                     mpConstraintItems->size());
  mCrossValidationConstraints = NULL;

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  for (j = 0; it != end; ++it, j++)
    {
      pConstraint = static_cast<CFitConstraint *>(*it);

      imax = pConstraint->getCrossValidationCount();
      if (imax == 0)
        {
          for (i = 0, imax = mpCrossValidationSet->getExperimentCount(); i < imax; i++)
            mCrossValidationConstraints(i, j) = pConstraint;
        }
      else
        {
          for (i = 0; i < imax; i++)
            {
              if ((Index = mpCrossValidationSet->keyToIndex(pConstraint->getCrossValidation(i))) == C_INVALID_INDEX)
                return false;
              mCrossValidationConstraints(Index, j) = pConstraint;
            };
        }
    }

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
      mpSteadyState->initialize(CCopasiTask::NO_OUTPUT, NULL);
      ContainerList.push_back(mpSteadyState);
    }

  if (!mpTrajectory)
    {
      mpTrajectory =
        dynamic_cast< CTrajectoryTask * >((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);

      if (mpTrajectory == NULL) fatalError();

      setValue("Time-Course", mpTrajectory->getKey());
      mpTrajectory->initialize(CCopasiTask::NO_OUTPUT, NULL);
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

  for (; it != end; ++it)
    if (static_cast<CFitConstraint *>(*it)->getConstraintViolation() != 0.0)
      return false;

  return true;
}

bool CFitProblem::calculate()
{
  mCounter += 1;
  bool Continue = true;

  unsigned i, imax = mpExperimentSet->getExperimentCount();
  unsigned j, jmax = mpOptItems->size();
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

  // Reset the constraints memory
  for (itConstraint = mpConstraintItems->begin(); itConstraint != endConstraint; ++itConstraint)
    static_cast<CFitConstraint *>(*itConstraint)->setLocalValue(0.0);

  CFitConstraint **ppConstraint = mExperimentConstraints.array();
  CFitConstraint **ppConstraintEnd;

  try
    {
      for (i = 0; i < imax && Continue; i++) // For each experiment
        {
          pExp = mpExperimentSet->getExperiment(i);

          mpModel->setInitialState(*mpInitialState);

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
                  Continue = mpSteadyState->process(true);

                  if (!Continue)
                    {
                      mCalculateValue = mInfinity;
                      break;
                    }

                  // We check after each simulation whether the constraints are violated.
                  ppConstraint = mExperimentConstraints[i];
                  ppConstraintEnd = ppConstraint + mExperimentConstraints.numCols();
                  for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                    if (*ppConstraint) (*ppConstraint)->checkConstraint();

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

                  if (mStoreResults)
                    mCalculateValue += pExp->sumOfSquaresStore(j, DependentValues);
                  else
                    mCalculateValue += pExp->sumOfSquares(j, Residuals);
                }

              // We check after each simulation whether the constraints are violated.
              ppConstraintEnd = ppConstraint + mExperimentConstraints.numCols();
              for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                if (*ppConstraint) (*ppConstraint)->checkConstraint();
              break;

            default:
              break;
            }

          // restore independent data
          pExp->restoreModelIndependentData();

          switch (pExp->getExperimentType())
            {
            case CCopasiTask::steadyState:
              mpSteadyState->restore();
              break;

            case CCopasiTask::timeCourse:
              mpTrajectory->restore();
              break;

            default:
              break;
            }
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
  unsigned C_INT32 k, kmax = mpExperimentSet->getExperimentCount();

  mRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

#ifdef COPASI_CROSSVALIDATION
  mCrossValidationRMS = std::numeric_limits<C_FLOAT64>::quiet_NaN();
  mCrossValidationSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();
#endif // COPASI_CROSSVALIDATION

  mParameterSD.resize(imax);
  mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

  mFisher.resize(imax, imax);
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
  dyp.resize(imax, jmax);

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

      for (j = 0; j < jmax; j++)
        dyp(i, j) = (mExperimentDependentValues[j] - DependentValues[j]) * Delta;

      // Restore the value
      (*mUpdateMethods[i])(Current);
    }

  DebugFile << dyp << std::endl;
  // This is necessary so that CExperiment::printResult shows the correct data.
  calculate();
  mStoreResults = false;

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
  DebugFile << mFisher << std::endl;
  CMatrix< C_FLOAT64 > A(mFisher);

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

  dgetrf_(&N, &N, mFisher.array(), &N, ipiv.array(), &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  DebugFile << "LU Factorization" << std::endl;
  DebugFile << mFisher << std::endl;

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

  dgetri_(&N, mFisher.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  lwork = (C_INT) work[0];
  work.resize(lwork);

  dgetri_(&N, mFisher.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

#ifdef XXXX
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
   *     A = U**T * U,  if UPLO = 'U', or
   *     A = L  * L**T,  if UPLO = 'L',
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

  dpotrf_(&U, &N, mFisher.array(), &N, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  DebugFile << "Cholesky Factorization" << std::endl;
  DebugFile << mFisher << std::endl;

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

  dpotri_(&U, &N, mFisher.array(), &N, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }
#endif // XXXX

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
   *          if JOBU = 'O',  A is overwritten with the first min(m,n)
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
  CMatrix< C_FLOAT64 > Tmp(imax, imax);

  C_INT lwork = -1; // Instruct dgesvd_ to determine work array size.
  CVector< C_FLOAT64 > work;
  work.resize(1);

  dgesvd_(&job, &job, &N, &N, mFisher.array(), &N, S.array(), U.array(),
          &N, VT.array(), &N, work.array(), &lwork, &info);

  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  lwork = (C_INT) work[0];
  work.resize(lwork);

  // This actually calculates the SVD of mFisher^T, since dgesvd uses
  // fortran notation, i.e., mFisher = V^T * B^T * U
  dgesvd_(&job, &job, &N, &N, mFisher.array(), &N, S.array(), U.array(),
          &N, VT.array(), &N, work.array(), &lwork, &info);

  mFisher = 0.0;
  for (i = 0; i < imax; i++)
    mFisher(i, i) = 1.0 / S[i];

  // Even if info is not zero we are still able to invert
  if (info)
    for (i = 1; i < imax; i++)
      mFisher(i - 1, i) = - work[i] * mFisher(i, i) * mFisher(i - 1, i - 1);

  DebugFile << "inv(B)" << std::endl;
  DebugFile << mFisher << std::endl;
  DebugFile << "U" << std::endl;
  DebugFile << U << std::endl;
  DebugFile << "VT" << std::endl;
  DebugFile << VT << std::endl;

  // Now we invert the Fisher Information Matrix. Please note that mFisher
  // now contains B^(-1) therefore we need to compute: VT^T * mFisher * U^T
  // For this we will use dgemm 2 times.

  char opN = 'N';
  char opT = 'T';

  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Beta = 0.0;

  mFisher = 0.0;
  for (i = 0; i < imax; i++)
    mFisher(i, i) = S[i];

  dgemm_(&opN, &opN, &N, &N, &N, &Alpha, U.array(), &N,
         mFisher.array(), &N, &Beta, Tmp.array(), &N);
  DebugFile << Tmp << std::endl;

  dgemm_(&opN, &opN, &N, &N, &N, &Alpha, Tmp.array(), &N,
         VT.array(), &N, &Beta, mFisher.array(), &N);

  DebugFile << "A = VT * B * U" << std::endl;
  DebugFile << mFisher << std::endl;

  mFisher = 0.0;
  for (i = 0; i < imax; i++)
    mFisher(i, i) = 1.0 / S[i];

  dgemm_(&opT, &opN, &N, &N, &N, &Alpha, VT.array(), &N,
         mFisher.array(), &N, &Beta, Tmp.array(), &N);
  DebugFile << Tmp << std::endl;

  dgemm_(&opN, &opT, &N, &N, &N, &Alpha, Tmp.array(), &N,
         U.array(), &N, &Beta, mFisher.array(), &N);

  DebugFile << "inv(A) = inv(U) * inv(B) * inv(VT)" << std::endl;
  DebugFile << mFisher << std::endl;

  mFisher = 0.0;
  for (i = 0; i < imax; i++)
    mFisher(i, i) = sqrt(1.0 / S[i]);

  dgemm_(&opN, &opN, &N, &N, &N, &Alpha, U.array(), &N,
         mFisher.array(), &N, &Beta, Tmp.array(), &N);
  DebugFile << Tmp << std::endl;

  dgemm_(&opN, &opT, &N, &N, &N, &Alpha, Tmp.array(), &N,
         Tmp.array(), &N, &Beta, mFisher.array(), &N);

  DebugFile << "inv(A) = (sqrt(inv(B)) * inv(U))^T * sqrt(inv(B)) * inv(U)" << std::endl;
  DebugFile << mFisher << std::endl;
#endif // XXXX

#ifdef XXXX
  // This has numericl problems
  /* We use dsytrf_ and dsytri_ to invert the symmetric fisher information matrix */

  /* int dsytrf_(char *uplo,
   *             integer *n,
   *             doublereal *a,
   *             integer * lda,
   *             integer *ipiv,
   *             doublereal *work,
   *             integer *lwork,
   *             integer *info);
   *
   *  -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     June 30, 1999
   *
   *  Purpose
   *  =======
   *
   *  DSYTRF computes the factorization of a real symmetric matrix A using
   *  the Bunch-Kaufman diagonal pivoting method.  The form of the
   *  factorization is
   *
   *     A = U*D*U**T  or  A = L*D*L**T
   *
   *  where U (or L) is a product of permutation and unit upper (lower)
   *  triangular matrices, and D is symmetric and block diagonal with
   *  1-by-1 and 2-by-2 diagonal blocks.
   *
   *  This is the blocked version of the algorithm, calling Level 3 BLAS.
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
   *          On exit, the block diagonal matrix D and the multipliers used
   *          to obtain the factor U or L (see below for further details).
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,N).
   *
   *  IPIV    (output) INTEGER array, dimension (N)
   *          Details of the interchanges and the block structure of D.
   *          If IPIV(k) > 0, then rows and columns k and IPIV(k) were
   *          interchanged and D(k,k) is a 1-by-1 diagonal block.
   *          If UPLO = 'U' and IPIV(k) = IPIV(k-1) < 0, then rows and
   *          columns k-1 and -IPIV(k) were interchanged and D(k-1:k,k-1:k)
   *          is a 2-by-2 diagonal block.  If UPLO = 'L' and IPIV(k) =
   *          IPIV(k+1) < 0, then rows and columns k+1 and -IPIV(k) were
   *          interchanged and D(k:k+1,k:k+1) is a 2-by-2 diagonal block.
   *
   *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK)
   *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
   *
   *  LWORK   (input) INTEGER
   *          The length of WORK.  LWORK >=1.  For best performance
   *          LWORK >= N*NB, where NB is the block size returned by ILAENV.
   *
   *          If LWORK = -1, then a workspace query is assumed; the routine
   *          only calculates the optimal size of the WORK array, returns
   *          this value as the first entry of the WORK array, and no error
   *          message related to LWORK is issued by XERBLA.
   *
   *  INFO    (output) INTEGER
   *          = 0:  successful exit
   *          < 0:  if INFO = -i, the i-th argument had an illegal value
   *          > 0:  if INFO = i, D(i,i) is exactly zero.  The factorization
   *                has been completed, but the block diagonal matrix D is
   *                exactly singular, and division by zero will occur if it
   *                is used to solve a system of equations.
   *
   *  Further Details
   *  ===============
   *
   *  If UPLO = 'U', then A = U*D*U', where
   *     U = P(n)*U(n)* ... *P(k)U(k)* ...,
   *  i.e., U is a product of terms P(k)*U(k), where k decreases from n to
   *  1 in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1
   *  and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as
   *  defined by IPIV(k), and U(k) is a unit upper triangular matrix, such
   *  that if the diagonal block D(k) is of order s (s = 1 or 2), then
   *
   *             (I    v    0)   k-s
   *     U(k) =  (0    I    0)   s
   *             (0    0    I)   n-k
   *             k-s   s   n-k
   *
   *  If s = 1, D(k) overwrites A(k,k), and v overwrites A(1:k-1,k).
   *  If s = 2, the upper triangle of D(k) overwrites A(k-1,k-1), A(k-1,k),
   *  and A(k,k), and v overwrites A(1:k-2,k-1:k).
   *
   *  If UPLO = 'L', then A = L*D*L', where
   *     L = P(1)*L(1)* ... *P(k)*L(k)* ...,
   *  i.e., L is a product of terms P(k)*L(k), where k increases from 1 to
   *  n in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1
   *  and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as
   *  defined by IPIV(k), and L(k) is a unit lower triangular matrix, such
   *  that if the diagonal block D(k) is of order s (s = 1 or 2), then
   *
   *             (I    0     0)  k-1
   *     L(k) =  (0    I     0)  s
   *             (0    v     I)  n-k-s+1
   *                k-1   s  n-k-s+1
   *
   *  If s = 1, D(k) overwrites A(k,k), and v overwrites A(k+1:n,k).
   *  If s = 2, the lower triangle of D(k) overwrites A(k,k), A(k+1,k),
   *  and A(k+1,k+1), and v overwrites A(k+2:n,k:k+1).
   *
   */

  char U = 'U';
  C_INT info = 0;
  C_INT N = imax;

  CVector< C_INT > ipiv;
  ipiv.resize(imax);

  C_INT lwork = -1; // Instruct dsytrf_ to determine work array size.
  CVector< C_FLOAT64 > work;
  work.resize(1);

  dsytrf_(&U, &N, mFisher.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 1, info);

      return false;
    }

  lwork = (C_INT) work[0];
  work.resize(lwork);

  dsytrf_(&U, &N, mFisher.array(), &N, ipiv.array(), work.array(), &lwork, &info);
  if (info)
    {
      mFisher = std::numeric_limits<C_FLOAT64>::quiet_NaN();
      mParameterSD = std::numeric_limits<C_FLOAT64>::quiet_NaN();

      CCopasiMessage(CCopasiMessage::WARNING, MCFitting + 2, info);

      return false;
    }

  DebugFile << mFisher << std::endl;
  DebugFile << ipiv << std::endl;

  /* int dsytri_(char *uplo,
   *             integer *n,
   *             doublereal *a,
   *             integer * lda,
   *             integer *ipiv,
   *             doublereal *work,
   *             integer *info);
   *
   *  -- LAPACK routine (version 3.0) --
   *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
   *     Courant Institute, Argonne National Lab, and Rice University
   *     March 31, 1993
   *
   *  Purpose
   *  =======
   *
   *  DSYTRI computes the inverse of a real symmetric indefinite matrix
   *  A using the factorization A = U*D*U**T or A = L*D*L**T computed by
   *  DSYTRF.
   *
   *  Arguments
   *  =========
   *
   *  UPLO    (input) CHARACTER*1
   *          Specifies whether the details of the factorization are stored
   *          as an upper or lower triangular matrix.
   *          = 'U':  Upper triangular, form is A = U*D*U**T;
   *          = 'L':  Lower triangular, form is A = L*D*L**T.
   *
   *  N       (input) INTEGER
   *          The order of the matrix A.  N >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the block diagonal matrix D and the multipliers
   *          used to obtain the factor U or L as computed by DSYTRF.
   *
   *          On exit, if INFO = 0, the (symmetric) inverse of the original
   *          matrix.  If UPLO = 'U', the upper triangular part of the
   *          inverse is formed and the part of A below the diagonal is not
   *          referenced; if UPLO = 'L' the lower triangular part of the
   *          inverse is formed and the part of A above the diagonal is
   *          not referenced.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,N).
   *
   *  IPIV    (input) INTEGER array, dimension (N)
   *          Details of the interchanges and the block structure of D
   *          as determined by DSYTRF.
   *
   *  WORK    (workspace) DOUBLE PRECISION array, dimension (N)
   *
   *  INFO    (output) INTEGER
   *          = 0: successful exit
   *          < 0: if INFO = -i, the i-th argument had an illegal value
   *          > 0: if INFO = i, D(i,i) = 0; the matrix is singular and its
   *               inverse could not be computed.
   *
   */
  dsytri_(&U, &N, mFisher.array(), &N, ipiv.array(), work.array(), &info);
  if (info)
    return false; // :TODO: create error message
#endif // XXXX

  DebugFile << mFisher << std::endl;

  // rescale the lower bound of the covariant matrix to have unit diagonal
  for (i = 0; i < imax; i++)
    {
      C_FLOAT64 & tmp = mFisher(i, i);

      tmp = sqrt(tmp);
      mParameterSD[i] = mSD * tmp;
    }

  for (i = 0; i < imax; i++)
    for (l = 0; l < i; l++)
      {
        mFisher(i, l) /= mFisher(i, i) * mFisher(l, l);
        mFisher(l, i) = mFisher(i, l);
      }

  for (i = 0; i < imax; i++)
    mFisher(i, i) = 1.0;

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

const CMatrix< C_FLOAT64 > & CFitProblem::getVariableCorrelations() const
  {return mFisher;}

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

void CFitProblem::initObjects()
{
  addObjectReference("Cross Validation Solution", mCrossValidationSolutionValue, CCopasiObject::ValueDbl);
  addObjectReference("Cross Validation Objective", mCrossValidationObjective, CCopasiObject::ValueDbl);
}

bool CFitProblem::calculateCrossValidation()
{
  mCounter += 1;
  bool Continue = true;

  unsigned i, imax = mpCrossValidationSet->getExperimentCount();
  unsigned j, jmax = mpOptItems->size();
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
                  Continue &= mpSteadyState->process(true);

                  if (!Continue)
                    {
                      CalculateValue = mInfinity;
                      break;
                    }

                  // We check after each simulation whether the constraints are violated.
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
              ppConstraintEnd = ppConstraint + mCrossValidationConstraints.numCols();
              for (; ppConstraint != ppConstraintEnd; ++ppConstraint)
                if (*ppConstraint) (*ppConstraint)->checkConstraint();
              break;

            default:
              break;
            }

          // restore independent data
          pExp->restoreModelIndependentData();

          switch (pExp->getExperimentType())
            {
            case CCopasiTask::steadyState:
              mpSteadyState->restore();
              break;

            case CCopasiTask::timeCourse:
              mpTrajectory->restore();
              break;

            default:
              break;
            }
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
