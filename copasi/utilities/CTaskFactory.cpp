// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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

#ifdef WITH_ANALYTICS
# include "analytics/CAnalyticsTask.h"
#endif // WITH_ANALYTICS

// static
CCopasiTask * CTaskFactory::createTask(const CTaskEnum::Task & type, const CCopasiContainer * pParent)
{
  CCopasiTask * pTask = NULL;

  switch (type)
    {
      case CTaskEnum::steadyState:
        pTask = new CSteadyStateTask(pParent);
        break;

      case CTaskEnum::timeCourse:
        pTask = new CTrajectoryTask(pParent);
        break;

      case CTaskEnum::scan:
        pTask = new CScanTask(pParent);
        break;

      case CTaskEnum::fluxMode:
        pTask = new CEFMTask(pParent);
        break;

      case CTaskEnum::optimization:
        pTask = new COptTask(pParent);
        break;

      case CTaskEnum::parameterFitting:
        pTask = new CFitTask(pParent);
        break;

      case CTaskEnum::mca:
        pTask = new CMCATask(pParent);
        break;

      case CTaskEnum::lna:
        pTask = new CLNATask(pParent);
        break;

      case CTaskEnum::lyap:
        pTask = new CLyapTask(pParent);
        break;

      case CTaskEnum::sens:
        pTask = new CSensTask(pParent);
        break;

      case CTaskEnum::tssAnalysis:
        pTask = new CTSSATask(pParent);
        break;

      case CTaskEnum::moieties:
        pTask = new CMoietiesTask(pParent);
        break;

      case CTaskEnum::crosssection:
        pTask = new CCrossSectionTask(pParent);
        break;

#ifdef  WITH_ANALYTICS

      case CTaskEnum::analytics:
        pTask = new CAnalyticsTask(pParent);
        break;
#endif // WITH_ANALYTICS

      default:
        break;
    }

  if (pTask != NULL)
    {
      const_cast< CCopasiContainer * >(pParent)->add(pTask, true);
    }

  return pTask;
}
