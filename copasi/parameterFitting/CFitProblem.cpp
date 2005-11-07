/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/07 20:39:50 $
   End CVS Header */

#include "copasi.h"

#include "CFitProblem.h"
#include "CFitItem.h"
#include "CFitTask.h"
#include "CExperimentSet.h"
#include "CExperiment.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "optimization/COptItem.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "utilities/CProcessReport.h"

//  Default constructor
CFitProblem::CFitProblem(const CCopasiTask::Type & type,
                         const CCopasiContainer * pParent):
    COptProblem(type, pParent),
    mpExperimentSet(NULL),
    mpTrajectoryProblem(NULL),
    mpInitialState(NULL)
{initializeParameter();}

// copy constructor
CFitProblem::CFitProblem(const CFitProblem& src,
                         const CCopasiContainer * pParent):
    COptProblem(src, pParent),
    mpExperimentSet(NULL),
    mpTrajectoryProblem(NULL),
    mpInitialState(NULL)
{initializeParameter();}

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

  elevateChildren();
}

bool CFitProblem::elevateChildren()
{
  // This call is necessarry since CFitProblem is derived from COptProblem.
  if (!COptProblem::elevateChildren()) return false;

  std::map<std::string, std::string> KeyMap;

  std::vector<CCopasiParameter *> * pExperiments =
    getGroup("Experiment Set")->CCopasiParameter::getValue().pGROUP;
  std::vector<CCopasiParameter *>::iterator itExp;
  std::vector<CCopasiParameter *>::iterator endExp;

  for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
    if (static_cast<CCopasiParameterGroup *>(*itExp)->getValue("Key").pKEY)
      KeyMap[*static_cast<CCopasiParameterGroup *>(*itExp)->getValue("Key").pKEY] =
        (*itExp)->getObjectName();

  mpExperimentSet =
    elevate<CExperimentSet, CCopasiParameterGroup>(getGroup("Experiment Set"));
  if (!mpExperimentSet) return false;

  std::map<std::string, std::string>::iterator itMap;
  std::map<std::string, std::string>::iterator endMap;
  CExperiment * pExperiment;
  for (itMap = KeyMap.begin(), endMap = KeyMap.end(); itMap != endMap; ++itMap)
    {
      pExperiment = mpExperimentSet->getExperiment(itMap->second);
      itMap->second = pExperiment->CCopasiParameter::getKey();
      pExperiment->setValue("Key", itMap->second);
    }

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  for (; it != end; ++it)
    {
      if (!((*it) = elevate<CFitItem, COptItem>(*it)))
        return false;

      pExperiments =
        (*it)->getParameter("Affected Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(KeyMap[*(*itExp)->getValue().pKEY]);
    }

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  for (; it != end; ++it)
    {
      if (!((*it) = elevate<CFitItem, COptItem>(*it)))
        return false;

      pExperiments =
        (*it)->getParameter("Affected Experiments")->getValue().pGROUP;

      for (itExp = pExperiments->begin(), endExp = pExperiments->end(); itExp != endExp; ++itExp)
        (*itExp)->setValue(KeyMap[*(*itExp)->getValue().pKEY]);
    }

  return true;
}

bool CFitProblem::setModel(CModel * pModel)
{return COptProblem::setModel(pModel);}

bool CFitProblem::setCallBack(CProcessReport * pCallBack)
{return COptProblem::setCallBack(pCallBack);}

bool CFitProblem::initialize()
{
  if (!COptProblem::initialize())
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCOptimization + 5)
        return false;
      else
        CCopasiMessage::getLastMessage();
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
  mExperimentUpdateMethods.resize(mpExperimentSet->size(),
                                  mpOptItems->size());
  mExperimentUpdateMethods = NULL;

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  CFitItem * pItem;
  unsigned C_INT32 i, imax;
  unsigned C_INT32 j;
  unsigned C_INT32 Index;

  for (j = 0; it != end; ++it, j++)
    {
      pItem = static_cast<CFitItem *>(*it);
      imax = pItem->getExperimentCount();
      if (imax == 0)
        {
          for (i = 0, imax = mpExperimentSet->size(); i < imax; i++)
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

  pdelete(mpTrajectoryProblem);
  mpTrajectoryProblem =
    new CTrajectoryProblem(*static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem()));

  static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem())->setStepNumber(1);

  pdelete(mpInitialState);
  mpInitialState = new CState(mpModel->getInitialState());

  return true;
}

bool CFitProblem::restore()
{
  *mpTrajectory->getProblem() = *mpTrajectoryProblem;
  pdelete(mpTrajectoryProblem);

  pdelete(mpInitialState);

  COptProblem::restore();
  return true;
}

/**
 * calculate() decides whether the problem is a steady state problem or a
 * trajectory problem based on whether the pointer to that type of problem
 * is null or not.  It then calls the process() method for that type of 
 * problem.  Currently process takes ofstream& as a parameter but it will
 * change so that process() takes no parameters.
 */
bool CFitProblem::calculate()
{
  mCounter += 1;
  bool Continue = true;

  unsigned i, imax = mpExperimentSet->size();
  unsigned j, jmax = mpOptItems->size();
  unsigned kmax;
  mCalculateValue = 0.0;

  CTrajectoryProblem * pProblem =
    static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem());
  CExperiment * pExp;

  try
    {
      for (i = 0; i < imax && Continue; i++) // For each experiment
        {
          pExp = mpExperimentSet->getExperiment(i);

          mpModel->setInitialState(mpInitialState);

          // set the global and experiment local fit item values.
          for (j = 0; j < jmax; j++)
            if (mExperimentUpdateMethods(i, j))
              (*mExperimentUpdateMethods(i, j))(static_cast<CFitItem *>((*mpOptItems)[j])->getLocalValue());

          kmax = pExp->getNumDataRows();

          for (j = 0; j < kmax && Continue; j++) // For each data row;
            {
              switch (pExp->getExperimentType())
                {
                case CCopasiTask::steadyState:
                  // set independent data
                  pExp->updateModelWithIndependentData(j);
                  Continue = mpSteadyState->process(true);
                  break;

                case CCopasiTask::timeCourse:
                  if (j)
                    {
                      pProblem->setEndTime(pExp->getTimeData()[j]);
                      pProblem->setStartTime(pExp->getTimeData()[j - 1]);
                      Continue = mpTrajectory->process(false);
                    }
                  else
                    {
                      // set independent data
                      pExp->updateModelWithIndependentData(j);
                      pProblem->setStartTime(pExp->getTimeData()[j]);
                      mpModel->setState(&mpModel->getInitialState());
                    }
                  break;

                default:
                  break;
                }

              mCalculateValue += pExp->sumOfSquares(j);
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
            }
        }
    }

  catch (...)
    {
      mCalculateValue = DBL_MAX;
      pExp->restoreModelIndependentData();
    }

  if (mpCallBack) return mpCallBack->progress(mhCounter);

  return true;
}

void CFitProblem::print(std::ostream * ostream) const
{*ostream << *this;}

void CFitProblem::printResult(std::ostream * ostream) const
  {COptProblem::printResult(ostream);}

std::ostream &operator<<(std::ostream &os, const CFitProblem & o)
{
  os << "Problem Description:" << std::endl;

  os << "Subtask: " << std::endl;

  if (o.mpSteadyState)
    o.mpSteadyState->getDescription().print(&os);
  else if (o.mpTrajectory)
    o.mpTrajectory->getDescription().print(&os);
  else
    os << "No Subtask specified.";

  os << std::endl;

  os << "List of Optimization Items:" << std::endl;

  std::vector< COptItem * >::const_iterator itItem =
    o.mpOptItems->begin();
  std::vector< COptItem * >::const_iterator endItem =
    o.mpOptItems->end();

  for (; itItem != endItem; ++itItem)
    os << "    " << **itItem << std::endl;

  return os;
}

bool CFitProblem::createObjectiveFunction()
{return true;}
