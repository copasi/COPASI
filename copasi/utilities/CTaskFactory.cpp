// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CTaskFactory.h"

#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "scan/CScanTask.h"
#include "elementaryFluxModes/CEFMTask.h"
#include "optimization/COptTask.h"
#include "parameterFitting/CFitTask.h"
#include "steadystate/CMCATask.h"
#include "lna/CLNATask.h"
#include "lyap/CLyapTask.h"
#include "sensitivities/CSensTask.h"
#include "tssanalysis/CTSSATask.h"
#include "moieties/CMoietiesTask.h"
#include "crosssection/CCrossSectionTask.h"
#include "timesens/CTimeSensTask.h"

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
