// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/copasi.h"

#include "CProblemFactory.h"

#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/scan/CScanProblem.h"
#include "copasi/elementaryFluxModes/CEFMProblem.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/steadystate/CMCAProblem.h"
#include "copasi/lna/CLNAProblem.h"
#include "copasi/lyap/CLyapProblem.h"
#include "copasi/sensitivities/CSensProblem.h"
#include "copasi/tssanalysis/CTSSAProblem.h"
#include "copasi/moieties/CMoietiesProblem.h"
#include "copasi/crosssection/CCrossSectionProblem.h"
#include "copasi/timesens/CTimeSensProblem.h"

#ifdef WITH_ANALYTICS
#  include "analytics/CAnalyticsProblem.h"
#endif // WITH_ANALYTICS

// static
CCopasiProblem * CProblemFactory::create(const CTaskEnum::Task & type, const CDataContainer * pParent)
{
  CCopasiProblem * pProblem = NULL;

  switch (type)
    {
      case CTaskEnum::Task::steadyState:
        pProblem = new CSteadyStateProblem(pParent);
        break;

      case CTaskEnum::Task::timeCourse:
        pProblem = new CTrajectoryProblem(pParent);
        break;

      case CTaskEnum::Task::scan:
        pProblem = new CScanProblem(pParent);
        break;

      case CTaskEnum::Task::fluxMode:
        pProblem = new CEFMProblem(pParent);
        break;

      case CTaskEnum::Task::optimization:
        pProblem = new COptProblem(CTaskEnum::Task::optimization, pParent);
        break;

      case CTaskEnum::Task::parameterFitting:
        pProblem = new CFitProblem(CTaskEnum::Task::parameterFitting, pParent);
        break;

      case CTaskEnum::Task::mca:
        pProblem = new CMCAProblem(pParent);
        break;

      case CTaskEnum::Task::lna:
        pProblem = new CLNAProblem(pParent);
        break;

      case CTaskEnum::Task::lyap:
        pProblem = new CLyapProblem(pParent);
        break;

      case CTaskEnum::Task::sens:
        pProblem = new CSensProblem(pParent);
        break;

      case CTaskEnum::Task::tssAnalysis:
        pProblem = new CTSSAProblem(pParent);
        break;

      case CTaskEnum::Task::moieties:
        pProblem = new CMoietiesProblem(CTaskEnum::Task::moieties, pParent);
        break;

      case CTaskEnum::Task::crosssection:
        pProblem = new CCrossSectionProblem(pParent);
        break;

#ifdef WITH_ANALYTICS

      case CTaskEnum::Task::analytics:
        pProblem = new CAnalyticsProblem(pParent);
        break;
#endif // WITH_ANALYTICS

      case CTaskEnum::Task::timeSens:
        pProblem = new CTimeSensProblem(pParent);
        break;

      default:
        break;
    }

  if (pProblem != NULL
      && dynamic_cast< CCopasiTask * >(pProblem->getObjectParent()) != NULL)
    pProblem->setMathContainer(static_cast< CCopasiTask * >(pProblem->getObjectParent())->getMathContainer());

  return pProblem;
}

// static
CCopasiProblem * CProblemFactory::copy(const CCopasiProblem * pSrc, const CDataContainer * pParent)
{
  if (pSrc == NULL)
    return NULL;

  CCopasiProblem * pCopy = NULL;

  switch (pSrc->getType())
    {
      case CTaskEnum::Task::steadyState:
        pCopy = new CSteadyStateProblem(*static_cast< const CSteadyStateProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::timeCourse:
        pCopy = new CTrajectoryProblem(*static_cast< const CTrajectoryProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::scan:
        pCopy = new CScanProblem(*static_cast< const CScanProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::fluxMode:
        pCopy = new CEFMProblem(*static_cast< const CEFMProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::optimization:
        pCopy = new COptProblem(*static_cast< const COptProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::parameterFitting:
        pCopy = new CFitProblem(*static_cast< const CFitProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::mca:
        pCopy = new CMCAProblem(*static_cast< const CMCAProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::lna:
        pCopy = new CLNAProblem(*static_cast< const CLNAProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::lyap:
        pCopy = new CLyapProblem(*static_cast< const CLyapProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::sens:
        pCopy = new CSensProblem(*static_cast< const CSensProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::tssAnalysis:
        pCopy = new CTSSAProblem(*static_cast< const CTSSAProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::moieties:
        pCopy = new CMoietiesProblem(*static_cast< const CMoietiesProblem * >(pSrc), pParent);
        break;

      case CTaskEnum::Task::crosssection:
        pCopy = new CCrossSectionProblem(*static_cast< const CCrossSectionProblem * >(pSrc), pParent);
        break;

#ifdef WITH_ANALYTICS

      case CTaskEnum::Task::analytics:
        pCopy = new CAnalyticsProblem(*static_cast< const CAnalyticsProblem * >(pSrc), pParent);
        break;
#endif // WITH_ANALYTICS

      case CTaskEnum::Task::timeSens:
        pCopy = new CTimeSensProblem(*static_cast< const CTimeSensProblem * >(pSrc), pParent);
        break;

      default:
        break;
    }

  if (pCopy != NULL
      && dynamic_cast< CCopasiTask * >(pCopy->getObjectParent()) != NULL)
    pCopy->setMathContainer(static_cast< CCopasiTask * >(pCopy->getObjectParent())->getMathContainer());

  return pCopy;
}
