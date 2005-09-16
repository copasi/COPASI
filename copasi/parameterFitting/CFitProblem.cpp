/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitProblem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/16 19:08:34 $
   End CVS Header */

#include "copasi.h"

#include "CFitProblem.h"

#include "optimization/COptItem.h"
 #include "steadystate/CSteadyStateTask.h"
 #include "trajectory/CTrajectoryTask.h"
 #include "utilities/CProcessReport.h"

//  Default constructor
CFitProblem::CFitProblem(const CCopasiTask::Type & type,
                         const CCopasiContainer * pParent):
    COptProblem(type, pParent)
{
  removeParameter("ObjectiveFunction");
  removeParameter("Maximize");

  addGroup("ExperimentSet");
}

// copy constructor
CFitProblem::CFitProblem(const CFitProblem& src,
                         const CCopasiContainer * pParent):
    COptProblem(src, pParent)
{}

// Destructor
CFitProblem::~CFitProblem()
{}

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
  /* :TODO: */

  mCounter += 1;
  bool success = false;

  try
    {
      if (mpSteadyState != NULL)
        success = mpSteadyState->process(true);

      if (mpTrajectory != NULL)
        success = mpTrajectory->process(true);

      mCalculateValue = mpFunction->calcValue();
    }

  catch (...)
    {
      success = false;
    }

  if (!success) mCalculateValue = DBL_MAX;

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
    o.mOptItemList.begin();
  std::vector< COptItem * >::const_iterator endItem =
    o.mOptItemList.end();

  for (; itItem != endItem; ++itItem)
    os << "    " << **itItem << std::endl;

  return os;
}
