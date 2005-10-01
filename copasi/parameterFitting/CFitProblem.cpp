/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/01 03:02:53 $
   End CVS Header */

#include "copasi.h"

#include "CFitProblem.h"
#include "CFitItem.h"
#include "CFitTask.h"
#include "CExperimentSet.h"
#include "CExperiment.h"

#include "model/CModel.h"
#include "optimization/COptItem.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "utilities/CProcessReport.h"

//  Default constructor
CFitProblem::CFitProblem(const CCopasiTask::Type & type,
                         const CCopasiContainer * pParent):
    COptProblem(type, pParent),
    mpExperimentSet(NULL)
{}

// copy constructor
CFitProblem::CFitProblem(const CFitProblem& src,
                         const CCopasiContainer * pParent):
    COptProblem(src, pParent),
    mpExperimentSet(NULL)
{}

// Destructor
CFitProblem::~CFitProblem()
{}

void CFitProblem::initializeParameter()
{
  removeParameter("ObjectiveFunction");
  removeParameter("Maximize");

  assertGroup("Experiment Set");

  elevateChildren();
}

bool CFitProblem::elevateChildren()
{
  mpExperimentSet =
    elevate<CExperimentSet, CCopasiParameterGroup>(getGroup("Experiment Set"));
  if (!mpExperimentSet) return false;

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  for (; it != end; ++it)
    if (!((*it) = elevate<CFitItem, COptItem>(*it))) return false;

  it = mpConstraintItems->begin();
  end = mpConstraintItems->end();

  for (; it != end; ++it)
    if (!((*it) = elevate<CFitItem, COptItem>(*it))) return false;

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
  mExperimentUpdateMethods.resize(mpExperimentSet->size());

  std::vector<COptItem * >::iterator it = mpOptItems->begin();
  std::vector<COptItem * >::iterator end = mpOptItems->end();

  CFitItem * pItem;
  unsigned i, imax;
  for (; it != end; ++it)
    {
      pItem = static_cast<CFitItem *>(*it);
      imax = pItem->getExperimentCount();
      if (imax == 0)
        {
          for (i = 0, imax = mpOptItems->size(); i < imax; i++)
            mExperimentUpdateMethods[i].push_back(pItem->COptItem::getUpdateMethod());
        }
      else
        {
          for (i = 0; i < imax; i++)
            // :TODO: map the experiment key to an experiment index
            // mExperimentUpdateMethods[pItem->getExperiment(i)].push_back(pItem->COptItem::getUpdateMethod();
;
        }
    }

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
  // :TODO: implmement me!

  mCounter += 1;
  bool Continue = true;

  unsigned i, imax = mpExperimentSet->size();
  unsigned j, jmax;
  mCalculateValue = 0.0;

  CTrajectoryProblem * pProblem =
    static_cast<CTrajectoryProblem *>(mpTrajectory->getProblem());

  try
    {
      for (i = 0; i < imax && Continue; i++) // For each experiment
        {
          CExperiment & Exp = *mpExperimentSet->getExperiment(i);

          // :TODO: set the global fit item values.
          // :TODO: set the experiment local fit item values.

          jmax = Exp.getNumRows();

          for (j = 0; j < jmax && Continue; j++) // For each data row;
            {
              // :TODO: set independent data

              switch (Exp.getExperimentType())
                {
                case CCopasiTask::steadyState:
                  Continue = mpSteadyState->process(true);
                  break;

                case CCopasiTask::timeCourse:
                  pProblem->setEndTime(Exp.getTimeData()[j]);
                  Continue = mpTrajectory->process(j ? false : true);
                  break;

                default:
                }

              mCalculateValue += Exp.sumOfSquares(j);
            }
        }
    }

  catch (...)
    {
      mCalculateValue = DBL_MAX;
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
