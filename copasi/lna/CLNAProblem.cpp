// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 *  CLNAProblem class.
 *  This class describes the LNA analysis problem.
 *
 *  Created for Copasi by Juergen Pahle 2010
 */

#include <string>

#include "copasi.h"
#include "CLNAProblem.h"
#include "CLNATask.h"
#include "steadystate/CSteadyStateTask.h"

#include "model/CModel.h"
#include "model/CState.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiRootContainer.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CLNAProblem::CLNAProblem(const CCopasiContainer * pParent):
  CCopasiProblem(CTaskEnum::lna, pParent)
{
  addParameter("Steady-State", CCopasiParameter::KEY, std::string(""));
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CLNAProblem &" src
 */
CLNAProblem::CLNAProblem(const CLNAProblem & src,
                         const CCopasiContainer * pParent):
  CCopasiProblem(src, pParent)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CLNAProblem::~CLNAProblem()
{DESTRUCTOR_TRACE;}

/**
 * Load a lna problem
 * @param "CReadConfig &" configBuffer
 */
void CLNAProblem::load(CReadConfig & configBuffer,
                       CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      bool SteadyStateRequested;
      configBuffer.getVariable("RepxSteadyStateAnalysis", "bool" ,
                               &SteadyStateRequested,
                               CReadConfig::LOOP);

      setSteadyStateRequested(SteadyStateRequested);
    }
}

/**
 * Set whether the steady state analysis is requested.
 * @param bool * steadyStateRequested
 */
void CLNAProblem::setSteadyStateRequested(const bool & steadyStateRequested)
{
  CSteadyStateTask * pSubTask = NULL;
  CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  if (pDataModel && pDataModel->getTaskList())
    pSubTask = dynamic_cast<CSteadyStateTask *>(&pDataModel->getTaskList()->operator[]("Steady-State"));

  if (steadyStateRequested && pSubTask)
    setValue("Steady-State", pSubTask->getKey());
  else
    setValue("Steady-State", std::string(""));
}

/**
 * Retrieve whether the steady state analysis is requested.
 * @return bool steadyStateRequested
 */
bool CLNAProblem::isSteadyStateRequested() const
{return (getValue< std::string >("Steady-State") != "");}

CSteadyStateTask * CLNAProblem::getSubTask() const
{
  if (isSteadyStateRequested())
    return dynamic_cast<CSteadyStateTask *>(CCopasiRootContainer::getKeyFactory()->get(getValue< std::string >("Steady-State")));
  else
    return NULL;
}

void CLNAProblem::printResult(std::ostream * ostream) const
{
  //this functionality is expected from the problem. However it is implemented in
  //the task.

  CLNATask* parent = dynamic_cast<CLNATask*>(getObjectParent());

  if (!parent) return;

  parent->printResult(ostream);
}

//print the description
std::ostream &operator<<(std::ostream &os, const CLNAProblem & o)
{
  os << "Problem Description:" << std::endl;

  if (o.isSteadyStateRequested())
    {
      os << "Calculation of a steady state is requested before the LNA." << std::endl << std::endl;

      if (o.getSubTask())
        {
          o.getSubTask()->getDescription().print(&os);
        }
      else
        {
          os << "However an error occurred. Please report this as a bug." << std::endl;
        }
    }
  else
    {
      os << "LNA is performed on the current state (which is not necessarily a steady state)." << std::endl;
    }

  os << std::endl;

  return os;
}

void CLNAProblem::print(std::ostream * ostream) const
{
  *ostream << *this;
}
