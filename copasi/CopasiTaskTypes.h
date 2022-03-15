// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 * This file is a convenience header that includes the core COPASI Task types
 */

#ifndef COPASI_TASK_TYPES_H
#define COPASI_TASK_TYPES_H

#include <copasi/trajectory/CTrajectoryTask.h>
#include <copasi/trajectory/CTrajectoryProblem.h>
#include <copasi/trajectory/CLsodaMethod.h>
#include <copasi/trajectory/CStochMethod.h>
#include <copasi/trajectory/CTimeSeries.h>

#include <copasi/moieties/CMoietiesTask.h>
#include <copasi/moieties/CMoietiesProblem.h>
#include <copasi/moieties/CMoietiesMethod.h>

#include <copasi/crosssection/CCrossSectionTask.h>
#include <copasi/crosssection/CCrossSectionProblem.h>
#include <copasi/crosssection/CCrossSectionMethod.h>

#include <copasi/elementaryFluxModes/CEFMTask.h>
#include <copasi/elementaryFluxModes/CEFMProblem.h>
#include <copasi/elementaryFluxModes/CEFMMethod.h>

#include <copasi/lna/CLNATask.h>
#include <copasi/lna/CLNAProblem.h>
#include <copasi/lna/CLNAMethod.h>

#include <copasi/lyap/CLyapTask.h>
#include <copasi/lyap/CLyapProblem.h>
#include <copasi/lyap/CLyapMethod.h>

#include <copasi/optimization/COptTask.h>
#include <copasi/optimization/COptProblem.h>
#include <copasi/optimization/COptMethod.h>
#include <copasi/optimization/COptMethodCoranaWalk.h>
#include <copasi/optimization/COptMethodDE.h>
#include <copasi/optimization/COptMethodEP.h>
#include <copasi/optimization/COptMethodGA.h>
#include <copasi/optimization/COptMethodGASR.h>
#include <copasi/optimization/COptMethodHookeJeeves.h>
#include <copasi/optimization/COptMethodLevenbergMarquardt.h>
#include <copasi/optimization/COptMethodNelderMead.h>
#include <copasi/optimization/COptMethodPraxis.h>
#include <copasi/optimization/COptMethodPS.h>
#include <copasi/optimization/COptMethodSA.h>
#include <copasi/optimization/COptMethodSRES.h>
#include <copasi/optimization/COptMethodSS.h>
#include <copasi/optimization/COptMethodStatistics.h>
#include <copasi/optimization/COptMethodSteepestDescent.h>

#include <copasi/optimization/COptItem.h>

#include <copasi/parameterFitting/CFitTask.h>
#include <copasi/parameterFitting/CFitProblem.h>
#include <copasi/parameterFitting/CFitItem.h>

#include <copasi/parameterFitting/CExperiment.h>
#include <copasi/parameterFitting/CExperimentFileInfo.h>
#include <copasi/parameterFitting/CExperimentObjectMap.h>
#include <copasi/parameterFitting/CExperimentSet.h>

#include <copasi/scan/CScanTask.h>
#include <copasi/scan/CScanProblem.h>
#include <copasi/scan/CScanTask.h>

#include <copasi/sensitivities/CSensTask.h>
#include <copasi/sensitivities/CSensProblem.h>
#include <copasi/sensitivities/CSensMethod.h>

#include <copasi/steadystate/CSteadyStateTask.h>
#include <copasi/steadystate/CSteadyStateProblem.h>
#include <copasi/steadystate/CSteadyStateMethod.h>

#include <copasi/steadystate/CMCATask.h>
#include <copasi/steadystate/CMCAProblem.h>
#include <copasi/steadystate/CMCAMethod.h>

#include <copasi/tssanalysis/CTSSATask.h>
#include <copasi/tssanalysis/CTSSAProblem.h>
#include <copasi/tssanalysis/CTSSAMethod.h>

#include <copasi/timesens/CTimeSensTask.h>
#include <copasi/timesens/CTimeSensProblem.h>
#include <copasi/timesens/CTimeSensMethod.h>

#include <copasi/sbml/CSBMLExporter.h>
#include <copasi/sbml/SBMLImporter.h>

#include <copasi/sedml/SEDMLImporter.h>
#include <copasi/sedml/SEDMLUtils.h>
#include <copasi/sedml/CSEDMLExporter.h>

#endif // COPASI_TASK_TYPES_H
