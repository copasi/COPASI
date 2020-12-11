// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CTaskFactory.h"

#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/elementaryFluxModes/CEFMTask.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/steadystate/CMCATask.h"
#include "copasi/lna/CLNATask.h"
#include "copasi/lyap/CLyapTask.h"
#include "copasi/sensitivities/CSensTask.h"
#include "copasi/tssanalysis/CTSSATask.h"
#include "copasi/moieties/CMoietiesTask.h"
#include "copasi/crosssection/CCrossSectionTask.h"
#include "copasi/timesens/CTimeSensTask.h"

#ifdef WITH_ANALYTICS
# include "analytics/CAnalyticsTask.h"
#endif // WITH_ANALYTICS

// static
CCopasiTask * CTaskFactory::createTask(const CTaskEnum::Task & type, const CDataContainer * pParent)
{
  CCopasiTask * pTask = NULL;

  switch (type)
    {
      case CTaskEnum::Task::steadyState:
        pTask = new CSteadyStateTask(pParent);
        break;

      case CTaskEnum::Task::timeCourse:
        pTask = new CTrajectoryTask(pParent);
        break;

      case CTaskEnum::Task::scan:
        pTask = new CScanTask(pParent);
        break;

      case CTaskEnum::Task::fluxMode:
        pTask = new CEFMTask(pParent);
        break;

      case CTaskEnum::Task::optimization:
        pTask = new COptTask(pParent);
        break;

      case CTaskEnum::Task::parameterFitting:
        pTask = new CFitTask(pParent);
        break;

      case CTaskEnum::Task::mca:
        pTask = new CMCATask(pParent);
        break;

      case CTaskEnum::Task::lna:
        pTask = new CLNATask(pParent);
        break;

      case CTaskEnum::Task::lyap:
        pTask = new CLyapTask(pParent);
        break;

      case CTaskEnum::Task::sens:
        pTask = new CSensTask(pParent);
        break;

      case CTaskEnum::Task::tssAnalysis:
        pTask = new CTSSATask(pParent);
        break;

      case CTaskEnum::Task::moieties:
        pTask = new CMoietiesTask(pParent);
        break;

      case CTaskEnum::Task::crosssection:
        pTask = new CCrossSectionTask(pParent);
        break;

#ifdef  WITH_ANALYTICS

      case CTaskEnum::Task::analytics:
        pTask = new CAnalyticsTask(pParent);
        break;
#endif // WITH_ANALYTICS

      case CTaskEnum::Task::timeSens:
        pTask = new CTimeSensTask(pParent);
        break;

      default:
        break;
    }

  if (pTask != NULL)
    {
      const_cast< CDataContainer * >(pParent)->add(pTask, true);
    }

  return pTask;
}

// static
CCopasiTask * CTaskFactory::copyTask(const CCopasiTask * pSrc, const CDataContainer * pParent)
{
  if (pSrc == NULL)
    return NULL;

  CCopasiTask * pCopy = NULL;

  switch (pSrc->getType())
    {
      case CTaskEnum::Task::steadyState:
        pCopy = new CSteadyStateTask(*static_cast< const CSteadyStateTask * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::timeCourse:
        pCopy = new CTrajectoryTask(pParent);
        break;

      case CTaskEnum::Task::scan:
        pCopy = new CScanTask(pParent);
        break;

      case CTaskEnum::Task::fluxMode:
        pCopy = new CEFMTask(pParent);
        break;

      case CTaskEnum::Task::optimization:
        pCopy = new COptTask(pParent);
        break;

      case CTaskEnum::Task::parameterFitting:
        pCopy = new CFitTask(pParent);
        break;

      case CTaskEnum::Task::mca:
        pCopy = new CMCATask(pParent);
        break;

      case CTaskEnum::Task::lna:
        pCopy = new CLNATask(pParent);
        break;

      case CTaskEnum::Task::lyap:
        pCopy = new CLyapTask(pParent);
        break;

      case CTaskEnum::Task::sens:
        pCopy = new CSensTask(pParent);
        break;

      case CTaskEnum::Task::tssAnalysis:
        pCopy = new CTSSATask(pParent);
        break;

      case CTaskEnum::Task::moieties:
        pCopy = new CMoietiesTask(pParent);
        break;

      case CTaskEnum::Task::crosssection:
        pCopy = new CCrossSectionTask(pParent);
        break;

#ifdef  WITH_ANALYTICS

      case CTaskEnum::Task::analytics:
        pCopy = new CAnalyticsTask(pParent);
        break;
#endif // WITH_ANALYTICS

      case CTaskEnum::Task::timeSens:
        pCopy = new CTimeSensTask(pParent);
        break;

      default:
        break;
    }

  return pCopy;
}
