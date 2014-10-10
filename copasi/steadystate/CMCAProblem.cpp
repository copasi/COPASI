// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CMCAProblem class.
 *  This class describes the metabolic control analysis problem, i.e., it allows to specify
 *  for example initial conditions.
 *
 *  Created for Copasi by Ralph Gauges 2004
 */

#include <string>

#include "copasi.h"
#include "CMCAProblem.h"
#include "CMCATask.h"
#include "CSteadyStateTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "report/CKeyFactory.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CMCAProblem::CMCAProblem(const CCopasiContainer * pParent):
  CCopasiProblem(CCopasiTask::mca, pParent),
  mInitialState()
{
  //  addParameter("SteadyStateRequested", CCopasiParameter::BOOL, true);
  addParameter("Steady-State", CCopasiParameter::KEY, std::string(""));
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CMCAProblem &" src
 */
CMCAProblem::CMCAProblem(const CMCAProblem & src,
                         const CCopasiContainer * pParent):
  CCopasiProblem(src, pParent)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CMCAProblem::~CMCAProblem()
{DESTRUCTOR_TRACE;}

/**
 * Load a mca problem
 * @param "CReadConfig &" configBuffer
 */
void CMCAProblem::load(CReadConfig & configBuffer,
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
 * Set the initial state of the problem.
 * @param const CState & initialState
 */
void CMCAProblem::setInitialState(const CState & initialState)
{
  mInitialState = initialState;
}

#ifdef XXXX
/**
 * Set the initial state of the problem.
 * @param const CStateX & InitialState
 */
void CMCAProblem::setInitialState(const CStateX & initialState)
{
  mInitialState = initialState;
  mpContainer = const_cast<CModel *>(mInitialState.getModel());
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState &" pInitialState
 */
const CState & CMCAProblem::getInitialState() const
{return mInitialState;}
#endif // XXXX

/**
 * Set whether the steady state analysis is requested.
 * @param bool * steadyStateRequested
 */
void CMCAProblem::setSteadyStateRequested(const bool & steadyStateRequested)
{
  CSteadyStateTask * pSubTask = NULL;
  CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  if (pDataModel && pDataModel->getTaskList())
    pSubTask = dynamic_cast<CSteadyStateTask *>((*pDataModel->getTaskList())["Steady-State"]);

  if (steadyStateRequested && pSubTask)
    setValue("Steady-State", pSubTask->getKey());
  else
    setValue("Steady-State", std::string(""));
}

/**
 * Retrieve whether the steady state analysis is requested.
 * @return bool steadyStateRequested
 */
bool CMCAProblem::isSteadyStateRequested() const
{return (* getValue("Steady-State").pKEY != "");}

CSteadyStateTask * CMCAProblem::getSubTask() const
{
  CSteadyStateTask * pSubTask = NULL;

  if (isSteadyStateRequested())
    {
      pSubTask = dynamic_cast<CSteadyStateTask *>(CCopasiRootContainer::getKeyFactory()->get(* getValue("Steady-State").pKEY));

      if (pSubTask == NULL)
        {
          const CCopasiDataModel * pDataModel = getObjectDataModel();
          assert(pDataModel != NULL);

          if (pDataModel && pDataModel->getTaskList())
            {
              pSubTask = dynamic_cast<CSteadyStateTask *>((*pDataModel->getTaskList())["Steady-State"]);
            }
        }
    }

  return pSubTask;
}

void CMCAProblem::printResult(std::ostream * ostream) const
{
  //this functionality is expected from the problem. However it is implemented in
  //the task.

  CMCATask* parent = dynamic_cast<CMCATask*>(getObjectParent());

  if (!parent) return;

  parent->printResult(ostream);
}

//print the description
std::ostream &operator<<(std::ostream &os, const CMCAProblem & o)
{
  os << "Problem Description:" << std::endl;

  //os << "Subtask: " << std::endl;

  if (o.isSteadyStateRequested())
    {
      os << "Calculation of a steady state is requested before the MCA." << std::endl << std::endl;

      if (o.getSubTask())
        {
          //os << "" << std::endl;
          o.getSubTask()->getDescription().print(&os);
        }
      else
        {
          os << "However an error occurred. Please report this as a bug." << std::endl;
        }
    }
  else
    {
      os << "MCA is performed on the current state (which is not necessarily a steady state)." << std::endl;
    }

  os << std::endl;

  return os;
}

void CMCAProblem::print(std::ostream * ostream) const
{*ostream << *this;}
