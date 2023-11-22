// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"
#include "CMCAProblem.h"
#include "CMCATask.h"
#include "CSteadyStateTask.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/report/CKeyFactory.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CMCAProblem::CMCAProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::mca, pParent)
{
  //  assertParameter("SteadyStateRequested", CCopasiParameter::Type::BOOL, true);
  assertParameter("Steady-State", CCopasiParameter::Type::KEY, std::string(""));
  setSteadyStateRequested(true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CMCAProblem &" src
 */
CMCAProblem::CMCAProblem(const CMCAProblem & src,
                         const CDataContainer * pParent):
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
      configBuffer.getVariable("RepxSteadyStateAnalysis", "bool",
                               &SteadyStateRequested,
                               CReadConfig::LOOP);

      setSteadyStateRequested(SteadyStateRequested);
    }
}

/**
 * Set whether the steady state analysis is requested.
 * @param bool * steadyStateRequested
 */
void CMCAProblem::setSteadyStateRequested(const bool & steadyStateRequested)
{
  CSteadyStateTask * pSubTask = nullptr;
  CDataModel* pDataModel = getObjectDataModel();

  if (pDataModel != nullptr
      && pDataModel->getTaskList())
    pSubTask = dynamic_cast<CSteadyStateTask *>(&pDataModel->getTaskList()->operator[]("Steady-State"));

  if (steadyStateRequested
      && pSubTask != nullptr)
    setValue("Steady-State", pSubTask->getKey());
  else
    setValue("Steady-State", std::string(""));
}

/**
 * Retrieve whether the steady state analysis is requested.
 * @return bool steadyStateRequested
 */
bool CMCAProblem::isSteadyStateRequested() const
{
  return (getValue< std::string >("Steady-State") != "");
}

CCopasiTask * CMCAProblem::getSubTask() const
{
  CCopasiTask * pSubTask = nullptr;

  if (isSteadyStateRequested())
    {
      pSubTask = dynamic_cast< CCopasiTask * >(CRootContainer::getKeyFactory()->get(getValue< std::string >("Steady-State")));

      if (pSubTask == nullptr)
        {
          CDataModel * pDataModel = getObjectDataModel();

          if (pDataModel != nullptr
              && pDataModel->getTaskList())
            pSubTask = dynamic_cast< CCopasiTask * >(&pDataModel->getTaskList()->operator[]("Steady-State"));
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
